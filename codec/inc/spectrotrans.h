#ifndef _spectrotrans
#define _spectrotrans

#include "spectro.h"
#include <complex>
#include <cmath>

namespace bfin
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
      //eff_size --- spectrogram effective size
      SpectroTrans()
	{
	  _half_shift  = _N / 2;
	  _quart_shift = _half_shift / 2;
	  _gen_sin_lut();
	  _swap_buf = new std::complex<spec_t>[_half_shift];
	}
      
      //dtor
      ~SpectroTrans(){ delete[] _sin_lut; delete[] _swap_buf; }

      //generate spectrogram. Leftover signal will be discarded.
      //spec --- target spectrogram
      //sig --- signal address
      //s_len --- signal length
      //offset --- frame offset
      //eff_size --- effective size, width of final spectrogram
      void gen_spectro(Spectro<spec_t>& spec, sig_t* sig, uint32_t s_len, uint16_t offset, uint16_t eff_size)
      {
	uint32_t spec_h = _calc_spec_h(s_len, offset); //calculate how many frames will be applied

	spec.resize(eff_size, spec_h);
	
	std::complex<spec_t>* freq = new std::complex<spec_t>[_N];

	for(uint32_t f_idx = 0; f_idx < spec_h; ++f_idx)
	  {
	    fft(sig + f_idx * offset, freq);
	    for(uint16_t k = 0; k < eff_size; ++k)
	      spec[f_idx][k] = std::abs(freq[k]);
	  }
      }
      
      //fft
      //sig --- signal frame, must be _T type in-place calculation.
      //freq --- 
      //f_size --- frame size, default equals _N
      void fft(sig_t* sig, std::complex<spec_t>* freq, uint32_t f_size = _N)
      {
	for(uint32_t k = 0; k < f_size; ++k)
	  {
	    freq[k].real(sig[k]);
	    freq[k].imag(0);
	  }

	std::cout << "fft" << std::endl;
	_rec_fft(freq, f_size);
      }
      
      //Discrete sine
      inline spec_t dsin(short n)
      {
	while(n < 0)   //Map negative to positive
	  n += _N;
	n = n >= _N ? (n % _N) : n;  //Elminate multiple periods
	//Map second half period to first half period
	return (n >= _half_shift) ? 0.0-_sin_lut[n - _half_shift] : _sin_lut[n];
      }
      //Discrete cos
      inline spec_t dcos(short n){ return dsin(n + _quart_shift); }

    private:
      uint16_t _half_shift;  //Half period shift to allocate sine LUT
      uint16_t _quart_shift; //Quarter period shift to calculate cosin values
      spec_t* _sin_lut; //Sine value LUT, half periods

      //private variables to perform FFT
      std::complex<spec_t> _o_ele;
      std::complex<spec_t> _e_ele;
      std::complex<spec_t> _w;
      std::complex<spec_t>* _swap_buf;
      
      //Will only generate a range of PI/2 sine table
      void _gen_sin_lut()
      {
	_sin_lut = new spec_t[_half_shift];
	for(uint16_t index = 0; index < _half_shift; ++index)
	  {
	    _sin_lut[index] = std::sin((spec_t(index) / _N) * 2 * M_PI);
	    _sin_lut[index] = std::abs(_sin_lut[index]) < 10E-8 ? 0.0 : _sin_lut[index]; //this 10E-8 threshold should bechecked. Might depend on the precision of the machine.
	  }
      }
      
      inline void _eo_swap(std::complex<spec_t>* arr, uint16_t len)
      {
	//std::complex<spec_t>* swap_buf = new std::complex<spec_t>[len / 2];
	
	for(uint16_t index = 0; index < _half_shift; ++index) //Copy out all odd index elements
	  _swap_buf[index] = arr[index * 2 + 1];
	for(uint16_t index = 0; index < _half_shift; ++index) //Copy all even index elements lower half
	  arr[index] = arr[index * 2];
	std::memcpy(arr + _half_shift, _swap_buf, _half_shift * sizeof(std::complex<spec_t>)); //Copy all odd index elements to upper half

	//delete[] swap_buf;
      }


      //Recursive FFT
      void _rec_fft(std::complex<spec_t>* X, uint16_t N)
      {
	std::cout << "in _rec_fft" << N << std::endl;
	//Termination condition. For a 1 element signal, its FFT is itself.
	if(N == 1)
	  return;
    
	else
	  {
	    _eo_swap(X, N);      //all evens to lower half, all odds to upper half
	    _rec_fft(X, N/2);       //recurse even items
	    _rec_fft(X + N/2, N/2);     //recurse odd  items
	    //combine results of two half recursions

	    for(uint16_t k = 0; k < N / 2; k++)
	      {
		_e_ele = X[k];
		_o_ele = X[k + N / 2];
		std::cout << "Here1" << std::endl;
		_w.real(dcos(k));
		std::cout << "Here2" << std::endl;
		_w.imag(dsin(k));
		std::cout << "Here3" << std::endl;
		X[k] = _e_ele + _w * _o_ele;
		X[k + N / 2] = _e_ele - _w * _o_ele;
	      }
	  }
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
