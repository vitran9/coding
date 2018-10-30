/*
* Copyright (C) 2018 David C. Harrison. All right reserved.
*
* You may not use, distribute, publish, or modify this code without
* the express written permission of the copyright holder.
*/

// int main() {
//   unsigned int[]{
//     100, 21, 22,
//   };



/**
* Sorts the array lexicographically.
*
* The trick is that we have to compare digits left-to-right
* (considering typical Latin decimal notation) and that each of
* two numbers to compare may have a different number of digits.
*
* This is very efficient in storage space, but inefficient in
* execution time; an approach that pre-visits each element and
* stores a translated representation will at least double your
* storage requirements (possibly a problem with large inputs)
* but require only a single translation of each element.
*/

// https://stackoverflow.com/questions/19588809/sort-array-of-integers-lexicographically-c

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>

#include "radix.h"

using namespace std;

static unsigned int cores_;
RadixSort::RadixSort(const unsigned int cores) {
  cores_ = cores;
  // cout << cores_ << endl;
}


void RadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) {

  std::vector<unsigned int> &list = lists[0];
  // for( auto list : lists){
  //
  // }

std::sort(
    std::begin(list),
    std::end(list),
    [](unsigned int lhs, unsigned int rhs) -> bool {
      // Returns true if lhs < rhs
      // Returns false otherwise
      const auto BASE      = 10;
      const bool LHS_FIRST = true;
      const bool RHS_FIRST = false;
      const bool EQUAL     = false;


      // There's no point in doing anything at all
      // if both inputs are the same; strict-weak
      // ordering requires that we return `false`
      // in this case.
      if (lhs == rhs) {
        return EQUAL;
      }

      // Compensate for sign
      if (lhs < 0 && rhs < 0) {
        // When both are negative, sign on its own yields
        // no clear ordering between the two arguments.
        //
        // Remove the sign and continue as for positive
        // numbers.
        lhs *= -1;
        rhs *= -1;
      }
      else if (lhs < 0) {
        // When the LHS is negative but the RHS is not,
        // consider the LHS "first" always as we wish to
        // prioritise the leading '-'.
        return LHS_FIRST;
      }
      else if (rhs < 0) {
        // When the RHS is negative but the LHS is not,
        // consider the RHS "first" always as we wish to
        // prioritise the leading '-'.
        return RHS_FIRST;
      }

      // Counting the number of digits in both the LHS and RHS
      // arguments is *almost* trivial.
      const auto lhs_digits = (
        lhs == 0
        ? 1
        : std::ceil(std::log(lhs+1)/std::log(BASE))
      );

      const auto rhs_digits = (
        rhs == 0
        ? 1
        : std::ceil(std::log(rhs+1)/std::log(BASE))
      );

      // Now we loop through the positions, left-to-right,
      // calculating the digit at these positions for each
      // input, and comparing them numerically. The
      // lexicographic nature of the sorting comes from the
      // fact that we are doing this per-digit comparison
      // rather than considering the input value as a whole.
      const auto max_pos = std::max(lhs_digits, rhs_digits);
      for (auto pos = 0; pos < max_pos; pos++) {
        if (lhs_digits - pos == 0) {
          // Ran out of digits on the LHS;
          // prioritise the shorter input
          return LHS_FIRST;
        }
        else if (rhs_digits - pos == 0) {
          // Ran out of digits on the RHS;
          // prioritise the shorter input
          return RHS_FIRST;
        }
        else {
          const auto lhs_x = (lhs / static_cast<decltype(BASE)>(std::pow(BASE, lhs_digits - 1 - pos))) % BASE;
          const auto rhs_x = (rhs / static_cast<decltype(BASE)>(std::pow(BASE, rhs_digits - 1 - pos))) % BASE;

          if (lhs_x < rhs_x)
          return LHS_FIRST;
          else if (rhs_x < lhs_x)
          return RHS_FIRST;
        }
      }

      // If we reached the end and everything still
      // matches up, then something probably went wrong
      // as I'd have expected to catch this in the tests
      // for equality.
      assert("Unknown case encountered");
      return false;
    }
  );

  // for(auto list : lists){
  //   sort(list);
  // }

}
