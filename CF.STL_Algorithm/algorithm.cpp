//
//  algorithm.cpp
//  CF.STL_Algorithm
//
//  Created by Alan Sampson on 9/12/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//
//  MARK: Reference.
//  @see: https://en.cppreference.com/w/cpp/header/algorithm

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <array>
#include <iterator>
#include <string>
#include <sstream>
#include <numeric>
#include <functional>
#include <thread>
#include <chrono>
#include <random>
#include <cctype>

using namespace std::literals::string_literals;

//  MARK: - Definitions.
/*
 *  MARK: in_quote()
 */
template <typename Container>
bool in_quote(const Container & cont, const std::string & s) {
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

/*
 *  MARK: consecutive_values()
 */
template <class Container, class Size, class T>
bool consecutive_values(const Container & c, Size count, const T & v) {
  return std::search_n(std::begin(c), std::end(c), count,v) != std::end(c);
}

/*
 *  MARK: selection_sort()
 */
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end) {
  for (ForwardIt i = begin; i != end; ++i) {
    std::iter_swap(i, std::min_element(i, end));
  }
}

/*
 *  MARK: quicksort()
 */
template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) {
  if (first == last) {
    return;
  }

  auto pivot = *std::next(first, std::distance(first,last) / 2);
  ForwardIt middle1 = std::partition(first, last,
                      [pivot](const auto& em) { return em < pivot; });
  ForwardIt middle2 = std::partition(middle1, last,
                      [pivot](const auto& em) { return !(pivot < em); });
  quicksort(first, middle1);
  quicksort(middle2, last);
}

/*
 *  MARK: merge_sort()
 */
template<class Iter>
void merge_sort(Iter first, Iter last)
{
  if (last - first > 1) {
    Iter middle = first + (last - first) / 2;
    merge_sort(first, middle);
    merge_sort(middle, last);
    std::inplace_merge(first, middle, last);
  }
}

/*
 *  MARK: operator <<()
 */
template<class Os, class Co>
Os & operator <<(Os & os, const Co & v) {
  for (auto i : v) {
    os << i << ' ';
  }
  return os << '\t';
}

// /*
//  *  MARK: operator <<()
//  */
//template<typename Os, typename V>
//Os & operator<< (Os & os, V const & v) {
//    os << "{ ";
//    for (auto const& e : v) os << e << ' ';
//    return os << "}";
//}

//  MARK: - Function Prototypes.
void fn_non_mod_sequences(void);
void fn_mod_sequences(void);
void fn_partitioning(void);
void fn_sorting(void);
void fn_bin_search(void);
void fn_sort_ops(void);
void fn_set_ops(void);
void fn_heap_ops(void);
void fn_min_max(void);
void fn_compare_ops(void);
void fn_permutation_ops(void);

//  MARK: - Implementation.
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "CF.STL_Algorithm"s << std::endl;

  fn_non_mod_sequences();
  fn_mod_sequences();
  fn_partitioning();
  fn_sorting();
  fn_bin_search();
  fn_sort_ops();
  fn_set_ops();
  fn_heap_ops();
  fn_min_max();
  fn_compare_ops();
  fn_permutation_ops();

  return 0;
}

//  MARK: - Non-modifying sequence operations
/*
 *  MARK: fn_non_mod_sequences()
 *  + std::all_of         checks if a predicate is true for all elements in a range
 *  + std::any_of         checks if a predicate is true for any elements in a range
 *  + std::none_of        checks if a predicate is true for no elements in a range
 *  + std::for_each       applies a function to a range of elements
 *  + std::for_each_n     applies a function object to the first n elements of a sequence
 *  + std::count          returns the number of elements satisfying specific criteria
 *  + std::count_if       ditto
 *  + std::mismatch       finds the first position where two ranges differ
 *  + std::find           finds the first element satisfying specific criteria
 *  + std::find_if        ditto
 *  + std::find_if_not    ditto
 *  + std::find_end       finds the last sequence of elements in a certain range
 *  + std::find_first_of  searches for any one of a set of elements
 *  + std::adjacent_find  finds the first two adjacent items that are equal (or satisfy a given predicate)
 *  + std::search         searches for a range of elements
 *  + std::search_n       searches a range for a number of consecutive copies of an element
 */
void fn_non_mod_sequences(void) {
  std::cout << "Function: "s << __func__ << std::endl;
  std::cout
    << "--------------------------------------------------------------------------------"s
    << '\n'
    << std::endl;

  /*
   *  TODO: std::all_of, std::any_of, std::none_of
   *  all_of  Checks if unary predicate p returns true for all elements in the range [first, last).
   *  any_of  Checks if unary predicate p returns true for at least one element in the range [first, last).
   *  none_of Checks if unary predicate p returns true for no elements in the range [first, last).
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::all_of, std::any_of, std::none_of"s << '\n'
    << std::endl;
  {
    std::vector<int> v (10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: "s;
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
       std::cout << "All numbers are even\n"s;
    }

    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), std::placeholders::_1, 2))) {
      std::cout << "None of them are odd\n"s;
    }

    /*
     *  MARK: Structure DivisibleBy
     */
    struct DivisibleBy {
      const int d;
      DivisibleBy(int n) : d(n) {}
      bool operator()(int n) const { return n % d == 0; }
    };

    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
      std::cout << "At least one number is divisible by 7\n"s;
    }
    std::putchar('\n');

    //  see also samples in std::for_each, std::find_if & std::find_if_not for other ways
    std::vector<std::string> tests {
      "abCDe",
      "abcDEfG",
      "abcdef",
      "12345",
      "abc1def",
      "Whatever",
      "whatever!",
      "whatever",
      "what\tever",
      "whatever next",
    };

    for (std::string tst : tests) {
      auto lc = std::all_of(tst.begin(), tst.end(), [](char c_) {
        return std::islower(c_);
      });

      std::cout << std::setw(20)
                << tst
                << ": "
                << std::boolalpha
                << lc
                << std::endl;
    }
    std::putchar('\n');
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::for_each
   *  Applies the given function object f to the result of dereferencing every iterator in the
   *  range [first, last)
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::for_each"s << '\n'
    << std::endl;
  {
    /*
     *  MARK: Structure Sum
     */
    struct Sum {
      void operator()(int n) { sum += n; }
      int sum { 0 };
    };

    std::vector<int> nums { 3, 4, 2, 8, 15, 267, };
   
    auto print = [](const int & n) { std::cout << " "s << n; };

    std::cout << "before:"s;
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';

    std::for_each(nums.begin(), nums.end(), [](int & n){ n++; });

    // calls Sum::operator() for each number
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());

    std::cout << "after: "s;
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
    std::cout << "sum: "s << s.sum << '\n';

    std::putchar('\n');

    //  demo a lambda that uses capture (by reference) to update a variable.
    //  [see also samples in std::all_of, std::find_if & std::find_if_not for a better way]
    std::vector<std::string> tests {
      "abCDe",
      "abcDEfG",
      "abcdef",
      "12345",
      "abc1def",
      "Whatever",
      "whatever!",
      "whatever",
      "what\tever",
      "whatever next",
    };

    for (std::string tst : tests) {
      bool lc = true;

      std::for_each(tst.begin(), tst.end(), [&lc](char const c_) {
          bool l_ = std::islower(c_);
          lc = lc ? l_ : lc;
//          std::cout << std::boolalpha << lc << ' ' << l_ << std::endl;
        });

      std::cout << std::setw(20)
                << tst
                << ": "
                << std::boolalpha
                << lc
                << std::endl;
    }
    std::putchar('\n');
  }
  std::cout << std::endl;

  /*
   *  TODO: std::for_each_n
   *  Applies the given function object f to the result of dereferencing every iterator in the
   *  range [first, first + n)
   *
   *  The following example uses a lambda function to increment all of the elements of a vector
   *  and then uses an overloaded operator() in a functor to compute their sum. Note that to
   *  compute the sum, it is recommended to use the dedicated algorithm std::accumulate.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::for_each_n"s << '\n'
    << std::endl;
  {
    std::vector<int> ns { 1, 2, 3, 4, 5, };
    for (auto n: ns) {
      std::cout << n << ", "s;
    }
    std::cout << '\n';

    std::for_each_n(ns.begin(), 3, [](auto & n){ n *= 2; });
    for (auto n: ns) {
      std::cout << n << ", "s;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::count, std::count_if
   *  std::count     counts the elements that are equal to value.
   *  std::count_if  counts elements for which predicate p returns true.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::count, std::count_if"s << '\n'
    << std::endl;
  {
    std::vector<long> v { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10, };

    // determine how many integers in a std::vector match a target value.
    long target1 = 3;
    long target2 = 5;
    long num_items1 = std::count(v.begin(), v.end(), target1);
    long num_items2 = std::count(v.begin(), v.end(), target2);
    std::cout << "number: "s << target1 << " count: "s << num_items1 << '\n';
    std::cout << "number: "s << target2 << " count: "s << num_items2 << '\n';

    // use a lambda expression to count elements divisible by 3.
    long num_items3 = std::count_if(v.begin(), v.end(), [](int i){ return i % 3 == 0; });
    std::cout << "number divisible by three: "s << num_items3 << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::mismatch
   *  Returns the first mismatching pair of elements from two ranges: one defined
   *  by [first1, last1) and another defined by [first2,last2). If last2 is not provided
   *  (overloads (1-4)), it denotes first2 + (last1 - first1).
   *
   *  This program determines the longest substring that is simultaneously found at the very
   *  beginning of the given string and at the very end of it, in reverse order (possibly overlapping)
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::mismatch"s << '\n'
    << std::endl;
  {
    std::string mirror_ends(const std::string & in);

    std::cout << mirror_ends("abXYZba"s) << '\n'
              << mirror_ends("abca"s) << '\n'
              << mirror_ends("aba"s) << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::find, std::find_if, std::find_if_not
   *  Returns the first element in the range [first, last) that satisfies specific criteria:
   *  find searches for an element equal to value
   *  find_if searches for an element for which predicate p returns true
   *  find_if_not searches for an element for which predicate q returns false
   *
   *  The following example finds an integer in a vector of integers.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::find, std::find_if, std::find_if_not"s << '\n'
    << std::endl;
  {
    int n1 = 3;
    int n2 = 5;

    std::vector<int> v { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    auto result1f = std::find(std::begin(v), std::end(v), n1);
    auto result2f = std::find(std::begin(v), std::end(v), n2);

    if (result1f != std::end(v)) {
      std::cout << "v contains: "s << n1 << '\n';
    }
    else {
      std::cout << "v does not contain: "s << n1 << '\n';
    }

    if (result2f != std::end(v)) {
      std::cout << "v contains: "s << n2 << '\n';
    }
    else {
      std::cout << "v does not contain: "s << n2 << '\n';
    }

    auto is_odd = [](int i_) { return (i_ % 2) != 0; };
    auto is_even = [](int i_) { return (i_ % 2) == 0; };

    auto result1if = std::find_if(std::begin(v), std::end(v), is_odd);
    std::cout << "The first odd value is "s << *result1if << '\n';
    auto result2if = std::find_if(std::begin(v), std::end(v), is_even);
    std::cout << "The first even value is "s << *result2if << '\n';

    auto result1nif = std::find_if_not(std::rbegin(v), std::rend(v), is_even);
    std::cout << "The last odd value is "s << *result1nif << '\n';
    auto result2nif = std::find_if_not(std::rbegin(v), std::rend(v), is_odd);
    std::cout << "The last even value is "s << *result2nif << '\n';

    //  see also samples in std::for_each, std::all_of for other ways
    std::vector<std::string> tests {
      "abCDe",
      "abcDEfG",
      "abcdef",
      "12345",
      "abc1def",
      "Whatever",
      "whatever!",
      "whatever",
      "what\tever",
      "whatever next",
    };

    for (std::string tst : tests) {
      auto fi = std::find_if(tst.begin(), tst.end(), [](char c_) {
        return !std::islower(c_);
      });
      bool lc = (fi != tst.end()) ? false : true;

      std::cout << std::setw(20)
                << tst
                << ": "
                << std::boolalpha
                << lc
                << std::endl;
    }
    std::putchar('\n');

    for (std::string tst : tests) {
      auto fi = std::find_if_not(tst.begin(), tst.end(), [](char c_) {
        return std::islower(c_);
      });
      bool lc = (fi != tst.end()) ? false : true;

      std::cout << std::setw(20)
                << tst
                << ": "
                << std::boolalpha
                << lc
                << std::endl;
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::find_end
   *  Searches for the last occurrence of the sequence [s_first, s_last) in the range [first, last).
   *
   *  The following code uses find_end() to search for two different sequences of numbers.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::find_end"s << '\n'
    << std::endl;
  {
    std::vector<int> v { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, };
    std::vector<int>::iterator result;

    std::vector<int> t1 { 1, 2, 3, };

    result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if (result == v.end()) {
      std::cout << "sequence not found\n"s;
    }
    else {
      std::cout << "last occurrence is at: "s
                << std::distance(v.begin(), result)
                << "\n"s;
    }

    std::vector<int> t2{ 4, 5, 6, };
    result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end());
    if (result == v.end()) {
      std::cout << "sequence not found\n"s;
    }
    else {
      std::cout << "last occurrence is at: "s
                << std::distance(v.begin(), result)
                << "\n"s;
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::find_first_of
   *  Searches the range [first, last) for any of the elements in the range [s_first, s_last).
   *
   *  The following code searches for any of specified integers in a vector of integers:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::find_first_of"s << '\n'
    << std::endl;
  {
    std::vector<int> v { 0, 2, 3, 25, 5, };
    std::vector<int> t { 3, 19, 10, 2, };

    auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());

    if (result == v.end()) {
      std::cout << "no elements of v were equal to 3, 19, 10 or 2\n"s;
    }
    else {
      std::cout << "found a match at "s
                << std::distance(v.begin(), result) << "\n"s;
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::adjacent_find
   *  Searches the range [first, last) for two consecutive equal elements.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::adjacent_find"s << '\n'
    << std::endl;
  {
    std::vector<int> v1 { 0, 1, 2, 3, 40, 40, 41, 41, 5, };

    auto i1 = std::adjacent_find(v1.begin(), v1.end());

    if (i1 == v1.end()) {
      std::cout << "no matching adjacent elements\n"s;
    }
    else {
      std::cout << "the first adjacent pair of equal elements at: "s
                << std::distance(v1.begin(), i1) << '\n';
    }

    auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
    if (i2 == v1.end()) {
      std::cout << "The entire vector is sorted in ascending order\n"s;
    }
    else {
      std::cout << "The last element in the non-decreasing subsequence is at: "s
                << std::distance(v1.begin(), i2) << '\n';
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::search
   *  Searches for the first occurrence of the sequence of elements [s_first, s_last) in the
   *  range [first, last).
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::search"s << '\n'
    << std::endl;
  {

    std::string str = "why waste time learning, when ignorance is instantaneous?"s;
    // str.find() can be used as well
    std::cout << std::boolalpha << in_quote(str, "learning"s) << '\n'
                                << in_quote(str, "lemming"s)  << '\n';

    std::vector<char> vec(str.begin(), str.end());
    std::cout << std::boolalpha << in_quote(vec, "learning"s) << '\n'
                                << in_quote(vec, "lemming"s)  << '\n';

    // The C++17 overload demo:
    std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                     " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"s;
    std::string needle = "pisci"s;
#if defined(CAN_USE_BOYER_MOORE)
    auto it = std::search(in.begin(), in.end(),
                   std::boyer_moore_searcher(
                      needle.begin(), needle.end()));
#else
    auto it = std::search(in.begin(), in.end(),
                          std::default_searcher(needle.begin(), needle.end()));
#endif /* defined(CAN_USE_BOYER_MOORE) */
    if (it != in.end()) {
        std::cout << "The string "s << needle << " found at offset "s
                  << it - in.begin() << '\n';
    }
    else {
        std::cout << "The string "s << needle << " not found\n"s;
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::search_n
   *  Searches the range [first, last) for the first sequence of count identical elements,
   *  each equal to the given value.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::search_n"s << '\n'
    << std::endl;
  {
    const char sequence[] = "1001010100010101001010101";

    std::cout << std::boolalpha;
    std::cout << "Has 4 consecutive zeros: "s
              << consecutive_values(sequence,4, '0') << '\n';
    std::cout << "Has 3 consecutive zeros: "s
              << consecutive_values(sequence,3, '0') << '\n';
  }
  std::cout << std::endl;

  return;
}

