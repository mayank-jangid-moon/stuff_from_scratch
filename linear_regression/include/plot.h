#include <stdio.h>
#include "structure.h"

int scatter_plot(DataFrame* df) {
    FILE* dataFile = fopen("scatter_data.txt", "wb");
    if (!dataFile) {
        fprintf(stderr, "Error: Could not open data file for writing.\n");
        return 1;
    }

    for (int i = 0; i < df->len_rows; i++) {
        fprintf(dataFile, "%lf %lf\n", df->data[0][i], df->data[1][i]);
    }
    fclose(dataFile);

    FILE* gnuplotPipe = _popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        fprintf(stderr, "Error: Could not open Gnuplot.\n");
        return 1;
    }

    fprintf(gnuplotPipe, "set title 'Scatter Plot of Quadratic Function with Noise'\n");
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");
    fprintf(gnuplotPipe, "plot 'scatter_data.txt' with points pt 7 ps 1.5\n"); // pt is point type, ps is point size
    fflush(gnuplotPipe);

    _pclose(gnuplotPipe);
    remove("scatter_data.txt");
    return 0;
}

void plot_line(double m, double c) {
    FILE* gnuplotPipe = _popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        fprintf(stderr, "Error: Could not open Gnuplot.\n");
        return;
    }

    fprintf(gnuplotPipe, "set title 'Line Plot: y = mx + c'\n");
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");
    fprintf(gnuplotPipe, "set xrange [-10:10]\n"); // Adjust x range as needed
    fprintf(gnuplotPipe, "set yrange [%lf:%lf]\n", c-10, c+10); // Adjust y range as needed
    fprintf(gnuplotPipe, "plot %lf * x + %lf title 'y = %.2lfx + %.2lf' with lines\n", m, c, m, c);

    fflush(gnuplotPipe);
    _pclose(gnuplotPipe);
}

void plot_scatter_and_line(double m, double c, DataFrame* df) {
    FILE* dataFile = fopen("scatter_line_data.txt", "w");
    if (!dataFile) {
        fprintf(stderr, "Error: Could not create data file.\n");
        return;
    }

    for (int i = 0; i < df->len_rows; i++) {
        fprintf(dataFile, "%lf %lf\n", df->data[0][i], df->data[1][i]);
    }
    fclose(dataFile);

    FILE* gnuplotPipe = _popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        fprintf(stderr, "Error: Could not open Gnuplot.\n");
        return;
    }
    double max_x = 0, min_x = 0, max_y = 0, min_y = 0;
    max_x = min_x = df->data[0][0];
    max_y = min_y = df->data[1][0];
    for (int i = 0; i < df->len_rows; i++) {
        if (max_x < df->data[0][i]) max_x = df->data[0][i];
        if (min_x > df->data[0][i]) min_x = df->data[0][i];
        if (max_y < df->data[1][i]) max_y = df->data[1][i];
        if (min_y > df->data[1][i]) min_y = df->data[1][i];
    }
    fprintf(gnuplotPipe, "set title 'Scatter Plot with Line y = mx + c'\n");
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");
    fprintf(gnuplotPipe, "set xrange [%lf:%lf]\n", min_x, max_x);
    fprintf(gnuplotPipe, "set yrange [%lf:%lf]\n", min_y, max_y);
    fprintf(gnuplotPipe, "plot 'scatter_line_data.txt' with points pt 7 ps 1.5 title 'Scatter Points', \\\n");
    fprintf(gnuplotPipe, "     %lf * x + %lf title 'y = %.2lfx + %.2lf' with lines\n", m, c, m, c);

    fflush(gnuplotPipe);
    _pclose(gnuplotPipe);

    remove("scatter_line_data.txt");
}