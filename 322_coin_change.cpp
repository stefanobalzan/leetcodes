class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // memoized solutions (0 .. amount)
        int coins_count[10001] = {0};

        for (int i = 1; i <= amount; ++i) {
            // using INT_MAX as sentinel value for "no solution" reduces the
            // number of branches in the inner loop
            // INT_MAX behaves nicely with std::min and there's no risk of
            // overflow, give amount <= 10_000
            int min_count = INT_MAX;

            for (int coin : coins) {
                if (i >= coin) {
                    int previous_count = coins_count[i - coin];
                    min_count = min(min_count, previous_count);
                }
            }

            coins_count[i] = min_count != INT_MAX ? min_count + 1 : INT_MAX;
        }

        // converting the sentinel value and returning the solution
        int change = coins_count[amount];
        return change != INT_MAX ? change : -1;       
    }
};
