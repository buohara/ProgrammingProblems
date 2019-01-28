#include "CTFFTR2.h"

static const double twoPi       = 6.28318530718;
static const complex<double> I  = complex<double>(0.0, 1.0);

/**
 * OnetBitSet Helper function to determine if value is a power of two. Checks for one
 * bit set.
 *
 * @param  val Power of 2 candidate [in].
 * @return     True if input is power of two, false otherwise.
 */

static bool OnetBitSet(uint32_t val)
{
    uint32_t numBits = 0;
    while (val)
    {
        if (val & 0x1)
        {
            numBits++;
        }

        val >>= 1;
    }

    if (numBits == 1)
    {
        return true;
    }

    return false;
}

/**
 * GetWaveform Generate a superposition of simple sinusoids over a given domain and
 * input wave parameters.
 *
 * @param waves   List of input wave amplitudes, frequencies, and phases [in].
 * @param domain  Domain over which to evaluate intput waves [in].
 * @param samples Superposition of input waves. Assumed empty on input [out].
 */

void GetWaveform(vector<SinusoidsParams> &waves, vector<double> &domain, vector<complex<double>> &samples)
{
    assert(samples.size() == 0);
    samples.resize(domain.size(), 0.0);

    for (uint32_t i = 0; i < domain.size(); i++)
    {
        for (auto &wave : waves)
        {
            double amp = wave.amp;
            double freq = wave.freq;
            double shift = wave.shift;

            samples[i] += amp * exp((I * twoPi * freq * domain[i]) - shift);
        }
    }
}

/**
 * DFTDirect Compute DFT of input waveform by directly evaluating DFT sum.
 *
 * @param waveform Waveform samples to compute DFT for [in].
 * @param dft      DFT of input waveform. Assumed to be empty input [out].
 */

void DFTDirect(vector<complex<double>> &waveform, vector<complex<double>> &dft)
{
    assert(dft.size() == 0);
    bool powerOfTwo = OnetBitSet(waveform.size());
    assert(powerOfTwo);

    dft.resize(waveform.size(), 0.0);

    return;

    const double N = (double)waveform.size();
    
    for (uint32_t i = 0; i < dft.size(); i++)
    {
        for (uint32_t j = 0; j < waveform.size(); j++)
        {
            double k = (double)i;
            double n = (double)j;

            complex<double> factor = exp(-(I * twoPi / N) * k * n);
            dft[i] += waveform[j] * factor;
        }
    }
}

/**
 * DIT Radix-2 decimiation in time for FFT. Split input into even and odd components,
 * recursively compute N/2 size DFT, then merge results.
 *
 * @param waveform Input wave form to compute FFT DIT computation for.
 * @param fft      Results of FFT DIT. Assumed to be empty on input [out].
 */

static void DIT2(vector<complex<double>> &waveform, vector<complex<double>> &fft)
{
    assert(fft.size() == 0);

    uint32_t size = (uint32_t)waveform.size();
    uint32_t hSize = size / 2;

    if (size == 1)
    {
        fft[0] = waveform[0];
        return;
    }

    vector<complex<double>> evenIn(hSize, 0.0);
    vector<complex<double>> oddIn(hSize, 0.0);
    vector<complex<double>> evenOut(hSize, 0.0);
    vector<complex<double>> oddOut(hSize, 0.0);

    fft.resize(size, 0.0);

    for (uint32_t i = 0; i < hSize; i++)
    {
        evenIn[i] = waveform[2 * i];
        oddIn[i] = waveform[2 * i + 1];
    }

    DIT2(evenIn, evenOut);
    DIT2(oddIn, oddOut);

    for (uint32_t i = 0; i < hSize; i++)
    {
        complex<double> twiddle = exp(-(I * twoPi * (double)i) / (double)size);

        fft[i] = evenOut[i] + twiddle * oddOut[i];
        fft[i + hSize] = evenOut[i] - twiddle * oddOut[i];
    }
}

/**
 * FFT Compute a simple Cooley-Tukey FFT on power-of-two size input.
 *
 * @param waveform Waveform to compute FFT for [in].
 * @param fft      Result of FFT. Assumed empty on input.
 */

void FFT(vector<complex<double>> &waveform, vector<complex<double>> &fft)
{
    assert(fft.size() == 0);
    bool powerOfTwo = OnetBitSet(waveform.size());
    assert(powerOfTwo);

    DIT2(waveform, fft);
}

/**
 * TestDFT Test routine for FFT. Compute both a direct DFT and FFT of simple waveform.
 * Report computation times and compare outputs of both methods.
 */

void TestDFT()
{
    // Generate time domain and test waveform.

    vector<SinusoidsParams> waves;
    waves.push_back({ 1.0, 4.0, 0.0 });

    const uint32_t numSamples = 1024;
    const double dt = twoPi / (double)numSamples;

    vector<double> domain;

    for (uint32_t i = 0; i < numSamples; i++)
    {
        domain.push_back(i * dt);
    }

    vector<complex<double>> samples;
    GetWaveform(waves, domain, samples);

    // Time the DFT

    vector<complex<double>> dft;

    long long t1 = GetMilliseconds();
    DFTDirect(samples, dft);
    long long t2 = GetMilliseconds();

    printf("DFT time: %gs\n", (double)(t2 - t1) / 1000.0);

    vector<double> dftMagnitudes(dft.size(), 0.0);

    for (uint32_t i = 0; i < dft.size(); i++)
    {
        dftMagnitudes[i] = sqrt(dft[i].real() * dft[i].real() + dft[i].imag() * dft[i].imag());
    }

    // Time the FFT

    vector<complex<double>> fft;

    t1 = GetMilliseconds();
    FFT(samples, fft);
    t2 = GetMilliseconds();

    printf("FFT time: %gs\n", (double)(t2 - t1) / 1000.0);

    __debugbreak();

    vector<double> fftMagnitudes(fft.size(), 0.0);

    for (uint32_t i = 0; i < fft.size(); i++)
    {
        fftMagnitudes[i] = sqrt(fft[i].real() * fft[i].real() + fft[i].imag() * fft[i].imag());
    }

    // Compare results

    for (uint32_t i = 0; i < numSamples; i++)
    {
        printf("DFT[%d] = %g, FFT[%d] = %g\n", i, dftMagnitudes[i], i, fftMagnitudes[i]);
    }

    __debugbreak();
}