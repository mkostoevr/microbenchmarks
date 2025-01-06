# Microbenchmarks
## Zen 5 (9950x, core 15, ~5500MHz)

| Benchmark                                                                             | CPU time |
| ------------------------------------------------------------------------------------- | -------- |
| `search_in_sorted_array`/`upper_bound_linear`                                         | 16.6 ns  |
| `search_in_sorted_array`/`upper_bound_linear_avx2`                                    | 9.67 ns  |
| `search_in_sorted_array`/`upper_bound_linear_avx512`                                  | 9.01 ns  |
| `search_in_cardinalities`/`find_by_offset_linear`                                     | 4.56 ns  |
| `search_in_cardinalities`/`find_by_offset_create_offsets_linear`                      | 14.5 ns  |
| `search_in_cardinalities`/`find_by_offset_create_offsets_linear_avx2`                 | 12.8 ns  |
| `hsum`/`hsum_f32x4_sse1`                                                              | 0.092 ns |
| `hsum`/`hsum_f32x4_sse3`                                                              | 0.092 ns |
| `hsum`/`hsum_f32x4_hadd`                                                              | 0.092 ns |
| `function_alignment`/`*`                                                              | 0.734 ns |
