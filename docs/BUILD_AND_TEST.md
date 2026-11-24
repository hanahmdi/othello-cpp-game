# Build and Verification Notes

This repository includes an unmodified historical source under `archive/` and a separate tested C++17 extension under `src/`.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## What was checked

- Initial board: four discs, two of each color
- Four legal opening moves for each color
- Invalid coordinates, occupied squares, and illegal passing are rejected
- Black's opening move at `(3, 5)` flips one white disc
- 25 seeded, complete games finish within a bounded number of turns
- Occupied cell counts remain within `[4, 64]`

The extension was also compiled and tested with address and undefined-behavior sanitizers. This does not verify the original implementation's completeness or establish game-engine correctness for all possible positions.
