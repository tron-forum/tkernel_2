/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2014/09/10.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)string.c (libstr)
 *	Standard string library (for kernel link)
 */

/*
 *	This file is linked to the kernel only when the
 *	C standard library is not used.
 */

#include <basic.h>
#include <tk/tkernel.h>
#include <libstr.h>

/* Define weak alias symbol */
#if	_Csym == 0
#define	weak_alias(nm, act)	__asm__(".weak "  #nm " ; "  #nm " = "  #act)
#else
#define	weak_alias(nm, act)	__asm__(".weak _" #nm " ; _" #nm " = _" #act)
#endif

#if	use_libstr_memcpy_implicit
	weak_alias(memcpy, tkl_memcpy);
#endif	/* use_libstr_memcpy_implicit */

#if	use_libstr_func_as_std
	weak_alias(memset, tkl_memset);
	weak_alias(memcmp, tkl_memcmp);
	weak_alias(memmove, tkl_memmove);
	weak_alias(strlen, tkl_strlen);
	weak_alias(strcmp, tkl_strcmp);
	weak_alias(strcpy, tkl_strcpy);
	weak_alias(strncpy, tkl_strncpy);
	weak_alias(strcat, tkl_strcat);
	weak_alias(strncat, tkl_strncat);
#endif	/* use_libstr_func_as_std */

/* memory access size */
#define	MASZ	(sizeof(unsigned long))
#define	MAMSK	(MASZ - 1)

/* memory access pointer */
typedef	union {
	unsigned char	*cp;
	unsigned long	*lp;
	unsigned long	lv;
} MPTR;

/*
 * tkl_memset : fill memory area
 */
void* tkl_memset( void *s, int c, size_t n )
{
	MPTR		m;
	size_t		cnt;
	unsigned long	val;

	m.cp = (unsigned char *)s;
	val = (unsigned char)c;

	cnt = m.lv & MAMSK;
	if ( cnt > 0 ) {
		/* Not aligned in WASZ bytes */
		if ( n < MASZ * 2) {
			cnt = n;
		} else {
			cnt = MASZ - cnt;
		}
		/* Fill preceding bytes to align */
		n -= cnt;
		do {
			*m.cp++ = (unsigned char)val;
		} while ( --cnt > 0 );
	}

	/* Fill in WASZ bytes unit */
	if ( n >= MASZ ) {
		cnt = n / MASZ;
		n &= MAMSK;
		val |= val << 8;
		val |= val << 16;
		do {
			*m.lp++ = val;
		} while ( --cnt > 0 );
	}

	/* Fill trailing bytes */
	while ( n-- > 0 ) {
		*m.cp++ = (unsigned char)val;
	}
	return s;
}

/*
 * tkl_memcmp : perform memory comparison
 */
int tkl_memcmp( const void *s1, const void *s2, size_t n )
{
	int	result;
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;

	while ( n-- > 0 ) {
		result = *p1++ - *p2++;
		if ( result != 0 ) return result;
	}
	return 0;
}

/*
 * tkl_memcpy : copy memory
 */
void* tkl_memcpy( void *dst, const void *src, size_t n )
{
	MPTR	s, d;
	size_t	cnt;

	d.cp = (unsigned char *)dst;
	s.cp = (unsigned char *)src;

	if ( ( (s.lv | d.lv) & MAMSK ) != 0 ) {
		/* Not aligned in WASZ bytes */
		if ( ( (s.lv ^ d.lv) & MAMSK ) != 0 || n < MASZ * 2) {
			/* Full copy in a byte unit */
			cnt = n;
		} else {
			/* Copy preceding bytes to align */
			cnt = MASZ - (s.lv & MAMSK);
		}
		/* Copy in a byte unit */
		n -= cnt;
		do {
			*d.cp++ = *s.cp++;
		} while ( --cnt > 0 );
	}

	/* Copy in WASZ bytes unit */
	if ( n >= MASZ ) {
		cnt = n / MASZ;
		n &= MAMSK;
		do {
			*d.lp++ = *s.lp++;
		} while ( --cnt > 0 );
	}

	/* Copy trailing bytes */
	while ( n-- > 0 ) {
		*d.cp++ = *s.cp++;
	}
	return dst;
}

/*
 * tkl_memmove : move memory
 */
