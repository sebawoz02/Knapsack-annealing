#include <iostream>
#include "parser.hpp"

int main() {
    std::string filename = "data/knapsack_5_items_new.csv";

    auto [items, capacity] = parse_csv(filename);

    std::cout << "Pojemnosc plecaka: " << capacity << "\n";
    std::cout << "Przedmioty:\n";
    for (const auto& item : items) {
        std::cout << "  Waga: " << item.weight << ", Profit: " << item.profit << "\n";
    }

    return 0;
}
