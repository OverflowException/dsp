This is a C++ project obtaining spectrogram and cepstrum coefficient array(CCA).

Dependencies: libavcodec, libavformat, libavutil, libswresample.
Build: make
Usage: 1.Prepare some audio files, each with a duration of a few seconds. Long audio files may result in overflow.
       2.Generate spectrogram and CCA with ./bin/spect.
       3.Plot spectrogram and CCA with ./data/plot_spect.py