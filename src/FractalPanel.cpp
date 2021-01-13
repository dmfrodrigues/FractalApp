#include "FractalFrame.h"

#ifdef __WXMSW__
    // #include "CURSOR_CROSS.h"
#endif

enum{
    ID_ChangeSettings = 1
};

///Constructor
FractalPanel::FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *bmp_)
    :wxPanel(p, wxID_ANY, wxDefaultPosition, s, wxBORDER_RAISED),
     parent(p),bmp(bmp_),bmp_buffer(1,1,24){
    // std::cerr << "Constructing FractalPanel" << std::endl;
    ///Initial settings
    /**Cursor*/{
        #ifdef __WXMSW__
            // SetCursor(CURSOR_CROSS);
        #endif
    }
    //popupMenu_ = new wxMenu;
    //popupMenu_->Append(ID_ChangeSettings, "Change settings");
    /**Create fractal thread*/{
        if(CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR){ wxLogError("Could not create main thread"); return; }
        if(GetThread()->Run()              != wxTHREAD_NO_ERROR){ wxLogError("Could not run main thread"   ); return; }
    }
    // std::cerr << "Done constructing FractalPanel" << std::endl;
}

const FractalBitmap* FractalPanel::GetFractalBitmap() const{
    return bmp;
}

typedef std::chrono::high_resolution_clock hrclock;
wxThread::ExitCode FractalPanel::Entry(){
    // std::cerr << "Entered FractalPanel thread function" << std::endl;
    /**Create fractal*/{
        bmp->lowpriority.lock(); bmp->next.lock(); bmp->data.lock(); bmp->next.unlock();
        bmp->Create(
            FractalBitmap::ComplexNum(FractalBitmap::complex_t(-0.75L),FractalBitmap::complex_t(0.0L)), //-0.75L,0.0L
            FractalBitmap::complex_t(5.0e-3),
            GetSize()
        ); //5.0e-3
        bmp->data.unlock(); bmp->lowpriority.unlock();
    }
    while(!GetThread()->TestDestroy()){
        {
            bmp->lowpriority.lock(); bmp->next.lock(); bmp->data.lock(); bmp->next.unlock();
            ///Update the fractal & measure time
            auto t1 = hrclock::now();
            bmp->Update();
            auto t2 = hrclock::now();
            auto dt = std::chrono::duration<long double>(t2-t1).count();
            /**Update values in ipanel for showing*/{
                parent->GetInfoPanel()->SetOrigin(bmp->GetOrigin());
                parent->GetInfoPanel()->SetStep(bmp->GetStep());
                parent->GetInfoPanel()->SetIterations(bmp->GetNum());
                parent->GetInfoPanel()->SetSecPerIter(dt/bmp->GetCyclesPerRun());
                parent->GetInfoPanel()->SetHorizontalSize(bmp->GetHorizontalSize());
            }
            /**Update ready-to-draw bitmap*/{
                std::lock_guard<std::mutex> lock_bmp_buffer(bmp_buffer_mutex);
                bmp_buffer = bmp->GetSubBitmap(wxRect(0, 0, bmp->GetWidth(), bmp->GetHeight()));
            }
            bmp->data.unlock(); bmp->lowpriority.unlock();
        }
        ///Update screen
        CallAfter([this]{this->parent->Refresh(false);});
    }
    // std::cerr << "Leaving FractalPanel thread function" << std::endl;
    return (wxThread::ExitCode)0;
}

void FractalPanel::OnSizeEvent(wxSizeEvent&){
    bmp->next.lock(); bmp->data.lock(); bmp->next.unlock();
    bmp->Create(bmp->GetCenter(), bmp->GetStep(), this->GetSize());
    bmp->data.unlock();
}

void FractalPanel::OnPaintEvent(wxPaintEvent&){
    std::lock_guard<std::mutex> lock_bmp_buffer(bmp_buffer_mutex);

    wxPaintDC dc(this);
    dc.DrawBitmap(bmp_buffer, 0, 0, true);
}

void FractalPanel::OnZoomEvent(wxMouseEvent& evt){
    wxPoint p = wxGetMousePosition() - GetScreenPosition();
    FractalBitmap::ComplexNum newcenter = bmp->GetOrigin() + FractalBitmap::ComplexNum(
        FractalBitmap::complex_t(p.x)*bmp->GetStep(), FractalBitmap::complex_t(-p.y)*bmp->GetStep()
    );
    FractalBitmap::complex_t newstep = bmp->GetStep()*FractalBitmap::complex_t(evt.GetWheelRotation() < 0 ? 3.16227766017L : 1.0L/3.16227766017L);
    bmp->next.lock(); bmp->data.lock(); bmp->next.unlock();
    bmp->Create(newcenter, newstep, GetSize());
    bmp->data.unlock();
}

wxBEGIN_EVENT_TABLE(FractalPanel, wxPanel)
    EVT_MOUSEWHEEL(FractalPanel::OnZoomEvent )
    EVT_SIZE      (FractalPanel::OnSizeEvent )
    EVT_ERASE_BACKGROUND(FractalPanel::OnEraseEvent)
    EVT_PAINT     (FractalPanel::OnPaintEvent)
wxEND_EVENT_TABLE()
