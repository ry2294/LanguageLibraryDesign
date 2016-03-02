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

double testingVector(vector<int>& nums, vector<int>& indexes) {
    vector<int> testVector;
    auto start = chrono::high_resolution_clock::now();
    for(auto num : nums) {
        vector<int>::iterator insertAt = testVector.begin();
        while(insertAt != testVector.end()) {
            if(*insertAt > num)
                break;
            ++insertAt;
        }
        testVector.insert(insertAt, num);
    }
    
    for(auto index : indexes) {
        vector<int>::iterator deleteAt = testVector.begin();
        while(index > 0) {
            deleteAt++;
            index--;
        }
        testVector.erase(deleteAt);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    std::cout << "Vector Elapsed Time = " << duration.count() << std::endl;
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

double testingList(vector<int>& nums, vector<int>& indexes) {
    list<int> testList;
    auto start = chrono::high_resolution_clock::now();
    for(auto num : nums) {
        list<int>::iterator insertAt = testList.begin();
        while(insertAt != testList.end()) {
            if(*insertAt > num)
                break;
            ++insertAt;
        }
        testList.insert(insertAt, num);
    }
    
    for(auto index : indexes) {
        list<int>::iterator deleteAt = testList.begin();
        while(index > 0) {
            deleteAt++;
            index--;
        }
        testList.erase(deleteAt);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    std::cout << "List Elapsed Time = " << duration.count() << std::endl;
    return duration.count();
}

int main() {
    vector<int> nums;
    vector<int> indexes;
    randomNumbers(100000, nums);
    randomIndexes(100000, indexes);
    
    testingVector(nums, indexes);
    testingList(nums, indexes);
    testingSet(nums, indexes);
}