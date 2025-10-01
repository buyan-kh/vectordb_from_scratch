#include <vector>
#include <map>
#include <utility>

class VectorDB {
public:
    bool addVector(int id, const std::vector<float>& vec);
    std::vector<std::pair<int, double>> findNearest(const std::vector<float>& query_vec, int k);
private:
    std::map<int, std::vector<float>> db;
    double cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b);
};

