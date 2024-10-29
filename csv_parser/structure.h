#ifndef ML_SCRATCH_H
#define ML_SCRATCH_H

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

void parse(const char* filename, DataFrame* df);
void free_dataframe(DataFrame* df);

#endif /* end of include guard: ML_SCRATCH_H */
