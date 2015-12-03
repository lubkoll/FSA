// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef SPACY_UTIL_CONCEPTS_LINEAR_OPERATOR_CONCEPT_HH
#define SPACY_UTIL_CONCEPTS_LINEAR_OPERATOR_CONCEPT_HH

#include "operatorConcept.hh"
#include "vectorConcept.hh"

namespace Spacy
{
  /// @cond
  class Vector;
  /// @endcond

  /**
   * @ingroup SpacyGroup
   * @brief Concept for linear operators in %Spacy.
   *
   * @code
   * // A: X->Y.
   * class MyOperator
   * {
   * public:
   *   // Copy constructor.
   *   MyOperator(const MyOperator&);
   *
   *   // Copy assignable x=y.
   *   MyOperator& operator=(const MyOperator& y);
   *
   *   // Compute A(x).
   *   ::Spacy::Vector operator()(const ::Spacy::Vector& x) const;
   *
   *   // In-place summation x+=y.
   *   MyOperator& operator+=(const MyOperator& y);
   *
   *   // In-place subtraction x-=y.
   *   MyOperator& operator-=(const MyOperator& y);
   *
   *   // In-place multiplication x*=a.
   *   MyOperator& operator*=(double a);
   *
   *   // Negation -y.
   *   MyOperator operator-(const MyOperator& y);
   *
   *   // Equality comparison x==y.
   *   bool operator==(const MyOperator& y);
   *
   *   // Apply as dual element x(y).
   *   Real operator()(const MyOperator& y);
   *
   *   // Access pointer to underlying function space.
   *   const VectorSpace& space() const;
   *
   *   // Access linear solver representing A(x)^-1
   *  LinearSolver solver() const;
   *
   *   // Access domain space X.
   *   const VectorSpace& domain() const;
   *
   *   // Access range space Y.
   *   const VectorSpace& range() const;
   * };
   * @endcode
   *
   * The member function `solver()` is allowed to return anything that fits into a `std::function<Vector(const Vector&)>`.
   *
   * @see OperatorConcept, VectorConcept, ::Spacy::LinearOperator
   */
  template <class Impl>
  using LinearOperatorConcept =
  std::integral_constant< bool ,
    VectorConcept<Impl>::value &&
    OperatorConcept<Impl>::value &&
    HasMemFn_solver<Impl>::value
  >;
}

#endif // SPACY_UTIL_CONCEPTS_LINEAR_OPERATOR_CONCEPT_HH