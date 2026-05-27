#include "Menu.h"
#include "FileIO.h"
#include <iostream>
#include <limits>
#include <sstream>

Menu::Menu(Warehouse &warehouse, const std::string &filename)
    : warehouse(warehouse), filename(filename) {}

void Menu::printHeader() {
    std::cout << "       Система управления складом     \n";
    std::cout << "1. Добавить товар\n";
    std::cout << "2. Редактировать товар\n";
    std::cout << "3. Удалить товар\n";
    std::cout << "4. Поиск и фильтрация\n";
    std::cout << "5. Сортировка товаров\n";
    std::cout << "6. Аналитика\n";
    std::cout << "7. Просмотр всех товаров\n";
    std::cout << "8. Сохранить данные\n";
    std::cout << "0. Выход\n";
}

void Menu::printProduct(const Product &p) {
    std::cout << "--------------------------------------\n";
    std::cout << "ID: " << p.getId() << "\n";
    std::cout << "Название: " << p.getName() << "\n";
    std::cout << "Категория: " << p.getCategory() << "\n";
    std::cout << "Цена: " << p.getPrice() << "\n";
    std::cout << "Количество: " << p.getQuantity() << "\n";
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

void Menu::addProduct() {
    std::cout << "\n--- Добавление нового товара ---\n";
    std::string id = getStringInput("ID: ");
    if (warehouse.idExists(id)) {
        std::cout << "Ошибка: Товар с таким ID уже существует.\n";
        return;
    }
    std::string name = getStringInput("Название: ");
    std::string category = getStringInput("Категория: ");
    double price = getDoubleInput("Цена: ", 0);
    int quantity = getIntInput("Количество: ", 0, 1000000);

    Product p(id, name, category, price, quantity);
    if (!Product::validate(p)) {
        std::cout << "Ошибка: Неверные данные товара.\n";
        return;
    }

    warehouse.add(p);
    std::cout << "Товар успешно добавлен.\n";
}

void Menu::editProduct() {
    std::cout << "\n--- Редактирование товара ---\n";
    std::string id = getStringInput("Введите ID товара для редактирования: ");
    Product *p = warehouse.findById(id);
    if (!p) {
        std::cout << "Товар не найден.\n";
        return;
    }

    printProduct(*p);
    std::cout << "\nВведите новые данные (оставьте пустым, чтобы сохранить текущее значение):\n";

    std::cout << "ID [" << p->getId() << "]: ";
    std::string newId;
    std::getline(std::cin, newId);
    if (!newId.empty() && newId != p->getId()) {
        if (warehouse.idExists(newId)) {
            std::cout << "Ошибка: Товар с таким ID уже существует.\n";
            return;
        }
        p->setId(newId);
    }

    std::cout << "Название [" << p->getName() << "]: ";
    std::string newName;
    std::getline(std::cin, newName);
    if (!newName.empty()) p->setName(newName);

    std::cout << "Категория [" << p->getCategory() << "]: ";
    std::string newCategory;
    std::getline(std::cin, newCategory);
    if (!newCategory.empty()) p->setCategory(newCategory);

    std::cout << "Цена [" << p->getPrice() << "]: ";
    std::string priceStr;
    std::getline(std::cin, priceStr);
    if (!priceStr.empty()) {
        try {
            p->setPrice(std::stod(priceStr));
        }
        catch (...) {
            std::cout << "Неверная цена.\n";
        }
    }

    std::cout << "Количество [" << p->getQuantity() << "]: ";
    std::string qtyStr;
    std::getline(std::cin, qtyStr);
    if (!qtyStr.empty()) {
        try {
            p->setQuantity(std::stoi(qtyStr));
        }
        catch (...) {
            std::cout << "Неверное количество.\n";
        }
    }

    if (!Product::validate(*p)) {
        std::cout << "Ошибка: Неверные данные товара.\n";
        return;
    }

    std::cout << "Товар успешно обновлен.\n";
}

void Menu::deleteProduct() {
    std::cout << "\n--- Удаление товара ---\n";
    std::cout << "1. Удалить по ID\n";
    std::cout << "2. Удалить по названию\n";
    int choice = getIntInput("Выбор: ", 1, 2);

    if (choice == 1) {
        std::string id = getStringInput("Введите ID: ");
        if (warehouse.removeById(id)) {
            std::cout << "Товар успешно удален.\n";
        }
        else {
            std::cout << "Товар не найден.\n";
        }
    }
    else {
        std::string name = getStringInput("Введите название: ");
        if (warehouse.removeByName(name)) {
            std::cout << "Товар(ы) успешно удален(ы).\n";
        }
        else {
            std::cout << "Товар не найден.\n";
        }
    }
}

void Menu::searchProducts() {
    std::cout << "\n--- Поиск и фильтрация ---\n";
    std::cout << "1. Поиск по названию (частичное совпадение)\n";
    std::cout << "2. Поиск по категории\n";
    std::cout << "3. Поиск по диапазону цен\n";
    int choice = getIntInput("Выбор: ", 1, 3);

    std::vector<Product> results;
    if (choice == 1) {
        std::string name = getStringInput("Введите название: ");
        results = warehouse.searchByName(name);
    }
    else if (choice == 2) {
        std::string category = getStringInput("Введите категорию: ");
        results = warehouse.searchByCategory(category);
    }
    else {
        double minPrice = getDoubleInput("Мин. цена: ", 0);
        double maxPrice = getDoubleInput("Макс. цена: ", minPrice);
        results = warehouse.searchByPriceRange(minPrice, maxPrice);
    }

    if (results.empty()) {
        std::cout << "Товары не найдены.\n";
    }
    else {
        std::cout << "\nНайдено товаров: " << results.size() << "\n";
        for (const auto &p : results) {
            printProduct(p);
        }
    }
}

void Menu::sortProducts() {
    std::cout << "\n--- Сортировка товаров ---\n";
    std::cout << "1. По цене (по возрастанию)\n";
    std::cout << "2. По цене (по убыванию)\n";
    std::cout << "3. По количеству (по возрастанию)\n";
    std::cout << "4. По количеству (по убыванию)\n";
    std::cout << "5. По названию (А-Я)\n";
    std::cout << "6. По названию (Я-А)\n";
    int choice = getIntInput("Выбор: ", 1, 6);

    switch (choice) {
        case 1:
            warehouse.sortByPrice(true);
            break;
        case 2:
            warehouse.sortByPrice(false);
            break;
        case 3:
            warehouse.sortByQuantity(true);
            break;
        case 4:
            warehouse.sortByQuantity(false);
            break;
        case 5:
            warehouse.sortByName(true);
            break;
        case 6:
            warehouse.sortByName(false);
            break;
    }
    std::cout << "Товары отсортированы.\n";
}

void Menu::showAnalytics() {
    std::cout << "\n--- Аналитика ---\n";

    double totalValue = warehouse.getTotalValue();
    std::cout << "Общая стоимость всех товаров: " << totalValue << "\n";

    auto lowStock = warehouse.getLowStock(5);
    std::cout << "\nТовары с остатком <= 5 шт: " << lowStock.size() << "\n";
    for (const auto &p : lowStock) {
        std::cout << "- " << p.getName() << " (" << p.getQuantity() << " шт)\n";
    }

    auto topExpensive = warehouse.getTopExpensive(3);
    std::cout << "\nТоп-3 самых дорогих товара:\n";
    for (const auto &p : topExpensive) {
        std::cout << "- " << p.getName() << ": " << p.getPrice() << "\n";
    }
}

void Menu::saveData() {
    try {
        FileIO::save(warehouse.getAll(), filename);
        std::cout << "Данные успешно сохранены.\n";
    }
    catch (const std::exception &e) {
        std::cout << "Ошибка сохранения: " << e.what() << "\n";
    }
}

void Menu::run() {
    try {
        auto products = FileIO::load(filename);
        for (const auto &p : products) {
            warehouse.add(p);
        }
        std::cout << "Загружено товаров из файла: " << products.size() << "\n";
    }
    catch (const std::exception &e) {
        std::cout << "Примечание: " << e.what() << ". Запуск с пустым складом.\n";
    }

    while (true) {
        printHeader();
        int choice = getIntInput("Выберите действие: ", 0, 8);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                searchProducts();
                break;
            case 5:
                sortProducts();
                break;
            case 6:
                showAnalytics();
                break;
            case 7:
                std::cout << "\n--- Все товары ---\n";
                for (const auto &p : warehouse.getAll()) {
                    printProduct(p);
                }
                if (warehouse.getAll().empty()) {
                    std::cout << "Склад пуст.\n";
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