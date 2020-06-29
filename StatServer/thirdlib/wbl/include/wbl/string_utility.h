
//////////////////////////////////////////////////////////////////////////
//
// 9/24/2003 by meteorchen@tencent.com
// 常用的字符串操作
//
//////////////////////////////////////////////////////////////////////////

#ifndef __WBL_STRING_UTILITY_H__
#define __WBL_STRING_UTILITY_H__

#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iosfwd>
#include <cassert>
#include <functional>
#include <iterator>
#include <wbl/macros.h>
#include <wbl/arithmetic.h>

namespace wbl
{

//////////////////////////////////////////////////////////////////////////
// CodePage Convert
/** convert a string to wstring
 *  \param str		source string
 *  \param count	length of source string
 *  \param wstr		result wstring
 *  \return			if success return true, otherwise return false
 */
template < typename Tr, typename A >
inline bool str2wstr(const char* str, size_t count, std::basic_string<wchar_t, Tr, A>& wstr)
{
	WBL_ASSERT(str != NULL && count >= 0);

	wchar_t *pBuf = new wchar_t[count + 1];
	size_t n = ::mbstowcs(pBuf, str, count);
	if(n == size_t(-1)){	// odd style, look at msdn
		delete[] pBuf;
		return false;
	}
	pBuf[n] = 0;
	wstr = pBuf;
	delete[] pBuf;
	return true;
}

/** convert a string to wstring
 *  \param str	source string
 *  \param wstr	result wstring
 *  \return		if match return true, otherwise return false
 */
inline bool str2wstr(const std::string& str, std::wstring& wstr)
{
	return str2wstr(str.c_str(), str.size(), wstr);
}

/** convert a string to wstring
 *  \param str	source string
 *  \return		result wstring
 */
inline std::wstring str2wstr(const char * str)
{
	WBL_ASSERT(str != NULL);

	std::wstring wstr;
	str2wstr(str, strlen(str), wstr);
	return wstr;
}

/** convert a string to wstring
 *  \param str	source string
 *  \return		result wstring
 */
inline std::wstring str2wstr(const std::string& str)
{
	std::wstring wstr;
	str2wstr(str.c_str(), str.size(), wstr);
	return wstr;
}

/** convert a wstring to string
 *  \param wstr		source wstring
 *  \param count	length of source wstring
 *  \param str		result string
 *  \return			if success return true, otherwise return false
 */
template < typename Tr, typename A >
inline bool wstr2str(const wchar_t * wstr, size_t count, std::basic_string<char, Tr, A>& str)
{
	WBL_ASSERT(wstr != NULL && count >= 0);

	const size_t nBufLen = count * 2 + 1;
	char *pBuf = new char[nBufLen];
	size_t n = ::wcstombs(pBuf, wstr, nBufLen);
	if(n == size_t(-1)){	// odd style, look at msdn
		delete[] pBuf;
		return false;
	}
	pBuf[n] = 0;
	str = pBuf;
	delete[] pBuf;
	return true;
}

/** convert a wstring to string
 *  \param wstr		source wstring
 *  \return			result string
 */
inline std::string wstr2str(const wchar_t* wstr)
{
	std::string str;
	wstr2str(wstr, wcslen(wstr), str);
	return str;
}

/** convert a wstring to string
 *  \param wstr		source wstring
 *  \return			result string
 */
inline std::string wstr2str(const std::wstring& wstr)
{
	std::string str;
	wstr2str(wstr.c_str(), wstr.size(), str);
	return str;
}

/** convert a wstring to string
 *  \param wstr		source wstring
 *  \param str		result string
 *  \return			if success return true, otherwise return false
 */
inline bool wstr2str(const std::wstring& wstr, std::string& str)
{
	return wstr2str(wstr.c_str(), wstr.size(), str);
}

//////////////////////////////////////////////////////////////////////////
// tchar traits

template < typename Ch >
struct CharTraits : public std::char_traits < Ch > {};

template <>
struct CharTraits < char > : public std::char_traits < char >
{
	typedef std::string StringT;

	static int_type ttolower(int_type c)	{ return ::tolower(c); }
	static int_type ttoupper(int_type c)	{ return ::toupper(c); }

	static int tisspace(int_type c)		{ return ::isspace(c); }
	static int tisalnum(int_type c)		{ return ::isalnum(c); }
	static int tisalpha(int_type c)		{ return ::isalpha(c); }
	static int tisdigit(int_type c)		{ return ::isdigit(c); }
	static int tisgraph(int_type c)		{ return ::isgraph(c); }
	static int tislower(int_type c)		{ return ::islower(c); }
	static int tisprint(int_type c)		{ return ::isprint(c); }
	static int tispunct(int_type c)		{ return ::ispunct(c); }
	static int tisupper(int_type c)		{ return ::isupper(c); }
	static int tisxdigit(int_type c)	{ return ::isxdigit(c); }
	static int tiscntrl(int_type c)		{ return ::iscntrl(c); }

	static char_type* tstrcat(char_type *dest, const char_type *src)					{ return ::strcat(dest, src); }
	static const char_type* tstrchr(const char_type *s, char_type c)							{ return ::strchr(s, c); }
	static int tstrcmp(const char_type *s1, const char_type *s2)						{ return ::strcmp(s1, s2); }
	static char_type* tstrcpy(char_type *dest, const char_type *src)					{ return ::strcpy(dest, src); }
	static size_t tstrlen(const char_type *s)											{ return ::strlen(s); }
	static char_type* tstrncat(char_type *dest, const char_type *src, size_t count)		{ return ::strncat(dest, src, count); }
	static int tstrncmp(const char_type *s1, const char_type *s2, size_t count)			{ return ::strncmp(s1, s2, count); }
	static char_type* tstrncpy(char_type *dest, const char_type *src, size_t count)		{ return ::strncpy(dest, src, count); }
	static const char_type* tstrstr(const char_type *s, const char_type *sub)					{ return ::strstr(s, sub); }

	static double tstrtod(const char_type* nptr, char_type** endptr)					{ return ::strtod(nptr, endptr); }
	static long tstrtol(const char_type* nptr, char_type** endptr, int base)			{ return ::strtol(nptr, endptr, base); }
	static unsigned long tstrtoul(const char_type* nptr, char_type** endptr, int base)	{ return ::strtoul(nptr, endptr, base); }

	static char_type* tstrend(char_type* s)												{ return ::strchr(s, 0); }
	static const char_type* tstrend(const char_type* s)									{ return ::strchr(s, 0); }

	template < typename Tr, typename A >
	static void ttombs(const char_type* s, size_t count, std::basic_string<char, Tr, A>& str)
	{ str.assign(s, count); }

	template < typename Tr, typename A >
	static void ttowcs(const char_type* s, size_t count, std::basic_string<wchar_t, Tr, A>& wstr)
	{ str2wstr(s, count, wstr); }

	template < typename Tr, typename A >
	static void tfrommbs(const char* mbs, size_t count, std::basic_string<char_type, Tr, A>& str)
	{ str.assign(mbs, count); }

	template < typename Tr, typename A >
	static void tfromwcs(const wchar_t* wcs, size_t count, std::basic_string<char_type, Tr, A>& str)
	{ wstr2str(wcs, count, str); }
};

template <>
struct CharTraits < wchar_t > : public std::char_traits < wchar_t >
{
	typedef std::wstring	StringT;

	static int_type ttolower(int_type c)	{ return ::towlower(c); }
	static int_type ttoupper(int_type c)	{ return ::towupper(c); }

	static int tisspace(int_type c)		{ return ::iswspace(c); }
	static int tisalnum(int_type c)		{ return ::iswalnum(c); }
	static int tisalpha(int_type c)		{ return ::iswalpha(c); }
	static int tisdigit(int_type c)		{ return ::iswdigit(c); }
	static int tisgraph(int_type c)		{ return ::iswgraph(c); }
	static int tislower(int_type c)		{ return ::iswlower(c); }
	static int tisprint(int_type c)		{ return ::iswprint(c); }
	static int tispunct(int_type c)		{ return ::iswpunct(c); }
	static int tisupper(int_type c)		{ return ::iswupper(c); }
	static int tisxdigit(int_type c)	{ return ::iswxdigit(c); }
	static int tiscntrl(int_type c)		{ return ::iswcntrl(c); }

