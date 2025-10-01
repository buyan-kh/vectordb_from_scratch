bool VectorDB::addVector(int id, const vector<float>& vec) {
    if (storage.find(id) != storage.end()) {
        return false;
    }
    storage[id] = vec;
    return true;
}