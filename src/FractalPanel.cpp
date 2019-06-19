#include "FractalFrame.h"
#include "CURSOR_CROSS.h"

enum{
    ID_ChangeSettings = 1
};

///Constructor
FractalPanel::FractalPanel(FractalFrame* p, wxSize s)
    :wxPanel(p, wxID_ANY, wxDefaultPosition, s, wxBORDER_RAISED),
     parent(p),is_sizeevt_handled(true){
    ///Initial settings
    SetCursor(CURSOR_CROSS);
    //popupMenu_ = new wxMenu;
    //popupMenu_->Append(ID_ChangeSettings, "Change settings");
}

void FractalPanel::OnZoomEvent(wxMouseEvent& evt){ parent->OnZoomEvent(evt); }

BEGIN_EVENT_TABLE(FractalPanel, wxPanel)
    EVT_MOUSEWHEEL(FractalPanel::OnZoomEvent)
    EVT_SIZE      (FractalPanel::OnSizeEvent)
END_EVENT_TABLE()
