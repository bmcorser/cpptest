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
    cout << "\n";
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

                /*
                cout << side_length << setfill(' ') << setw(5);
                cout << side << setfill(' ') << setw(5);
                cout << side_index << setfill(' ') << setw(6);
                cout << edge << setfill(' ') << setw(5);
                cout << edge_inner << setfill(' ') << setw(6);
                */

                /*
                 *  a ___ b
                 *   \   /
                 *    \ /
                 *     c
                 *
                 */
                unsigned a = ring[side_length][edge];
                unsigned b = ring[side_length][edge + 1];
                unsigned c = ring[side_length - 1][edge_inner];
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
                    unsigned d = ring[side_length - 1][edge_inner];
                    // contribute_to_normal_index(normal_index, c, b, d);
                    // cout << setfill(' ') << setw(28) << b << setw(3) << d << setw(3) << c << setw(3) << " /\\\n";
                    array<unsigned, 3> triangle = {b, d, c};
                    triangles.push_back(triangle);
                }
            }
        }
        // cout << "\n";
    }
    NormalIndex boundary_neighbours;
    unsigned boundary_ring = n - 1;
    for (unsigned side = 0; side < 6; ++side) { // side
        for (unsigned side_index = 0; side_index < boundary_ring; ++side_index) { // boundary vertex
            unsigned vertex = side * boundary_ring + side_index;
            unsigned vertex_inner = side * (boundary_ring - 1) + side_index;
            if (side_index == 0) { // corner
                /*
                 *     v ---- a
                 *    / \
                 *   /   \
                 *  c     b
                 *
                 */
                unsigned a = ring[boundary_ring][vertex + 1];
                unsigned b = ring[boundary_ring - 1][vertex_inner];
                unsigned c = ring[boundary_ring][vertex - 1];
                boundary_neighbours[ring[boundary_ring][vertex]].push_back(a, b, c);
            } else {
                /*
                 *  d ---- v ---- a
                 *        / \
                 *       /   \
                 *      c     b
                 *
                 */
                unsigned a = ring[boundary_ring][vertex + 1];
                unsigned b = ring[boundary_ring - 1][vertex_inner];
                unsigned c = ring[boundary_ring - 1][vertex_inner - 1];
                unsigned d = ring[boundary_ring][vertex - 1];
                boundary_neighbours[ring[boundary_ring][vertex]].push_back(a, b, c, d);
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
                if (vertex % side_length == 0) {
                    /*
                     * interior corner
                     *
                     *      e-----f
                     *             \
                     *              \
                     *  d ----(*)    a
                     *          \
                     *           \
                     *      c     b
                     *
                     */
                    unsigned a = ring[side_length + 1][vertex_outer + 1];
                    unsigned b = ring[side_length][vertex + 1];
                    unsigned c = ring[side_length - 1][vertex_inner];
                    unsigned d = ring[side_length][vertex - 1];
                    unsigned e = ring[side_length + 1][vertex_outer - 1];
                    unsigned f = ring[side_length + 1][vertex_outer];
                    cout << "interior corner " << ring[side_length][vertex] << ": " << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
                    neighbours[ring[side_length][vertex]].push_back(a, b, c, d, e, f);
                } else {
                    /*
                     * interior boundary
                     *
                     *      e-----f
                     *
                     *
                     *  d ----(*)---- a
                     *
                     *
                     *      c-----b
                     *
                     */
                    unsigned a = ring[side_length][vertex + 1];
                    unsigned b = ring[side_length - 1][vertex_inner];
                    unsigned c = ring[side_length - 1][vertex_inner - 1];
                    unsigned d = ring[side_length][vertex - 1];
                    unsigned e = ring[side_length + 1][vertex_outer];
                    unsigned f = ring[side_length + 1][vertex_outer + 1];
                    cout << "interior boundary " << ring[side_length][vertex] << ": " << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
                    neighbours[ring[side_length][vertex]].push_back(a, b, c, d, e, f);
                }
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
    */
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        cout << i  << setfill(' ') << setw(2) << ": " <<setw(2) ;
        for (unsigned j = 0; j < neighbours[i].size(); ++j) {
            cout << neighbours[i][j] << setfill(' ') << setw(2) << " ";
        }
        cout << "\n";
    }
}
