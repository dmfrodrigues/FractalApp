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
    FractalBitmap::complex_t step;
    FractalBitmap::iter_t iter;
    long double secPerIter;
    FractalBitmap::complex_t hsize;

    InfoPanel(FractalFrame *p);

    void OnEraseEvent(wxEraseEvent &){};
    void OnPaintEvent(wxPaintEvent &evt);
public:
    void SetOrigin        (FractalBitmap::ComplexNum origin    );
    void SetStep          (FractalBitmap::complex_t  step      );
    void SetIterations    (FractalBitmap::iter_t     iter      );
    void SetSecPerIter    (long double               secPerIter);
    void SetHorizontalSize(FractalBitmap::complex_t  hsize     );

    FractalBitmap::ComplexNum GetOrigin        () const;
    FractalBitmap::complex_t  GetStep          () const;
    FractalBitmap::iter_t     GetIterations    () const;
    long double               GetSecPerIter    () const;
    FractalBitmap::complex_t  GetHorizontalSize() const;

    wxDECLARE_EVENT_TABLE();
};

#endif
