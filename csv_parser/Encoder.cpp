#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_functions.h"

int get_cols(FILE*);
int get_rows(FILE*);

int main() {
	FILE* fp = fopen("data_preprocessed.csv", "r");
	if (fp == NULL) {
		printf("Error opening the file!\n");
		exit(EXIT_FAILURE);
	}
	int col_count = get_cols(fp);
	int row_count = get_rows(fp);
	char* token;
	char buffer[1000];
	
	char*** data = (char***)malloc(row_count * sizeof(char**));
	for (int i = 0; i < row_count; i++) {
		data[i] = (char**)malloc(col_count * sizeof(char*));
	}

	for (int i = 0; i < row_count; i++) {
		fgets(buffer, 1000, fp);
		token = strtok(buffer, ",");
		int j = 0;
		while (token != NULL) {
			//printf("%s\n", token);
			data[i][j] = (char*)malloc(strlen(token) * sizeof(char));
			strcpy(data[i][j], token);
			j++;
			token = strtok(NULL, ",");
		}
	}
	
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			printf("%s, ", data[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int get_cols(FILE* fp) {
	int col_count = 0;
	char first_row[1000];
	char* token;
	fgets(first_row, 1000, fp);
	token = strtok(first_row, ",");
	while (token != NULL) {
		//printf("%s\n", token);
		token = strtok(NULL, ",");
		col_count++;
	}
	fseek(fp, 0, SEEK_SET);
	return col_count;
}

int get_rows(FILE* fp) {
	int lines = 0;
	char buf_ch = fgetc(fp);
	while (buf_ch != EOF) {
		if (buf_ch == '\n') {
			lines++;
		}
		buf_ch = fgetc(fp);
	}
	fseek(fp, 0, SEEK_SET);
	return lines;
}