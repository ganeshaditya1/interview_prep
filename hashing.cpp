#include <bits/stdc++.h>

class hasher {
public:
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;
};

class separate_chaining : public hasher {
private:
    std::vector<std::list<std::pair<int, int>>> buckets;
    static const int DEFAULT_SIZE = 11;
public:
    separate_chaining() : buckets(DEFAULT_SIZE) {}
    separate_chaining(int size) : buckets(size) {}
    void set(int key, int value) {
        std::list<std::pair<int, int>>& bucket = buckets[key % buckets.size()];
        for(auto& p: bucket) {
            if(p.first == key) {
                p.second = value;
                return;
            }
        }

        bucket.push_back({key, value});
    }

    int get(int key) {        
        std::list<std::pair<int, int>>& bucket = buckets[key % buckets.size()];
        if(bucket.empty()) {
            return -1;
        }

        for(auto& p: bucket) {
            if(p.first == key) {
                return p.second;
            }
        }
        return -1;
    }
};

/* The following three hashing algorithms/collision resolution algorithms are called open addressing schemes.*/

class linear_probing : public hasher {
private:
    std::vector<std::pair<int, int>*> hash_table;
    static const int DEFAULT_SIZE = 200;
public:
    linear_probing() : hash_table(DEFAULT_SIZE, nullptr) {}
    linear_probing(int size) : hash_table(size, nullptr) {}

    void set(int key, int value) {
        int hash_index = key % hash_table.size();
        int counter = 0;
        while(hash_table[hash_index] != nullptr) {
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
            if(hash_table[hash_index]->first == key) {
                hash_table[hash_index]->second = value;
                return;
            } else {
                hash_index = (hash_index + 1) % hash_table.size();
            }
        }
        if(hash_table[hash_index] == nullptr) {
            hash_table[hash_index] = new std::pair<int, int>();
            hash_table[hash_index]->first = key;
            hash_table[hash_index]->second = value;
            return;
        } 
        throw std::runtime_error("Hash table full.");
    }

    int get(int key) {
        int hash_index = key % hash_table.size();
        int counter = 0;
        while(hash_table[hash_index] != nullptr) {
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
            if(hash_table[hash_index]->first == key) {
                return hash_table[hash_index]->second;
            } else {
                hash_index = (hash_index + 1) % hash_table.size();
            }
        }
        throw std::runtime_error("Key not found.");
    }
};

class quadratic_probing : public hasher {
private:
    std::vector<std::pair<int, int>*> hash_table;
    static const int DEFAULT_SIZE = 200;
public:
    quadratic_probing() : hash_table(DEFAULT_SIZE, nullptr) {}
    quadratic_probing(int size) : hash_table(size, nullptr) {}

    void set(int key, int value) {
        int hash_index = key % hash_table.size();
        int counter = 0, current_pos = hash_index;
        while(hash_table[current_pos] != nullptr) {
            if(hash_table[current_pos]->first == key) {
                hash_table[current_pos]->second = value;
                return;
            } else {
                current_pos = (current_pos + (counter * counter)) % hash_table.size();
            }
            
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
        }
        if(hash_table[current_pos] == nullptr) {
            hash_table[current_pos] = new std::pair<int, int>();
            hash_table[current_pos]->first = key;
            hash_table[current_pos]->second = value;
            return;
        } 
        throw std::runtime_error("Hash table full.");
    }

    int get(int key) {
        int hash_index = key % hash_table.size();
        int counter = 0, current_pos = hash_index;
        while(hash_table[current_pos] != nullptr) {
            if(hash_table[current_pos]->first == key) {
                return hash_table[current_pos]->second;
            } else {
                current_pos = (current_pos + (counter * counter)) % hash_table.size();
            }
            
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
        }
        throw std::runtime_error("Hash table full.");
    }
};


class double_hashing : public hasher {
private:
    std::vector<std::pair<int, int>*> hash_table;
    static const int DEFAULT_SIZE = 200;
public:
    double_hashing() : hash_table(DEFAULT_SIZE, nullptr) {}
    double_hashing(int size) : hash_table(size, nullptr) {}

