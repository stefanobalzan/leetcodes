class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        size_t h = obstacleGrid.size();
        size_t w = obstacleGrid[0].size();

        // DP matrix
        // NOTE: space be optimized to O(w) since only the result
        //       for the previous row is required
        vector<vector<uint>> paths(h, vector<uint>(w));

        // initialize DP matrix 
        paths[0][0] = (obstacleGrid[0][0] == 0) ? 1 : 0;

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                // skip cell [0][0] - already initialized
                if (i == 0 && j == 0) {
                    continue;
                }

                if (obstacleGrid[i][j] == 1) {
                    paths[i][j] = 0;
                } else {
                    uint top = (i > 0) ? paths[i - 1][j] : 0;
                    uint left = (j > 0) ? paths[i][j - 1] : 0;
                    paths[i][j] = top + left;
                }
            }
        }

        // print obstacle grid and paths count grid (DP matrix)
        // printGrid(obstacleGrid);
        // cout << endl;
        // printGrid(paths);

        return paths[h - 1][w - 1];
    }

    template<typename T>
    void printGrid(vector<vector<T>>& grid) {
        size_t h = grid.size();
        size_t w = grid[0].size();

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};
