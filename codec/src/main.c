#include "audiodec.h"

int main(int argc, char** argv)
{
 
    // check parameters
    if(argc != 3)
      {
        fprintf(stderr, "Usage: %s audiofile samplerate\n", argv[0]);
        return 0;
      }
    
    // decode data
    int sample_rate = atoi(argv[2]);
    printf("Sample rate = %d\n", sample_rate);
    double* data;
    int size;
    if (decode_audio_file(argv[1], sample_rate, &data, &size) != 0) {
        return -1;
    }
 
    // sum data
    for(int count=0; count < size; ++count)
      printf("%f\n", data[count]);
      
    // display result and exit cleanly
    free(data);
    return 0;
}
