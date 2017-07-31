#include <set>
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <iomanip>

using namespace std;

int triangular_number(int n) {
    return (n * (n  + 1)) / 2;
}

int centered_hexagonal_number(int n) {
    return 1 + 6 * triangular_number(n);
}


int main() {
    unsigned n = 3;
    vector<unsigned> ring[n];
    vector< array<unsigned, 3> > triangles;

    // populate ring indices
    ring[0].push_back(0); // initial condition
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = centered_hexagonal_number(i - 1); j < centered_hexagonal_number(i); ++j) {
            ring[i].push_back(j);
        }
    }
    for (unsigned i = 0; i < n; ++i) {
        cout << i << ": \n";
        for (unsigned j = 0; j < ring[i].size(); ++j) {
            // cout << " " <<  setfill(' ') << setw(2) << j;
        }
        // cout << "\n";
        for (unsigned j = 0; j < ring[i].size(); ++j) {
            cout << " " <<  setfill(' ') << setw(2) << ring[i][j];
        }
        cout << "\n";
    }
    /*
        * i = side length
        * k = triangle start index
        * j = side
    */
    for (unsigned side_length = 1; side_length < n; ++side_length) { // ring
        for (unsigned side = 0; side < 6; ++side) { // side
            cout << "--\n";
            for (unsigned triangle_start = 0; triangle_start < side_length; ++triangle_start) { // boundary vertex
                unsigned side_increment = side * side_length;
                unsigned side_increment_inner = side * (side_length - 1);
                /*
                    *  a ___ b
                    *   \   /
                    *    \ /
                    *     c
                    *
                    */
                unsigned a = ring[side_length][side_increment + triangle_start];
                unsigned b, c;
                if (side_increment + triangle_start + 1 == ring[side_length].size()) {
                    cout << triangle_start << ": ";
                    b = ring[side_length][triangle_start];
                    c = ring[side_length - 1][triangle_start];
                } else {
                    b = ring[side_length][side_increment + triangle_start + 1];
                    c = ring[side_length - 1][side_increment_inner + triangle_start];
                }
                cout << a << " " << b << " " << c << " \\/\n";
                array<unsigned, 3> triangle = {a, b, c};
                triangles.push_back(triangle);
                if ((triangle_start + 1) % 2 == 0) {
                    /*
                    *     b'
                    *    / \
                    *   /___\
                    *  c'    d
                    *
                    */
                    unsigned b_ = ring[side_length][side_increment + triangle_start];
                    unsigned d;
                    if (side_increment_inner + triangle_start == ring[side_length - 1].size()) {
                        cout << triangle_start << ": ";
                        d = ring[side_length - 1][triangle_start];
                    } else {
                        d = ring[side_length - 1][side_increment_inner + triangle_start];
                    }
                    unsigned c_ = ring[side_length - 1][side_increment_inner + triangle_start - 1];
                    cout << b_ << " " << d << " " << c_ << " /\\\n";
                    array<unsigned, 3> triangle = {b_, d, c_};
                    triangles.push_back(triangle);
                }

            }
            }
            cout << "==\n";
    }
}