/*
 *  MARK: mirror_ends()
 */
inline
std::string mirror_ends(const std::string & in) {
    return std::string(in.begin(), std::mismatch(in.begin(), in.end(), in.rbegin()).first);
}

//  MARK: - Modifying sequence operations
/*
 *  MARK: fn_mod_sequences()
 *  + std::copy            copies a range of elements to a new location
 *  + std::copy_if         ditto
 *  + std::copy_n          copies a number of elements to a new location
 *  + std::copy_backward   copies a range of elements in backwards order
 *  + std::move            moves a range of elements to a new location
 *  + std::move_backward   moves a range of elements to a new location in backwards order
 *  + std::fill            copy-assigns the given value to every element in a range
 *  + std::fill_n          copy-assigns the given value to N elements in a range
 *  + std::transform       applies a function to a range of elements, storing results in a destination range
 *  + std::generate        assigns the results of successive function calls to every element in a range
 *  + std::generate_n      assigns the results of successive function calls to N elements in a range
 *  + std::remove          removes elements satisfying specific criteria
 *  + std::remove_if       ditto
 *  + std::remove_copy     copies a range of elements omitting those that satisfy specific criteria
 *  + std::remove_copy_if  ditto
 *  + std::replace         replaces all values satisfying specific criteria with another value
 *  + std::replace_if      ditto
 *  + std::replace_copy    copies a range, replacing elements satisfying specific criteria with another value
 *  + std::replace_copy_if ditto
 *  + std::swap            swaps the values of two objects
 *  + std::swap_ranges     swaps two ranges of elements
 *  + std::iter_swap       swaps the elements pointed to by two iterators
 *  + std::reverse_copy    creates a copy of a range that is reversed
 *  + std::rotate          rotates the order of elements in a range
 *  + std::rotate_copy     copies and rotate a range of elements
 *  + std::shift_left      shifts elements in a range
 *  + std::shift_right     ditto
 *  + std::random_shuffle  [deperecated] randomly re-orders elements in a range
 *  + std::shuffle         randomly re-orders elements in a range
 *  + std::sample          selects n random elements from a sequence
 *  + std::unique          removes consecutive duplicate elements in a range
 *  + std::unique_copy     creates a copy of some range of elements that contains no consecutive duplicates
 */
