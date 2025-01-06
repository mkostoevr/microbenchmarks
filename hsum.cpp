#include <cstdint>
#include <x86intrin.h>

#include <benchmark/benchmark.h>

static void __attribute__((noinline))
warmup(benchmark::State &state)
{
	int i = 0;
	for (auto _ : state)
		benchmark::DoNotOptimize(i++);
}

BENCHMARK(warmup);

static void __attribute__((noinline))
hsum_f32x4_sse1(benchmark::State &state)
{
	__m128 v = _mm_set1_ps(0);
	for (auto _ : state) {
		__m128 shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1)); // [ C D | B A ]
		__m128 sums = _mm_add_ps(v, shuf);                           // sums = [ D+C C+D | B+A A+B ]
		shuf = _mm_movehl_ps(shuf, sums);                            // [   C   D | D+C C+D ], let the compiler avoid a mov by reusing shuf
		sums = _mm_add_ss(sums, shuf);
		benchmark::DoNotOptimize(_mm_cvtss_f32(sums));
	}
}

BENCHMARK(hsum_f32x4_sse1);

static void __attribute__((noinline))
hsum_f32x4_sse3(benchmark::State &state)
{
	__m128 v = _mm_set1_ps(0);
	for (auto _ : state) {
		__m128 shuf = _mm_movehdup_ps(v);  // broadcast elements 3,1 to 2,0
		__m128 sums = _mm_add_ps(v, shuf);
		shuf = _mm_movehl_ps(shuf, sums);  // high half -> low half
		sums = _mm_add_ss(sums, shuf);
		benchmark::DoNotOptimize(_mm_cvtss_f32(sums));
	}
}

BENCHMARK(hsum_f32x4_sse3);

static void __attribute__((noinline))
hsum_f32x4_hadd(benchmark::State &state)
{
	__m128 v = _mm_set1_ps(0);
	for (auto _ : state) {
		__m128 sums = _mm_hadd_ps(v, v);
		sums = _mm_hadd_ps(sums,sums);
		benchmark::DoNotOptimize(_mm_cvtss_f32(sums));
	}
}

BENCHMARK(hsum_f32x4_hadd);

#if 0

float hsum256_ps_avx(__m256 v) {
    __m128 vlow  = _mm256_castps256_ps128(v);
    __m128 vhigh = _mm256_extractf128_ps(v, 1); // high 128
    __m128 v128  = _mm_add_ps(vlow, vhigh);     // add the low 128
    return hsum_ps_sse3(v128);             // and inline the sse3 version, which is optimal for AVX
    // (no wasted instructions, and all of them are the 4B minimum)
}


///////// double
double hsum_pd_sse2(__m128d vd) {                      // v = [ B | A ]
    __m128 undef  = _mm_undefined_ps();                       // don't worry, we only use addSD, never touching the garbage bits with an FP add
    __m128 shuftmp= _mm_movehl_ps(undef, _mm_castpd_ps(vd));  // there is no movhlpd
    __m128d shuf  = _mm_castps_pd(shuftmp);
    return  _mm_cvtsd_f64(_mm_add_sd(vd, shuf));
}


///////// int32
int hsum_epi32_sse2(__m128i x) {
#ifdef __AVX__
    __m128i hi64  = _mm_unpackhi_epi64(x, x);           // 3-operand non-destructive AVX lets us save a byte without needing a mov
#else
    __m128i hi64  = _mm_shuffle_epi32(x, _MM_SHUFFLE(1, 0, 3, 2));
#endif
    __m128i sum64 = _mm_add_epi32(hi64, x);
    __m128i hi32  = _mm_shufflelo_epi16(sum64, _MM_SHUFFLE(1, 0, 3, 2));    // Swap the low two elements
    __m128i sum32 = _mm_add_epi32(sum64, hi32);
    return _mm_cvtsi128_si32(sum32);       // SSE2 movd
    //return _mm_extract_epi32(hl, 0);     // SSE4, even though it compiles to movd instead of a literal pextrd r32,xmm,0
}

int hsum_epi32_ssse3_slow_smallcode(__m128i x){
    x = _mm_hadd_epi32(x, x);
    x = _mm_hadd_epi32(x, x);
    return _mm_cvtsi128_si32(x);
}




// adapted from Marat's AVX http://stackoverflow.com/questions/13219146/how-to-sum-m256-horizontally/13222410#13222410
float hsum_ps_marat(__m128 x) {
    const __m128 sumQuad = x;
    const __m128 loDual = sumQuad;
    // hiDual = ( -, -, x3 + x7, x2 + x6 )
    const __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
    // sumDual = ( -, -, x1 + x3 + x5 + x7, x0 + x2 + x4 + x6 )
    const __m128 sumDual = _mm_add_ps(loDual, hiDual);
    // lo = ( -, -, -, x0 + x2 + x4 + x6 )
    const __m128 lo = sumDual;
    // hi = ( -, -, -, x1 + x3 + x5 + x7 )
    const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
    // sum = ( -, -, -, x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 )
    const __m128 sum = _mm_add_ss(lo, hi);  // add_ps defeat's clang's shuffle optimizer
    return _mm_cvtss_f32(sum);
}

float hsum256_slotin(__m256i x) {
    // Split into two 4-element registers.
    __m128 l = _mm256_extracti128_si256(x, 0);
    __m128 h = _mm256_extracti128_si256(x, 1);
    // Add them together (now we have 4 ints).
    l = _mm_add_epi32(l, h);
    // Horizontal add (now we have 2 ints).
    l = _mm_hadd_epi32(l, l);
    // Extract and add them normally.
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1);
}

#endif

BENCHMARK_MAIN();
