/*  defines.h  2007-06-15
 *
 * Copyright (C) 2007 Svyatoslav Kondrat (Valiska)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#if !defined ( _HAVE_DEFINES_H_)
#define _HAVE_DEFINES_H_

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

/* 
 * Critical errors/assertions 
 */
#define MPLIB_WARNING(str...) {\
    fprintf(stderr, "\n*** MPLIB WARNING: %s(): ", __ASSERT_FUNCTION);\
    fprintf(stderr, str); fprintf(stderr, "\n");\
    fflush(stderr);\
  }

#ifdef MPLIB_NO_ASSERT
#	define MPLIB_ASSERT(cond) 
#	define MPLIB_CRITICAL(cond,str,...)
#	define MPLIB_WARNING(str...) {\
	    fprintf(stderr, "\n*** MPLIB WARNING: %s(): ", __ASSERT_FUNCTION);\
	    fprintf(stderr, str); fprintf(stderr, "\n");\
	    fflush(stderr);\
	  }
#else
#	define MPLIB_WARNING(str...) {\
	    fprintf(stderr, "\n*** MPLIB WARNING: %s(): ", __ASSERT_FUNCTION);\
	    fprintf(stderr, str); fprintf(stderr, "\n");\
	    fflush(stderr);\
	  }
#	define MPLIB_CRITICAL(cond,str...)\
	  if (!(cond)) {\
	    fprintf(stderr, "\n*** MPLIB CRITICAL: assertion ('%s') failed in '%s'. "\
			    ,__STRING(cond), __ASSERT_FUNCTION);\
	    fprintf(stderr, "Assertion message: "str);\
	    fprintf(stderr, ", aborting.\n");\
	    fflush(stderr);\
	        abort();\
	  }
#	define MPLIB_ASSERT(cond) { \
	  if (!(cond)) {\
	    fprintf(stderr, "\n*** MPLIB ASSERTION ('%s') FAILED in \"%s\"",\
			__STRING(cond), __ASSERT_FUNCTION);\
	    fprintf(stderr, ", aborting.\n");\
	    fflush(stderr);\
	        abort();\
	  } }
#endif


/* 
 * For debugging 
 */
#ifdef DEBUG

  #define DPRINT(str...) fprintf(stderr, str); fflush(stderr);

  #define DPRINT_VECTOR(s, q, n)  {\
    int i ; \
    for (i = 0; i < n; i++) { \
      fprintf (stderr, "%s[%d]=%f\n", s, i, q[i]); fflush(stderr);} \
      fprintf(stderr, "\n"); fflush(stderr);\
    }

#else

  #define DPRINT(str...)
  #define DPRINT_VECTOR(s, q, n)

#endif /* DEBUG */

#endif /* _HAVE_DEFINES_H_ */ 

