class Solution {
public:
    int mySqrt(int x) {
        // handle 0, 1 cases
        if (x < 2)
            return x;

        int a = 0;
        int b = min(x, 46341);
        int root, div;

        while (a < b - 1) {
            root = (a + b) / 2;
            // cout << "a " << a << " b " << b << " root " << root << endl;

            // computing root * root won't overflow since
            // root is always bound < 46341
            if (root * root > x)
                b = root;
            else
                a = root;
        }

        // a is now floor(sqrt(x))
        return a;
    }
};

// NOTE: an alternative and even faster implementation is based
//       on Newton-Raphson.
//
//       Start with
//           y_0 = 2^(bitlen/2)
//       And iterate till convergence (with integer arithmetic).
//           y_{n+1} = (y_n + n / y_n) /2
