// NOTE: this file offers two solutions to the problem:
//       - maxProfit()
//           space efficient (optimized)
//       - maxProfitPartialArray()
//           storing the full vector of partial solutions for each day
//           (useful for printing and studying the anglorightm)

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        size_t days = prices.size();

        if (days < 2)
            return 0;

        // profits[j][h]
        // 2D vectors representing the best profit
        // - with j completed trades
        // - and not holding/holding (0 / 1) a position
        // one for profit at time t and one for (t - 1)
        vector<array<int, 2>> p(k + 1);
        vector<array<int, 2>> p_prev(k + 1);        

        // sentinel value for impossible solutions
        // IMPOSSIBLE ~= -1e9
        // even under the worst case scenario it won't interfere
        // with valid solutions (k <= 100 and prices[i] <= 1000)
        // this minimizes the number of branches 
        const int IMPOSSIBLE = INT_MIN / 2;

        p_prev[0] = {0, -prices[0]};

        for (int j = 1; j < k + 1; ++j) {
            p_prev[j] = {IMPOSSIBLE, IMPOSSIBLE};
        }

        for (int t = 1; t < days; ++t) {
            int price = prices[t];

            // initialize profits[t][0]
            p[0][0] = 0;
            p[0][1] = max(p_prev[0][1], -price);

            for (int j = 1; j < k + 1; ++j) {
                // not holding, j completed transactions
                // can come from either:
                //   - profits[t-1][j][0]     (no change)
                //   - profits[t-1][j-1][1]   (was holding, selling now)

                // picking the path that maximise the profit
                int max_profit = max(
                    p_prev[j][0],
                    p_prev[j - 1][1] + price
                );
                p[j][0] = max_profit;
                
                // holding, j completed transactions (excluding holding one)
                // can come from either:
                //   - profits[t-1][j][1]     (no change, keep holding)
                //   - profits[t-1][j][0]     (was not holding, buying now)
                max_profit = max(
                    p_prev[j][1],
                    p_prev[j][0] - price
                );
                p[j][1] = max_profit;
            }

            // p becomes p_prev for the following day
            swap(p, p_prev);
        }

        int max_profit = 0;
        for (int j = 0; j < k + 1; ++j) {
            max_profit = max(max_profit, p_prev[j][0]);
        }
        
        return max_profit;
    }

    int maxProfitPartialArray(int k, vector<int>& prices) {
        size_t days = prices.size();

        if (days < 2)
            return 0;

        // profits[t][j][h]
        // 3D vector representing the best profit
        // - up to day t
        // - with j completed trades
        // - and not holding/holding (0 / 1) a position
        vector<vector<array<int, 2>>> profits(
            days,
            vector<array<int, 2>> (k + 1)
        );

        // sentinel value for impossible solutions
        // IMPOSSIBLE ~= -1e9
        // even under the worst case scenario it won't interfere
        // with valid solutions (k <= 100 and prices[i] <= 1000)
        // this minimizes the number of branches 
        const int IMPOSSIBLE = INT_MIN / 2;

        profits[0][0] = {0, -prices[0]};

        for (int j = 1; j < k + 1; ++j) {
            profits[0][j] = {IMPOSSIBLE, IMPOSSIBLE};
        }

        for (int t = 1; t < days; ++t) {
            int price = prices[t];

            // initialize profits[t][0]
            profits[t][0][0] = 0;
            profits[t][0][1] = max(profits[t - 1][0][1], -price);

            for (int j = 1; j < k + 1; ++j) {
                // not holding, j completed transactions
                // can come from either:
                //   - profits[t-1][j][0]     (no change)
                //   - profits[t-1][j-1][1]   (was holding, selling now)

                // picking the path that maximise the profit
                int max_profit = max(
                    profits[t - 1][j][0],
                    profits[t - 1][j - 1][1] + price
                );
                profits[t][j][0] = max_profit;
                
                // holding, j completed transactions (excluding holding one)
                // can come from either:
                //   - profits[t-1][j][1]     (no change, keep holding)
                //   - profits[t-1][j][0]     (was not holding, buying now)
                max_profit = max(
                    profits[t - 1][j][1],
                    profits[t - 1][j][0] - price
                );
                profits[t][j][1] = max_profit;
            }
        }

        // enable to visualize the partial DP solutions
        // printProfits(profits);

        int max_profit = 0;
        for (int j = 0; j < k + 1; ++j) {
            max_profit = max(max_profit, profits[days - 1][j][0]);
        }
        
        return max_profit;
    }


    void printProfits(const vector<vector<array<int, 2>>>& profits) {
        const int IMPOSSIBLE = INT_MIN / 2;
        int days = profits.size();
        int k = profits[0].size() - 1;
        
        cout << "DP Table (not_holding / holding, X = impossible)\n\n";
        
        // header
        cout << "Day |";
        for (int j = 0; j <= k; ++j) {
            cout << " Trans=" << j << "      |";
        }
        cout << "\n";
        
        // separator
        cout << "----|";
        for (int j = 0; j <= k; ++j) {
            cout << "--------------|";
        }
        cout << "\n";
        
        // helper function to format a value
        auto formatVal = [&](int val) -> string {
            if (val <= IMPOSSIBLE / 2) {
                return "X";
            }
            return (val >= 0 ? " " : "") + to_string(val);
        };
        
        // rows
        for (int t = 0; t < days; ++t) {
            printf("%3d |", t);
            
            for (int j = 0; j <= k; ++j) {
                string notHolding = formatVal(profits[t][j][0]);
                string holding = formatVal(profits[t][j][1]);
                
                printf(" %4s / %-4s  |", notHolding.c_str(), holding.c_str());
            }
            printf("\n");
        }
        cout << "\n";
    }
};
