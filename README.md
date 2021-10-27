# About

External for Windows version of Max 8 (Max/MSP). Extrapolates an integer (in `mod_n`) of a list from any positive index.
For a list `A={a_0, ..., a_m}` in `mod_n`.

`output = n * [index/list_len] + list_k`, where `k = (index % m)`.

Default values are `mod_12` and 256 elements set `a={0, 0, ... , 0}`.
