#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OrderedSetCycle
{
public:
    OrderedSetCycle() { }
    ~OrderedSetCycle() { }
    void push_back(unsigned value) {
        if (find(vec.begin(), vec.end(), value) == vec.end()) {
            return vec.push_back(value);
        }
    }
    void push_back(unsigned a, unsigned b, unsigned c) {
        push_back(a);
        push_back(b);
        push_back(c);
    }
    void push_back(unsigned a, unsigned b, unsigned c, unsigned d) {
        push_back(a);
        push_back(b);
        push_back(c);
        push_back(d);
    }
    void push_back(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e, unsigned f) {
        push_back(a);
        push_back(b);
        push_back(c);
        push_back(d);
        push_back(e);
        push_back(f);
    }
    unsigned size() { return vec.size(); }
    unsigned operator[](int index) {
        unsigned end = vec.size();
        // negative access
        if (index < 0) {
            if (abs(index) < end) {
                return vec[end + index];
            } else {
                return vec[end + (index % end)];
            }
        }
        // positive access
        if (index < end) {
            return vec[index];
        } else {
            return vec[index % end];
        }
    }
private:
    vector<unsigned> vec;
};
