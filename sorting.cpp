#include <bits/stdc++.h>

/*
* Time complexity: 
* Best case: O(N), Worst case: O(N^2), Average case: O(N^2)
*
* Space Complexity:
* O(1) for all cases.
*/
void bubble_sort(std::vector<int>& input) {
    int n = input.size();
    bool swapped = false;
    do {
        swapped = false;
        for(int j = 0; j < n; j++) {
            if(j + 1 < n && input[j] > input[j + 1]) {
                std::swap(input[j], input[j + 1]);
                swapped = true;
            }
        }
    } while(swapped);
}

typedef void (*sorting_algo)(std::vector<int>& input);

void test_algorithm(sorting_algo function) {
    std::vector<std::vector<int>> test_cases = {
        {},
        {1},
        {0},
        {-1},
        {1, 0},
        {0, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {6, 0, 4, -2, -4, -10, -8, 2, -6, 8},
        {15, -3, 12, -6, 6, 3, 0, -9, 9},
        {15, -3, 12, -6, 6, 3, 0, -9, 9, -6, 6},
        {-3, 3, 9, 15, 6, -9, 6, 12, 0, -6, -6},
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {-1, -1, -1, -1},
        {-1, -1, -1, 1, 2, 3},
        {1, 2, 3, 4, 4, 4},
        {-1, -1, -1, 1, 1, 1},
        {1, 1, 1, -1, -1, -1},
    };

    for(auto& test_case: test_cases) {        
        std::vector<int> test_case_copy(test_case.begin(), test_case.end());
        std::vector<int> sorted_output(test_case.begin(), test_case.end());
        sort(sorted_output.begin(), sorted_output.end());

        function(test_case);

        bool failed = false;
        for(int i = 0; i < test_case.size(); i++) {
            if(test_case[i] != sorted_output[i]) {
                failed = true;
                break;
            }
        }

        if(failed) {            
            std::cout << "The following test case failed." << std::endl;
            for(auto num: test_case_copy) {
                std::cout << num << " ";
            }

            std::cout << std::endl << "This was the ouput produced." << std::endl;            
            for(auto num: test_case) {
                std::cout << num << " ";
            }
            std::cout << std::endl << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    return 0;
}