	static char_type* tstrcat(char_type *dest, const char_type *src)					{ return ::wcscat(dest, src); }
	static const char_type* tstrchr(const char_type *s, char_type c)							{ return ::wcschr(s, c); }
	static int tstrcmp(const char_type *s1, const char_type *s2)						{ return ::wcscmp(s1, s2); }
	static char_type* tstrcpy(char_type *dest, const char_type *src)					{ return ::wcscpy(dest, src); }
	static size_t tstrlen(const char_type *s)											{ return ::wcslen(s); }
	static char_type* tstrncat(char_type *dest, const char_type *src, size_t count)		{ return ::wcsncat(dest, src, count); }
	static int tstrncmp(const char_type *s1, const char_type *s2, size_t count)			{ return ::wcsncmp(s1, s2, count); }
	static char_type* tstrncpy(char_type *dest, const char_type *src, size_t count)		{ return ::wcsncpy(dest, src, count); }
	static const char_type* tstrstr(const char_type *s, const char_type *sub)					{ return ::wcsstr(s, sub); }

	static double tstrtod(const char_type* nptr, char_type** endptr)					{ return ::wcstod(nptr, endptr); }
	static long tstrtol(const char_type* nptr, char_type** endptr, int base)			{ return ::wcstol(nptr, endptr, base); }
	static unsigned long tstrtoul(const char_type* nptr, char_type** endptr, int base)	{ return ::wcstoul(nptr, endptr, base); }

	static char_type* tstrend(char_type* s)												{ return ::wcschr(s, 0); }
	static const char_type* tstrend(const char_type* s)									{ return ::wcschr(s, 0); }

	template < typename Tr, typename A >
	static void ttombs(const char_type* s, size_t count, std::basic_string<char, Tr, A>& str)
	{ wstr2str(s, count, str); }

	template < typename Tr, typename A >
	static void ttowcs(const char_type* s, size_t count, std::basic_string<wchar_t, Tr, A>& wstr)
	{ wstr.assign(s, count); }

	template < typename Tr, typename A >
	static void tfrommbs(const char* mbs, size_t count, std::basic_string<char_type, Tr, A>& str)
	{ str2wstr(mbs, count, str); }

	template < typename Tr, typename A >
	static void tfromwcs(const wchar_t* wcs, size_t count, std::basic_string<char_type, Tr, A>& str)
	{ str.assign(wcs, count); }
};

//////////////////////////////////////////////////////////////////////////
// Compare Functional

/** character equal compare ignore case
 */
template < typename Ch >
struct ch_equal_to_nocase : public std::binary_function < Ch, Ch, bool >
{
	bool operator()(Ch c1, Ch c2) const
	{
		return CharTraits<Ch>::ttoupper(c1) == CharTraits<Ch>::ttoupper(c2);
	}
};

/** character equal compare ignore case
 */
template < typename Ch >
class ch_equal_nocase : public std::unary_function < Ch, bool >
{
	typename CharTraits<Ch>::int_type	m_ch;
public:
	ch_equal_nocase(Ch c)
		: m_ch(CharTraits<Ch>::ttoupper(c))
	{}

