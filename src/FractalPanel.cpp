#include "FractalFrame.h"
#include "CURSOR_CROSS.h"

enum{
    ID_ChangeSettings = 1
};

///Constructor
FractalPanel::FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *frac)
    :wxPanel(p, wxID_ANY, wxDefaultPosition, s, wxBORDER_RAISED),
     parent(p),f(frac),bmp(1,1,24){
    ///Initial settings
    SetCursor(CURSOR_CROSS);
    //popupMenu_ = new wxMenu;
    //popupMenu_->Append(ID_ChangeSettings, "Change settings");
    /**Create fractal thread*/{
        if(CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR){ wxLogError("Could not create main thread"); return; }
        if(GetThread()->Run()              != wxTHREAD_NO_ERROR){ wxLogError("Could not run main thread"   ); return; }
    }
}

typedef std::chrono::high_resolution_clock hrclock;
wxThread::ExitCode FractalPanel::Entry(){
    /**Create fractal*/{
        f->New(FractalBitmap::ComplexNum(FractalBitmap::ComplexT(-0.75),FractalBitmap::ComplexT(0.0L)),
            FractalBitmap::ComplexT(5.0e-3), GetSize(), true);
    }
    while(!GetThread()->TestDestroy()){
        {
            ///Update the fractal & measure time
            std::lock_guard<std::mutex> lock(f->Mutex);
            auto t1 = hrclock::now();
            f->UpdateMath();
            auto t2 = hrclock::now();
            auto dt = std::chrono::duration<long double>(t2-t1).count();
            /**Update values in ipanel for showing*/{
                std::lock_guard<std::mutex> lock2(parent->ipanel->Mutex);
                parent->ipanel->origin = f->GetOrigin();
                parent->ipanel->step = f->GetStep();
                parent->ipanel->numIt = f->GetNum();
                parent->ipanel->secPerIt = dt/f->GetCyclesPerRun();
                parent->ipanel->horizontalSize = f->GetHorizontalSize();
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

void FractalPanel::OnSizeEvent(wxSizeEvent& evt){
    std::lock_guard<std::mutex> lock(f->Mutex);

    wxPoint p = wxGetMousePosition() - this->GetScreenPosition();
    f->New(f->GetCenter(), f->GetStep(), this->GetSize(), true);
};

void FractalPanel::OnPaintEvent(wxPaintEvent& p){
    std::lock_guard<std::mutex> lock(bmpMutex);

    wxPaintDC dc(this);
    dc.DrawBitmap(bmp, 0, 0, true);
}

void FractalPanel::OnZoomEvent(wxMouseEvent& evt){
    std::lock_guard<std::mutex> lock(f->Mutex);

    wxPoint p = wxGetMousePosition() - GetScreenPosition();
    FractalBitmap::ComplexNum newcenter = f->GetOrigin() + FractalBitmap::ComplexNum(
        FractalBitmap::ComplexT(p.x)*f->GetStep(), FractalBitmap::ComplexT(-p.y)*f->GetStep()
    );
    FractalBitmap::ComplexT newstep = f->GetStep()*FractalBitmap::ComplexT(evt.GetWheelRotation() < 0 ? 3.16227766017L : 1.0L/3.16227766017L);
    f->New(newcenter, newstep, GetSize(), true);
}

BEGIN_EVENT_TABLE(FractalPanel, wxPanel)
    EVT_MOUSEWHEEL(FractalPanel::OnZoomEvent )
    EVT_SIZE      (FractalPanel::OnSizeEvent )
    EVT_ERASE_BACKGROUND(FractalPanel::OnEraseEvent)
    EVT_PAINT     (FractalPanel::OnPaintEvent)
END_EVENT_TABLE()
