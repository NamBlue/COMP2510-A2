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
        fprintf(stderr, "%s\n%s\n%s\n", "Must specify two arguments when executing this program,"
            ,"the target character set and then the destination character set."
            ,"Consult Readme.txt for more information.");
        return 1;
    }
    
    strcpy(set1, argv[1]);
    strcpy(set2, argv[2]);
    
    escapeCheck(set1);
    escapeCheck(set2);
    
    expandRange(set1);
    expandRange(set2);
    
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
Checks and expands the range of both sets and checks if length exceeds MAXSIZE
*/
int expandRange(char *set) {
    int i, j, k;
    int len = strlen(set);
    char a, b, temp[LINESIZE];

    for (i = 0; i < len; i++) {
        if (set[i] == '-' && (i != 0 && i != len - 1)) {
            /*Checks*/
            if (set[i - 1] > set[i + 1]) {
               fprintf(stderr, "%s\n", "Invalid range of characters!!");
               exit(2);
            }
            /*Expands into a temp array*/
            a = set[i - 1];
            b = set[i + 1];
            if (a == b) {
                strcpy(&set[i - 1], &set[i + 1]);
            } else {
                for (j = 0; a < b; a++, j++) {
                    temp[j] = a + 1;
                }
                temp[j] = '\0';
                /*Shifts the set array to the right to accomodate the expanded characters*/
                strcpy(&set[i + strlen(temp) - 1], &set[i + 1]);
                /*Copies the expanded array into the right positions*/
                for (j = i, k = 0; temp[k] != '\0'; k++, j++) {
                    set[j] = temp[k];
                }
            }
            len = strlen(set);            
            i += strlen(temp);
        }
    }
    if (strlen(set) > MAXSIZE - 1) {
        fprintf(stderr, "%s\n", "Argument length exceed 255 characters");
        exit(3);
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
Translates using set1 to set2 into standard output
*/
int translate(char *set1, char *set2) {
    int i;
    char c;
    
    while((c = getchar()) != EOF) {
        for (i = strlen(set1); i > 0; i--) {
            if(c == set1[i - 1]) {
                c = set2[i - 1];
                break;
            }
        }
        putchar(c);
    }
    return 0;
}