	bool operator()(Ch c) const
	{
		return m_ch == CharTraits<Ch>::ttoupper(c);
	}
};

//////////////////////////////////////////////////////////////////////////
// Trim Utility

/** trim left
 *  \param s	string to trim
 */
template < typename Ch, typename Tr, typename A >
inline void TrimLeft(std::basic_string<Ch, Tr, A>& s)
{
	typename std::basic_string<Ch, Tr, A>::iterator it = s.begin();
	while(it != s.end() && CharTraits<Ch>::tisspace(*it))
		++it;
	s.erase(s.begin(), it);
}

/** trim left copy
 *  \param s	string to trim
 *  \return		result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> TrimLeftCopy(const std::basic_string<Ch, Tr, A>& s)
{
	typename std::basic_string<Ch, Tr, A>::const_iterator it = s.begin();
	while(it != s.end() && CharTraits<Ch>::tisspace(*it))
		++it;
	return std::basic_string<Ch, Tr, A>(it, s.end());
}

/** trim left
 *  \param s	string to trim
 */
template < typename Ch >
inline void TrimLeft(Ch * s)
{
	WBL_ASSERT(s != NULL);

	// find first non-space position
	Ch *p = s;
	while(CharTraits<Ch>::tisspace(*p))
		++p;
	// move to front
	while(*p != 0)
		*s++ = *p++;
	*s = 0;
}

/** trim left copy
 *  \param s	string to trim
 *  \return		result
 */
template < typename Ch >
inline std::basic_string<Ch> TrimLeftCopy(const Ch * s)
{
	WBL_ASSERT(s != NULL);

	// find first non-space position
	const Ch *p = s;
	while(CharTraits<Ch>::tisspace(*p))
		++p;
	return std::basic_string<Ch>(p);
}

/** trim left
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 */
template < typename Ch, typename Tr, typename A, typename TrimStrT >
inline void TrimLeft(std::basic_string<Ch, Tr, A>& s, const TrimStrT& szTrim)
{
	s.erase(0, s.find_first_not_of(szTrim));
}

/** trim left copy
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A, typename TrimStrT >
inline std::basic_string<Ch, Tr, A> TrimLeftCopy(const std::basic_string<Ch, Tr, A>& s, const TrimStrT& szTrim)
{
	return s.substr(s.find_first_not_of(szTrim));
}

/** trim left
 *  \param str		the string to trim
 *  \param szTrim	characters to remove
 */
template < typename Ch >
inline void TrimLeft(Ch *str, const Ch *szTrim)
{
	WBL_ASSERT(str != NULL && szTrim != NULL);

	// find character not in szTrim
	const Ch *pTrimEnd = CharTraits<Ch>::tstrend(szTrim);
	Ch *p = str;
	while(std::find(szTrim, pTrimEnd, *p) != pTrimEnd)
		++p;
	// move to front
	while(*p != 0)
		*str++ = *p++;
	*str = 0;
}

/** trim left copy
 *  \param str		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> TrimLeftCopy(const Ch *str, const Ch *szTrim)
{
	WBL_ASSERT(str != NULL && szTrim != NULL);

	// find character not in szTrim
	const Ch *pTrimEnd = CharTraits<Ch>::tstrend(szTrim);
	const Ch *p = str;
	while(std::find(szTrim, pTrimEnd, *p) != pTrimEnd)
		++p;
	return std::basic_string<Ch>(p);
}

/** trim right
 *  \param s		the string to trim
 */
template < typename Ch, typename Tr, typename A >
inline void TrimRight(std::basic_string<Ch, Tr, A>& s)
{
	typename std::basic_string<Ch, Tr, A>::iterator it = s.end();
	if(it == s.begin())
		return;
	while(it != s.begin() && CharTraits<Ch>::tisspace(*--it));
	s.erase(it + 1, s.end());
}

/** trim right copy
 *  \param s		the string to trim
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> TrimRightCopy(const std::basic_string<Ch, Tr, A>& s)
{
	typename std::basic_string<Ch, Tr, A>::const_iterator it = s.end();
	if(it == s.begin())
		return;
	while(it != s.begin() && CharTraits<Ch>::tisspace(*--it));
	return s.substr(s.begin(), it + 1);
}

/** trim right
 *  \param s		the string to trim
 */
template < typename Ch >
inline void TrimRight(Ch * s)
{
	WBL_ASSERT(s != NULL);

	// find last non-space position
	Ch *pEnd = NULL;
	while(*s != 0){
		if(!CharTraits<Ch>::tisspace(*s))
			pEnd = ++s;
		else
			++s;
	}
	// cut down
	if(pEnd != NULL)
		*pEnd = 0;
}

/** trim right copy
 *  \param s		the string to trim
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> TrimRightCopy(const Ch * s)
{
	WBL_ASSERT(s != NULL);

	// find last non-space position
	const Ch *pEnd = NULL;
	while(*s != 0){
		if(!CharTraits<Ch>::tisspace(*s))
			pEnd = ++s;
		else
			++s;
	}
	return pEnd != NULL ? std::basic_string<Ch>(s, pEnd) : std::basic_string<Ch>(s);
}

/** trim right
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 */
template < typename Ch, typename Tr, typename A, typename TrimStrT >
inline void TrimRight(std::basic_string<Ch, Tr, A>& s, const TrimStrT& szTrim)
{
	s.erase(s.find_last_not_of(szTrim) + 1);
}

/** trim right copy
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A, typename TrimStrT >
inline std::basic_string<Ch, Tr, A> TrimRightCopy(const std::basic_string<Ch, Tr, A>& s, const TrimStrT& szTrim)
{
	return s.substr(0, s.find_last_not_of(szTrim) + 1);
}

/** trim right
 *  \param str		the string to trim
 *  \param szTrim	characters to remove
 */
template < typename Ch >
inline void TrimRight(Ch *str, const Ch *szTrim)
{
	WBL_ASSERT(str != NULL && szTrim != NULL);

	// find last character not in szTrim
	const Ch *pTrimEnd = CharTraits<Ch>::tstrend(szTrim);
	Ch *pEnd = NULL;
	while(*str != 0){
		if(std::find(szTrim, pTrimEnd, *str) == pTrimEnd)
			pEnd = ++str;	// record the last character not in szTrim
		else
			++str;
	}
	// cut down
	if(pEnd != NULL)
		*pEnd = 0;
}

/** trim right copy
 *  \param str		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> TrimRightCopy(const Ch *str, const Ch *szTrim)
{
	WBL_ASSERT(str != NULL && szTrim != NULL);

	// find last character not in szTrim
	const Ch *pTrimEnd = CharTraits<Ch>::tstrend(szTrim);
	Ch *pEnd = NULL;
	while(*str != 0){
		if(std::find(szTrim, pTrimEnd, *str) == pTrimEnd)
			pEnd = ++str;	// record the last character not in szTrim
		else
			++str;
	}
	return pEnd != NULL ? std::basic_string<Ch>(str, pEnd) : std::basic_string<Ch>(str);
}

/** trim left and right
 *  \param s		the string to trim
 */
template < typename Ch, typename Tr, typename A >
inline void Trim(std::basic_string<Ch, Tr, A>& s)
{
	TrimRight(s);
	TrimLeft(s);
}

/** trim left and right copy
 *  \param s		the string to trim
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> TrimCopy(const std::basic_string<Ch, Tr, A>& s)
{
	std::basic_string<Ch, Tr, A> ss = TrimLeftCopy(s);
	TrimRight(ss);
	return ss;
}

/** trim left and right
 *  \param s		the string to trim
 */
template < typename Ch >
void Trim(Ch *s)
{
	WBL_ASSERT(s != NULL);
	
	// find begin
	Ch *pBegin = s;
	while(CharTraits<Ch>::tisspace(*pBegin))
		++pBegin;
	// find end
	Ch *pEnd = NULL, *pTmp = pBegin;
	while(*pTmp != 0){
		if(!CharTraits<Ch>::tisspace(*pTmp))
			pEnd = ++pTmp;
		else
			++pTmp;
	}
	// move string
	if(pEnd == NULL)
		pEnd = pTmp;
	while(pBegin != pEnd)
		*s++ = *pBegin++;
	*s = 0;
}

/** trim left and right copy
 *  \param s		the string to trim
 *  \return			result
 */
template < typename Ch >
std::basic_string<Ch> TrimCopy(const Ch *s)
{
	WBL_ASSERT(s != NULL);
	
	// find begin
	const Ch *pBegin = s;
	while(CharTraits<Ch>::tisspace(*pBegin))
		++pBegin;
	// find end
	const Ch *pEnd = NULL, *pTmp = pBegin;
	while(*pTmp != 0){
		if(!CharTraits<Ch>::tisspace(*pTmp))
			pEnd = ++pTmp;
		else
			++pTmp;
	}
	// move string
	if(pEnd == NULL)
		pEnd = pTmp;
	return std::basic_string<Ch>(pBegin, pEnd);
}

/** trim left and right
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 */
template < typename StringT, typename TrimStrT >
inline void Trim(StringT& s, const TrimStrT& szTrim)
{
	TrimRight(s, szTrim);
	TrimLeft(s, szTrim);
}

/** trim left and right copy
 *  \param s		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A, typename TrimStrT >
inline std::basic_string<Ch, Tr, A> TrimCopy(const std::basic_string<Ch, Tr, A>& s, const TrimStrT& szTrim)
{
	std::basic_string<Ch, Tr, A> ss = TrimLeftCopy(s, szTrim);
	TrimRight(ss, szTrim);
	return ss;
}

/** trim left and right copy
 *  \param str		the string to trim
 *  \param szTrim	characters to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> TrimCopy(const Ch *str, const Ch *szTrim)
{
	WBL_ASSERT(str != NULL && szTrim != NULL);
	std::basic_string<Ch> ss = TrimLeftCopy(str, szTrim);
	TrimLeft(ss, szTrim);
	return ss;
}

//////////////////////////////////////////////////////////////////////////
// Case Convert Utility

/** make string to upper
 *  \param s	string to make upper
 */
template < typename Ch, typename Tr, typename A >
inline void MakeUpper(std::basic_string<Ch, Tr, A>& s)
{
	std::transform(s.begin(), s.end(), s.begin(), 
		CharTraits<Ch>::ttoupper);
}

/** make string to upper
 *  \param s	string to make upper
 */
template < typename Ch >
inline void MakeUpper(Ch *s)
{
	WBL_ASSERT(s != NULL);
	while(*s != 0)
		*s++ = CharTraits<Ch>::ttoupper(*s);
}

/** make string to lower
 *  \param s	string to make lower
 */
template < typename Ch, typename Tr, typename A >
inline void MakeLower(std::basic_string<Ch, Tr, A>& s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		CharTraits<Ch>::ttolower);
}

/** make string to lower
 *  \param s	string to make lower
 */
template < typename Ch >
inline void MakeLower(Ch *s)
{
	WBL_ASSERT(s != NULL);
	while(*s != 0)
		*s++ = CharTraits<Ch>::ttolower(*s);
}

/** Converts all of the characters in this String to upper case
 *  \param s	source string
 *  \return		result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ToUpper(const std::basic_string<Ch, Tr, A>& s)
{
	std::basic_string<Ch, Tr, A> r;
	r.reserve(s.size());
	std::transform(s.begin(), s.end(), std::inserter(r, r.end()),
		CharTraits<Ch>::ttoupper);
	return r;
}

/** Converts all of the characters in this String to upper case
 *  \param s	source string
 *  \return		result
 */
template < typename Ch >
inline std::basic_string<Ch> ToUpper(const Ch *s)
{
	WBL_ASSERT(s != NULL);
	std::basic_string<Ch> ss(s);
	MakeUpper(ss);
	return ss;
}

/** Converts all of the characters in this String to lower case
 *  \param s	source string
 *  \return		result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ToLower(const std::basic_string<Ch, Tr, A>& s)
{
	std::basic_string<Ch, Tr, A> r;
	r.reserve(s.size());
	std::transform(s.begin(), s.end(), std::inserter(r, r.end()),
		CharTraits<Ch>::ttolower);
	return r;
}

/** Converts all of the characters in this String to lower case
 *  \param s	source string
 *  \return		result
 */
template < typename Ch >
inline std::basic_string<Ch> ToLower(const Ch *s)
{
	WBL_ASSERT(s != NULL);
	std::basic_string<Ch> ss(s);
	MakeLower(ss);
	return ss;
}

//////////////////////////////////////////////////////////////////////////
// StartsWith Utility