void fn_mod_sequences(void) {
  std::cout << "Function: "s << __func__ << std::endl;
  std::cout
    << "--------------------------------------------------------------------------------"s
    << '\n'
    << std::endl;

  /*
   *  TODO: std::copy, std::copy_if
   *  Copies the elements in the range, defined by [first, last), to another range beginning at d_first.
   *  std::copy Copies all elements in the range [first, last) starting from first and proceeding to
   *  last - 1. The behavior is undefined if d_first is within the range [first, last). In this case,
   *  std::copy_backward may be used instead.
   *  std::copy_if Only copies the elements for which the predicate pred returns true. The relative
   *  order of the elements that are copied is preserved. The behavior is undefined if the source and
   *  the destination ranges overlap.
   *
   *  The following code uses copy to both copy the contents of one vector to another and to display
   *  the resulting vector:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::copy, std::copy_if"s << '\n'
    << std::endl;
  {
    std::vector<int> from_vector(10);
    std::iota(from_vector.begin(), from_vector.end(), 0);

    std::vector<int> to_vector;
    std::copy(from_vector.begin(), from_vector.end(),
              std::back_inserter(to_vector));

// or, alternatively,
//  std::vector<int> to_vector(from_vector.size());
//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
// either way is equivalent to
//  std::vector<int> to_vector = from_vector;

    std::cout << "to_vector contains: "s;
    std::copy(to_vector.begin(), to_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::cout << "odd numbers in to_vector are: "s;
    std::copy_if(to_vector.begin(), to_vector.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 [](int x) { return (x % 2) == 1; });
    std::cout << '\n';

    // demo the alternative,
    std::vector<int> other_vector(from_vector.size());
    std::copy(from_vector.begin(), from_vector.end(), other_vector.begin());
    std::cout << "even numbers in other_vector are: "s;
    std::copy_if(to_vector.begin(), to_vector.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 [](int x) { return (x % 2) == 0; });
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::copy_n
   *  Copies exactly count values from the range beginning at first to the range beginning at result.
   *  Formally, for each integer 0 ≤ i < count, performs *(result + i) = *(first + i). Overlap of
   *  ranges is formally permitted, but leads to unpredictable ordering of the results.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::copy_n"s << '\n'
    << std::endl;
  {
    std::string in = "1234567890"s;
    std::string out;

    std::copy_n(in.begin(), 4, std::back_inserter(out));
    std::cout << out << '\n';

    std::vector<int> v_in(128);
    std::iota(v_in.begin(), v_in.end(), 1);
    std::vector<int> v_out(v_in.size());

    std::copy_n(v_in.cbegin(), 100, v_out.begin());
    std::cout << std::accumulate(v_out.begin(), v_out.end(), 0) << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::copy_backward
   *  Copies the elements from the range, defined by [first, last), to another range ending at d_last.
   *  The elements are copied in reverse order (the last element is copied first), but their relative
   *  order is preserved.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::copy_backward"s << '\n'
    << std::endl;
  {
    std::vector<int> from_vector;
    for (int i = 0; i < 10; i++) {
      from_vector.push_back(i);
    }

    std::vector<int> to_vector(15);

    std::cout << "from_vector contains: "s;
    std::copy(from_vector.begin(), from_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());

    std::cout << "to_vector contains: "s;
    for (auto i : to_vector) {
      std::cout << i << " "s;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::move
   *  Moves the elements in the range [first, last), to another range beginning at d_first, starting
   *  from first and proceeding to last - 1. After this operation the elements in the moved-from range
   *  will still contain valid values of the appropriate type, but not necessarily the same values as
   *  before the move.
   *
   *  The following code moves thread objects (which themselves are not copyable) from one container
   *  to another.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::move"s << '\n'
    << std::endl;
  {
    void f_sleep(int);
    std::vector<std::thread> vt;
    vt.emplace_back(f_sleep, 1);
    vt.emplace_back(f_sleep, 2);
    vt.emplace_back(f_sleep, 3);
    std::list<std::thread> lt;
    // copy() would not compile, because std::thread is noncopyable

    std::move(vt.begin(), vt.end(), std::back_inserter(lt));
    for (auto & t_ : lt) {
      t_.join();
    }
  }
  std::cout << std::endl;

  /*
   *  TODO: std::move_backward
   *  Moves the elements from the range [first, last), to another range ending at d_last. The elements
   *  are moved in reverse order (the last element is moved first), but their relative order is preserved.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::move_backward"s << '\n'
    << std::endl;
  {
    std::vector<std::string> src{"foo"s, "bar"s, "baz"s};
    std::vector<std::string> dest(src.size());

    std::cout << "src: "s;
    for (const auto & s : src) {
      std::cout << s << ' ';
    }

    std::cout << "\ndest: "s;
    for (const auto & s : dest) {
      std::cout << s << ' ';
    }
    std::cout << '\n';

    std::move_backward(src.begin(), src.end(), dest.end());

    std::cout << "src: "s;
    for (const auto & s : src) {
      std::cout << s << ' ';
    }

    std::cout << "\ndest: "s;
    for (const auto & s : dest) {
      std::cout << s << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::fill
   *  Assigns the given value to the elements in the range [first, last).
   *
   *  The following code uses fill() to set all of the elements of a vector of ints to -1:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::fill"s << '\n'
    << std::endl;
  {
    std::vector<int> v { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    std::fill(v.begin(), v.end(), -1);

    for (auto elem : v) {
      std::cout << elem << " "s;
    }
    std::cout << "\n"s;
  }
  std::cout << std::endl;

  /*
   *  TODO: std::fill_n
   *  Assigns the given value to the first count elements in the range beginning at first if
   *  count > 0. Does nothing otherwise.
   *
   *  The following code uses fill_n() to assign -1 to the first half of a vector of integers:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::fill_n"s << '\n'
    << std::endl;
  {
    std::vector<int> v1 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    std::fill_n(v1.begin(), 5, -1);

    std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::transform
   *  applies the given function to a range and stores the result in another range,
   *  beginning at d_first.
   *
   *  The following code uses transform to convert a string in place to uppercase using the
   *  toupper function and then transforms each char to its ordinal value:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::transform"s << '\n'
    << std::endl;
  {
    std::string str("hello"s);
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });

    std::vector<std::size_t> ordinals;
    std::transform(str.begin(), str.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });

    std::cout << str << ':';
    for (auto ord : ordinals) {
      std::cout << ' ' << ord << ' ' << static_cast<char>(ord);
    }

    std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
                   ordinals.begin(), std::plus<>{});

    std::cout << '\n';
    for (auto ord : ordinals) {
      std::cout << ord << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::generate
   *  Assigns each element in range [first, last) a value generated by the given function object g.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::generate"s << '\n'
    << std::endl;
  {
    int f_gen(void);

    std::vector<int> v(5);
      std::generate(v.begin(), v.end(), f_gen);

    std::cout << "v: "s;
    for (auto iv : v) {
      std::cout << iv << " "s;
    }
    std::cout << "\n"s;

    // Initialize with default values 0,1,2,3,4 from a lambda function
    // Equivalent to std::iota(v.begin(), v.end(), 0);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });

    std::cout << "v: "s;
    for (auto iv : v) {
      std::cout << iv << " "s;
    }
    std::cout << "\n"s;
  }
  std::cout << std::endl;

  /*
   *  TODO: std::generate_n
   *  Assigns values, generated by given function object g, to the first count elements in the
   *  range beginning at first, if count>0. Does nothing otherwise.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::generate_n"s << '\n'
    << std::endl;
  {
    std::mt19937 rng; // default constructed, seeded with fixed seed
    std::generate_n(std::ostream_iterator<std::mt19937::result_type>(std::cout, " "),
                    5, std::ref(rng));
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::remove, std::remove_if
   *  Removes all elements satisfying specific criteria from the range [first, last) and returns
   *  a past-the-end iterator for the new end of the range.
   *
   *  The following code removes all spaces from a string by shifting all non-space characters
   *  to the left and then erasing the extra. This is an example of erase-remove idiom
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::remove, std::remove_if"s << '\n'
    << std::endl;
  {
    std::string str1 = "Text with some   spaces"s;
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << str1 << '\n';

    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n"s;
    str2.erase(std::remove_if(str2.begin(),
                              str2.end(),
                              [](unsigned char x){ return std::isspace(x); }),
               str2.end());
    std::cout << str2 << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::remove_copy, std::remove_copy_if
   *  Copies elements from the range [first, last), to another range beginning at d_first,
   *  omitting the elements which satisfy specific criteria. Source and destination ranges
   *  cannot overlap.
   *
   *  The following code outputs a string while erasing the spaces on the fly.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::remove_copy, std::remove_copy_if"s << '\n'
    << std::endl;
  {
    std::string str1 = "Text with some   spaces"s;
    std::cout << "before: "s << str1 << '\n';

    std::cout << "after:  "s;
    std::remove_copy(str1.begin(), str1.end(),
                     std::ostream_iterator<char>(std::cout), ' ');
    std::cout << '\n';
    
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n"s;
    std::string str3;
    std::stringstream ob;
    std::ostream_iterator<char> ost(ob);
    std::cout << "before:\n"s << str2 << '\n';
    std::remove_copy_if(str2.begin(), str2.end(), ost,
                        [](unsigned char x){ return std::isspace(x); });
    str3 = ob.str();
    std::cout << "after:\n"s << str3 << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::replace, std::replace_if
   *  Replaces all elements satisfying specific criteria with new_value in the range [first, last).
   *
   *  The following code at first replaces all occurrences of 8 with 88 in a vector of integers.
   *  Then it replaces all values less than 5 with 55.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::replace, std::replace_if"s << '\n'
    << std::endl;
  {
    std::array<int, 10> sn { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3, };

    std::replace(sn.begin(), sn.end(), 8, 88);

    for (int a_ : sn) {
      std::cout << a_ << " ";
    }
    std::cout << '\n';

    std::replace_if(sn.begin(), sn.end(),
                    std::bind(std::less<int>(), std::placeholders::_1, 5), 55);
    for (int a_ : sn) {
      std::cout << a_ << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::replace_copy, std::replace_copy_if
   *  Copies the elements from the range [first, last) to another range beginning at d_first
   *  replacing all elements satisfying specific criteria with new_value. The source and
   *  destination ranges cannot overlap.
   *
   *  The following copy prints a vector, replacing all values over 5 with 99 on the fly.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::replace_copy, std::replace_copy_if"s << '\n'
    << std::endl;
  {
    std::vector<int> v { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3, };
    std::replace_copy_if(v.begin(), v.end(),
                         std::ostream_iterator<int>(std::cout, " "),
                         [](int n){ return n > 5; }, 99);
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::swap
   *  Swaps the values a and b.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::swap"s << '\n'
    << std::endl;
  {
    //  --------------------------------------------------------------------------------
    std::cout << "primitives\n"s;
    int a = 5, b = 3;

    // before
    std::cout << a << ' ' << b << '\n';

    std::swap(a, b);

    // after
    std::cout << a << ' ' << b << '\n';
    
    auto print_int = [](int i_) { std::cout << i_ << ' '; };
    auto print_str = [](std::string i_) { std::cout << i_ << ' '; };

    //  --------------------------------------------------------------------------------
    std::cout << "arrays\n"s;
    int a1[] { 0, 1, 2, 3, 4, 5, };
    int b1[] { 5, 4, 3, 2, 1, 0, };

    std::cout << "before swap:"s << std::endl;
    std::cout << "a1 { "s;
    std::for_each(std::begin(a1), std::end(a1), print_int);
    std::cout << "}"s << '\n';
    std::cout << "a2 { "s;
    std::for_each(std::begin(b1), std::end(b1), print_int);
    std::cout << "}"s << '\n';

    std::swap(a1, b1);

    std::cout << "after swap:"s << std::endl;
    std::cout << "a1 { "s;
    std::for_each(std::begin(a1), std::end(a1), print_int);
    std::cout << "}"s << '\n';
    std::cout << "a2 { "s;
    std::for_each(std::begin(b1), std::end(b1), print_int);
    std::cout << "}"s << '\n';

    //  --------------------------------------------------------------------------------
    std::cout << "collections <std::vector>\n"s;
    std::vector<std::string> v1 { "zero"s, "one"s, "two"s, "three"s, "four"s, };
    std::vector<std::string> v2 { "three"s, "two"s, "one"s, "zero"s, };

    std::cout << "v1 { "s;
    std::for_each(std::begin(v1), std::end(v1), print_str);
    std::cout << "}"s << '\n';
    std::cout << "v2 { "s;
    std::for_each(std::begin(v2), std::end(v2), print_str);
    std::cout << "}"s << '\n';

    std::swap(v1, v2);

    std::cout << "v1 { "s;
    std::for_each(std::begin(v1), std::end(v1), print_str);
    std::cout << "}"s << '\n';
    std::cout << "v2 { "s;
    std::for_each(std::begin(v2), std::end(v2), print_str);
    std::cout << "}"s << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::swap_ranges
   *  Exchanges elements between range [first1, last1) and another range starting at first2.
   *
   *  Demonstrates swapping of subranges from different containers
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::swap_ranges"s << '\n'
    << std::endl;
  {
    std::vector<int> vs = { 1, 2, 3, 4, 5, };
    std::list<int> ls = { -1, -2, -3, -4, -5, };

    auto print_int = [](int i_) { std::cout << std::setw(4) << i_; };

    std::cout << "vs: ";
    std::for_each(vs.begin(), vs.end(), print_int);
    std::cout << '\n';
    std::cout << "ls: ";
    std::for_each(ls.begin(), ls.end(), print_int);
    std::cout << '\n';

    std::swap_ranges(vs.begin(), vs.begin() + 3, ls.begin());

    std::cout << "vs: ";
    std::for_each(vs.begin(), vs.end(), print_int);
    std::cout << '\n';
    std::cout << "ls: ";
    std::for_each(ls.begin(), ls.end(), print_int);
    std::cout << '\n';

//    for (int n_ : vs) {
//      std::cout << std::setw(4) << n_;
//    }
//    std::cout << '\n';
//    for (int n_ : ls) {
//      std::cout << std::setw(4) << n_;
//    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::iter_swap
   *  Swaps the values of the elements the given iterators are pointing to.
   *
   *  The following is an implementation of selection sort in C++
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::iter_swap"s << '\n'
    << std::endl;
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> vg;
    generate_n(back_inserter(vg), 20, bind(dist, gen));

    std::cout << "Before sort: ";
    for (auto e_ : vg) {
      std::cout << std::setw(4) << e_;
    }
    std::cout << '\n';

    selection_sort(vg.begin(), vg.end());

    std::cout << " After sort: ";
    for (auto e_ : vg) {
      std::cout << std::setw(4) << e_;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::reverse_copy
   *  Copies the elements from the range [first, last) to another range beginning at d_first
   *  in such a way that the elements in the new range are in reverse order.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::reverse_copy"s << '\n'
    << std::endl;
  {
    auto print = [](std::vector<int> const & v) {
      for (const auto & value : v) {
        std::cout << std::setw(5) << value;
      }
      std::cout << "    "s;
    };

    std::vector<int> v({ 1, 2, 3, });
    print(v);

    std::vector<int> destination(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));
    print(destination);

    std::reverse_copy(std::rbegin(v), std::rend(v), std::begin(destination));
    print(destination);

    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::rotate
   *  Performs a left rotation on a range of elements.
   *  Specifically, std::rotate swaps the elements in the range [first, last) in such a way that
   *  the element n_first becomes the first element of the new range and n_first - 1 becomes
   *  the last element.
   *
   *  std::rotate is a common building block in many algorithms. This example demonstrates
   *  insertion sort:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::rotate"s << '\n'
    << std::endl;
  {
    std::vector<int> vr { 2, 4, 2, 0, 5, 10, 7, 3, 7, 1, };

    std::cout << std::setw(24) << "before sort: "s;
    for (int n_ : vr) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';

    // insertion sort
    for (auto i_ = vr.begin(); i_ != vr.end(); ++i_) {
      std::rotate(std::upper_bound(vr.begin(), i_, *i_), i_, i_ + 1);
    }

    std::cout << std::setw(24) << "after sort: "s;
    for (int n_ : vr) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';

    // simple rotation to the left
    std::rotate(vr.begin(), vr.begin() + 1, vr.end());

    std::cout << std::setw(24) << "simple rotate left: "s;
    for (int n_ : vr) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';

    // simple rotation to the right
    std::rotate(vr.rbegin(), vr.rbegin() + 1, vr.rend());

    std::cout << std::setw(24) << "simple rotate right: "s;
    for (int n_ : vr) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::rotate_copy
   *  Copies the elements from the range [first, last), to another range beginning at d_first
   *  in such a way, that the element n_first becomes the first element of the new range and
   *  n_first - 1 becomes the last element.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::rotate_copy"s << '\n'
    << std::endl;
  {
    std::vector<int> src = { 1, 2, 3, 4, 5, };
    auto pivot = std::find(src.begin(), src.end(), 3);
    std::vector<int> dest(src.size());

    std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());

    for (const auto & i_ : dest) {
      std::cout << std::setw(4) << i_;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

#if __cplusplus >= 202000
  /*
   *  TODO: std::shift_left, std::shift_right
   *  Shifts the elements in the range [first, last) by n positions.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::shift_left, std::shift_right"s << '\n'
    << std::endl;
  {
    struct S {
      int value { 0 };
      bool specified_state { true };
   
      S(int v = 0) : value{v} {}
      S(S const & rhs) = default;
      S(S && rhs) { *this = std::move(rhs); }
      S & operator =(S const & rhs) = default;
      S & operator =(S && rhs) {
        if (this != &rhs) {
          value = rhs.value;
          specified_state = rhs.specified_state;
          rhs.specified_state = false;
        }
        return *this;
      }
    };

    std::ostream & operator <<(std::ostream & os, std::vector<S> const & v);

    std::vector<S> v {1, 2, 3, 4, 5, 6, 7, };
    std::cout << v;

    std::shift_left(v.begin(), v.end(), 3);
    std::cout << v;

    std::shift_right(v.begin(), v.end(), 2);
    std::cout << v;
  }
  std::cout << std::endl;
#endif

  /*
   *  TODO: std::random_shuffle, std::shuffle
   *  Reorders the elements in the given range [first, last) such that each possible permutation
   *  of those elements has equal probability of appearance.
   *
   *  The following code randomly shuffles the integers 1..10:
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::random_shuffle, std::shuffle"s << '\n'
    << std::endl;
  {
    std::vector<int> vs = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, };

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vs.begin(), vs.end(), g);

    std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n"s;
  }
  std::cout << std::endl;

  /*
   *  TODO: std::sample
   *  Selects n elements from the sequence [first; last) (without replacement) such that
   *  each possible sample has equal probability of appearance, and writes those selected
   *  elements into the output iterator out. Random numbers are generated using the random
   *  number generator g.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::sample"s << '\n'
    << std::endl;
  {
    std::string in = "hgfedcba"s, out;
    std::sample(in.begin(), in.end(), std::back_inserter(out),
                5, std::mt19937{std::random_device{}()});
    std::cout << "five random letters out of "s << in << " : "s << out << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::unique
   *  Eliminates all except the first element from every consecutive group of equivalent elements
   *  from the range [first, last) and returns a past-the-end iterator for the new logical end of
   *  the range.
   *  Removing is done by shifting the elements in the range in such a way that elements to be
   *  erased are overwritten. Relative order of the elements that remain is preserved and the
   *  physical size of the container is unchanged. Iterators pointing to an element between the
   *  new logical end and the physical end of the range are still dereferenceable, but the elements
   *  themselves have unspecified values. A call to unique is typically followed by a call to a
   *  container's erase method, which erases the unspecified values and reduces the physical size
   *  of the container to match its new logical size.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::unique"s << '\n'
    << std::endl;
  {
    // a vector containing several duplicate elements
    std::vector<int> v { 1, 2, 1, 1, 3, 3, 3, 4, 5, 4, };
 
    // remove consecutive (adjacent) duplicates
    auto last = std::unique(v.begin(), v.end());
    // v now holds {1 2 1 3 4 5 4 x x x}, where 'x' is indeterminate
    v.erase(last, v.end());
    for (int i : v) {
      std::cout << std::setw(4) << i;
    }
    std::cout << '\n';

    // sort followed by unique, to remove all duplicates
    std::sort(v.begin(), v.end()); // {1 1 2 3 4 4 5}
    last = std::unique(v.begin(), v.end());
    // v now holds {1 2 3 4 5 x x}, where 'x' is indeterminate
    v.erase(last, v.end());
    for (int i : v) {
      std::cout << std::setw(4) << i;
    }
    std::cout << "\n";
  }
  std::cout << std::endl;

  /*
   *  TODO: std::unique_copy
   *  Copies the elements from the range [first, last), to another range beginning at d_first
   *  in such a way that there are no consecutive equal elements. Only the first element of
   *  each group of equal elements is copied.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::unique_copy"s << '\n'
    << std::endl;
  {
    std::string s1 = "The      string    with many       spaces!"s;
    std::cout << "before: "s << s1 << '\n';

    std::string s2;
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
                     [](char c1, char c2){ return c1 == ' ' && c2 == ' '; });

    std::cout << "after:  "s << s2 << '\n';
  }
  std::cout << std::endl;

  return;
}
 
#if __cplusplus >= 202000
/*
 *  MARK: operator <<()
 */
std::ostream & operator <<(std::ostream & os, std::vector<S> const & v) {
  for (const auto & s : v) {
    s.specified_state ? os << s.value << ' ' : os << "? ";
  }
  return os << '\n';
}
#endif

/*
 *  MARK: f_sleep()
 */
inline
void f_sleep(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "thread " << n << " ended" << '\n';
}

/*
 *  MARK: f_gen()
 */
inline
int f_gen(void) {
  static int i = 1;
  return i++;
}

//  MARK: - Partitioning operations
/*
 *  MARK: fn_partitioning()
 *  + std::is_partitioned   determines if the range is partitioned by the given predicate
 *  + std::partition        divides a range of elements into two groups
 *  + std::partition_copy   copies a range dividing the elements into two groups
 *  + std::stable_partition divides elements into two groups while preserving their relative order
 *  + std::partition_point  locates the partition point of a partitioned range
 */
void fn_partitioning(void) {
  std::cout << "Function: "s << __func__ << std::endl;
  std::cout
    << "--------------------------------------------------------------------------------"s
    << '\n'
    << std::endl;
  
  /*
   *  TODO: std::is_partitioned
   *  Returns true if all elements in the range [first, last) that satisfy the predicate p
   *  appear before all elements that don't. Also returns true if [first, last) is empty.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_partitioned"s << '\n'
    << std::endl;
  {
    std::array<int, 9> ap = { 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    auto is_even = [](int i) { return i % 2 == 0; };
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(ap.begin(), ap.end(), is_even) << ' ';

    std::partition(ap.begin(), ap.end(), is_even);
    std::cout << std::is_partitioned(ap.begin(), ap.end(), is_even) << ' ';

    std::reverse(ap.begin(), ap.end());
    std::cout << std::is_partitioned(ap.cbegin(), ap.cend(), is_even) << ' ';
    std::cout << std::is_partitioned(ap.crbegin(), ap.crend(), is_even) << '\n';
    std::cout << '\n';

    auto pri = [](int i_){ std::cout << std::setw(4) << i_; };
    std::array<int, 9> ao = { 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    std::cout << "before partition:\n"s;
    std::for_each(ao.begin(), ao.end(), pri);
    std::cout << '\n';
    std::cout << "  is even?: "s;
    std::cout << std::is_partitioned(ap.begin(), ap.end(), is_even) << '\n';

    std::cout << "after partition:\n"s;
    std::partition(ao.begin(), ao.end(), is_even);
    std::for_each(ao.begin(), ao.end(), pri);
    std::cout << '\n';
    std::cout << "   is even?: "s;
    std::cout << std::is_partitioned(ao.cbegin(), ao.cend(), is_even) << '\n';

    std::cout << "after reverse:\n"s;
    std::reverse(ao.begin(), ao.end());
    std::for_each(ao.begin(), ao.end(), pri);
    std::cout << '\n';
    std::cout << "  is even?: "s;
    std::cout << std::is_partitioned(ao.cbegin(), ao.cend(), is_even) << '\n';

    std::cout << "with reverse iteretor\n"s;
    std::for_each(ao.crbegin(), ao.crend(), pri);
    std::cout << '\n';
    std::cout << "  is even?: "s;
    std::cout << std::is_partitioned(ao.crbegin(), ao.crend(), is_even) << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::partition
   *  Reorders the elements in the range [first, last) in such a way that all elements for
   *  which the predicate p returns true precede the elements for which predicate p returns
   *  false. Relative order of the elements is not preserved.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::partition"s << '\n'
    << std::endl;
  {
    std::vector<int> ov = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    std::cout << "Original vector:\n    "s;
    for(int elem : ov) {
      std::cout << std::setw(4) << elem;
    }

    auto it = std::partition(ov.begin(), ov.end(), [](int i){return i % 2 == 0;});

    std::cout << "\nPartitioned vector:\n    "s;
    std::copy(std::begin(ov), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * "s;
    std::copy(it, std::end(ov), std::ostream_iterator<int>(std::cout, " "));

    std::forward_list<int> fl = { 1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92, };
    std::cout << "\nUnsorted list:\n    "s;
    for (int n_ : fl) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';

    quicksort(std::begin(fl), std::end(fl));
    std::cout << "Sorted using quicksort:\n    "s;
    for (int fi : fl) {
      std::cout << std::setw(4) << fi;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::partition_copy
   *  Copies the elements from the range [first, last) to two different ranges depending on
   *  the value returned by the predicate p. The elements that satisfy the predicate p are
   *  copied to the range beginning at d_first_true. The rest of the elements are copied to
   *  the range beginning at d_first_false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::partition_copy"s << '\n'
    << std::endl;
  {
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, };
    int true_arr[5] = { 0 };
    int false_arr[5] = { 0 };

    std::partition_copy(std::begin(arr), std::end(arr), std::begin(true_arr), std::begin(false_arr),
                        [] (int i) { return i > 5; });

    std::cout << " true_arr: "s;
    for (int x : true_arr) {
      std::cout << std::setw(4) << x;
    }
    std::cout << '\n';

    std::cout << "false_arr: "s;
    for (int x : false_arr) {
      std::cout << std::setw(4) << x;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::stable_partition
   *  Reorders the elements in the range [first, last) in such a way that all elements
   *  for which the predicate p returns true precede the elements for which predicate p
   *  returns false. Relative order of the elements is preserved.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::stable_partition"s << '\n'
    << std::endl;
  {
    std::vector<int> vp { 0, 0, 3, 0, 2, 4, 5, 0, 7, };
    std::stable_partition(vp.begin(), vp.end(), [](int n){return n > 0;});
    for (int n_ : vp) {
      std::cout << std::setw(4) << n_;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::partition_point
   *  Examines the partitioned (as if by std::partition) range [first, last) and locates
   *  the end of the first partition, that is, the first element that does not satisfy p
   *  or last if all elements satisfy p.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::partition_point"s << '\n'
    << std::endl;
  {
    std::array<int, 9> vp = { 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    auto is_even = [](int i){ return i % 2 == 0; };
    std::partition(vp.begin(), vp.end(), is_even);

    auto par_pt = std::partition_point(vp.begin(), vp.end(), is_even);

    std::cout << "Before partition:\n    "s;
    std::copy(vp.begin(), par_pt, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter partition:\n    "s;
    std::copy(par_pt, vp.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
  }
  std::cout << std::endl;

  return;
}

//  MARK: - Sorting operations
/*
 *  MARK: fn_sorting()
 *  + std::is_sorted          checks whether a range is sorted into ascending order
 *  + std::is_sorted_until    finds the largest sorted subrange
 *  + std::sort               sorts a range into ascending order
 *  + std::partial_sort       sorts the first N elements of a range
 *  + std::partial_sort_copy  copies and partially sorts a range of elements
 *  + std::stable_sort        sorts a range of elements while preserving order between equal elements
 *  + std::nth_element        partially sorts the given range making sure that it is partitioned by
 *                            the given element
 */
void fn_sorting(void) {
  std::cout << "Function: "s << __func__ << std::endl;
  std::cout
    << "--------------------------------------------------------------------------------"s
    << '\n'
    << std::endl;

  /*
   *  TODO: std::is_sorted
   *  Checks if the elements in range [first, last) are sorted in non-descending order.
   *  A sequence is sorted with respect to a comparator comp if for any iterator it
   *  pointing to the sequence and any non-negative integer n such that it + n is a
   *  valid iterator pointing to an element of the sequence, comp(*(it + n), *it)
   *  evaluates to false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_sorted"s << '\n'
    << std::endl;
  {
    int digits[] = { 3, 1, 4, 1, 5, };

    for (auto i_ : digits) {
      std::cout << std::setw(4) << i_;
    }
    std::cout << ": is_sorted: " << std::boolalpha
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';

    std::sort(std::begin(digits), std::end(digits));

    for (auto i_ : digits) {
      std::cout << std::setw(4) << i_;
    }
    std::cout << ": is_sorted: "
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::is_sorted_until
   *  Examines the range [first, last) and finds the largest range beginning at first in which
   *  the elements are sorted in non-descending order.
   *  A sequence is sorted with respect to a comparator comp if for any iterator it pointing to
   *  the sequence and any non-negative integer n such that it + n is a valid iterator pointing
   *  to an element of the sequence, comp(*(it + n), *it) evaluates to false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_sorted_until"s << '\n'
    << std::endl;
  {
    std::random_device rd;
    std::mt19937 g(rd());
    const int N = 6;
    int nums[N] = { 3, 1, 4, 1, 5, 9, };
 
    const int min_sorted_size = 4;
    long sorted_size = 0;
    do {
      std::shuffle(nums, nums + N, g);
      int * sorted_end = std::is_sorted_until(nums, nums + N);
      sorted_size = std::distance(nums, sorted_end);

      for (auto i : nums) std::cout << std::setw(3) << i;
      std::cout << " : " << sorted_size << " initial sorted elements\n"s;
    } while (sorted_size < min_sorted_size);
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::sort
   *  Sorts the elements in the range [first, last) in non-descending order. The order of equal
   *  elements is not guaranteed to be preserved.
   *  A sequence is sorted with respect to a comparator comp if for any iterator it pointing to
   *  the sequence and any non-negative integer n such that it + n is a valid iterator pointing
   *  to an element of the sequence, comp(*(it + n), *it) (or *(it + n) < *it) evaluates to false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::sort"s << '\n'
    << std::endl;
  {
    auto print = [](int i_) { std::cout << std::setw(3) << i_; };

    std::array<int, 10> sa = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3, };
    std::for_each(sa.begin(), sa.end(), print);
//    for (auto a_ : sa) {
//      std::cout << std::setw(4) << a_;
//    }
    std::cout << '\n';

    // sort using the default operator<
    std::sort(sa.begin(), sa.end());
    std::for_each(sa.begin(), sa.end(), print);
//    for (auto a_ : sa) {
//      std::cout << std::setw(4) << a_;
//    }
    std::cout << '\n';

    // sort using a standard library compare function object
    std::sort(sa.begin(), sa.end(), std::greater<int>());
    std::for_each(sa.begin(), sa.end(), print);
//    for (auto a_ : sa) {
//      std::cout << std::setw(4) << a_;
//    }
    std::cout << '\n';

    // sort using a custom function object
    struct {
      bool operator ()(int a_, int b) const { return a_ < b; }
    } customLess;
    std::sort(sa.begin(), sa.end(), customLess);
    std::for_each(sa.begin(), sa.end(), print);
//    for (auto a_ : sa) {
//      std::cout << std::setw(4) << a_;
//    }
    std::cout << '\n';

    // sort using a lambda expression
    std::sort(sa.begin(), sa.end(), [](int a, int b) { return a > b; });
    std::for_each(sa.begin(), sa.end(), print);
//    for (auto a_ : sa) {
//      std::cout << std::setw(4) << a_;
//    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::partial_sort
   *  Rearranges elements such that the range [first, middle) contains the sorted middle - first
   *  smallest elements in the range [first, last).
   *  The order of equal elements is not guaranteed to be preserved. The order of the remaining
   *  elements in the range [middle, last) is unspecified.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::partial_sort"s << '\n'
    << std::endl;
  {
    auto print = [](int a_){ std::cout << std::setw(3) << a_; };

    std::array<int, 10> sa { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3, };
    std::array<int, 10> sb;
    std::copy(sa.begin(), sa.end(), sb.begin());
    std::for_each(sa.begin(), sa.end(), print);
    std::cout << '\n';

    std::partial_sort(sa.begin(), sa.begin() + 3, sa.end());
    std::for_each(sa.begin(), sa.end(), print);
    std::cout << '\n';
//    for (int a : sa) {
//      std::cout << a << " ";
//    }
    
    std::partial_sort(sb.begin(), sb.begin() + 3, sb.end(), [](int a, int b) { return a > b; });
    std::for_each(sb.begin(), sb.end(), print);
    std::cout << '\n';

    std::partial_sort(sa.begin(), sa.begin() + 3, sa.end(), [](int a, int b) { return a > b; });
    std::for_each(sa.begin(), sa.end(), print);
    std::cout << '\n';

    std::partial_sort(sb.begin(), sb.begin() + 3, sb.end(), [](int a, int b) { return a < b; });
    std::for_each(sb.begin(), sb.end(), print);
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::partial_sort_copy
   *  Sorts some of the elements in the range [first, last) in ascending order, storing the result
   *  in the range [d_first, d_last).
   *  At most d_last - d_first of the elements are placed sorted to the range [d_first, d_first + n).
   *  n is the number of elements to sort (n = min(last - first, d_last - d_first)). The order of
   *  equal elements is not guaranteed to be preserved.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::partial_sort_copy"s << '\n'
    << std::endl;
  {
    auto print = [](int a_) { std::cout << std::setw(3) << a_; };

    std::vector<int> v0 {  4,  2,  5,  1,  3, };
    std::vector<int> v1 { 10, 11, 12, };
    std::vector<int> v2 { 10, 11, 12, 13, 14, 15, 16, };
    std::vector<int>::iterator it;

    std::cout << "v0: "s;
    std::for_each(v0.begin(), v0.end(), print);
    std::cout << '\n';
    std::cout << "v1: "s;
    std::for_each(v1.begin(), v1.end(), print);
    std::cout << '\n';
    std::cout << "v2: "s;
    std::for_each(v2.begin(), v2.end(), print);
    std::cout << '\n'
              << '\n';

    it = std::partial_sort_copy(v0.begin(), v0.end(), v1.begin(), v1.end());

    std::cout << "Writing to the smaller vector in ascending order gives: "s;
    std::for_each(v1.begin(), v1.end(), print);
//    for (int a : v1) {
//        std::cout << a << " ";
//    }
    std::cout << '\n';
    if (it == v1.end()) {
      std::cout << "The return value is the end iterator\n"s;
    }

    it = std::partial_sort_copy(v0.begin(), v0.end(), v2.begin(), v2.end(),
                                std::greater<int>());

    std::cout << "Writing to the larger vector in descending order gives: "s;
    std::for_each(v2.begin(), v2.end(), print);
//    for (int a : v2) {
//        std::cout << a << " ";
//    }
    std::cout << '\n';
    std::cout << "The return value is the iterator to "s << *it << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::stable_sort
   *  Sorts the elements in the range [first, last) in non-descending order. The order of
   *  equivalent elements is guaranteed to be preserved.
   *  A sequence is sorted with respect to a comparator comp if for any iterator it pointing
   *  to the sequence and any non-negative integer n such that it + n is a valid iterator
   *  pointing to an element of the sequence, comp(*(it + n), *it) (or *(it + n) < *it)
   *  evaluates to false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::stable_sort"s << '\n'
    << std::endl;
  {
    /*
     *  MARK Structure Employee
     */
    struct Employee {
      int age;
      std::string name;  // Does not participate in comparisons

      bool operator <(Employee const & rhs) const {
          return age < rhs.age;
      }
    };
    
    std::vector<Employee> ve = {
      { 108, "Zaphod", },
      {  32, "Arthur", },
      { 108, "Ford", },
    };

    auto emp_print = [](Employee const & e_) {
      std::cout << std::setw(4) << e_.age
                << std::setw(10) << e_.name
                << '\n';
    };

    std::for_each(ve.begin(), ve.end(), emp_print);

    std::stable_sort(ve.begin(), ve.end());

//    for (const Employee & e : v)
//      std::cout << e.age << ", " << e.name << '\n';
    std::for_each(ve.begin(), ve.end(), emp_print);
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::nth_element
   *  nth_element is a partial sorting algorithm that rearranges elements in [first, last) such that:
   *  + The element pointed at by nth is changed to whatever element would occur in that position
   *    if [first, last) were sorted.
   *  + All of the elements before this new nth element are less than or equal to the elements after
   *    the new nth element.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::nth_element"s << '\n'
    << std::endl;
  {
    auto print = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vs { 5, 6, 4, 3, 2, 6, 7, 9, 3, };

    std::cout << std::setw(20) << "before sort: "s;
    std::for_each(vs.begin(), vs.end(), print);
    std::cout << '\n';
    
    std::nth_element(vs.begin(), vs.begin() + vs.size() / 2, vs.end());
    std::cout << std::setw(20) << "after 1st sort: "s;
    std::for_each(vs.begin(), vs.end(), print);
    std::cout << '\n';
    std::cout << "The median is " << vs[vs.size() / 2] << '\n';

    std::nth_element(vs.begin(), vs.begin() + 1, vs.end(), std::greater<int>());
    std::cout << std::setw(20) << "after 2nd sort: "s;
    std::for_each(vs.begin(), vs.end(), print);
    std::cout << '\n';
    std::cout << "The second largest element is "s << vs[1] << '\n';
  }
  std::cout << std::endl;

  return;
}

//  MARK: - Binary search operations (on sorted ranges)
/*
 *  MARK: fn_bin_search()
 *  + std::lower_bound    returns an iterator to the first element not less than the given value
 *  + std::upper_bound    returns an iterator to the first element greater than a certain value
 *  + std::binary_search  determines if an element exists in a certain range
 *  + std::equal_range    returns range of elements matching a specific key
 */
void fn_bin_search(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;
  
  /*
   *  TODO: std::lower_bound
   *  Returns an iterator pointing to the first element in the range [first, last) that is not
   *  less than (i.e. greater or equal to) value, or last if no such element is found.
   *  The range [first, last) must be partitioned with respect to the expression element < value
   *  or comp(element, value), i.e., all elements for which the expression is true must precede
   *  all elements for which the expression is false. A fully-sorted range meets this criterion.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::lower_bound"s << '\n'
    << std::endl;
  {
    std::vector<int> data = { 1, 2, 4, 5, 5, 6, };

    for (int i_ = 0; i_ < 8; ++i_) {
      // Search for first element that is not less than i
      auto lower = std::lower_bound(data.begin(), data.end(), i_);

      std::cout << i_ << " <= "s;
      if (lower != data.end()) {
        std::cout << *lower << " at index "s << std::distance(data.begin(), lower);
      }
      else {
        std::cout << "not found"s;
      }
      std::cout << '\n';
    }
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::upper_bound
   *  Returns an iterator pointing to the first element in the range [first, last) that is greater
   *  than value, or last if no such element is found.
   *  The range [first, last) must be partitioned with respect to the expression !(value < element)
   *  or !comp(value, element), i.e., all elements for which the expression is true must precede all
   *  elements for which the expression is false. A fully-sorted range meets this criterion.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::upper_bound"s << '\n'
    << std::endl;
  {
    std::vector<int> data = { 1, 2, 4, 5, 5, 6, };

    for (int i = 0; i < 7; ++i) {
      // Search first element that is greater than i
      auto upper = std::upper_bound(data.begin(), data.end(), i);

      std::cout << i << " < "s;
      if (upper != data.end()) {
        std::cout << *upper << " at index "s << std::distance(data.begin(), upper);
      }
      else {
        std::cout << "not found"s;
      }
      std::cout << '\n';
    }
  }

  std::cout << std::endl;
  
  /*
   *  TODO: std::binary_search
   *  Checks if an element equivalent to value appears within the range [first, last).
   *  For std::binary_search to succeed, the range [first, last) must be at least partially
   *  ordered with respect to value, i.e. it must satisfy all of the following requirements:
   *  + partitioned with respect to element < value or comp(element, value) (that is, all
   *    elements for which the expression is true precedes all elements for which the
   *    expression is false)
   *  + partitioned with respect to !(value < element) or !comp(value, element)
   *  + for all elements, if element < value or comp(element, value) is true then
   *    !(value < element) or !comp(value, element) is also true
   *  A fully-sorted range meets these criteria.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::binary_search"s << '\n'
    << std::endl;
  {
    std::vector<int> haystack { 1, 3, 4, 5, 9, };
    std::vector<int> needles { 1, 2, 3, };

    for (auto needle : needles) {
      std::cout << "Searching for "s << needle << '\n';
      if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
        std::cout << "Found "s << needle << '\n';
      }
      else {
        std::cout << "no dice!\n"s;
      }
    }
    std::cout << '\n';

    for (auto needle : needles) {
      std::cout << "Searching for "s << needle << '\n';
      if (std::binary_search(haystack.begin(), haystack.end(), needle,
                             [](int a_, int b_) { return a_ > b_; })) {
        std::cout << "Found "s << needle << '\n';
      }
      else {
        std::cout << "no dice!\n"s;
      }
    }
    std::cout << '\n';

    for (auto needle : needles) {
      std::cout << "Searching for "s << needle << '\n';
      if (std::binary_search(haystack.crbegin(), haystack.crend(), needle,
                             [](int a_, int b_) { return a_ > b_; })) {
        std::cout << "Found "s << needle << '\n';
      }
      else {
        std::cout << "no dice!\n"s;
      }
    }
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::equal_range
   *  Returns a range containing all elements equivalent to value in the range [first, last).
   *  The range [first, last) must be at least partially ordered with respect to value,
   *  i.e. it must satisfy all of the following requirements:
   *  +`partitioned with respect to element < value or comp(element, value) (that is, all
   *    elements for which the expression is true precedes all elements for which the expression
   *    is false)
   *  + partitioned with respect to !(value < element) or !comp(value, element)
   *  + for all elements, if element < value or comp(element, value) is true then !(value < element)
   *    or !comp(value, element) is also true
   *  A fully-sorted range meets these criteria.
   *  The returned range is defined by two iterators, one pointing to the first element that is
   *  not less than value and another pointing to the first element greater than value. The first
   *  iterator may be alternatively obtained with std::lower_bound(), the second - with
   *  std::upper_bound().
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::equal_range"s << '\n'
    << std::endl;
  {
    struct S {
      int number;
      char name;
      // note: name is ignored by this comparison operator
      bool operator< (S const & s) const { return number < s.number; }
    };

    // note: not ordered, only partitioned w.r.t. S defined below
    std::vector<S> vec = {
      { 1, 'A', }, { 2, 'B', }, { 2, 'C', }, { 2, 'D', }, { 4, 'G', }, { 3, 'F', }
    };

    S value = { 2, '?', };

    auto p = std::equal_range(vec.begin(), vec.end(), value);

    for (auto i = p.first; i != p.second; ++i) {
      std::cout << i->name << ' ';
    }
    std::cout << '\n';

    // heterogeneous comparison:
    struct Comp {
      bool operator() ( const S& s, int i ) const { return s.number < i; }
      bool operator() ( int i, const S& s ) const { return i < s.number; }
    };

    auto p2 = std::equal_range(vec.begin(),vec.end(), 2, Comp{});

    for (auto i = p2.first; i != p2.second; ++i) {
      std::cout << i->name << ' ';
    }
  }
  std::cout << std::endl;

  return;
}

//  MARK: - Other operations on sorted ranges
/*
 *  MARK: fn_sort_ops()
 *  + std::merge          merges two sorted ranges
 *  + std::inplace_merge  merges two ordered ranges in-place
 */
void fn_sort_ops(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::merge
   *  Merges two sorted ranges [first1, last1) and [first2, last2) into one sorted range beginning
   *  at d_first.
   *  A sequence is said to be sorted with respect to a comparator comp if for any iterator it
   *  pointing to the sequence and any non-negative integer n such that it + n is a valid iterator
   *  pointing to an element of the sequence, comp(*(it + n), *it) evaluates to false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::merge"s << '\n'
    << std::endl;
  {
    // fill the vectors with random numbers
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 9);

    std::vector<int> v1(10), v2(10);
    std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
    std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));

    // sort
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    // output v1
    std::cout << "v1 : "s;
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // output v2
    std::cout << "v2 : "s;
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // merge
    std::vector<int> dst;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));

    // output
    std::cout << "dst: "s;
    std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::inplace_merge
   *  Merges two consecutive sorted ranges [first, middle) and [middle, last) into one sorted range
   *  [first, last).
   *  A sequence [first, last) is said to be sorted with respect to a comparator comp if for any
   *  iterator it pointing to the sequence and any non-negative integer n such that it + n is a
   *  valid iterator pointing to an element of the sequence, comp(*(it + n), *it) evaluates to false.
   *  This merge is stable, which means that for equivalent elements in the original two ranges, the
   *  elements from the first range (preserving their original order) precede the elements from the
   *  second range (preserving their original order).
   *
   *  The following code is an implementation of merge sort.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::inplace_merge"s << '\n'
    << std::endl;
  {
    auto prt = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vs { 8, 2, -2, 0, 11, 11, 1, 7, 3, };
    std::for_each(vs.begin(), vs.end(), prt);
    std::cout << '\n';

    merge_sort(vs.begin(), vs.end());

    std::for_each(vs.begin(), vs.end(), prt);
//    for(auto n_ : vs) {
//      std::cout << std::setw(3) << n_;
//    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  return;
}
  
