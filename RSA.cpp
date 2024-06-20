#include <iostream>
#include <random>
#include <cmath>
#include <vector>

using namespace std;

bool is_prime(long n) { // Check prime value
    if (n <= 1) return false;
 
    for (long i = 2; i <= n / 2; i++)
        if (n % i == 0) return false;
 
    return true;
}

long gcd(long a, long b) { // Find greatest common divisor
    while (b != 0) {
        long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

long mod_power(long a, long b, long n) { // Modular exponentiation
    long r = 1;
    while (b > 0) {
        if (b % 2 == 1) r = (r * a) % n;
        b >>= 1;
        a = (a * a) % n;
    }
    return r;
}

vector<long> rsa_setup(long p, long q) { // RSA key generation
    long n = p * q, phi = (p - 1) * (q - 1);
    long e = 2;
    while (gcd(e, phi) != 1) e++;

    long k = 1;
    while (((k*phi) + 1) * 1.0 / e != ((k*phi) + 1) / e) k++;

    long private_key = ((k*phi) + 1) / e;
    vector<long> res{n, e, private_key};
    return res;
}

long encrypt(long n, long e, long message) { // RSA encryption
    return mod_power(message, e, n);
}

long decrypt(long n, long d, long encrypted_message) { // RSA decryption
    return mod_power(encrypted_message, d, n);
}

int main() {
    // Small prime numbers
    vector<long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
    101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
    229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367,
    373, 379, 383, 389, 397, 401};

    long trials = 10, count = 0;
    for (long i = 0; i < trials; ++i) {
        long idx1 = rand() % primes.size();
        long idx2 = rand() % primes.size();
        while (idx1 == idx2) idx2 = rand() % primes.size();
        long p = primes[idx1];
        long q = primes[idx2];

        vector<long> temp = rsa_setup(p, q);
        long n = temp[0], e = temp[1], d = temp[2];

        cout << "Value p = " << p << " and q = " << q << endl;
        cout << "Public key e = " << e << endl;
        cout << "Private key d = " << d << endl;

        long message = rand() % n; // Plaintext (0 to n-1)
        long en = encrypt(n, e, message); // Ciphertext

        cout << "Plaintext M: " << message << endl;
        cout << "Ciphertext C: " << en << endl;

        if (message != decrypt(n, d, en)) {
            cout << "Error for p=" << p << " q=" << q << endl;
            count++;
        }
        else cout << "Correct!" << endl;
        cout << "------------------------------" << endl;
    }

    cout << "Error rate: " << long(count * 100.0 / trials) << "%" << endl;

    return 0;
}
