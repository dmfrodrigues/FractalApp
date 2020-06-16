/**
 * file: CURSOR_CROSS.h
 *
 * This header file provides access to a 32x32 cursor with the shape of a greek
 * cross, with main color black and white edges.
 * This cursor shape makes easier for the user to know precisely the position of
 * the cursor
 */

#ifndef CURSOR_CROSS_H_INCLUDED
#define CURSOR_CROSS_H_INCLUDED

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <wx/cursor.h>
#pragma GCC diagnostic pop

extern const wxCursor CURSOR_CROSS;

#endif ///CURSOR_CROSS_H_INCLUDED
