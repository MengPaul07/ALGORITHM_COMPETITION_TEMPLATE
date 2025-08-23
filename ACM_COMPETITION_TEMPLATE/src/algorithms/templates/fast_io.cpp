#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

namespace fast_io {
    inline void read(int &x) {
        x = 0;
        int f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = getchar();
        }
        x *= f;
    }

    inline void write(int x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }

    inline void readString(char *str) {
        char ch = getchar();
        while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
        int index = 0;
        while (ch != ' ' && ch != '\n' && ch != '\r' && ch != EOF) {
            str[index++] = ch;
            ch = getchar();
        }
        str[index] = '\0';
    }

    inline void writeString(const char *str) {
        while (*str) {
            putchar(*str++);
        }
    }
}