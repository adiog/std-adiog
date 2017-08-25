#include <io>
#include "dataStructure/BinaryIndexTree.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    cin >> v;
    dataStructure::BinaryIndexTree bit(v);
    cout << bit << endl;
    cout << bit.getValues() << endl;
    return 0;
}