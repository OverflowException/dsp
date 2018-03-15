#ifndef _SPECTRO_H
#define _SPECTRO_H

#include <cmath>
#include <cstdint>
#include <array>
#include <iostream>

namespace bfin
{
  //_T --- signal element type
  //_N --- number of samples per frame
  //_O --- frame offset
  template<typename _T, uint16_t _N, uint16_t _O>
  class Spectro
    {
    public:
      //ctor
      //sig -- signal start
      //s_size --- total signal size
      //f_size --- frame size
      //o_size --- offset size
      Spectro(_T* sig, uint32_t s_size)
	{
	  _half_shift  = _N / 2;
	  _quart_shift = _half_shift / 2;
	  _gen_sin_lut();
	}

      //dtor
      ~Spectro()
	{
	  delete[] _sin_lut;
	}

      void fft(double* sig)
      {
	std::cout << "This is fft!" << std::endl;
      }
      
      //Discrete sine
      inline double dsin(uint16_t n)
      {
	n = n >= _N ? (n %_N) : n;  //Elminate multiple periods
	//Map second half period to first half period
	return (n >= _half_shift) ? 0.0-_sin_lut[n - _half_shift] : _sin_lut[n];
      }
      //Discrete cos
      inline double dcos(uint16_t n)
      {
	return dsin(n + _quart_shift);
      }
    private:
      typedef _T sig_t;
      uint16_t _half_shift;  //Half period shift to allocate sine LUT
      uint16_t _quart_shift; //Quarter period shift to calculate cosin values
      double* _sin_lut; //Sine value LUT
      
      //Will only generate a range of PI/2 sine table
      void _gen_sin_lut()
      {
	_sin_lut = new double[_half_shift];
	//_sin_lut = (double*)malloc(_half_shift * sizeof(double));
	for(uint16_t index = 0; index < _half_shift; ++index)
	  {
	    _sin_lut[index] = std::sin((double(index) / _N) * 2 * M_PI);
	    _sin_lut[index] = std::abs(_sin_lut[index]) < 10E-8 ? 0.0 : _sin_lut[index]; //this 10E-8 threshold should bechecked. Might depend on the precision of the machine.
	  }
      }
    };
}






/* void separate(complex<double>* a, int n) */
/* { */
/*   complex<double>* b = new complex<double>[n/2]; */
/*   for(int i=0; i<n/2; i++)    //copy all odd elements to heap storage */
/*     b[i] = a[i*2+1]; */
/*   for(int i=0; i<n/2; i++)    //copy all even elements to lower-half of a[] */
/*     a[i] = a[i*2]; */
/*   for(int i=0; i<n/2; i++)    // copy all odd (from heap) to upper-half of a[] */
/*     a[i+n/2] = b[i]; */
/*   delete[] b;                 //delete heap storage */
/* } */

/* //N must be a power-of-2 */
/* //Currently no check for this condition. */
/* //N input samples in X[] are FFT'd and results left in X[]. */
/* //Because of Nyquist theorem, N samples means */
/* //only first N/2 FFT results in X[] are the answer. */
/* //(upper half of X[] is a reflection with no new information). */
/* void fft2(complex<double>* X, int N) */
/* { */
/*   if(N < 2) */
/*     return; */
    
/*   else */
/*     { */
/*       separate(X,N);      //all evens to lower half, all odds to upper half */
/*       fft2(X, N/2);       //recurse even items */
/*       fft2(X+N/2, N);     //recurse odd  items */
/*       //combine results of two half recursions */
/*       for(int k=0; k<N/2; k++) */
/* 	{ */
/* 	  complex<double> e = X[k]; */
/* 	  complex<double> o = X[k+N/2]; */
/* 	  complex<double> w = exp(complex<double>(0,-2.*M_PI*k/N)); */
/* 	  X[k] = e + w * o; */
/* 	  X[k+N/2] = e - w * o; */
/*         } */
/*     } */
/* } */


#endif
