#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <limits>
#include <random>
#include <sys/stat.h>
#include <cstdlib>  


// This is a Function to convert float to IEEE 754 16-bit half-precision with rounding
uint16_t floatToHalf(float value) {
    uint32_t f = *(uint32_t*)&value;
    uint16_t sign = (f >> 16) & 0x8000;
    int32_t exponent = ((f >> 23) & 0xFF) - 127 + 15;
    uint32_t mantissa = (f & 0x007FFFFF);

    if (exponent <= 0) return sign; 
    if (exponent >= 31) return sign | 0x7C00; 

    uint16_t rounded_mantissa = (mantissa >> 13) + ((mantissa & 0x1000) >> 12);
    return sign | (exponent << 10) | (rounded_mantissa & 0x3FF);
}

// This is a Function to convert 16-bit half-precision back to 32-bit float
float halfToFloat(uint16_t h) {
    uint32_t sign = (h & 0x8000) << 16;
    uint32_t exponent = ((h & 0x7C00) >> 10);
    uint32_t mantissa = (h & 0x03FF) << 13;

    if (exponent == 0) {
        if (mantissa == 0) return 0.0f;
        exponent = 1;
    } else if (exponent == 31) {
        return std::numeric_limits<float>::infinity(); 
    }
    exponent += 127 - 15;

    uint32_t f = (sign | (exponent << 23) | mantissa);
    return *(float*)&f;
}

int main() {

      size_t N = 1000000;
    std::vector<float> data(N);
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    
    for (size_t i = 0; i < N; i++) {
          data[i] = distribution(generator);
    }
   

    // To Save full-precision (32-bit) floating point data
    std::ofstream fullFile("full_precision.bin", std::ios::binary);
    fullFile.write(reinterpret_cast<const char*>(data.data()), N * sizeof(float));
    fullFile.close();

    //To Convert to 16-bit half precision
    std::vector<uint16_t> compressedData(N);
    for (int i = 0; i < N; i++) {
        compressedData[i] = floatToHalf(data[i]);
    }

    //To Save compressed (16-bit) floating point data
    std::ofstream compressedFile("compressed_half_precision.bin", std::ios::binary);
    compressedFile.write(reinterpret_cast<const char*>(compressedData.data()), N * sizeof(uint16_t));
    compressedFile.close();

    //To Compute Mean Squared Error (MSE) and Mean Absolute Error (MAE)
    double mse = 0.0;
    double mae = 0.0;
    double max_error = 0.0;
    for (int i = 0; i < N; i++) {
        float reconstructed = halfToFloat(compressedData[i]);
        double diff = data[i] - reconstructed;
        mse += diff * diff;
        mae += std::abs(diff);
        max_error = std::max(max_error, std::abs(diff));
    }
    mse /= N;
    mae /= N;

    // To compare the file size
    std::cout << "Original Size: " << N * sizeof(float) / 1024.0 << " KB\n";
    std::cout << "Compressed Size: " << N * sizeof(uint16_t) / 1024.0 << " KB\n";
    std::cout << "Storage Savings: " 
              << 100.0 * (1 - (double)(N * sizeof(uint16_t)) / (N * sizeof(float))) 
              << "%\n";
    std::cout << "Mean Squared Error: " << mse << "\n";
    std::cout << "Mean Absolute Error: " << mae << "\n";
    std::cout << "Maximum Absolute Error: " << max_error << "\n";

    return 0;
}