//  MARK: - Set operations (on sorted ranges)
/*
 *  MARK: fn_set_ops()
 *  + std::includes                 returns true if one sequence is a subsequence of another
 *  + std::set_difference           computes the difference between two sets
 *  + std::set_intersection         computes the intersection of two sets
 *  + std::set_symmetric_difference computes the symmetric difference between two sets
 *  + std::set_union                computes the union of two sets
 */
void fn_set_ops(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::includes
   *  Returns true if the sorted range [first2, last2) is a subsequence of the sorted
   *  range [first1, last1). (A subsequence need not be contiguous.)
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::includes"s << '\n'
    << std::endl;
  {
    auto const
      v1 = { 'a', 'b', 'c', 'f', 'h', 'x', },
      v2 = { 'a', 'b', 'c', },
      v3 = { 'a', 'c', },
      v4 = { 'a', 'a', 'b', },
      v5 = { 'g', },
      v6 = { 'a', 'c', 'g', },
      v7 = { 'A', 'B', 'C', };

    auto no_case = [](char a, char b) { return std::tolower(a) < std::tolower(b); };

    std::cout
      << v1 << "\nincludes:\n"s << std::boolalpha
      << v2 << ": "s << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n'
      << v3 << ": "s << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n'
      << v4 << ": "s << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n'
      << v5 << ": "s << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n'
      << v6 << ": "s << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end()) << '\n'
      << v7 << ": "s << std::includes(v1.begin(), v1.end(), v7.begin(), v7.end(), no_case)
            << " (case-insensitive)\n"s;
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::set_difference
   *  Copies the elements from the sorted range [first1, last1) which are not found in the
   *  sorted range [first2, last2) to the range beginning at d_first.
   *  The resulting range is also sorted. Equivalent elements are treated individually, that
   *  is, if some element is found m times in [first1, last1) and n times in [first2, last2),
   *  it will be copied to d_first exactly std::max(m-n, 0) times. The resulting range cannot
   *  overlap with either of the input ranges.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::set_difference"s << '\n'
    << std::endl;
  {
    std::vector<int> v1 { 1, 2, 5, 5, 5, 9, };
    std::vector<int> v2 { 2, 5, 7, };
    std::vector<int> diff;

    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::inserter(diff, diff.begin()));

    for (auto i : v1) {
      std::cout << i << ' ';
    }
    std::cout << "minus ";
    for (auto i : v2) {
      std::cout << i << ' ';
    }
    std::cout << "is: ";
    for (auto i : diff) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::set_intersection
   *  Constructs a sorted range beginning at d_first consisting of elements that are found
   *  in both sorted ranges [first1, last1) and [first2, last2). If some element is found
   *  m times in [first1, last1) and n times in [first2, last2), the first std::min(m, n)
   *  elements will be copied from the first range to the destination range. The order of
   *  equivalent elements is preserved. The resulting range cannot overlap with either of
   *  the input ranges.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::set_intersection"s << '\n'
    << std::endl;
  {
      std::vector<int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, };
      std::vector<int> v2 {             5,    7,    9, 10, };
      std::sort(v1.begin(), v1.end());
      std::sort(v2.begin(), v2.end());

      std::vector<int> v_intersection;

      std::set_intersection(v1.begin(), v1.end(),
                            v2.begin(), v2.end(),
                            std::back_inserter(v_intersection));
    for (int n : v_intersection) {
      std::cout << n << ' ';
    }
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::set_symmetric_difference
   *  Computes symmetric difference of two sorted ranges: the elements that are found in either
   *  of the ranges, but not in both of them are copied to the range beginning at d_first. The
   *  resulting range is also sorted.
   *  If some element is found m times in [first1, last1) and n times in [first2, last2), it will
   *  be copied to d_first exactly std::abs(m-n) times. If m>n, then the last m-n of those elements
   *  are copied from [first1,last1), otherwise the last n-m elements are copied from [first2,last2).
   *  The resulting range cannot overlap with either of the input ranges.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::set_symmetric_difference"s << '\n'
    << std::endl;
  {
    std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8         };
    std::vector<int> v2{             5,    7,    9, 10, };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> v_symDifference;

    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference));

    for (int n : v_symDifference) {
      std::cout << n << ' ';
    }
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::set_union
   *  Constructs a sorted union beginning at d_first consisting of the set of elements present
   *  in one or both sorted ranges [first1, last1) and [first2, last2).
   *  If some element is found m times in [first1, last1) and n times in [first2, last2), then
   *  all m elements will be copied from [first1, last1) to d_first, preserving order, and then
   *  exactly std::max(n-m, 0) elements will be copied from [first2, last2) to d_first, also
   *  preserving order.
   *  The resulting range cannot overlap with either of the input ranges.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::set_union"s << '\n'
    << std::endl;
  {
    {
      std::vector<int> v1 = { 1, 2, 3, 4, 5, };
      std::vector<int> v2 = {       3, 4, 5, 6, 7, };
      std::vector<int> dest1;

      std::set_union(v1.begin(), v1.end(),
                     v2.begin(), v2.end(),
                     std::back_inserter(dest1));

      for (const auto & i : dest1) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }
    {
      std::vector<int> v1 = { 1, 2, 3, 4, 5, 5, 5, };
      std::vector<int> v2 = {       3, 4, 5,       6, 7, };
      std::vector<int> dest1;

      std::set_union(v1.begin(), v1.end(),
                     v2.begin(), v2.end(),
                     std::back_inserter(dest1));

      for (const auto & i : dest1) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }
  }
  std::cout << std::endl;

  return;
}

