/*
  Copyright (c) 2013 Julien Pommier.

  Small test & bench for PFFFT, comparing its performance with the scalar FFTPACK, FFTW, Intel MKL, and Apple vDSP

  How to build: 

  on linux, with fftw3:
  gcc -o test_pffft -DHAVE_FFTW -msse -mfpmath=sse -O3 -Wall -W pffft.c test_pffft.c fftpack.c -L/usr/local/lib -I/usr/local/include/ -lfftw3f -lm

  on macos, without fftw3:
  clang -o test_pffft -DHAVE_VECLIB -O3 -Wall -W pffft.c test_pffft.c fftpack.c -L/usr/local/lib -I/usr/local/include/ -framework Accelerate

  on macos, with fftw3:
  clang -o test_pffft -DHAVE_FFTW -DHAVE_VECLIB -O3 -Wall -W pffft.c test_pffft.c fftpack.c -L/usr/local/lib -I/usr/local/include/ -lfftw3f -framework Accelerate

  on macos, with fftw3 and Intel MKL:
  clang -o test_pffft -I /opt/intel/mkl/include -DHAVE_FFTW -DHAVE_VECLIB -DHAVE_MKL  -O3 -Wall -W pffft.c test_pffft.c fftpack.c -L/usr/local/lib -I/usr/local/include/ -lfftw3f -framework Accelerate /opt/intel/mkl/lib/libmkl_{intel_lp64,sequential,core}.a

  on windows, with visual c++:
  cl /Ox -D_USE_MATH_DEFINES /arch:SSE test_pffft.c pffft.c fftpack.c
  
  build without SIMD instructions:
  gcc -o test_pffft -DPFFFT_SIMD_DISABLE -O3 -Wall -W pffft.c test_pffft.c fftpack.c -lm

 */

#include "pffft.h"
#include "test_pffft.h"
#include "fftpack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#ifdef HAVE_SYS_TIMES
#  include <sys/times.h>
#  include <unistd.h>
#endif

#ifdef HAVE_VECLIB
#  include <Accelerate/Accelerate.h>
#endif

#ifdef HAVE_FFTW
#  include <fftw3.h>
#endif

#ifdef HAVE_MKL
#  include <mkl_dfti.h>
#endif

#define MAX_OF(x,y) ((x)>(y)?(x):(y))

double frand() {
  return rand()/(double)RAND_MAX;
}

