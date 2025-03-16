# Exploring Lossy Floating-Point Compression: Understanding Storage Savings vs. Precision Loss

## Introduction

In this experiment, we explore lossy floating-point compression by manipulating the least significant bits (LSBs) of the mantissa and analyzing its impact on storage savings and precision loss. The goal is to find an optimal balance between reducing storage space and maintaining computational accuracy.

## Experiment Overview

We generated a large dataset of floating-point numbers from three different distributions:

- **Uniform Distribution**
- **Gaussian (Normal) Distribution**
- **Exponential Distribution**

Each distribution is stored in separate folders: `Uniform Distribution`, `Gaussian (Normal) Distribution`, and `Exponential Distribution`, containing:

- `root_plotting`: Code for visualizing storage savings, MSE, and compression trade-offs.
- `32-16bit_MSE.cpp`: Computes precision loss metrics for 32-bit to 16-bit conversion.
- `og-vs-com_gzip.cpp`: Applies LSB zeroing and gzip compression to analyze storage savings.

We applied lossy compression by zeroing out between 8 and 16 LSBs of the mantissa. We stored both the full-precision and compressed data in binary format and analyzed:

- On-disk file sizes to measure storage savings
- Statistical properties before and after compression
- Mean Squared Error (MSE) to quantify precision loss
- Visualization of distribution changes

## Key Finding: Zeroing Out LSBs Alone Does Not Reduce File Size

A crucial realization emerged during the analysis: zeroing out the least significant bits of the mantissa does not change the file size. This is because:

- In standard IEEE 754 floating-point representation, each float is stored in a fixed 32-bit (4-byte) format.
- Modifying the least significant bits alters precision but does not alter the byte representation in memory or storage.
- The file size remains unchanged because each value still occupies the same number of bytes on disk.

## Why Does Bitwise Manipulation Not Reduce Storage?

Floating-point numbers are stored in a structured binary format:

| Component  | Bits |
|------------|------|
| Sign       | 1    |
| Exponent   | 8    |
| Mantissa   | 23   |

Zeroing out the least significant bits of the mantissa only affects precision but does not change the overall storage requirement. The disk space is determined by the number of floating-point values stored, not by how much of the mantissa is used.

## Compression Methods That Work

To achieve actual file size reduction, we explored two additional techniques:

1. **Applying gzip compression after zeroing out LSBs**: This exploits redundancy introduced by zeroed bits, leading to real storage savings.
2. **Converting from 32-bit to 16-bit floating point**: This halves storage requirements but introduces significant precision loss.

## Experimental Results

### Storage Savings and Precision Loss

## Uniform Distribution

| Method                      | Original Size (MB) | Compressed Size (MB) | Storage Savings (%) | MSE   |
|-----------------------------|-------------------|-------------------|-----------------|---------------|
| No Compression              | 3.81              | 3.81              | 0%              | 0.0           |
| gzip Compression            | 3.81              | 3.42              | 10.2%           | 0.0           |
| 8-bit zeroing + gzip        | 3.81              | 2.72              | 28.6%           | 4.41e-11      |
| 10-bit zeroing + gzip       | 3.81              | 2.47              | 35.04%          | 7.08e-10      |
| 12-bit zeroing + gzip       | 3.81              | 2.14              | 43.8%           | 1.13e-08      |
| 16-bit zeroing + gzip       | 3.81              | 1.60              | 58.1%           | 2.90e-06      |
| 32-bit to 16-bit conversion | 3.81              | 1.90              | 50.0%           | 171799        |


## Graph Analysis
1. Storage Savings vs. Compression Techniques

This graph illustrates the percentage of storage savings achieved using different compression techniques. It helps visualize how various methods impact storage efficiency.

![storage_savings](https://github.com/user-attachments/assets/871b477f-3029-4473-8f05-7e5720d254a0)

2. MSE vs. Compression Techniques

This plot shows the Mean Squared Error (MSE) introduced by each compression technique. It highlights the trade-off between compression and data accuracy. 

![MSE_vs_Techniques](https://github.com/user-attachments/assets/afb2fa17-4e04-4d85-8bfa-e9a643e5fdef)

3. Storage Savings vs. MSE (Sweet Spot Analysis)

This graph helps identify the optimal compression technique that provides the best balance between storage savings and minimal loss in precision. The "Sweet Spot" is highlighted, representing the most efficient technique.

![sweet_spot](https://github.com/user-attachments/assets/dbd37a95-0a33-4bab-aa94-22df3e6ec3e0)

## Finding the Sweet Spot
To determine the best trade-off between storage savings and precision loss, we calculated a **Compression Efficiency Metric**:

Compression Efficiency = Storage Savings (%)​ / MSE 

- **8-bit zeroing + gzip** is the most efficient method, offering **28.6% storage savings** with minimal precision loss (**MSE = 4.41e-11**).
- **10-bit zeroing  + gzip** is another strong option, providing **35% storage savings** with an **MSE of 7.07e-10**.
- **16-bit zeroing or 32-bit to 16-bit conversion** results in excessive precision loss, making them less ideal for precision-critical applications.

#### Gaussian Distribution

| Method                     | Original Size (MB) | Compressed Size (MB) | Storage Savings (%) | MSE         |
|----------------------------|--------------------|----------------------|---------------------|-------------|
| 32-bit to 16-bit conversion| 3.81               | 1.90                 | 50.0%               | 8.27386e-05 |
| gzip Compression           | 3.81               | 3.53                 | 7.3%                | 0.0         |
| 8-bit zeroing + gzip       | 3.81               | 2.87                 | 24.7%               | 1.6735e-10  |
| 10-bit zeroing + gzip      | 3.81               | 2.68                 | 29.7%               | 2.69561e-09 |
| 12-bit zeroing + gzip      | 3.81               | 2.42                 | 36.4%               | 4.32203e-08 |
| 16-bit zeroing + gzip      | 3.81               | 1.79                 | 53.1%               | 1.09706e-05 |

#### Exponential Distribution

| Method                     | Original Size (MB) | Compressed Size (MB) | Storage Savings (%) | MSE         |
|----------------------------|--------------------|----------------------|---------------------|-------------|
| 32-bit to 16-bit conversion| 3.81               | 1.90                 | 50.0%               | 0.000140414 |
| gzip Compression           | 3.81               | 3.47                 | 8.9%                | 0.0         |
| 8-bit zeroing + gzip       | 3.81               | 2.79                 | 26.8%               | 3.33151e-10 |
| 10-bit zeroing + gzip      | 3.81               | 2.58                 | 32.3%               | 5.33735e-09 |
| 12-bit zeroing + gzip      | 3.81               | 2.27                 | 40.5%               | 8.55999e-08 |
| 16-bit zeroing + gzip      | 3.81               | 1.69                 | 55.6%               | 2.18084e-05 |

## Conclusion & Key Takeaways

- Zeroing out LSBs alone **does not reduce file size** because IEEE 754 floating-point numbers maintain a fixed 32-bit storage structure.
- To achieve actual storage savings, **additional compression techniques (gzip) or reducing bit-width (16-bit float conversion) are needed**.
- **Gaussian and Exponential distributions show similar trends to Uniform distribution** in storage savings and precision loss, with Exponential data suffering slightly higher MSE.
- **8-bit or 10-bit zeroing followed by gzip compression** provides an optimal balance between storage savings and precision retention.
- **Converting 32-bit floats to 16-bit** halves storage but introduces significant loss, making it suitable only for applications that tolerate large errors.

This experiment highlights the importance of understanding data representation before applying compression techniques and provides insights into how lossy floating-point compression can be optimized for different use cases.

