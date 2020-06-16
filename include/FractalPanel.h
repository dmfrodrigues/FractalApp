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

    wxBitmap bmp;
    std::mutex bmpMutex;

    wxThread::ExitCode Entry();

    void OnZoomEvent(wxMouseEvent& evt);
    void OnSizeEvent(wxSizeEvent& evt);
    void OnEraseEvent(wxEraseEvent &){};
    void OnPaintEvent(wxPaintEvent& p);

    //void UpdateInfoPanel();

    wxDECLARE_EVENT_TABLE();
};

#endif
