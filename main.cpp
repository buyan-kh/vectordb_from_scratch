#include <iostream>
#include "vector_db.h"
using namespace std;

void printVector(const std::vector<float>& vec) {
    cout << "[ ";
    for (float val : vec)
    {
        cout << val << " ";
    }
    cout << "]" << endl;
}

void run_query(VectorDB& db) {
    std::vector<float> query_vector = {0.8, 0.2, 0.05};
    std::cout << "searching vectors similar to: ";
    printVector(query_vector);

    int k = 2;
    std::vector<std::pair<int, double>> nearest_neighbors = db.findNearest(query_vector, k);

    std::cout << "---search results ---\n";

    if (nearest_neighbors.empty())
    {
        cout << "no neighbors found. " << std:endl;
    } else {
        for (const auto& neighbor : nearest_neighbors) 
        {
            std::cout << " - Vector ID: " << neighbor.first
            << ", Similarity Score: " << neighbor.second << endl;
        }
    }
    std::cout << "-----------------\n";
}


int main() {
    cout << "initializing vector database...\n";
    VectorDB db;

    cout << "adding sample vectors...\n";
    db.addVector(1, {1.0, 2.0, 3.0});
    db.addVector(2, {0.9, 0.1, 0.0});
    db.addVector(3, {0.0, 1.0, 0.0});
    db.addVector(4, {0.0, 0.0, 1.0});
    db.addVector(5, {0.1, 0.9, 0.1});
    cout << "sample data added. \n";

    std::vector<float> query_vector = {0.8, 0.2, 0.05};
    cout << "searching vectors similar to: ";
    printVector(query_vector);
    cout << endl;

    int k = 2;
    cout << "finding the top " << k << " neighbors. \n";
    std::vector<std::pair<int, double>> nearest_neighbors = db.findNearest(query_vector, k);
    
    if (nearest_neighbors.empty())
    {
        cout << "no neighbors found. \n";
    } else
    {
        cout << "---search results---\n";
        for (const auto& neighbor : nearest_neighbors)
        {
            cout << " - Vector ID: " << neighbor.first
            << ", Similarity score: " << neighbor.second << endl;
        }
        cout << "-----------------\n";
    }

    return 0;
        


}
