#include "FractalBitmap.h"

FractalBitmap::FractalBitmap():wxBitmap(1,1,24){}

void FractalBitmap::Create(FractalBitmap::ComplexNum center_, FractalBitmap::complex_t step_, wxSize sz_){
    wxBitmap::Create(sz_, 24);
    /*
    wxNativePixelData px(*((wxBitmap*)this));
    const unsigned N = GetWidth()*GetHeight();
    wxNativePixelData::Iterator p = px.GetPixels();
    for(unsigned i = 0; i < N; ++i, ++p){
        p.Red() = p.Green() = p.Blue() = 0;
    }
    */

    SetStep(step_);
    SetCenter(center_);
}

FractalBitmap::ComplexNum FractalBitmap::GetOrigin() const {
    return origin;
}

void FractalBitmap::SetOrigin(const ComplexNum &origin_){
    this->origin = origin_;
}

FractalBitmap::ComplexNum FractalBitmap::GetCenter() const {
    return GetCenterFromOrigin(GetOrigin(), GetStep(), GetSize());
}

void FractalBitmap::SetCenter(const ComplexNum &center){
    this->origin = GetOriginFromCenter(center, GetStep(), GetSize());
}

FractalBitmap::complex_t FractalBitmap::GetStep() const {
    return step;
}

void FractalBitmap::SetStep(const complex_t &step_){
    this->step = step_;
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
