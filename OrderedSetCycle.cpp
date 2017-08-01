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
    unsigned size() { return vec.size(); }
    unsigned operator[](int index) {
        unsigned end = vec.size();
        if (index < end) {
            if (index < 0) {
               if (abs(index) < end) {
                    return vec[end + index];
               } else {
                    return vec[end + (index % end)];
               }
            } else {
                return vec[index];
            }
        } else {
            return vec[index % end];
        }
    }
private:
    vector<unsigned> vec;
};

