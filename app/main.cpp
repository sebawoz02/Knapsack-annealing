#include <iostream>
#include <annealing.hpp>
#include "parser.hpp"

int main() {
    std::string filename = "/home/sebawoz02/CLionProjects/Knapsack-annealing/app/data/knapsack_5_items_new.csv";

    auto [items, capacity] = parse_csv(filename);

    std::cout << "Pojemnosc plecaka: " << capacity << "\n";
    std::cout << "Przedmioty:\n";
    for (const auto& item : items) {
        std::cout << "  Waga: " << item.weight << ", Profit: " << item.profit << "\n";
    }

    // Parametry SA
    const double T_init = 1000.0;
    const double T_min = 0.01;
    const double alpha = 0.95;
    const int max_iter = 1000;

    std::vector<int> best_solution = simulated_annealing(items, capacity, T_init, T_min, alpha, max_iter);

    double best_value = evaluate(best_solution, items, capacity);
    std::cout << "Najlepsze znalezione rozwiazanie: ";
    for (int x : best_solution) std::cout << x << " ";
    std::cout << "\nWartosc: " << best_value << std::endl;

    return 0;
}
