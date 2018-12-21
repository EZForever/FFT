#ifndef __FFT_COMPLEX_H__
#define __FFT_COMPLEX_H__

typedef struct {
  double real;
  double imag;
} fft_complex;

inline fft_complex complex(double real);
inline fft_complex complex2(double real, double imag);
inline fft_complex complexAdd(fft_complex a, fft_complex b);
inline fft_complex complexSub(fft_complex a, fft_complex b);
inline fft_complex complexMul(fft_complex a, fft_complex b);

#endif