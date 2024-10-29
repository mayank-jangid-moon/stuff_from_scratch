#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/structure.h"
#include "include/csv_parser.h"
#include "include/plot.h"

double cost(DataFrame* df, int w, int b) {
	double loss = 0;
	for (size_t i = 0; i < df->len_rows; i++) {
		loss += pow(df->data[1][i] - (w * df->data[0][i] + b), 2);
	}
	loss = loss / df->len_rows;
	return loss;
}

void gradient_descent(DataFrame* df, double* w, double* b, double eeta) {
	double diff_w = 0, diff_b = 0;
	for (int i = 0; i < df->len_rows; i++) {
		diff_w += df->data[0][i] * (df->data[1][i] - ((*w) * df->data[0][i] + *b));
	}
	diff_w = -2 * diff_w / df->len_rows;

	for (int i = 0; i < df->len_rows; i++) {
		diff_b += df->data[1][i] - ((*w) * df->data[0][i] + *b);
	}
	diff_b = -2 * diff_b / df->len_rows;

	*w = *w + -eeta * diff_w;
	*b = *b + -eeta * diff_b;
}

double sum_square(DataFrame* df, double w, double b) {
	double ss = 0;
	for (int i = 0; i < df->len_rows; i++) {
		ss += pow(df->data[1][i] - (w * df->data[0][i] + b), 2);
	}
	return ss;
}

double r_square(DataFrame* df, double w, double b, double avg_y) {
	return (sum_square(df, 0, avg_y) - sum_square(df, w, b)) / sum_square(df, 0, avg_y) * 100;
}

int main() {
	DataFrame df = { 0 };
	removeCarriageReturn("Salary.csv", "clean.csv");
	parse("clean.csv", &df);

	/*for (size_t i = 0; i < df.len_cols; i++) {
		for (size_t j = 0; j < df.len_rows; j++) {
			printf("[%lu][%lu] = %lf\n", i, j, df.data[i][j]);
		}
	}*/

	//for (int i = 0; i < df.len_rows; i++) {   //PLEASE DOUBLE KI SIZE PE REHEN KARE AUR APNE DATA KO SCALE KAR LE :PRAYING_HANDS:
	//	df.data[1][i] /= 10000;               // Y
	//	df.data[0][i] /= 10000;               // X
	//}

	double avg_y = 0;
	for (int i = 0; i < df.len_rows; i++) avg_y += df.data[1][i];
	avg_y /= df.len_rows;

	double w = 0, b = avg_y;
	int epochs = 1000000;
	double eeta = 0.0001;

	//scatter_plot(&df);
	plot_line(w, b);

	for (int i = 0; i < epochs; i++) {
		gradient_descent(&df, &w, &b, eeta);
		if (i % 500 == 0) printf("%d\n", i);
	}

	printf("The R Squared Value of Fit Line is: %lf%\n", r_square(&df, w, b, avg_y));
	printf("The equation of fit line is: y = %lfx + %lf\n", w, b);
	plot_scatter_and_line(w, b, &df);

	free_dataframe(&df);
	return 0;
}