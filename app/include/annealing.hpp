#ifndef KNAPSACK_ANNEALING_ANNEALING_HPP
#define KNAPSACK_ANNEALING_ANNEALING_HPP

#include <item.hpp>
#include <vector>

double evaluate(const std::vector<int>& solution, const std::vector<Item>& items, int max_weight);
std::vector<int> simulated_annealing(const std::vector<Item>& items, int max_weight,
                               double T_init, double T_min, double alpha, int max_iter);

#endif //KNAPSACK_ANNEALING_ANNEALING_HPP
