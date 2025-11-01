class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        size_t len = points.size();
        unsigned int max_count = 0;

        // len = 0 -> no points
        // len = 1 -> one point (infinite lines)
        if (len < 2) {
            return len;
        }

        for (int i = 0; i < len; ++i) {
            int x_1 = points[i][0];
            int y_1 = points[i][1];

            // pre-allocate a hash map for (n - 1) potential lines
            // taking i-th point as a reference, the lines through
            // i-th point and all the other j-th points (j != i) are
            // identified by the slope m = p / q.
            // The slope can be represented exactly with a (int, int) pair
            // and given the constraints on the coordinates, p and q can be 
            // combined into one single 32bit unsigned int32 that can be
            // used as a unique key.
            unordered_map<uint32_t, unsigned int> line_counts(len - 1);

            for (int j = 0; j < len; ++j) {
                if (j == i) continue;

                int x_2 = points[j][0];
                int y_2 = points[j][1];

                // compute p and q
                int p = y_2 - y_1;
                int q = x_2 - x_1;

                // reduce p and q and handle sign
                int m_gcd = gcd(p, q);
                if (q < 0) {p = -p; q = -q;}
                p = p / m_gcd;
                q = q / m_gcd;

                int key = ((uint32_t)p << 16) + (uint32_t)q;
                ++line_counts[key];
            }

            for (auto item : line_counts)
                // adding one to the count since i-th point was never considered
                max_count = max(max_count, item.second + 1);
        }

        return max_count;
    }
};