    static inline int h1(int key) {
        return (key % 5) + 1;
    }

    static inline int h2(int key) {
        return (key % 7) + 1;
    }

    void set(int key, int value) {
        int hash_index = h1(key) % hash_table.size();
        int counter = 0, current_pos = hash_index;
        while(hash_table[current_pos] != nullptr) {
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
            if(hash_table[current_pos]->first == key) {
                hash_table[current_pos]->second = value;
                return;
            } else {
                current_pos = (h1(key) + (counter * h2(key))) % hash_table.size();
            }
        }

        if(hash_table[current_pos] == nullptr) {
            hash_table[current_pos] = new std::pair<int, int>();
            hash_table[current_pos]->first = key;
            hash_table[current_pos]->second = value;
            return;
        }
        throw std::runtime_error("Hash table full.");
    }

    int get(int key) {
        int hash_index = h1(key) % hash_table.size();
        int counter = 0, current_pos = hash_index;
        while(hash_table[current_pos] != nullptr) {
            if(hash_table[current_pos]->first == key) {
                return hash_table[current_pos]->second;
            } else {
                current_pos = (h1(key) + (counter * h2(key))) % hash_table.size();
            }
            
            // Avoid infinite loops.
            if(counter++ == hash_table.size()) {
                break;
            }
        }
        throw std::runtime_error("Hash table full.");
    }
};

void tester(hasher& hash_obj, bool open_addressing=false) {
    for(int i = 1; i < 10; i++) {
        hash_obj.set(i, i * i);
    }

    for(int i = 20; i < 30; i++) {
        hash_obj.set(i, i * i);
    }
    if(open_addressing) {
        // All the hash functions have a size of 25, so this should fail.
        int count = 0;
        for(int i = 30; i <= 40; i++) {
            try {
                hash_obj.set(i, i * i);
            } catch(std::runtime_error) {
                count++;
            }
        }

        if(count != 5) {
            std::cout << "Set operations failure count mismatch. Expect 5, actual count: " << count << std::endl;
        }
    }

    hash_obj.set(5, 125);
    hash_obj.set(7, 49 * 7);

    for(int i = 1; i < 10; i++) {
        int v = hash_obj.get(i);
        int expected_value = i * i;
        if(i == 5 || i == 7) {
            expected_value *= i;
        }
        if(v != expected_value) {
            std::cout << "Value mismatch for key: " << i << " Expected value: " << expected_value << " Found value: " << v << std::endl;
        }
    }
    try {
        if(hash_obj.get(12) != -1) {
            std::cout << "value mismatch. key: " << 12 << " Expected -1 found: " << hash_obj.get(12) << std::endl;
        }
    } catch(std::runtime_error e) {}

    for(int i = 20; i < 30; i++) {
        int v = hash_obj.get(i);
        int expected_value = i * i;
        if(i == 5 || i == 7) {
            expected_value *= i;
        }
        if(v != expected_value) {
            std::cout << "Value mismatch for key: " << i << " Expected value: " << expected_value << " Found value: " << v << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    // All the hash functions have a fixed size of 25;
    const int size = 25;
    separate_chaining sc;
    linear_probing lp(size);
    quadratic_probing qp(size);
    double_hashing dh(size);

    // The bool indicates if this hashing object is open addressing scheme.
    std::vector<std::tuple<std::string, hasher&, bool>> hasher_testcases = {
        {"Separate chaining", sc, false},
        {"Linear Probing", lp, true},
        {"Quadratic probing", qp, true},
        {"Double hashing", dh, true}
    };

    for(auto& hash_testcase: hasher_testcases) {
        auto& [hasher_name, hashing_obj, open_addressing] = hash_testcase;
        std::cout << "Testing " << hasher_name << std::endl;
        tester(hashing_obj, open_addressing);
    }

    return 0;
}