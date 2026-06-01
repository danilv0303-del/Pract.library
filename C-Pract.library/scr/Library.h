#pragma once
#include "Book.h"
#include <functional>
#include <string>
#include <vector>

class Library {
private:
    std::vector<Book> books;

    static bool caseInsensitiveCompare(const std::string &a, const std::string &b);

public:
    void add(const Book &book);
    bool update(const std::string &id, const Book &updated);
    bool removeById(const std::string &id);
    bool removeByTitle(const std::string &title);

    Book *findById(const std::string &id);
    Book *findByTitle(const std::string &title);

    std::vector<Book> searchByTitle(const std::string &title) const;
    std::vector<Book> searchByAuthor(const std::string &author) const;
    std::vector<Book> searchByGenre(const std::string &genre) const;
    std::vector<Book> searchByYearRange(int minYear, int maxYear) const;
    std::vector<Book> searchByPriceRange(double minPrice, double maxPrice) const;

    void sortByYear(bool ascending = true);
    void sortByCopies(bool ascending = true);
    void sortByTitle(bool ascending = true);
    void sortByAuthor(bool ascending = true);

    double getTotalValue() const;
    std::vector<Book> getLowStock(int threshold = 2) const;
    std::vector<Book> getTopExpensive(int count = 3) const;

    const std::vector<Book> &getAll() const;
    bool idExists(const std::string &id) const;
    void clear();
};