void* tkl_memmove( void *dst, const void *src, size_t n )
{
	MPTR	s, d;
	size_t	cnt;

	d.cp = (unsigned char *)dst;
	s.cp = (unsigned char *)src;

	if ( d.cp < s.cp ) {	/* Copy forward */
		if ( ( (s.lv | d.lv) & MAMSK ) != 0 ) {
			if ( ( (s.lv ^ d.lv) & MAMSK ) != 0 || n < MASZ * 2 ) {
				cnt = n;
			} else {
				cnt = MASZ - (s.lv & MAMSK);
			}
			n -= cnt;
			do {
				*d.cp++ = *s.cp++;
			} while ( --cnt > 0 );
		}
		if ( n >= MASZ ) {
			cnt = n / MASZ;
			n &= MAMSK;
			do {
				*d.lp++ = *s.lp++;
			} while ( --cnt > 0 );
		}
		while ( n-- > 0 ) {
			*d.cp++ = *s.cp++;
		}
	} else {		/* Copy backward */
		s.cp += n;
		d.cp += n;
		if ( ( (s.lv | d.lv) & MAMSK ) != 0 ) {
			if ( ( (s.lv ^ d.lv) & MAMSK ) != 0 || n < MASZ * 2 ) {
				cnt = n;
			} else {
				cnt = s.lv & MAMSK;
			}
			n -= cnt;
			do {
				*--d.cp = *--s.cp;
			} while ( --cnt > 0 );
		}
		if ( n >= MASZ ) {
			cnt = n / MASZ;
			n &= MAMSK;
			do {
				*--d.lp = *--s.lp;
			} while ( --cnt > 0 );
		}
		while ( n-- > 0 ) {
			*--d.cp = *--s.cp;
		}
	}
	return dst;
}

/*
 * tkl_strlen : get text string length
 */
size_t tkl_strlen( const char *s )
{
	char	*cp = (char *)s;

	while ( *cp != '\0' ) cp++;
	return (size_t)(cp - s);
}

/*
 * tkl_strcmp : perform text string comparison
 */
int tkl_strcmp( const char *s1, const char *s2 )
{
	for ( ; *s1 == *s2; s1++, s2++ ) {
		if ( *s1 == '\0' ) return 0;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}

#if	0
/*
 * tkl_strncmp : perform text string comparison of specified length
 */
int tkl_strncmp( const char *s1, const char *s2, size_t n )
{
	int	result;

	while ( n-- > 0 ) {
		result = (unsigned char)*s1 - (unsigned char)*s2++;
		if ( result != 0 ) return result;
		if ( *s1++ == '\0' ) break;
	}
	return 0;
}
#endif

/*
 * tkl_strcpy : copy text string
 */
char* tkl_strcpy( char *dst, const char *src )
{
	char	*dp = dst;

	while ( (*dp++ = *src++) != '\0' );
	return dst;
}

/*
 * tkl_strncpy : copy text string of specified length
 */
char* tkl_strncpy( char *dst, const char *src, size_t n )
{
	char	*dp = dst;

	while ( n-- > 0 ) {
		if ( (*dp++ = *src++) == '\0' ) {
			while ( n-- > 0 ) *dp++ = '\0';
			break;
		}
	}
	return dst;
}

/*
 * tkl_strcat : perform text string concatenation
 */
char* tkl_strcat( char *dst, const char *src )
{
	char	*dp = dst;

	while ( *dp != '\0' ) dp++;
	while ( (*dp++ = *src++) != '\0' );
	return dst;
}

/*
 * tkl_strncat : perform concatenation on text string of specified length
 */
char* tkl_strncat( char *dst, const char *src, size_t n )
{
	char	*dp = dst;

	while ( *dp != '\0' ) dp++;
	while ( n-- > 0 ) {
		if ( (*dp++ = *src++) == '\0' ) return dst;
	}
	*dp = '\0';
	return dst;
}

/*
 * tkl_strtoul : convert text string to integer value (unsigned long int)
 */
unsigned long int tkl_strtoul( const char *nptr, char **endptr, int base )
{
	unsigned long int	value = 0;
	int		sign = 1;
	int		i;

	while ( (*nptr == ' ' || *nptr == '\t') ) {
		++nptr;
	}

	switch ( *nptr ) {
	  case '-':
		sign = -1;
		/* no break */
	  case '+':
		++nptr;
		/* no break */
	  default:
		break;
	}

	if ( base == 16 ) {
		if ( *nptr == '0' ) {
			++nptr;
			if ( *nptr == 'X' || *nptr == 'x' ) {
				++nptr;
			}
		}
	} else if ( base == 0 ) {
		if ( *nptr == '0' ) {
			++nptr;
			if ( *nptr == 'X' || *nptr == 'x' ) {
				++nptr;
				base = 16;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	} else if ( base < 2 || base > 36 ) {
		base = 10;
	}

	while ( *nptr != '\0' ) {
		if ( *nptr >= '0' && *nptr <= '9' ) {
			i = *nptr - '0';
		} else if ( *nptr >= 'A' && *nptr <= 'Z' ) {
			i = *nptr - 'A' + 10;
		} else if ( *nptr >= 'a' && *nptr <= 'z' ) {
			i = *nptr - 'a' + 10;
		} else {
			break;
		}
		if ( i >= base ) {
			break;
		}
		value = value * base + i;
		++nptr;
	}
	if ( endptr != NULL ) {
		*endptr = (char *)nptr;
	}
	return value * sign;
}

