#include <iostream> 
#include <string> 
#include <vector> 

std::vector<int> PrefixFunction(std::string& str) {
  int str_len = str.size();
  std::vector<int> prefix(str_len, 0);

  for (int i = 1; i < str_len; ++i) {
    int k = prefix[i - 1];

    while(k > 0 && str[k] != str[i]) {
      k = prefix[k - 1];
    }

    if (str[k] == str[i]) {
      prefix[i] = k + 1;
    }
  }

  return prefix;
}

int main() {
  std::string str_in;
  std::cin >> str_in;
  for (auto i: PrefixFunction(str_in)) {
    std::cout << i << " ";
  }
}
