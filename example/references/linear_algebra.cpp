// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <units/isq/si/energy.h> // IWYU pragma: keep
#include <units/isq/si/force.h>
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h> // IWYU pragma: keep
#include <units/format.h>
#include <units/quantity_io.h>
#include <linear_algebra.hpp>
#include <iostream>

namespace STD_LA {

template<class ET, class OT>
std::ostream& operator<<(std::ostream& os, const vector<ET, OT>& v)
{
  os << "|";
  for (auto i = 0U; i < v.size(); ++i) {
    os << fmt::format(" {:>9}", v(i));
  }
  os << " |";
  return os;
}

template<class ET, class OT>
std::ostream& operator<<(std::ostream& os, const matrix<ET, OT>& v)
{
  for (auto i = 0U; i < v.rows(); ++i) {
    os << "|";
    for (auto j = 0U; j < v.columns(); ++j) {
      os << fmt::format(" {:>9}", v(i, j));
    }
    os << (i != v.rows() - 1U ? " |\n" : " |");
  }
  return os;
}

}  // namespace STD_LA

namespace {

using namespace units::isq;
using namespace units::isq::si::length_references;
using namespace units::isq::si::force_references;

template<typename Rep = double>
using vector = std::math::fs_vector<Rep, 3>;

template<typename Rep = double>
using matrix = std::math::fs_matrix<Rep, 3, 3>;

void vector_of_quantity_add()
{
  std::cout << "\nvector_of_quantity_add:\n";

  vector<si::length<si::metre>> v = { 1 * m, 2 * m, 3 * m };
  vector<si::length<si::metre>> u = { 3 * m, 2 * m, 1 * m };
  vector<si::length<si::kilometre>> t = { 3 * km, 2 * km, 1 * km };

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";
  std::cout << "t = " << t << "\n";

  std::cout << "v + u = " << v + u << "\n";
  std::cout << "v + t = " << v + t << "\n";
  std::cout << "t[m]  = " << vector<si::length<si::metre>>(t) << "\n";
}

void vector_of_quantity_multiply_same()
{
  std::cout << "\nvector_of_quantity_multiply_same:\n";

  vector<si::length<si::metre>> v = { 1 * m, 2 * m, 3 * m };
  vector<si::length<si::metre>> u = { 3 * m, 2 * m, 1 * m };

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";

  std::cout << "v * u    = " << v * u << "\n";
  std::cout << "2 * m * v = " << 2. * m * v << "\n";
}

void vector_of_quantity_multiply_different()
{
  std::cout << "\nvector_of_quantity_multiply_different:\n";

  vector<si::force<si::newton>> v = { 1 * N, 2 * N, 3 * N };
  vector<si::length<si::metre>> u = { 3 * m, 2 * m, 1 * m };

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";

  std::cout << "v * u    = " << v * u << "\n";
  std::cout << "2 * N * u = " << 2. * N * u << "\n";
  std::cout << "2 * u    = " << 2 * u << "\n";
}

void vector_of_quantity_divide_by_scalar()
{
  std::cout << "\nvector_of_quantity_divide_by_scalar:\n";

  vector<si::length<si::metre>> v = { 4 * m, 8 * m, 12 * m };

  std::cout << "v = " << v << "\n";

  // TODO Uncomment when bug in the LA is fixed
  // std::cout << "v / (2 * s) = " << v / (2 * s) << "\n";
  // std::cout << "v / 2 = " << v / 2 << "\n";
}

void vector_of_quantity_tests()
{
  vector_of_quantity_add();
  vector_of_quantity_multiply_same();
  vector_of_quantity_multiply_different();
  vector_of_quantity_divide_by_scalar();
}

void matrix_of_quantity_add()
{
  std::cout << "\nmatrix_of_quantity_add:\n";

  matrix<si::length<si::metre>> v = {{ 1 * m, 2 * m, 3 * m }, { 4 * m, 5 * m, 6 * m }, { 7 * m, 8 * m, 9 * m }};
  matrix<si::length<si::metre>> u = {{ 3 * m, 2 * m, 1 * m }, { 3 * m, 2 * m, 1 * m }, { 3 * m, 2 * m, 1 * m }};
  matrix<si::length<si::millimetre>> t = {{ 3 * mm, 2 * mm, 1 * mm }, { 3 * mm, 2 * mm, 1 * mm }, { 3 * mm, 2 * mm, 1 * mm }};

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";
  std::cout << "t =\n" << t << "\n";

  std::cout << "v + u =\n" << v + u << "\n";
  std::cout << "v + t =\n" << v + t << "\n";

  // TODO Uncomment when fixed in the LA lib
  // std::cout << "v[mm] =\n" << matrix<si::length<si::millimetre>>(v) << "\n";
}

void matrix_of_quantity_multiply_same()
{
  std::cout << "\nmatrix_of_quantity_multiply_same:\n";
  
  matrix<si::length<si::metre>> v = {{ 1 * m, 2 * m, 3 * m }, { 4 * m, 5 * m, 6 * m }, { 7 * m, 8 * m, 9 * m }};
  vector<si::length<si::metre>> u = { 3 * m, 2 * m, 1 * m };

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";

  std::cout << "v * u =\n" << v * u << "\n";
  std::cout << "2 * m * u =\n" << 2. * m * u << "\n";
}

void matrix_of_quantity_multiply_different()
{
  std::cout << "\nmatrix_of_quantity_multiply_different:\n";

  vector<si::force<si::newton>> v = { 1 * N, 2 * N, 3 * N };
  matrix<si::length<si::metre>> u = {{ 1 * m, 2 * m, 3 * m }, { 4 * m, 5 * m, 6 * m }, { 7 * m, 8 * m, 9 * m }};

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";

  std::cout << "v * u =\n" << v * u << "\n";
  std::cout << "2 * N * u =\n" << 2. * N * u << "\n";
  std::cout << "2 * u =\n" << 2 * u << "\n";
}

void matrix_of_quantity_divide_by_scalar()
{
  std::cout << "\nmatrix_of_quantity_divide_by_scalar:\n";

  matrix<si::length<si::metre>> v = {{ 2 * m, 4 * m, 6 * m }, { 4 * m, 6 * m, 8 * m }, { 8 * m, 4 * m, 2 * m }};

  std::cout << "v =\n" << v << "\n";

  // TODO Uncomment when bug in the LA is fixed
  // std::cout << "v / (2 * s) =\n" << v / (2 * s) << "\n";
  // std::cout << "v / 2 =\n" << v / 2 << "\n";
}

void matrix_of_quantity_tests()
{
  matrix_of_quantity_add();
  matrix_of_quantity_multiply_same();
  matrix_of_quantity_multiply_different();
  matrix_of_quantity_divide_by_scalar();
}

template<units::Unit U = si::metre, units::Representation Rep = double>
using length_v = si::length<U, vector<Rep>>;

template<units::Unit U = si::newton, units::Representation Rep = double>
using force_v = si::force<U, vector<Rep>>;

void quantity_of_vector_add()
{
  std::cout << "\nquantity_of_vector_add:\n";

  length_v<> v(vector<>{ 1, 2, 3 });
  length_v<> u(vector<>{ 3, 2, 1 });
  length_v<si::kilometre> t(vector<>{ 3, 2, 1 });

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";
  std::cout << "t = " << t << "\n";

  std::cout << "v + u = " << v + u << "\n";
  std::cout << "v + t = " << v + t << "\n";
  std::cout << "t[m]  = " << quantity_cast<si::metre>(t) << "\n";
}

void quantity_of_vector_multiply_same()
{
  std::cout << "\nquantity_of_vector_multiply_same:\n";

  length_v<> v(vector<>{ 1, 2, 3 });
  length_v<> u(vector<>{ 3, 2, 1 });

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";

  std::cout << "v * u    = " << v * u << "\n";
  std::cout << "2 * m * v = " << 2. * m * v << "\n";
}

void quantity_of_vector_multiply_different()
{
  std::cout << "\nquantity_of_vector_multiply_different:\n";

  force_v<> v(vector<>{ 1, 2, 3 });
  length_v<> u(vector<>{ 3, 2, 1 });

  std::cout << "v = " << v << "\n";
  std::cout << "u = " << u << "\n";

  std::cout << "v * u    = " << v * u << "\n";
  std::cout << "2 * N * u = " << 2. * N * u << "\n";
  std::cout << "2 * u    = " << 2 * u << "\n";
}

void quantity_of_vector_divide_by_scalar()
{
  std::cout << "\nquantity_of_vector_divide_by_scalar:\n";

  length_v<> v(vector<>{ 4, 8, 12 });

  std::cout << "v = " << v << "\n";

  // TODO Uncomment when bug in the LA is fixed
  // std::cout << "v / 2 * s = " << v / 2 * s << "\n";
  // std::cout << "v / 2 = " << v / 2 << "\n";
}

void quantity_of_vector_tests()
{
  quantity_of_vector_add();
  quantity_of_vector_multiply_same();
  quantity_of_vector_multiply_different();
  quantity_of_vector_divide_by_scalar();
}

template<units::Unit U = si::metre, units::Representation Rep = double>
using length_m = si::length<U, matrix<Rep>>;

void quantity_of_matrix_add()
{
  std::cout << "\nquantity_of_matrix_add:\n";

  length_m<> v(matrix<>{{ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }});
  length_m<> u(matrix<>{{ 3, 2, 1 }, { 3, 2, 1 }, { 3, 2, 1 }});
  length_m<si::kilometre> t(matrix<>{{ 3, 2, 1 }, { 3, 2, 1 }, { 3, 2, 1 }});

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";
  std::cout << "t =\n" << t << "\n";

  std::cout << "v + u =\n" << v + u << "\n";
  std::cout << "v + t =\n" << v + t << "\n";

  // TODO Uncomment when fixed in the LA lib
  // std::cout << "v[mm] =\n" << matrix<si::length<si::millimetre>>(v) << "\n";
}

void quantity_of_matrix_multiply_same()
{
  std::cout << "\nquantity_of_matrix_multiply_same:\n";
  
  length_m<> v(matrix<>{{ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }});
  length_v<> u(vector<>{ 3, 2, 1 });

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";

  std::cout << "v * u =\n" << v * u << "\n";
  std::cout << "2 * m * u =\n" << 2. * m * u << "\n";
}

void quantity_of_matrix_multiply_different()
{
  std::cout << "\nquantity_of_matrix_multiply_different:\n";

  force_v<> v(vector<>{ 1, 2, 3 });
  length_m<> u(matrix<>{{ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }});

  std::cout << "v =\n" << v << "\n";
  std::cout << "u =\n" << u << "\n";

  std::cout << "v * u =\n" << v * u << "\n";
  std::cout << "2 * N * u =\n" << 2. * N * u << "\n";
  std::cout << "2 * u =\n" << 2 * u << "\n";
}

void quantity_of_matrix_divide_by_scalar()
{
  std::cout << "\nquantity_of_matrix_divide_by_scalar:\n";

  length_m<> v(matrix<>{{ 2, 4, 6 }, { 4, 6, 8 }, { 8, 4, 2 }});

  std::cout << "v =\n" << v << "\n";

  // TODO Uncomment when bug in the LA is fixed
  // std::cout << "v / (2 * s) =\n" << v / (2 * s) << "\n";
  // std::cout << "v / 2 =\n" << v / 2 << "\n";
}

void quantity_of_matrix_tests()
{
  quantity_of_matrix_add();
  quantity_of_matrix_multiply_same();
  quantity_of_matrix_multiply_different();
  quantity_of_matrix_divide_by_scalar();
}

}  // namespace

int main()
{
  vector_of_quantity_tests();
  matrix_of_quantity_tests();
  quantity_of_vector_tests();
  quantity_of_matrix_tests();
}
