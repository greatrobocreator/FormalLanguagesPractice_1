#include "MaxPrefixTests.h"

#include "../RegexParser.h"

TEST_F(MaxPrefixTests, InvalidRegexOperation) {
  EXPECT_THROW(RegexParser("a+").MaxPrefixOfSymbols('a'),
               std::invalid_argument);
  EXPECT_THROW(RegexParser("b.").MaxPrefixOfSymbols('a'),
               std::invalid_argument);
  EXPECT_THROW(RegexParser("*").MaxPrefixOfSymbols('a'), std::invalid_argument);
  EXPECT_THROW(RegexParser("ab..").MaxPrefixOfSymbols('a'),
               std::invalid_argument);
}

TEST_F(MaxPrefixTests, InvalidSymbol) {
  EXPECT_THROW(RegexParser("ab.c+").MaxPrefixOfSymbols('1'),
               std::invalid_argument);
  EXPECT_THROW(RegexParser("ab.c+").MaxPrefixOfSymbols('e'),
               std::invalid_argument);
  EXPECT_THROW(RegexParser("ab.c+").MaxPrefixOfSymbols('u'),
               std::invalid_argument);
  EXPECT_THROW(RegexParser("ab.u+").MaxPrefixOfSymbols('a'),
               std::invalid_argument);
}

TEST_F(MaxPrefixTests, InvalidOperandsCount) {
  EXPECT_THROW(RegexParser("ab.cbc+").MaxPrefixOfSymbols('a'),
               std::invalid_argument);
}

TEST_F(MaxPrefixTests, SimpleTests) {
  EXPECT_EQ(RegexParser("ab+c.aba.*.bac.+.+*").MaxPrefixOfSymbols('a'), 2);
  EXPECT_EQ(RegexParser("acb..bab.c.*.ab.ba.+.+*a.").MaxPrefixOfSymbols('c'),
            0);
}

TEST_F(MaxPrefixTests, InfinityTests) {
  /// (a+b)*
  EXPECT_GE(RegexParser("ab+*").MaxPrefixOfSymbols('a'),
            std::numeric_limits<int>::max());

  /// c(a+b)*c*
  EXPECT_GE(RegexParser("cab+*.c*.").MaxPrefixOfSymbols('c'),
            std::numeric_limits<int>::max());
}

TEST_F(MaxPrefixTests, EpsilonTests) {
  /// 11b*a*
  EXPECT_GE(RegexParser("11.b*.a*.").MaxPrefixOfSymbols('a'),
            std::numeric_limits<int>::max());
}

TEST_F(MaxPrefixTests, EmptyTest) {
  EXPECT_THROW(RegexParser("").MaxPrefixOfSymbols('a'), std::invalid_argument);
}