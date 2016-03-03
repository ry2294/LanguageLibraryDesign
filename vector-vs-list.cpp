#include <random>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <list>
#include <set>
#include <chrono>

using namespace std;

class Node {
    private:
    int num;
    string dummyString;
    int dummyint;
    bool dummyBool;
    double dummyDouble;
    public:
    bool operator<(const Node& node) const {
        if(this->num < node.num) return true;
        return false;
    }
    Node(int val) {
        num = val;
    }
};

void randomNumbers(int N, vector<int>& nums, vector<Node>& nodes, int seed) {
    unordered_set<int> numsset;
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, numeric_limits<int>::max());
    
    for(int i = 0; i < N; i++) {
        auto num = distribution(generator);
        if(numsset.find(num) == numsset.end()) {
            numsset.insert(num);
            nums.push_back(num);
            Node node(num);
            nodes.push_back(node);
        } else i--;
    }
}

void randomIndexes(int N, vector<int>& indexes, int seed) {
    unordered_set<int> indexset;
    default_random_engine generator(seed);
    
    for(int i = N - 1; i >= 0; i--) {
        uniform_int_distribution<int> distribution(0, i);
        auto num = distribution(generator);
        indexes.push_back(num);
    }
}

template<class Container, typename type>
void insertIntoContainer(Container& container, vector<type>& nums) {
    for(auto num : nums) {
        auto insertAt = container.begin();
        while(insertAt != container.end()) {
            if(num < *insertAt)
                break;
            insertAt++;
        }
        container.insert(insertAt, num);
    }
}


template<typename type>
void insertIntoContainer(set<type>& container, vector<type>& nums) {
    for(auto num : nums) {
        container.insert(num);
    }
}

template<class Container>
void deleteFromContainer(Container& container, vector<int>& indexes) {
    for(auto index : indexes) {
        auto deleteAt = container.begin();
        while(index > 0) {
            deleteAt++;
            index--;
        }
        container.erase(deleteAt);
    }
}

template<class Container, typename type>
double testingContainer(Container& container, vector<type>& nums, vector<int>& indexes) {
    auto start = chrono::high_resolution_clock::now();
    
    insertIntoContainer(container, nums);
    deleteFromContainer(container, indexes);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    int Ns[] {1000, 5000, 10000, 50000, 100000, 200000, 300000, 
    400000, 500000, 600000};
    int seeds[] {1233213, 5432432, 43255342};
    
    for(auto N : Ns) {
        double intVectorSecs = 0, intListSeconds = 0, intSetSeconds = 0;
        double nodeVectorSecs = 0, nodeListSeconds = 0, nodeSetSeconds = 0;
        for(auto seed : seeds) {
            vector<int> nums;
            vector<Node> nodes;
            vector<int> indexes;
            randomNumbers(N, nums, nodes, seed);
            randomIndexes(N, indexes, seed);
            
            vector<int> intTestVector; list<int> intTestList; set<int> intTestSet;
            vector<Node> nodeTestVector; list<Node> nodeTestList; set<Node> nodeTestSet;
            
            intVectorSecs+= testingContainer(intTestVector, nums, indexes);
            intListSeconds+= testingContainer(intTestList, nums, indexes);
            intSetSeconds+= testingContainer(intTestSet, nums, indexes);
            
            nodeVectorSecs+= testingContainer(nodeTestVector, nodes, indexes);
            nodeListSeconds+= testingContainer(nodeTestList, nodes, indexes);
            nodeSetSeconds+= testingContainer(nodeTestSet, nodes, indexes);
        }
        cout << "int Vector duration = " << intVectorSecs / 3 << "secs ";
        cout << "int List duration = " << intListSeconds / 3 << "secs ";
        cout << "int Set duration = " << intSetSeconds / 3 << "secs" << endl;
        cout << "Node Vector duration = " << nodeVectorSecs / 3 << "secs ";
        cout << "Node List duration = " << nodeListSeconds / 3 << "secs ";
        cout << "Node Set duration = " << nodeSetSeconds / 3 << "secs" << endl;
    }
}