# README

## Overview

This repository contains code and analysis related to lossy floating-point compression for different types of distributions: **Uniform Distribution**, **Gaussian (Normal) Distribution**, and **Exponential Distribution**.

Each folder contains:
- `root_plotting/`: Code for generating and analyzing histograms , graphs and data trends.
- `32-16bit_MSE.cpp`: Evaluates compression impact by converting 32 bit to 16 bit on storage and precision .
- `og-vs-com_gzip.cpp`: Evaluating compression impact by zeroing out 8,10,12,16 bits + gzip conversion on storage and precision .

### 1. `Task-report.md`

This file contains a detailed report and analysis on **Lossy Floating-point Compression: Understanding Storage Saving vs Precision Loss for Various Distributions**.

**Description:**
This document presents an experiment on lossy floating-point compression by zeroing out the least significant bits (LSBs) of the mantissa and analyzing its impact on storage savings and precision loss. Key findings reveal that bitwise manipulation alone does not reduce file size due to the fixed IEEE 754 format, but combining it with gzip compression or reducing bit-width (e.g., 32-bit to 16-bit) achieves meaningful storage savings. The study identifies optimal trade-offs between precision retention and compression efficiency, highlighting effective strategies for reducing storage without significant loss of accuracy.

---

### 2. `compress.cpp`

This file compares the effects of lossy floating-point compression across different probability distributions by zeroing out the least significant bits (LSBs) and analyzing the impact on storage savings and precision loss.

**Description:**
The program generates floating-point data from uniform, Gaussian, and exponential distributions, applies bit-masking compression to reduce precision, and evaluates its effects. By computing the Mean Squared Error (MSE), mean, and standard deviation before and after compression, the study highlights how different distributions respond to lossy compression. The data is stored in binary format, and storage savings are assessed by comparing file sizes, providing insights into the trade-offs between data precision and compression efficiency across distributions.

---

### 3. `root_plotting`

This folder contains code for generating and analyzing graphs related to:
- Storage Savings vs. Compression Techniques
- MSE vs. Compression Techniques
- Storage Savings vs. MSE (Sweet Spot Analysis)

A detailed analysis is available in `Task-report.md`.

---

### 4. `32-16bit_MSE.cpp`

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

---

### 5. `og-vs-com_gzip.cpp`

**Description:**
- Generates a dataset of floating-point numbers based on the specific distribution (Uniform, Gaussian, Exponential).
- Applies different levels of LSB zeroing (8, 10, 12, 16 bits).
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

---

This structure is replicated for **Uniform Distribution**, **Gaussian (Normal) Distribution**, and **Exponential Distribution**, ensuring a comprehensive analysis of compression efficiency across different data distributions.

## How to Run

```sh
# make sure that you are in the particular folder
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

## Author

**Gaurav Chawla**

