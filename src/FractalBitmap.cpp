#include "FractalBitmap.h"

FractalBitmap::FractalBitmap():wxBitmap(1,1,24){}

FractalBitmap::ComplexNum FractalBitmap::GetOriginFromCenter(ComplexNum cent, complex_t st, wxSize s){
    return cent + ComplexNum(complex_t(-s.x/2)*st, complex_t(+s.y/2)*st);
}

FractalBitmap::ComplexNum FractalBitmap::GetCenterFromOrigin(ComplexNum orig, complex_t st, wxSize s){
    return orig + ComplexNum(complex_t(+s.x/2)*st, complex_t(-s.y/2)*st);
}
