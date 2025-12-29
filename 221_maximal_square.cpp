class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        size_t w = matrix[0].size();
        size_t h = matrix.size();

        uint max_edge = 0;
        vector<vector<uint>> m(h, vector<uint>(w));

        // NOTE: it's possible to optimize space complexity to O(w)
        //       by only storing the previous row.
        //       This would also improve cache locality and speed.

        for (size_t i = 0; i < h; ++i) {
            m[i][0] = matrix[i][0] - '0';
            max_edge = max(max_edge, m[i][0]);
        }

        for (size_t j = 0; j < w; ++j) {
            m[0][j] = matrix[0][j] - '0';
            max_edge = max(max_edge, m[0][j]);
        }

        for (size_t i = 1; i < h; ++i) {
            for (size_t j = 1; j < w; ++j) {      

                if (matrix[i][j] == '0') {
                    m[i][j] = 0;

                } else {
                    uint a = m[i][j - 1];      // left block
                    uint b = m[i - 1][j - 1];  // left-upper block
                    uint c = m[i - 1][j];      // upper block

                    m[i][j] = min({a, b, c}) + 1;
                    max_edge = max(max_edge, m[i][j]);
                }
            }
        }

        return max_edge * max_edge;
    }
};
