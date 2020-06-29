
#ifndef __WBL_MACROS_H__
#define __WBL_MACROS_H__

#define chSTR(x)     #x
#define chSTR2(x)    chSTR(x)
#define chMSG(desc)  message(__FILE__ "(" chSTR2(__LINE__) "):" desc)

#ifdef _DEBUG
# define WBL_DEBUG_ONLY(x)	x
#else
# define WBL_DEBUG_ONLY(x)
#endif

#define WBL_JOIN(x,y)		WBL_DO_JOIN(x,y)
#define WBL_DO_JOIN(x,y)	WBL_DO_JOIN2(x,y)
#define WBL_DO_JOIN2(x,y)	x##y

#define BEGIN_COMMENT	/##*
#define END_COMMENT		*##/
#define LINE_COMMENT	/##/

#define _WBL_ASSERT_FAIL(file, line, expr)	{							\
		char sz[128];													\
		sprintf(sz, "File %hs, line %d : %hs",							\
			file, line, expr);											\
		::MessageBoxA(NULL, sz,											\
			"Asserting Failed", MB_OK | MB_ICONERROR);					\
		DebugBreak();													\
	}

// define WBL_ASSERT
#ifdef ATLASSERT
# define WBL_ASSERT	ATLASSERT
#else
# ifdef ASSERT
#  define WBL_ASSERT	ASSERT
# else
#  ifdef _WIN32
#   ifdef _DEBUG
#    include <windows.h>
#    define WBL_ASSERT(x)	{ if (!(x)) _WBL_ASSERT_FAIL(__FILE__, __LINE__, #x) }
#   else
#    define WBL_ASSERT(x)
#   endif
#  else
#   include <assert.h>
#   define WBL_ASSERT	assert
#  endif
# endif
#endif

// define WBL_VERIFY
#ifdef VERIFY
# define WBL_VERIFY VERIFY
#else
# ifndef NDEBUG
#  define WBL_VERIFY WBL_ASSERT
# else
#  define WBL_VERIFY(x)	x
# endif
#endif

#ifndef HAVE_SOCKADDR_IN_SIN_LEN
#	if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)	// BSD
#		define HAVE_SOCKADDR_IN_SIN_LEN	1
#	endif
#endif

#ifndef HAVE_SOCKADDR_SA_LEN
#	if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)	// BSD
#		define HAVE_SOCKADDR_SA_LEN	1
#	endif
#endif

#if HAVE_SOCKADDR_IN_SIN_LEN
#	define SET_SOCKADDR_IN_LENGTH(x)	x.sin_len = sizeof(x)
#	define GET_SOCKADDR_IN_LENGTH(x)	x.sin_len
#else
#	define SET_SOCKADDR_IN_LENGTH(x)	
#	define GET_SOCKADDR_IN_LENGTH(x)	sizeof(x)
#endif

#if HAVE_SOCKADDR_SA_LEN
#	define SET_SOCKADDR_LENGTH(x)	x.sa_len = sizeof(x)
#	define GET_SOCKADDR_LENGTH(x)	x.sa_len
#else
#	define SET_SOCKADDR_LENGTH(x)	
#	define GET_SOCKADDR_LENGTH(x)	sizeof(x)
#endif

#ifdef __GNUC__
#	define WBL_ATTRIBUTE_PACKED	 __attribute__((packed))
#else
#	define WBL_ATTRIBUTE_PACKED
#endif

#if _MSC_FULL_VER > 100000000
#  define WBL_MSVC_FULL_VER _MSC_FULL_VER
#else
#  define WBL_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

#if defined(_MSC_VER) && defined(WBL_MSVC_FULL_VER) && (WBL_MSVC_FULL_VER >=140050215)
#   define WBL_IS_POD(T) (__is_pod(T) && __has_trivial_constructor(T))
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__)))
#   define WBL_IS_POD(T) __is_pod(T)
#elif defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#   define WBL_IS_POD(T) __is_pod(T)
#elif defined(__CODEGEARC__)
#   define WBL_IS_POD(T) __is_pod(T)
#elif defined(__DMC__) && (__DMC__ >= 0x848)
#   define WBL_IS_POD(T) (__typeinfo(T) & 0x800)
#endif

#endif

