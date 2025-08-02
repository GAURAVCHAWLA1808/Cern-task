#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
#include <bitset>
#include <numeric>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// This is a Function to generate random numbers from a given distribution
template <typename Distribution>
vector<float> generate_data(size_t n, Distribution dist) {
    random_device rd;
    mt19937 gen(rd());
    vector<float> data(n);
    for (size_t i = 0; i < n; i++) {
        data[i] = dist(gen);
    }
    return data;
}

// This is a Function to compress floating-point numbers by zeroing out the least significant bits
float compress(float value, int bits_to_zero) {
    if (bits_to_zero <= 0 || bits_to_zero >= 23) return value; 
    
    uint32_t int_rep = *reinterpret_cast<uint32_t*>(&value);
    int_rep &= ~((1 << bits_to_zero) - 1); 
    
    return *reinterpret_cast<float*>(&int_rep);
}

// This is a Function to compress a vector of floating points
vector<float> compress_data(const vector<float>& data, int bits_to_zero) {
    vector<float> compressed;
    compressed.reserve(data.size());
    for (float val : data) {
        compressed.push_back(compress(val, bits_to_zero));
    }
    return compressed;
}

//This is a Function to save data in binary format
void save_binary(const string& filename, const vector<float>& data) {
    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));
    file.close();
}

//This is a Function to compute Mean Squared Error (MSE)
double compute_mse(const vector<float>& original, const vector<float>& compressed) {
    double mse = 0.0;
    for (size_t i = 0; i < original.size(); i++) {
        double diff = original[i] - compressed[i];
        mse += diff * diff;
    }
    return mse / original.size();
}

//This is a Compute mean and standard deviation
pair<double, double> compute_stats(const vector<float>& data) {
    double mean = accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = 0.0;
    for (float val : data) {
        variance += (val - mean) * (val - mean);
    }
    variance /= data.size();
    return {mean, sqrt(variance)};
}

// This is a Function to get file size
size_t get_file_size(const string& filename) {
    return fs::exists(filename) ? fs::file_size(filename) : 0;
}

int main() {
    size_t n = 1e6; 
    
    // This Generate random numbers from different distributions
    vector<float> uniform_data = generate_data(n, uniform_real_distribution<float>(0.0, 1.0));
    vector<float> gaussian_data = generate_data(n, normal_distribution<float>(0.0, 1.0));
    vector<float> exponential_data = generate_data(n, exponential_distribution<float>(1.0));
    
    // To Apply lossy compression (zero out 10 least significant bits)
    int bits_to_zero = 10;
    vector<float> compressed_uniform = compress_data(uniform_data, bits_to_zero);
    vector<float> compressed_gaussian = compress_data(gaussian_data, bits_to_zero);
    vector<float> compressed_exponential = compress_data(exponential_data, bits_to_zero);


    
    //To  Save to binary files
    save_binary("uniform_original.bin", uniform_data);
    save_binary("uniform_compressed.bin", compressed_uniform);
    save_binary("gaussian_original.bin", gaussian_data);
    save_binary("gaussian_compressed.bin", compressed_gaussian);
    save_binary("exponential_original.bin", exponential_data);
    save_binary("exponential_compressed.bin", compressed_exponential);
    
    // To Compute statistics before and after compression
    auto [mean_u, stddev_u] = compute_stats(uniform_data);
    auto [mean_cu, stddev_cu] = compute_stats(compressed_uniform);
    cout << "Uniform Distribution: Mean = " << mean_u << ", Std Dev = " << stddev_u << endl;
    cout << "Compressed Uniform: Mean = " << mean_cu << ", Std Dev = " << stddev_cu << endl;
    
    // To Compute MSE
    double mse_uniform = compute_mse(uniform_data, compressed_uniform);
    double mse_gaussian = compute_mse(gaussian_data, compressed_gaussian);
    double mse_exponential = compute_mse(exponential_data, compressed_exponential);
    
    cout << "MSE (Uniform): " << mse_uniform << endl;
    cout << "MSE (Gaussian): " << mse_gaussian << endl;
    cout << "MSE (Exponential): " << mse_exponential << endl;
    
    // To Measure file sizes and calculate storage savings
    size_t original_size_u = get_file_size("uniform_original.bin");
    size_t compressed_size_u = get_file_size("uniform_compressed.bin");
    size_t original_size_g = get_file_size("gaussian_original.bin");
    size_t compressed_size_g = get_file_size("gaussian_compressed.bin");
    size_t original_size_e = get_file_size("exponential_original.bin");
    size_t compressed_size_e = get_file_size("exponential_compressed.bin");
    
    cout << "Storage Savings Analysis:\n";
    cout << "Uniform: Original = " << original_size_u / 1024 << " KB, Compressed = " << compressed_size_u / 1024 << " KB, Savings = " 
         << (1.0 - (double)compressed_size_u / original_size_u) * 100 << "%\n";
    cout << "Gaussian: Original = " << original_size_g / 1024 << " KB, Compressed = " << compressed_size_g / 1024 << " KB, Savings = " 
         << (1.0 - (double)compressed_size_g / original_size_g) * 100 << "%\n";
    cout << "Exponential: Original = " << original_size_e / 1024 << " KB, Compressed = " << compressed_size_e / 1024 << " KB, Savings = " 
         << (1.0 - (double)compressed_size_e / original_size_e) * 100 << "%\n";
    
    return 0;
}
