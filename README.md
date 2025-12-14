# cache-browser-sim-cpp

> **Status:** Standardized for Public Archival

A collection of C++20 data structures exercises demonstrating linked list implementations through two interactive simulators:

1. **Cache Memory Simulator** - A direct-mapped cache backed by a CSV "main memory" file with configurable write policies.
2. **Browser History Simulator** - A singly linked-list browser history with URL tracking, navigation, and frequency reporting.

## Features

### Cache Simulator (`q1.cpp`)
- Loads memory data from CSV file
- Supports load and store operations
- Configurable cache hit policies: write-through vs write-back
- Configurable cache miss policies: write-allocate vs write-around
- FIFO eviction with 20-entry capacity
- Hexadecimal address/data conversion

### Browser History (`q2.cpp`)
- Visit URLs with frequency tracking
- Back/forward navigation
- Forward history clearing on branch changes
- Top-K most visited URLs reporting
- Cross-platform HTML page generation (Windows, Linux, macOS)

## Project Structure

```
.
├── q1.cpp           # Cache memory simulator
├── q2.cpp           # Browser history simulator
├── Memory.csv       # Sample memory data for cache simulator
├── CMakeLists.txt   # CMake build configuration
├── LICENSE          # MIT License
├── CONTRIBUTING.md  # Contribution guidelines
├── CHANGELOG.md     # Version history
└── README.md        # This file
```

## Requirements

- C++20 compatible compiler (g++ 10+, clang++ 10+, MSVC 2019+)
- CMake 3.29+ (optional, for CMake builds)

## Installation & Build

### Using CMake (Recommended)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Direct Compilation

**Cache Simulator:**
```bash
g++ -std=c++20 q1.cpp -o cache_sim
```

**Browser History:**
```bash
g++ -std=c++20 q2.cpp -o browser_history
```

## Usage

### Cache Simulator

```bash
./cache_sim    # or ./build/cache_sim
```

1. Select cache hit policy (write-through / write-back)
2. Select cache miss policy (write-allocate / write-around)
3. Enter addresses in decimal and data in hexadecimal
4. Type 'exit' to quit

> **Note:** Update the memory file path in `q1.cpp` or ensure `Memory.csv` is in the expected location.

### Browser History

```bash
./browser_history    # or ./build/browser_history
```

Menu options:
1. Visit a URL
2. Move back in history
3. Move forward in history
4. Display top K most frequently visited URLs
5. Display all history
6. Exit

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.
