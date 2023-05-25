#include <iostream>
#include <string>
#include <vector>

std::vector<int> ZFunction(std::string& str){
  int str_len = str.size();
  std::vector<int> z(str_len, 0);
  z[0] = str_len;
  int left = 0, right = 0;

  for (int i = 1; i < str_len; ++i) {

    if (i <= right) {
    z[i] = std::min(z[i - left], right - i);
    }
    
    while (i + z[i] < str_len && str[z[i]] == str[z[i] + i]) {
      z[i]++;
    }

    if (right < i  + z[i]) {
    right = i + z[i];
    left = i;
    }
  }

  return z;
}

int main() {
  std::string str_in; 
  std::cin >> str_in;
  for (auto i: ZFunction(str_in)) {
    std::cout << i << " ";
  }
}
