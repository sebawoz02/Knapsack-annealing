#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>

std::pair<std::vector<Item>, int> parse_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
        return {{}, 0};
    }

    std::string line;
    std::getline(file, line); // Pomijamy nagłówek

    std::vector<std::vector<int>> all_rows;

    // Wczytaj wszystkie wiersze jako liczby całkowite
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(ss, cell, ',')) {
            try {
                row.push_back(std::stoi(cell));
            } catch (const std::invalid_argument&) {
                std::cerr << "Blad parsowania liczby: " << cell << std::endl;
                break;
            }
        }

        if (row.size() >= 11) {
            all_rows.push_back(row);
        }
    }

    if (all_rows.empty()) {
        std::cerr << "Brak poprawnych danych w pliku." << std::endl;
        return {{}, 0};
    }

    // Losowy wybór jednej instancji
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int index = std::rand() % all_rows.size();
    const auto& values = all_rows[index];

    std::vector<Item> items;
    for (int i = 0; i < 5; ++i) {
        items.push_back({values[i], values[i + 5]});
    }

    int capacity = values[10];
    return {items, capacity};
}
