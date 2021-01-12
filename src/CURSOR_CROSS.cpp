#include "CURSOR_CROSS.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <wx/bitmap.h>
#pragma GCC diagnostic pop

static const unsigned char uCROSS_bits[] = {
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
      0, 128,   0,   0,
    255, 255, 255, 255,
      0, 128,   0,   0,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    255, 191, 254, 255,
    };
static const unsigned char uCROSS_mask[] = {
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
      0,   0,   0, 128,
      0,   0,   0, 128,
      0,   0,   0, 128,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255,  63, 254, 255,
    255, 255, 255, 255,
    };
static const char *CROSS_bits = reinterpret_cast<const char*>(uCROSS_bits);
static const char *CROSS_mask = reinterpret_cast<const char*>(uCROSS_mask);
#ifdef __WXMSW__
/*
wxCursor CreateCURSOR_CROSS(){
    wxInitAllImageHandlers();
    wxBitmap CROSS_bitmap(CROSS_bits, 32, 32);
    wxBitmap CROSS_mask_bitmap(CROSS_mask, 32, 32);
    CROSS_bitmap.SetMask(new wxMask(CROSS_mask_bitmap));
    wxImage CROSS_image = CROSS_bitmap.ConvertToImage();
    CROSS_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 15);
    CROSS_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 15);
    wxCursor CROSS_cursor = wxCursor(CROSS_image);
    return CROSS_cursor;
}
const wxCursor CURSOR_CROSS = CreateCURSOR_CROSS();
*/
#endif
#if defined(__WXGTK__) or defined(__WXMOTIF__)
/*
wxCursor CreateCURSOR_CROSS(){
    wxInitAllImageHandlers();
        wxCursor CROSS_cursor = wxCursor(CROSS_bits, 32, 32, 6, 14,
                                        CROSS_mask, wxWHITE, wxBLACK);

    return CROSS_cursor;
}
*/
#endif
