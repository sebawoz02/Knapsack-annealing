#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

struct Item {
    int weight;
    int profit;
};

// Parsuje CSV i zwraca listę przedmiotów oraz pojemność plecaka
std::pair<std::vector<Item>, int> parse_csv(const std::string& filename);

#endif // PARSER_HPP
