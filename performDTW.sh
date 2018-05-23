#!/bin/bash

BIN_DIR="./bin"
SAMPLE_DIR="./samples"
DATA_DIR="./data"
DTW="$BIN_DIR/dtwmatch"

$DTW $SAMPLE_DIR/one.wav $SAMPLE_DIR/one_test.wav 48000
$DTW $SAMPLE_DIR/one.wav $SAMPLE_DIR/two_test.wav 48000
$DTW $SAMPLE_DIR/one.wav $SAMPLE_DIR/three_test.wav 48000
echo -e "\n"

$DTW $SAMPLE_DIR/two.wav $SAMPLE_DIR/one_test.wav 48000
$DTW $SAMPLE_DIR/two.wav $SAMPLE_DIR/two_test.wav 48000
$DTW $SAMPLE_DIR/two.wav $SAMPLE_DIR/three_test.wav 48000
echo -e "\n"

$DTW $SAMPLE_DIR/three.wav $SAMPLE_DIR/one_test.wav 48000
$DTW $SAMPLE_DIR/three.wav $SAMPLE_DIR/two_test.wav 48000
$DTW $SAMPLE_DIR/three.wav $SAMPLE_DIR/three_test.wav 48000
echo -e "\n"
