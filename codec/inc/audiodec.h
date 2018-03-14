#include <stdio.h>
#include <stdlib.h>
 
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
 
 
int decode_audio_file(const char* path, const int sample_rate, double** data, int* size);
