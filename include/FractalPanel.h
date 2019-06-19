#ifndef FRACTALPANEL_H_INCLUDED
#define FRACTALPANEL_H_INCLUDED

#include <atomic>

class FractalFrame;

class FractalPanel: public wxPanel {
friend class FractalFrame;
public:
    FractalPanel(FractalFrame* p, wxSize s);
private:
    FractalFrame    *parent;

    void OnZoomEvent(wxMouseEvent& evt);
    std::atomic<bool> is_sizeevt_handled;
    void OnSizeEvent(wxSizeEvent& evt){ is_sizeevt_handled = false; };

    wxDECLARE_EVENT_TABLE();
};

#endif
