// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2013, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: David Weese <david.weese@fu-berlin.de>
// ==========================================================================
// Basic concept definitions, e.g. DefaultConstructible, Comparable, ...
// ==========================================================================

// SEQAN_NO_GENERATED_FORWARDS

#ifndef SEQAN_CORE_INCLUDE_SEQAN_BASIC_FUNDAMENTAL_CONCEPTS_H_
#define SEQAN_CORE_INCLUDE_SEQAN_BASIC_FUNDAMENTAL_CONCEPTS_H_

namespace seqan {

// ---------------------------------------------------------------------------
// ==> boost/concept_check.hpp <==
// ---------------------------------------------------------------------------

// (C) Copyright Jeremy Siek 2000.
// Copyright 2002 The Trustees of Indiana University.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// ============================================================================
// Assignment Concepts
// ============================================================================

/*!
 * @concept DefaultConstructibleConcept
 * @brief A type with a default constructor.
 *
 * @headerfile <seqan/basic.h>
 * 
 * @signature DefaultConstructible<T>
 * 
 * Expects an instance of type <tt>T</tt> to be default constructible.
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T()
 * T a;
 * @endcode
 *
 * @see AssignableConcept
 * @see CopyConstructibleConcept
 * @see DestructibleConcept
 */

/**
.Concept.DefaultConstructibleConcept
..cat:Basic
..summary:A type with a default constructor.
..signature:DefaultConstructible<T>
..remarks:
...text:Expects an instance of type $T$ to be default constructible.
..example.text:Valid expressions:
..example.code:
T()
T a;
..include:seqan/basic.h
..see:Concept.AssignableConcept
..see:Concept.CopyConstructibleConcept
*/

SEQAN_CONCEPT(DefaultConstructible,(T))
{
    SEQAN_CONCEPT_USAGE(DefaultConstructible) 
    {
        T a;                // require default constructor
        ignoreUnusedVariableWarning(a);
    }
};

/*!
 * @concept DestructibleConcept
 * @brief A type with a destructor.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature Destructible<T>
 * 
 * Expects an instance of type <tt>T</tt> to be destructible.
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T()
 * T a;
 * @endcode
 *
 * @see DefaultConstructibleConcept
 */

/**
.Concept.DestructibleConcept
..cat:Basic
..summary:A type with a destructor.
..signature:Destructible<T>
..remarks:
...text:Expects an instance of type $T$ to be destructible.
..example.text:Valid expressions:
..example.code:
T()
T a;
..include:seqan/basic.h
..see:Concept.DefaultConstructibleConcept
*/

SEQAN_CONCEPT(Destructible, (T))
{
    SEQAN_CONCEPT_USAGE(Destructible) 
    {
        // It is hard to test this.
    }
};

/*!
 * @concept AssignableConcept
 * @brief A type with an assignment operator.
 *
 * @headerfile <seqan/basic.h>
 * 
 * @signature Assignable<T>
 * 
 * Expects instances of type <tt>T</tt> to be assignable into each other.
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * a = b;  // a, b are of type T
 * @endcode
 *
 * @see DefaultConstructibleConcept
 */

/*!
 * @fn AssignableConcept::operator=
 * @brief C++ built-in assignment operator.
 *
 * The C++ standard requires the assignment operator to be a member function.
 *
 * @signature T & T::operator=(T const & other);
 */

/**
.Concept.AssignableConcept
..cat:Basic
..summary:A type with an assignment operator.
..signature:Assignable<T>
..remarks:
...text:Expects instances of type $T$ to be assignable into each other.
..example.text:Valid expressions:
..example.code:
a = b;  // a, b are of type T
..include:seqan/basic.h

.Function.assign.concept:Concept.AssignableConcept
.Function.operator=.concept:Concept.AssignableConcept
*/

// TODO(holtgrew): Test availability of assign() function?

SEQAN_CONCEPT(Assignable,(T))
{
    SEQAN_CONCEPT_USAGE(Assignable) 
    {
#if !defined(_ITERATOR_)    // back_insert_iterator broken for VC++ STL
        a = b;              // require assignment operator
#endif
        constConstraints(b);
    }
private:
    void constConstraints(const T& x) 
    {
#if !defined(_ITERATOR_)    // back_insert_iterator broken for VC++ STL
        a = x;              // const required for argument to assignment
#else
        ignoreUnusedVariableWarning(x);
#endif
    }
private:
    T a;
    T b;
};

/*!
 * @concept CopyConstructibleConcept
 * @brief A type with a copy-constructor.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature CopyConstructible<T>
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T a(b);  // b is of type T
 * @endcode
 * 
 * @see DefaultConstructibleConcept
 */

/**
.Concept.CopyConstructibleConcept
..cat:Basic
..summary:A type with a copy-constructor.
..signature:CopyConstructible<T>
..example.text:Valid expressions:
..example.code:
T a(b);  // b is of type T
..include:seqan/basic.h
*/

SEQAN_CONCEPT(CopyConstructible,(T))
{
    SEQAN_CONCEPT_USAGE(CopyConstructible) 
    {
        T a(b);            // require copy constructor
        T* ptr = &a;       // require address of operator
        constConstraints(a);
        ignoreUnusedVariableWarning(ptr);
    }
private:
    void constConstraints(const T& a) 
    {
        T c(a);            // require const copy constructor
        const T* ptr = &a; // require const address of operator
        ignoreUnusedVariableWarning(c);
        ignoreUnusedVariableWarning(ptr);
    }
    T b;
};


// ============================================================================
// Relation Concepts
// ============================================================================

// The C++ standard requirements for many concepts talk about return
// types that must be "convertible to bool".  The problem with this
// requirement is that it leaves the door open for evil proxies that
// define things like operator|| with strange return types.  Two
// possible solutions are:
// 1) require the return type to be exactly bool
// 2) stay with convertible to bool, and also
//    specify stuff about all the logical operators.
// For now we just test for convertible to bool.

/*!
 * @fn requireBooleanExpr
 * @headerfile <seqan/basic.h>
 * @brief Tests for a boolean expression.
 *
 * @signature void requireBooleanExpr(x);
 *
 * @param[in] x Object that must be convertible to <tt>bool</tt>
 *
 * This function can be used to test for functions returning bools, e.g. less operators.
 *
 * @see SEQAN_CONCEPT_USAGE
 */

/**
.Function.requireBooleanExpr
..summary:Tests for a boolean expression.
..cat:Concepts
..signature:requireBooleanExpr(x)
..param.x: Object that must be convertible to $bool$.
..remarks:This function can be used to test for available boolean functions, e.g. less operators.
..include:seqan/basic.h
..see:Macro.SEQAN_CONCEPT_USAGE
 */
template <class T>
void requireBooleanExpr(const T& t) 
{
    bool x = t;
    ignoreUnusedVariableWarning(x);
}


/*!
 * @concept EqualityComparableConcept
 * @brief A type that can be equality compared.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature EqualityComparable<T>
 * 
 * @section Remarks
 * 
 * Expects instances of type <tt>T</tt> to be comparable via <tt>operator==</tt>
 * and <tt>operator!=</tt>. Comparison operators must return boolean convertible
 * values. <tt>operator==</tt> must be an equivalence relation.
 * 
 * @section Examples
 * 
 * Valid expressions:
 * 
 * @code{.cpp}
 * a == b;
 * a != b;
 * @endcode
 *
 * Invariants:
 *
 * <ul>
 *  <li><tt>(a == a)</tt> (reflexivity)</li>
 *  <li><tt>(a == b)</tt> => <tt> (b == a)</tt> (symmetry)</li>
 *  <li> <tt>(a == b) &amp;&amp;(b == c)</tt> => <tt>(a == c)</tt> (transitivity)</li>
 * </ul>
 * 
 * @see ComparableConcept
 */

/*!
 * @fn EqualityComparableConcept::operator==
 * @brief Operator to compare for equality.
 *
 * @signature bool T::operator==(T const & other) const;
 *
 * The equality operator can be implemented as a member or as a global function.
 *
 * Usually, there is an implementation of <tt>operator==()</tt> for custom data
 * types and then <tt>operator!=()</tt> uses <tt>operator==()</tt>.
 *
 * @see EqualityComparableConcept::operator==
 */

/*!
 * @fn EqualityComparableConcept::operator!=
 * @brief Operator to compare for inequality.
 *
 * @signature bool T::operator!=(T const & other) const;
 *
 * The inequality operator can be implemented as a member or as a global function.
 *
 * Usually, the inequality operator is implemented as <tt>!operator==(a, b)</tt>.
 *
 * @see EqualityComparableConcept::operator==
 */

/**
.Concept.EqualityComparableConcept
..cat:Comparisons
..summary:A type that can be equality compared.
..signature:EqualityComparable<T>
..remarks:
...text:Expects instances of type $T$ to be comparable via $operator==$ and $operator!=$. 
Comparison operators must return boolean convertible values.
$operator==$ must be an equivalence relation.
..example.text:Valid expressions:
..example.code:
a == b;
a != b;
..example.text:Invariants:\br
$a==a$ (reflexivity)\nl
$a==b$ \Rightarrow $b==a$ (symmetry)\nl
$a==b$ and $b==c$ \Rightarrow $a==c$ (transitivity)
..include:seqan/basic.h
*/

SEQAN_CONCEPT(EqualityComparable,(T))
{
    SEQAN_CONCEPT_USAGE(EqualityComparable) 
    {
        requireBooleanExpr(a == b);
        requireBooleanExpr(a != b);
    }
private:
    T a, b;
};

/*!
 * @concept LessThanComparableConcept
 * @brief A type that can be less-than compared.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature LessThanComparable<T>
 * 
 * Expects instances of type <tt>T</tt> to be comparable via <tt>operator<</tt>.
 * Comparison operator must return a boolean convertible value.
 * <tt>operator&lt;<tt> must be a partial ordering.
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * a < b;
 * @endcode
 *
 * Invariants:
 * <ul>
 *   <li><tt>!(a &lt; a)</tt> (irreflexivity)</li>
 *   <li><tt>!(b &lt; a)</tt> => <tt>a < b</tt> (antisymmetry)</li>
 *   <li><tt>(a &lt; b) &amp;&amp; (b < c)</tt> =&gt; <tt>a &lt; c</tt> (transitivity)</li>
 * </ul>
 * 
 * @see ComparableConcept
 */

/*!
 * @fn LessThanComparableConcept::operator<
 * @brief C++ built-in less-than comparison operator.
 *
 * @signature bool T::operator<(T const & other) const;
 */

/**
.Concept.LessThanComparableConcept
..cat:Comparisons
..summary:A type that can be less-than compared.
..signature:LessThanComparable<T>
..remarks:
...text:Expects instances of type $T$ to be comparable via $operator<$. 
Comparison operator must return a boolean convertible value.
$operator<$ must be a partial ordering.
..example.text:Valid expressions:
..example.code:
a < b;
..example.text:Invariants:\br
$\not a<a$ (irreflexivity)\nl
$a<b$ \Rightarrow $\not b<a$ (antisymmetry)\nl
$a<b$ and $b<c$ \Rightarrow $a<c$ (transitivity)
..include:seqan/basic.h

.Function.operator<.concept:Concept.LessThanComparableConcept
*/

SEQAN_CONCEPT(LessThanComparable,(T))
{
    SEQAN_CONCEPT_USAGE(LessThanComparable) 
    {
        requireBooleanExpr(a < b);
    }
private:
    T a, b;
};

/*!
 * @concept ComparableConcept
 * @extends EqualityComparableConcept
 * @extends LessThanComparableConcept
 * @brief A type that can be compared.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature Comparable<T>
 * 
 * Expects instances of type <tt>T</tt> to be comparable. Comparison operators
 * must return boolean convertible values.
 * 
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * a < b;
 * a > b;
 * a <= b;
 * a >= b;
 * @endcode
 *
 * Invariants:
 *
 * <ul>
 *   <li><tt>(a &lt; b)</tt> <=> <tt>b &gt; a</tt></li>
 *   <li><tt>(a &lt;= b)</tt> <=> <tt>b &gt;= a</tt></li>
 *   <li><tt>(a == b)</tt> <=> <tt>(a &gt;= b) &amp;&amp; (b &gt;= a)</tt></li>
 * </ul>
 * 
 * @see EqualityComparableConcept
 * @see LessThanComparableConcept
 */

/*!
 * @fn ComparableConcept::operator>
 * @brief C++ built-in greater-than comparison operator.
 *
 * @signature bool T::operator>(T const & other) const;
 *
 * This operator can be implemented as a member or a global function.
 */

/*!
 * @fn ComparableConcept#operator<=
 * @brief C++ built-in less-than-or-equal comparison operator.
 *
 * @signature bool T::operator<=(T const & other) const;
 *
 * This operator can be implemented as a member or a global function.
 */

/*!
 * @fn ComparableConcept#operator>=
 * @brief C++ built-in greather-than-or-equal comparison operator.
 *
 * @signature bool T::operator>=(T const & other) const;
 *
 * This operator can be implemented as a member or a global function.
 */

/**
.Concept.ComparableConcept
..cat:Comparisons
..summary:A type that can be compared.
..signature:Comparable<T>
..baseconcept:Concept.LessThanComparableConcept
..remarks:
...text:Expects instances of type $T$ to be comparable. Comparison operators must return boolean convertible values.
..example.text:Valid expressions:
..example.code:
a < b;
a > b;
a <= b;
a >= b;
..example.text:Invariants:\br
$a<b$ \Leftrightarrow $b>a$\nl
$a<=b$ \Leftrightarrow $b>=a$\nl
$a<=b$ \Leftrightarrow $a<b$ or ($a<=b$ and $a>=b$)
..include:seqan/basic.h
..see:Concept.EqualityComparableConcept
..see:Concept.LessThanComparableConcept

.Function.operator<=.concept:Concept.ComparableConcept
.Function.operator>.concept:Concept.ComparableConcept
.Function.operator>=.concept:Concept.ComparableConcept
*/

// This is equiaent to SGI STL's LessThanComparable.
SEQAN_CONCEPT(Comparable,(T))
{
    SEQAN_CONCEPT_USAGE(Comparable) 
    {
        requireBooleanExpr(a < b);
        requireBooleanExpr(a > b);
        requireBooleanExpr(a <= b);
        requireBooleanExpr(a >= b);
    }
private:
    T a, b;
};


// ============================================================================
// Forwards
// ============================================================================

SEQAN_CONCEPT(IntegerConcept, (T));
SEQAN_CONCEPT(SignedIntegerConcept, (T));
SEQAN_CONCEPT(UnsignedIntegerConcept, (T));

// ============================================================================
// Test fulfilled concepts
// ============================================================================

template <typename T>
struct Is< SignedIntegerConcept<T> >
{
    typedef
        // Explicitely unsigned.
        typename IfC< IsSameType<T, signed char>::VALUE,     True,
        typename IfC< IsSameType<T, short>::VALUE,           True,
        typename IfC< IsSameType<T, int>::VALUE,             True,
        typename IfC< IsSameType<T, long>::VALUE,            True,
        typename IfC< IsSameType<T, __int64>::VALUE,         True,
        False
        >::Type>::Type>::Type>::Type>::Type Type;
        enum { VALUE = Type::VALUE };
};

template <typename T>
struct Is< UnsignedIntegerConcept<T> >
{
    typedef
        // Explicitely unsigned.
        typename IfC< IsSameType<T, unsigned char>::VALUE,   True,
        typename IfC< IsSameType<T, unsigned short>::VALUE,  True,
        typename IfC< IsSameType<T, unsigned int>::VALUE,    True,
        typename IfC< IsSameType<T, unsigned long>::VALUE,   True,
        typename IfC< IsSameType<T, __uint64>::VALUE,        True,
        False
        >::Type>::Type>::Type>::Type>::Type Type;
        enum { VALUE = Type::VALUE };
};

template <typename T>
struct Is< IntegerConcept<T> >
{
    typedef
        // char is not necessarily equal to signed or unsigned char.
        typename IfC< IsSameType<T, char>::VALUE,                True,
        // Is T a signed integer?
        typename IfC< Is< SignedIntegerConcept<T> >::VALUE,      True,
        // Is T an unsigned integer?
        typename IfC< Is< UnsignedIntegerConcept<T> >::VALUE,    True,
        False
        >::Type>::Type>::Type Type;
        enum { VALUE = Type::VALUE };
};

template <typename T>
struct Is< SignedIntegerConcept<T const> > : Is< SignedIntegerConcept<typename RemoveConst<T>::Type> > {};

template <typename T>
struct Is< UnsignedIntegerConcept<T const> > : Is< UnsignedIntegerConcept<typename RemoveConst<T>::Type> > {};

template <typename T>
struct Is< IntegerConcept<T const> > : Is< IntegerConcept<typename RemoveConst<T>::Type> > {};


/**
.Metafunction.IsSignedInteger:
..cat:Basic
..summary:Tests for a type to be of signed integral aue.
..signature:IsSignedInteger<T>::Type
..param.T:Type that is tested.
..returns.param.Type:@Tag.Logical Values.True@, if $T$ is a signed integral type, @Tag.Logical Values.False@ otherwise.
...default:@Tag.Logical Values.False@
..status:deprecated, please use $Is<SignedIntegerConcept<T> >::Type$
..include:seqan/basic.h
..see:Metafunction.IsUnsignedInteger
 */

/**
.Metafunction.IsUnsignedInteger:
..cat:Basic
..summary:Tests for a type to be of unsigned integral aue.
..signature:IsUnsignedInteger<T>::Type
..param.T:Type that is tested.
..returns.param.Type:@Tag.Logical Values.True@, if $T$ is an unsigned integral type, @Tag.Logical Values.False@ otherwise.
...default:@Tag.Logical Values.False@
..status:deprecated, please use $Is<UnsignedIntegerConcept<T> >::Type$
..include:seqan/basic.h
 */

/*!
 * @mfn IsInteger
 * @brief Tests for a type to be of integral value.
 * @headerfile seqan/basic.h
 * 
 * @signature IsInteger<T>::Type
 * 
 * @tparam T Type that is tested.
 * 
 * @return TReturn 
 * 
 * @deprecated Please use <tt>Is&lt;IntegerConcept&lt;T&gt; &gt;::Type</tt>.
 * 
 * @see IsIntegral
 */

/**
.Metafunction.IsInteger:
..cat:Basic
..summary:Tests for a type to be of integral aue.
..signature:IsInteger<T>::Type
..param.T:Type that is tested.
..returns.param.Type:@Tag.Logical Values.True@, if $T$ is an ingegral type, @Tag.Logical Values.False@ otherwise.
...default:@Tag.Logical Values.False@
..status:deprecated, please use $Is<IntegerConcept<T> >::Type$
..include:seqan/basic.h
..see:Metafunction.IsSignedInteger
..see:Metafunction.IsUnsignedInteger
 */

/*!
 * @mfn IsIntegral
 * @brief Tests for a type to be of integral vaule.
 * @headerfile seqan/basic.h
 * 
 * @signature IsIntegral<T>::Type
 * 
 * @tparam T Type that is tested.
 * 
 * @return TReturn 
 * 
 * @deprecated Please use <tt>Is&lt;IntegerConcept&lt;T&gt; &gt;::Type</tt>.
 */

/**
.Metafunction.IsIntegral:
..cat:Basic
..summary:Tests for a type to be of integral aue.
..signature:IsIntegral<T>::Type
..param.T:Type that is tested.
..returns.param.Type:@Tag.Logical Values.True@, if $T$ is an ingegral type, @Tag.Logical Values.False@ otherwise.
...default:@Tag.Logical Values.False@
..status:deprecated, please use $Is<IntegerConcept<T> >::Type$
..include:seqan/basic.h
 */

// deprecation wrappers
template <typename T>
struct IsSignedInteger : Is< SignedIntegerConcept<T> > {};
template <typename T>
struct IsUnsignedInteger : Is< UnsignedIntegerConcept<T> > {};
template <typename T>
struct IsInteger : Is< IntegerConcept<T> > {};

template <typename T>
struct IsIntegral : IsInteger<T> {};

// ============================================================================
// Concepts for integers
// ============================================================================

// Baseconceptly there are two ways to check concepts:
//
// 1. Define expressions and rules a passing type must fulfill.
// 2. Let the concept check fail by default and only let it pass for the types
//    that definitely fulfill the concept

// We try variant 1, as it lets the user to define his/her own integer types
// without the need to specialize all kinds of Integer/SignedInteger/UnsignedInteger concepts.

/*!
 * @concept IntegerConcept
 * @extends ComparableConcept
 * @extends EqualityComparableConcept
 * @extends AssignableConcept
 * @extends CopyConstructibleConcept
 * @extends DefaultConstructibleConcept
 * @extends DestructibleConcept
 * @brief An integral type.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature IntegerConcept<T>
 * 
 * Expects an instance of type <tt>T</tt> to be of integral value and to provide
 * the same operations as <tt>int</tt>. The integer concept imposes no
 * restrictions on an available sign. Every type <tt>T</tt> that fulfills the
 * @link IntegerConcept @endlink fulfills either the @link SignedIntegerConcept
 * @endlink or the @link UnsignedIntegerConcept @endlink.
 * 
 * @section Examples
 * 
 * @code{.cpp}
 * SEQAN_CONCEPT_ASSERT((IntegerConcept<int>));
 * SEQAN_CONCEPT_ASSERT((IntegerConcept<char>));
 * //SEQAN_CONCEPT_ASSERT((IntegerConcept<double>));                       // fails to compile
 *  
 * std::cout << Is<IntegerConcept<char> >::VALUE << std::endl;             // 1
 * std::cout << Is<IntegerConcept<int> >::VALUE << std::endl;              // 1
 * std::cout << Is<IntegerConcept<unsigned short> >::VALUE << std::endl;   // 1
 * std::cout << Is<IntegerConcept<double> >::VALUE << std::endl;           // 0
 * @endcode
 *
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T a, b;
 * int c;
 *  
 * a = 0u;
 * b = 1u;
 * c = a;
 *  
 * b = a + 1u;
 * b = a + a;
 * b += a;
 * b += 1u;
 * b = a++;
 * b = ++a;
 *  
 * b = a - a;
 * b = a - 1u;
 * b -= a;
 * b -= 1u;
 * b = a--;
 * b = --a;
 *  
 * b = a * a;
 * b = a * 1u;
 * b *= a;
 * b *= 1u;
 *  
 * b = a / a;
 * b = a / 1u;
 * b /= a;
 * b /= 1u;
 *  
 * b = a << a;
 * b = a << 1;
 * b <<= a;
 * b <<= 1;
 *  
 * b = a >> a;
 * b = a >> 1;
 * b >>= a;
 * b >>= 1;
 * @endcode
 */

/**
.Concept.IntegerConcept
..cat:Basic
..baseconcept:Concept.ComparableConcept
..baseconcept:Concept.EqualityComparableConcept
..summary:An integral type.
..signature:IntegerConcept<T>
..remarks:
...text:Expects an instance of type $T$ to be of integral value and to provide the same operations as $int$.
The integer concept imposes no restrictions on an available sign.
Every type $T$ that fulfills the @Concept.IntegerConcept@ fulfills either the @Concept.SignedIntegerConcept@ or the @Concept.UnsignedIntegerConcept@.
..example.code:
SEQAN_CONCEPT_ASSERT((IntegerConcept<int>));
SEQAN_CONCEPT_ASSERT((IntegerConcept<char>));
//SEQAN_CONCEPT_ASSERT((IntegerConcept<double>));                       // fails to compile

std::cout << Is<IntegerConcept<char> >::VALUE << std::endl;             // 1
std::cout << Is<IntegerConcept<int> >::VALUE << std::endl;              // 1
std::cout << Is<IntegerConcept<unsigned short> >::VALUE << std::endl;   // 1
std::cout << Is<IntegerConcept<double> >::VALUE << std::endl;           // 0
..example.text:Valid expressions:
..example.code:
T a, b;
int c;

a = 0u;
b = 1u;
c = a;

b = a + 1u;
b = a + a;
b += a;
b += 1u;
b = a++;
b = ++a;

b = a - a;
b = a - 1u;
b -= a;
b -= 1u;
b = a--;
b = --a;

b = a * a;
b = a * 1u;
b *= a;
b *= 1u;

b = a / a;
b = a / 1u;
b /= a;
b /= 1u;

b = a << a;
b = a << 1;
b <<= a;
b <<= 1;

b = a >> a;
b = a >> 1;
b >>= a;
b >>= 1;
..include:seqan/basic.h
..see:Concept.SignedIntegerConcept
..see:Concept.UnsignedIntegerConcept
*/

SEQAN_CONCEPT(IntegerConcept, (TValue)) :
    Comparable<TValue>
{
    TValue a, b;
    int c;
    
    SEQAN_CONCEPT_USAGE(IntegerConcept)
    {
        a = 0u;
        b = 1u;
        c = a;
        
        b = a + 1u;
        b = a + a;
        b += a;
        b += 1u;
        b = a++;
        b = ++a;

        b = a - a;
        b = a - 1u;
        b -= a;
        b -= 1u;
        b = a--;
        b = --a;
        
        b = a * a;
        b = a * 1u;
        b *= a;
        b *= 1u;

        b = a / a;
        b = a / 1u;
        b /= a;
        b /= 1u;
        
        b = a << a;
        b = a << 1;
        b <<= a;
        b <<= 1;

        b = a >> a;
        b = a >> 1;
        b >>= a;
        b >>= 1;
                
        SEQAN_STATIC_ASSERT_MSG(static_cast<TValue>(0u) < static_cast<TValue>(1u), "Integer has wrong order.");
    }
};

/*!
 * @concept SignedIntegerConcept
 * @extends IntegerConcept
 * @brief An integral type with a sign.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature SignedIntegerConcept<T>
 * 
 * Expects an instance of type <tt>T</tt> to represent (possibly negative)
 * integral values and to provide the same operations as <tt>int</tt>. Every
 * type <tt>T</tt> that fulfills the @link IntegerConcept @endlink fulfills
 * either the @link SignedIntegerConcept @endlink or the @link
 * UnsignedIntegerConcept @endlink.
 * 
 * @section Examples
 * 
 * @code{.cpp}
 * SEQAN_CONCEPT_ASSERT((SignedIntegerConcept<int>));
 * //SEQAN_CONCEPT_ASSERT((SignedIntegerConcept<unsigned short>));             // fails to compile
 *  
 * std::cout << Is<SignedIntegerConcept<char> >::VALUE << std::endl;           // 0
 * std::cout << Is<SignedIntegerConcept<int> >::VALUE << std::endl;            // 0
 * std::cout << Is<SignedIntegerConcept<unsigned short> >::VALUE << std::endl; // 1
 * std::cout << Is<SignedIntegerConcept<double> >::VALUE << std::endl;         // 0
 * @endcode
 *
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T a;
 * int b;
 *  
 * a = -1;
 * b = a;
 *  
 * a = a - a;
 * a = a + 1;
 * a = a - 1;
 *  
 * a = a / 2;
 *  
 * static_cast<T>(-1) < static_cast<T>(0);
 * @endcode
 */

/**
.Concept.SignedIntegerConcept
..cat:Basic
..baseconcept:Concept.IntegerConcept
..summary:An integral type with a sign.
..signature:SignedIntegerConcept<T>
..remarks:
...text:Expects an instance of type $T$ to represent (possibly negative) integral values and to provide the same operations as $int$.
Every type $T$ that fulfills the @Concept.IntegerConcept@ fulfills either the @Concept.SignedIntegerConcept@ or the @Concept.UnsignedIntegerConcept@.
..example.code:
SEQAN_CONCEPT_ASSERT((SignedIntegerConcept<int>));
//SEQAN_CONCEPT_ASSERT((SignedIntegerConcept<unsigned short>));             // fails to compile

std::cout << Is<SignedIntegerConcept<char> >::VALUE << std::endl;           // 0
std::cout << Is<SignedIntegerConcept<int> >::VALUE << std::endl;            // 0
std::cout << Is<SignedIntegerConcept<unsigned short> >::VALUE << std::endl; // 1
std::cout << Is<SignedIntegerConcept<double> >::VALUE << std::endl;         // 0
..example.text:Valid expressions:
..example.code:
T a;
int b;

a = -1;
b = a;

a = a - a;
a = a + 1;
a = a - 1;

a = a / 2;

static_cast<T>(-1) < static_cast<T>(0);
..include:seqan/basic.h
*/

// an integer that must have a sign
SEQAN_CONCEPT(SignedIntegerConcept, (TValue)) :
    IntegerConcept<TValue>
{
    TValue a;
    int b;
    
    SEQAN_CONCEPT_USAGE(SignedIntegerConcept)
    {
        a = -1;
        b = a;
        
        a = a - a;
        a = a + 1;
        a = a - 1;

        a = a / 2;
        
        SEQAN_STATIC_ASSERT_MSG(static_cast<TValue>(-1) < static_cast<TValue>(0), "Signed integer is either not signed or has wrong order.");
    }
};

/*!
 * @concept UnsignedIntegerConcept
 * @extends IntegerConcept
 * @brief An integral type without a sign.
 * 
 * @headerfile <seqan/basic.h>
 * 
 * @signature UnsignedIntegerConcept<T>
 * 
 * Expects an instance of type <tt>T</tt> to represent non-negative integral
 * values and to provide the same operations as <tt>unsigned int</tt>. Every
 * type <tt>T</tt> that fulfills the @link IntegerConcept @endlink fulfills
 * either the @link SignedIntegerConcept @endlink or the @link
 * UnsignedIntegerConcept @endlink.
 * 
 * @section Examples
 * 
 * @code{.cpp}
 * //SEQAN_CONCEPT_ASSERT((UnsignedIntegerConcept<int>));                          // fails to compile
 * SEQAN_CONCEPT_ASSERT((UnsignedIntegerConcept<unsigned short>));
 *  
 * std::cout << Is<UnsignedIntegerConcept<char> >::VALUE << std::endl;             // 0
 * std::cout << Is<UnsignedIntegerConcept<int> >::VALUE << std::endl;              // 0
 * std::cout << Is<UnsignedIntegerConcept<unsigned short> >::VALUE << std::endl;   // 1
 * std::cout << Is<UnsignedIntegerConcept<double> >::VALUE << std::endl;           // 0
 * @endcode
 *
 * @section Valid Expressions
 * 
 * @code{.cpp}
 * T a;
 * unsigned int b;
 *  
 * a = 1u;
 * b = a;
 *  
 * std::cout << static_cast<T>(0) < static_cast<T>(-1) << std::endl;  // 1
 * @endcode
 */

/**
.Concept.UnsignedIntegerConcept
..cat:Basic
..baseconcept:Concept.IntegerConcept
..summary:An integral type without a sign.
..signature:UnsignedIntegerConcept<T>
..remarks:
...text:Expects an instance of type $T$ to represent non-negative integral values and to provide the same operations as $unsigned int$.
Every type $T$ that fulfills the @Concept.IntegerConcept@ fulfills either the @Concept.SignedIntegerConcept@ or the @Concept.UnsignedIntegerConcept@.
..example.code:
//SEQAN_CONCEPT_ASSERT((UnsignedIntegerConcept<int>));                          // fails to compile
SEQAN_CONCEPT_ASSERT((UnsignedIntegerConcept<unsigned short>));

std::cout << Is<UnsignedIntegerConcept<char> >::VALUE << std::endl;             // 0
std::cout << Is<UnsignedIntegerConcept<int> >::VALUE << std::endl;              // 0
std::cout << Is<UnsignedIntegerConcept<unsigned short> >::VALUE << std::endl;   // 1
std::cout << Is<UnsignedIntegerConcept<double> >::VALUE << std::endl;           // 0
..example.text:Valid expressions:
..example.code:
T a;
unsigned int b;

a = 1u;
b = a;

std::cout << static_cast<T>(0) < static_cast<T>(-1) << std::endl;  // 1
..include:seqan/basic.h
*/


// an integer that mustn't have a sign
SEQAN_CONCEPT(UnsignedIntegerConcept, (TValue)) :
    IntegerConcept<TValue>
{
    TValue a;
    unsigned b;
    
    SEQAN_CONCEPT_USAGE(UnsignedIntegerConcept)
    {
        a = 1u;
        b = a;

        SEQAN_STATIC_ASSERT_MSG(static_cast<TValue>(0) < static_cast<TValue>(-1), "Unsigned integer is either signed or has wrong order.");
    }
};


// This would be variant 2 (disabled for now):
/*
SEQAN_CONCEPT(IntegerConcept, (TValue))
{
    SEQAN_CONCEPT_USAGE(IntegerConcept)
    {
        x.error_type_must_be_an_integer_type();     // for the sake of readability we break the coding style rule here.
    }

private:
    T x;
};

template <> struct IntegerConcept<char> {};
template <> struct IntegerConcept<signed char> {};
template <> struct IntegerConcept<unsigned char> {};
template <> struct IntegerConcept<short> {};
template <> struct IntegerConcept<unsigned short> {};
template <> struct IntegerConcept<int> {};
template <> struct IntegerConcept<unsigned int> {};
template <> struct IntegerConcept<long> {};
template <> struct IntegerConcept<unsigned long> {};
//template <> struct IntegerConcept<__int64> {};
//template <> struct IntegerConcept<__uint64> {};

SEQAN_CONCEPT(SignedIntegerConcept, (TValue))
{
    SEQAN_CONCEPT_USAGE(SignedIntegerConcept)
    {
        x.error_type_must_be_a_signed_integer_type();
    }

private:
    T x;
};

template <> struct SignedIntegerConcept<char> {};
template <> struct SignedIntegerConcept<short> {};
template <> struct SignedIntegerConcept<int> {};
template <> struct SignedIntegerConcept<long> {};
//template <> struct SignedIntegerConcept<__int64> {};

SEQAN_CONCEPT(UnsignedIntegerConcept, (TValue))
{
    SEQAN_CONCEPT_USAGE(UnignedIntegerConcept)
    {
        x.error_type_must_be_an_unsigned_integer_type();
    }

private:
    T x;
};

template <> struct UnignedIntegerConcept<unsigned char> {};
template <> struct UnignedIntegerConcept<unsigned short> {};
template <> struct UnignedIntegerConcept<unsigned int> {};
template <> struct UnignedIntegerConcept<unsigned long> {};
//template <> struct UnignedIntegerConcept<__uint64> {};
*/

}  // namespace seqan

#endif  // #ifndef SEQAN_CORE_INCLUDE_SEQAN_BASIC_FUNDAMENTAL_CONCEPTS_H_
