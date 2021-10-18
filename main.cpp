#include <iostream>

#include "RegexParser.h"

int main() {
  std::string input;
  char target_char;

  std::cout << "Input regular expression:" << std::endl;
  std::getline(std::cin, input);

  std::cout << "Input target symbol:" << std::endl;
  std::cin >> target_char;

  long long answer = RegexParser(input).MaxPrefixOfSymbols(target_char);

  std::cout << ((answer >= std::numeric_limits<int>::max())
                    ? "INF"
                    : std::to_string(answer))
            << std::endl;

  return 0;
}
