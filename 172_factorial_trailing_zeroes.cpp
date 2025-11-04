class Solution {
public:
    int trailingZeroes(int n) {
        // Counting trailing zeroes means counting the factors of 10.
        // That means counting 2s and 5s across all the factors 1 ... N
        // and considering min(count_2, count_5).
        // In factorials however count_5 <= count_2, there are always more 2s.
        // Counting 5s is enough to answer the problem.
        
        // A log(N) solution to compute the total number of 5s across all
        // factors 1 ... N is the following:
        //    N // 5.      -> number of factors multiple of 5 (contributing one 5 each)
        //    N // (5^2)   -> number of factors multiple of 25 (contribuiting one more 5 each)
        //    N // (5^3)   -> ...

        int i = 5;
        int factors = 0;

        while (i <= n) {
            factors += n / i;
            i = i * 5;
        }

        return factors;

    }
};
