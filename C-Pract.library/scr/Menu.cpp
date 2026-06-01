#include "Menu.h"
#include "FileIO.h"
#include <iostream>
#include <limits>
#include <sstream>

Menu::Menu(Library &library, const std::string &filename)
    : library(library), filename(filename) {}

void Menu::printHeader() {
    std::cout << "\n==========================================\n";
    std::cout << "     Система управления библиотекой       \n";
    std::cout << "==========================================\n";
    std::cout << "1. Добавить книгу\n";
    std::cout << "2. Редактировать книгу\n";
    std::cout << "3. Удалить книгу\n";
    std::cout << "4. Поиск и фильтрация\n";
    std::cout << "5. Сортировка книг\n";
    std::cout << "6. Аналитика\n";
    std::cout << "7. Просмотр всех книг\n";
    std::cout << "8. Сохранить данные\n";
    std::cout << "0. Выход\n";
    std::cout << "==========================================\n";
}

void Menu::printBook(const Book &b) {
    std::cout << "------------------------------------------\n";
    std::cout << "ID: " << b.getId() << "\n";
    std::cout << "Название: " << b.getTitle() << "\n";
    std::cout << "Автор: " << b.getAuthor() << "\n";
    std::cout << "Жанр: " << b.getGenre() << "\n";
    std::cout << "Год издания: " << b.getYear() << "\n";
    std::cout << "Количество экземпляров: " << b.getCopies() << "\n";
    std::cout << "Цена: " << b.getPrice() << "\n";
}

