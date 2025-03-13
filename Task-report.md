# Exploring Lossy Floating-Point Compression: Understanding Storage Savings vs. Precision Loss

## Introduction
In this experiment, we explore lossy floating-point compression by manipulating the least significant bits (LSBs) of the mantissa and analyzing its impact on storage savings and precision loss. The goal is to find an optimal balance between reducing storage space and maintaining computational accuracy.

## Experiment Overview
We generated a large dataset of floating-point numbers from three different distributions:

- **Uniform**
- **Gaussian**
- **Exponential**

Then, we applied lossy compression by zeroing out between 8 and 16 LSBs of the mantissa. We stored both the full-precision and compressed data in binary format and analyzed:

- **On-disk file sizes** to measure storage savings
- **Statistical properties** before and after compression
- **Mean Squared Error (MSE)** to quantify precision loss
- **Visualization of distribution changes**

## Key Finding: Zeroing Out LSBs Alone Does Not Reduce File Size
A crucial realization emerged during the analysis: zeroing out the least significant bits of the mantissa does not change the file size. This is because:

- In standard **IEEE 754 floating-point representation**, each float is stored in a fixed **32-bit (4-byte)** format.
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

| Method                      | Original Size (MB) | Compressed Size (MB) | Storage Savings (%) | MSE   |
|-----------------------------|-------------------|-------------------|-----------------|---------------|
| No Compression              | 3.81              | 3.81              | 0%              | 0.0           |
| gzip Compression            | 3.81              | 3.42              | 10.2%           | 0.0           |
| 8-bit zeroing + gzip        | 3.81              | 2.72              | 28.6%           | 4.41e-11      |
| 12-bit zeroing + gzip       | 3.81              | 2.14              | 43.8%           | 1.13e-08      |
| 16-bit zeroing + gzip       | 3.81              | 1.60              | 58.1%           | 2.90e-06      |
| 32-bit to 16-bit conversion | 3.81              | 1.90              | 50.0%           | 171799        |

## Finding the Sweet Spot
To determine the best trade-off between storage savings and precision loss, we calculated a **Compression Efficiency Metric**:

Compression Efficiency = Storage Savings (%)​ / MSE 

- **8-bit zeroing + gzip** is the most efficient method, offering **28.6% storage savings** with minimal precision loss (**MSE = 4.41e-11**).
- **10-bit zeroing (Uniform Distribution) + gzip** is another strong option, providing **35% storage savings** with an **MSE of 7.07e-10**.
- **16-bit zeroing or 32-bit to 16-bit conversion** results in excessive precision loss, making them less ideal for precision-critical applications.

## Conclusion & Key Takeaways
- **Zeroing out LSBs alone does not reduce file size** because IEEE 754 floating-point numbers maintain a fixed **32-bit storage structure**.
- **To achieve actual storage savings, additional compression techniques (gzip) or reducing bit-width (16-bit float conversion) are needed**.
- **8-bit or 10-bit zeroing followed by gzip compression provides an optimal balance between storage savings and precision retention**.
- **Converting 32-bit floats to 16-bit halves storage but introduces significant loss**, making it suitable only for applications that tolerate large errors.

This experiment highlights the importance of understanding data representation before applying compression techniques and provides insights into how **lossy floating-point compression can be optimized** for different use cases.


