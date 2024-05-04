#include <iostream>

// КОДИРОВАНИЕ ХЕММИНГА

/**
В первой строке ввода подается число строк t, дальше t закодированных бинарных строк

Выводятся t декодированных строк
 */

int CeiledLog2(int a) {
    auto b = static_cast<float>(a);
    int result = (*reinterpret_cast<int*>(&b) >> 23) - 127; // evil pointer hack
    if (a == 1 << result) {
        return result;
    }
    return result + 1;
}

bool IsPowerOfTwo(int a) {
    auto b = static_cast<float>(a);
    a = *reinterpret_cast<int*>(&b);
    return (a & ((1 << 23) - 1)) == 0;
}

std::string decode(std::string s) {
    int length = s.size();
    int control_bits = CeiledLog2(length + 1);

    int real_control_bitset[control_bits];
    int control_bitset[control_bits];
    for (int i = 0; i < control_bits; i++) {
        real_control_bitset[i] = 0;
        control_bitset[i] = 0;
    }

    for (int i = 1; i < length + 1; i++) {
        char ch = s[i - 1];
        if (ch == '0') {
            continue;
        }

        if (IsPowerOfTwo(i)) {
            real_control_bitset[CeiledLog2(i)] = 1;
            continue;
        }
        int j = i;
        int counter = 0;
        while (j > 0) {
            int v = j & 1;
            if (v) {
                control_bitset[counter] ^= 1;
            }
            counter++;
            j >>= 1;
        }
    }

    int error_bit = 0;

    for (int i = control_bits - 1; i > -1; i--) {
        error_bit <<= 1;
        error_bit += real_control_bitset[i] ^ control_bitset[i];
    }
    std::string decoded_string;

    for (int i = 1; i < length + 1; i++) {
        char ch = s[i - 1];

        if (IsPowerOfTwo(i)) {
            continue;
        }
        if (i == error_bit) {
            ch = ch == '1' ? '0' : '1';
        }
        decoded_string += ch;
    }

    return decoded_string;
}

int main() {
    int t;
    std::cin >> t;
    std::string s;

    for (int i = 0; i < t; i++) {
        std::cin >> s;
        std::cout << decode(s) << '\n';
    }
    return 0;
}
