#!/bin/bash

PL="plot_spect.py"

python $PL sp one_spectro.data
python $PL sp two_spectro.data
python $PL sp three_spectro.data

python $PL ce one_cepstra.data
python $PL ce two_cepstra.data
python $PL ce three_cepstra.data
