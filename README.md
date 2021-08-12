# BDS - Better Dynamic Strings

This library facilitates the use of strings in C.

It includes the most used and useful functions to work with strings.

# How BDS strings work

This library is inspired by [SDS](https://github.com/antirez/sds) but without using [Fat Pointer](http://libcello.org/learn/a-fat-pointer-library). With the advantages and disadvantages that it represents.

Disadvantages:

- It cannot be used directly in functions that accept pointer to char.

Advantage:

- Internally, it is easier to understand.
- It does not require assigning the pointer in every operation and you can share the pointer without remapping or encapsulating the pointer.

BDS vs SDS examples:

```c
// SDS
printf("%s\n", sds_string);
sds s = sdsempty();
s = sdscat(s, "Hello ");
s = sdscat(s, "World!");
printf("%s\n", s);

// BDS
printf("%s\n", bds_tring->ptr);

bds_t s = bds_empty();
bds_strcat(s, "Hello ");
bds_strcat(s, "World!");
printf("%s\n", s->ptr);
```

In this example, we can see how each `sdscat` returns a pointer in addition to requiring the pointer as an argument. This occurs because the **SDS** functions when allocating memory, changes the pointer, so it requires saving the new pointer.

This is fixed in **BDS**, in exchange for having to use `->ptr` when you need to use it in other functions outside the string library.

## How to use the library?

```c++
struct bds_t {
	char* 		ptr;
	uint32_t 	size;
	uint32_t 	len;
};
```

**`bds_t`** is the structure, and contains important and useful data.

* **`ptr`** is the pointer to the character string.
* **`size`** size reserved in memory.
* **`len`** is the length of the string, like `strlen()`

**String creation with BDS**

- **`bds_empty`** create an empty string with a default size.
- **`bds_create`** create an empty string and allows you to set the memory size.
- **`bds_new`** create a string and copy the value of a char pointer.
- **`bds_dup`** you create a fresh copy of a BDS string.

- **`bds_refresh`** important when using strings in functions external to the library. Allows you to recalculate the length of the string.
- **`bds_resize`** change the memory size of the string.
- **`bds_free`** frees all memory of the string.

**Working with strings**

- **`bds_clear`** clear the string.
- **`bds_set`** sets the string to the value of the char pointer.
- **`bds_cat`** concatenate two strings.
- **`bds_cpy`** copy the value of a string.
- **`bds_range`** turn the string into a smaller (or equal) string containing only the substring specified by the 'start' and 'end' indexes.
- **`bds_tolower`** converts the entire string to lowercase.
- **`bds_toupper`** converts the entire string to uppercase.
- **`bds_fmt`** format the string as the `printf` function using `%`. For BDS strings use `%s` and `s->ptr`.
- **`bds_catfmt`** like `bds_fmt` but concatenating the string.
- **`bds_cmp`** compares two strings character by character.

**Working with BDS and C strings**

- **`bds_strcat`** concatenate a string and a C string.
- **`bds_strcmp`** compares a string and a C string character by character.

## Compile Example

To compile in GCC, use the following commands within the library folder:

```
mkdir build
gcc -Isource/ -Wall main/main.c source/bds.c -o build/bds

In Windows: build\bds.exe
In Mac and Linux: ./build/bds
```

Tested with GCC, MinGW, XCode and Visual Studio 2017.

## Issue Report

You can report a problem in English or Spanish.

> Link to GitHub: <https://github.com/adricoin2010/UTF8-Iterator>

## License

**BDS** is distributed with an MIT License. You can see LICENSE.txt for more info.
