#include <bits/stdc++.h>

/*
* Going from left to right, compare two elements at a time.
* Move the bigger element to the right.
* Keep iterating over the array while doing this until no element 
* has changed in the input array.
*
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
        for(int j = 0; j < n - 1; j++) {
            if(input[j] > input[j + 1]) {
                std::swap(input[j], input[j + 1]);
                swapped = true;
            }
        }
    } while(swapped);
}

/* 
* At each step we will insert the given element into the currect spot on the left side.
* For this find where the current element needs to be inserted to the
* left of the current postion. Move all the elements on the right side 
* of that position one step to the right.
* Then insert the current element in that position.
*
* Time complexity: 
* Best case: O(N), Worst case: O(N^2), Average case: O(N^2)
*
* Space Complexity:
* O(1) for all cases.
*/
void insertion_sort(std::vector<int>& input) {
    for(int i = 0; i < input.size(); i++) {
        int current = input[i];
        int j = i - 1;
        while(j >= 0 && input[j] > current) {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = current;
    }
}

/*
* Select the smallest element to the right of the current position.
* Swap that with the current element.
*
* Time complexity: 
* Best case: O(N^2), Worst case: O(N^2), Average case: O(N^2)
*
* Space Complexity:
* O(1) for all cases.
*/
void selection_sort(std::vector<int>& input) {
    for(int i = 0; i < input.size(); i++) {
        int current_min = i;
        for(int j = i + 1; j < input.size(); j++) {
            if(input[current_min] > input[j]) {
                current_min = j;
            }
        }

        if(current_min != i) {
            std::swap(input[current_min], input[i]);
        }
    }
}
/* 
* Time complexity: 
* Best case: O(NlogN), Worst case: O(N^2), Average case: O(NlogN)
*
* Space Complexity:
* O(1) for all cases.
*
* Quick sort is not stable sort. Quick sort is an inplace sort.
*/
int quicksort_partition(std::vector<int>& input, int lo, int hi) {
    if(lo < 0 || lo > hi) {
        return -1;
    } 
    if(lo == hi) {
        return lo;
    }

    int pivot = input[hi];
    int left_edge = lo - 1;
    for(int i = lo; i < hi; i++) {
        if(input[i] <= pivot) {
            left_edge++;
            std::swap(input[left_edge], input[i]);
        }
    }
    left_edge++;
    std::swap(input[left_edge], input[hi]);
    return left_edge;
}

void quick_sort(std::vector<int>& input, int left, int right) {
    if(left >= right || input.empty())  {
        return;
    }

    int p = quicksort_partition(input, left, right);
    if(p == -1 || p > right + 1) {
        return;
    }

    quick_sort(input, left, p - 1);
    quick_sort(input, p + 1, right);
}

// This is for the typedef. Ignore this. This isn't that consequential.
void quick_sort_wrapper(std::vector<int>& input) {
    quick_sort(input, 0, input.size() - 1);
}


/* 
* 1. Keep subdividing the current array into two halfs. 
* 2. Allocate memory the size of each half.
* 3. Recursively call the merge_sort function on each half and also pass in the vector
* that was allocated the size of each half.
* 4. If the size of the input vector is 1, then just copy that one element into the output
* space and return.
*    Else subdivide the input vector into two halfs and again call the mergesort function on the 
* two halves. 
* 5. Once the call returns. Merge the two halves together.
*
* Time complexity: 
* Best case: Omega(NlogN), Worst case: O(NlogN), Average case: Theta(NlogN)
*
* Space Complexity:
* O(N) for all cases.
*
* Stable sort. Not in-place sort. Good for external sort algorithms. Can be paralized.
* Merge sort on Linked lists doesn't require any additional memory.
*/
void merge_sort(std::vector<int>& input, int left, int right, std::vector<int>& output) {
    if(left == right) {
        output[0] = input[left];
        return;
    }

    int middle = (left + right)/2;
    std::vector<int> left_half(middle - left + 1, 0), right_half(right - middle, 0);
    
    merge_sort(input, left, middle, left_half);
    merge_sort(input, middle + 1, right, right_half);

    int left_edge = 0, i = 0, j = 0;
    while(i < left_half.size() || j < right_half.size()) {
        if(i < left_half.size() && j < right_half.size()) {
            if(left_half[i] <= right_half[j]) {
                output[left_edge++] = left_half[i++];
            } else {
                output[left_edge++] = right_half[j++];
            }
        } else if(i < left_half.size()) {
            output[left_edge++] = left_half[i++];
        } else if(j < right_half.size()) {
            output[left_edge++] = right_half[j++];
        }
    }
}


void merge_sort_wrapper(std::vector<int>& input) {
    if(input.empty()) {
        return;
    }
    std::vector<int> output(input.begin(), input.end());
    merge_sort(input, 0, input.size() - 1, output);
    input = output;
}

/* 
* Time complexity: 
* Best case: all O(NlogN)
*
* Space Complexity:
* O(1) for all cases.
*
* Not Stable sort. In-place sort. Here I have implemented a sift up operation for heapify
* But it is recommended to implement a sift down operation. These operations need to be 
* performed for every single item in the heap. 
*
* Heapify is a O(N) algorithm. https://stackoverflow.com/a/18742428/2340452
*/
void max_heapify(std::vector<int>& input) {
    // Do it top to bottom. 
    int N = input.size();
    for(int i = 0; i < N; i++) {
        int parent = (i - 1)/2;
        int current = i;
        while(current >= 0 && parent >= 0 && input[current] > input[parent]) {
            std::swap(input[parent], input[current]);
            current = parent;
            parent = (current - 1)/2;
        }
    }
}

void heap_sort(std::vector<int>& input) {
    max_heapify(input);
    // after the heapify call. The element at the position 0, i.e. the root element of the heap
    // is the maximum element in the array. We have to "pop" that element. i.e. move it to the 
    // last position in the array where it belongs. And copy the last element to the top.
    // Then we move the element at the top to it's correct position. After this step atleast
    // 1 element is in it's right position. So repeat the process with the lement at n - 1 position.

    for(int i = input.size() - 1; i >= 0; i--) {
        std::swap(input[0], input[i]);
        int index = 0;
        while(index < i) {
            int left_child = (index * 2) + 1, right_child = (index * 2) + 2;
            int child_index = index;
            if(left_child < i && right_child < i && input[index] < std::max(input[left_child], input[right_child])) {
                child_index = input[left_child] > input[right_child] ? left_child : right_child;                
            } else if (left_child < i && input[index] < input[left_child]) {
                child_index = left_child;
            } else if(right_child < i && input[index] < input[right_child]) {
                child_index = right_child;
            } 

            if(child_index < i && input[index] < input[child_index]) {
                std::swap(input[index], input[child_index]);
                index = child_index;
            } else {
                break;
            }
        }
    }
}

/*
* In this algorithm count the occurences of each elements 
* and walk over the counts in an ascending order and output
* the element corresponding to the key in the output array while
* decrementing the count.
*
* Time complexity: 
* Best case: all O(N)
*
* Space Complexity:
* O(N) for all cases.
*
* Not Stable sort, but can be made stable. Not In-place sort. 
*/
void counting_sort(std::vector<int>& input) {
    if(input.empty()) {
        return;
    }
    int min_elem = input[0], max_elem = input[0];
    for(auto num: input) {
        min_elem = std::min(min_elem, num);
        max_elem = std::max(max_elem, num);
    }

    std::vector<int> counts(max_elem - min_elem + 1, 0);
    for(auto num: input) {
        counts[num - min_elem]++;
    }

    /*
    * For making this stable sort, after taking counts, we will 
    * walk over the input array from right to left. 
    * Because of the counts array we already know how many times
    * the given element we are currently looking at appears in the array.
    * 
    * We just need to know where to place the current element in the output array.
    * 
    * If 0 occurs 10 times and 1 occurs 5 times. Then assuming there are only 3 
    * twos the first 2 occurs at the index position 15. The next 2 at 
    * index position 16. And the final 2 occurs at 17. 
    * 
    * By adding the counts of 0 and 1 we get the location where the first 2 needs to be placed.
    * If we add the count of 2 to that as well, we will get to the loction of the last 2.
    * 
    * Since we are iterating from right to left we just need to look at the count of 2 and write the
    * 2 at that location and decrement the count. So the next time we see the 2 again we just use the
    * counts again and write the 2 at that location and move on.
    *
    */
    for(int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i - 1];
    }

    std::vector<int> output(input.size(), 0);
    for(int i = input.size() - 1; i >= 0; i--) {
        output[counts[input[i] - min_elem] - 1] = input[i];
        counts[input[i] - min_elem]--;
    }

    for(int i = 0; i < input.size(); i++) {
        input[i] = output[i];
    }
}

