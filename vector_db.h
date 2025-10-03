#ifndef VECTOR_DB_H
#define VECTOR_DB_H
#include <vector>
#include <map>
#include <utility>
#include <string>

class VectorDB {
public:
    bool addVector(int id, const std::vector<float>& vec);
    std::vector<std::pair<int, double>> findNearest(const std::vector<float>& query_vec, int k);

    bool saveToFile(const std::string& filename);

    bool loadFromFile(const std::string& filename);

private:
    std::map<int, std::vector<float>> db;
    double cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b);
};

#endif // VECTOR_DB_H


