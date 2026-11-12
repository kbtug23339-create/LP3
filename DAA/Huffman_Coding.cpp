#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

// 1. Node Definition
struct Node {
    int freq;
    string symbol;      // empty for internal nodes
    Node *left, *right;
    Node(int f, string s = "", Node* l = nullptr, Node* r = nullptr)
        : freq(f), symbol(s), left(l), right(r) {}
};

map<string, string> codes;

// 2. Traverse tree to assign prefix codes
void get_codes(Node* node, string code = "") {
    if (!node->symbol.empty()) {   // Leaf node
        codes[node->symbol] = code;
        return;
    }
    get_codes(node->left, code + "0");
    get_codes(node->right, code + "1");
}

int main() {
    // --- Main Program ---
    vector<string> symbols = {"m1", "m2", "m3", "m4", "m5", "m6", "m7"};
    vector<int> freqs = {4, 5, 7, 8, 10, 12, 20};

    // Build initial leaf nodes
    vector<Node*> nodes;
    for (size_t i = 0; i < symbols.size(); i++)
        nodes.push_back(new Node(freqs[i], symbols[i]));

    // Combine two smallest nodes greedily until one root remains
    while (nodes.size() > 1) {
        // stable sort keeps the same tie-breaking as Python's sort
        stable_sort(nodes.begin(), nodes.end(),
                    [](Node* a, Node* b) { return a->freq < b->freq; });
        Node* left = nodes.front();
        nodes.erase(nodes.begin());
        Node* right = nodes.front();
        nodes.erase(nodes.begin());
        nodes.push_back(new Node(left->freq + right->freq, "", left, right));
    }

    // Generate and print codes
    get_codes(nodes[0]);

    cout << "Symbol | Frequency | Huffman Code" << endl;
    cout << string(35, '-') << endl;
    for (size_t i = 0; i < symbols.size(); i++) {
        cout << left << setw(6) << symbols[i] << " | "
             << right << setw(9) << freqs[i] << " | "
             << codes[symbols[i]] << endl;
    }

    cout << string(35, '-') << endl;
    cout << "Time Complexity : O(n^2) [O(n log n) if using Min-Heap]" << endl;
    cout << "Space Complexity: O(n)" << endl;
    return 0;
}


//Complexity Analysis :
//Time complexity: O(nlogn) where n is the number of unique characters.
//If there are n nodes, extractMin() is called 2*(n – 1) times. 
//extractMin() takes O(logn) time as it calls minHeapify(). So, overall time complexity is O(nlogn).
//Space Complexity is O(n) 
//Where n is the number of Unique Characters

/*
ALGORITHM: Huffman Encoding (Greedy Strategy)

1. Start.
2. Take the symbols and their frequencies as input.
3. Create one leaf node for every symbol (node = frequency + symbol).
4. Repeat while more than one node remains in the list:
     a. Sort the nodes in increasing order of frequency.
     b. Remove the two nodes with the smallest frequencies (left, right).
     c. Create a new internal node whose frequency = left.freq + right.freq,
        with left and right as its children.
     d. Add the new node back to the list.
5. The one remaining node is the root of the Huffman tree.
6. Traverse the tree from the root:
     a. Moving to the left child appends '0' to the code.
     b. Moving to the right child appends '1' to the code.
     c. When a leaf node is reached, store the code built so far for its symbol.
7. Display each symbol with its frequency and Huffman code.
8. Stop.

Time Complexity : O(n^2) with repeated sorting, O(n log n) with a Min-Heap
Space Complexity: O(n)
*/
