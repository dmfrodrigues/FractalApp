#include <wx/wx.h>
#include "FractalFrame.h"

class TestBitmap: public FractalBitmap {
public:
    TestBitmap():FractalBitmap(){}
    TestBitmap(const TestBitmap &p):FractalBitmap(){
        Create(p.GetCenter(), p.GetStep(), p.GetSize());
    }
    void Create(ComplexNum o, complex_t st, wxSize s) override{
        FractalBitmap::Create(o, st, s);
    }
    TestBitmap* Clone() const override{
        return new TestBitmap(*this);
    }
    void Update(){}
    iter_t GetNum()            const override{ static int i = 0; return ++i; }
    iter_t GetCyclesPerRun()   const override{ return 1; }
    bool SaveFile(const wxString& , wxBitmapType , const wxPalette * = NULL) const override{
        return true;
    }
};

class FractalApp: public wxApp{
private:
    FractalFrame *fractalFrame;
    FractalBitmap *f;
public:
    virtual bool OnInit(){
        wxInitAllImageHandlers();
        f = new TestBitmap();
        fractalFrame = new FractalFrame(f);
        fractalFrame->Show(true);
        return true;
    }
    int OnExit(){
        delete f;
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(FractalApp);
