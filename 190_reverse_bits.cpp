class Solution {
public:
    std::string bitsToString(unsigned int n, unsigned int blk) {
        std::string s;
        s.reserve(32 + n / blk); // 32 bits + spacing

        for (int i = 31; i >= 0; --i) {
            s.push_back(((n >> i) & 1) ? '1' : '0');
            if (i % blk == 0 && i != 0) s.push_back(' ');
        }

        return s;
    }

    int reverseBits(int n) {
        // The strategy consists in a divide-et-impera approach, where smaller
        // blocks are swapped recursively (16 bits, then 8bits, ...).
        //     
        //   n = ((n & mask) << mask_width) | ((n & ~mask) >> mask_width)
        //
        // EXAMPLE: (1 byte width for simplicity)
        //     1010 0110 - input
        //     0110 1010 - 4 bit mask
        //     1001 1010 - 2 bit mask
        //     0110 0101 - 1 bit mask
        //
        // NOTE: this solution implements the reversal completely in software.
        //       On some architectures it might be possible to perform the
        //       same in hardware.
        //       If speed is of extreme concern, a strategy based on an 8 bits
        //       or 16 bits lookup table works better. It comes of course at
        //       the expense of memory (256 B - 1 KB for 8 bits vs 128 KB - 
        //       256 KB for 16 bits)

        int x = static_cast<unsigned int>(n);

        x = x << 16 | x >> 16;
        x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
        x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
        x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
        x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);

        return x;

        // To visualize the bit representation
        // cout << "step i: " << bitsToString(x, 4) << endl;
    }
};
