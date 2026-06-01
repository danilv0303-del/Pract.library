#include "Library.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

bool Library::caseInsensitiveCompare(const std::string &a, const std::string &b) {
    std::string ca = a, cb = b;
    std::transform(ca.begin(), ca.end(), ca.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    std::transform(cb.begin(), cb.end(), cb.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return ca < cb;
}

void Library::add(const Book &book) {
    if (idExists(book.getId())) {
        throw std::runtime_error("Book with ID " + book.getId() + " already exists");
    }
    books.push_back(book);
}

bool Library::update(const std::string &id, const Book &updated) {
    for (auto &b : books) {
        if (b.getId() == id) {
            if (updated.getId() != id && idExists(updated.getId())) {
                return false;
            }
            b = updated;
            return true;
        }
    }
    return false;
}

bool Library::removeById(const std::string &id) {
    auto it = std::remove_if(books.begin(), books.end(), [&id](const Book &b) { return b.getId() == id; });
    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

bool Library::removeByTitle(const std::string &title) {
    std::string searchLower = title;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    auto it = std::remove_if(books.begin(), books.end(), [&searchLower](const Book &b) {
        std::string bt = b.getTitle();
        std::transform(bt.begin(), bt.end(), bt.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return bt == searchLower;
    });
    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

Book *Library::findById(const std::string &id) {
    for (auto &b : books) {
        if (b.getId() == id) return &b;
    }
    return nullptr;
}

Book *Library::findByTitle(const std::string &title) {
    std::string searchLower = title;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    for (auto &b : books) {
        std::string bt = b.getTitle();
        std::transform(bt.begin(), bt.end(), bt.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (bt == searchLower) return &b;
    }
    return nullptr;
}

std::vector<Book> Library::searchByTitle(const std::string &title) const {
    std::string searchLower = title;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    std::vector<Book> result;
    for (const auto &b : books) {
        std::string bt = b.getTitle();
        std::transform(bt.begin(), bt.end(), bt.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (bt.find(searchLower) != std::string::npos) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Book> Library::searchByAuthor(const std::string &author) const {
    std::string searchLower = author;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    std::vector<Book> result;
    for (const auto &b : books) {
        std::string ba = b.getAuthor();
        std::transform(ba.begin(), ba.end(), ba.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (ba.find(searchLower) != std::string::npos) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Book> Library::searchByGenre(const std::string &genre) const {
    std::string searchLower = genre;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    std::vector<Book> result;
    for (const auto &b : books) {
        std::string bg = b.getGenre();
        std::transform(bg.begin(), bg.end(), bg.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (bg == searchLower) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Book> Library::searchByYearRange(int minYear, int maxYear) const {
    std::vector<Book> result;
    for (const auto &b : books) {
        if (b.getYear() >= minYear && b.getYear() <= maxYear) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Book> Library::searchByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Book> result;
    for (const auto &b : books) {
        if (b.getPrice() >= minPrice && b.getPrice() <= maxPrice) {
            result.push_back(b);
        }
    }
    return result;
}

void Library::sortByYear(bool ascending) {
    std::sort(books.begin(), books.end(), [ascending](const Book &a, const Book &b) {
        return ascending ? a.getYear() < b.getYear() : a.getYear() > b.getYear();
    });
}

void Library::sortByCopies(bool ascending) {
    std::sort(books.begin(), books.end(), [ascending](const Book &a, const Book &b) {
        return ascending ? a.getCopies() < b.getCopies() : a.getCopies() > b.getCopies();
    });
}

void Library::sortByTitle(bool ascending) {
    std::sort(books.begin(), books.end(), [ascending](const Book &a, const Book &b) {
        bool result = caseInsensitiveCompare(a.getTitle(), b.getTitle());
        return ascending ? result : !result;
    });
}

void Library::sortByAuthor(bool ascending) {
    std::sort(books.begin(), books.end(), [ascending](const Book &a, const Book &b) {
        bool result = caseInsensitiveCompare(a.getAuthor(), b.getAuthor());
        return ascending ? result : !result;
    });
}

double Library::getTotalValue() const {
    double total = 0.0;
    for (const auto &b : books) {
        total += b.getPrice() * b.getCopies();
    }
    return total;
}

std::vector<Book> Library::getLowStock(int threshold) const {
    std::vector<Book> result;
    for (const auto &b : books) {
        if (b.getCopies() <= threshold) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Book> Library::getTopExpensive(int count) const {
    std::vector<Book> sorted = books;
    std::sort(sorted.begin(), sorted.end(), [](const Book &a, const Book &b) {
        return a.getPrice() > b.getPrice();
    });
    if ((int)sorted.size() > count) {
        sorted.resize(count);
    }
    return sorted;
}

const std::vector<Book> &Library::getAll() const {
    return books;
}

bool Library::idExists(const std::string &id) const {
    for (const auto &b : books) {
        if (b.getId() == id) return true;
    }
    return false;
}

void Library::clear() {
    books.clear();
}