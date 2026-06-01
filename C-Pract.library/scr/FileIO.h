#pragma once
#include "Book.h"
#include <string>
#include <vector>

class FileIO {
public:
    static void save(const std::vector<Book> &books, const std::string &filename);
    static std::vector<Book> load(const std::string &filename);
};