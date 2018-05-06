#ifndef _TRIGOLUT_H
#define _TRIGOLUT_H

#include <vector>
#include <cmath>

namespace dsp
{
  //_T --- value type of this trigonometric LUT
  //_N --- number of steps per period
  template<typename _T, int _N>
    class TrigoLut
    {
      typedef _T val_t;
      
    public:
      //ctor
      TrigoLut()
	{
	  if(_N % 4 != 0)
	    throw std::invalid_argument("Number of steps per period should be a multiple of 4!");
	    
	  this->_half_shift = _N / 2;
	  this->_quart_shift = _half_shift / 2;
	  
	  if(_N <= 0)
	    throw std::invalid_argument("Number of steps per period should not be negative!");

	  _gen_sin_lut();	  
	}
      ~TrigoLut(){_sin_lut.clear();};

      inline val_t dsin(int n)
      {
	n %= _N;
	n += _N;
	
	n = n >= _N ? (n % _N) : n;  //Elminate multiple periods
	//Map second half period to first half period
	return (n >= _half_shift) ? (val_t(0) - _sin_lut[n - _half_shift]) : _sin_lut[n];
      }

      inline val_t dcos(int n){ return dsin(n + _quart_shift); }
      
    private:
      std::vector<val_t> _sin_lut;
      int _half_shift;
      int _quart_shift;
      
      void _gen_sin_lut()
      {
	_sin_lut.resize(_half_shift);
	for(int idx = 0; idx < _half_shift; ++idx)
	  _sin_lut[idx] = std::sin((val_t(idx) / _N) * 2 * M_PI);
      }
    };
}



#endif
