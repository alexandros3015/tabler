#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>

int main() {
    system("cls");
    char arithorgeo[10];
    double rate, intercept;
    int arorgeo, end;
    int x = 0;
    printf("Aritmetic or Geometric (all lowercase): ");
    scanf("%s", arithorgeo);
    if (strcmp(arithorgeo, "arithmetic") == 0 || strcmp(arithorgeo, "ari") == 0 || strcmp(arithorgeo, "a") == 0) {
        arorgeo = 0;
    } else if (strcmp(arithorgeo, "geometric") == 0 || strcmp(arithorgeo, "geo") == 0 || strcmp(arithorgeo, "g") == 0) {
        arorgeo = 1;
    } else {
        printf("Please either aritmetic or geometric");
        return 1;
    }
    char start0[4];
    printf("Enter your rate (Common difference/common ratio): ");
    scanf("%lf", &rate);
    printf("Enter your intercept (or start, X is 0): ");
    scanf("%lf", &intercept);
    printf("Ending X value (gotta stop somewhere): ");
    scanf("%d", &end);
    printf("Is the first value you put in f(1) (no for f(0)): ");
    scanf("%s", start0);
    
    if (strcmp(start0, "no") == 0 || strcmp(start0, "n") == 0) {
        // no more
    } else if (strcmp(start0, "yes") || strcmp(start0, "y") == 0) {
        if (arorgeo == 0) {
            intercept = intercept - rate;
        } else if (arorgeo == 1) {
            intercept = intercept / rate;
        } else {
            printf("ERROR");
            return 1;
        }
    } else {
        printf("Please enter a valid input");
        return 1;
    }
    printf("  n  |  f(n)\n");
    printf("-----------------\n");
    if (arorgeo == 0) {
        
        while (x <= end) {
            printf(" %3d | %f\n", x, intercept + (x * rate));
            ++x;
        }
    } else if (arorgeo == 1) {
            while (x <= end) {
                printf(" %3d | %f\n", x, intercept * pow(rate, x));
                ++x;
            }
    }
    if (arorgeo == 0) {
        printf("\nLine: f(n) = %lfn + %lf", rate, intercept);
    } else if (arorgeo == 1) {
        printf("\nLine: f(n) = %lf^n * %lf", rate, intercept);
    }        
    return 0;
}