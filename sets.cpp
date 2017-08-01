#include <set>
#include <iostream>

using namespace std;

int main(){
    set<set<unsigned>> triangles;

    set<unsigned> a = {0, 1, 2};
    triangles.insert(a);

    a = {0, 2, 3};
    triangles.insert(a);
    set<set<unsigned>>::iterator triangle;
    unsigned i = 0;
    for (triangle = triangles.begin(); triangle != triangles.end(); ++triangle) {
        set<unsigned>::iterator index;
        for (index = (*triangle).begin(); index != (*triangle).end(); ++index) {
            cout << i << ": " << (*index) << " ";
            i++;
        }
        cout << "\n";
        i = 0;
    }
    /*
    */
    a = {2, 0, 3};
    set<set<unsigned>>::iterator search = triangles.find(a);
    if (search == triangles.end()) {
        cout << "not finded";
    } else {
        cout << "finded it ";
        for (auto index: (*search)) {
            cout << index << " ";
        }
    }
}
