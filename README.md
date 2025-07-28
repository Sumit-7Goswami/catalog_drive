# Secret Sharing Assignment

This repository contains:

- `catalog.cpp` — C++ implementation that:
  - Reads `testcase1.json` and `testcase2.json`
  - Decodes values in various bases
  - Applies Lagrange interpolation to find the constant term (secret)
  - Filters out invalid and negative results

- `json.hpp` — Header-only JSON library by nlohmann

## Usage:

```bash
g++ -std=c++17 catalog.cpp -o secret
./secret > output.txt
cat output.txt
