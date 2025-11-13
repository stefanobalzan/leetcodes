class Solution {
public:
    int hammingWeight(int n) {
        int weight = 0;

        while (n != 0) {
            weight += n % 2;
            n = n / 2;
        }
        
        return weight;
    }
};
