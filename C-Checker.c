// this is an exercise from chapter 1
//Objective: create a program that checkes C programs for syntax errors

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file.c>\n", argv[0]);
        return 1;
    }

    char command[512];

    // -fsyntax-only tells gcc to check syntax but not produce an output file
    snprintf(command, sizeof(command), "gcc -fsyntax-only \"%s\" 2> gcc_errors.txt", argv[1]);

    int result = system(command);

    if (result == 0) {
        printf("✅ No syntax errors found in %s\n", argv[1]);
    } else {
        printf("❌ Syntax errors found in %s:\n\n", argv[1]);

        // Print the contents of gcc_errors.txt
        FILE *f = fopen("gcc_errors.txt", "r"); //will save found syntax errors inside of gcc_errors.txt 
        if (f) {
            char line[256];
            while (fgets(line, sizeof(line), f)) {
                printf("%s", line);
            }
            fclose(f);
        } else {
            perror("Failed to open gcc_errors.txt");
        }
    }

    return result;
}

//When running this program, you can use the command: .\exercise.exe <file-to-check.c> only after building it with gcc.
