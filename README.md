# c2dmp-hsm

> **C**ompute **D**istance using **D**ifferences, **M**isplaced characters and **P**refix depth – **H**euristic **S**tring **M**atching

## Installation

#### Cloning the repository
```bash
git clone https://github.com/TsukiNi22/c2dmp-hsm
cd c2dmp-hsm
```

#### Build & Installation
```bash
export BUILD_DIR=build
cmake -S . -B $BUILD_DIR -DCMAKE_BUILD_TYPE=optimized
sudo cmake --build $BUILD_DIR --target install --parallel $(nproc)
```

#### Include
| Include                              | Content                                                                      |
| ------------------------------------ | ---------------------------------------------------------------------------- |
| -lc2dmp-hsm                          | `Nothing for now`                                                            |
| <c2dmp-hsm/c2dmp-hsm.hpp>            | `float c2dmp(const std::string_view a, const std::string_view b)`            |
| <c2dmp-hsm/algorithm/optimized.hpp>  | `float c2dmp_optimized(const std::string_view a, const std::string_view b)`  |
| <c2dmp-hsm/algorithm/simplified.hpp> | `float c2dmp_simplified(const std::string_view a, const std::string_view b)` |

## Description

This algorithm is used to determine the distance between 2 words. It generates a floating coefficient and the lowest one is the "nearest".

> [!WARNING]
> As stated in the title, this algorithm is heuristic, which means that the solution found isn't 100% technically the exact nearest but still aims for the best possible string that will match the wanted string and not necessarily the exact nearest one.

> [!CAUTION]
> The algorithm is case sensitive

### Parameters

- **s1** = the first string that will be used for the prefix search
- **s2** = the second string that will be used for the prefix comparison
- **prefixDepthSearch** (default: `3`) = depth of the prefix search
- **UINTN** (default: `uint32_t`) = type used for the computation of values, which limits the maximum value and influences the optimisation

### Core Principles

- **Distance**
```
The distance is the final floating value that determines the similarity between two given strings.
This value is computed by adding costs (which can be positive or negative). The value starts at '0'.
(The lower the value the better. If it goes below 0 it should represent a good match.)
```
- **Differences**
```
When comparing 2 characters they are normalized (such as A → a, Â → a, é → e, ...).
By default when both characters are equal the cost is '0'.
Differences are evaluated at '+1' for the cost and correspond to the difference between two characters at the same index of the strings.
During a comparison there is a possibility for the cost to be '-0.5', if two characters are equal before normalization
and also different from their normalized version.
```
- **Misplaced characters**
```
During the comparison of the characters in parallel we count the number of misplaced characters.
Misplaced characters are those that aren't equal to their corresponding character at the same position in the second array
but have another matching character in the second array that is also not equal to its corresponding position.
The cost of a misplaced character is by default '1' but it is multiplied by a coefficient.
The coefficient uses the number of characters separating both strings abs(len(s1) - len(s2)) marked as 'diff'.
The floor limit is when 'diff' is 0 and the ceiling limit is when 'diff' is 10.
Limits: 1.01 <= coef <= 1.25
coef = 1.01 + (diff / 10) * 0.25;
coef = clamp(coef, 1.01, 1.25);
```
- **Prefix depth**
```
The given prefix depth is the number of potential prefixes tested, each starting one character later than the previous in s1.
The size of the biggest prefix found is used for the final distance value computation.
The cost of a character in a prefix is by default '1' but it is multiplied by a coefficient.
The coefficient uses the depth where the biggest prefix was found marked as 'prefix_depth',
and the biggest prefix marked as 'prefix_size'.
The coefficient is proportional to the percentage of the prefix size compared to the length of s1.
Limits: 0 <= upper_limit <= 2, 0 <= coef <= upper_limit 
upper_limit = 2
for i in prefix_depth: 
    upper_limit *= (1 - (i / prefixDepthSearch))
coef = (upper_limit * (prefix_size / len(s1))); 
```

## Complexity

### Parameters

- **n** = `len(s1)`
- **m** = `len(s2)`
- **k** = `sizeof(UINTN)` → can be `1`, `2`, `4` or `8` for respectively `uint8_t`, `uint16_t`, `uint32_t` and `uint64_t`

### Time Complexity

| Case  | Complexity |
|------|------------|
| Best | `O(m + min(n, m))` |
| Avg  | `O(m + min(n, m))` |
| Worst| `O(m + min(n, m))` |

### Memory Complexity

> [!WARNING]
> constants only valid for `c2dmp-hsm_optimized.cpp` ([here](https://github.com/TsukiNi22/c2dmp-hsm/blob/main/c2dmp-hsm/c2dmp-hsm_optimized.cpp))

| Case  | Complexity |
|------|------------|
| Best | `O(1)` → constant (`637` bytes) |
| Avg  | `O(1)` → constant (`271 × k + 366` bytes) |
| Worst| `O(1)` → constant (`2534` bytes) |

## Licence
![CC-BY-NC-4.0](https://img.shields.io/badge/build-CC--BY--NC--4.0-brightgreen?style=for-the-badge&logo=github&label=Licence&link=https%3A%2F%2Fgithub.com%2FTsukiNi22%2Fc2dmp-hsm%2Fblob%2Fmain%2FLICENSE.md)
