#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "audiodec.h"
#include "spect.h"
#include "spectrotrans.h"
#include "cepstratrans.h"

using namespace std;
int main(int argc, char** argv)
{
 
  //Check parameters
  if(argc != 5)
    {
      std::cerr << "Usage: " << argv[0] << " audiofile samplerate spectrogram cepstralcoeff" << std::endl;
      return 0;
    }

  std::ofstream fs;
  
  //Decode data
  int sample_rate = atoi(argv[2]);
  cout << "Sample rate = " << sample_rate << std::endl;
  double* data;
  int size;
  if(decode_audio_file(argv[1], sample_rate, &data, &size) != 0)
    {
      return -1;
    }
  std::cout << "data size = " << size << std::endl;
  
  //Generate spectrogram
  dsp::Spect<double> sp;
  dsp::SpectroTrans<double, double, 1024> spt;
  spt.gen_spectro(sp, data, size, 200, 100);

  //Output spectrogram
  fs.open(argv[3]);
  fs << sp.height() << "\t" << sp.width() << "\n";
  fs << sp << std::endl;
  fs.close();
  
  //Generate cepstral coefficient array from spectrogram
  dsp::Spect<double> ce;
  dsp::CepstraTrans<double, double> cet(sp);
  cet.gen_cepstra(ce, 30);

  //Output CCA
  fs.open(argv[4]);
  fs << ce.height() << "\t" << ce.width() << "\n";
  fs << ce << std::endl;
  fs.close();
  
  free(data);
  return 0;
}
