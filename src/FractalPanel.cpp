#include "FractalFrame.h"
#include "CURSOR_CROSS.h"

enum{
    ID_ChangeSettings = 1
};

///Constructor
FractalPanel::FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *frac)
    :wxPanel(p, wxID_ANY, wxDefaultPosition, s, wxBORDER_RAISED),
     parent(p),f(frac),is_sizeevt_handled(true){
    ///Initial settings
    SetCursor(CURSOR_CROSS);
    //popupMenu_ = new wxMenu;
    //popupMenu_->Append(ID_ChangeSettings, "Change settings");
    /**Create fractal thread*/{
        if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR){
            wxLogError("Could not create main thread"); return;
        }
        if (GetThread()->Run() != wxTHREAD_NO_ERROR){
            wxLogError("Could not run main thread"   ); return;
        }
    }
}

typedef std::chrono::high_resolution_clock hrclock;
wxThread::ExitCode FractalPanel::Entry(){
    /**Create fractal*/{
        f->New(FractalBitmap::ComplexNum(FractalBitmap::ComplexT(-0.75),FractalBitmap::ComplexT(0.0L)),
            FractalHeight*FractalBitmap::ComplexT(1.0L/1.06L/GetSize().y), GetSize(), true); //1.0L/0.8L/GetSize().y
    }
    while(true){
        {
            std::lock_guard<std::mutex> lock(f->Mutex);
            ///Update the fractal & measure time
            auto t1 = hrclock::now();
            f->UpdateMath();
            auto t2 = hrclock::now();
            dt = std::chrono::duration<long double>(t2-t1).count();
        }
        ///Update the screen
        wxPaintEvent p;
        ProcessEvent(p);
    }
    return (wxThread::ExitCode)0;
}

void FractalPanel::UpdateInfoPanel(){
    wxPoint p = wxGetMousePosition() - GetScreenPosition();
    FractalBitmap::ComplexNum c = f->GetOrigin() + FractalBitmap::ComplexNum(+(FractalBitmap::ComplexT)p.x*f->GetStep(),-(FractalBitmap::ComplexT)p.y*f->GetStep());
    parent->ipanel->Update(c, f->GetStep(), f->GetNum(), dt/f->GetCyclesPerRun(), f->GetHorizontalSize());
}

void FractalPanel::OnSizeEvent(wxSizeEvent& evt){
    std::lock_guard<std::mutex> lock(f->Mutex);

    wxPoint p = wxGetMousePosition() - this->GetScreenPosition();
    f->New(f->GetCenter(), f->GetStep(), this->GetSize(), true);

};

void FractalPanel::OnPaintEvent(wxPaintEvent& p){
    std::lock_guard<std::mutex> lock(f->Mutex);
    if(f->GetNum() != 0){
        wxClientDC dc(this);
        dc.DrawBitmap(*((wxBitmap*)f), 0, 0, true);
        ///Update the InfoPanel
        CallAfter(&FractalPanel::UpdateInfoPanel);
    }
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
    EVT_PAINT     (FractalPanel::OnPaintEvent)
END_EVENT_TABLE()
