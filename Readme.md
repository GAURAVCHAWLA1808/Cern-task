# README

## Overview

This project includes three C++ programs that analyze floating-point compression techniques, compute mean squared error (MSE), and measure storage savings. The programs explore lossy compression methods like 16-bit half-precision conversion and least significant bit (LSB) zeroing.

## Files

### 1. `32-16bit_MSE.cpp`

**Description:**
- Converts 32-bit floating-point numbers to 16-bit IEEE 754 half-precision format.
- Computes Mean Squared Error (MSE), Mean Absolute Error (MAE), and Maximum Absolute Error.
- Saves the original and compressed data to binary files.
- Reports storage savings and error metrics.

**Key Functions:**
- `floatToHalf(float value)`: Converts a 32-bit float to 16-bit half-precision.
- `halfToFloat(uint16_t h)`: Converts 16-bit half-precision back to 32-bit float.
- MSE, MAE, and storage savings calculations.

**Output:**
- Prints file sizes, error metrics, and compression savings.

### 2. `distributions_mse.cpp`

**Description:**
- Generates random numbers from Uniform, Gaussian, and Exponential distributions.
- Applies lossy compression by zeroing out least significant bits.
- Computes MSE and statistical properties before and after compression.
- Saves original and compressed data to binary files.

**Key Functions:**
- `generate_data(size_t n, Distribution dist)`: Generates random numbers.
- `compress(float value, int bits_to_zero)`: Zeroes out LSBs for compression.
- `compute_mse(const vector<float>& original, const vector<float>& compressed)`: Computes MSE.
- `compute_stats(const vector<float>& data)`: Computes mean and standard deviation.

**Output:**
- Prints MSE for different distributions.
- Displays storage savings and statistical differences.

### 3. `og-vs-com_gzip.cpp`

**Description:**
- Generates a dataset of uniform random floating-point numbers.
- Applies different levels of LSB zeroing (8, 12, 16 bits).
- Computes MSE for each compression level.
- Saves data and compresses it using Gzip.
- Compares storage savings from LSB zeroing vs. Gzip compression.

**Key Functions:**
- `compressData(vector<float> &data, int bits_to_zero)`: Applies LSB zeroing.
- `calculateMSE(const vector<float> &original, const vector<float> &compressed)`: Computes MSE.
- `getGzipCompressedSize(const string &filename)`: Measures Gzip compression size.

**Output:**
- Prints MSE for different LSB zeroing levels.
- Displays storage savings from LSB zeroing and Gzip.

## How to Run

```sh
# Compile the programs
g++ 32-16bit_MSE.cpp -o 32-16bit_MSE
./32-16bit_MSE

g++ distributions_mse.cpp -o distributions_mse
./distributions_mse

g++ og-vs-com_gzip.cpp -o og-vs-com_gzip
./og-vs-com_gzip
```

## Dependencies

- C++17 or later
- Standard C++ libraries (`iostream`, `fstream`, `vector`, `cmath`, `random`, `filesystem`)
- Gzip (for `og-vs-com_gzip.cpp`)

## Results

- Compression significantly reduces storage size with minor errors.
- 16-bit half-precision achieves high savings but introduces rounding errors.
- Zeroing LSBs provides adjustable compression with controlled precision loss.
- Gzip compression is highly effective for storage reduction.

## Author

**Gaurav Chawla**

