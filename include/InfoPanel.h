#ifndef INFOPANEL_H_INCLUDED
#define INFOPANEL_H_INCLUDED

class FractalFrame;

class InfoPanel: public wxPanel {
friend class FractalFrame;
friend class FractalPanel;
private:
    FractalFrame *parent;
    wxTextCtrl *ReCtrl, *ImCtrl, *StepCtrl, *ItCtrl, *TimeCtrl, *DiamCtrl;
    InfoPanel(FractalFrame *p);

    void OnEraseEvent(wxEraseEvent &evt){};
    void OnPaintEvent(wxPaintEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

#endif
