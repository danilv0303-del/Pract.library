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

void FileIO::save(const std::vector<Book> &books, const std::string &filename) {
    ensureDirectoryExists(filename);
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    for (const auto &b : books) {
        file << b.toString() << "\n";
    }
    file.close();
}

std::vector<Book> FileIO::load(const std::string &filename) {
    std::vector<Book> books;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return books;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                books.push_back(Book::fromString(line));
            }
            catch (const std::exception &) {
            }
        }
    }
    file.close();
    return books;
}