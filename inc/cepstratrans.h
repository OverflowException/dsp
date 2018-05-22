#ifndef _CEPSTRATRANS_H
#define _CEPSTRATRANS_H

#include "mat.h"
#include "trigolut.h"


namespace dsp
{
  //_SPEC_T --- spectrogram element type
  //_CEPS_T --- cepstrum element type
  //_N --- width of input spectrogram
  template<typename _SPEC_T, typename _CEPS_T, uint16_t _N>
    class CepstraTrans
    {
      typedef _SPEC_T spectro_t;
      typedef _CEPS_T cepstra_t;

    public:
      //ctor
      CepstraTrans(){ _trigo_lut.resize(_N * 4); }
      
      //dtor
      ~CepstraTrans(){}

      void gen_cepstra(Mat<spectro_t>& spectro, Mat<cepstra_t>& cepstra, uint16_t eff_size)
      {
	if(eff_size >= _N)
	  return;
	
	cepstra.resize(eff_size, spectro.height());
	
	uint32_t row; //Row index. Each row of spectrogram is a spectrum. Each row of CCA is a cepstrum.
	uint16_t sp_idx, ce_idx; //Spectrum element index, cepstrum element index
	int phase = 0;
	int delta_phase = 0;
	cepstra_t ce_val; //Intermediate value
	
	//Traverse rows of (CCA)
	for(row = 0; row < cepstra.height(); ++row)
	  //Traverse elements of CCA
	  for(ce_idx = 0; ce_idx < cepstra.width(); ++ce_idx)
	    {
	      ce_val = 0;
	      phase = ce_idx * 2;
	      delta_phase = ce_idx * 4;

	      //Traverse elements of spectrogram
	      for(sp_idx = 0; sp_idx < _N; ++sp_idx, phase += delta_phase)
		ce_val +=  spectro[row][sp_idx] * _trigo_lut.dcos(phase);

	      ce_val *= 1 / sqrt(_N);
	      cepstra[row][ce_idx] = (ce_idx == 0 ? ce_val : ce_val * _cepstrum_const);
	    }
      }
      
    private:
      TrigoLut<cepstra_t> _trigo_lut;
      const cepstra_t _cepstrum_const = std::sqrt(2);
    };
}







#endif
