// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_SIEVE_H
#define PROJECT_SIEVE_H

#include <cmath>
#include <vector>

namespace dataStructure {

    class Sieve {
      public:
        Sieve(unsigned int range) : sieve(range+1U, true), primesInRange(range+1U, 0) {
            sieve[0] = false;
            sieve[1] = false;
            for (unsigned int k = 2U; k <= std::sqrt(range); k++) {
                if (sieve[k]) {
                    unsigned int kk = 2U * k;
                    while (kk <= range) {
                        sieve[kk] = false;
                        kk += k;
                    }
                }
            }
            for (unsigned int p = 1U; p < sieve.size(); p++) {
                primesInRange[p] = primesInRange[p - 1U];
                if (sieve[p]) {
                    primes.push_back(p);
                    primesInRange[p]++;
                }
            }
        }

        int countPrimesInRange(unsigned int k) { return primesInRange[k]; }
        bool isPrime(unsigned int k) { return sieve[k]; }

        const std::vector<unsigned int> &getPrimes(void) { return primes; }

      private:
        std::vector<bool> sieve;
        std::vector<unsigned int> primes;
        std::vector<unsigned int> primesInRange;
    };
}

#endif  // PROJECT_SIEVE_H
