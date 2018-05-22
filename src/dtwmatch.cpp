#include <string>
#include <limits>
#include <cfloat>
#include <cassert>
#include <iostream>
#include "audiodec.h"
#include "mat.h"
#include "spectrotrans.h"
#include "cepstratrans.h"

using namespace std;

template<typename _T>
void genDistMat(const dsp::Mat<_T>& templ, const dsp::Mat<_T>& samp, dsp::Mat<_T>& dist)
{
  assert(templ.width() != 0 && templ.height() != 0 &&
	 samp.width() !=0 && samp.height() != 0);
  assert(templ.width() == samp.width());

  dist.resize(samp.height(), templ.height());
  //dRow --- row index of distance matrix
  //dCol --- column index of distance matrix
  //mCol --- column index of template and index
  uint32_t dRow, dCol, mCol;
  _T diff;
  for(dRow = 0; dRow < dist.height(); ++dRow)
    for(dCol = 0; dCol < dist.width(); ++dCol)
      {
	dist[dRow][dCol] = _T(0);
	for(mCol = 0; mCol < templ.width(); ++mCol)
	  //Replace canonical euclidian distance with absolute value
	  if((diff = templ[dRow][mCol] - samp[dCol][mCol]) < 0)
	    dist[dRow][dCol] += 0 - diff;
	  else
	    dist[dRow][dCol] += diff;
      }
}

template<typename _T>
void dtw(const dsp::Mat<_T>& dist)
{
  assert(dist.width() != 0 && dist.height() != 0);

  uint32_t row, col;
  //The first row
  for(col = 1; col < dist.width(); ++col)
    dist[0][col] += dist[0][col - 1];

  _T distMin;
  //The other rows
  for(row = 1; row < dist.height(); ++row)
    {
      //The first element of this row
      dist[row][0] += dist[row - 1][0];

      //The other elements of this row
      for(col = 1; col < dist.width(); ++col)
	{
	  distMin = dist[row][col - 1] < dist[row - 1][col] ? dist[row][col - 1] : dist[row - 1][col];
	  dist[row][col] += distMin < dist[row - 1][col - 1] ? distMin : dist[row - 1][col - 1];
	}
    }
}

int main(int argc, char** argv)
{
  if(argc != 4)
    {
      std::cerr << "Usage: " << argv[0] << " audiofile1 audiofile2 samplerate" << std::endl;
      return 0;
    }

  //Decode audio file
  double* data1, *data2;
  int size1, size2;
  int sample_rate = atoi(argv[3]);
  if(decode_audio_file(argv[1], sample_rate, &data1, &size1) != 0)
    {
      std::cerr << "Unable to decode " << argv[1] << "!";
      return 0;
    }

  if(decode_audio_file(argv[2], sample_rate, &data2, &size2) != 0)
    {
      std::cerr << "Unable to decode " << argv[2] << "!";
      return 0;
    }

  //Generate spectrograms
  dsp::Mat<double> sp1, sp2;
  dsp::SpectroTrans<double, double, 1024> spt;
  spt.gen_spectro(sp1, data1, size1, 200, 100);
  spt.gen_spectro(sp2, data2, size2, 200, 100);
  // std::cout << sp1 << std::endl;
  // std::cout << std::endl;

  // std::cout << sp2 << std::endl;
  // std::cout << std::endl;
  
  //Generate cepstral coefficient arrays from spectrograms
  dsp::Mat<double> ce1, ce2;
  dsp::CepstraTrans<double, double, 100> cet;
  cet.gen_cepstra(sp1, ce1, 30);
  cet.gen_cepstra(sp2, ce2, 30);

  dsp::Mat<double> spDist, ceDist;
  //Apply dtw to spectrograms
  genDistMat(sp1, sp2, spDist);
  //std::cout << spDist << std::endl;
  dtw(spDist);
  //Apply dtw to CCAs
  genDistMat(ce1, ce2, ceDist);
  dtw(ceDist);

  
  std::cout << "Spectrogram dtw = " << spDist[spDist.height() - 1][spDist.width() - 1] <<
    "\nCCA dtw = " << ceDist[ceDist.height() - 1][ceDist.width() - 1] << std::endl;
  
  return 0;
}
