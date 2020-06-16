#ifndef HDPRINTSCREENDIALOG_H_INCLUDED
#define HDPRINTSCREENDIALOG_H_INCLUDED

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <wx/wx.h>
#pragma GCC diagnostic pop

#include "FractalBitmap.h"

class HDPrintscreenDialog: public wxDialog {
public:
    HDPrintscreenDialog(wxWindow *p, FractalBitmap::ComplexNum *c, FractalBitmap::complex_t *z, wxSize *s, FractalBitmap::IterationT *it);
private:
    ///================================
    ///VARIABLES
    wxTextCtrl *ReCtrl, *ImCtrl, *StepCtrl, *SzXCtrl, *SzYCtrl, *ItCtrl;
    FractalBitmap::ComplexNum *center;
    FractalBitmap::complex_t *step;
    wxSize *sz;
    FractalBitmap::IterationT* numIt;
    ///================================
    ///BUTTONS AND CALLBACKS
    wxButton*     OKBtn; void OnOK    (wxCommandEvent& event);
    wxButton* CancelBtn; void OnCancel(wxCommandEvent& event);
    ///================================
    ///EVENT TABLE
    DECLARE_EVENT_TABLE()
};

#endif // HDPRINTSCREENDIALOG_H_INCLUDED
