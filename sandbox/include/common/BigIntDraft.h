// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPP_TRAINING_BIGINT_H
#define CPP_TRAINING_BIGINT_H

class BigInt {
  public:
    using Sign = int8_t;

    /*
    using DigitType = uint32_t;
    using BiggerDigit = uint64_t;
    */

    using DigitType = uint8_t;
    using BiggerDigit = uint16_t;

    using Internal = std::vector<DigitType>;

    static const DigitWidth;
    static const BiggerDigit maxDigit;

    struct Digit {
        Digit(DigitType digit) : digit(digit) {}

        std::pair<Digit, Digit> operator+(Digit bd) {
            BiggerDigit result = static_cast<BiggerDigit>(digit) +
                                 static_cast<BiggerDigit>(bd.digit);
            return {static_cast<Digit>(result % maxDigit),
                    static_cast<Digit>(result / maxDigit)};
        }

        std::pair<Digit, Digit> operator*(Digit bd) {
            BiggerDigit result = static_cast<BiggerDigit>(digit) *
                                 static_cast<BiggerDigit>(bd.digit);
            return {static_cast<Digit>(result % maxDigit),
                    static_cast<Digit>(result / maxDigit)};
        }

        std::pair<Digit, Digit> operator-(Digit bd) {
            DigitType digitTemp = digit;
            DigitType underflow = 0;
            if (digit < bd.digit) {
                digitTemp += maxDigit;
                underflow = 1;
            }
            BiggerDigit result = static_cast<BiggerDigit>(digitTemp) -
                                 static_cast<BiggerDigit>(bd.digit);
            return {static_cast<Digit>(result % maxDigit),
                    static_cast<Digit>(underflow)};
        }

        DigitType digit;
    };

    BigInt(Internal &&internal, Sign sign) : internal(std::move(internal)), sign(sign) {}

    BigInt(std::string& s) {}

    BigInt(uint64_t uint64, sign = 1) : sign(sign) {
        auto num = uint64;
        while (num > 0) {
            internal.push_back(num % maxdigit);
            num /= maxDigit;
        }
    }

    BigInt(int64_t int64) {
        if (int64 >= 0) {
            BigInt tmp(static_cast<uint64_t>(int64));
            std::swap(tmp, *this);
        } else {
            BigInt tmp(static_cast<uint64_t>(-int64), -1);
            std::swap(tmp, *this);
        }
    }

    void flip(void) { sign *= -1; }

    void operator<<(unsigned int shift) {
        if (shift) {
            Internal ret(internal.size() + shift, 0);
            std::copy(internal.begin(), internal.end(), ret.begin() + shift);
            std::swap(internal, shift);
        }
    }

    void operator>>(unsigned int shift) {
        if (shift) {
            Internal ret(internal.size() + shift, 0);
            std::copy(internal.begin(), internal.end(), ret.begin() + shift);
            std::swap(internal, shift);
        }
    }

    Digit get(Internal internal, int index) {
        if (index >= internal.size()) {
            return 0;
        } else {
            return internal[index];
        }
    }

    BigInt operator+(BigInt& bigInt) {
        if (bigInt.sign == -1){



        } else {
            Internal resInternal(internal);
            int i = 0;
            std::pair<Digit, Digit> res;
            while((i < internal.size()) || (i < bigInt.internal.size())) {
                res = get(internal, i) + get(bigInt.internal, i);
                res = ru

            }


    }
    BigInt operator/(BigInt& bigInt) { auto res = div_mod(bigInt); return res.first; }
    std::pair<BigInt, BigInt> div_mod(BigInt &bigInt) {

    }

  private:
    Internal internal;
    Sign sign;
};

unsigned int BigInt::digitWidth = sizeof(DigitType);
BiggerDigit BigInt::maxDigit = static_cast<BiggerDigit>(static_cast<BigDigit>(-1) + 1U);

std::ostream& operator<<(std::ostream& os, const BigInt& bigInt) {
    if (sign == -1) {
        os << "-";
    }
}

#endif  // CPP_TRAINING_BIGINT_H
