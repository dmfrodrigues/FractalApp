#include "FractalFrame.h"

#include "HDPrintscreenDialog.h"
#include "CURSOR_CROSS.h"

#include <chrono>
#include <fstream>
#include <mutex>

///Event enumeration
enum{
    ID_PRINTSCREEN    = 1,
    ID_HDPRINTSCREEN  = 2
};
///Constructor
FractalFrame::FractalFrame(FractalBitmap *p):wxFrame(nullptr, wxID_ANY, "Mandelbrot set plotter"),f(p){
    /**Cursor*/{
        SetCursor(CURSOR_CROSS);
    }
    /**Menu*/{
        wxMenu* menuFile      = new wxMenu;
        wxMenuItem* menuItem_Printscreen   = new wxMenuItem(menuFile, ID_PRINTSCREEN  , wxT("Save printscreen"));
        wxMenuItem* menuItem_HDPrintscreen = new wxMenuItem(menuFile, ID_HDPRINTSCREEN, wxT("Save HD printscreen"));
        menuFile->Append(menuItem_Printscreen  );
        menuFile->Append(menuItem_HDPrintscreen);

        wxMenuBar* menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "File");
        this->SetMenuBar(menuBar);
    }
    /**Panels*/{
        fpanel = new FractalPanel(this, wxSize(1150, 500));
        ipanel = new InfoPanel   (this);
    }
    /**Background color*/{
        SetBackgroundColour(ipanel->GetBackgroundColour());
    }
    /**Sizers*/{
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(fpanel, 1, wxALL | wxEXPAND, 5);
        sizer->Add(ipanel, 0, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 7);
        sizer->SetSizeHints(this);
        this->SetSizer(sizer);
    }
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
wxThread::ExitCode FractalFrame::Entry(){
    /**Create fractal*/{
        f->New(FractalBitmap::ComplexNum(FractalBitmap::ComplexT(-0.75),FractalBitmap::ComplexT(0.0L)),
            FractalHeight*FractalBitmap::ComplexT(1.0L/0.8L/GetSize().y), fpanel->GetSize(), true);
    }
    std::chrono::duration<long double> dt;
    auto factor = f->GetCyclesPerRun();
    while(true){
        {
            std::lock_guard<std::mutex> lock(f->Mutex);
            ///Update the fractal
            auto t1 = hrclock::now();
            f->UpdateMath();
            auto t2 = hrclock::now();
            dt = t2-t1;
            ///Update the screen
            wxClientDC dc(fpanel);
            dc.DrawBitmap(*((wxBitmap*)f), 0, 0, true);
            factor = f->GetCyclesPerRun();
        }
        ///Update the InfoPanel
        CallAfter(&FractalFrame::UpdateInfoPanel, dt.count()/factor);
        ///Process size event (because it involves a lot of things)
        if(!fpanel->is_sizeevt_handled   ){ CallAfter(&FractalFrame::OnSizeEvent); fpanel->is_sizeevt_handled    = true; }
    }
    return (wxThread::ExitCode)0;
}

void FractalFrame::UpdateInfoPanel(const long double& secPerIt){
    wxPoint p = wxGetMousePosition() - fpanel->GetScreenPosition();
    FractalBitmap::ComplexNum c = f->GetOrigin() + FractalBitmap::ComplexNum(+(FractalBitmap::ComplexT)p.x*f->GetStep(),-(FractalBitmap::ComplexT)p.y*f->GetStep());
    ipanel->Update(c, f->GetStep(), f->GetNum(), secPerIt, f->GetHorizontalSize());
}

void FractalFrame::OnZoomEvent(wxMouseEvent& evt){
    std::lock_guard<std::mutex> lock(f->Mutex);

    wxPoint p = wxGetMousePosition() - fpanel->GetScreenPosition();
    FractalBitmap::ComplexNum newcenter = f->GetOrigin() + FractalBitmap::ComplexNum(
        FractalBitmap::ComplexT(p.x)*f->GetStep(), FractalBitmap::ComplexT(-p.y)*f->GetStep()
    );
    FractalBitmap::ComplexT newstep = f->GetStep()*FractalBitmap::ComplexT(evt.GetWheelRotation() < 0 ? 3.16227766017L : 1.0L/3.16227766017L);
    f->New(newcenter, newstep, fpanel->GetSize(), true);
}

void FractalFrame::OnSizeEvent(){
    std::lock_guard<std::mutex> lock(f->Mutex);

    wxPoint p = wxGetMousePosition() - fpanel->GetScreenPosition();
    f->New(f->GetCenter(), f->GetStep(), fpanel->GetSize(), true);
}


void NewImageName(const char* format, char* name){
    const unsigned long N = 100000;
    for(unsigned long i = 0; i < N; ++i){
        sprintf(name, format, i);
        if(!std::ifstream(name)) return;
    }
    throw std::logic_error("no available names");
}
void FractalFrame::OnPrintscreenEvent(wxCommandEvent &event){
    std::lock_guard<std::mutex> lock(f->Mutex);

    char new_path[256];
    NewImageName(".\\Printscreens\\Image_%04d.png", new_path);
    if(f->SaveFile(new_path, wxBITMAP_TYPE_PNG))
        wxLogMessage("Printscreen saved as " + wxString(new_path));
}
void FractalFrame::OnHDPrintscreenEvent(wxCommandEvent &event){
    std::lock_guard<std::mutex> lock(f->Mutex);

    char new_path[256];
    NewImageName(".\\Printscreens\\Image_%04d.png", new_path);

    FractalBitmap::ComplexNum center = f->GetCenter();
    FractalBitmap::ComplexT step = f->GetStep();
    wxSize sz = f->GetSize();
    FractalBitmap::IterationT num = f->GetNum();
    HDPrintscreenDialog *dialog = new HDPrintscreenDialog(this, &center, &step, &sz, &num);
    if(dialog->ShowModal() != wxID_OK) return;
    FractalBitmap *g = f->CreateNew(center, step, sz, true);

    num /= g->GetCyclesPerRun();
    while(--num){
        g->UpdateMath();
    }
    if(g->SaveFile(new_path, wxBITMAP_TYPE_PNG))
        wxLogMessage("Printscreen saved as " + wxString(new_path));
}

///MACROS - redirect events to functions
wxBEGIN_EVENT_TABLE(FractalFrame, wxFrame)
    EVT_MOUSEWHEEL(FractalFrame::OnZoomEvent)
    EVT_MENU(ID_PRINTSCREEN  , FractalFrame::OnPrintscreenEvent  )
    EVT_MENU(ID_HDPRINTSCREEN, FractalFrame::OnHDPrintscreenEvent)
wxEND_EVENT_TABLE()
