#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {

	char arithorgeo[10];
	double rate, intercept;
	int arorgeo, end;
	int x = 0;

	printf("Arithmetic or Geometric (all lowercase): ");
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
    
    if (strcmp(start0, "yes") || strcmp(start0, "y") == 0) {
        intercept = intercept - rate;
    } else if (strcmp(start0, "no") == 0 || strcmp(start0, "n") == 0) {
        // Uhh idk why one would want to do anything here
    } else {
        printf("Please enter a valid input");
        return 1;
    }

	printf("  n  |  f(n)\n");
	printf("-----------------\n");

	if (arorgeo == 0) {
	    
	    while (x <= end) {
			printf(" %3d | %f\n", x, intercept + x * rate);
			++x;
		}
	} else if (arorgeo == 1) {
    
    	if (intercept == 0) {
    			intercept = 1;
    		}
    		while (x <= end) {
    			printf(" %3d | %f\n", x, intercept * pow(rate, x));
    			++x;
    		}
	}
	return 0;
}