/* compare results with the regular fftpack */
extern void pffft_validate_N(int N, int cplx) {
  int Nfloat = N*(cplx?2:1);
  int Nbytes = Nfloat * sizeof(float);
  float *ref, *in, *out, *tmp, *tmp2;
  PFFFT_Setup *s = pffft_new_setup(N, cplx ? PFFFT_COMPLEX : PFFFT_REAL);
  int pass;

  if (!s) { printf("Skipping N=%d, not supported\n", N); return; }
  ref = pffft_aligned_malloc(Nbytes);
  in = pffft_aligned_malloc(Nbytes);
  out = pffft_aligned_malloc(Nbytes);
  tmp = pffft_aligned_malloc(Nbytes);
  tmp2 = pffft_aligned_malloc(Nbytes);

  for (pass=0; pass < 2; ++pass) {
    float ref_max = 0;
    int k;
    //printf("N=%d pass=%d cplx=%d\n", N, pass, cplx);
    // compute reference solution with FFTPACK
    if (pass == 0) {
      float *wrk = malloc(2*Nbytes+15*sizeof(float));
      for (k=0; k < Nfloat; ++k) {
        ref[k] = in[k] = frand()*2-1;
        out[k] = 1e30;
      }
      if (!cplx) {
        rffti(N, wrk);
        rfftf(N, ref, wrk);
        // use our ordering for real ffts instead of the one of fftpack
        {
          float refN=ref[N-1];
          for (k=N-2; k >= 1; --k) ref[k+1] = ref[k];
          ref[1] = refN;
        }
      } else {
        cffti(N, wrk);
        cfftf(N, ref, wrk);
      }
      free(wrk);
    }

    for (k = 0; k < Nfloat; ++k) ref_max = MAX_OF(ref_max, fabs(ref[k]));

      
    // pass 0 : non canonical ordering of transform coefficients  
    if (pass == 0) {
      // test forward transform, with different input / output
      pffft_transform(s, in, tmp, 0, PFFFT_FORWARD);
      memcpy(tmp2, tmp, Nbytes);
      memcpy(tmp, in, Nbytes);
      pffft_transform(s, tmp, tmp, 0, PFFFT_FORWARD);
      for (k = 0; k < Nfloat; ++k) {
        assert(tmp2[k] == tmp[k]);
      }

      // test reordering
      pffft_zreorder(s, tmp, out, PFFFT_FORWARD);
      pffft_zreorder(s, out, tmp, PFFFT_BACKWARD);
      for (k = 0; k < Nfloat; ++k) {
        assert(tmp2[k] == tmp[k]);
      }
      pffft_zreorder(s, tmp, out, PFFFT_FORWARD);
    } else {
      // pass 1 : canonical ordering of transform coeffs.
      pffft_transform_ordered(s, in, tmp, 0, PFFFT_FORWARD);
      memcpy(tmp2, tmp, Nbytes);
      memcpy(tmp, in, Nbytes);
      pffft_transform_ordered(s, tmp, tmp, 0, PFFFT_FORWARD);
      for (k = 0; k < Nfloat; ++k) {
        assert(tmp2[k] == tmp[k]);
      }
      memcpy(out, tmp, Nbytes);
    }

    {
      for (k=0; k < Nfloat; ++k) {
        if (!(fabs(ref[k] - out[k]) < 1e-3*ref_max)) {
          printf("%s forward PFFFT mismatch found for N=%d\n", (cplx?"CPLX":"REAL"), N);
          exit(1);
        }
      }
        
      if (pass == 0) pffft_transform(s, tmp, out, 0, PFFFT_BACKWARD);
      else   pffft_transform_ordered(s, tmp, out, 0, PFFFT_BACKWARD);
      memcpy(tmp2, out, Nbytes);
      memcpy(out, tmp, Nbytes);
      if (pass == 0) pffft_transform(s, out, out, 0, PFFFT_BACKWARD);
      else   pffft_transform_ordered(s, out, out, 0, PFFFT_BACKWARD);
      for (k = 0; k < Nfloat; ++k) {
        assert(tmp2[k] == out[k]);
        out[k] *= 1.f/N;
      }
      for (k = 0; k < Nfloat; ++k) {
        if (fabs(in[k] - out[k]) > 1e-3 * ref_max) {
          printf("pass=%d, %s IFFFT does not match for N=%d\n", pass, (cplx?"CPLX":"REAL"), N); break;
          exit(1);
        }
      }
    }

    // quick test of the circular convolution in fft domain
    {
      float conv_err = 0, conv_max = 0;

      pffft_zreorder(s, ref, tmp, PFFFT_FORWARD);
      memset(out, 0, Nbytes);
      pffft_zconvolve_accumulate(s, ref, ref, out, 1.0);
      pffft_zreorder(s, out, tmp2, PFFFT_FORWARD);
      
      for (k=0; k < Nfloat; k += 2) {
        float ar = tmp[k], ai=tmp[k+1];
        if (cplx || k > 0) {
          tmp[k] = ar*ar - ai*ai;
          tmp[k+1] = 2*ar*ai;
        } else {
          tmp[0] = ar*ar;
          tmp[1] = ai*ai;
        }
      }
      
      for (k=0; k < Nfloat; ++k) {
        float d = fabs(tmp[k] - tmp2[k]), e = fabs(tmp[k]);
        if (d > conv_err) conv_err = d;
        if (e > conv_max) conv_max = e;
      }
      if (conv_err > 1e-5*conv_max) {
        printf("zconvolve error ? %g %g\n", conv_err, conv_max); exit(1);
      }
    }

  }

  printf("%s PFFFT is OK for N=%d\n", (cplx?"CPLX":"REAL"), N); fflush(stdout);
  
  pffft_destroy_setup(s);
  pffft_aligned_free(ref);
  pffft_aligned_free(in);
  pffft_aligned_free(out);
  pffft_aligned_free(tmp);
  pffft_aligned_free(tmp2);
}

// void pffft_validate(int cplx) {
//   static int Ntest[] = { 16, 32, 64, 96, 128, 160, 192, 256, 288, 384, 5*96, 512, 576, 5*128, 800, 864, 1024, 2048, 2592, 4000, 4096, 12000, 36864, 0};
//   int k;
//   for (k = 0; Ntest[k]; ++k) {
//     int N = Ntest[k];
//     if (N == 16 && !cplx) continue;
//     pffft_validate_N(N, cplx);
//   }
// }

int array_output_format = 1;

#ifndef PFFFT_SIMD_DISABLE
void validate_pffft_simd(); // a small function inside pffft.c that will detect compiler bugs with respect to simd instruction 
#endif