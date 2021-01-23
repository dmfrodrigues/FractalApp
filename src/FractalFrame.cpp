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
FractalFrame::FractalFrame(FractalBitmap *bmp):wxFrame(nullptr, wxID_ANY, "Fractal app"){
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

void FractalFrame::OnPrintscreenEvent(wxCommandEvent &){
    wxFileDialog saveFileDialog(this, ("Save screenshot as"), "", "",
        "PNG files (*.png)|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL) return;
    std::string path = saveFileDialog.GetPath().ToStdString();

    if(fpanel->GetFractalBitmap()->SaveFile(path, wxBITMAP_TYPE_PNG))
        wxLogMessage("Printscreen saved as " + wxString(path) + ".png");
}
void FractalFrame::OnHDPrintscreenEvent(wxCommandEvent &){
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

    wxFileDialog saveFileDialog(this, ("Save HD screenshot as"), "", "",
        "PNG files (*.png)|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL) return;
    std::string path = saveFileDialog.GetPath().ToStdString();

    num /= g->GetCyclesPerRun();
    while(--num){
        g->Update();
    }
    if(g->SaveFile(path, wxBITMAP_TYPE_PNG))
        wxLogMessage("Printscreen saved as " + wxString(path));
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
