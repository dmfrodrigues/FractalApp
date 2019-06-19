#ifndef FRACTALFRAME_H_INCLUDED
#define FRACTALFRAME_H_INCLUDED

#include <wx/wx.h>
#include "FractalBitmap.h"

#include "FractalPanel.h"
#include "InfoPanel.h"

const FractalBitmap::ComplexT    FractalHeight(2.5L);        ///vertical height of the fractal at zoom==1

///=========================================================
///FRACTALFRAME
class FractalFrame: public wxFrame, public wxThreadHelper {
public:
    FractalFrame(FractalBitmap *p);
private:
    FractalPanel* fpanel;
    InfoPanel*    ipanel;

    wxThread::ExitCode Entry();

    FractalBitmap *f;

    friend void FractalPanel::OnZoomEvent(wxMouseEvent& evt);
    void OnZoomEvent(wxMouseEvent& evt);
    void OnSizeEvent();

    void OnPrintscreenEvent(wxCommandEvent &event);
    void OnHDPrintscreenEvent(wxCommandEvent &event);

    void UpdateInfoPanel(const long double& secPerIt);

    wxDECLARE_EVENT_TABLE();
};


#endif
