```cpp
#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}
```

```sh
@echo off
g++ "%~1" -std=c++17 -O2 -o sol.exe || exit /b 1
g++ "%~2" -std=c++17 -O2 -o std.exe || exit /b 1
g++ gen.cpp -std=c++17 -O2 -o gen.exe || exit /b 1

set /a t=0
:loop
    set /a t+=1
    gen.exe %t% > in.txt
    sol.exe < in.txt > out.txt
    std.exe < in.txt > ans.txt
    fc out.txt ans.txt > nul

    if not errorlevel 1 (
        echo [Test %t%] Accepted.
        goto loop
    )

    echo [Test %t%] WRONG ANSWER!
    echo ===== input =====
    type in.txt
    echo ===== my =====
    type out.txt
    echo ===== std =====
    type ans.txt
    pause
exit /b 0
```

```sh
# 1) 本地常用（有警告，便于发现问题）
g++ a.cpp -std=c++17 -O2 -Wall -Wextra -Wshadow -o a

# 2) 调试版（保留符号）
g++ a.cpp -std=c++17 -O0 -g -o a

# 3) 调试版 + STL 越界检查（GCC/libstdc++）
g++ a.cpp -std=c++17 -O0 -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -o a

# 4) ASan + UBSan 一起开（线下调 bug 很好用）
g++ a.cpp -std=c++17 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o a
```

```sh
# Windows (MinGW g++)：改可执行文件栈大小为 256MB
g++ a.cpp -std=c++17 -O2 -Wl,--stack,268435456 -o a.exe

# Linux：运行前调栈深（当前 shell 有效）
ulimit -s unlimited
./a
```
