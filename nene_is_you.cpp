#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

/* 
    Summary so far:

    Create a map where a character corresponds to another character, 
        initially, if A is found as an input, and it does not exist yet in the map, then set the contents of map A to A, B to B etc.

    Aside from the input requirements, create a list of "active" characters and default them to false
        set already existing keys in the map as active 
        if A becomes D then that means A is no longer active and D becomes the next active one, will be useful later

    For each statement, where 
        X will be equal the first character 
        Y is the replacement character

        if a does not actively exist then just ignore the next part
            ex: 
                Map Contents = {A:A, B:B, C:C}
                Statement = D(X) -> E(Y)
                ignore 
        
        if b is already active before the replacement happens, then that means two different colors would change at the same time 
            therefore the picture could no longer be restored output NO
            EXIT program

        Check for the value of each key in the map if it corresponds to X (at this point, it will be guaranteed to exist in one of the keys)
            change the value of key -> Y

    Output YES

    When reversing the statements, check whether the current key is inactive, if it does, it is possible to
    snowball the contents if it follows a linear pattern where
        Ex: imagine D is inactive
        m[D] -> C
        m[C] -> B 
        m[B] -> A
        m[A] -> Z

        then it would be possible to snowball the results with
        m[D] -> D
        m[C] -> C
        m[B] -> B
        m[A] -> A

        however, this current version does not take into account three way loops yet
*/

int numberOfSteps(int counter, map<char, char> &m, vector<string> &reverse, vector<bool> &active) {
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << "In here" << endl;
        char key = it->first;
        char value = it->second;

        if(key == value) continue;

        cout << active[key - 65] << endl;

        while(!active[key - 65]) {
            cout << "Inactive key detected: " << key << endl;
            char nextKey = value;
            active[value - 65] = false;
            active[key - 65] = true;
            m[key] = key;

            reverse.push_back(value + " is " + key);
            counter++;
            it = m.find(nextKey);
            key = it->first;
            value = it->second;
        }        
    }
    cout << "Exiting " << endl;
    return counter;
}

int main() {
    int r, c, n, counter = 0;
    vector<bool> active(26, false);
    map<char, char> m;
    vector<string> statements, reverse;
    cin >> r >> c;

    for(int i = 0; i < r; i++) {
        string test;        
        char a;
        for(int j = 0; j < c; j++) {
            cin >> a;
            if (m.find(a) == m.end()) {
                m[a] = a;
                active[a - 65] = true;
            }
            test += a;
        }
    }

    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        string statement;
        getline(cin, statement);
        statements.push_back(statement);
    }

    for (string statement: statements) {
        char a = statement[0];
        char b = statement[statement.size() - 1];
        // if the key does not exist ignore the next part
        if (!active[a - 65]) continue;
        
        // if b actively exists before the switchup then it is no longer possible to restore
        if (active[b - 65]) {
            cout << "NO" << endl;
            return 0;
        }

        active[a - 65] = false;
        active[b - 65] = true;

        for (auto x: m) {
            char key = x.first;
            char value = x.second;

            if (key == a) {
                m[key] = b;
                break;
            }
        }
    }

    cout << "YES" << endl;
    cout << numberOfSteps(0, m, reverse, active) << endl;
}

