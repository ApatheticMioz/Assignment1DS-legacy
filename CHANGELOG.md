# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [1.0.0] - Initial Archival Release

### Added
- Cache memory simulator (`q1.cpp`) with support for:
  - Direct-mapped cache backed by CSV memory file
  - Write-through and write-back policies
  - Write-allocate and write-around policies
  - FIFO eviction with 20-entry capacity
- Browser history simulator (`q2.cpp`) with support for:
  - URL visit tracking with frequency counting
  - Back/forward navigation
  - Top-K most visited URLs reporting
  - Cross-platform HTML page generation and opening
- CMake build configuration for C++20
- Sample memory data file (`Memory.csv`)

### Changed
- Repository standardized for public archival
- Documentation overhauled with professional README
- Added standard open-source health files (LICENSE, CONTRIBUTING, etc.)
