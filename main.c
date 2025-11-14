#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif


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
    int plotornah = 0; // 1 is do plot 0 is no

    // Variable to print the table in the console, or nahh
    int printornah = 1;
    int deleteafter = 1; // 1 means don't delete the file after plotting
    int edge = 0;
    if (argc > 1) {
        for (int x = 0; x < argc; x++) {
            
            if (strcmp(argv[x], "--p") == 0 || strcmp(argv[x], "--plot") == 0 || strcmp(argv[x], "-p") == 0) {
                plotornah = 1;
            }
            
            else if (strcmp(argv[x], "--noprint") == 0 || strcmp(argv[x], "--n") == 0 || strcmp(argv[x], "-n") == 0) {
                printornah = 0;
            } 
            
            else if (strcmp(argv[x], "--remove") == 0 || strcmp(argv[x], "--r") == 0 || strcmp(argv[x], "-r") == 0) {
                deleteafter = 0;
            } 
            
            else if (strcmp(argv[x], "--edge") == 0 || strcmp(argv[x], "--e") == 0 || strcmp(argv[x], "-e") == 0) {
            	edge = 1;
            }

            else if (strcmp(argv[x], "--help") == 0 || strcmp(argv[x], "--h") == 0 || strcmp(argv[x], "-h") == 0) {
                printf("Usage: tabler [options]\n");
                printf("Options:\n");
                printf("  --p, --plot: Plot the graph\n");
                printf("  --noprint, --n: Don't print the graph\n");
                printf("  --remove: Remove the file after plotting\n");
                printf("  --edge: Haha funny edge (suggested by dalepwo)\n");
                printf("  --help: Print this help message\n");
                return 0;
            }

            else {
                printf("Invalid option: %s\n", argv[x]);
                return 1;
            }
        }
    }
    char arithorgeo[15];
    double rate, intercept;
    int arorgeo, end; // Arorgeo: 1 is geometric 0 is arithmetic 2 is exponential
    int x = 0;
    FILE *fp = fopen("data.txt", "w");  // filetime hehehehe

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Arithmetic or  geometric prompt
    printf("Arithmetic, Geometric, or Exponential (a, g, or e): ");
    scanf("%14s", arithorgeo);

    if (strcmp(arithorgeo, "arithmetic") == 0 || strcmp(arithorgeo, "ari") == 0 || strcmp(arithorgeo, "a") == 0) {
        arorgeo = 0;
    } 
    
    else if (strcmp(arithorgeo, "geometric") == 0 || strcmp(arithorgeo, "geo") == 0 || strcmp(arithorgeo, "g") == 0) {
        arorgeo = 1;
    } 
    
    else if (strcmp(arithorgeo, "exponential") == 0 || strcmp(arithorgeo, "e") == 0) {
        arorgeo = 2;
    }
    
    else {
        printf("Please enter 'arithmetic', 'geometric', or 'exponential'\n");
        return 1;
    }

    // Get the rate and intercept
    printf("Enter your rate (Common difference/common ratio): ");
    if (scanf("%lf", &rate) != 1) {
        printf("Error: Invalid input for rate. Please enter a number.\n");
        return 1;
    }

    printf("Enter your staring value (y): ");
    if (scanf("%lf", &intercept) != 1) {
        printf("Error: Invalid input for intercept. Please enter a number.\n");
        return 1;
    }

    printf("min: ");
    if (scanf("%d", &x) != 1) {
        printf("Error: Invalid input for minimum. Please enter a number.\n");
        return 1;
    }

    printf("max: ");
    if (scanf("%d", &end) != 1) {
        printf("Error: Invalid input for Maximum. Please enter a number.\n");
        return 1;
    }

    int start_point = 0;
    printf("Enter x value for given intercept: ");
    if (scanf("%d", &start_point) != 1) {
        printf("Error: Invalid input for x value. Please enter a number.\n");
        return 1;
    }

    // Error handling

    if (rate == 0 && arorgeo == 1) {
        printf("Error: Geometric sequences cannot have a ratio of 0.\n");
        return 1;
    }

    if (intercept == 0 && arorgeo == 1) {
        printf("Error: An intercept for a geometric sequence will result in all values become 0. Replacing 0 with 1.\n");
        intercept = 1;
    }

    if (end < x) {
        printf("Error: Max value should be greater than min value.\n");
        return 1;
    }

    double base = 0.0;
    
    if (arorgeo == 0) {
        base = intercept - rate * start_point;
    }

    else if (arorgeo == 1) {
        base = intercept / pow(rate, start_point);
    }

    else if (arorgeo == 2) {
        base = intercept / exp(rate * start_point);
    }
    
    else {
        printf("Please enter a valid input.\n");
        return 1;
    }

    if(printornah == 1){
        printf("  n | f(n)\n");
        printf("----------\n");
    }
    // Show the graph and write the data
    while (x <= end) {
        if (edge == 1) {
        	#ifdef _WIN32
    			system("cls");  // Windows
			#else
    			system("clear");  // Linux/macOS
			#endif
			SLEEP(500);
        }

        double fn = 0;
        if (arorgeo == 0) {
            fn = base + x * rate; // Arithmetic
        } 
        
        else if (arorgeo == 1) {
            fn = base * pow(rate, x); // Geometric
        } 
        
        else if (arorgeo == 2) {
            fn = base * exp(rate * x); // Exponential
        }
        
        if (printornah == 1) {
            printf("%3d | %lg\n", x, fn);
        }


        fprintf(fp, "%d %lf\n", x, fn);
        ++x;
    }
    
    if (arorgeo == 0) {
        printf("Equation: f(n) = %lg + %lg * n\n", base, rate);
    } 
    
    else if (arorgeo == 1) {
        printf("Equation: f(n) = %lg * %lg ^ n\n", base, rate);
    } 
    
    else if (arorgeo == 2) {
        printf("Equation: f(n) = %lg * e ^ (%lg * n)\n", base, rate);
    }    

    fclose(fp);

    // Open Graph
    if (plotornah == 1) {
        plotGraph("data.txt");
    }
    
    if (deleteafter == 0) {
        if (remove("data.txt") == 0) {
            printf("Sucessfully deleted file");
        } else {
            printf("Error: could not delete file");
        }
    }
    return 0;
}
