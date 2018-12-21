#include "fft_complex.h"

inline fft_complex complex(double real) {
  return (fft_complex){real, 0};
}

inline fft_complex complex2(double real, double imag) {
  return (fft_complex){real, imag};
}

inline fft_complex complexAdd(fft_complex a, fft_complex b) {
  return (fft_complex){a.real + b.real, a.imag + b.imag};
}

inline fft_complex complexSub(fft_complex a, fft_complex b) {
  return (fft_complex){a.real - b.real, a.imag - b.imag};
}

inline fft_complex complexMul(fft_complex a, fft_complex b) {
  return (fft_complex){a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
}

