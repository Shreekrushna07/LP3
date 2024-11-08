#include<bits/stdc++.h>
using namespace std;

vector<int> arr(1000, -1);
int recursive(int n) {
    if (n==0 || n==1) {
        return n;
    } 
    if (arr[n] != -1) {
        return arr[n];
    }
    arr[n] = recursive(n-1) + recursive(n-2);
    return arr[n];
}

void nonRecursive(int n) {
    int prev1 = 0, prev2 = 1, result;
    if (n == 0) {
        cout<<prev1;
    } else if (n==1) {
        cout<<prev1<<", "<<prev2;
    } else {
        cout<<prev1<<", "<<prev2;
        for (int i=2; i<n; i++) {
            result = prev1 + prev2;
            cout<<", "<<result;
            prev1 = prev2;
            prev2 = result;
        }
    }
    cout<<endl;
}

int main() {
    int n;
    cout<<"Enter the position of number: ";
    cin>>n;

    if (n<0) {
        cout<<"Please enter a positive number."<<endl;
        return 1;
    }

    int ch;
    while(true) {
        cout<<"\n1. Non-recursive";
        cout<<"\n2. Recursive";
        cout<<"\n3. Exit";
        cout<<"\nEnter the choice: ";
        cin>>ch;
        switch (ch) {
            case 1:
                nonRecursive(n);
                break;

            case 2:
                cout<<"\n******************************************\n";
                for (int i=0; i<n; i++) {
                    cout<<recursive(i)<<", ";
                }
                cout<<endl;
                break;

            case 3:
                exit(0);
                break;

            default:
                cout << "Invalid choice! Please select 1, 2, or 3." << endl;
        }
        
    }
    return 0;
}