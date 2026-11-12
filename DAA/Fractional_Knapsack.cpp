#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
using namespace std;

void print_list(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

double fractional_knapsack(const vector<int>& values, const vector<int>& weights, int capacity) {
    // Step 1: Pair items as (ratio, value, weight) and sort descending
    vector<tuple<double, int, int>> items;
    for (size_t i = 0; i < values.size(); i++)
        items.push_back(make_tuple((double)values[i] / weights[i], values[i], weights[i]));
    sort(items.begin(), items.end(), greater<tuple<double, int, int>>());  // Greedily sorts by ratio (v / w)

    double total_value = 0.0;

    // Step 2: Greedily pick items
    for (auto& it : items) {
        int v = get<1>(it);
        int w = get<2>(it);

        if (capacity == 0)
            break;

        if (w <= capacity) {
            // Take complete item
            capacity -= w;
            total_value += v;
            printf("Weight taken: %4d | Value added: %6.2f | 100%%\n", w, (double)v);
        } else {
            // Take fractional item to fill remaining capacity
            double fraction = (double)capacity / w;
            double fraction_val = v * fraction;
            total_value += fraction_val;
            printf("Weight taken: %4d | Value added: %6.2f | %.1f%%\n", capacity, fraction_val, fraction * 100);
            capacity = 0;
        }
    }
    return total_value;
}

int main() {
    // --- Main Program ---
    // Inputs: values, weights, and total knapsack capacity
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;

    cout << "Knapsack Capacity: " << capacity << endl;
    cout << "Values : "; print_list(values); cout << endl;
    cout << "Weights: "; print_list(weights); cout << "\n" << endl;

    double max_profit = fractional_knapsack(values, weights, capacity);

    cout << string(45, '-') << endl;
    printf("Maximum Value / Profit: %.2f\n", max_profit);
    cout << "Time Complexity : O(n log n)" << endl;
    cout << "Space Complexity: O(1) auxiliary" << endl;
    return 0;
}

/*
ALGORITHM: Fractional Knapsack (Greedy Method)

1. Start.
2. Input the values[], weights[] of n items and the knapsack capacity W.
3. For every item calculate the ratio = value / weight.
4. Sort the items in decreasing order of ratio.
5. Set total_value = 0.
6. For each item in the sorted order:
     a. If the remaining capacity is 0, stop the loop.
     b. If weight <= remaining capacity:
          - take the whole item,
          - capacity = capacity - weight,
          - total_value = total_value + value.
     c. Otherwise (the item does not fit completely):
          - fraction = remaining capacity / weight,
          - total_value = total_value + value * fraction,
          - capacity = 0 (the knapsack is now full).
7. Display the maximum value (total_value).
8. Stop.

Time Complexity : O(n log n)   (dominated by sorting)
Space Complexity: O(1) auxiliary
*/


// Time Complexity : O(N)
// Space Complexity : O(1)
