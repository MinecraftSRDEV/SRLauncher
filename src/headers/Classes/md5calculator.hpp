class MD5 {
public:
    MD5() { init(); }

    // Funkcja przetwarzająca ciąg znaków
    std::string calculate(const std::string &input) {
        init();
        process(reinterpret_cast<const unsigned char*>(input.c_str()), input.size());
        finalize();
        return hexdigest();
    }

    // Funkcja przetwarzająca plik
    std::string calculateFromFile(const std::string &filename) {
        init();
        std::ifstream file(filename, std::ifstream::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        const size_t bufferSize = 1024;
        char buffer[bufferSize];

        while (file.good()) {
            file.read(buffer, bufferSize);
            process(reinterpret_cast<const unsigned char*>(buffer), file.gcount());
        }

        file.close();
        finalize();
        return hexdigest();
    }

private:
    static constexpr size_t blockSize = 64;  // 512-bitowe bloki
    unsigned int state[4];                   // Przechowuje A, B, C, D
    unsigned long long bitCount;             // Liczba przetworzonych bitów
    unsigned char buffer[blockSize];         // Bufor dla 64 bajtów
    bool finalized;

    // Tabela sinusów używana przez MD5
    static constexpr unsigned int T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453,  0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    void init() {
        finalized = false;
        bitCount = 0;

        // Inicjalizacja zmiennych MD5 (A, B, C, D)
        state[0] = 0x67452301;
        state[1] = 0xefcdab89;
        state[2] = 0x98badcfe;
        state[3] = 0x10325476;
    }

    void process(const unsigned char *data, size_t length) {
        size_t i = 0;

        // Przetwarzanie w blokach po 512 bitów (64 bajty)
        while (length--) {
            buffer[bitCount / 8 % blockSize] = data[i++];
            bitCount += 8;

            if (bitCount / 8 % blockSize == 0) {
                transform(buffer);
            }
        }
    }

    void finalize() {
        if (finalized) return;

        // Padding
        unsigned char padding[blockSize] = { 0x80 };
        size_t paddingLength = (bitCount / 8 % blockSize < 56) ? (56 - bitCount / 8 % blockSize) : (120 - bitCount / 8 % blockSize);
        process(padding, paddingLength);

        // Dodaj długość wiadomości
        unsigned long long bitCountTemp = bitCount;
        for (size_t i = 0; i < 8; ++i) {
            buffer[56 + i] = (bitCountTemp >> (i * 8)) & 0xff;
        }

        transform(buffer);
        finalized = true;
    }

    void transform(const unsigned char block[blockSize]) {
        unsigned int a = state[0], b = state[1], c = state[2], d = state[3], f, g;

        unsigned int x[16];
        for (int i = 0; i < 16; ++i) {
            x[i] = (block[i * 4 + 0]) |
                   (block[i * 4 + 1] << 8) |
                   (block[i * 4 + 2] << 16) |
                   (block[i * 4 + 3] << 24);
        }

        for (int i = 0; i < 64; ++i) {
            if (i < 16) {
                f = (b & c) | (~b & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | (~d & c);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            } else {
                f = c ^ (b | ~d);
                g = (7 * i) % 16;
            }

            unsigned int temp = d;
            d = c;
            c = b;
            b = b + leftRotate((a + f + T[i] + x[g]), shiftAmounts[i]);
            a = temp;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
    }

    // Rotacja bitów w lewo
    unsigned int leftRotate(unsigned int x, unsigned int n) {
        return (x << n) | (x >> (32 - n));
    }

    std::string hexdigest() {
        std::stringstream ss;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ss << std::hex << std::setw(2) << std::setfill('0') << ((state[i] >> (j * 8)) & 0xff);
            }
        }
        return ss.str();
    }

    static constexpr unsigned int shiftAmounts[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
};