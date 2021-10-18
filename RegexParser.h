#pragma once

#include <string>
#include <unordered_set>
#include <utility>

class RegexParser {
 public:
  RegexParser(std::string s,
              std::unordered_set<char> alphabet = {'a', 'b', 'c'})
      : s(std::move(s)), alphabet(std::move(alphabet)){};

  long long MaxPrefixOfSymbols(char target_char);

 private:
  std::string s;
  std::unordered_set<char> alphabet;
};

std::string MakeExceptionMessage(std::string message,
                                 const std::string& invalid_argument, size_t i);