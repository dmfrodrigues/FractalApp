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
 * (`complex_t`), and `std::complex<complex_t>` as fundamental complex type
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

//#include "mc_float.h"

using namespace std;

class FractalBitmap: public wxBitmap{
public:
    ///PUBLIC TYPEDEFS
    typedef long double complex_t;
    typedef unsigned long long iter_t;
    typedef std::complex<complex_t> ComplexNum;

public:

    std::mutex Mutex;

    /**
     * @brief Initializes the object using the arguments to start calculations from the beginning.
     * 
     * @param   o           origin (or center) of the fractal
     * @param   st          step (distance between two consecutive pixels)
     * @param   s           size of the fractal in pixels (width, height)
     * @param   IsCenter    true if provided argument `o` is the center of the
                            fractal, false if `o` is the origin.
     */
    virtual void init(ComplexNum o, complex_t st, wxSize s, bool IsCenter = false) = 0;
    /**
     * @brief Clones object and returns pointer. Must be freed by the caller.
     * 
     * @return FractalBitmap* 
     */
    virtual FractalBitmap* clone() const = 0;

    ///CALCULATIONS ==================================================
    /**
     * @brief Make calculations, and update pixels accordingly.
     */
    virtual void update() = 0;

    ///GET FUNCTIONS =================================================
    /**
     * /!\ It IS mandatory to overload the GET functions.
     * Provide information to the outside world, so the panels' information can
     * be updated
     */
    virtual ComplexNum getOrigin()         const = 0;
    virtual ComplexNum getCenter()         const = 0;
    virtual complex_t   getStep()           const = 0;
    virtual iter_t getNum()            const = 0;
    virtual complex_t   GetHorizontalSize() const = 0;
    virtual iter_t GetCyclesPerRun()   const = 0;

    ///STATIC FUNCTIONS ==============================================
    /**
     * /!\ These functions should NOT be overloaded.
     * Get origin of fractal from the provided center in a fractal with step
     * `st` and size `s`, and vice-versa
     */
    static ComplexNum GetOriginFromCenter(ComplexNum cent, complex_t st, wxSize s);
    static ComplexNum GetCenterFromOrigin(ComplexNum orig, complex_t st, wxSize s);
};

#endif // FRACTALBITMAP_H_INCLUDED
