#pragma once

#include <vector>
#include <assert.h>
#include <math.h>
#include <complex>
#include "utils.h"

using namespace std;

struct SinusoidsParams
{
    double amp;
    double freq;
    double shift;
};

void GetWaveform(vector<SinusoidsParams> &waves, vector<double> &domain, vector<complex<double>> &samples);
void DFTDirect(vector<complex<double>> &samples, vector<complex<double>> &dft);
void FFT(vector<complex<double>> &waveform, vector<complex<double>> &fft);

void TestDFT();