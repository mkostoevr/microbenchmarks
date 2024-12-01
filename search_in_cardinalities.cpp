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

/* Benchmarks. */

static void __attribute__((noinline))
find_by_offset_linear(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> cardinalities(count);
	for (size_t i = 0; i < count; i++) {
		cardinalities[i] = rng();
	}
	for (auto _ : state) {
		size_t offset = rng();
		size_t i = 0;
		while (i < count) {
			if (cardinalities[i] > offset)
				break;
			offset -= cardinalities[i];
			i++;
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(find_by_offset_linear);

static void __attribute__((noinline))
find_by_offset_create_offsets_linear(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> cardinalities(count);
	std::vector<uint64_t> offsets(count);
	for (size_t i = 0; i < count; i++) {
		cardinalities[i] = rng();
	}
	for (auto _ : state) {
		size_t offset = rng();
		size_t next_base = 0;
		for (size_t i = 0; i < count; i++) {
			offsets[i] = next_base + cardinalities[i];
			next_base = offsets[i];
		}
		size_t i = 0;
		while (i < count) {
			if (offsets[i] > offset)
				break;
			i++;
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(find_by_offset_create_offsets_linear);

static void __attribute__((noinline))
find_by_offset_create_offsets_linear_avx2(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> cardinalities(count);
	std::vector<uint64_t> offsets(count);
	for (size_t i = 0; i < count; i++) {
		cardinalities[i] = rng();
	}
	for (auto _ : state) {
		size_t offset = rng();
		size_t next_base = 0;
		for (size_t i = 0; i < count; i++) {
			offsets[i] = next_base + cardinalities[i];
			next_base = offsets[i];
		}
		size_t i = 0;
		__m256i x = _mm256_set1_epi64x(offset);
		while (i < count) {
			uint64_t mask = cmpgt64x4(&offsets[i], x);
			if (mask == 0) {
				i += 4;
			} else {
				i += __builtin_clz(mask) - 1;
				break;
			}
		}
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(find_by_offset_create_offsets_linear_avx2);

static void __attribute__((noinline))
find_by_offset_create_offsets_build_mask_ffs(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> cardinalities(count);
	std::vector<uint64_t> offsets(count);
	for (size_t i = 0; i < count; i++) {
		cardinalities[i] = rng();
	}
	for (auto _ : state) {
		size_t offset = rng();
		size_t next_base = 0;
		for (size_t i = 0; i < count; i++) {
			offsets[i] = next_base + cardinalities[i];
			next_base = offsets[i];
		}
		uint64_t mask = 0;
		for (size_t i = 0; i < count; i++) {
			mask |= (offsets[i] > offset) << i;
		}
		size_t i = mask != 0 ? __builtin_clz(mask) - 1 : 63;
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(find_by_offset_create_offsets_build_mask_ffs);

static void __attribute__((noinline))
find_by_offset_create_offsets_build_mask_ffs_avx2(benchmark::State &state)
{
	size_t count = 64;
	std::minstd_rand rng;
	std::vector<uint64_t> cardinalities(count);
	std::vector<uint64_t> offsets(count);
	for (size_t i = 0; i < count; i++) {
		cardinalities[i] = rng();
	}
	for (auto _ : state) {
		size_t offset = rng();
		size_t next_base = 0;
		for (size_t i = 0; i < count; i++) {
			offsets[i] = next_base + cardinalities[i];
			next_base = offsets[i];
		}
		__m256i x = _mm256_set1_epi64x(offset);
		uint64_t mask = (
			(cmpgt64x4(&offsets[0], x) << 0) |
			(cmpgt64x4(&offsets[4], x) << 4) |
			(cmpgt64x4(&offsets[8], x) << 8) |
			(cmpgt64x4(&offsets[12], x) << 12) |
			(cmpgt64x4(&offsets[16], x) << 16) |
			(cmpgt64x4(&offsets[20], x) << 20) |
			(cmpgt64x4(&offsets[24], x) << 24) |
			(cmpgt64x4(&offsets[28], x) << 28) |
			(cmpgt64x4(&offsets[32], x) << 32) |
			(cmpgt64x4(&offsets[36], x) << 36) |
			(cmpgt64x4(&offsets[40], x) << 40) |
			(cmpgt64x4(&offsets[44], x) << 44) |
			(cmpgt64x4(&offsets[48], x) << 48) |
			(cmpgt64x4(&offsets[52], x) << 52) |
			(cmpgt64x4(&offsets[56], x) << 56) |
			(cmpgt64x4(&offsets[60], x) << 60)
		);
		size_t i = mask != 0 ? __builtin_clz(mask) - 1 : 63;
		benchmark::DoNotOptimize(i);
	}
}

BENCHMARK(find_by_offset_create_offsets_build_mask_ffs_avx2);

BENCHMARK_MAIN();
