//$TCC -I../libCanvas -L../libCanvas/Release -llibCanvas fft_complex.c fft.c test.c -o test.exe && ./test
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libCanvas.h>
#include "fft.h"

#define W 128
#define H 128

fft_complex data[3][W * H];

/*
  12345
    3
   234
    3
   234
    3
*/

int main(void) {
  PCVS pCLoad = cvsCreate(W, H, NULL, 0, 0);
  cvsIOInit();
  cvsLoad(pCLoad, L".\\A.png");
  cvsIOUninit();

  PCVS pC = cvsCreate(5 * W, 6 * H, "FFT", 0, 0);
  cvsClear(pC, 0);
  cvsShow(pC, 1);
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      COLORREF c = cvsGetPx(pCLoad, i, j);
      cvsSetPx(pC, i    , j        , c);
      cvsSetPx(pC, i + W, j        , RGB(GetRValue(c), 0, 0));
      cvsSetPx(pC, i + W, j + H * 2, RGB(0, GetGValue(c), 0));
      cvsSetPx(pC, i + W, j + H * 4, RGB(0, 0, GetBValue(c)));
      data[0][i * W + j] = complex(GetRValue(c) / 255.0);
      data[1][i * W + j] = complex(GetGValue(c) / 255.0);
      data[2][i * W + j] = complex(GetBValue(c) / 255.0);
    }
  }
  cvsRefresh(pC);
  FFT2(data[0], W, H);
  FFT2(data[1], W, H);
  FFT2(data[2], W, H);
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      cvsSetPx(pC, i + W * 2, j        , RGB((int)(data[0][i * W + j].real * 255), 0, 0));
      cvsSetPx(pC, i + W * 2, j + H * 2, RGB(0, (int)(data[1][i * W + j].real * 255), 0));
      cvsSetPx(pC, i + W * 2, j + H * 4, RGB(0, 0, (int)(data[2][i * W + j].real * 255)));
      cvsSetPx(pC, i + W * 2, j + H * 1, RGB((int)(data[0][i * W + j].imag * 255), 0, 0));
      cvsSetPx(pC, i + W * 2, j + H * 3, RGB(0, (int)(data[1][i * W + j].imag * 255), 0));
      cvsSetPx(pC, i + W * 2, j + H * 5, RGB(0, 0, (int)(data[2][i * W + j].imag * 255)));
    }
  }
  cvsRefresh(pC);
  IFFT2(data[0], W, H);
  IFFT2(data[1], W, H);
  IFFT2(data[2], W, H);
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      cvsSetPx(pC, i + W * 3, j        , RGB((int)(data[0][i * W + j].real * 255), 0, 0));
      cvsSetPx(pC, i + W * 3, j + H * 2, RGB(0, (int)(data[1][i * W + j].real * 255), 0));
      cvsSetPx(pC, i + W * 3, j + H * 4, RGB(0, 0, (int)(data[2][i * W + j].real * 255)));
      cvsSetPx(pC, i + W * 4, j        , RGB((int)(data[0][i * W + j].real * 255), (int)(data[1][i * W + j].real * 255), (int)(data[2][i * W + j].real * 255)));
      cvsSetPx(pC, i + W * 3, j + H * 1, RGB((int)(data[0][i * W + j].imag * 255), 0, 0));
      cvsSetPx(pC, i + W * 3, j + H * 3, RGB(0, (int)(data[1][i * W + j].imag * 255), 0));
      cvsSetPx(pC, i + W * 3, j + H * 5, RGB(0, 0, (int)(data[2][i * W + j].imag * 255)));
      cvsSetPx(pC, i + W * 4, j + H * 1, RGB((int)(data[0][i * W + j].imag * 255), (int)(data[1][i * W + j].imag * 255), (int)(data[2][i * W + j].imag * 255)));
    }
  }
  cvsRefresh(pC);
  getchar();
  cvsShow(pC, 0);
  cvsDestroy(pC);
  cvsDestroy(pCLoad);
  return 0;
}