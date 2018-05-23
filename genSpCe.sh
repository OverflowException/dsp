#!/bin/bash

BIN_DIR="./bin"
SAMPLE_DIR="./samples"
DATA_DIR="./data"
SP="$BIN_DIR/genspect"

$SP $SAMPLE_DIR/one.wav 48000 $DATA_DIR/one_spectro.data $DATA_DIR/one_cepstra.data
$SP $SAMPLE_DIR/two.wav 48000 $DATA_DIR/two_spectro.data $DATA_DIR/two_cepstra.data
$SP $SAMPLE_DIR/three.wav 48000 $DATA_DIR/three_spectro.data $DATA_DIR/three_cepstra.data
