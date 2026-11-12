// Experiment No. 4: 0/1 Knapsack using Dynamic Programming

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void print_list(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

int knapsack_01(const vector<int>& values, const vector<int>& weights, int capacity,
                vector<int>& selected_items) {
    int n = values.size();
    // Step 1: Create DP table of size (n + 1) x (capacity + 1)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Step 2: Fill DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Step 3: Backtrack to find selected items
    selected_items.clear();
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected_items.push_back(i);   // 1-based index
            w -= weights[i - 1];
        }
    }
    reverse(selected_items.begin(), selected_items.end());

    return dp[n][capacity];
}

int main() {
    // --- Main Program ---
    // Example from SPPU LP-3 Lab Manual
    vector<int> values = {50, 100, 150, 200};
    vector<int> weights = {8, 16, 32, 40};
    int capacity = 64;

    vector<int> items;
    int max_profit = knapsack_01(values, weights, capacity, items);

    cout << "Values   : "; print_list(values); cout << endl;
    cout << "Weights  : "; print_list(weights); cout << endl;
    cout << "Capacity : " << capacity << endl;
    cout << string(35, '-') << endl;
    cout << "Maximum Profit : " << max_profit << endl;
    cout << "Selected Items : "; print_list(items); cout << endl;
    cout << string(35, '-') << endl;
    cout << "Time Complexity : O(n * W)" << endl;
    cout << "Space Complexity: O(n * W)" << endl;
    return 0;
}

/*
ALGORITHM: 0/1 Knapsack (Dynamic Programming)

1. Start.
2. Input the values[], weights[] of n items and the knapsack capacity W.
3. Create a table dp[0..n][0..W] and initialise every cell to 0.
   dp[i][w] = maximum value using the first i items with capacity w.
4. For i = 1 to n:
     For w = 1 to W:
        a. If weights[i-1] <= w:
             dp[i][w] = max( dp[i-1][w],
                             values[i-1] + dp[i-1][w - weights[i-1]] )
           (either leave item i, or take it and add its value)
        b. Else:
             dp[i][w] = dp[i-1][w]       (item i does not fit)
5. The maximum profit is dp[n][W].
6. Backtrack to find the selected items:
     Set w = W.
     For i = n down to 1:
        If dp[i][w] != dp[i-1][w]:
            item i is selected, and w = w - weights[i-1].
7. Display the maximum profit and the selected items.
8. Stop.

Time Complexity : O(n * W)
Space Complexity: O(n * W)
*/

    // Recursive Solution :
    // Time Complexity : O(2^n) 
    // Space Complexity : O(N)

    // Memoized Dynamic Programming :
    // Time Complexity : O(n*bagWeight)
    // Space Complexity : O(n*bagWeight) + O(n)

    // Tabulated Dynamic Programming :
    // Time Complexity : O(n*bagWeight)
    // Space Complexity : O(n*bagWeight)

