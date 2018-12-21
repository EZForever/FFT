#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fft.h"

inline double FFT_PI(void) {return atan(1) * 4;}

void fftBinSort(fft_complex data[], int dataLen) {
  int i, j, k;
  fft_complex t;

  j = dataLen / 2;
  for(i = 1; i <= dataLen - 2; i++) {
    if(i < j) {
      t = data[j];
      data[j] = data[i];
      data[i] = t;
    }

    k = dataLen / 2;
    do {
      if(k > j) break;
      j -= k;
      k /= 2;
    } while(k);
    j += k;
  }
}

fft_complex *fftAlloc(int *dataLen) {
  int i = 1;
  while(1 << i < *dataLen) i++;
  *dataLen = 1 << i;
  return (fft_complex *)calloc(*dataLen, sizeof(fft_complex));
}

fft_complex *fftAlloc2(int *dataW, int *dataH) {
  int i = 1;
  while(1 << i < *dataW) i++;
  *dataW = 1 << i;
  i = 1;
  while(1 << i < *dataH) i++;
  *dataH = 1 << i;
  return (fft_complex *)calloc(*dataW * *dataH, sizeof(fft_complex));
}

void fft(fft_complex data[], int dataLen, int ifft) {
  int i;

  fftBinSort(data, dataLen);
  fft_complex *W = (fft_complex *)malloc(dataLen / 2 * sizeof(fft_complex));
  double angle;
  ifft = ifft ? 1 : -1;
  for(i = 0; i < dataLen / 2; i++) {
    angle = i * FFT_PI() * 2 / dataLen;
    W[i] = complex2(cos(angle), ifft * sin(angle));
  }

  int log2 = 0;
  i = dataLen;
  while(i >> 1) {
    i >>= 1;
    log2++;
  }
  for(i = 0; i < log2; i++) {
    int group = 1 << (log2 - 1 - i), dist = 1 << i, unit = 1 << i;
    for(int j = 0; j < group; j++) {
      int step = 2 * dist * j;
      for(int k = 0; k < unit; k++) {
        fft_complex t = complexMul(data[step + k + dist], W[dataLen * k / 2 / dist]);
        data[step + k + dist] = complexSub(data[step + k], t);
        data[step + k] = complexAdd(data[step + k], t);
      }
    }
  }
  if(ifft == 1) {
    for(i = 0; i < dataLen; i++) {
      data[i].real /= dataLen;
      data[i].imag /= dataLen;
    }
  }
}

void fft2(fft_complex data[], int dataW, int dataH, int ifft) {
  fft_complex dataColumn[dataH];
  int i, j;

  for(i = 0; i < dataH; i++)
    fft(&data[i * dataW], dataW, ifft);
  for(j = 0; j < dataW; j++) {
    for(i = 0; i < dataH; i++)
      dataColumn[i] = data[i * dataW + j];
    fft(dataColumn, dataH, ifft);
    for(i = 0; i < dataH; i++)
      data[i * dataW + j] = dataColumn[i];
  }
}