/** Tests if this sequence starts with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \param pr	equal compare
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename II1, typename II2, typename Pr >
inline bool StartsWith(II1 f1, II1 l1, II2 f2, II2 l2, Pr pr)
{
	for(; f1 != l1 && f2 != l2; ++f1, ++f2){
		if(!pr(*f1, *f2))
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename II1, typename II2 >
inline bool StartsWith(II1 f1, II1 l1, II2 f2, II2 l2)
{
	for(; f1 != l1 && f2 != l2; ++f1, ++f2){
		if(*f1 != *f2)
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch >
inline bool StartsWith(const Ch* s1, const Ch* s2)
{
	return StartsWith(s1, CharTraits<Ch>::tstrend(s1), 
			s2, CharTraits<Ch>::tstrend(s2));
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWith(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return StartsWith(s1.begin(), s1.end(), s2.begin(), s2.end());
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWith(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return StartsWith(s1.begin(), s1.end(), 
			s2, CharTraits<Ch>::tstrend(s2));
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWith(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return StartsWith(s1, CharTraits<Ch>::tstrend(s1),
			s2.begin(), s2.end());
}

/** Tests if this sequence starts with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch >
inline bool StartsWithNoCase(const Ch* s1, const Ch* s2)
{
	return StartsWith(s1, CharTraits<Ch>::tstrend(s1), 
			s2, CharTraits<Ch>::tstrend(s2), ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence starts with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWithNoCase(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return StartsWith(s1.begin(), s1.end(), s2.begin(), s2.end(), ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence starts with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWithNoCase(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return StartsWith(s1.begin(), s1.end(), 
			s2, CharTraits<Ch>::tstrend(s2),
			ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence starts with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool StartsWithNoCase(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return StartsWith(s1, CharTraits<Ch>::tstrend(s1),
			s2.begin(), s2.end(), ch_equal_to_nocase<Ch>());
}

//////////////////////////////////////////////////////////////////////////
// EndsWith Utility

/** Tests if this sequence ends with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \param pr	equal compare
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename BI1, typename BI2, typename Pr >
inline bool EndsWith(BI1 f1, BI1 l1, BI2 f2, BI2 l2, Pr pr)
{
	for(--f1,--l1,--f2,--l2; f1 != l1 && f2 != l2; --l1, --l2){
		if(!pr(*l1, *l2))
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence ends with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename II1, typename II2 >
inline bool EndsWith(II1 f1, II1 l1, II2 f2, II2 l2)
{
	for(--f1,--l1,--f2,--l2; f1 != l1 && f2 != l2; --l1, --l2){
		if(*l1 != *l2)
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence ends with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch >
inline bool EndsWith(const Ch* s1, const Ch* s2)
{
	return EndsWith(s1, CharTraits<Ch>::tstrend(s1), 
			s2, CharTraits<Ch>::tstrend(s2));
}

/** Tests if this sequence ends with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWith(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return EndsWith(s1.begin(), s1.end(), s2.begin(), s2.end());
}

/** Tests if this sequence ends with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWith(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return EndsWith(s1.begin(), s1.end(), 
			s2, CharTraits<Ch>::tstrend(s2));
}

/** Tests if this sequence ends with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWith(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return EndsWith(s1, CharTraits<Ch>::tstrend(s1),
			s2.begin(), s2.end());
}

/** Tests if this sequence ends with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch >
inline bool EndsWithNoCase(const Ch* s1, const Ch* s2)
{
	return EndsWith(s1, CharTraits<Ch>::tstrend(s1), 
			s2, CharTraits<Ch>::tstrend(s2), ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence ends with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWithNoCase(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return EndsWith(s1.begin(), s1.end(), 
			s2.begin(), s2.end(), ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence ends with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWithNoCase(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return EndsWith(s1.begin(), s1.end(), 
			s2, CharTraits<Ch>::tstrend(s2),
			ch_equal_to_nocase<Ch>());
}

/** Tests if this sequence ends with the specified prefix sequence, ignore case
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename Ch, typename Tr, typename A >
inline bool EndsWithNoCase(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return EndsWith(s1, CharTraits<Ch>::tstrend(s1),
			s2.begin(), s2.end(), ch_equal_to_nocase<Ch>());
}

//////////////////////////////////////////////////////////////////////////
// Compare Utility
/** compare
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch >
inline int Compare(const Ch* s1, const Ch* s2)
{
	return strcmp(s1, s2);
}

/** compare
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int Compare(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return s1.compare(s2);
}

/** compare
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int Compare(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return s1.compare(s2);
}

/** compare
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int Compare(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return -s2.compare(s1);
}

//////////////////////////////////////////////////////////////////////////
// Ignore Case Compare Utility

/** compare ignore case
 *  \param f1	start of first sequence
 *  \param l1	end of first sequence
 *  \param f2	start of second sequence
 *  \param l2	end of sequence sequence
 *  \return		0 if two sequence equals, positive number if first sequence
 *  			large than second sequence, negative otherwise
 */
template < typename II1, typename II2, typename Ch >
inline int CompareNoCase(II1 f1, II1 l1, II2 f2, II2 l2, Ch)
{
	for(; f1 != l1 && f2 != l2; ++f1, ++f2){
		int r = CharTraits<Ch>::ttolower(*f1)
			- CharTraits<Ch>::ttolower(*f2);
		if(r > 0)
			return 1;
		if(r < 0)
			return -1;
	}
	if(f1 == l1)
		return f2 == l2 ? 0 : -1;
	return 1;
}

/** compare ignore case
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch >
inline int CompareNoCase(const Ch* s1, const Ch* s2)
{
	WBL_ASSERT(s1 != NULL && s2 != NULL);
	return CompareNoCase(s1, CharTraits<Ch>::tstrend(s1),
			s2, CharTraits<Ch>::tstrend(s2), Ch());
}

/** compare ignore case
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int CompareNoCase(const std::basic_string<Ch, Tr, A>& s1,
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return CompareNoCase(s1.begin(), s1.end(), s2.begin(), s2.end(), Ch());
}

/** compare ignore case
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int CompareNoCase(const std::basic_string<Ch, Tr, A>& s1, 
						 const Ch* s2)
{
	return CompareNoCase(s1.begin(), s1.end(), 
			s2, CharTraits<Ch>::tstrend(s2), Ch());
}

/** compare ignore case
 *  \param s1	first string
 *  \param s2	second string
 *  \return		0 if two string equals, positive number if first string
 *  			large than second string, negative otherwise
 */
template < typename Ch, typename Tr, typename A >
inline int CompareNoCase(const Ch* s1, 
						 const std::basic_string<Ch, Tr, A>& s2)
{
	return CompareNoCase(s1, CharTraits<Ch>::tstrend(s1),
			s2.begin(), s2.end(), Ch());
}

//////////////////////////////////////////////////////////////////////////
// Replace Utility

/** replace all chOld to chNew in string s
 */
template < typename Ch, typename Tr, typename A >
inline void ReplaceAll(std::basic_string<Ch, Tr, A>& s,
					   Ch chOld,
					   Ch chNew)
{
	std::replace(s.begin(), s.end(), chOld, chNew);
}

/** replace all chOld to chNew in string s
 */
template < typename Ch >
inline void ReplaceAll(Ch * s,
					   Ch chOld,
					   Ch chNew)
{
	std::replace(s, CharTraits<Ch>::tstrend(s), chOld, chNew);
}

/** replace all sequence [fo, lo) to sequence [fn, ln] in string s
 *  return value means the count of [fo, lo) replaced.
 */
