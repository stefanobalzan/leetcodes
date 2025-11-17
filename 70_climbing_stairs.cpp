class Solution {
// Step N can be reached either with a single step or a double step
// therefore the possible distinct ways for N steps are:
//
//    climbStairs(N) = climbStairs(N - 1) + climbStairs(N - 2)
//    
// with
//    climbStairs(1) = 1
//    climbStairs(2) = 2
//
// This is effectively a fibonacci sequence.
//
// The proposed solution implements two important optimizations:
// 1. memoization to avoid redundant calculations
// 2. recursion elimination: avoids hitting stack overflows
//    (although the problem states n <= 45, it's not strictly required)
//
// In dynamic programming this approach is called bottom-up.

private:
    int paths[46] = {0, 1, 2};  // paths[n] = distinct paths to step n
    int max_step = 2;           // highest computed step

public:
    int climbStairs(int n) {
        if (max_step >= n)
            return paths[n];

        for (int step = max_step + 1; step <= n; ++step) {
            paths[step] = paths[step - 1] + paths[step - 2];
        }

        return paths[n];
    }
};
