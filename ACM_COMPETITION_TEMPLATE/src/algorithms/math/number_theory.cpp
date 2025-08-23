#include <iostream>
#include <vector>
#include <algorithm>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the least common multiple (LCM) of two numbers
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Function to generate all prime numbers up to a given limit using the Sieve of Eratosthenes
std::vector<int> sieveOfEratosthenes(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    std::vector<int> primes;
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime numbers

    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

// Example usage
int main() {
    int num = 29;
    std::cout << num << " is " << (isPrime(num) ? "prime" : "not prime") << std::endl;

    int a = 12, b = 15;
    std::cout << "GCD of " << a << " and " << b << " is " << gcd(a, b) << std::endl;
    std::cout << "LCM of " << a << " and " << b << " is " << lcm(a, b) << std::endl;

    int limit = 50;
    std::vector<int> primes = sieveOfEratosthenes(limit);
    std::cout << "Primes up to " << limit << ": ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}