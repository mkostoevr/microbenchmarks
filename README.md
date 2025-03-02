# Microbenchmarks
## Zen 5, 5500MHz

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

## Tiger Lake, 3000MHz

| Benchmark                                                                             | CPU time |
| ------------------------------------------------------------------------------------- | -------- |
| `search_in_sorted_array_32`/`upper_bound_binary`                                      | 32.1 ns  |
| `search_in_sorted_array_32`/`upper_bound_linear`                                      | 19.6 ns  |
| `search_in_sorted_array_32`/`upper_bound_linear_heuristical`                          | 24.3 ns  |
| `search_in_sorted_array_32`/`upper_bound_linear_sse4_2`                               | 18.7 ns  |
| `search_in_sorted_array_32`/`upper_bound_linear_avx2`                                 | 18.7 ns  |
| `search_in_sorted_array_32`/`upper_bound_linear_avx512`                               | 14.2 ns  |
| `search_in_sorted_array_64`/`upper_bound_binary`                                      | 39.0 ns  |
| `search_in_sorted_array_64`/`upper_bound_linear`                                      | 28.0 ns  |
| `search_in_sorted_array_64`/`upper_bound_linear_heuristical`                          | 25.2 ns  |
| `search_in_sorted_array_64`/`upper_bound_linear_sse4_2`                               | 23.3 ns  |
| `search_in_sorted_array_64`/`upper_bound_linear_avx2`                                 | 20.7 ns  |
| `search_in_sorted_array_64`/`upper_bound_linear_avx512`                               | 16.9 ns  |
| `search_in_sorted_array_128`/`upper_bound_binary`                                     | 48.5 ns  |
| `search_in_sorted_array_128`/`upper_bound_linear`                                     | 40.7 ns  |
| `search_in_sorted_array_128`/`upper_bound_linear_heuristical`                         | 28.3 ns  |
| `search_in_sorted_array_128`/`upper_bound_linear_sse4_2`                              | 32.4 ns  |
| `search_in_sorted_array_128`/`upper_bound_linear_avx2`                                | 24.3 ns  |
| `search_in_sorted_array_128`/`upper_bound_linear_avx512`                              | 20.2 ns  |
| `search_in_sorted_array_256`/`upper_bound_binary`                                     | 57.1 ns  |
| `search_in_sorted_array_256`/`upper_bound_linear`                                     | 61.6 ns  |
| `search_in_sorted_array_256`/`upper_bound_linear_heuristical`                         | 28.9 ns  |
| `search_in_sorted_array_256`/`upper_bound_linear_sse4_2`                              | 47.3 ns  |
| `search_in_sorted_array_256`/`upper_bound_linear_avx2`                                | 31.4 ns  |
| `search_in_sorted_array_256`/`upper_bound_linear_avx512`                              | 24.6 ns  |
| `hsum`/`hsum_f32x4_sse1`                                                              | 0.334 ns |
| `hsum`/`hsum_f32x4_sse3`                                                              | 0.334 ns |
| `hsum`/`hsum_f32x4_hadd`                                                              | 0.334 ns |
