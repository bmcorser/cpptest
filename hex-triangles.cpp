#include <set>
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef map< unsigned, vector<unsigned> > NormalIndex;
typedef vector< array<unsigned, 3> > TriangleList;
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

int triangular_number(int n) {
    return (n * (n  + 1)) / 2;
}

int centered_hexagonal_number(int n) {
    return 1 + 6 * triangular_number(n);
}

void set_push_back(vector<unsigned> &dest, unsigned value) {
    if (find(dest.begin(), dest.end(), value) == dest.end()) {
        dest.push_back(value);
    }
}

void contribute_edge_pair(vector<unsigned> &dest, unsigned left, unsigned right) {
    bool needs_left = find(dest.begin(), dest.end(), left) == dest.end();
    bool needs_right = find(dest.begin(), dest.end(), right) == dest.end();
    if (needs_left && needs_right) {
        dest.push_back(left);
        dest.push_back(right);
    }
}

void contribute_to_normal_index(map< unsigned, vector<unsigned> > &normal_index, unsigned a, unsigned b, unsigned c) {
    set_push_back(normal_index[a], b);
    set_push_back(normal_index[a], c);
    set_push_back(normal_index[b], a);
    set_push_back(normal_index[b], c);
    set_push_back(normal_index[c], a);
    set_push_back(normal_index[c], b);
    /*
    contribute_edge_pair(normal_index[c], a, b);
    contribute_edge_pair(normal_index[a], b, c);
    contribute_edge_pair(normal_index[b], a, c);
    */
}

int main() {
    unsigned n = 3;
    OrderedSetCycle ring[n];
    TriangleList triangles;

    // populate ring indices
    ring[0].push_back(0); // initial condition
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = centered_hexagonal_number(i - 1); j < centered_hexagonal_number(i); ++j) {
            ring[i].push_back(j);
        }
    }
    for (unsigned i = 0; i < n; ++i) {
        // cout << i << ": \n";
        for (unsigned j = 0; j < ring[i].size(); ++j) {
            // cout << " " <<  setfill(' ') << setw(2) << j;
        }
        // cout << "\n";
        for (unsigned j = 0; j < ring[i].size(); ++j) {
            // cout << " " <<  setfill(' ') << setw(2) << ring[i][j];
        }
        // cout << "\n";
    }
    // cout << "\n";
    /*
        * i = side length
        * k = triangle start index
        * j = side
    */
    for (unsigned side_length = 1; side_length < n; ++side_length) { // ring
        // cout << "ring side index edge inner\n";
        for (unsigned side = 0; side < 6; ++side) { // side
            for (unsigned side_index = 0; side_index < side_length; ++side_index) { // boundary vertex
                unsigned edge = side * side_length + side_index;
                unsigned edge_inner = side * (side_length - 1) + side_index;

                // cout << side_length << setfill(' ') << setw(5);
                // cout << side << setfill(' ') << setw(5);
                // cout << side_index << setfill(' ') << setw(6);
                // cout << edge << setfill(' ') << setw(5);
                // cout << edge_inner << setfill(' ') << setw(6);

                /*
                 *  a ___ b
                 *   \   /
                 *    \ /
                 *     c
                 *
                 */
                unsigned a = ring[side_length][edge];
                unsigned b = ring[side_length][0];
                unsigned c = ring[side_length - 1][0];
                // contribute_to_normal_index(normal_index, a, b, c);
                // cout << setfill(' ') << setw(6) << a << setw(3) << b << setw(3) << c << setw(3) << " \\/\n";
                array<unsigned, 3> triangle = {a, b, c};
                triangles.push_back(triangle);
                if ((edge + 1) % 2 == 0 && side_length > 1) {

                    /*
                     *     b'
                     *    / \
                     *   /___\
                     *  c'    d
                     *
                     */
                    unsigned b_ = ring[side_length][edge];
                    unsigned d;
                    if (edge_inner < ring[side_length - 1].size()) {
                        d = ring[side_length - 1][edge_inner];
                    } else {
                        d = ring[side_length - 1][0];
                    }
                    unsigned c_ = ring[side_length - 1][edge_inner - 1];
                    // contribute_to_normal_index(normal_index, c_, b_, d);
                    // cout << setfill(' ') << setw(28) << b_ << setw(3) << d << setw(3) << c_ << setw(3) << " /\\\n";
                    array<unsigned, 3> triangle = {b_, d, c_};
                    triangles.push_back(triangle);
                }
            }
        }
        // cout << "\n";
    }
    /*
    NormalIndex boundary_neighbours;
    for (unsigned side = 0; side < 6; ++side) { // side
        for (unsigned side_index = 0; side_index < side_length; ++side_index) { // boundary vertex
            unsigned edge = side * n + side_index;
            unsigned edge_inner = side * (side_length - 1) + side_index;
            if ((edge % n) == 0) {  // corner
                boundary_neighbours[ring[n][edge]].push_back(
            }
        }
    }
    NormalIndex neighbours;
    for (unsigned side_length = 1; side_length < n - 1; ++side_length) { // ring
        for (unsigned side = 0; side < 6; ++side) { // side
            for (unsigned side_index = 0; side_index < side_length; ++side_index) { // boundary vertex
                unsigned edge = side * side_length + side_index;
                unsigned edge_inner = side * (side_length - 1) + side_index;
            }
        }
    }
    */
    /*
    for (unsigned i = 0; i < normal_index.size(); ++i) {
        cout << i  << setfill(' ') << setw(2)<< ": "<<setw(2) ;
        for (unsigned j = 0; j < normal_index[i].size(); ++j) {
            cout << normal_index[i][j] << setfill(' ') << setw(2) << " ";
        }
        cout << "\n";
    }
    */
}
