#include "FractalBitmap.h"

FractalBitmap::FractalBitmap():wxBitmap(1,1,24){}

FractalBitmap::ComplexNum FractalBitmap::GetOrigin() const { return origin; }
void       FractalBitmap::SetOrigin(const ComplexNum &orig){ this->origin = orig; }
FractalBitmap::ComplexNum FractalBitmap::GetCenter() const { return GetCenterFromOrigin(GetOrigin(), GetStep(), GetSize()); }

FractalBitmap::complex_t FractalBitmap::GetHorizontalSize() const{
    return GetStep()*(complex_t)GetSize().x;
}

FractalBitmap::ComplexNum FractalBitmap::GetOriginFromCenter(ComplexNum cent, complex_t st, wxSize s){
    return cent + ComplexNum(complex_t(-s.x/2)*st, complex_t(+s.y/2)*st);
}

FractalBitmap::ComplexNum FractalBitmap::GetCenterFromOrigin(ComplexNum orig, complex_t st, wxSize s){
    return orig + ComplexNum(complex_t(+s.x/2)*st, complex_t(-s.y/2)*st);
}