/* 
* Sort all the numbers by the last digit of the number.
* Then proceed to sort the array of the previous step using the last but one digit using a stable sort.
* If the last but one digit is the same and we used a stable sort previously, then the elements 
* will already be ordered by the last digit.
* If the last but one digit is different then the bigger number will be placed after the smaller number.
* Do this for the next digit and keep doing it till we run out of digits.
* We use exp to keep track of what position within the number we are working on. We use counting sort
* for this. The stable version of counting sort.
*
* Time complexity: 
* Best case: all O(D*(N + B)) D => max number of digits. N=> Number of elements to sort. B => Base
*
* Space Complexity:
* O(N) for all cases.
*
* Stable sort. Not In-place sort. Doesn't work with negative numbers.
*/
void radix_counting_sort(std::vector<int>& input, int exp) {
    if(input.empty()) {
        return;
    }
    
    std::vector<int> counts(11, 0);
    for(auto num: input) {
        counts[(num / exp) % 10]++;
    }

    // for stable sort
    for(int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i - 1];
    }

    std::vector<int> output(input.size(), 0);
    for(int i = input.size() - 1; i >= 0; i--) {
        output[counts[(input[i] / exp) % 10] - 1] = input[i];
        counts[(input[i] / exp) % 10]--;
    }

    for(int i = 0; i < input.size(); i++) {
        input[i] = output[i];
    }
}

