#include "RegexParser.h"

#include <deque>

long long RegexParser::MaxPrefixOfSymbols(char target_char) {
  struct DPState {
    long long max_prefix;

    /// -1 means that there is no full word of target chars
    long long max_full_word;

    DPState(char c, char target_c)
        : max_prefix(c == target_c), max_full_word(c == target_c ? 1 : -1) {
      if (c == '1') {
        max_full_word = 0;
      }
    };

    DPState& operator+=(const DPState& r) {
      max_prefix = std::max(max_prefix, r.max_prefix);
      max_full_word = std::max(max_full_word, r.max_full_word);
      return *this;
    }

    DPState& operator*=(const DPState& r) {
      if (max_full_word >= 0) {
        max_prefix = std::max(max_full_word + r.max_prefix, max_prefix);
      }
      if (r.max_full_word == -1) {
        max_full_word = -1;
      } else if (max_full_word >= 0) {
        max_full_word = max_full_word + r.max_full_word;
      }
      return *this;
    }

    DPState& operator*() {
      if (max_full_word >= 1) {
        max_full_word = std::numeric_limits<int>::max();
        max_prefix = max_full_word;
      } else {
        max_full_word = 0;
      }
      return *this;
    }
  };

  if(s.empty()) {
    throw std::invalid_argument("Invalid regular expression: empty");
  }

  if (alphabet.find(target_char) == alphabet.end()) {
    throw std::invalid_argument("Invalid target symbol '" +
                                std::string(1, target_char) + "'");
  }

  std::deque<DPState> dp;

  for (size_t i = 0; i < s.size(); ++i) {
    const auto& c = s[i];
    if (alphabet.find(c) != alphabet.end() || c == '1') {
      dp.emplace_back(c, target_char);
    } else if (c == '+' || c == '.') {
      if (dp.size() < 2) {
        throw std::invalid_argument(MakeExceptionMessage(
            "Invalid regular expression: too few args for operation '" +
                std::string(1, c) + "'",
            s, i));
      }
      auto right_operand = dp.back();
      dp.pop_back();
      (c == '+') ? (dp.back() += right_operand) : (dp.back() *= right_operand);
    } else if (c == '*') {
      if (dp.empty()) {
        throw std::invalid_argument(MakeExceptionMessage(
            "Invalid regular expression: too few args for operation '" +
                std::string(1, c) + "'",
            s, i));
      }
      *dp.back();
    } else {
      throw std::invalid_argument(
          MakeExceptionMessage("Invalid regular expression: unknown symbol '" +
                                   std::string(1, c) + "'",
                               s, i));
    }
  }

  if (dp.size() > 1) {
    throw std::invalid_argument(
        "Invalid regular expression: too few operation (" +
        std::to_string(dp.size() - 1) + " extra operands)");
  }
  return dp.back().max_prefix;
}

std::string MakeExceptionMessage(std::string message,
                                 const std::string& invalid_argument,
                                 size_t i) {
  message += '\n';
  message += invalid_argument;
  message += '\n';
  message += std::string(i, ' ');
  message += "^\n";
  return message;
}