#ifndef FRACTALFRAME_H_INCLUDED
#define FRACTALFRAME_H_INCLUDED

#include "FractalBitmap.h"

#include "FractalPanel.h"
#include "InfoPanel.h"

///=========================================================
///FRACTALFRAME
class FractalFrame: public wxFrame {
friend class FractalPanel;
friend class InfoPanel;
public:
    FractalFrame(FractalBitmap *p);
private:
    FractalPanel* fpanel;
    InfoPanel*    ipanel;

    void OnPrintscreenEvent(wxCommandEvent &event);
    void OnHDPrintscreenEvent(wxCommandEvent &event);
    void OnCloseEvent(wxCloseEvent& evt);

    wxDECLARE_EVENT_TABLE();
};


#endif
