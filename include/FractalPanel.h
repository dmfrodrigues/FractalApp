#ifndef FRACTALPANEL_H_INCLUDED
#define FRACTALPANEL_H_INCLUDED

#include <atomic>

class FractalFrame;

class FractalPanel: public wxPanel, public wxThreadHelper {
friend class FractalFrame;
friend class InfoPanel;
public:
    FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *frac);
private:
    FractalFrame  *parent;
    FractalBitmap *f;

    std::atomic<double> dt;

    wxThread::ExitCode Entry();

    void OnZoomEvent(wxMouseEvent& evt);
    std::atomic<bool> is_sizeevt_handled;
    void OnSizeEvent(wxSizeEvent& evt);
    void OnEraseEvent(wxEraseEvent &evt){};
    void OnPaintEvent(wxPaintEvent& p);

    //void UpdateInfoPanel();

    wxDECLARE_EVENT_TABLE();
};

#endif
