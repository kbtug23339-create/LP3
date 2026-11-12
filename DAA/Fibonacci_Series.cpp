// Fibonacci Series using Iteration and Recursion
// Iteration :
// Time Complexity = O(N)
// Space Complexity : O(1)
// Recursion :
// Time Complexity : O(1.618^N)
// Space Complexity : O(N) due to Auxilliary Stack Space
// Time Complexity is derived using Binet's Formula
// Time Complexity = 1/root(5)*[(1+root(5)/2)^n-(1-root(5)/2)^n]


#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;   // exact up to F(93)

// 1. Recursive Method: F(n) = F(n-1) + F(n-2)
long long rec_count = 0;

ull fib_recursive(int n) {
    rec_count++;
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 2. Non-Recursive Method: Dynamic Programming (Bottom-Up)
vector<ull> fib_iterative(int n) {
    if (n == 0)
        return vector<ull>{0};
    vector<ull> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n < 0) {
        cout << "Enter a positive number." << endl;
    } else {

        // NON-RECURSIVE OUTPUT
        cout << "\n================================";
        cout << "\n NON-RECURSIVE METHOD (ITERATIVE)";
        cout << "\n================================\n";

        vector<ull> series = fib_iterative(n);

        cout << "Fibonacci Series: [";
        for (size_t i = 0; i < series.size(); i++) {
            if (i) cout << ", ";
            cout << series[i];
        }
        cout << "]" << endl;

        cout << "Fibonacci Number F(" << n << "): "
             << series[n] << endl;

        cout << "Time Complexity: O(n)" << endl;
        cout << "Space Complexity: O(n)" << endl;


        // RECURSIVE OUTPUT
        cout << "\n================================";
        cout << "\n RECURSIVE METHOD";
        cout << "\n================================\n";

        rec_count = 0;
        ull ans = fib_recursive(n);

        cout << "Fibonacci Number F(" << n << "): "
             << ans << endl;

        cout << "Recursive Calls: " << rec_count << endl;

        cout << "Time Complexity: O(2^n)" << endl;
        cout << "Space Complexity: O(n)" << endl;
    }

    return 0;
}

/*
ALGORITHM: Fibonacci Series

A) Recursive method
   1. Start.
   2. Read n.
   3. Define fib_recursive(n):
        a. If n <= 1, return n          (base case: F(0)=0, F(1)=1).
        b. Otherwise return fib_recursive(n-1) + fib_recursive(n-2).
   4. Call fib_recursive(n) and count the number of calls made.
   5. Display F(n) and the call count.
   Time Complexity : O(2^n)    Space Complexity : O(n) (call stack depth)

B) Non-recursive method (Dynamic Programming, bottom-up)
   1. Start.
   2. Read n. If n < 0, display an error and stop.
   3. If n = 0, the series is [0].
   4. Create an array dp[0..n]; set dp[0] = 0 and dp[1] = 1.
   5. For i = 2 to n:  dp[i] = dp[i-1] + dp[i-2].
   6. Display the array dp (the series) and dp[n] (the nth Fibonacci number).
   7. Stop.
   Time Complexity : O(n)      Space Complexity : O(n)
*/
