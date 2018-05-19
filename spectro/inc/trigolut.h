#ifndef _TRIGOLUT_H
#define _TRIGOLUT_H

#include <vector>
#include <cmath>

namespace dsp
{
  //_T --- value type of this trigonometric LUT
  //_N --- number of steps per period
  template<typename _T>
    class TrigoLut
    {
      typedef _T val_t;
      
    public:
      //ctor
      TrigoLut(int size = 0)
	{
	  if(size != 0)
	    resize(size);
	}
      ~TrigoLut(){ _sin_lut.clear(); };

      void resize(int size)
      {
	if(size % 4 != 0)
	  throw std::invalid_argument("Number of steps per period should be a multiple of 4!");

	if(size <= 0)
	  throw std::invalid_argument("Number of steps per period should not be negative!");

	this->_nsteps = size;
	this->_half_shift = _nsteps / 2;
	this->_quart_shift = _half_shift / 2;

	_gen_sin_lut();
      }

      
      inline val_t dsin(int n)
      {
	//Eliminate multiple periods
	n %= _nsteps;

	//Map negative phase to positive
	if(n < 0)
	  n += _nsteps;
	
	//Map second half period to first half period
	return (n >= _half_shift) ? (val_t(0) - _sin_lut[n - _half_shift]) : _sin_lut[n];
      }

      inline val_t dcos(int n){ return dsin(n + _quart_shift); }
      
    private:
      std::vector<val_t> _sin_lut;
      int _nsteps;
      int _half_shift;
      int _quart_shift;
      
      void _gen_sin_lut()
      {
	_sin_lut.resize(_half_shift);
	for(int idx = 0; idx < _half_shift; ++idx)
	  _sin_lut[idx] = std::sin((val_t(idx) / _nsteps) * 2 * M_PI);
      }
    };
}



#endif