int Menu::getIntInput(const std::string &prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Неверный ввод. Попробуйте снова.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double Menu::getDoubleInput(const std::string &prompt, double min) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Неверный ввод. Попробуйте снова.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string Menu::getStringInput(const std::string &prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    while (value.empty()) {
        std::cout << "Поле не может быть пустым. Попробуйте снова.\n";
        std::cout << prompt;
        std::getline(std::cin, value);
    }
    return value;
}

void Menu::pressEnter() {
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::addBook() {
    std::cout << "\n--- Добавление новой книги ---\n";
    std::string id = getStringInput("ID: ");
    if (library.idExists(id)) {
        std::cout << "Ошибка: Книга с таким ID уже существует.\n";
        return;
    }
    std::string title = getStringInput("Название: ");
    std::string author = getStringInput("Автор: ");
    std::string genre = getStringInput("Жанр: ");
    int year = getIntInput("Год издания: ", 1, 9999);
    int copies = getIntInput("Количество экземпляров: ", 0, 1000000);
    double price = getDoubleInput("Цена: ", 0);

    Book b(id, title, author, genre, year, copies, price);
    if (!Book::validate(b)) {
        std::cout << "Ошибка: Неверные данные книги.\n";
        return;
    }

    library.add(b);
    std::cout << "Книга успешно добавлена.\n";
}

void Menu::editBook() {
    std::cout << "\n--- Редактирование книги ---\n";
    std::string id = getStringInput("Введите ID книги для редактирования: ");
    Book *b = library.findById(id);
    if (!b) {
        std::cout << "Книга не найдена.\n";
        return;
    }

    printBook(*b);
    std::cout << "\nВведите новые данные (оставьте пустым, чтобы сохранить текущее значение):\n";

    std::cout << "ID [" << b->getId() << "]: ";
    std::string newId;
    std::getline(std::cin, newId);
    if (!newId.empty() && newId != b->getId()) {
        if (library.idExists(newId)) {
            std::cout << "Ошибка: Книга с таким ID уже существует.\n";
            return;
        }
        b->setId(newId);
    }

    std::cout << "Название [" << b->getTitle() << "]: ";
    std::string newTitle;
    std::getline(std::cin, newTitle);
    if (!newTitle.empty()) b->setTitle(newTitle);

    std::cout << "Автор [" << b->getAuthor() << "]: ";
    std::string newAuthor;
    std::getline(std::cin, newAuthor);
    if (!newAuthor.empty()) b->setAuthor(newAuthor);

    std::cout << "Жанр [" << b->getGenre() << "]: ";
    std::string newGenre;
    std::getline(std::cin, newGenre);
    if (!newGenre.empty()) b->setGenre(newGenre);

    std::cout << "Год издания [" << b->getYear() << "]: ";
    std::string yearStr;
    std::getline(std::cin, yearStr);
    if (!yearStr.empty()) {
        try {
            b->setYear(std::stoi(yearStr));
        }
        catch (...) {
            std::cout << "Неверный год.\n";
        }
    }

    std::cout << "Количество экземпляров [" << b->getCopies() << "]: ";
    std::string copiesStr;
    std::getline(std::cin, copiesStr);
    if (!copiesStr.empty()) {
        try {
            b->setCopies(std::stoi(copiesStr));
        }
        catch (...) {
            std::cout << "Неверное количество.\n";
        }
    }

    std::cout << "Цена [" << b->getPrice() << "]: ";
    std::string priceStr;
    std::getline(std::cin, priceStr);
    if (!priceStr.empty()) {
        try {
            b->setPrice(std::stod(priceStr));
        }
        catch (...) {
            std::cout << "Неверная цена.\n";
        }
    }

    if (!Book::validate(*b)) {
        std::cout << "Ошибка: Неверные данные книги.\n";
        return;
    }

    std::cout << "Книга успешно обновлена.\n";
}

void Menu::deleteBook() {
    std::cout << "\n--- Удаление книги ---\n";
    std::cout << "1. Удалить по ID\n";
    std::cout << "2. Удалить по названию\n";
    int choice = getIntInput("Выбор: ", 1, 2);

    if (choice == 1) {
        std::string id = getStringInput("Введите ID: ");
        if (library.removeById(id)) {
            std::cout << "Книга успешно удалена.\n";
        }
        else {
            std::cout << "Книга не найдена.\n";
        }
    }
    else {
        std::string title = getStringInput("Введите название: ");
        if (library.removeByTitle(title)) {
            std::cout << "Книга(и) успешно удалена(ы).\n";
        }
        else {
            std::cout << "Книга не найдена.\n";
        }
    }
}

void Menu::searchBooks() {
    std::cout << "\n--- Поиск и фильтрация ---\n";
    std::cout << "1. Поиск по названию (частичное совпадение)\n";
    std::cout << "2. Поиск по автору\n";
    std::cout << "3. Поиск по жанру\n";
    std::cout << "4. Поиск по диапазону года издания\n";
    std::cout << "5. Поиск по диапазону цен\n";
    int choice = getIntInput("Выбор: ", 1, 5);

    std::vector<Book> results;
    if (choice == 1) {
        std::string title = getStringInput("Введите название: ");
        results = library.searchByTitle(title);
    }
    else if (choice == 2) {
        std::string author = getStringInput("Введите автора: ");
        results = library.searchByAuthor(author);
    }
    else if (choice == 3) {
        std::string genre = getStringInput("Введите жанр: ");
        results = library.searchByGenre(genre);
    }
    else if (choice == 4) {
        int minYear = getIntInput("Мин. год: ", 1, 9999);
        int maxYear = getIntInput("Макс. год: ", minYear, 9999);
        results = library.searchByYearRange(minYear, maxYear);
    }
    else {
        double minPrice = getDoubleInput("Мин. цена: ", 0);
        double maxPrice = getDoubleInput("Макс. цена: ", minPrice);
        results = library.searchByPriceRange(minPrice, maxPrice);
    }

    if (results.empty()) {
        std::cout << "Книги не найдены.\n";
    }
    else {
        std::cout << "\nНайдено книг: " << results.size() << "\n";
        for (const auto &b : results) {
            printBook(b);
        }
    }
}

void Menu::sortBooks() {
    std::cout << "\n--- Сортировка книг ---\n";
    std::cout << "1. По году издания (по возрастанию)\n";
    std::cout << "2. По году издания (по убыванию)\n";
    std::cout << "3. По количеству экземпляров (по возрастанию)\n";
    std::cout << "4. По количеству экземпляров (по убыванию)\n";
    std::cout << "5. По названию (А-Я)\n";
    std::cout << "6. По названию (Я-А)\n";
    std::cout << "7. По автору (А-Я)\n";
    std::cout << "8. По автору (Я-А)\n";
    int choice = getIntInput("Выбор: ", 1, 8);

    switch (choice) {
        case 1:
            library.sortByYear(true);
            break;
        case 2:
            library.sortByYear(false);
            break;
        case 3:
            library.sortByCopies(true);
            break;
        case 4:
            library.sortByCopies(false);
            break;
        case 5:
            library.sortByTitle(true);
            break;
        case 6:
            library.sortByTitle(false);
            break;
        case 7:
            library.sortByAuthor(true);
            break;
        case 8:
            library.sortByAuthor(false);
            break;
    }
    std::cout << "Книги отсортированы.\n";
}

void Menu::showAnalytics() {
    std::cout << "\n--- Аналитика ---\n";

    double totalValue = library.getTotalValue();
    std::cout << "Общая стоимость книжного фонда: " << totalValue << "\n";

    auto lowStock = library.getLowStock(2);
    std::cout << "\nКниги, требующие пополнения (остаток <= 2 шт): " << lowStock.size() << "\n";
    for (const auto &b : lowStock) {
        std::cout << "- " << b.getTitle() << " (" << b.getCopies() << " экз)\n";
    }

    auto topExpensive = library.getTopExpensive(3);
    std::cout << "\nТоп-3 самых дорогих книг:\n";
    for (const auto &b : topExpensive) {
        std::cout << "- " << b.getTitle() << ": " << b.getPrice() << "\n";
    }
}

void Menu::saveData() {
    try {
        FileIO::save(library.getAll(), filename);
        std::cout << "Данные успешно сохранены.\n";
    }
    catch (const std::exception &e) {
        std::cout << "Ошибка сохранения: " << e.what() << "\n";
    }
}

void Menu::run() {
    try {
        auto books = FileIO::load(filename);
        for (const auto &b : books) {
            library.add(b);
        }
        std::cout << "Загружено книг из файла: " << books.size() << "\n";
    }
    catch (const std::exception &e) {
        std::cout << "Примечание: " << e.what() << ". Запуск с пустой библиотекой.\n";
    }

    while (true) {
        printHeader();
        int choice = getIntInput("Выберите действие: ", 0, 8);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                editBook();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                searchBooks();
                break;
            case 5:
                sortBooks();
                break;
            case 6:
                showAnalytics();
                break;
            case 7:
                std::cout << "\n--- Все книги ---\n";
                for (const auto &b : library.getAll()) {
                    printBook(b);
                }
                if (library.getAll().empty()) {
                    std::cout << "Библиотека пуста.\n";
                }
                break;
            case 8:
                saveData();
                break;
            case 0:
                std::cout << "Выход...\n";
                return;
        }
        pressEnter();
    }
}