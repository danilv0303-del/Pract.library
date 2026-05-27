#include "Product.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

Product::Product() : price(0.0), quantity(0) {}

Product::Product(const std::string &id, const std::string &name, const std::string &category, double price, int quantity)
    : id(id), name(name), category(category), price(price), quantity(quantity) {}

std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setId(const std::string &newId) { id = newId; }
void Product::setName(const std::string &newName) { name = newName; }
void Product::setCategory(const std::string &newCategory) { category = newCategory; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setQuantity(int newQuantity) { quantity = newQuantity; }

std::string Product::toString() const {
    return id + "," + name + "," + category + "," + std::to_string(price) + "," + std::to_string(quantity);
}

Product Product::fromString(const std::string &line) {
    std::istringstream iss(line);
    std::string id, name, category, priceStr, quantityStr;

    if (!std::getline(iss, id, ',') ||
        !std::getline(iss, name, ',') ||
        !std::getline(iss, category, ',') ||
        !std::getline(iss, priceStr, ',') ||
        !std::getline(iss, quantityStr, ',')) {
        throw std::runtime_error("Invalid line format: " + line);
    }

    double price = std::stod(priceStr);
    int quantity = std::stoi(quantityStr);

    return Product(id, name, category, price, quantity);
}

bool Product::validate(const Product &p) {
    if (p.id.empty() || p.name.empty() || p.category.empty()) return false;
    if (p.price < 0 || p.quantity < 0) return false;
    return true;
}