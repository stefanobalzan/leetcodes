class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        
        if (len == 1)
            return nums[0];
    
        if (len == 2)
            return nums[0] > nums[1] ? nums[0] : nums[1]; 
        
        int total_1 = nums[1];
        int total_2 = nums[0];
        // total_1: best total up to the previous hosue (i - 1)
        //          the (i - 1) house is considered if beneficial
        // total_2: best total up to the previous-previous house (i - 2)

        for (int i = 2; i < len; ++i) {
            if (total_2 + nums[i] > total_1) {
                int temp = total_1;
                total_1 = total_2 + nums[i];
                total_2 = max(temp, total_2);
            } else {
                total_2 = max(total_1, total_2);
            }
        }
        // the max(total_1, total_2) operations are there to preserve
        // the optimal total up to i - 2 step.
        // it is necessary to properly propagate forward the best total_2
        // value and not just the one computed last

        return total_1;
    }
};

// NOTE: this solution is logically correct and follows dynamic programming
//       principles, however the canonical solution is the following:
//
//
//    int rob(vector<int>& nums) {
//        int n = nums.size();
//        if (n == 1) return nums[0];
//
//        int prev2 = 0;         // dp[i-2]
//        int prev1 = 0;         // dp[i-1]
//        for (int num : nums) {
//            int curr = max(prev1, prev2 + num);
//            prev2 = prev1;
//            prev1 = curr;
//        }
//        return prev1;
//    }
//
//
// This solution minimizes the number of state variables and operations
// and clearly exposes the recurring nature of the DP problem:
//
//    dp[i] = max(dp[i-1], dp[i-2] + nums[i])
