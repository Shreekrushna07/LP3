// Dynamci approach

#include <bits/stdc++.h>
using namespace std;

class Knapsack {
    int n; // Number of items
    int w; // Maximum capacity of the knapsack
    vector<pair<int, int>> input; // Vector to store value and weight pairs
    vector<vector<int>> ans; // DP table for storing results
public:
    void accept();
    void zerooneknapsack();
    void display(); 
};

void Knapsack::accept() {
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the max capacity of bag: ";
    cin >> w;
    input.resize(n);
    cout << "\nEnter the value and weight of each item\n";
    for (int i = 0; i < n; i++) {
        cin >> input[i].first >> input[i].second;
    }
    ans.resize(n + 1, vector<int>(w + 1, 0));
}

void Knapsack::zerooneknapsack() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (i == 0 || j == 0) {
                ans[i][j] = 0;
            } else if (j >= input[i - 1].second) {
                ans[i][j] = max(ans[i - 1][j], ans[i - 1][j - input[i - 1].second] + input[i - 1].first);
            } else {
                ans[i][j] = ans[i - 1][j];
            }
        }
    }
}

void Knapsack::display() {
    cout << "\nValue\t\tWeight\n";
    for (const auto &pair : input) {
        cout << pair.first << "\t\t" << pair.second << endl;
    }
    cout << "Maximum Profit: " << ans[n][w] << endl;
}

int main() {
    Knapsack obj;
    obj.accept();
    obj.zerooneknapsack();
    obj.display();
    return 0;
}