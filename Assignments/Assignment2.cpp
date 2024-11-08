#include<bits/stdc++.h>
using namespace std;

struct node {
    char c;
    int freq;
    node *left, *right;
    node(char c, int freq) {
        this->c = c;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct compare
{
    bool operator()(node *left, node *right) {
        return left->freq > right->freq;
    }
};

void printnode(struct node *root, string str, unordered_map<char, string>&huffmancodes) {
    if (!root) {
        return;
    } if (!root->left && !root->right) {
        cout<<root->c<<": "<<str<<endl;
        huffmancodes[root->c] = str;
    }

    printnode(root->left, str+"0", huffmancodes);
    printnode(root->right, str+"1", huffmancodes);
}

string decoding(struct node* root, string encode) {
    string decodestr = "";
    node *current = root;

    for (char c: encode) {
        if (c=='0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodestr += current->c;
            current = root;
        }
    }

    return decodestr;
}

void huffman(string str, unordered_map<char, int> my_map) {
    priority_queue<node*, vector<node*>, compare> minheap;
    for (auto pair: my_map) {
        minheap.push(new node(pair.first, pair.second));
    }
    while(minheap.size() != 1) {
        node *left = minheap.top(); minheap.pop();
        node *right = minheap.top(); minheap.pop();

        int sum = left->freq + right->freq;
        node *top = new node('$', sum);

        top->left = left;
        top->right = right;

        minheap.push(top);
    }
    // printnode(minheap.top(), "");
    unordered_map<char, string> huffmancodes;
    string encodes = "";
    string encode2 = "";
    printnode(minheap.top(), "", huffmancodes);
    for (char c: str) {
        encodes += huffmancodes[c];
        encode2 += huffmancodes[c] + " ";
    }
    // cout<<"\nEncode string: "<<encodes<<endl;
    cout<<"\nEncode string: "<<encode2<<endl;
    cout<<"Decode string: "<<decoding(minheap.top(), encodes);
}

int main() {
    string s;
    cout<<"Enter the string: ";
    cin>>s;

    unordered_map<char, int> my_map;
    for (char c: s) {
        my_map[c]++;
    }
    huffman(s, my_map);
    return 0;
}

// hufmancoding