//  MARK: - Heap operations
/*
 *  MARK: fn_heap_ops()
 *  + std::is_heap        checks if the given range is a max heap
 *  + std::is_heap_until  finds the largest subrange that is a max heap
 *  + std::make_heap      creates a max heap out of a range of elements
 *  + std::push_heap      adds an element to a max heap
 *  + std::pop_heap       removes the largest element from a max heap
 *  + std::sort_heap      turns a max heap into a range of elements sorted in ascending order
 */
void fn_heap_ops(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::is_heap
   *  Checks if the elements in range [first, last) are a max heap.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_heap"s << '\n'
    << std::endl;
  {
    std::vector<int> vh { 3, 1, 4, 1, 5, 9, };

    std::cout << "initially, vh: "s;
    for (auto i : vh) {
      std::cout << std::setw(3) << i;
    }
    std::cout << '\n';

    if (!std::is_heap(vh.begin(), vh.end())) {
      std::cout << "making heap...\n"s;
      std::make_heap(vh.begin(), vh.end());
    }

    std::cout << "after make_heap, vh: "s;
    for (auto i : vh) {
      std::cout << std::setw(3) << i;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::is_heap_until
   *  Examines the range [first, last) and finds the largest range beginning at first which
   *  is a max heap.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_heap_until"s << '\n'
    << std::endl;
  {
    std::vector<int> vh { 3, 1, 4, 1, 5, 9, };

    std::make_heap(vh.begin(), vh.end());

    // probably mess up the heap
    vh.push_back(2);
    vh.push_back(6);

    auto heap_end = std::is_heap_until(vh.begin(), vh.end());

    std::cout << "all of vh: ";
    for (auto i : vh) {
      std::cout << std::setw(3) << i;
    }
    std::cout << '\n';

    std::cout << "only heap: ";
    for (auto i = vh.begin(); i != heap_end; ++i) {
      std::cout << std::setw(3) << *i;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::make_heap
   *  Constructs a max heap in the range [first, last). The first version of the function
   *  uses operator< to compare the elements, the second uses the given comparison function
   *  comp.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::make_heap"s << '\n'
    << std::endl;
  {
    std::cout << "Max heap:\n"s;

    auto printvec = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vh { 3, 2, 4, 1, 5, 9, };

    std::cout << std::setw(45) << "initially, vh: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    std::make_heap(vh.begin(), vh.end());

    std::cout << std::setw(45) << "after make_heap, vh: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    std::pop_heap(vh.begin(), vh.end());

    std::cout << std::setw(45) << "after pop_heap, vh: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    auto top = vh.back();
    vh.pop_back();
    std::cout << std::setw(45) << "former top element: "s << std::setw(3) << top << '\n';

    std::cout << std::setw(45) << "after removing the former top element, vh: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n' << '\n';

    std::cout << "Min heap:\n"s;

    std::vector<int> v1 { 3, 2, 4, 1, 5, 9, };

    std::cout << std::setw(45) << "initially, v1: "s;
    std::for_each(v1.begin(), v1.end(), printvec);
    std::cout << '\n';

    std::make_heap(v1.begin(), v1.end(), std::greater<>{});

    std::cout << std::setw(45) << "after make_heap, v1: "s;
    std::for_each(v1.begin(), v1.end(), printvec);
    std::cout << '\n';

    std::pop_heap(v1.begin(), v1.end(), std::greater<>{});

    std::cout << std::setw(45) << "after pop_heap, v1: "s;
    std::for_each(v1.begin(), v1.end(), printvec);
    std::cout << '\n';

    auto top1 = v1.back();
    v1.pop_back();
    std::cout << std::setw(45) << "former top element: "s << std::setw(3) << top1 << '\n';

    std::cout << std::setw(45) << "after removing the former top element, v1: "s;
    std::for_each(v1.begin(), v1.end(), printvec);
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::push_heap
   *  Inserts the element at the position last-1 into the max heap defined by the range
   *  [first, last-1). The first version of the function uses operator< to compare the
   *  elements, the second uses the given comparison function comp.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::push_heap"s << '\n'
    << std::endl;
  {
    auto printvec = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vh { 3, 1, 4, 1, 5, 9, };

    std::make_heap(vh.begin(), vh.end());

    std::cout << "vh: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    vh.push_back(6);

    std::cout << "before push_heap: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    std::push_heap(vh.begin(), vh.end());

    std::cout << " after push_heap: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::pop_heap
   *  Swaps the value in the position first and the value in the position last-1 and makes
   *  the subrange [first, last-1) into a heap. This has the effect of removing the first
   *  element from the heap defined by the range [first, last).
   *  The first version of the function uses operator< to compare the elements, which makes
   *  the heap a max heap. The second uses the given comparison function comp.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::pop_heap"s << '\n'
    << std::endl;
  {
    auto printvec = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vh { 3, 1, 4, 1, 5, 9, };

    std::make_heap(vh.begin(), vh.end());

    std::cout << "v: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    std::pop_heap(vh.begin(), vh.end()); // moves the largest to the end

    std::cout << "after pop_heap: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    int largest = vh.back();
    vh.pop_back();  // actually removes the largest element
    std::cout << "largest element: "s << largest << '\n';

    std::cout << "heap without largest: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::sort_heap
   *  Converts the max heap [first, last) into a sorted range in ascending order. The resulting
   *  range no longer has the heap property.
   *  The first version of the function uses operator< to compare the elements, the second uses
   *  the given comparison function comp.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::sort_heap"s << '\n'
    << std::endl;
  {
    auto printvec = [](int i_) { std::cout << std::setw(3) << i_; };

    std::vector<int> vh = { 3, 1, 4, 1, 5, 9, };

    std::make_heap(vh.begin(), vh.end());

    std::cout << "  heap: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';

    std::sort_heap(vh.begin(), vh.end());

    std::cout << "sorted: "s;
    std::for_each(vh.begin(), vh.end(), printvec);
    std::cout << '\n';
  }
  std::cout << std::endl;

  return;
}

//  MARK: - Minimum/maximum operations
/*
 *  MARK: fn_min_max()
 *  + std::max            returns the greater of the given values
 *  + std::max_element    returns the largest element in a range
 *  + std::min            returns the smaller of the given values
 *  + std::min_element    returns the smallest element in a range
 *  + std::minmax         returns the smaller and larger of two elements
 *  + std::minmax_element returns the smallest and the largest elements in a range
 *  + std::clamp          clamps a value between a pair of boundary values
 */
void fn_min_max(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::max
   *  Returns the greater of the given values.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::max"s << '\n'
    << std::endl;
  {
    std::cout << "larger of 1 and 9999 is " << std::max(1, 9999) << '\n'
              << "larger of 'a', and 'b' is '" << std::max('a', 'b') << "'\n"
              << "longest of \"foo\", \"bar\", and \"hello\" is \""
              << std::max({ "foo", "bar", "hello" },
                          [](const std::string_view s1, const std::string_view s2) {
                              return s1.size() < s2.size();
                          }) << "\"\n";
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::max_element
   *  Finds the greatest element in the range [first, last).
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::max_element"s << '\n'
    << std::endl;
  {
    bool abs_compare(int a, int b);

    std::vector<int> vm { 3, 1, -14, 1, 5, 9, };
    std::vector<int>::iterator result;

    result = std::max_element(vm.begin(), vm.end());
    std::cout << "max element at: " << std::distance(vm.begin(), result) << '\n';

    result = std::max_element(vm.begin(), vm.end(), abs_compare);
    std::cout << "max element (absolute) at: " << std::distance(vm.begin(), result) << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::min
   *  Returns the smaller of the given values.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::min"s << '\n'
    << std::endl;
  {
    std::cout << "smaller of 1 and 9999 is " << std::min(1, 9999) << '\n'
              << "smaller of 'a', and 'b' is '" << std::min('a', 'b') << "'\n"
              << "shortest of \"foo\", \"bar\", and \"hello\" is \""
              << std::min({ "foo", "bar", "hello" },
                          [](const std::string_view s1, const std::string_view s2) {
                              return s1.size() < s2.size();
                          }) << "\"\n";
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::min_element
   *  Finds the smallest element in the range [first, last).
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::min_element"s << '\n'
    << std::endl;
  {
    std::vector<int> vm { 3, 1, 4, 1, 5, 9, };

    std::vector<int>::iterator result = std::min_element(vm.begin(), vm.end());
    std::cout << "min element at: " << std::distance(vm.begin(), result);
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::minmax
   *  Returns the lowest and the greatest of the given values.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::minmax"s << '\n'
    << std::endl;
  {
    std::vector<int> vm { 3, 1, 4, 1, 5, 9, 2, 6, };
    std::cout << "vm["s << 0 << ","s << vm.size() - 1 << "]: "s;
    std::for_each(vm.begin(), vm.end(), [](int i_) {
      std::cout << std::setw(3) << i_;
    });
    std::cout << '\n';

    std::srand(static_cast<unsigned>(std::time(0)));
    std::pair<int, int> bounds = std::minmax(std::rand() % vm.size(),
                                             std::rand() % vm.size());

    std::cout << "vm["s << bounds.first << ","s << bounds.second << "]: "s;
    for (int i = bounds.first; i < bounds.second; ++i) {
      std::cout << std::setw(3) << vm[i];
    }
    std::cout << '\n';
//    std::for_each(vm[bounds.first], vm[bounds.second], [](int i_) {
//      std::cout << std::setw(3) << i_;
//    });
//    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::minmax_element
   *  Finds the smallest and greatest element in the range [first, last).
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::minmax_element"s << '\n'
    << std::endl;
  {
    const auto vm = { 3, 9, 1, 4, 2, 5, 9, };

    std::cout << "vm["s << 0 << ","s << vm.size() - 1 << "]: "s;
    std::for_each(vm.begin(), vm.end(), [](int i_) {
      std::cout << std::setw(3) << i_;
    });
    std::cout << '\n';

    const auto [min, max] = std::minmax_element(begin(vm), end(vm));

    std::cout << "min = " << *min << ", max = " << *max << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::clamp
   *  If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi;
   *  otherwise returns v
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::clamp"s << '\n'
    << std::endl;
  {
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<> d(-300, 300);
    std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
    for(int n = 0; n < 5; ++n) {
        int v = d(g);
        std::cout << std::setw(4) << v
                  << std::setw(20) << std::clamp(v, INT8_MIN, INT8_MAX)
                  << std::setw(21) << std::clamp(v, 0, UINT8_MAX) << '\n';
    }
  }
  std::cout << std::endl;

  return;
}

/*
 *  MARK: abs_compare
 */
inline
bool abs_compare(int a, int b) {
  return (std::abs(a) < std::abs(b));
}

//  MARK: - Comparison operations
/*
 *  MARK: fn_compare_ops()
 *  + std::equal  determines                  if two sets of elements are the same
 *  + std::lexicographical_compare            returns true if one range is lexicographically
 *                                            less than another
 *  + std::lexicographical_compare_three_way  compares two ranges using three-way comparison (C++20)
 */
void fn_compare_ops(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::equal
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::equal"s << '\n'
    << std::endl;
  {
    bool is_palindrome(std::string const & s_);

    std::vector<std::string> tests { "radar"s, "hello"s };
    for (auto test : tests) {
      std::cout << "\"" << test << "\" "
                << (is_palindrome(test) ? "is" : "is not")
                << " a palindrome\n";
    }
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::lexicographical_compare
   *  Checks if the first range [first1, last1) is lexicographically less than the second
   *  range [first2, last2)
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::lexicographical_compare"s << '\n'
    << std::endl;
  {
    auto printvec = [](char c_) { std::cout << std::left << std::setw(2) << c_; };

    std::vector<char> v1 { 'a', 'b', 'c', 'd', 'e', 'f', };
    std::vector<char> v2 { 'a', 'b', 'c', 'd', 'e', 'f', };

    std::mt19937 rg{std::random_device{}()};
    while (!std::lexicographical_compare(v1.begin(), v1.end(),
                                         v2.begin(), v2.end())) {
//      for (auto c : v1) std::cout << c << ' ';
      std::for_each(v1.begin(), v1.end(), printvec);
      std::cout << ">= ";
//      for (auto c : v2) std::cout << c << ' ';
      std::for_each(v2.begin(), v2.end(), printvec);
      std::cout << '\n';

      std::shuffle(v1.begin(), v1.end(), rg);
      std::shuffle(v2.begin(), v2.end(), rg);
    }

//    for (auto c : v1) std::cout << c << ' ';
    std::for_each(v1.begin(), v1.end(), printvec);
    std::cout << "<  ";
//    for (auto c : v2) std::cout << c << ' ';
    std::for_each(v2.begin(), v2.end(), printvec);
    std::cout << '\n';
  }
  std::cout << std::endl;

  /*
   *  TODO: std::lexicographical_compare_three_way
   *  C++20
   *  Lexicographically compares two ranges [first1, last1) and [first2, last2) using three-way
   *  comparison and produces a result of the strongest applicable comparison category type.
   */
//  std::cout
//    << "................................................................................"s
//    << '\n'
//    << "std::lexicographical_compare_three_way"s << '\n'
//    << std::endl;
//
//  std::cout << std::endl;

  return;
}

/*
 *  MARK: is_palindrome()
 */
inline
bool is_palindrome(const std::string & s_) {
    return std::equal(s_.begin(), s_.begin() + s_.size() / 2, s_.rbegin());
}

//  MARK: - Permutation operations
/*
 8  MARK: fn_permutation_ops()
 *  + std::is_permutation   determines if a sequence is a permutation of another sequence
 *  + std::next_permutation generates the next greater lexicographic permutation of a range of elements
 *  + std::prev_permutation generates the next smaller lexicographic permutation of a range of elements
 */
void fn_permutation_ops(void) {
std::cout << "Function: "s << __func__ << std::endl;
std::cout
  << "--------------------------------------------------------------------------------"s
  << '\n'
  << std::endl;

  /*
   *  TODO: std::is_permutation
   *  Returns true if there exists a permutation of the elements in the range [first1, last1)
   *  that makes that range equal to the range [first2,last2), where last2 denotes
   *  first2 + (last1 - first1) if it was not given.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::is_permutation"s << '\n'
    << std::endl;
  {
    static constexpr auto v1 = { 1, 2, 3, 4, 5, };
    static constexpr auto v2 = { 3, 5, 4, 1, 2, };
    static constexpr auto v3 = { 3, 5, 4, 1, 1, };

    std::cout << "{ "s << v2 << " }"s << " is a permutation of "s
              << "{ "s << v1 << " }"s << ": "s << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n'
              << "{ "s << v3 << " }"s << " is a permutation of "s
              << "{ "s << v1 << " }"s << ": "s << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::next_permutation
   *  Permutes the range [first, last) into the next permutation, where the set of all
   *  permutations is ordered lexicographically with respect to operator< or comp.
   *  Returns true if such a "next permutation" exists; otherwise transforms the range
   *  into the lexicographically first permutation (as if by std::sort(first, last, comp))
   *  and returns false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::next_permutation"s << '\n'
    << std::endl;
  {
    std::string s = "aba"s;
    std::sort(s.begin(), s.end());
    do {
      std::cout << s << '\n';
    } while (std::next_permutation(s.begin(), s.end()));
  }
  std::cout << std::endl;
  
  /*
   *  TODO: std::prev_permutation
   *  Transforms the range [first, last) into the previous permutation from the set of all
   *  permutations that are lexicographically ordered with respect to operator< or comp.
   *  Returns true if such permutation exists, otherwise transforms the range into the
   *  last permutation (as if by std::sort(first, last); std::reverse(first, last);) and
   *  returns false.
   */
  std::cout
    << "................................................................................"s
    << '\n'
    << "std::prev_permutation"s << '\n'
    << std::endl;
  {
    std::string s = "abc"s;
    std::sort(s.begin(), s.end(), std::greater<char>());
    do {
      std::cout << s << ' ';
    } while (std::prev_permutation(s.begin(), s.end()));
    std::cout << '\n';
  }
  std::cout << std::endl;

  return;
}
