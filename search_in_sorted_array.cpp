#include <random>
#include <vector>
#include <x86intrin.h>

#include <benchmark/benchmark.h>

#ifndef COUNT
#define COUNT 64
#endif

/* Utilities. */

static inline uint64_t
cmpgt64x2(uint64_t *x_ptr, __m128i y_vec)
{
	__m128i x_vec = _mm_loadu_si128((__m128i *)x_ptr);
	__m128i mask = _mm_cmpgt_epi64(x_vec, y_vec);
	return _mm_movemask_pd((__m128d)mask);
}

static inline uint64_t
cmpgt64x4(uint64_t *x_ptr, __m256i y_vec)
{
	__m256i x_vec = _mm256_loadu_si256((__m256i *)x_ptr);
	__m256i mask = _mm256_cmpgt_epi64(x_vec, y_vec);
	return _mm256_movemask_pd((__m256d)mask);
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
upper_bound_binary(benchmark::State &state)
{
	size_t count = COUNT;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		uint64_t value = rng();
		uint64_t *begin = &values[0];
		uint64_t *end = &values[count];
		while (begin != end) {
			uint64_t *mid = begin + (end - begin) / 2;
			if (*mid > value) {
				end = mid;
			} else {
				begin = mid + 1;
			}
		}
		benchmark::DoNotOptimize(begin - &values[0]);
	}
}

BENCHMARK(upper_bound_binary);

static void __attribute__((noinline))
upper_bound_linear(benchmark::State &state)
{
	size_t count = COUNT;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		uint64_t value = rng();
		size_t i = 0;
		while (i < count) {
			if (values[i] > value)
				break;
			i++;
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear);

static void __attribute__((noinline))
upper_bound_linear_heuristical(benchmark::State &state)
{
	size_t count = COUNT;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		uint64_t value = rng();
		uint64_t first = values[0];
		uint64_t last = values[count - 1];
		if (first > value)
			continue; /* i = 0 */
		if (value >= last)
			continue; /* i = count */
		/* Guess the i to start. */
		size_t i = ((double)(value - first) /
			    (double)(last - first)) * count;
		if (values[i] <= value) {
			while (i < count) {
				if (values[++i] > value)
					break;
			}
		} else {
			while (i > 0) {
				if (values[i - 1] <= value)
					break;
				i--;
			}
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear_heuristical);

static void __attribute__((noinline))
upper_bound_linear_sse4_2(benchmark::State &state)
{
	size_t count = COUNT;
	std::minstd_rand rng;
	std::vector<uint64_t> values(count);
	init_dataset(values, rng);
	for (auto _ : state) {
		__m128i value = _mm_set1_epi64x(rng());
		size_t i = 0;
		while (i < count) {
			uint64_t mask = cmpgt64x2(&values[i], value);
			if (mask == 0) {
				i += 2;
			} else {
				i += __builtin_ctz(mask);
				break;
			}
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(upper_bound_linear_sse4_2);

static void __attribute__((noinline))
upper_bound_linear_avx2(benchmark::State &state)
{
	size_t count = COUNT;
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
	size_t count = COUNT;
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
