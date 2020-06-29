
//////////////////////////////////////////////////////////////////////////
// Algorithm
// author: meteorchen@tencent.com
//////////////////////////////////////////////////////////////////////////

#ifndef __WBL_ARITHMETIC_H__
#define __WBL_ARITHMETIC_H__

#include <algorithm>
#include <string.h>

namespace wbl
{
/** copy if, extension of std::copy
 *  \param first		first position
 *  \param last			last position
 *  \param destBegin	output iterator
 *  \param pr			the pred
 *  \return				the output iterator
 */
template < typename II, typename OI, typename PR>
inline OI copy_if(II first, II last, OI destBegin, PR pr)
{
	while (first != last) {
		if(pr(*first))
			*destBegin++ = *first;
		++first;
	}
	return destBegin;
}

/** for_each if, extension of std::for_each
 *  \param first		first position
 *  \param last			last position
 *  \param func			the functor to execute
 *  \param pr			the pred
 *  \return				return func
 */
template < typename I, typename UF, typename UP >
inline UF for_each_if(I first, I last, UF func, UP pred)
{
    for(; first != last; ++first) {
        if(pred(*first))
            func(*first);
    }
    return func;
}

/** remove all sub sequence [first2,last2) from [first1, last1)
 *  \param first1		first position of sequence
 *  \param last1		last position of sequence
 *  \param first2		first position of sub sequence
 *  \param last2		last position of sub sequence
 *  \return				the last position of sequence after remove
 *  like std::remove, you must to erase the redundant sequence [RETURN, last1) yourself.
 */
template < typename OI, typename II >
OI remove_sub_sequence(OI first1, OI last1, II first2, II last2)
{
	OI r1 = std::search(first1, last1, first2, last2);
	OI w = r1, r2 = r1;
	const int nDiff = std::distance(first2, last2);
	while(r2 != last1){
		std::advance(r1, nDiff);						// ignore [first2, last2)
		r2 = std::search(r1, last1, first2, last2);		// find next
		while(r1 != r2){								// write element
			*w = *r1;
			++w, ++r1;
		}
	}
	return w;
}

/** remove all sub sequence [first2,last2) from [first1, last1)
 *  \param first1		first position of sequence
 *  \param last1		last position of sequence
 *  \param first2		first position of sub sequence
 *  \param last2		last position of sub sequence
 *  \param pr			pred
 *  \return				the last position of sequence after remove
 *  like std::remove, you must to erase the redundant sequence [RETURN, last1) yourself.
 */
template < typename OI, typename II, typename Pr >
OI remove_sub_sequence(OI first1, OI last1, II first2, II last2, Pr pr)
{
	OI r1 = std::search(first1, last1, first2, last2, pr);
	OI w = r1, r2 = r1;
	const int nDiff = std::distance(first2, last2);
	while(r2 != last1){
		std::advance(r1, nDiff);						// ignore [first2, last2)
		r2 = std::search(r1, last1, first2, last2, pr);	// find next
		while(r1 != r2){								// write element
			*w = *r1;
			++w, ++r1;
		}
	}
	return w;
}

/** like remove_sub_sequence, but result copy to a new sequence
 *  \param first1		first position of sequence
 *  \param last1		last position of sequence
 *  \param first2		first position of sub sequence
 *  \param last2		last position of sub sequence
 *  \return				the last position of sequence after remove
 */
template < typename II1, typename II2, typename OI >
OI remove_sub_sequence_copy(II1 first1, II1 last1, II2 first2, II2 last2, OI out)
{
	II1 r1 = std::search(first1, last1, first2, last2);
	std::copy(first1, r1, out);
	II1 r2 = r1;
	const int nDiff = std::distance(first2, last2);
	while(r2 != last1){
		std::advance(r1, nDiff);						// ignore [first2, last2)
		r2 = std::search(r1, last1, first2, last2);		// find next
		std::copy(r1, r2, out);
		r1 = r2;
	}
	return out;
}

/** like remove_sub_sequence, but result copy to a new sequence
 *  \param first1		first position of sequence
 *  \param last1		last position of sequence
 *  \param first2		first position of sub sequence
 *  \param last2		last position of sub sequence
 *  \param pr			pred
 *  \return				the last position of sequence after remove
 */
template < typename II1, typename II, typename OI, typename Pr >
OI remove_sub_sequence_copy(II1 first1, II1 last1, II first2, II last2, OI out, Pr pr)
{
	II1 r1 = std::search(first1, last1, first2, last2, pr);
	std::copy(first1, r1, out);
	II1 r2 = r1;
	const int nDiff = std::distance(first2, last2);
	while(r2 != last1){
		std::advance(r1, nDiff);						// ignore [first2, last2)
		r2 = std::search(r1, last1, first2, last2, pr);	// find next
		std::copy(r1, r2, out);
		r1 = r2;
	}
	return out;
}

/** find nth element, extension of std::find
 *  \param first		first position
 *  \param last			last position
 *  \param n			n
 *  \param v			element to find
 *  \return				the position of nth element v
 */
template < typename II, typename DiffT, typename ValT >
inline II find_n(II first, II last, DiffT n, const ValT& v)
{
	first = std::find(first, last, v);
	for(; n > 1 && first != last; --n)
		first = std::find(++first, last, v);
	return first;
}

/** find nth if, extension of std::find
 *  \param first		first position
 *  \param last			last position
 *  \param n			n
 *  \param p			pred
 *  \return				the position of nth element v
 */
template < typename II, typename DiffT, typename Pr >
inline II find_n_if(II first, II last, DiffT n, Pr p)
{
	first = std::find_if(first, last, p);
	for(; n > 1 && first != last; --n)
		first = std::find_if(++first, last, p);
	return first;
}

template<typename _InputIter1, typename _InputIter2>
int __lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
		_InputIter2 __first2, _InputIter2 __last2)
{   
	while (__first1 != __last1 && __first2 != __last2) {
		if (*__first1 < *__first2)
			return -1; 
		if (*__first2 < *__first1)
			return 1;
		++__first1;
		++__first2;
	}   
	if (__first2 == __last2) {
		return !(__first1 == __last1);
	}   
	else {
		return -1; 
	}   
}   

