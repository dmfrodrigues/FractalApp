#include "FractalFrame.h"

#include "HDPrintscreenDialog.h"

#include <chrono>
#include <fstream>
#include <mutex>

///Event enumeration
enum{
    ID_PRINTSCREEN    = 1,
    ID_HDPRINTSCREEN  = 2
};
///Constructor
FractalFrame::FractalFrame(FractalBitmap *bmp):wxFrame(nullptr, wxID_ANY, "Mandelbrot set plotter"){
    std::cerr << "+FractalFrame::FractalFrame" << std::endl;
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
        fpanel = new FractalPanel(this, wxSize(1150, 500), bmp);
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
    std::cerr << "-FractalFrame::FractalFrame" << std::endl;
}

const FractalPanel* FractalFrame::GetFractalPanel() const{
    return fpanel;
}

InfoPanel* FractalFrame::GetInfoPanel(){
    return ipanel;
}

void NewImageName(const char* format, char* name){
    const unsigned N = 100000;
    for(unsigned i = 0; i < N; ++i){
        sprintf(name, format, i);
        if(!std::ifstream(name)) return;
    }
    throw std::logic_error("no available image names");
}
void FractalFrame::OnPrintscreenEvent(wxCommandEvent &){
    char new_path[256];
    NewImageName("./Printscreens/Image_%04d.png", new_path);
    {
        if(fpanel->GetFractalBitmap()->SaveFile(new_path, wxBITMAP_TYPE_PNG))
            wxLogMessage("Printscreen saved as " + wxString(new_path));
    }
}
void FractalFrame::OnHDPrintscreenEvent(wxCommandEvent &){
    char new_path[256];
    NewImageName("./Printscreens/Image_%04d.png", new_path);

    FractalBitmap *g;
    FractalBitmap::iter_t num;
    {
        // std::lock_guard<std::mutex> lock(fpanel->f->Mutex);

        FractalBitmap::ComplexNum center = fpanel->GetFractalBitmap()->GetCenter();
        FractalBitmap::complex_t  step   = fpanel->GetFractalBitmap()->GetStep();
        wxSize                    sz     = fpanel->GetFractalBitmap()->GetSize();
        num                              = fpanel->GetFractalBitmap()->GetNum();
        HDPrintscreenDialog *dialog = new HDPrintscreenDialog(this, &center, &step, &sz, &num);
        if(dialog->ShowModal() != wxID_OK) return;
        g = fpanel->GetFractalBitmap()->Clone();
        g->Create(center, step, sz);
    }

    num /= g->GetCyclesPerRun();
    while(--num){
        g->Update();
    }
    if(g->SaveFile(new_path, wxBITMAP_TYPE_PNG))
        wxLogMessage("Printscreen saved as " + wxString(new_path));
}

void FractalFrame::OnCloseEvent(wxCloseEvent&){
    fpanel->GetThread()->Delete();
    Destroy();
}

///MACROS - redirect events to functions
wxBEGIN_EVENT_TABLE(FractalFrame, wxFrame)
    EVT_MENU(ID_PRINTSCREEN  , FractalFrame::OnPrintscreenEvent  )
    EVT_MENU(ID_HDPRINTSCREEN, FractalFrame::OnHDPrintscreenEvent)
    EVT_CLOSE(FractalFrame::OnCloseEvent)
wxEND_EVENT_TABLE()
