#ifndef H_RATIONAL
#define H_RATIONAL
#include <iostream>
#include <numeric>
#include <stdexcept>

void Reduce(int64_t& p, int64_t& q);

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};
class Rational {
 private:
  int64_t p_ = 0;
  int64_t q_ = 1;

 public:
  Rational();
  Rational(int64_t p, int64_t q);  // NOLINT
  Rational(int64_t p);             // NOLINT
  Rational(const Rational& r);
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational& operator=(const Rational& other);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int64_t val);
  void SetDenominator(int64_t val);
};
std::ostream& operator<<(std::ostream& ost, const Rational& val);
std::istream& operator>>(std::istream& ist, Rational& val);
Rational operator+(Rational a);
Rational operator-(Rational a);
Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);
Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);
bool operator<(const Rational& first, const Rational& other);
bool operator>(const Rational& first, const Rational& other);
bool operator==(const Rational& first, const Rational& other);
bool operator!=(const Rational& first, const Rational& other);
bool operator<=(const Rational& first, const Rational& other);
bool operator>=(const Rational& first, const Rational& other);
#endif
