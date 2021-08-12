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

#include "bds.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BDS_MALLOC 	malloc
#define BDS_CALLOC 	calloc
#define BDS_REALLOC realloc
#define BDS_FREE 	free

#define BASE 	8

bds_t bds_empty(void) {
	return bds_create(64);
}

bds_t bds_create(uint32_t size) {
	bds_t result = BDS_CALLOC(1, sizeof(struct bds_base_t));
	result->ptr = BDS_CALLOC(size, sizeof(char));
	result->size = size;
	result->len = 0;
	return result;
}

bds_t bds_new(const char* in) {
	uint32_t in_len = (in == NULL) ? 0 : strlen(in);
	uint32_t size = in_len + BASE;
	if (in_len <= 0)
		return bds_empty();
	bds_t result = bds_create(size);
	memcpy(result->ptr, in, in_len);
	result->size = size;
	result->len = in_len;

	return result;
}

bds_t bds_dup(bds_t in) {

	if (in) {
		bds_t result = bds_create(in->len + BASE);
		memcpy(result->ptr, in->ptr, in->len);
		result->ptr[in->len + 1] = '\0';
		result->len = in->len;
		return result;
	}

	return bds_empty();
}

void bds_refresh(bds_t s) {
	if (s) {
		s->len = strnlen(s->ptr, s->size);
	}
}

void bds_resize(bds_t s, uint32_t new_size) {
	if (s) {
		s->ptr = BDS_REALLOC(s->ptr, new_size * sizeof(char));
		s->ptr[new_size - 1] = '\0';
		s->size = new_size;
	}
}

void bds_free(bds_t s) {
	if (s) {
		BDS_FREE(s->ptr);
		BDS_FREE(s);
	}
}


// working with strings
void bds_clear(bds_t s) {
	if (s) {
		s->ptr[0] = '\0';
		s->len = 0;
	}
}

void bds_set(bds_t s, const char* in) {
	if (s && in) {
		uint32_t in_len = strlen(in);
		if (s->size < in_len)
			bds_resize(s, in_len + BASE);
		memcpy(s->ptr, in, in_len);
		s->ptr[in_len] = '\0';
		s->len = in_len;
	}
}

void bds_cat(bds_t s, const bds_t in) {
	if (s && in) {
		uint32_t max_len = s->len + in->len;
		if (s->size < max_len)
			bds_resize(s, max_len + BASE);
		memcpy(s->ptr + s->len, in->ptr, in->len);
		s->ptr[max_len] = '\0';
		s->len = max_len;
	}
}

void bds_cpy(bds_t s, const bds_t in) {
	if (s && in) {
		if (s->size < in->len)
			bds_resize(s, in->len + BASE);
		memcpy(s->ptr, in->ptr, in->len);
		s->ptr[in->len] = '\0';
		s->len = in->len;
	}
}

bool bds_cmp(const bds_t s1, const bds_t s2) {
	if (s1 && s2) {
		if (s1->len != s2->len) return false;
		for (uint32_t i = 0; i < s1->len; i++) {
			if (s1->ptr[i] != s2->ptr[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void bds_range(bds_t s, uint32_t start, uint32_t end) {
	if (s) {
		if (start > end) return;
		if (start > s->len) return;
		if (end > s->len) return;

		uint32_t len = end - start;

		memcpy(s->ptr, s->ptr + start, len);
		s->ptr[len] = '\0';
		s->len = len;
	}
}

void bds_tolower(bds_t s) {
    for (uint32_t i = 0; i < s->len; i++) {
    	s->ptr[i] = tolower(s->ptr[i]);
    }
}

void bds_toupper(bds_t s) {
    for (uint32_t i = 0; i < s->len; i++) {
    	s->ptr[i] = toupper(s->ptr[i]);
    }
}

void bds_fmt(bds_t s, const char* fmt, ...) {
	static char buffer[4096];
	va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    bds_set(s, buffer);
}

void bds_catfmt(bds_t s, const char* fmt, ...) {
	static char buffer[4096];
	va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    bds_strcat(s, buffer);
}


// working with strings and classic char*
void bds_strcat(bds_t s, const char* in) {
	if (s && in) {
		uint32_t in_len = strlen(in);
		uint32_t max_len = s->len + in_len;
		if (s->size < max_len)
			bds_resize(s, max_len + BASE);
		memcpy(s->ptr + s->len, in, in_len);
		s->ptr[max_len] = '\0';
		s->len = max_len;
	}
}

bool bds_strcmp(const bds_t s1, const char* s2) {
	if (s1 && s2) {
		if (s1->len != strlen(s2)) return false;
		for (uint32_t i = 0; i < s1->len; i++) {
			if (s1->ptr[i] != s2[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

#undef BDS_MALLOC
#undef BDS_CALLOC
#undef BDS_REALLOC
#undef BDS_FREE

#undef BASE
