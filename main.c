#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// freaky GNUPlot stuff
void plotGraph(const char *filename) {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot != NULL) {
        fprintf(gnuplot, "set title 'Sequence Graph'\n");
        fprintf(gnuplot, "set xlabel 'n'\n");
        fprintf(gnuplot, "set ylabel 'f(n)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot '%s' with lines\n", filename);
        pclose(gnuplot);
    } else {
        printf("Error: Could not open gnuplot.\n");
    }
}

int main(int argc, char *argv[]) {
    int plotornah = 0;

    // Variable to print the table in the console, or nahh
    int printornah = 1;

    if (argc > 1) {
        for (int x = 0; x < argc; x++) {
            if (strcmp(argv[x], "--p") == 0 || strcmp(argv[x], "--plot") == 0) {
                plotornah = 1;
            }
            else if (strcmp(argv[x], "--noprint") == 0 || strcmp(argv[x], "--n") == 0) {
                printornah = 0;
            }
        }
    }
    char arithorgeo[10];
    double rate, intercept;
    int arorgeo, end;
    int x = 0;
    FILE *fp = fopen("data.txt", "w");  // filetime hehehehe

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Arithmetic or  geometric prompt
    printf("Arithmetic or Geometric (all lowercase): ");
    scanf("%s", arithorgeo);

    if (strcmp(arithorgeo, "arithmetic") == 0 || strcmp(arithorgeo, "ari") == 0 || strcmp(arithorgeo, "a") == 0) {
        arorgeo = 0;
    } else if (strcmp(arithorgeo, "geometric") == 0 || strcmp(arithorgeo, "geo") == 0 || strcmp(arithorgeo, "g") == 0) {
        arorgeo = 1;
    } else {
        printf("Please enter 'arithmetic' or 'geometric'\n");
        return 1;
    }

    // Get the rate and intercept
    printf("Enter your rate (Common difference/common ratio): ");
    scanf("%lf", &rate);
    printf("Enter your intercept (or start, f(0)): ");
    scanf("%lf", &intercept);
    printf("min: ");
    scanf("%d", &x);
    printf("max: ");
    scanf("%d", &end);

    char start0[4];
    printf("Is the first value you put in f(1) (no for f(0)): ");
    scanf("%s", start0);

    if (strcmp(start0, "no") == 0 || strcmp(start0, "n") == 0 || strcmp(start0, "0") == 0) {
        // Nothing
    } else if (strcmp(start0, "yes") == 0 || strcmp(start0, "y") == 0 || strcmp(start0, "1")) {
        // Nah, I'd adapt
        if (arorgeo == 0) {
            intercept -= rate;
        } else if (arorgeo == 1) {
            intercept /= rate;
        }
    } else {
        printf("Please enter a valid input.\n");
        return 1;
    }

    if(printornah == 1){
        printf("  n | f(n\n");
        printf("----------\n");
    }
    // Show the graph and write the data
    if (arorgeo == 0) {
        // Arithmetic sequence
        while (x <= end) {
            double fn = intercept + x * rate;
            if(printornah == 1){
                printf("%3d | %lf\n", x, fn);
            }
            fprintf(fp, "%d %lf\n", x, fn);
            ++x;
        }
        if(printornah == 1){
            printf("\nf(n) = %lf + %lf * n\n", intercept, rate);
        }
    } else if (arorgeo == 1) {
        // Geometric sequence
        while (x <= end) {
            double fn = intercept * pow(rate, x);
            if(printornah == 1){
                printf("%3d | %lf\n", x, fn);
            }
            fprintf(fp, "%d %lf\n", x, fn);
            ++x;
        }
        if(printornah == 1){
            printf("\nf(n) = %lf * %lf^n\n", intercept, rate);
        }
    }


    fclose(fp);

    // Open Graph
    if (plotornah == 1) {
        plotGraph("data.txt");
    }
    return 0;
}
