#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, x, counter = 0; 
    vector<int> arr;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        arr.push_back(x);
    }

    sort(arr.begin(), arr.end());
    for (int num: arr) {
        if (num <= counter) {
            counter++;
        } else {
            break;
        }
    } 

    cout << counter << endl;
}