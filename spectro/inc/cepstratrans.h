#ifndef _CEPSTRATRANS_H
#define _CEPSTRATRANS_H

#include "spect.h"
#include "trigolut.h"


namespace dsp
{
  //_SPEC_T --- spectrogram element type
  //_CEPS_T --- cepstrum element type
  template<typename _SPEC_T, typename _CEPS_T>
    class CepstraTrans
    {
      typedef _SPEC_T spectro_t;
      typedef _CEPS_T cepstra_t;

    public:
      //ctor
      CepstraTrans(const Spect<spectro_t>& spectro)
	{
	  _spectro_ptr = &spectro;
	  _trigo_lut.resize(_spectro_ptr->width() * 4);
	}
      
      //dtor
      ~CepstraTrans(){}

      void gen_cepstra(Spect<cepstra_t>& cepstra, uint16_t eff_size)
      {
	if(eff_size >= _spectro_ptr->width())
	  return;
	
	cepstra.resize(eff_size, _spectro_ptr->height());
	
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
	      for(sp_idx = 0; sp_idx < _spectro_ptr->width(); ++sp_idx, phase += delta_phase)
		ce_val +=  (*_spectro_ptr)[row][sp_idx] * _trigo_lut.dcos(phase);

	      ce_val *= 1 / sqrt(_spectro_ptr->width());
	      cepstra[row][ce_idx] = (ce_idx == 0 ? ce_val : ce_val * _cepstrum_const);
	    }
      }
      
    private:
      TrigoLut<cepstra_t> _trigo_lut;
      const Spect<spectro_t>* _spectro_ptr;

      const cepstra_t _cepstrum_const = std::sqrt(2);
    };
}







#endif
