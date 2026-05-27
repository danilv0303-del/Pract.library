#include "FileIO.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

static void ensureDirectoryExists(const std::string &filepath) {
    std::string dir = filepath.substr(0, filepath.find_last_of("/\\"));
    if (!dir.empty()) {
        std::filesystem::create_directories(dir);
    }
}

void FileIO::save(const std::vector<Product> &products, const std::string &filename) {
    ensureDirectoryExists(filename);
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    for (const auto &p : products) {
        file << p.toString() << "\n";
    }
    file.close();
}

std::vector<Product> FileIO::load(const std::string &filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return products;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                products.push_back(Product::fromString(line));
            }
            catch (const std::exception &) {
            }
        }
    }
    file.close();
    return products;
}