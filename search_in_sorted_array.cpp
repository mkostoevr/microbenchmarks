#include <random>
#include <vector>
#include <x86intrin.h>

#include <benchmark/benchmark.h>

/* Utilities. */

static inline uint64_t
cmpgt64x4(uint64_t *x_ptr, __m256i y_vec)
{
	__m256i x_vec = _mm256_loadu_si256((__m256i *)x_ptr);
	__m256i mask = _mm256_cmpgt_epi64(x_vec, y_vec);
	return _mm256_movemask_ps((__m256)mask);
}

static inline uint64_t
cmpgt64x8(uint64_t *x_ptr, __m512i y_vec)
{
	__m512i x_vec = _mm512_loadu_si512((__m512i *)x_ptr);
	__mmask16 mask = _mm512_cmpgt_epi64_mask(x_vec, y_vec);
	return (uint64_t)mask;
}

static inline void
init_dataset(std::vector<uint64_t> &values, std::minstd_rand &rng)
{
	for (size_t i = 0; i < values.size(); i++) {
		values[i] = rng();
	}
	std::sort(values.begin(), values.end());
}

/* Benchmarks. */

static void __attribute__((noinline))
warmup(benchmark::State &state)
{
	int i = 0;
	for (auto _ : state)
		benchmark::DoNotOptimize(i++);
}

BENCHMARK(warmup);

static void __attribute__((noinline))
upper_bound_linear(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		uint64_t value = rng();
		size_t i = 0;
		while (i < count) {
			if (values[i++] > value)
				break;
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear);

static void __attribute__((noinline))
upper_bound_linear_avx2(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		__m256i value = _mm256_set1_epi64x(rng());
		size_t i = 0;
		while (i < count) {
			uint64_t mask = cmpgt64x4(&values[i], value);
			if (mask == 0) {
				i += 4;
			} else {
				i += __builtin_ctz(mask);
				break;
			}
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear_avx2);

static void __attribute__((noinline))
upper_bound_linear_avx512(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		__m512i value = _mm512_set1_epi64(rng());
		size_t i = 0;
		while (i < count) {
			uint64_t mask = cmpgt64x8(&values[i], value);
			if (mask == 0) {
				i += 8;
			} else {
				i += __builtin_ctz(mask);
				break;
			}
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear_avx512);

BENCHMARK_MAIN();
