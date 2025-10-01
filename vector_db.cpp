#include "vector_db.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>

bool VectorDB::addVector(int id, const vector<float>& vec) {
    if (storage.find(id) != storage.end()) {
        cerr << "error: vector with id " << id << "already exists" << endl;
        return false;
    }
    storage[id] = vec;
    return true;
}

vector<pair<int, double>> VectorDB::findNearest(const vector<float>& query_vec, int k) {

    if (storage.empty()) {
        cerr << "database is empty cant find nearest neighbors" << endl;
        return {};
    }

    if (k <= 0) {
        cerr << "error: k must be positive" << endl;
        return {};
    }

    vector<pair<int, double>> similarities;

    for (const auto& pair : storage) {
        double sim = cosineSimilarity(query_vec, pair.second);
        similarities.push_back({pair.first, sim});
    }

    sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (k < similarities.size()) {
        similarities.resize(k);
    }

    return similarities;
}