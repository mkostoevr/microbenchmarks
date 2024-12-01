# Microbenchmarks
## Zen 5 (9950x, core 15, ~5500MHz)

| Benchmark                                                                             | CPU time |
| ------------------------------------------------------------------------------------- | -------- |
| `search_in_sorted_array`/`upper_bound_linear`                                         | 18.8 ns  |
| `search_in_sorted_array`/`upper_bound_linear_avx2`                                    | 9.34 ns  |
| `search_in_sorted_array`/`upper_bound_linear_avx512`                                  | 8.97 ns  |
| `search_in_cardinalities`/`find_by_offset_linear`                                     | 5.23 ns  |
| `search_in_cardinalities`/`find_by_offset_create_offsets_linear`                      | 14.4 ns  |
| `search_in_cardinalities`/`find_by_offset_create_offsets_linear_avx2`                 | 12.7 ns  |
| `hsum`/`hsum_f32x4_sse1`                                                              | 0.114 ns |
| `hsum`/`hsum_f32x4_sse3`                                                              | 0.092 ns |
| `hsum`/`hsum_f32x4_hadd`                                                              | 0.092 ns |
| `function_alignment`/`*`                                                              | 0.734 ns |
