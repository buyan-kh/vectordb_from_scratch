#include "vector_db.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>

bool VectorDB::addVector(int id, const std::vector<float>& vec) {
    if (db.find(id) != db.end()) {
        std::cerr << "error: vector with id " << id << " already exists" << std::endl;
        return false;
    }
    db[id] = vec;
    return true;
}

std::vector<std::pair<int, double>> VectorDB::findNearest(const std::vector<float>& query_vec, int k) {

    if (db.empty()) {
        std::cerr << "database is empty can't find nearest neighbors" << std::endl;
        return {};
    }

    if (k <= 0) {
        std::cerr << "error: k must be positive" << std::endl;
        return {};
    }

    std::vector<std::pair<int, double>> similarities;

    for (const auto& pair : db) {
        double sim = cosineSimilarity(query_vec, pair.second);
        similarities.push_back({pair.first, sim});
    }

    sort(similarities.begin(), similarities.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second;
    });

    if (k < similarities.size()) {
        similarities.resize(k);
    }

    return similarities;
}

double VectorDB::cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b) {
    if (a.size() != b.size() || a.empty()) {
        throw std::invalid_argument("vectors must have same non zero dimensions");
    }
    double dot_product = 0.0;
    double norm_a = 0.0;
    double norm_b = 0.0;

    for (size_t i = 0; i < a.size(); i++)
    {
        dot_product += a[i] * b[i];

        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }

    double magnitude = sqrt(norm_a) * sqrt(norm_b);

    if (magnitude == 0) {
        return 0.0;
    }

    return dot_product / magnitude;
}