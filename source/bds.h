/*
bds - Better Dynamic String. Version 0.1.0

Original code by Adrian Guerrero Vera (adrianwk94@gmail.com)
MIT License
Copyright (c) 2021 Adrian Guerrero Vera

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BDS_H
#define BDS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

struct bds_base_t {
	char* 		ptr;
	uint32_t 	size;
	uint32_t 	len;
};

typedef struct bds_base_t* bds_t;

bds_t	bds_empty	(void);
bds_t 	bds_create	(uint32_t size);
bds_t	bds_new 	(const char* in);
bds_t	bds_dup		(bds_t in); // create and copy a string with an input string.

void	bds_refresh (bds_t s); // count the length of the string. Useful when it has been used in other libraries.
void	bds_resize	(bds_t s, uint32_t new_size);
void	bds_free	(bds_t s);

// working with strings
void 	bds_clear 	(bds_t s);

void	bds_set 	(bds_t s, const char* in);
void 	bds_cat 	(bds_t s, const bds_t in);
void 	bds_cpy 	(bds_t s, const bds_t in);
bool	bds_cmp 	(const bds_t s1, const bds_t s2);

void	bds_range	(bds_t s, uint32_t start, uint32_t end);

void 	bds_tolower (bds_t s);
void 	bds_toupper (bds_t s);

void	bds_fmt 	(bds_t s, const char* fmt, ...);
void	bds_catfmt 	(bds_t s, const char* fmt, ...);

// working with BDS and C strings
void 	bds_strcat 	(bds_t s, const char* in);
bool	bds_strcmp 	(const bds_t s1, const char* s2);

#endif
