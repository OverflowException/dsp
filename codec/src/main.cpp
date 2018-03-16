#include <string>
#include <iostream>
#include <sstream>
#include "audiodec.h"
#include "spectro.h"
#include "spectrotrans.h"


#define M_PI 3.14159265358979323846

using namespace std;

// separate even/odd elements to lower/upper halves of array respectively.
// Due to Butterfly combinations, this turns out to be the simplest way 
// to get the job done without clobbering the wrong elements.
void separate (complex<double>* a, int n) {
    complex<double>* b = new complex<double>[n/2];  // get temp heap storage
    for(int i=0; i<n/2; i++)    // copy all odd elements to heap storage
        b[i] = a[i*2+1];
    for(int i=0; i<n/2; i++)    // copy all even elements to lower-half of a[]
        a[i] = a[i*2];
    for(int i=0; i<n/2; i++)    // copy all odd (from heap) to upper-half of a[]
        a[i+n/2] = b[i];
    delete[] b;                 // delete heap storage
}

// N must be a power-of-2, or bad things will happen.
// Currently no check for this condition.
//
// N input samples in X[] are FFT'd and results left in X[].
// Because of Nyquist theorem, N samples means 
// only first N/2 FFT results in X[] are the answer.
// (upper half of X[] is a reflection with no new information).
void fft2 (complex<double>* X, int N) {
    if(N < 2) {
        // bottom of recursion.
        // Do nothing here, because already X[0] = x[0]
    } else {
        separate(X,N);      // all evens to lower half, all odds to upper half
        fft2(X,     N/2);   // recurse even items
        fft2(X+N/2, N/2);   // recurse odd  items
        // combine results of two half recursions
        for(int k=0; k<N/2; k++) {
            complex<double> e = X[k    ];   // even
            complex<double> o = X[k+N/2];   // odd
                         // w is the "twiddle-factor"
            complex<double> w = exp( complex<double>(0,-2.*M_PI*k/N) );
            X[k    ] = e + w * o;
            X[k+N/2] = e - w * o;
        }
    }
}


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
  
  // complex<double>* sig = new complex<double>[1024];

  
  // for(int k = 0; k < 1024; ++k)
  //   {
  //     sig[k].real(data[k]);
  //     sig[k].imag(0);
  //   }
  // fft2(sig, 1024);


  
  bfin::Spectro<double> sp;
  bfin::SpectroTrans<double, double, 1024> spt;
  spt.gen_spectro(sp, data, size, 512, 100);
  //spt.fft(data, sig);
  for(uint32_t row = 0; row < sp.height(); ++row)
    {
      for(uint16_t col = 0; col < sp.width(); ++col)
	std::cout << sp[row][col] << " ";
      std::cout << std::endl;
    }

  
  // for(int k = 0; k < 1024; ++k)
  //   cout << sig[k] << endl;


  // std::cout << std::endl;
  // std::complex<double> c_test;
  // for(uint16_t k = 0; k < 16; ++k)
  //   {
  //     c_test.real(spt.dcos(-k));
  //     c_test.imag(spt.dsin(-k));
  //     std::cout << c_test;
  //     c_test = exp(std::complex<double>(0,-2.*M_PI*k/16));
  //     std::cout << " " << c_test << std::endl;
  //   }
  
  free(data);
  return 0;
}
