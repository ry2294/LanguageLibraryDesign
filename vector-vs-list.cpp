#include <random>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <list>

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

void testingVector(vector<int>& nums, vector<int>& indexes) {
    vector<int> testVector;
    for(auto num : nums) {
        int i = 0;
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
}

void testingList(vector<int>& nums, vector<int>& indexes) {
    list<int> testList;
    for(auto num : nums) {
        int i = 0;
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
}

int main() {
    vector<int> nums;
    vector<int> indexes;
    randomNumbers(10, nums);
    randomIndexes(10, indexes);
    testingVector(nums, indexes);
    testingList(nums, indexes);
}