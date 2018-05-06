#include <string>
#include <iostream>
#include <sstream>
#include "audiodec.h"
#include "spect.h"
#include "spectrotrans.h"

using namespace std;
int main(int argc, char** argv)
{
 
  //Check parameters
  if(argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << " audiofile samplerate" << std::endl;
      return 0;
    }
    
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
  
  dsp::Spect<double> sp;
  dsp::SpectroTrans<double, double, 1024> spt;
  spt.gen_spectro(sp, data, size, 200, 100);
  //spt.fft(data, sig);

  std::cout << sp.height() << "\t" << sp.width() << std::endl;
  for(uint32_t row = 0; row < sp.height(); ++row)
    {
      for(uint16_t col = 0; col < sp.width(); ++col)
	std::cout << sp[row][col] << " ";
      std::cout << std::endl;
    }
  
  free(data);
  return 0;
}
