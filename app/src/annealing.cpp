#include <annealing.hpp>
#include <random>
#include <algorithm>

static std::vector<int> generate_neighbor(const std::vector<int>& current_solution);
static std::vector<int> generate_greedy_solution(const std::vector<Item>& items, int max_weight);
static std::vector<int> generate_random_solution(const std::vector<Item>& items, int max_weight);

static std::vector<int> generate_greedy_solution(const std::vector<Item>& items, int max_weight) {
    size_t n = items.size();
    std::vector<std::pair<double, int>> ratio_index;

    for (size_t i = 0; i < n; ++i) {
        double ratio = (double)items[i].profit / items[i].weight;
        ratio_index.emplace_back(ratio, i);
    }

    // Sortujemy malejąco po stosunku value/weight
    std::sort(ratio_index.rbegin(), ratio_index.rend());

    std::vector<int> solution(n, 0);
    int current_weight = 0;

    for (auto& [ratio, idx] : ratio_index) {
        if (current_weight + items[idx].weight <= max_weight) {
            solution[idx] = 1;
            current_weight += items[idx].weight;
        }
    }
    return solution;
}

static std::vector<int> generate_random_solution(const std::vector<Item>& items, int max_weight) {
    size_t n = items.size();
    std::vector<int> solution(n, 0);
    std::vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0); // [0, 1, ..., n-1]

    std::random_device rd;
    std::mt19937 gen(rd());
    shuffle(indices.begin(), indices.end(), gen);

    int current_weight = 0;
    for (int i : indices) {
        if (current_weight + items[i].weight <= max_weight) {
            solution[i] = 1;
            current_weight += items[i].weight;
        }
    }
    return solution;
}


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

    std::vector<int> current_solution = generate_random_solution(items, max_weight);
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
