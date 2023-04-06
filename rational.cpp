#include "rational.h"

void Reduce(int64_t& p, int64_t& q) {
  int64_t gcd = std::gcd(p, q);
  p /= gcd;
  q /= gcd;
  if (q < 0) {
    p = -p;
    q = -q;
  }
}
Rational::Rational() = default;

Rational::Rational(int64_t p, int64_t q) {  // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero();
  }
  p_ = p;
  q_ = q;
  Reduce(p_, q_);
}

Rational::Rational(int64_t p) {  // NOLINT
  p_ = p;
  q_ = 1;
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

Rational& Rational::operator+=(const Rational& other) {
  p_ = p_ * other.q_ + q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce(p_, q_);
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce(p_, q_);
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = q_ * other.q_;
  Reduce(p_, q_);
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.p_ == 0) {
    throw RationalDivisionByZero();
  }
  p_ = p_ * other.q_;
  q_ = q_ * other.p_;
  Reduce(p_, q_);
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int64_t val) {
  p_ = val;
  Reduce(p_, q_);
}

void Rational::SetDenominator(int64_t val) {
  if (val == 0) {
    throw RationalDivisionByZero();
  }
  q_ = val;
  Reduce(p_, q_);
}

Rational& Rational::operator=(const Rational& other) {
  if (this != &other) {
    p_ = other.p_;
    q_ = other.q_;
  }
  return *this;
}

Rational operator+(Rational a) {
  return a;
}

Rational operator-(Rational a) {
  a.SetNumerator(-a.GetNumerator());
  return a;
}

Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  if (other.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }
  Rational copy = first;
  copy /= other;
  return copy;
}

std::ostream& operator<<(std::ostream& ost, const Rational& val) {
  if (val.GetDenominator() == 1) {
    ost << val.GetNumerator();
  } else {
    ost << val.GetNumerator() << '/' << val.GetDenominator();
  }
  return ost;
}

std::istream& operator>>(std::istream& ist, Rational& val) {
  char rational_in[100]{'\0'};
  int64_t p = 0, q = 0;
  ist >> rational_in;
  bool p_minus = false, q_minus = false, slash_exist = false;
  int curr = 0;
  while (rational_in[curr] != '\0') {
    if (rational_in[curr] == '+') {
      ++curr;
    }
    if (rational_in[curr] == '/') {
      slash_exist = true;
    } else if (rational_in[curr] == '-') {
      if (slash_exist) {
        q_minus = true;
      } else {
        p_minus = true;
      }
    } else if (slash_exist) {
      q *= 10;
      q += rational_in[curr] - '0';
    } else {
      p *= 10;
      p += rational_in[curr] - '0';
    }
    ++curr;
  }
  p = (p_minus ? -p : p);
  q = (q_minus ? -q : q);
  val.SetNumerator(p);
  if (slash_exist) {
    val.SetDenominator(q);
  }
  return ist;
}
bool operator<(const Rational& first, const Rational& other) {
  return (first.GetNumerator() * other.GetDenominator() < first.GetDenominator() * other.GetNumerator());
}

bool operator>(const Rational& first, const Rational& other) {
  return other < first;
}

bool operator==(const Rational& first, const Rational& other) {
  return !(first < other) && !(other < first);
}

bool operator!=(const Rational& first, const Rational& other) {
  return !(first == other);
}

bool operator<=(const Rational& first, const Rational& other) {
  return !(first > other);
}

bool operator>=(const Rational& first, const Rational& other) {
  return !(first < other);
}