inline int __lexicographical_compare_3way(const unsigned char* __first1,
		const unsigned char* __last1,
		const unsigned char* __first2,
		const unsigned char* __last2)
{
	const ptrdiff_t __len1 = __last1 - __first1;
	const ptrdiff_t __len2 = __last2 - __first2;
	const int __result = memcmp(__first1, __first2, __len1 > __len2 ? __len2 : __len1);
	return __result != 0 ? __result 
		: (__len1 == __len2 ? 0 : (__len1 < __len2 ? -1 : 1));
}

inline int __lexicographical_compare_3way(const char* __first1, const char* __last1,
		const char* __first2, const char* __last2)
{
#if CHAR_MAX == SCHAR_MAX
	return __lexicographical_compare_3way(
			(const signed char*) __first1,
			(const signed char*) __last1,
			(const signed char*) __first2,
			(const signed char*) __last2);
#else
	return __lexicographical_compare_3way((const unsigned char*) __first1,
			(const unsigned char*) __last1,
			(const unsigned char*) __first2,
			(const unsigned char*) __last2);
#endif
}

/**
 *  lexicographical compare
 *  \param  first1  An input iterator.
 *  \param  last1   An input iterator.
 *  \param  first2  An input iterator.
 *  \param  last2   An input iterator.
 *  \return   An int, as with memcmp.
 *
 *  The return value will be less than zero if the first range is
 *  "lexigraphically less than" the second, greater than zero if the second
 *  range is "lexigraphically less than" the first, and zero otherwise.
 */
template<typename _InputIter1, typename _InputIter2>
int lexicographical_compare_3way(_InputIter1 first1, _InputIter1 last1,
		_InputIter2 first2, _InputIter2 last2)
{
	return __lexicographical_compare_3way(first1, last1, first2, last2);
}

/** is_sorted, a predicated testing whether a range is sorted in nondescending order.
 *  \param __first	first position
 *  \param __last	last position
 *  \return			if the sequence is sorted by <, return true, otherwise return false
 */
template<typename _ForwardIter>
bool is_sorted(_ForwardIter __first, _ForwardIter __last)
{
	if (__first == __last)
		return true;

	_ForwardIter __next = __first;
	for (++__next; __next != __last; __first = __next, ++__next) {
		if (*__next < *__first)
			return false;
	}

	return true;
}

/** is_sorted, a predicated testing whether a range is sorted in nondescending order.
 *  \param __first	first position
 *  \param __last	last position
 *  \param __comp	less compare
 *  \return			if the sequence is sorted by __comp, return true, otherwise return false
 */
template<typename _ForwardIter, typename _StrictWeakOrdering>
bool is_sorted(_ForwardIter __first, _ForwardIter __last, _StrictWeakOrdering __comp)
{
	if (__first == __last)
		return true;

	_ForwardIter __next = __first;
	for (++__next; __next != __last; __first = __next, ++__next) {
		if (__comp(*__next, *__first))
			return false;
	}

	return true;
}

}

#endif

