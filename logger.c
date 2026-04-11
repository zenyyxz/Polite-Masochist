#include <stdio.h>
#include <stdlib.h>

/* 
 * The INTERCAL "Double-Pipe" Logger
 * Because 65,535 primes will absolutely murder your scrollback buffer.
 * This pipes everything from the INTERCAL binary to both stdout and a file.
 */

int main() {
    printf("Starting the INTERCAL Prime Sieve...\n");
    printf("Logging output to 'primes.txt' and console simultaneously.\n\n");

    // We use popen to capture the raw Roman numeral output from the INTERCAL binary
    FILE *in = popen("./primes", "r");
    if (!in) {
        perror("Failed to run ./primes. Make sure you compiled it first!");
        return 1;
    }

    FILE *out = fopen("primes.txt", "w");
    if (!out) {
        perror("Failed to open primes.txt for writing");
        return 1;
    }

    char buf[256];
    while (fgets(buf, sizeof(buf), in)) {
        // Print to console
        printf("%s", buf);
        // Save to file
        fprintf(out, "%s", buf);
        // Flush to ensure we don't lose data if we ctrl+c
        fflush(out);
    }

    pclose(in);
    fclose(out);

    printf("\nDone. All primes saved to primes.txt\n");

    printf("Converting primes.txt to decimal format (primes_in_decimal.txt)...\n");
    if (system("./roman_to_decimal") == 0) {
        printf("Conversion complete.\n");
    } else {
        fprintf(stderr, "Error: Could not run roman_to_decimal converter.\n");
    }

    return 0;
}
