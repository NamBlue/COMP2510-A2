#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define LINESIZE 1024
#define MAXSIZE 256

/*
Method prototypes
*/
int escapeCheck(char *set);
int rangeCheck(char *set);
int expandRange(char *set);
int truncate(char *set1, char *set2);
int translate(char *set1, char *set2);

/*
Main, the entry point
*/
int main (int argc, char *argv[]) {
    char set1[LINESIZE];
    char set2[LINESIZE];
        
    if (argc != 3) {
        fprintf(stderr, "%s\n%s\n", "Must specify two arguments when executing this program,"
            ,"the target character set and then the destination character set");
        return 1;
    }
    
    strcpy(set1, argv[1]);
    strcpy(set2, argv[2]);
    
    escapeCheck(set1);
    escapeCheck(set2);
    
    rangeCheck(set1);
    rangeCheck(set2);
    /*
    Expand range
    */
    
    truncate(set1, set2);
    translate(set1, set2);
    return 0;
}

/*
Check for escape characters and stores them as one escape character
*/
int escapeCheck(char *set) {
    int i;
    int a = strlen(set);
    
    for (i = 0; i < a; i++) {
        if (set[i] == '\\') {
            switch (set[i + 1]) {
                case '\\' :
                    set[i] = '\\';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'a' :
                    set[i] = '\a';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'b' :
                    set[i] = '\b';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'f' :
                    set[i] = '\f';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'n' :
                    set[i] = '\n';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'r' :
                    set[i] = '\r';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 't' :
                    set[i] = '\t';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case 'v' :
                    set[i] = '\v';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case '\'' :
                    set[i] = '\'';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                case '\"' :
                    set[i] = '\"';
                    strcpy(&set[i + 1], &set[i + 2]);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

/*
Checks the range of both sets
*/
int rangeCheck(char *set) {
    int i;
    int a = strlen(set);

    for (i = 0; i < a; i++) {
        if (set[i] == '-' && (i != 0 || i != a - 1)) {
            if (set[i - 1] > set[i + 1]) {
               fprintf(stderr, "%s\n", "Invalid range of characters!!");
               exit(2);
            }
            i += 2;
        }
    }
    return 0;
}

/*
Expands the range of both sets and checks if length exceeds MAXSIZE
*/
int expandRange(char *set) {
    int i;
    int len = strlen(set);
    char a, b, temp[LINESIZE];
    
    strcpy(temp, set);

    for (i = 0; i < len; i++) {
        if (set[i] == '-' && (i != 0 || i != len - 1)) {
            a = set[i - 1];
            b = set[i + 1];
            for (a; a < b; a++) {
                /*Expand into a array and use strlen to get size changed*/
            }
            i += 2;
        }
    }
    return 0;
}

/*
Truncates the longest set to make both sets of equal length
*/
int truncate(char *set1, char *set2) {
    int a, b;
    
    a = strlen(set1);
    b = strlen(set2);
    
    if (a > b) {
        set1[b] = '\0';
    }
    if (a < b) {
        set2[a] = '\0';
    }
    return 0;
}

/*
Translates using set1 to set2 to standard output
*/
int translate(char *set1, char *set2) {
    int i,a;
    char c;
    a = strlen(set1);
       
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