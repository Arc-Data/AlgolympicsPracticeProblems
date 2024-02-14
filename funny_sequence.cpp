#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    vector<int> arr = {2, 3};
    cin >> n;

    if (n <= 1) {
        cout << arr[n] << endl;
        return 0;
    }

    for (int i = 2; i < n; i++) {
        int num = 2 * arr[i -  1] - arr[i - 2] + 2;
        arr.push_back(num);
    }
    
    cout << arr[arr.size() - 1] << endl;
}