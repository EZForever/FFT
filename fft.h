#ifndef __FFT_H__
#define __FFT_H__
#include "fft_complex.h"

//FFT_PI: Value of pi.
inline double FFT_PI(void);
//fftBinSort: "Sort" input data array in binary reverse order. Called by fft().
void fftBinSort(fft_complex data[], int dataLen);
//fftAlloc: Allocate sufficent space for fft(). free() after usage.
fft_complex *fftAlloc(int *dataLen);
fft_complex *fftAlloc2(int *dataW, int *dataH);
//fft: Actual FFT operactions. dataLen must be a power of 2.
void fft(fft_complex data[], int dataLen, int ifft);
void fft2(fft_complex data[], int dataW, int dataH, int ifft);

//These are for remembering things easlier.
#define FFT(data, dataLen) fft((data), (dataLen), 0)
#define IFFT(data, dataLen) fft((data), (dataLen), 1)
#define FFT2(data, dataW, dataH) fft2((data), (dataW), (dataH), 0)
#define IFFT2(data, dataW, dataH) fft2((data), (dataW), (dataH), 1)

#endif