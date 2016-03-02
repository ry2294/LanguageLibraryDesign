#include <random>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <list>
#include <set>
#include <chrono>

using namespace std;

void randomNumbers(int N, vector<int>& nums) {
    unordered_set<int> numsset;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, numeric_limits<int>::max());
    
    for(int i = 0; i < N; i++) {
        auto num = distribution(generator);
        if(numsset.find(num) == numsset.end()) {
            numsset.insert(num);
            nums.push_back(num);
        } else i--;
    }
}

void randomIndexes(int N, vector<int>& indexes) {
    unordered_set<int> indexset;
    default_random_engine generator;
    
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

double testingSet(vector<int>& nums, vector<int>& indexes) {
    set<int> testSet;
    auto start = chrono::high_resolution_clock::now();
    for(auto num : nums) {
        testSet.insert(num);
    }
    
    for(auto index : indexes) {
        set<int>::iterator deleteAt = testSet.begin();
        while(index > 0) {
            deleteAt++;
            index--;
        }
        testSet.erase(deleteAt);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    std::cout << "Set Elapsed Time = " << duration.count() << std::endl;
    return duration.count();
}

int main() {
    vector<int> nums;
    vector<int> indexes;
    randomNumbers(100000, nums);
    randomIndexes(100000, indexes);
    
    vector<int> testVector; list<int> testList;
    std::cout << "Vector duration = " << testingContainer(testVector, nums, indexes) << " secs" << std::endl;
    std::cout << "List duration = " << testingContainer(testList, nums, indexes) << " secs" << std::endl;
    testingSet(nums, indexes);
}