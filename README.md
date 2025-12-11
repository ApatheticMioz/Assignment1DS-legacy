# Assignment1DS

Interactive C++20 exercises for a data structures course:
- [q1.cpp](q1.cpp): a simple direct-mapped cache simulator backed by a CSV "main memory" file.
- [q2.cpp](q2.cpp): a singly linked-list browser history that can open or generate HTML pages and report top-K visited URLs.

## Key Features
- Cache simulator loads `Memory.csv`, supports load/store, write-through vs write-back, and write-allocate vs write-around.
- Browser history supports visit, back/forward navigation, forward-clear on branch changes, and frequency-ranked reporting.
- Cross-platform HTML opening helper (Windows, Linux, macOS) for generated pages.
- CMake setup for building the browser history target.

## Tech Stack
- C++20
- CMake 3.29+

## Project Layout
- Core sources: [q1.cpp](q1.cpp), [q2.cpp](q2.cpp)
- Data: [Memory.csv](Memory.csv) (plus an unused copy) for the cache simulator
- Build artifacts (ignored): `cmake-build-debug/`

## Build and Run
### Using CMake (q2 target)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/Assignment1DS   # On Windows: build\Assignment1DS.exe
```

### Direct compile (q2)
```bash
g++ -std=c++20 q2.cpp -o browser_history
./browser_history       # On Windows: browser_history.exe
```

### Direct compile (q1 cache simulator)
```bash
g++ -std=c++20 q1.cpp -o cache_sim
./cache_sim             # On Windows: cache_sim.exe
```
> q1 currently hardcodes the memory file path (`D:\work\Assignment1DS\Memory.csv`). Update the path or place `Memory.csv` accordingly before running.

## Usage Notes
- q1: choose write policies, then enter decimal addresses and hex data; the cache evicts oldest entries once it reaches 20 nodes and updates the CSV for write-through/allocate cases.
- q2: menu-driven CLI for visiting URLs (generates `url.html`), navigating back/forward, listing history, and printing top-K most frequent URLs.

## Housekeeping
- `.gitignore` excludes build outputs, IDE metadata, and archives while preserving source CSV and HTML files.
