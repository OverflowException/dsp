#ifndef _MAT_H
#define _MAT_H

#include <cstdint>
#include <array>
#include <iostream>
#include <cstring>
#include <vector>
#include <iostream>


namespace dsp
{
  template<typename _T>
    class Mat
    {
    public:
      typedef _T value_type;
      //ctor
      //h --- height, number of spectras
      //w --- width, sample points per spectra
      Mat(uint32_t w = 0, uint32_t h = 0) : _w(w), _h(h)
	{
	  _data = NULL;
	  if(w != 0 && h != 0)
	    _alloc_data(w, h);
	}

      //dtor
      ~Mat(){ _dealloc_data(); }
      
      void resize(uint32_t w, uint32_t h)
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

      inline uint32_t width() const { return _w; }
      inline uint32_t height() const { return _h; }
      
      inline value_type*& operator[](uint32_t row){ return _data[row]; }
      inline value_type*& operator[](uint32_t row) const { return _data[row]; }

      friend std::ostream& operator<<(std::ostream& os, const Mat& m)
      {
	for(uint32_t row = 0; row < m.height(); ++row)
	{
	  for(uint32_t col = 0; col < m.width(); ++col)
	    os << m._data[row][col] << " ";
	  os << "\n";
	}

	return os;
      }
      
    private:
      uint32_t _w;
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

      inline void _alloc_data(uint32_t w, uint32_t h)
      {
	_data = new value_type*[h];
	for(uint32_t r_idx = 0; r_idx < h; ++r_idx)
	  _data[r_idx] = new value_type[w];
      }
    };
}

#endif
