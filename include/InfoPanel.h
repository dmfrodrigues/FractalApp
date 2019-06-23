#ifndef INFOPANEL_H_INCLUDED
#define INFOPANEL_H_INCLUDED

class FractalFrame;

class InfoPanel: public wxPanel {
friend class FractalFrame;
friend class FractalPanel;
private:
    FractalFrame *parent;
    wxTextCtrl *ReCtrl, *ImCtrl, *StepCtrl, *ItCtrl, *TimeCtrl, *DiamCtrl;

    std::mutex Mutex;

    FractalBitmap::ComplexNum origin;
    FractalBitmap::ComplexT step;
    FractalBitmap::IterationT numIt;
    long double secPerIt;
    FractalBitmap::ComplexT horizontalSize;

    InfoPanel(FractalFrame *p);

    void OnEraseEvent(wxEraseEvent &evt){};
    void OnPaintEvent(wxPaintEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

#endif
