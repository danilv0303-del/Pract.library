#pragma once
#include "Product.h"
#include <string>
#include <vector>

class FileIO {
public:
    static void save(const std::vector<Product> &products, const std::string &filename);
    static std::vector<Product> load(const std::string &filename);
};