#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stddef.h>

typedef struct str str;
struct str {
	size_t len;
	char* ptr;
};

typedef struct DataFrame DataFrame;
struct DataFrame {
	size_t len_rows;
	size_t len_cols;
	str* col_names;
	double** data;
};

#endif
