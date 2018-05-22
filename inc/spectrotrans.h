#ifndef _SPECTROTRANS_H
#define _SPECTROTRANS_H

#include "mat.h"
#include <complex>
#include <cmath>
#include <typeinfo>
#include "trigolut.h"

namespace dsp
{
  //_SIG_T --- signal element type
  //_SPEC_T --- spectrogram element type
  //_N --- number of samples per frame
  template<typename _SIG_T, typename _SPEC_T, uint16_t _N>
  class SpectroTrans
    {
      typedef _SIG_T sig_t;
      typedef _SPEC_T spec_t;
    public:
      //ctor
      SpectroTrans(){ _trigo_lut.resize(_N); }
      
      //dtor
      ~SpectroTrans(){}

      //generate spectrogram. Leftover signal will be discarded.
      //spec --- target spectrogram
      //sig --- signal address
      //s_len --- signal length
      //offset --- frame offset
      //eff_size --- effective size, width of final spectrogram
      void gen_spectro(Mat<spec_t>& spec, const sig_t* sig, uint32_t s_len, uint16_t offset, uint16_t eff_size)
      {
	uint32_t spec_h = _calc_spec_h(s_len, offset); //calculate how many frames will be applied

	if(eff_size > _N / 2) //Will not accept spectrogram width > half frame length
	  return;
	
	spec.resize(eff_size, spec_h); //resize spectrogram
	
	for(uint32_t f_idx = 0; f_idx < spec_h; ++f_idx, sig += offset) //sliding frames
	  {
	    for(uint32_t k = 0; k < _N; ++k) //initialise frequency spectre for recursion
	      {
		_freq[k].real(sig[k]);
		_freq[k].imag(0);
	      }
	    
	    _eo_swap(_freq, _N);
	    fft2(_freq, _N / 2);
	    fft2(_freq + _N / 2, _N / 2);
	    
	    for(uint16_t k = 0; k < eff_size; ++k)
	      {
		_e_ele = _freq[k];
		_o_ele = _freq[k + _N / 2];
		_w.real(_trigo_lut.dcos(-k));
		_w.imag(_trigo_lut.dsin(-k));
		spec[f_idx][k] = static_cast<spec_t>(std::log10(std::abs(_e_ele + _w * _o_ele)));
	      }
	  }
      }

      //Radix-2 FFT
      void fft2(std::complex<spec_t>* X, uint16_t N = _N)
      {
	//Termination condition. For a 1 element signal, its FFT is itself.
	if(N == 1)
	  return;
    
	else
	  {
	    _eo_swap(X, N);      //all evens to lower half, all odds to upper half
	    fft2(X, N/2);       //recurse even items
	    fft2(X + N/2, N/2);     //recurse odd  items
	    //combine results of two half recursions

	    for(uint16_t k = 0; k < N / 2; k++)
	      {
		_e_ele = X[k];
		_o_ele = X[k + N / 2];
		_w.real(_trigo_lut.dcos(-k * _N / N));
		_w.imag(_trigo_lut.dsin(-k * _N / N));
		X[k] =         _e_ele + _w * _o_ele;
		X[k + N / 2] = _e_ele - _w * _o_ele;
	      }
	  }
      }
      
    private:
      TrigoLut<spec_t> _trigo_lut;

      //private variables to perform FFT
      std::complex<spec_t> _o_ele;
      std::complex<spec_t> _e_ele;
      std::complex<spec_t> _w;
      std::complex<spec_t> _freq[_N];
      std::complex<spec_t> _swap_buf[_N / 2];
      
      template<typename _AT>
      void _eo_swap(_AT* arr, uint16_t len)
      {
	uint16_t idx = 0;
	uint16_t half_len = len / 2;
	
	for(idx = 0; idx < half_len; ++idx) //Copy out all odd index elements
	  _swap_buf[idx] = arr[idx * 2 + 1];
	for(idx = 0; idx < half_len; ++idx) //Copy all even index elements lower half
	  arr[idx] = arr[idx * 2];

	std::memcpy(arr + half_len, _swap_buf, half_len * sizeof(_AT));
      }
                  
      uint32_t _calc_spec_h(uint32_t s_len, uint16_t offset)
      {
	if(s_len < _N || offset == 0) //signal length shorter than frame size
	  return 0;

	uint16_t fo_quo = _N / offset;    // frame / offset quotient
	uint16_t fo_rem = _N % offset;    // frame / offset remainder
	uint32_t spec_h = s_len / offset - fo_quo; //determine spectrogram height
	spec_h += s_len % offset < fo_rem ? 0 : 1;

	return spec_h;
      }
      
    };
}

#endif
