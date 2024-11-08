#include <bits/stdc++.h>
using namespace std;

bool compare(pair<int, int> item1, pair<int, int> item2) {
    double valueperweight1 = (double)item1.first / item1.second;
    double valueperweight2 = (double)item2.first / item2.second;
    return valueperweight1 > valueperweight2;
}

int main() {
    int numberitem;
    cout << "Enter the number of items: ";
    cin >> numberitem;
    vector<pair<int, int>> item(numberitem);

    for (int i = 0; i < numberitem; i++) {
        cout << "Enter the value and weight: ";
        cin >> item[i].first >> item[i].second;
    }

    sort(item.begin(), item.end(), compare);

    int maxcapacity;
    cout << "Enter maximum capacity of bag: ";
    cin >> maxcapacity;

    double maxvalue = 0;  // Initialize maxvalue to 0

    for (int i = 0; i < numberitem; i++) {
        if (maxcapacity >= item[i].second) {
            maxcapacity -= item[i].second;
            maxvalue += item[i].first;
        } else {
            double valueperweight = (double)item[i].first / item[i].second;
            maxvalue += valueperweight * maxcapacity;
            break;  // Since this is a fractional knapsack, break once capacity is full
        }
    }

    cout << "Maximum value is " << maxvalue;
    return 0;
}