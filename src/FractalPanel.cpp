#include "FractalFrame.h"

#ifdef __WXMSW__
    #include "CURSOR_CROSS.h"
#endif

enum{
    ID_ChangeSettings = 1
};

///Constructor
FractalPanel::FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *frac)
    :wxPanel(p, wxID_ANY, wxDefaultPosition, s, wxBORDER_RAISED),
     parent(p),f(frac),bmp(1,1,24){
    ///Initial settings
    /**Cursor*/{
        #ifdef __WXMSW__
            SetCursor(CURSOR_CROSS);
        #endif
    }
    //popupMenu_ = new wxMenu;
    //popupMenu_->Append(ID_ChangeSettings, "Change settings");
    /**Create fractal thread*/{
        if(CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR){ wxLogError("Could not create main thread"); return; }
        if(GetThread()->Run()              != wxTHREAD_NO_ERROR){ wxLogError("Could not run main thread"   ); return; }
    }
}

const FractalBitmap* FractalPanel::GetFractalBitmap() const{
    return f;
}

typedef std::chrono::high_resolution_clock hrclock;
wxThread::ExitCode FractalPanel::Entry(){
    /**Create fractal*/{
        f->reset(FractalBitmap::ComplexNum(FractalBitmap::complex_t(-0.75L),FractalBitmap::complex_t(0.0L)), //-0.75L,0.0L
            FractalBitmap::complex_t(5.0e-3), GetSize(), true); //5.0e-3
    }
    while(!GetThread()->TestDestroy()){
        {
            ///Update the fractal & measure time
            auto t1 = hrclock::now();
            f->UpdateMath();
            auto t2 = hrclock::now();
            auto dt = std::chrono::duration<long double>(t2-t1).count();
            /**Update values in ipanel for showing*/{
                parent->GetInfoPanel()->SetOrigin(f->GetOrigin());
                parent->GetInfoPanel()->SetStep(f->GetStep());
                parent->GetInfoPanel()->SetIterations(f->GetNum());
                parent->GetInfoPanel()->SetSecPerIter(dt/f->GetCyclesPerRun());
                parent->GetInfoPanel()->SetHorizontalSize(f->GetHorizontalSize());
            }
            /**Update ready-to-draw bitmap*/{
                std::lock_guard<std::mutex> lock3(bmpMutex);
                bmp = f->GetSubBitmap(wxRect(0, 0, f->GetWidth(), f->GetHeight()));
            }

        }
        ///Update screen
        CallAfter([this]{this->parent->Refresh(false);});
    }
    return (wxThread::ExitCode)0;
}

void FractalPanel::OnSizeEvent(wxSizeEvent&){
    f->reset(f->GetCenter(), f->GetStep(), this->GetSize(), true);
}

void FractalPanel::OnPaintEvent(wxPaintEvent&){
    std::lock_guard<std::mutex> lock(bmpMutex);

    wxPaintDC dc(this);
    dc.DrawBitmap(bmp, 0, 0, true);
}

void FractalPanel::OnZoomEvent(wxMouseEvent& evt){
    wxPoint p = wxGetMousePosition() - GetScreenPosition();
    FractalBitmap::ComplexNum newcenter = f->GetOrigin() + FractalBitmap::ComplexNum(
        FractalBitmap::complex_t(p.x)*f->GetStep(), FractalBitmap::complex_t(-p.y)*f->GetStep()
    );
    FractalBitmap::complex_t newstep = f->GetStep()*FractalBitmap::complex_t(evt.GetWheelRotation() < 0 ? 3.16227766017L : 1.0L/3.16227766017L);
    f->reset(newcenter, newstep, GetSize(), true);
}

BEGIN_EVENT_TABLE(FractalPanel, wxPanel)
    EVT_MOUSEWHEEL(FractalPanel::OnZoomEvent )
    EVT_SIZE      (FractalPanel::OnSizeEvent )
    EVT_ERASE_BACKGROUND(FractalPanel::OnEraseEvent)
    EVT_PAINT     (FractalPanel::OnPaintEvent)
END_EVENT_TABLE()
