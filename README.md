# Deterministic Evaluation of an Accumulation

## Background

As we've discussed before, floating point math is *technically* deterministic - that is, performing the same set of mathematical operations, in the same order, using the same floating point representation (which includes being consistent about the use of temporary values in registers), will reliably produce the same results.
In practice, those conditions are very difficult to meet.
For example, parallelizing a calculation with OpenMP will often cause different parts of a problem to be divided between threads in a dynamic manner, so that there is genuine randomness in the order in which operations are performed.
Because floating point arithmetic is not associative, operations as simple as summing all the values in a vector will produce slightly different results depending on the order in which the elements are added together.

An unfortunate consequence of this is that computational chemistry simulations are very difficult to replicate exactly.
This can be a problem when trying to track down bugs that only occur upon rare occasions, when attempting to identify sources of numerical instability, or when validating a parallelized algorithm.
One possible solution, under certain circumstances, is to switch from doing floating-point math to doing integer math.
To understand how this works, suppose you have a double precision value of `1.041872619831`.
If you multiply this double precision value by a large number, you can represent part of the mantissa as an integer.
For example, if you multiply by `10000`, you can approximately store the entire value as the integer `10419`.
To convert back to a double precision value, just divide by the same large number; in our example, this will give a result of approximately `1.0419`, which means that we have obviously lost a certain amount of precision.
Nonetheless, if we do math exclusively with integer representations of floating point numbers, we don't need to worry about the nuances of floating precision math (including the non-associativity issue).
A possible strategy is therefore to convert floating point values to an integer type, do math with them, and then convert them back to floating point representations.
This allows for practical calculations that are much closer to being genuinely deterministic.

Although this might seem like an awkward solution (and it is!), there are real-world situations where this is a reasonable approach.
For example, Tinker9 is a molecular dynamics code that provides users the option to do something very similar to what we've described (see these files for details: [precision.h](https://github.com/TinkerTools/tinker9/blob/master/include/ff/precision.h) and [energybuffer.h](https://github.com/TinkerTools/tinker9/blob/master/include/ff/energybuffer.h)).

## Task

In `src/main.cpp`, you will find a code that initializes a large vector with random, double precision values between `0.0` and `1.0`.
It then calls a template function called `accumulate` several times with different types (specifically, `float`, `double`, `int`, and `long`).
Your task is to add code to the `accumulate` function so that it accumulates (that is, sums) all the values in this vector.
Your `accumulate` function must do this twice: the first time, by adding the vector's values in order from the first index to the last index, and the second time, by adding the vector's values in order from the last index to the first index.
**Print both sums, as well as the difference between the two sums.**

The template function's type `T` indicates what type should be used to represent the intermediate values of the sum as it is being computed.
When the type is `int` or `long`, you will need to perform conversions similar to that described in the Background information.
Try to maximize the precision of your `int`/`long` representation.
This means multiplying by a very large value, but also avoiding any integer overflows (you'll want to use [std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits) to help with this).
Regardless of the type of `T`, convert your sum to a `double` after all the values have been added.
If you do this correctly, you should find that the `int`/`long` representations produce the same result, regardless of the order of the summation.

Write a brief summary of your observations.
Also write a brief explanation of the limitations of this method - why doesn't it make sense to always use integer representations instead of floating point representations?

## Hints

An easy way to cause a template to behave differently depending on the type is to use `is_same`.
For example,

```
  if ( std::is_same<T, int>::value ) {
    // Do stuff that assumes "T" is "int"
    ...
  }

Note that temporary variables (from intermediate calculation steps) can cause you problems during this problem.
For example, the following two are **not** the same:

```
long sum = 0;
long factor = 1024;
double value = 1.1;

sum += value * factor;
```

```
long sum = 0;
long factor = 1024;
double value = 1.1;

long intermediate = value * factor;
sum += intermediate;
```

When in doubt, try doing explicit casts.
