#include <annealing.hpp>
#include <random>

static std::vector<int> generate_neighbor(const std::vector<int>& current_solution);

double evaluate(const std::vector<int>& solution, const std::vector<Item>& items, int max_weight)
{
    int total_weight = 0, total_value = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i]) {
            total_weight += items[i].weight;
            total_value += items[i].profit;
        }
    }
    if (total_weight > max_weight)
        return -1e9; // kara za przekroczenie wagi
    return total_value;
}

std::vector<int> simulated_annealing(const std::vector<Item>& items, int max_weight,
                               double T_init, double T_min, double alpha, int max_iter) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);

    std::vector<int> current_solution(items.size(), 0);
    std::vector<int> best_solution = current_solution;

    double T = T_init;
    double current_value = evaluate(current_solution, items, max_weight);
    double best_value = current_value;

    while (T > T_min) {
        for (int i = 0; i < max_iter; ++i) {
            std::vector<int> neighbor = generate_neighbor(current_solution);
            double neighbor_value = evaluate(neighbor, items, max_weight);
            double delta = neighbor_value - current_value;

            if (delta > 0 || prob_dist(gen) < exp(delta / T)) {
                current_solution = neighbor;
                current_value = neighbor_value;

                if (current_value > best_value) {
                    best_solution = current_solution;
                    best_value = current_value;
                }
            }
        }
        T *= alpha; // schładzanie
    }

    return best_solution;
}


std::vector<int> generate_neighbor(const std::vector<int>& current_solution) {
    std::vector<int> neighbor = current_solution;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, neighbor.size() - 1);
    int index = dist(gen);
    neighbor[index] = 1 - neighbor[index]; // zmiana 0 -> 1 lub 1 -> 0
    return neighbor;
}
