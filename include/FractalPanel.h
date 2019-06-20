#ifndef FRACTALPANEL_H_INCLUDED
#define FRACTALPANEL_H_INCLUDED

#include <atomic>

class FractalFrame;

class FractalPanel: public wxPanel {
friend class FractalFrame;
public:
    FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *frac);
private:
    FractalFrame  *parent;
    FractalBitmap *f;

    void OnZoomEvent(wxMouseEvent& evt);
    std::atomic<bool> is_sizeevt_handled;
    void OnSizeEvent(wxSizeEvent& evt);

    wxDECLARE_EVENT_TABLE();
};

#endif
