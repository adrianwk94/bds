#include "bds.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

void print_string(bds_t s) {
	printf("[ len %u, size %u ] -> %s\n", s->len, s->size, s->ptr);
}

void print_info(bds_t s, const char* info) {
	printf("[ len %u, size %u ] -> %s\n", s->len, s->size, info);
}

int main() {

	bds_t test_empty = bds_empty();
	print_info(test_empty, "test_empty");

	bds_t test_create = bds_create(512);
	print_info(test_create, "test_dup");

	bds_t test_new = bds_new("Hello");
	print_string(test_new);

	bds_t test_dup = bds_dup(test_new);
	print_string(test_dup);

	strncpy(test_dup->ptr, "Hello Earth", test_dup->size);
	bds_refresh(test_dup);
	print_string(test_dup);

	bds_set(test_empty, "World");
	print_string(test_empty);

	bds_cpy(test_create, test_new);
	print_string(test_create);

	assert(bds_cmp(test_new, test_create));

	bds_cat(test_new, test_empty);
	print_string(test_new);

	bds_fmt(test_create, "%s %s", test_create->ptr, test_empty->ptr);
	print_string(test_create);

	bds_catfmt(test_create, ", %s", test_dup->ptr);
	print_string(test_create);

	assert(bds_strcmp(test_create, "Hello World, Hello Earth"));

	bds_toupper(test_create);
	print_string(test_create);

	return 0;
}
