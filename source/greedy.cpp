#include "greedy.h"


std::pair<int, double> min_index(const TSP& tsp, int cur_city, const std::vector<bool>& used){
    int next_city = 0;
    int first_valid = 0;
    int dimension = used.size();
    double cur_distance, min_distance;

    while(first_valid < dimension && used[first_valid++]);

    next_city = first_valid;
    min_distance = tsp.get_distance(cur_city, first_valid);

    for(int i = first_valid; i < dimension; i++){
        if(!used[i]){
            cur_distance = tsp.get_distance(cur_city, i + 1);
            if(cur_distance < min_distance){
                next_city = i + 1;
                min_distance = cur_distance;
            }
        }
    }
    return std::pair<int, double>(next_city, min_distance);
}


std::pair<double, std::vector<int> > greedy_tsp(const TSP& tsp){
    int dimension = tsp.get_dimension();
    int next_city = 1;
    double total_distance = 0;

    std::vector<int> path(dimension);
    std::vector<bool> used(dimension);

    used[next_city - 1] = true;
    path[0] = next_city;

    std::pair<int, double> city_weight;

    for(int i = 1; i < dimension; i++){
        city_weight = min_index(tsp, next_city, used);
        next_city = city_weight.first;
        total_distance += city_weight.second;
        used[next_city - 1] = true;
        path[i] = next_city;
    }
    total_distance += tsp.get_distance(path[dimension - 1], path[0]);

    return std::pair<double, std::vector<int> >(total_distance, path);
}