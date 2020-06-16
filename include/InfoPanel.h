#ifndef INFOPANEL_H_INCLUDED
#define INFOPANEL_H_INCLUDED

class FractalFrame;

class InfoPanel: public wxPanel {
private:
    FractalFrame *parent;
    wxTextCtrl *ReCtrl, *ImCtrl, *StepCtrl, *ItCtrl, *TimeCtrl, *DiamCtrl;

    std::mutex Mutex;

    FractalBitmap::ComplexNum origin;
    FractalBitmap::complex_t step;
    FractalBitmap::iter_t iter;
    long double secPerIter;
    FractalBitmap::complex_t hsize;

    void OnEraseEvent(wxEraseEvent &){};
    void OnPaintEvent(wxPaintEvent &evt);
public:
    InfoPanel(FractalFrame *p);

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
