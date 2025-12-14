class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t len = prices.size();

        if (len < 2)
            return 0;

        vector<int> best_left(len);
        vector<int> best_right(len);
        
        int min_price = prices[0];

        for (size_t i = 1; i < len; ++i) {
            best_left[i] = max(
                best_left[i - 1],
                prices[i] - min_price 
            );
            min_price = min(min_price, prices[i]);
        }

        int max_price = prices[len - 1];

        for (size_t i = len - 2; i != (size_t)-1; --i) {
            best_right[i] = max(
                best_right[i + 1],
                max_price - prices[i]
            );
            max_price = max(max_price, prices[i]);
        }

        int max_return = 0;

        for (size_t i = 0; i < len; ++i) {
            int ret = best_left[i] + best_right[i];
            max_return = std::max(max_return, ret);
        }

        return max_return;            
    }
};
