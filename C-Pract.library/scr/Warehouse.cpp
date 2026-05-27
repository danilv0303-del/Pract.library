#include "Warehouse.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

bool Warehouse::caseInsensitiveCompare(const std::string &a, const std::string &b) {
    std::string ca = a, cb = b;
    std::transform(ca.begin(), ca.end(), ca.begin(), [](unsigned char c) { return std::tolower(c); });
    std::transform(cb.begin(), cb.end(), cb.begin(), [](unsigned char c) { return std::tolower(c); });
    return ca < cb;
}

void Warehouse::add(const Product &product) {
    if (idExists(product.getId())) {
        throw std::runtime_error("Product with ID " + product.getId() + " already exists");
    }
    products.push_back(product);
}

bool Warehouse::update(const std::string &id, const Product &updated) {
    for (auto &p : products) {
        if (p.getId() == id) {
            if (updated.getId() != id && idExists(updated.getId())) {
                return false;
            }
            p = updated;
            return true;
        }
    }
    return false;
}

bool Warehouse::removeById(const std::string &id) {
    auto it = std::remove_if(products.begin(), products.end(), [&id](const Product &p) { return p.getId() == id; });
    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }
    return false;
}

bool Warehouse::removeByName(const std::string &name) {
    auto it = std::remove_if(products.begin(), products.end(), [this, &name](const Product &p) {
        std::string pName = p.getName();
        std::string searchName = name;
        std::transform(pName.begin(), pName.end(), pName.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(searchName.begin(), searchName.end(), searchName.begin(), [](unsigned char c) { return std::tolower(c); });
        return pName == searchName;
    });
    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }
    return false;
}

Product *Warehouse::findById(const std::string &id) {
    for (auto &p : products) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}

Product *Warehouse::findByName(const std::string &name) {
    for (auto &p : products) {
        std::string pName = p.getName();
        std::string searchName = name;
        std::transform(pName.begin(), pName.end(), pName.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(searchName.begin(), searchName.end(), searchName.begin(), [](unsigned char c) { return std::tolower(c); });
        if (pName == searchName) return &p;
    }
    return nullptr;
}

std::vector<Product> Warehouse::searchByName(const std::string &name) const {
    std::string searchLower = name;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return std::tolower(c); });

    std::vector<Product> result;
    for (const auto &p : products) {
        std::string pName = p.getName();
        std::transform(pName.begin(), pName.end(), pName.begin(), [](unsigned char c) { return std::tolower(c); });
        if (pName.find(searchLower) != std::string::npos) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Product> Warehouse::searchByCategory(const std::string &category) const {
    std::string catLower = category;
    std::transform(catLower.begin(), catLower.end(), catLower.begin(), [](unsigned char c) { return std::tolower(c); });

    std::vector<Product> result;
    for (const auto &p : products) {
        std::string pCat = p.getCategory();
        std::transform(pCat.begin(), pCat.end(), pCat.begin(), [](unsigned char c) { return std::tolower(c); });
        if (pCat == catLower) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Product> Warehouse::searchByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Product> result;
    for (const auto &p : products) {
        if (p.getPrice() >= minPrice && p.getPrice() <= maxPrice) {
            result.push_back(p);
        }
    }
    return result;
}

void Warehouse::sortByPrice(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const Product &a, const Product &b) {
        return ascending ? a.getPrice() < b.getPrice() : a.getPrice() > b.getPrice();
    });
}

void Warehouse::sortByQuantity(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const Product &a, const Product &b) {
        return ascending ? a.getQuantity() < b.getQuantity() : a.getQuantity() > b.getQuantity();
    });
}

void Warehouse::sortByName(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const Product &a, const Product &b) {
        bool result = caseInsensitiveCompare(a.getName(), b.getName());
        return ascending ? result : !result;
    });
}

double Warehouse::getTotalValue() const {
    double total = 0.0;
    for (const auto &p : products) {
        total += p.getPrice() * p.getQuantity();
    }
    return total;
}

std::vector<Product> Warehouse::getLowStock(int threshold) const {
    std::vector<Product> result;
    for (const auto &p : products) {
        if (p.getQuantity() <= threshold) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Product> Warehouse::getTopExpensive(int count) const {
    std::vector<Product> sorted = products;
    std::sort(sorted.begin(), sorted.end(), [](const Product &a, const Product &b) {
        return a.getPrice() > b.getPrice();
    });
    if ((int)sorted.size() > count) {
        sorted.resize(count);
    }
    return sorted;
}

const std::vector<Product> &Warehouse::getAll() const {
    return products;
}

bool Warehouse::idExists(const std::string &id) const {
    for (const auto &p : products) {
        if (p.getId() == id) return true;
    }
    return false;
}

void Warehouse::clear() {
    products.clear();
}