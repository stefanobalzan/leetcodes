/*

NOTE: this is dynamic programming solution with O(n^2) time and space
      complexity. Acceptable given the problem constraints, but other
      solutions also exists:

    +---------------------------+------------------+------------------+
    | Solution                  | Time Complexity  | Space Complexity |
    +---------------------------+------------------+------------------+
    | Bruteforce                | O(n^3)           | O(1)             |
    +---------------------------+------------------+------------------+
    | DP (2D table)             | O(n^2)           | O(n^2)           |
    +---------------------------+------------------+------------------+
    | Expand-around-centers     | O(n^2)           | O(1)             |
    +---------------------------+------------------+------------------+
    | Manacher's Algorithm      | O(n)             | O(n)             |
    +---------------------------+------------------+------------------+
*/


class Solution {
public:
    string longestPalindrome(string s) {
        size_t len = s.size();

        vector<vector<bool>> palindromes(len, vector<bool>(len, false));
        array<size_t, 2> longest = {0, 1};

        // initialize 1-char solutions (always a palindrome)
        for (size_t i = 0; i < len; ++i) {
            palindromes[i][i] = true;
        }
        
        // initialize 2-char solutions
        for (size_t i = 0; i < len - 1; ++i) {
            if (s[i] == s[i + 1]) {
                palindromes[i][i + 1] = true;
                longest = {i, 2};
            }
        }

        // verify recursively all the strings from length 3 to len
        // using the DP matrix partial solutions
        for (size_t span = 2; span < len; ++span) {
            for (size_t i = 0; i < len - span; ++i) {
                  
                if (s[i] == s[i + span] && palindromes[i + 1][i + span - 1]) {
                    palindromes[i][i + span] = true;
                    longest = {i, span + 1};
                }

            }
        }

        return s.substr(longest[0], longest[1]);   
    }
};
