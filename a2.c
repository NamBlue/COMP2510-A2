#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define LINESIZE 1024
#define MAXSIZE 256

/*
Method prototypes
*/
int rangeCheck(char set[]);

/*
Seperates the argument into two sets for target and destination characters
*/
int storeSet(char *argv[], char set1[], char set2[]) {
    int i, j;
    for (i = 0; *argv[i] != ' '; i++) {
        set1[i] = *argv[i];
    }
    for (j = 0; *argv[i] != ' '; j++) {
        set2[j] = *argv[i];
    }
    return 0;
}

/*
Main, the entry point
*/
int main (int argc, char *argv[]) {
    char set1[LINESIZE];
    char set2[LINESIZE];
    int i, a, b;
    char c;
    
        
    if (argc != 3) {
        fprintf(stderr, "%s\n%s\n", "Must specify two arguments when executing this program,"
            ,"the target character set and then the destination character set");
        return 1;
    }
    
    strcpy(set1, argv[1]);
    strcpy(set2, argv[2]);
    
    rangeCheck(set1);
    rangeCheck(set2);
    
    a = strlen(set1);
    b = strlen(set2);
    /*Truncate*/
    if (a > b) {
        set1[b] = '\0';
    }
    if (a < b) {
        set2[a] = '\0';
    }
    
    /*Translate*/
    while((c = getchar()) != EOF) {
        for (i = a; i > 0; i--) {
            if(c == set1[i - 1] && set2[i - 1] != '\0') {
                c = set2[i - 1];
            }
        }
        putchar(c);
    }
    
    return 0;
}

/*
Checks the range of both sets
*/
int rangeCheck(char set[]) {
    int i;
    int a = strlen(set);

    for (i = 0; i < a; i++) {
        if (set[i] == '-' && (i != 0 || i != a - 1)) {
            if (set[i - 1] > set[i + 1]) {
               fprintf(stderr, "%s\n", "Invalid range of characters!!");
               return 2;
            }
            i += 2;
        }
    }
    return 0;
}
