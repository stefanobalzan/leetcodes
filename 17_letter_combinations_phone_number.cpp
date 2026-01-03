class Solution {
private:
    const array<string, 10> keys = {
        "",                    // 0 - (space)
        "",                    // 1 - (punctuation)
        "abc",                 // 2
        "def",                 // 3
        "ghi",                 // 4
        "jkl",                 // 5
        "mno",                 // 6
        "pqrs",                // 7
        "tuv",                 // 8
        "wxyz"                 // 9
    };

    void backtrack(
        int index,
        string& current,
        const string& digits,
        vector<string>& result
    ) {
    
    // if done, stop recursing and save the combination
    if (current.size() == digits.size()) {
        result.push_back(current);
        return;
    }

    int digit = digits[index] - '0';

    // explore each character associated to the i-th digit
    for (auto c : keys[digit]) {
        // update the combination string
        current = current + c;
        // recurse moving onto the next digit
        backtrack(index + 1, current, digits, result);
        // undo the choice (backtrack)
        current = current.substr(0, index);
    }
}

public:    
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        string current;

        // call recursive backtrack function starting at first digit
        backtrack(0, current, digits, result);

        return result;
    }
};
