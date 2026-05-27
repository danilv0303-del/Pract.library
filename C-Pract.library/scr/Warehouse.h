#pragma once
#include "Product.h"
#include <functional>
#include <string>
#include <vector>

class Warehouse {
private:
    std::vector<Product> products;

    static bool caseInsensitiveCompare(const std::string &a, const std::string &b);

public:
    void add(const Product &product);
    bool update(const std::string &id, const Product &updated);
    bool removeById(const std::string &id);
    bool removeByName(const std::string &name);

    Product *findById(const std::string &id);
    Product *findByName(const std::string &name);

    std::vector<Product> searchByName(const std::string &name) const;
    std::vector<Product> searchByCategory(const std::string &category) const;
    std::vector<Product> searchByPriceRange(double minPrice, double maxPrice) const;

    void sortByPrice(bool ascending = true);
    void sortByQuantity(bool ascending = true);
    void sortByName(bool ascending = true);

    double getTotalValue() const;
    std::vector<Product> getLowStock(int threshold = 5) const;
    std::vector<Product> getTopExpensive(int count = 3) const;

    const std::vector<Product> &getAll() const;
    bool idExists(const std::string &id) const;
    void clear();
};