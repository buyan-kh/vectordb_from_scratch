#include <vector>
#include <map>
#include <utility>
using namespace std;

class VectorDB {
public:
    bool addVector(int id, const vector<float>& vec);
    vector<pair<int, double>> findNearest(const vector<float>& query_vec, int k);
private:
    map<int, vector<float>> db;
    double cosineSimilarity(const vector<float>& a, const vector<float>& b);
};

