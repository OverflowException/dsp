#ifndef _SPECT_H
#define _SPECT_H

#include <cstdint>
#include <array>
#include <iostream>
#include <cstring>
#include <vector>


namespace dsp
{
  template<typename _T>
    class Spect
    {
    public:
      typedef _T value_type;
      //ctor
      //h --- height, number of spectras
      //w --- width, sample points per spectra
      Spect(uint16_t w = 0, uint32_t h = 0) : _w(w), _h(h)
	{
	  _data = NULL;
	  if(w != 0 && h != 0)
	    _alloc_data(w, h);
	}

      //dtor
      ~Spect(){ _dealloc_data(); }
      
      void resize(uint16_t w, uint32_t h)
      {
	if(w == _w && h == _h)
	  return;
	
	_dealloc_data();
	if(h != 0 && w != 0)
	  {
	    _alloc_data(w, h);
	    _w = w; _h = h;
	  }
      }

      inline uint16_t width(){ return _w; }
      inline uint32_t height(){ return _h; }
      
      inline value_type*& operator[](uint32_t row){ return _data[row]; }
	
    private:
      uint16_t _w;
      uint32_t _h;
      value_type** _data;
      
      inline void _dealloc_data()
      {
	if(_data == NULL)
	  return;

	for(uint32_t r_idx = 0; r_idx < _h; ++r_idx)
	  delete[] _data[r_idx];

	delete[] _data;
	_data = NULL;
      }

      inline void _alloc_data(uint16_t w, uint32_t h)
      {
	_data = new value_type*[h];
	for(uint32_t r_idx = 0; r_idx < h; ++r_idx)
	  _data[r_idx] = new value_type[w];
      }
    };
}

#endif