void radix_sort(std::vector<int>& input) {
    if(input.empty()) {
        return;
    }
    int min_elem = input[0], max_elem = input[0];
    for(auto num: input) {
        min_elem = std::min(min_elem, num);
        max_elem = std::max(max_elem, num);
    }
    // Hack to make this work for arrays with negative elements.
    if(min_elem < 0) {
        sort(input.begin(), input.end());
        return;
    }

    int exp = 1;
    while(max_elem) {
        radix_counting_sort(input, exp);
        exp *= 10;
        max_elem  /= 10;
    }
}


/*
* Divide the elements into a K buckets.
* Sort the buckets individually
* Walk the buckets and emit the elements.
*
* Time complexity: 
* Depends on the underlaying sorting algorithm.
*
* Space Complexity:
* O(N + K) for all cases.
*
* Stable sort. Not In-place sort.
*/
void bucket_sort(std::vector<int>& input, int k) {
    std::vector<std::vector<int>> buckets(k + 1, std::vector<int>());
    
    int max_elem = *std::max_element(input.begin(), input.end());
    int min_elem = *std::min_element(input.begin(), input.end());
    double denominator = max_elem - min_elem;
    denominator = denominator == 0 ? 1 : denominator;
    for(auto num: input) {
        buckets[(int)(((num - min_elem) / denominator) * k)].push_back(num);
    }

    int left_edge = 0;
    for(auto& bucket: buckets) {
        std::sort(bucket.begin(), bucket.end());
        for(auto num: bucket) {
            input[left_edge++] = num;
        }
    }
}

void bucket_sort_wrapper(std::vector<int>& input) {
    if(input.empty()) {
        return;
    }
    bucket_sort(input, 10);
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
        {0, 0},
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
        {1, 1, 1, -1, -1, -1}
    };

    bool atleast_one_fail = false;
    for(auto& test_case: test_cases) {
        std::vector<int> test_case_copy(test_case.begin(), test_case.end());
        std::vector<int> sorted_output(test_case.begin(), test_case.end());
        sort(sorted_output.begin(), sorted_output.end());

        function(test_case);

        bool failed = false;
        for(int i = 0; i < test_case.size(); i++) {
            if(test_case[i] != sorted_output[i]) {
                failed = true;
                atleast_one_fail = true;
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
    if(!atleast_one_fail) {
        std::cout << "Pass." << std::endl << std::endl;
    }
}

int main(int argc, char** argv) {
    std::vector<std::pair<std::string, sorting_algo>> sorting_functions = {
        {"Bubble sort", bubble_sort},
        {"Insertion sort", insertion_sort},
        {"Selection sort", selection_sort},
        {"Quick sort", quick_sort_wrapper},
        {"Merge sort", merge_sort_wrapper},
        {"Heap sort", heap_sort},
        {"Counting sort", counting_sort},
        {"Radix sort", radix_sort},
        {"Bucket sort", bucket_sort_wrapper}
    };
    for(auto& sorting_function: sorting_functions) {
        std::cout << "Testing " << sorting_function.first << std::endl;
        test_algorithm(sorting_function.second);
    }
    return 0;
}