template < typename Ch, typename Tr, typename A, typename II_O, typename II_N, typename Pr >
int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  II_O fo,
					  II_O lo,
					  II_N fn,
					  II_N ln,
					  Pr pr)
{
	if(fo == lo)
		return 0;

	typedef std::basic_string<Ch, Tr, A> StrT;
	typename StrT::iterator iPos = std::search(s.begin(), s.end(),
		fo, lo, pr);								// current position szOld in s
	if(iPos == s.end())
		return 0;
	typename StrT::iterator iWrite = s.begin();		// position writed in s
	StrT str;										// temp string to save result
	int nCount = 0;									// count of replacement
	int nOldSize = std::distance(fo, lo);
	int nNewSize = std::distance(fn, ln);
	str.reserve(nNewSize < nOldSize ? s.size() : (s.size() * 2));
	for(; iPos != s.end(); ++nCount){
		str.append(iWrite, iPos);					// append src string
		str.append(fn, ln);							// append szNew
		iWrite = iPos + nOldSize;					// ignore szOld
		iPos = std::search(iWrite, s.end(),
			fo, lo, pr);							// find next
	}
	str.append(iWrite, s.end());					// append last sub-string
	s.swap(str);
	return nCount;
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A, typename Pr >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew,
					  Pr pr)
{
	return ReplaceAll(s, szOld.begin(), szOld.end(),
			szNew.begin(), szNew.end(), pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template<typename Ch, typename Tr, typename A>
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAll(s, szOld, szNew, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A, typename Pr >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew,
					  Pr pr)
{
	WBL_ASSERT(szOld != NULL && szNew != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	WBL_ASSERT(szOld != NULL && szNew != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	WBL_ASSERT(szNew != NULL);

	return ReplaceAll(s, szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	WBL_ASSERT(szOld != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	WBL_ASSERT(szOld != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	WBL_ASSERT(szOld != NULL);

	return ReplaceAll(s, szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAll(s, &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAll(std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	return ReplaceAll(s, &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), std::equal_to<Ch>());
}

/** replace all chOld to chNew in string s, ignore case
 */
template < typename Ch, typename Tr, typename A >
inline void ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s,
					   Ch chOld,
					   Ch chNew)
{
	std::replace_if(s.begin(), s.end(), ch_equal_nocase<Ch>(chOld), chNew);
}

/** replace all chOld to chNew in string s, ignore case
 */
template < typename Ch >
inline void ReplaceAllNoCase(Ch * s,
					   Ch chOld,
					   Ch chNew)
{
	std::replace_if(s, CharTraits<Ch>::tstrend(s), ch_equal_nocase<Ch>(chOld), chNew);
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAll(s, szOld, szNew, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	assert(szOld != NULL && szNew != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	assert(szNew != NULL);

	return ReplaceAll(s, szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	assert(szOld != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	assert(szOld != NULL);

	return ReplaceAll(s, szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	assert(szOld != NULL);

	return ReplaceAll(s, szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAll(s, &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline int ReplaceAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	return ReplaceAll(s, &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), ch_equal_to_nocase<Ch>());
}

//////////////////////////////////////////////////////////////////////////
// Replace Copy Utility
/** replace all chOld to chNew in string s
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s,
					   Ch chOld,
					   Ch chNew)
{
	std::basic_string<Ch, Tr, A> ss(s);
	std::replace(ss.begin(), ss.end(), chOld, chNew);
	return ss;
}

/** replace all chOld to chNew in string s
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllCopy(const Ch * s,
					   Ch chOld,
					   Ch chNew)
{
	std::basic_string<Ch> ss(s);
	std::replace(ss.begin(), ss.end(), chOld, chNew);
	return ss;
}

/** replace all sequence [fo, lo) to sequence [fn, ln] in string s
 *  return value means the count of [fo, lo) replaced.
 */
template < typename II_S, typename II_O, typename II_N, typename OI, typename Pr >
void ReplaceAllCopy(II_S fs, II_S ls, 
					  II_O fo,
					  II_O lo,
					  II_N fn,
					  II_N ln,
					  OI out,
					  Pr pr)
{
	if(fo == lo){
		std::copy(fs, ls, out);
		return;
	}

	II_S iPos = std::search(fs, ls,
		fo, lo, pr);								// current position szOld in s
	if(iPos == ls){
		std::copy(fs, ls, out);
		return;
	}
	int nOldSize = std::distance(fo, lo);
	II_S iWrite = fs;		// position writed in s
	for(; iPos != ls; ){
		std::copy(iWrite, iPos, out);				// append src string
		std::copy(fn, ln, out);						// append szNew
		iWrite = iPos + nOldSize;					// ignore szOld
		iPos = std::search(iWrite, ls,
			fo, lo, pr);							// find next
	}
	std::copy(iWrite, ls, out);						// append last sub-string
}

template < typename Ch, typename Tr, typename A, typename II_S, typename II_O, typename II_N, typename Pr >
inline std::basic_string<Ch, Tr, A>& ReplaceAllCopyImpl(II_S fs, II_S ls, 
					  II_O fo,
					  II_O lo,
					  II_N fn,
					  II_N ln,
					  std::basic_string<Ch, Tr, A>& out,
					  Pr pr)
{
	const int nSize = std::distance(fs, ls);
	const int nOldSize = std::distance(fo, lo);
	const int nNewSize = std::distance(fn, ln);
	out.reserve(nNewSize < nOldSize ? nSize : (nSize * 2));
	ReplaceAllCopy(fs, ls, fo, lo, fn, ln, std::back_inserter(out), pr);
	return out;
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A, typename Pr >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew,
					  Pr pr)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld.begin(), szOld.end(),
			szNew.begin(), szNew.end(), str, pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A, typename Pr >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew,
					  Pr pr)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld.begin(), szOld.end(),
			szNew.begin(), szNew.end(), str, pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template<typename Ch, typename Tr, typename A>
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, szNew, str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template<typename Ch, typename Tr, typename A>
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, szNew, str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A, typename Pr >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew,
					  Pr pr)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \param pr		compare functor
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Pr >
inline std::basic_string<Ch> ReplaceAllCopy(const Ch * s, 
					  const Ch* szOld, 
					  const Ch* szNew,
					  Pr pr)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, pr);
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllCopy(const Ch * s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), str, std::equal_to<Ch>());
}

/** replace all substring szOld to szNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), str, std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, str, std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllCopy(const Ch * s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, str, std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, str, std::equal_to<Ch>());
}

/** replace all substring szOld to chNew in string s
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, str, std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), str, std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch* s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), str, std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all chOld to szNew in string s
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllCopy(const Ch * s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), str, std::equal_to<Ch>());
}

/** replace all chOld to chNew in string s, ignore case
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s,
					   Ch chOld,
					   Ch chNew)
{
	std::basic_string<Ch, Tr, A> ss(s);
	std::replace_if(ss.begin(), ss.end(), ch_equal_nocase<Ch>(chOld), chNew);
	return ss;
}

/** replace all chOld to chNew in string s, ignore case
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllNoCaseCopy(const Ch * s,
					   Ch chOld,
					   Ch chNew)
{
	std::basic_string<Ch> ss(s);
	std::replace_if(ss.begin(), ss.end(), ch_equal_nocase<Ch>(chOld), chNew);
	return ss;
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAllCopy(s, szOld, szNew, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	return ReplaceAllCopy(s, szOld, szNew, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllNoCaseCopy(const Ch * s, 
					  const Ch* szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld.begin(), szOld.end(),
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const Ch * s, 
					  const Ch* szOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			szNew.begin(), szNew.end(), str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllNoCaseCopy(const Ch * s, 
					  const Ch* szOld, 
					  Ch chNew)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld, CharTraits<Ch>::tstrend(szOld),
			&chNew, (&chNew) + 1, str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, str, ch_equal_to_nocase<Ch>());
}

/** replace all substring szOld to chNew in string s, ignore case
 *  \param s		string to replace
 *  \param szOld	the string to be replaced
 *  \param chNew	the replacement char
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const Ch * s, 
					  const std::basic_string<Ch, Tr, A>& szOld, 
					  Ch chNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), szOld.begin(), szOld.end(),
			&chNew, (&chNew) + 1, str, ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), str, ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const Ch * s, 
					  Ch chOld, 
					  const std::basic_string<Ch, Tr, A>& szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), &chOld, (&chOld) + 1,
			szNew.begin(), szNew.end(), str, ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> ReplaceAllNoCaseCopy(const std::basic_string<Ch, Tr, A>& s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch, Tr, A> str;
	return ReplaceAllCopyImpl(s.begin(), s.end(), &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

/** replace all chOld to szNew in string s, ignore case
 *  \param s		string to replace
 *  \param chOld	the char to be replaced
 *  \param szNew	the replacement string
 *  \return			count of szOld replaced
 */
template < typename Ch >
inline std::basic_string<Ch> ReplaceAllNoCaseCopy(const Ch * s, 
					  Ch chOld, 
					  const Ch* szNew)
{
	std::basic_string<Ch> str;
	return ReplaceAllCopyImpl(s, CharTraits<Ch>::tstrend(s), &chOld, (&chOld) + 1,
			szNew, CharTraits<Ch>::tstrend(szNew), str, ch_equal_to_nocase<Ch>());
}

//////////////////////////////////////////////////////////////////////////
// Remove Utility

/** remove all chRemove from s
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAll(std::basic_string<Ch, Tr, A>& s,
					  Ch chRemove)
{
	s.erase( std::remove(s.begin(), s.end(), chRemove),
		s.end() );
}

/** remove all chRemove from s
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 */
template < typename Ch >
inline void RemoveAll(Ch *s, Ch chRemove)
{
	WBL_ASSERT(s != NULL);

	*std::remove(s, 
		CharTraits<Ch>::tstrend(s),
		chRemove) = 0;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch >
inline void RemoveAll(Ch *s, const Ch *szRemove)
{
	WBL_ASSERT( s != NULL && szRemove != NULL);

	*remove_sub_sequence(s, CharTraits<Ch>::tstrend(s),
		szRemove, CharTraits<Ch>::tstrend(szRemove)) = 0;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAll(Ch* s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	*remove_sub_sequence(s, CharTraits<Ch>::tstrend(s), 
			szRemove.begin(), szRemove.end()) = 0;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAll(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	s.erase(remove_sub_sequence(s.begin(), s.end(), 
			szRemove.begin(), szRemove.end()),
		s.end());
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAll(std::basic_string<Ch, Tr, A>& s,
					 const Ch* szRemove)
{
	WBL_ASSERT(szRemove != NULL);

	typedef std::basic_string<Ch, Tr, A> StrT;
	s.erase(remove_sub_sequence(s.begin(), s.end(), 
			szRemove, CharTraits<Ch>::tstrend(szRemove)),
		s.end());
}

/** remove all chRemove from s, ignore case
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAllNoCase(std::basic_string<Ch, Tr, A>& s,
					  Ch chRemove)
{
	s.erase( std::remove_if(s.begin(), s.end(), 
			ch_equal_nocase<Ch>(chRemove)),
		s.end() );
}

/** remove all chRemove from s, ignore case
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 */
template < typename Ch >
inline void RemoveAllNoCase(Ch *s, Ch chRemove)
{
	WBL_ASSERT(s != NULL);

	*std::remove_if(s, 
		CharTraits<Ch>::tstrend(s),
		ch_equal_nocase<Ch>(chRemove)) = 0;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch >
inline void RemoveAllNoCase(Ch *s, const Ch *szRemove)
{
	WBL_ASSERT(s != NULL && szRemove != NULL);

	*remove_sub_sequence(s, CharTraits<Ch>::tstrend(s),
		szRemove, CharTraits<Ch>::tstrend(szRemove),
		ch_equal_to_nocase<Ch>()) = 0;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAllNoCase(Ch *s, const std::basic_string<Ch, Tr, A>& szRemove)
{
	assert(s != NULL && szRemove != NULL);

	*remove_sub_sequence(s, CharTraits<Ch>::tstrend(s),
		szRemove.begin(), szRemove.end(),
		ch_equal_to_nocase<Ch>()) = 0;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAllNoCase(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	s.erase(remove_sub_sequence(s.begin(), s.end(), 
			szRemove.begin(), szRemove.end(),
			ch_equal_to_nocase<Ch>()),
		s.end());
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 */
template < typename Ch, typename Tr, typename A >
inline void RemoveAllNoCase(std::basic_string<Ch, Tr, A>& s,
					 const Ch* szRemove)
{
	WBL_ASSERT(szRemove != NULL);

	s.erase(remove_sub_sequence(s.begin(), s.end(), 
			szRemove, CharTraits<Ch>::tstrend(szRemove),
			ch_equal_to_nocase<Ch>()),
		s.end());
}

//////////////////////////////////////////////////////////////////////////
// Remove Copy Utility

/** remove all chRemove from s
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllCopy(const std::basic_string<Ch, Tr, A>& s,
					  Ch chRemove)
{
	std::basic_string<Ch, Tr, A> ss;
	ss.reserve(s.size());
	std::remove_copy(s.begin(), s.end(), std::back_inserter(ss), chRemove);
	return ss;
}

/** remove all chRemove from s
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> RemoveAllCopy(const Ch *s, Ch chRemove)
{
	const size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	std::remove_copy(s, s + len, std::back_inserter(ss), chRemove);
	return ss;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> RemoveAllCopy(const Ch *s, const Ch *szRemove)
{
	const size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	remove_sub_sequence_copy(s, s + len,
		szRemove, CharTraits<Ch>::tstrend(szRemove), std::back_inserter(ss));
	return ss;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllCopy(const std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	std::basic_string<Ch> ss;
	ss.reserve(s.size());
	remove_sub_sequence_copy(s.begin(), s.end(),
		szRemove.begin(), szRemove.end(), std::back_inserter(ss));
	return ss;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllCopy(const Ch* s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	remove_sub_sequence_copy(s, s + len, 
		szRemove.begin(), szRemove.end(), std::back_inserter(ss));
	return ss;
}

/** remove all szRemove from s
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllCopy(const std::basic_string<Ch, Tr, A>& s,
					 const Ch* szRemove)
{
	std::basic_string<Ch> ss;
	ss.reserve(s.size());
	remove_sub_sequence_copy(s.begin(), s.end(),
		szRemove, CharTraits<Ch>::tstrend(szRemove), std::back_inserter(ss));
	return ss;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllNoCaseCopy(Ch *s, const std::basic_string<Ch, Tr, A>& szRemove)
{
	size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	remove_sub_sequence_copy(s, s + len, 
		szRemove.begin(), szRemove.end(), 
		std::back_inserter(ss), ch_equal_to_nocase<Ch>());
	return ss;
}

/** remove all chRemove from s, ignore case
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllNoCaseCopy(std::basic_string<Ch, Tr, A>& s,
					  Ch chRemove)
{
	std::basic_string<Ch, Tr, A> ss;
	ss.reserve(s.size());
	std::remove_copy_if(s.begin(), s.end(), std::back_inserter(ss), ch_equal_nocase<Ch>(chRemove));
	return ss;
}

/** remove all chRemove from s, ignore case
 *  \param s		string to replace
 *  \param chRemove	the character to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> RemoveAllNoCaseCopy(Ch *s, Ch chRemove)
{
	const size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	std::remove_copy_if(s, s + len, std::back_inserter(ss), 
			ch_equal_nocase<Ch>(chRemove));
	return ss;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch >
inline std::basic_string<Ch> RemoveAllNoCaseCopy(Ch *s, const Ch *szRemove)
{
	size_t len = CharTraits<Ch>::tstrlen(s);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	remove_sub_sequence_copy(s, s + len, 
		szRemove, CharTraits<Ch>::tstrend(szRemove), 
		std::back_inserter(ss), ch_equal_to_nocase<Ch>());
	return ss;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllNoCaseCopy(std::basic_string<Ch, Tr, A>& s, 
					  const std::basic_string<Ch, Tr, A>& szRemove)
{
	std::basic_string<Ch> ss;
	ss.reserve(s.size());
	remove_sub_sequence_copy(s.begin(), s.end(),
		szRemove.begin(), szRemove.end(), 
		std::back_inserter(ss), ch_equal_to_nocase<Ch>());
	return ss;
}

/** remove all szRemove from s, ignore case
 *  \param s		string to replace
 *  \param szRemove	the string to remove
 *  \return			result
 */
template < typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> RemoveAllNoCaseCopy(std::basic_string<Ch, Tr, A>& s,
					 const Ch* szRemove)
{
	size_t len = CharTraits<Ch>::tstrlen(szRemove);
	std::basic_string<Ch> ss;
	ss.reserve(len);
	remove_sub_sequence_copy(s.begin(), s.end(), 
		szRemove, szRemove + len,
		std::back_inserter(ss), ch_equal_to_nocase<Ch>());
	return ss;
}

//////////////////////////////////////////////////////////////////////////
// Match Wildcard

/** match wildcard
 *  \param f1			first position of wildcard string
 *  \param l1			last position of wildcard string
 *  \param f2			first position of string to match
 *	\param l2			last position of string to match
 *	\param asterisk		asterisk character
 *	\param question		question character
 *	\param pr			equals compare
 *	\return				if match, return true, otherwise return false
 */
template < typename FI1, typename FI2, typename ValueT, typename Pr >
bool MatchWildcard(FI1 f1, FI1 l1, FI2 f2, FI2 l2, ValueT asterisk, ValueT question, Pr pr)
{
	for(; f1 != l1 && f2 != l2 ; ){
		char c1 = *f1, c2 = *f2;
		if(c1 == asterisk){
			++f1;
			while(f2 != l2){
				if(MatchWildcard(f1, l1, f2, l2, asterisk, question, pr))
					return true;
				++f2;
			}
			return f1 == l1;
		}else if(c1 == question){
			++f1;
			++f2;
		}else{
			//if(c1 != c2)
			if(!pr(c1, c2))
				return false;
			++f1;
			++f2;
		}
	}
	if(f2 != l2)
		return false;
	for(; f1 != l1; ++f1){
		if(*f1 != '*')
			return false;
	}
	return true;
}

/** match wildcard
 *  \param f1			first position of wildcard string
 *  \param l1			last position of wildcard string
 *  \param f2			first position of string to match
 *	\param l2			last position of string to match
 *	\param asterisk		asterisk character
 *	\param question		question character
 *	\return				if match, return true, otherwise return false
 */
template < typename FI1, typename FI2, typename ValueT >
inline bool MatchWildcard(FI1 f1, FI1 l1, FI2 f2, FI2 l2, ValueT asterisk, ValueT question)
{
	return MatchWildcard(f1, l1, f2, l2, asterisk, question, std::equal_to<ValueT>());
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const std::string& pat, const std::string& str)
{
	return MatchWildcard(pat.begin(), pat.end(),
			str.begin(), str.end(),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const std::wstring& pat, const std::wstring& str)
{
	return MatchWildcard(pat.begin(), pat.end(),
			str.begin(), str.end(),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const char * pat, const char * str)
{
	return MatchWildcard(pat, CharTraits<char>::tstrend(pat),
			str, CharTraits<char>::tstrend(str),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const wchar_t * pat, const wchar_t * str)
{
	return MatchWildcard(pat, CharTraits<wchar_t>::tstrend(pat),
			str, CharTraits<wchar_t>::tstrend(str),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const std::string& pat, const char * str)
{
	return MatchWildcard(pat.begin(), pat.end(),
			str, CharTraits<char>::tstrend(str),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const std::wstring pat, const wchar_t * str)
{
	return MatchWildcard(pat.begin(), pat.end(),
			str, CharTraits<wchar_t>::tstrend(str),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const char * pat, const std::string& str)
{
	return MatchWildcard(pat, CharTraits<char>::tstrend(pat),
			str.begin(), str.end(),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcard(const wchar_t * pat, const std::wstring& str)
{
	return MatchWildcard(pat, CharTraits<wchar_t>::tstrend(pat),
			str.begin(), str.end(),
			L'*', L'?');
}

//////////////////////////////////////////////////////////////////////////
// Match Wildcard Ignore Case

/** match wildcard ignore case
 *  \param f1			first position of wildcard string
 *  \param l1			last position of wildcard string
 *  \param f2			first position of string to match
 *	\param l2			last position of string to match
 *	\param asterisk		asterisk character
 *	\param question		question character
 *	\return				if match, return true, otherwise return false
 */
template < typename FI1, typename FI2, typename ValueT >
bool MatchWildcardNoCase(FI1 f1, FI1 l1, FI2 f2, FI2 l2, ValueT asterisk, ValueT question)
{
	return MatchWildcard(f1, l1, f2, l2, asterisk, question, ch_equal_to_nocase<ValueT>());
}

/** match wildcard ignore case
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const std::string& pat, const std::string& str)
{
	return MatchWildcardNoCase(pat.begin(), pat.end(),
			str.begin(), str.end(),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const std::wstring& pat, const std::wstring& str)
{
	return MatchWildcardNoCase(pat.begin(), pat.end(),
			str.begin(), str.end(),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const char * pat, const char * str)
{
	return MatchWildcardNoCase(pat, CharTraits<char>::tstrend(pat),
			str, CharTraits<char>::tstrend(str),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const wchar_t * pat, const wchar_t * str)
{
	return MatchWildcardNoCase(pat, CharTraits<wchar_t>::tstrend(pat),
			str, CharTraits<wchar_t>::tstrend(str),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const std::string& pat, const char * str)
{
	return MatchWildcardNoCase(pat.begin(), pat.end(),
			str, CharTraits<char>::tstrend(str),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const std::wstring pat, const wchar_t * str)
{
	return MatchWildcardNoCase(pat.begin(), pat.end(),
			str, CharTraits<wchar_t>::tstrend(str),
			L'*', L'?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const char * pat, const std::string& str)
{
	return MatchWildcardNoCase(pat, CharTraits<char>::tstrend(pat),
			str.begin(), str.end(),
			'*', '?');
}

/** match wildcard
 *  \param pat	wildcard pattern string, * means zero or more character, ? means one character
 *  \param str	string to match
 *  \return		if match return true, otherwise return false
 */
inline bool MatchWildcardNoCase(const wchar_t * pat, const std::wstring& str)
{
	return MatchWildcardNoCase(pat, CharTraits<wchar_t>::tstrend(pat),
			str.begin(), str.end(),
			L'*', L'?');
}

//////////////////////////////////////////////////////////////////////////
// ToString

template < typename T >
inline std::string ToString(const T& val)
{
	std::ostringstream ost;
	ost << val;
	return ost.str();
}

inline std::string ToString(const std::string& s)
{
	return s;
}

inline std::string ToString(const char* s)
{
	return s != NULL ? s : "";
}

template < typename T >
inline std::wstring ToWString(const T& val)
{
	std::wostringstream ost;
	ost << val;
	return ost.str();
}

inline std::wstring ToWString(const std::wstring& s)
{
	return s;
}

inline std::wstring ToWString(const wchar_t* s)
{
	return s != NULL ? s : L"";
}

//////////////////////////////////////////////////////////////////////////
// String Compare Functional

/** less compare ignore case
 */
struct less_nocase
{
	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, const
			std::basic_string<Ch, Tr, A>& s2) const
	{
		return CompareNoCase(s1, s2) < 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, 
			const Ch* s2) const
	{
		return CompareNoCase(s1, s2) < 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const Ch* s1, const std::basic_string<Ch, Tr, A>& s2)
			const
	{
		return CompareNoCase(s1, s2) < 0;
	}

	template < typename Ch >
	bool operator()(const Ch* s1, const Ch* s2) const
	{
		return CompareNoCase(s1, s2) < 0;
	}
};

/** equals compare ignore case
 */
struct equal_nocase
{
	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, const
			std::basic_string<Ch, Tr, A>& s2) const
	{
		return CompareNoCase(s1, s2) == 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, 
			const Ch* s2) const
	{
		return CompareNoCase(s1, s2) == 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const Ch* s1, const std::basic_string<Ch, Tr, A>& s2) 
			const
	{
		return CompareNoCase(s1, s2) == 0;
	}

	template < typename Ch >
	bool operator()(const Ch* s1, const Ch* s2) const
	{
		return CompareNoCase(s1, s2) == 0;
	}
};

/** greater compare ignore case
 */
struct greater_nocase
{
	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, const
			std::basic_string<Ch, Tr, A>& s2) const
	{
		return CompareNoCase(s1, s2) > 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, 
			const Ch* s2) const
	{
		return CompareNoCase(s1, s2) > 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const Ch* s1, const std::basic_string<Ch, Tr, A>& s2) 
			const
	{
		return CompareNoCase(s1, s2) > 0;
	}

	template < typename Ch >
	bool operator()(const Ch* s1, const Ch* s2) const
	{
		return CompareNoCase(s1, s2) > 0;
	}
};

/** less equal compare ignore case
 */
struct less_equal_nocase
{
	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, const
			std::basic_string<Ch, Tr, A>& s2) const
	{
		return CompareNoCase(s1, s2) <= 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, 
			const Ch* s2) const
	{
		return CompareNoCase(s1, s2) <= 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const Ch* s1, const std::basic_string<Ch, Tr, A>& s2) 
			const
	{
		return CompareNoCase(s1, s2) <= 0;
	}

	template < typename Ch >
	bool operator()(const Ch* s1, const Ch* s2) const
	{
		return CompareNoCase(s1, s2) <= 0;
	}
};

/** greater equal compare ignore case
 */
struct greater_equal_nocase
{
	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, const
			std::basic_string<Ch, Tr, A>& s2) const
	{
		return CompareNoCase(s1, s2) >= 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const std::basic_string<Ch, Tr, A>& s1, 
			const Ch* s2) const
	{
		return CompareNoCase(s1, s2) >= 0;
	}

	template < typename Ch, typename Tr, typename A >
	bool operator()(const Ch* s1, const std::basic_string<Ch, Tr, A>& s2) 
			const
	{
		return CompareNoCase(s1, s2) >= 0;
	}

	template < typename Ch >
	bool operator()(const Ch* s1, const Ch* s2) const
	{
		return CompareNoCase(s1, s2) >= 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// Split

/** split string
 *  \param fs	first position of source sequence
 *  \param ls	last position of source sequence
 *  \param fo	first position of separator sequence
 *  \param lo	last position of separator sequence
 *  \param pr	equals compare functor
 *  \param o	output iterator
 *  \param x	this parameter will ignore, it use to indicates type StringT only
 *  \return		true always
 */
template < typename II_S, typename II_O, typename Pr, typename OI, typename StringT >
bool Split(II_S fs, II_S ls,
		II_O fo, II_O lo,
		Pr pr,
		OI o,
		const StringT * x)
{
	if(fo == lo){
		*o = StringT(fs, ls);
		return true;
	}

	II_S iPos = std::search(fs, ls,
		fo, lo, pr);								// current position szOld in s
	if(iPos == ls){
		*o = StringT(fs, ls);
		return true;
	}
	int nOldSize = std::distance(fo, lo);
	for(; iPos != ls; ){
		*o = StringT(fs, iPos);					// append src string
		fs = iPos + nOldSize;					// ignore szOld
		iPos = std::search(fs, ls,
			fo, lo, pr);							// find next
	}
	if(fs != ls)
		*o = StringT(fs, ls);
	return true;
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool Split(const std::basic_string<Ch, Tr, A>& s,
		const std::basic_string<Ch, Tr, A>& separator, 
		ContainerT& v)
{
	return Split(s.begin(), s.end(),
			separator.begin(), separator.end(),
			std::equal_to<Ch>(), std::back_inserter(v),
			&s);
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool Split(const std::basic_string<Ch, Tr, A>& s, 
		const Ch * separator, ContainerT& v)
{
	return Split(s.begin(), s.end(),
			separator, CharTraits<Ch>::tstrend(separator),
			std::equal_to<Ch>(), std::back_inserter(v),
			&s);
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool Split(const std::basic_string<Ch, Tr, A>& s, 
		Ch separator, ContainerT& v)
{
	return Split(s.begin(), s.end(),
			&separator, &separator + 1,
			std::equal_to<Ch>(), std::back_inserter(v),
			&s);
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool Split(const Ch * s, const std::basic_string<Ch, Tr, A>& separator,
		ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s),
			separator.begin(), separator.end(),
			std::equal_to<Ch>(), std::back_inserter(v),
			&separator);
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename ContainerT >
inline bool Split(const Ch * s, const Ch * separator, ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s),
			separator, CharTraits<Ch>::tstrend(separator),
			std::equal_to<Ch>(), std::back_inserter(v),
			static_cast<std::basic_string<Ch>*>(NULL));
}

/** split string
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename ContainerT >
inline bool Split(const Ch * s, Ch separator, ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s),
			&separator, &separator + 1,
			std::equal_to<Ch>(), std::back_inserter(v),
			static_cast<std::basic_string<Ch>*>(NULL));
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool SplitNoCase(const std::basic_string<Ch, Tr, A>& s, 
		const std::basic_string<Ch, Tr, A>& separator,
		ContainerT& v)
{
	return Split(s.begin(), s.end(), 
			separator.begin(), separator.end(),
			equal_nocase(), std::back_inserter(v),
			&s);
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool SplitNoCase(const std::basic_string<Ch, Tr, A>& s,
		const Ch * separator, ContainerT& v)
{
	return Split(s.begin(), s.end(), 
			separator, CharTraits<Ch>::tstrend(separator),
			equal_nocase(), std::back_inserter(v),
			&s);
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool SplitNoCase(const std::basic_string<Ch, Tr, A>& s,
		Ch separator, ContainerT& v)
{
	return Split(s.begin(), s.end(), 
			&separator, &separator + 1,
			equal_nocase(), std::back_inserter(v),
			&s);
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename Tr, typename A,
		typename ContainerT >
inline bool SplitNoCase(const Ch * s,
		const std::basic_string<Ch, Tr, A>& separator,
		ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s), 
			separator.begin(), separator.end(), 
			equal_nocase(), std::back_inserter(v),
			&separator);
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename ContainerT >
inline bool SplitNoCase(const Ch * s, const Ch * separator, 
		ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s), 
			separator, CharTraits<Ch>::tstrend(separator), 
			equal_nocase(), std::back_inserter(v),
			static_cast<std::basic_string<Ch>*>(NULL));
}

/** split string ignore case
 *  \param s			source string
 *  \param separator	separator
 *  \param v			result
 *  \return				always true
 */
template < typename Ch, typename ContainerT >
inline bool SplitNoCase(const Ch * s, Ch separator, 
		ContainerT& v)
{
	return Split(s, CharTraits<Ch>::tstrend(s), 
			&separator, &separator + 1, 
			equal_nocase(), std::back_inserter(v),
			static_cast<std::basic_string<Ch>*>(NULL));
}

//////////////////////////////////////////////////////////////////////////
// Join
/** join string with a separator to an ostream
 *  \param f1	first position of string sequence
 *  \param l1	last position of string sequence
 *  \param f2	first position of separator
 *  \param l2	last position of separator
 *  \param ost	output stream
 */
template < typename FI1, typename FI2, typename Ch, typename Tr >
inline void Join(FI1 f1, FI1 l1, FI2 f2, FI2 l2, std::basic_ostream<Ch, Tr>& ost)
{
	if(f1 == l1)
		return;
	ost << *f1;
	for(++f1; f1 != l1; ++f1){
		std::copy(f2, l2, std::ostreambuf_iterator<Ch>(ost));
		ost << *f1;
	}
}

/** Join string with a separator
 *  \param f1	first position of string sequence
 *  \param l1	last position of string sequence
 *  \param f2	first position of separator
 *  \param l2	last position of separator
 *  \return		result string
 */
#if (defined(_MSC_VER) && (_MSC_VER <= 1300) && !defined(__BORLANDC__)) || !defined(_CPPLIB_VER) || (_CPPLIB_VER < 306)
template < typename FI1, typename FI2, typename Ch >
inline std::basic_string<Ch> Join(FI1 f1, FI1 l1, FI2 f2, FI2 l2, Ch * dummy = 0)
{
	std::basic_ostringstream<Ch> os;
	Join(f1, l1, f2, l2, os);
	return os.str();
}
#else
template < typename FI1, typename FI2 >
inline std::basic_string<typename std::iterator_traits<FI2>::value_type> Join(FI1 f1, FI1 l1, FI2 f2, FI2 l2, typename std::iterator_traits<FI2>::value_type * dummy = 0)
{
	typedef typename std::iterator_traits<FI2>::value_type	Ch;
	std::basic_ostringstream<Ch> os;
	Join(f1, l1, f2, l2, os);
	return os.str();
}
#endif

/** Join string with a separator
 *  \param f1			first position of string sequence
 *  \param l1			last position of string sequence
 *  \param separator	separator
 *  \return				result string
 */
template < typename FI, typename Ch, typename Tr, typename A >
inline std::basic_string<Ch, Tr, A> Join(FI f1, FI l1, const std::basic_string<Ch, Tr, A>& separator)
{
	return Join(f1, l1, separator.begin(), separator.end(), (Ch *)(0));
}

/** Join string with a separator
 *  \param f1			first position of string sequence
 *  \param l1			last position of string sequence
 *  \param separator	separator
 *  \return				result string
 */
template < typename FI, typename Ch >
inline std::basic_string<Ch> Join(FI f1, FI l1, const Ch * separator)
{
	return Join(f1, l1, separator, CharTraits<Ch>::tstrend(separator), (Ch *)(0));
}

/** Join string with a separator
 *  \param f1			first position of string sequence
 *  \param l1			last position of string sequence
 *  \param separator	separator
 *  \return				result string
 */
template < typename FI, typename Ch >
inline std::basic_string<Ch> Join(FI f1, FI l1, Ch separator)
{
	return Join(f1, l1, &separator, &separator + 1, (Ch *)(0));
}

/** Join string with a separator
 *  \param con			string's container
 *  \param separator	separator
 *  \return				result string
 */
template < typename Ch, typename Tr, typename A, 
		 typename ContainerT >
inline std::basic_string<Ch, Tr, A> Join(const ContainerT& con, const std::basic_string<Ch, Tr, A>& separator)
{
	return Join(con.begin(), con.end(), separator);
}

/** Join string with a separator
 *  \param con			string's container
 *  \param separator	separator
 *  \return				result string
 */
template < typename Ch, typename ContainerT >
inline std::basic_string<Ch> Join(const ContainerT& con, const Ch * separator)
{
	return Join(con.begin(), con.end(), separator);
}

/** Join string with a separator
 *  \param con			string's container
 *  \param separator	separator
 *  \return				result string
 */
template < typename Ch, typename ContainerT >
inline std::basic_string<Ch> Join(const ContainerT& con, Ch separator)
{
	return Join(con.begin(), con.end(), separator);
}

} // end namespace

#endif

