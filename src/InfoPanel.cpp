#include "FractalFrame.h"

#include "myConversions.h"

InfoPanel::InfoPanel(FractalFrame* p):wxPanel(p), parent(p){
    ///

    wxStaticText* ReStat   = new wxStaticText(this, wxID_ANY,                       "Re(c) = ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    ReCtrl                 = new wxTextCtrl  (this, wxID_ANY,   "+0.11223344556677889900e-123", wxDefaultPosition, wxSize(270,27), wxALIGN_RIGHT);
    ReCtrl                 ->SetEditable(false);
    wxStaticText* ImStat   = new wxStaticText(this, wxID_ANY,                       "Im(c) = ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    ImCtrl                 = new wxTextCtrl  (this, wxID_ANY,   "-0.00998877665544332211e+321", wxDefaultPosition, wxSize(270,27), wxALIGN_RIGHT);
    ImCtrl                 ->SetEditable(false);

    wxStaticText* StepStat = new wxStaticText(this, wxID_ANY,                         "Step: ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    StepCtrl               = new wxTextCtrl  (this, wxID_ANY,                 "0.1234567e-123", wxDefaultPosition, wxSize(130,27), wxALIGN_RIGHT);
    StepCtrl               ->SetEditable(false);

    wxStaticText* ItStat   = new wxStaticText(this, wxID_ANY,             "Total no. cycles: ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    ItCtrl                 = new wxTextCtrl  (this, wxID_ANY,                         "123456", wxDefaultPosition, wxSize(110,27), wxALIGN_RIGHT);
    ItCtrl                 ->SetEditable(false);

    wxStaticText* TimeStat = new wxStaticText(this, wxID_ANY,   "Time elapsed per cycle (s): ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    TimeCtrl               = new wxTextCtrl  (this, wxID_ANY,                 "0.112233445566", wxDefaultPosition, wxSize(160,27), wxALIGN_RIGHT);
    TimeCtrl               ->SetEditable(false);

    wxStaticText* DiamStat = new wxStaticText(this, wxID_ANY, "Horizontal size of the image: ", wxDefaultPosition,  wxDefaultSize, wxALIGN_RIGHT);
    DiamCtrl               = new wxTextCtrl  (this, wxID_ANY,               "0.11223344556677", wxDefaultPosition, wxSize(150,27), wxALIGN_RIGHT);
    DiamCtrl               ->SetEditable(false);

    ///Static box sizer (creates rectangle with title)
    wxStaticBoxSizer* StatBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Settings");
    ///1st line
    wxBoxSizer* sizerLine1 = new wxBoxSizer(wxHORIZONTAL);
    sizerLine1->Add(  ReStat, 0, wxLEFT,  3); sizerLine1->Add(  ReCtrl, 0, 0, 0);

    sizerLine1->Add(  ItStat, 0, wxLEFT, 20); sizerLine1->Add(  ItCtrl, 0, 0, 0);
    sizerLine1->Add(TimeStat, 0, wxLEFT, 20); sizerLine1->Add(TimeCtrl, 0, 0, 0);
    ///2nd line
    wxBoxSizer* sizerLine2 = new wxBoxSizer(wxHORIZONTAL);
    sizerLine2->Add(  ImStat, 0, wxLEFT,  3); sizerLine2->Add(  ImCtrl, 0, 0, 0);
    sizerLine2->Add(StepStat, 0, wxLEFT, 20); sizerLine2->Add(StepCtrl, 0, 0, 0);
    sizerLine2->Add(DiamStat, 0, wxLEFT, 20); sizerLine2->Add(DiamCtrl, 0, 0, 0);
    ///Add stuff together
    StatBoxSizer->Add(sizerLine1, 1, wxLEFT | wxBOTTOM | wxRIGHT, 6);
    StatBoxSizer->Add(sizerLine2, 1, wxLEFT | wxBOTTOM | wxRIGHT, 6);
    StatBoxSizer->SetSizeHints(this);
    this->SetSizer(StatBoxSizer);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
void InfoPanel::SetOrigin        (FractalBitmap::ComplexNum origin_    ){ if(origin_     != GetOrigin        ()){ std::lock_guard<std::mutex> lock(Mutex); this->origin     = origin_    ; } }
void InfoPanel::SetStep          (FractalBitmap::complex_t  step_      ){ if(step_       != GetStep          ()){ std::lock_guard<std::mutex> lock(Mutex); this->step       = step_      ; } }
void InfoPanel::SetIterations    (FractalBitmap::iter_t     iter_      ){ if(iter_       != GetIterations    ()){ std::lock_guard<std::mutex> lock(Mutex); this->iter       = iter_      ; } }
void InfoPanel::SetSecPerIter    (long double               secPerIter_){ if(secPerIter_ != GetSecPerIter    ()){ std::lock_guard<std::mutex> lock(Mutex); this->secPerIter = secPerIter_; } }
void InfoPanel::SetHorizontalSize(FractalBitmap::complex_t  hsize_     ){ if(hsize_      != GetHorizontalSize()){ std::lock_guard<std::mutex> lock(Mutex); this->hsize      = hsize_     ; } }
#pragma GCC diagnostic pop

FractalBitmap::ComplexNum InfoPanel::GetOrigin        () const { return origin    ; }
FractalBitmap::complex_t  InfoPanel::GetStep          () const { return step      ; }
FractalBitmap::iter_t     InfoPanel::GetIterations    () const { return iter      ; }
long double               InfoPanel::GetSecPerIter    () const { return secPerIter; }
FractalBitmap::complex_t  InfoPanel::GetHorizontalSize() const { return hsize     ; }

void InfoPanel::OnPaintEvent(wxPaintEvent &){
    std::lock_guard<std::mutex> lock(Mutex);

    wxPoint p = wxGetMousePosition() - parent->GetFractalPanel()->GetScreenPosition();
    FractalBitmap::ComplexNum MousePosC = GetOrigin() +
        FractalBitmap::ComplexNum(
            +(FractalBitmap::complex_t)p.x * GetStep(),
            -(FractalBitmap::complex_t)p.y * GetStep()
        );

    ReCtrl  ->ChangeValue(float2str(MousePosC.real(), 20, std::ios_base::scientific | std::ios_base::showpos));
    ImCtrl  ->ChangeValue(float2str(MousePosC.imag(), 20, std::ios_base::scientific | std::ios_base::showpos));
    StepCtrl->ChangeValue(float2str(GetStep()       ,  4, std::ios_base::scientific));
    ItCtrl  ->ChangeValue(std::to_string(GetIterations()));
    TimeCtrl->ChangeValue(float2str(GetSecPerIter(), 12, std::ios_base::fixed));
    DiamCtrl->ChangeValue(float2str(GetHorizontalSize(), 6));
}

wxBEGIN_EVENT_TABLE(InfoPanel, wxPanel)
    EVT_ERASE_BACKGROUND(InfoPanel::OnEraseEvent)
    EVT_PAINT(InfoPanel::OnPaintEvent)
wxEND_EVENT_TABLE()
