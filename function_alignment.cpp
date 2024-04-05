#include <benchmark/benchmark.h>

#define CREATE_BENCHMARK(type, asm_fn) \
	extern "C" type asm_fn(void); \
	inline BENCHMARK_ALWAYS_INLINE void \
	call_##asm_fn(benchmark::State &state) { \
		for (auto _ : state) { \
			asm_fn(); \
		} \
	} \
	BENCHMARK(call_##asm_fn)

CREATE_BENCHMARK(int, return_0_aligned_4096);

CREATE_BENCHMARK(int, return_0_cross_32);
CREATE_BENCHMARK(int, return_0_cross_64);
CREATE_BENCHMARK(int, return_0_cross_128);
CREATE_BENCHMARK(int, return_0_cross_4096);

BENCHMARK_MAIN();
