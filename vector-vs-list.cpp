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
    public:
    
};

void randomNumbers(int N, vector<int>& nums, int seed) {
    unordered_set<int> numsset;
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, numeric_limits<int>::max());
    
    for(int i = 0; i < N; i++) {
        auto num = distribution(generator);
        if(numsset.find(num) == numsset.end()) {
            numsset.insert(num);
            nums.push_back(num);
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

template<class Container>
void insertIntoContainer(Container& container, vector<int>& nums) {
    for(auto num : nums) {
        auto insertAt = container.begin();
        while(insertAt != container.end()) {
            if(*insertAt > num)
                break;
            insertAt++;
        }
        container.insert(insertAt, num);
    }
}

template<>
void insertIntoContainer<set<int>>(set<int>& container, vector<int>& nums) {
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

template<class Container>
double testingContainer(Container& container, vector<int>& nums, vector<int>& indexes) {
    auto start = chrono::high_resolution_clock::now();
    
    insertIntoContainer(container, nums);
    deleteFromContainer(container, indexes);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    int seeds[] {1233213, 5432432, 43255342};
    
    for(auto N = 10; N <= 10000; N*=10) {
        double vectorSecs = 0, listSeconds = 0, setSeconds = 0;
        for(auto seed : seeds) {
            vector<int> nums;
            vector<int> indexes;
            randomNumbers(N, nums, seed);
            randomIndexes(N, indexes, seed);
            
            vector<int> testVector; list<int> testList; set<int> testSet;
            vectorSecs+= testingContainer(testVector, nums, indexes);
            listSeconds+= testingContainer(testList, nums, indexes);
            setSeconds+= testingContainer(testSet, nums, indexes);
        }
        cout << "Vector duration = " << vectorSecs / 3 << "secs ";
        cout << "List duration = " << listSeconds / 3 << "secs ";
        cout << "Set duration = " << setSeconds / 3 << "secs" << endl;
    }
}