#ifndef _CEPSTRATRANS_H
#define _CEPSTRATRANS_H

#include "spect.h"
#include "trigolut.h"

namespace dsp
{
  //_SPEC_T --- spectrogram element type
  //_CEPS_T --- cepstrum element type
  //_SPEC_N --- actual width of spectrogram
  //_CEPS_N --- actual width of cepstrum
  template<typename _SPEC_T, typename _CEPS_T, uint16_t _SPEC_N, uint16_t _CEPS_N>
    class CepstrumTrans
    {
      typedef _SPEC_T spectro_t;
      typedef _CEPS_T cepstra_t;

    public:
      //ctor
      CepstraTrans(){}
      
      //dtor
      ~CepstraTrans(){}

      void gen_cepstra(const Spect<spectro_t>& spectro, Spect<cepstra_t>& cepstra, uint16_t eff_size)
      {
	
      }
      
    private:
      TrigoLut<spec_t, _N> _trigo_lut;
    }
}







#endif
