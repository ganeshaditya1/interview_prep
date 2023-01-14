#include <bits/stdc++.h>

/*
* Time complexity: 
* Worst case: O(logN), Best case: O(1), Average case: O(logN)
*
* Space complexity: O(1)
*/
int binary_search(std::vector<int>& input, int key) {
    int lo = 0, hi = input.size() - 1;
    while(lo < hi) {        
        int middle = (lo + hi)/2;
        if(input[middle] == key) {
            return middle;
        } else if(input[middle] > key) {
            hi = middle - 1;
        } else {
            lo = middle + 1;
        }
    }
    if(input[lo] == key) {
        return lo;
    } else {
        return -1;
    }
}

int main(int argc, char** argv) {
    std::vector<std::vector<int>> test_cases = {
        {},
        {1},
        {0},
        {-1},
        {0, 1},
        {0, 0},
        {1, 2, 3, 4, 5},
        {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8},
        {-9, -6, -3, 0, 3, 6, 9, 12, 15},
        {-9, -6, -6, -3, 0, 3, 6, 6, 9, 12, 15},
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {-1, -1, -1, -1},
        {-1, -1, -1, 1, 2, 3},
        {1, 2, 3, 4, 4, 4},
        {-1, -1, -1, 1, 1, 1},
    };

    for(auto& test_case: test_cases) {
        for(auto num: test_case) {
            int index = binary_search(test_case, num);
            if(index < 0 || index >= test_case.size() || test_case[index] != num) {
                std::cout << "Test case failed for input: " << num << "Returned index: " << index << std::endl;
                for(auto num: test_case) {
                    std::cout << num << ", ";
                }
                std::cout << std::endl;
            }

        }
        if(test_case.empty()) {
            continue;
        }
        int index = binary_search(test_case, test_case[0] - 5);
        if(index != -1) {
            std::cout << "Test case failed for input: " << test_case[0] - 5 << "Returned index: " << index << std::endl;
            for(auto num: test_case) {
                std::cout << num << ", ";
            }
            std::cout << std::endl;
        }

        index = binary_search(test_case, test_case.back() + 5);
        if(index != -1) {
            std::cout << "Test case failed for input: " << test_case.back() + 5 << "Returned index: " << index << std::endl;
            for(auto num: test_case) {
                std::cout << num << ", ";
            }
            std::cout << std::endl;
        }
    }
}