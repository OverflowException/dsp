#include <string>
#include <iostream>
#include <sstream>
#include "audiodec.h"
#include "spectro.h"
#include "spectrotrans.h"

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
  printf("Sample rate = %d\n", sample_rate);
  double* data;
  int size;
  if(decode_audio_file(argv[1], sample_rate, &data, &size) != 0)
    {
      return -1;
    }

  bfin::Spectro<double> sp;
  bfin::SpectroTrans<double, double, 64> spt;
  spt.gen_spectro(sp, data, size, 32, 30);
  
    // bfin::Spectro<double, 1024, 512> spec(data, size);

    // std::string input;
    // std::istringstream iss;
    // uint16_t number;
    // while(true)
    //   {
    // 	std::cout << "1024 points in 2PI, input a positive integer" << std::endl;
    // 	std::cin >> input;
	
    // 	if(input == "q")
    // 	  break;

    // 	iss.clear(std::ios::goodbit);
    // 	iss.str(input);
	  
    // 	iss >> number;

    // 	std::cout << "dcos = "  << spec.dcos(number) << std::endl;
    // 	std::cout << "dsin = "  << spec.dsin(number) << std::endl;
    //   }

    // spec.fft(data);
    // // display result and exit cleanly
    free(data);
    return 0;
}
