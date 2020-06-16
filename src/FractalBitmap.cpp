#include "FractalBitmap.h"

FractalBitmap::FractalBitmap():wxBitmap(1,1,24){}

void FractalBitmap::Create(FractalBitmap::ComplexNum o, FractalBitmap::complex_t st, wxSize s){
    wxBitmap::Create(s, 24);
    wxNativePixelData px(*((wxBitmap*)this));
    const unsigned N = GetWidth()*GetHeight();
    wxNativePixelData::Iterator p = px.GetPixels();
    for(unsigned i = 0; i < N; ++i, ++p){
        p.Red() = p.Green() = p.Blue() = 0;
    }

    SetStep(st);
    SetCenter(o);
}

FractalBitmap::ComplexNum FractalBitmap::GetOrigin() const {
    return origin;
}

void FractalBitmap::SetOrigin(const ComplexNum &orig){
    this->origin = orig;
}

FractalBitmap::ComplexNum FractalBitmap::GetCenter() const {
    return GetCenterFromOrigin(GetOrigin(), GetStep(), GetSize());
}

void FractalBitmap::SetCenter(const ComplexNum &cent){
    this->origin = GetOriginFromCenter(cent, GetStep(), GetSize());
}

FractalBitmap::complex_t FractalBitmap::GetStep() const {
    return step;
}

void FractalBitmap::SetStep(const complex_t &stp){
    this->step = stp;
}

FractalBitmap::complex_t FractalBitmap::GetHorizontalSize() const{
    return GetStep()*(complex_t)GetSize().x;
}

FractalBitmap::ComplexNum FractalBitmap::GetOriginFromCenter(ComplexNum cent, complex_t st, wxSize s){
    return cent + ComplexNum(complex_t(-s.x/2)*st, complex_t(+s.y/2)*st);
}

FractalBitmap::ComplexNum FractalBitmap::GetCenterFromOrigin(ComplexNum orig, complex_t st, wxSize s){
    return orig + ComplexNum(complex_t(+s.x/2)*st, complex_t(-s.y/2)*st);
}
