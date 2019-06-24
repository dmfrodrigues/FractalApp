/**
 * file: FractalBitmap.h
 *
 * This header file provides the definition of the FractalBitmap class.
 * FractalBitmap provides an easy interface to allow calculations, plotting and
 * saving images of fractals.
 *
 * FractalBitmap inherits from wxBitmap, to inherit some useful functions, since
 * the FractalBitmap class is meant to be seen from the outside as a black-box
 * encapsulating a lot of heavy calculations, serving as a sort of an 'evolving
 * image'.
 *
 * FractalBitmap must not be used directly, but rather overloaded to correspond
 * to the user's needs.
 *
 * Currently, this class uses `long double` as fundamental floating type
 * (`ComplexT`), and `std::complex<ComplexT>` as fundamental complex type
 * (`ComplexNum`).
 * /!\ BEWARE THAT `std::complex` IS VERY SLOW if compiled with default options.
 * To make `std::complex` calculations decently fast, compile FractalBitmap.cpp
 * with the -ffast-math flag.
 */

#ifndef FRACTALBITMAP_H_INCLUDED
#define FRACTALBITMAP_H_INCLUDED

#include <complex>
#include <mutex>
#include <wx/rawbmp.h>

#include "gaf.h"

using namespace std;

class FractalBitmap: public wxBitmap{
public:
    ///PUBLIC TYPEDEFS
    typedef gaf<32> ComplexT;
    typedef unsigned long long IterationT;
    typedef std::complex<ComplexT> ComplexNum;

public:
    /**
     * It is NOT mandatory to overload FractalBitmap::FractalBitmap.
     */
    FractalBitmap();

    std::mutex Mutex;

    /**
     * /!\ It IS mandatory to overload FractalBitmap::New.
     * FractalBitmap::New receives parameters, and resets the object using the
     * arguments to start calculations from the beginning.
     * @param   o           origin (or center) of the fractal
     * @param   st          step (distance between two consecutive pixels)
     * @param   s           size of the fractal in pixels (width, height)
     * @param   IsCenter    true if provided argument `o` is the center of the
                            fractal, false if `o` is the origin.
     */
    virtual void New(ComplexNum o, ComplexT st, wxSize s, bool IsCenter = false) = 0;
    /**
     * /!\ It IS mandatory to overload FractalBitmap::CreateNew.
     * FractalBitmap::CreateNew receives the same parameters as
     * FractalBitmap::New. It creates a new object in the heap, runs New on it,
     * and returns the pointer to the new object
     * @param   o           origin (or center) of the fractal
     * @param   st          step (distance between two consecutive pixels)
     * @param   s           size of the fractal in pixels (width, height)
     * @param   IsCenter    true if provided argument `o` is the center of the
                            fractal, false if `o` is the origin.
     */
    virtual FractalBitmap* CreateNew(ComplexNum o, ComplexT st, wxSize s, bool IsCenter = false) const = 0;
    /**
     * It is NOT mandatory to overload FractalBitmap::~FractalBitmap.
     * This is a dummy destructor, since FractalBitmap inherits everything from
     * wxBitmap (thus inheriting its destructor), while only adding functions,
     * not variables.
     */
    ~FractalBitmap(){};

    ///CALCULATIONS ==================================================
    /**
     * /!\ It IS mandatory to overload FractalBitmap::UpdateMath.
     * Make calculations, and update pixels accordingly. This is the most
     * important function of the class.
     */
    virtual void UpdateMath() = 0;

    ///GET FUNCTIONS =================================================
    /**
     * /!\ It IS mandatory to overload the GET functions.
     * Provide information to the outside world, so the panels' information can
     * be updated
     */
    virtual ComplexNum GetOrigin()         const = 0;
    virtual ComplexNum GetCenter()         const = 0;
    virtual ComplexT   GetStep()           const = 0;
    virtual IterationT GetNum()            const = 0;
    virtual ComplexT   GetHorizontalSize() const = 0;
    virtual IterationT GetCyclesPerRun()   const = 0;

    ///STATIC FUNCTIONS ==============================================
    /**
     * /!\ These functions should NOT be overloaded.
     * Get origin of fractal from the provided center in a fractal with step
     * `st` and size `s`, and vice-versa
     */
    static ComplexNum GetOriginFromCenter(ComplexNum cent, ComplexT st, wxSize s);
    static ComplexNum GetCenterFromOrigin(ComplexNum orig, ComplexT st, wxSize s);

};

#endif // FRACTALBITMAP_H_INCLUDED
