#include <set>
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "OrderedSetCycle.cpp"

using namespace std;
typedef map<unsigned, OrderedSetCycle> NormalIndex;

int triangular_number(int n) {
    return (n * (n  + 1)) / 2;
}

int centered_hexagonal_number(int n) {
    return 1 + 6 * triangular_number(n);
}

void add_rightmost_triangles(vector< array<unsigned, 3> > &triangles, unsigned v,unsigned a, unsigned b, unsigned c, unsigned d, unsigned e) {
    array<unsigned, 3> one = {v, a, b};
    triangles.push_back(one);
    array<unsigned, 3> two = {v, b, c};
    triangles.push_back(two);
    array<unsigned, 3> three = {v, c, d};
    triangles.push_back(three);
    array<unsigned, 3> four = {v, d, e};
    triangles.push_back(four);
}

int main() {
    unsigned n = 4;
    OrderedSetCycle ring[n];
    vector< array<unsigned, 3> > triangles;
    map< unsigned, vector<unsigned> > normal_index;

    // populate ring indices
    ring[0].push_back(0); // initial condition
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = centered_hexagonal_number(i - 1); j < centered_hexagonal_number(i); ++j) {
            ring[i].push_back(j);
        }
    }
    /*
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
    */
    NormalIndex boundary_neighbours;
    unsigned boundary_ring = n - 1;
    for (unsigned side = 0; side < 6; ++side) { // side
        for (unsigned side_index = 0; side_index < boundary_ring; ++side_index) { // boundary vertex
            unsigned vertex = side * boundary_ring + side_index;
            unsigned vertex_inner = side * (boundary_ring - 1) + side_index;
            if (side_index == 0) { // corner
                /*
                 *    (v)---- a
                 *    / \
                 *   /   \
                 *  c     b
                 *
                 */
                unsigned v = ring[boundary_ring][vertex];
                unsigned a = ring[boundary_ring][vertex + 1];
                unsigned b = ring[boundary_ring - 1][vertex_inner];
                unsigned c = ring[boundary_ring][vertex - 1];
                boundary_neighbours[v].push_back(a, b, c);
            } else {
                /*
                 *  d ----(v)---- a
                 *        / \
                 *       /   \
                 *      c     b
                 *
                 */
                unsigned v = ring[boundary_ring][vertex];
                unsigned a = ring[boundary_ring][vertex + 1];
                unsigned b = ring[boundary_ring - 1][vertex_inner];
                unsigned c = ring[boundary_ring - 1][vertex_inner - 1];
                unsigned d = ring[boundary_ring][vertex - 1];
                boundary_neighbours[v].push_back(a, b, c, d);
            }
        }
    }
    NormalIndex neighbours;
    neighbours[0].push_back(1, 2, 3, 4,  5, 6);  // initial condition
    for (unsigned side_length = 1; side_length < n - 1; ++side_length) { // ring
        for (unsigned side = 0; side < 6; ++side) { // side
            for (unsigned side_index = 0; side_index < side_length; ++side_index) { // interior vertex
                unsigned vertex = side * side_length + side_index;
                unsigned vertex_inner = side * (side_length - 1) + side_index;
                unsigned vertex_outer = side * (side_length + 1) + side_index;
                unsigned v = ring[side_length][vertex];
                unsigned a, b, c, d, e, f;
                if (vertex % side_length == 0) {
                    /*
                     * interior corner
                     *
                     *      e-----f
                     *             \
                     *              \
                     *  d ----(v)    a
                     *          \
                     *           \
                     *      c     b
                     *
                     */
                    a = ring[side_length + 1][vertex_outer + 1];
                    b = ring[side_length][vertex + 1];
                    c = ring[side_length - 1][vertex_inner];
                    d = ring[side_length][vertex - 1];
                    e = ring[side_length + 1][vertex_outer - 1];
                    f = ring[side_length + 1][vertex_outer];
                    // cout << "interior corner " << ring[side_length][vertex] << ": " << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
                    neighbours[v].push_back(a, b, c, d, e, f);
                } else {
                    /*
                     * interior boundary
                     *
                     *      e-----f
                     *
                     *
                     *  d ----(v)---- a
                     *
                     *
                     *      c-----b
                     *
                     */
                    a = ring[side_length][vertex + 1];
                    b = ring[side_length - 1][vertex_inner];
                    c = ring[side_length - 1][vertex_inner - 1];
                    d = ring[side_length][vertex - 1];
                    e = ring[side_length + 1][vertex_outer];
                    f = ring[side_length + 1][vertex_outer + 1];
                    // cout << "interior boundary " << ring[side_length][vertex] << ": " << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
                    neighbours[ring[side_length][vertex]].push_back(a, b, c, d, e, f);
                }
                // add four rightmost triangles
                add_rightmost_triangles(triangles, v, e, f, a, b, c);
            }
       }
        cout << "\n";
    }
    /*
    for (unsigned i = 0; i < boundary_neighbours.size(); ++i) {
        cout << i  << setfill(' ') << setw(2) << ": " <<setw(2) ;
        for (unsigned j = 0; j < boundary_neighbours[i].size(); ++j) {
            cout << boundary_neighbours[i][j] << setfill(' ') << setw(2) << " ";
        }
        cout << "\n";
    }
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        cout << i  << setfill(' ') << setw(2) << ": " <<setw(2) ;
        for (unsigned j = 0; j < neighbours[i].size(); ++j) {
            cout << neighbours[i][j] << setfill(' ') << setw(2) << " ";
        }
        cout << "\n";
    }
    */
    for (unsigned i = 0; i < triangles.size(); ++i) {
        for (unsigned j = 0; j < triangles[i].size(); ++j) {
            cout << triangles[i][j] << setfill(' ') << setw(2) << " ";
        }
        cout << "\n";
    }
}
