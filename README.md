# FormalLanguagesPractice_1

## Build
```
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

This will create two binary files in cmake-build-debug folder:

+ FormalLanguagesPractice_1 - for using with stdin
+ Tests - for running tests

## Coverage report

After building the project you can create coverage report

```
make coverage_report
```

This will create coverage html-report cmake-build-debug/coverage/index.html


## Algorithm description

Let's solve problem using dynamic programming on stack of RPN evaluation.

Dynamic programming state - 
+ max prefix of target symbols 
+ max size of word of kind (target_char)^k

Result state of operation '+' is just maximum of both operands


Max prefix of 'ab.' is maximum of "a.max_full_word + b.max_prefix" and "a.max_prefix", because each prefix of 'ab.' is prefix of 'a' or full 'a' of target chars and prefix of 'b'.

Max full word of 'ab.' is sum of full words size of 'a' and 'b'.


For operation 'a*' result is pretty simple - if full word size greater than zero then result is (infinity, infinity). Else result is (a.max_prefix, 0).

After reading all string result is on the top of stack.
