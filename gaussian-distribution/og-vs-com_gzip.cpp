#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdint>
#include <sys/stat.h>
#include <cstdlib>  
#include <cmath>    

//This is a Function to apply LSB zeroing (lossy compression)
void compressData(std::vector<float> &data, int bits_to_zero) {
    uint32_t mask = ~((1 << bits_to_zero) - 1); 
    for (float &x : data) {
        uint32_t *bits = reinterpret_cast<uint32_t *>(&x);
        *bits &= mask;  
    }
}

//This is a Function to calculate Mean Squared Error (MSE)
double calculateMSE(const std::vector<float> &original, const std::vector<float> &compressed) {
    double mse = 0.0;
    size_t N = original.size();
    
    for (size_t i = 0; i < N; i++) {
        double diff = original[i] - compressed[i];
        mse += diff * diff;
    }
    
    return mse / N;
}

//This is To Save float vector to a binary file
void saveToFile(const std::string &filename, const std::vector<float> &data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char *>(data.data()), data.size() * sizeof(float));
    file.close();
}

//This is a Function to get file size
long getFileSize(const std::string &filename) {
    struct stat stat_buf;
    return (stat(filename.c_str(), &stat_buf) == 0) ? stat_buf.st_size : -1;
}

//This is to Compress using gzip and get compressed size
long getGzipCompressedSize(const std::string &filename) {
    std::string command = "gzip -kf " + filename;  
    system(command.c_str());  
    return getFileSize(filename + ".gz");  
}

int main() {
   
    //This is to Generate large dataset
    size_t N = 1000000;
    std::vector<float> original_data(N);
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0, 1.0);


    
    for (size_t i = 0; i < N; i++) {
        original_data[i] = distribution(generator);
    }

    //This is to Create compressed datasets with different LSB zeroing
    std::vector<float> compressed_8 = original_data;
    std::vector<float> compressed_10 = original_data;
    std::vector<float> compressed_12 = original_data;
    std::vector<float> compressed_16 = original_data;

    compressData(compressed_8, 8);
    compressData(compressed_10, 10);
    compressData(compressed_12, 12);
    compressData(compressed_16, 16);

    //To Calculate MSE for different compression levels
    double mse_8 = calculateMSE(original_data, compressed_8);
    double mse_10 = calculateMSE(original_data, compressed_10);
    double mse_12 = calculateMSE(original_data, compressed_12);
    double mse_16 = calculateMSE(original_data, compressed_16);

    //To Save to files
    saveToFile("original.bin", original_data);
    saveToFile("compressed_8.bin", compressed_8);
    saveToFile("compressed_10.bin", compressed_10);
    saveToFile("compressed_12.bin", compressed_12);
    saveToFile("compressed_16.bin", compressed_16);

    // This is to Measure file sizes before compression
    long original_size = getFileSize("original.bin");
    long compressed_8_size = getFileSize("compressed_8.bin");
    long compressed_10_size = getFileSize("compressed_10.bin");
    long compressed_12_size = getFileSize("compressed_12.bin");
    long compressed_16_size = getFileSize("compressed_16.bin");

    //This is to Compress files using gzip and get compressed sizes
    long original_gz_size = getGzipCompressedSize("original.bin");
    long compressed_8_gz_size = getGzipCompressedSize("compressed_8.bin");
    long compressed_10_gz_size = getGzipCompressedSize("compressed_10.bin");
    long compressed_12_gz_size = getGzipCompressedSize("compressed_12.bin");
    long compressed_16_gz_size = getGzipCompressedSize("compressed_16.bin");

    //This is to Display results
    std::cout << "Original File Size: " << original_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 8 Bits File Size: " << compressed_8_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 10 Bits File Size: " << compressed_10_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 12 Bits File Size: " << compressed_12_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 16 Bits File Size: " << compressed_16_size / (1024.0 * 1024) << " MB\n";

    std::cout << "\nAfter gzip compression:\n";
    std::cout << "Original Compressed: " << original_gz_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 8 Bits  + (gzip): " << compressed_8_gz_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 10 Bits + (gzip): " << compressed_10_gz_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 12 Bits + (gzip): " << compressed_12_gz_size / (1024.0 * 1024) << " MB\n";
    std::cout << "Compressed 16 Bits + (gzip): " << compressed_16_gz_size / (1024.0 * 1024) << " MB\n";

    std::cout << "\nMean Squared Error (MSE):\n";
    std::cout << "MSE (8-bit zeroing): " << mse_8 << "\n";
    std::cout << "MSE (10-bit zeroing): " << mse_10 << "\n";
    std::cout << "MSE (12-bit zeroing): " << mse_12 << "\n";
    std::cout << "MSE (16-bit zeroing): " << mse_16 << "\n";

    return 0;
}