#ifndef FRACTALFRAME_H_INCLUDED
#define FRACTALFRAME_H_INCLUDED

#include <atomic>
#include <wx/wx.h>
#include "FractalBitmap.h"

#include "FractalPanel.h"
#include "InfoPanel.h"

const FractalBitmap::ComplexT    FractalHeight(2.5L);        ///vertical height of the fractal at zoom==1

///=========================================================
///FRACTALFRAME
class FractalFrame: public wxFrame, public wxThreadHelper {
friend class FractalPanel;
public:
    FractalFrame(FractalBitmap *p);
private:
    FractalPanel* fpanel;
    InfoPanel*    ipanel;

    wxThread::ExitCode Entry();

    //FractalBitmap *f;

    std::atomic<double> dt;

    friend void FractalPanel::OnZoomEvent(wxMouseEvent& evt);
    void OnZoomEvent(wxMouseEvent& evt);

    void OnPrintscreenEvent(wxCommandEvent &event);
    void OnHDPrintscreenEvent(wxCommandEvent &event);
    void OnPaintEvent(wxPaintEvent& p);

    void UpdateInfoPanel();

    wxDECLARE_EVENT_TABLE();
};


#endif
