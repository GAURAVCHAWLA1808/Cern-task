# README

## Overview

This project includes three C++ programs that analyze floating-point compression techniques, compute mean squared error (MSE), and measure storage savings. The programs explore lossy compression methods like 16-bit half-precision conversion and least significant bit (LSB) zeroing.

## Files

### 1. `Task-report.md`

- This file contains a detailed report and analysis on lossy Floating-point Compression : Understanding Storage Saving vs Precision loss
  
**Description:**
This document presents an experiment on lossy floating-point compression by zeroing out the least significant bits (LSBs) of the mantissa and analyzing its impact on storage savings and precision loss. Key findings reveal that bitwise manipulation alone does not reduce file size due to the fixed IEEE 754 format, but combining it with gzip compression or reducing bit-width (e.g., 32-bit to 16-bit) achieves meaningful storage savings. The study identifies optimal trade-offs between precision retention and compression efficiency, highlighting effective strategies for reducing storage without significant loss of accuracy.

### 2. `root_plotting`
This folder contains code for generating and analyzing graphs related to:

- Storage Savings vs. Compression Techniques
- MSE vs. Compression Techniques
- Storage Savings vs. MSE (Sweet Spot Analysis)

A detailed analysis is available in Task-report.md.

### 3. `32-16bit_MSE.cpp`

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

### 4. `distributions_mse.cpp`

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

### 5. `og-vs-com_gzip.cpp`

**Description:**
- Generates a dataset of uniform random floating-point numbers.
- Applies different levels of LSB zeroing (8, 10 , 12, 16 bits).
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
# 32-16bit_MSE.cpp
g++ -std=c++17 32-16bit_MSE.cpp -o 32-16bit_MSE
./32-16bit_MSE

#distributions_mse.cpp
g++ -std=c++17 distributions_mse.cpp -o distributions_mse
./distributions_mse

#og-vs-com_gzip.cpp
g++ -std=c++17 og-vs-com_gzip.cpp -o og-vs-com_gzip
./og-vs-com_gzip

#root_ploting 
# To compile the program, replace `<filename>` with your actual output filename:
g++ -o <filename> root_plotting/<filename>.cpp $(root-config --cflags --glibs)
./<filename>

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

