class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        size_t s_len = s.size();
        
        // optimizing, since vector is constant 
        std::vector<string>::iterator wordDictBegin = wordDict.begin();
        std::vector<string>::iterator wordDictEnd = wordDict.end();
        
        // lookup table for tested substrings (memoization)
        vector<bool> tested_substr(s_len, false);
        
        // stack to keep track of {substring start, wordDict iterator}
        // for each of the previous steps
        // this avoids recursion and all the issues that come with it
        stack<pair<size_t, std::vector<string>::iterator>> search_idxs;

        size_t start_idx = 0;
        auto it = wordDictBegin;
        int word_len;

        // each outer iteration either:
        // "pushes a match" into the stack and moves to the shorter sub-string
        // OR
        // "pulls the previous step" from the stack and resume the matching
        // 
        // it stops when start_idx == s_len (entire string matched)
        while(start_idx != s_len) {

            // cout << "start_idx: " << start_idx << endl;
            // cout << "s: " << s.substr(start_idx) << endl;

            // if the substring has already been tested, no need to test again
            // pop from the stack and test other words at the previous step 
            if (tested_substr[start_idx]) {
                tie(start_idx, it) = search_idxs.top();
                search_idxs.pop();
                continue;
            }

            // test all the dictionary words against the beginning
            // of the sub-string
            while (it != wordDictEnd) {
                string word = *it;
                // cout << "w: " << word << endl;

                word_len = word.size();
                bool match = (s.compare(start_idx, word_len, word) == 0);
                if (match) {
                    // cout << "MATCH!" << endl;
                    break;
                }
                
                ++it;
            }

            // if no match is found, go back to the previous step and continue
            // iterating on word dictionary from where it left
            if (it == wordDictEnd) {
                // exit condition: all dict words tested on the entire string
                if (start_idx == 0)
                    return false;
                
                // memoize tested substring
                tested_substr[start_idx] = true;

                // pop from the stack 
                // go back and resume testing dict words at the prev step
                tie(start_idx, it) = search_idxs.top();
                search_idxs.pop();
            
            // if a match is found, push the substring (start index) and
            // the iterator into the stack and repeat the process with the
            // new substring
            } else {
                search_idxs.push({start_idx, ++it});
                start_idx += word_len;
                it = wordDictBegin;
            }
        }

        return true;
    }
};
