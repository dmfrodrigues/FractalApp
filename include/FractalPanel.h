#ifndef FRACTALPANEL_H_INCLUDED
#define FRACTALPANEL_H_INCLUDED

#include <atomic>

class FractalFrame;

class FractalPanel: public wxPanel, public wxThreadHelper {
private:
    FractalFrame  *parent;
    FractalBitmap *bmp;

    wxBitmap bmp_buffer;
    std::mutex bmpMutex;
public:
    FractalPanel(FractalFrame* p, wxSize s, FractalBitmap *bmp);

    const FractalBitmap* GetFractalBitmap() const;
private:
    wxThread::ExitCode Entry();

    void OnZoomEvent(wxMouseEvent& evt);
    void OnSizeEvent(wxSizeEvent& evt);
    void OnEraseEvent(wxEraseEvent &){};
    void OnPaintEvent(wxPaintEvent& p);

    wxDECLARE_EVENT_TABLE();
};

#endif
