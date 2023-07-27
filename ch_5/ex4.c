/* Author: Brian Randall
 * Date: 7/13/2023
 *
 * Exercise 5.4 from The C Programming Language 2nd Edition. Create a function strend(s, t) that
 * determines if string t is the end of string s and returns 1 if true, 0 o/w. Main reads two lines
 * from stdin, with the first one being s and the second t, separated by a newline character.
 *
 * Compile: cc ex4.c
 * Run: ./a.out < ex4_test.txt
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int strend(char *, char *);

int main() {

    // allocate space for a string s and token t
    char *s = (char*) malloc(MAXLINE);
    char *t = (char*) malloc(MAXLINE);

    // read two strings from stdin 
    fgets(s, MAXLINE, stdin);
    fgets(t, MAXLINE, stdin);

    // check if token t is at the end of string s
    strend(s, t) ? printf("True\n") : printf("False\n");

    // free malloc'd space
    free(s);
    free(t);
}

int strend(char *s, char *t) {

    // find end of each string
    // iterate backwards through each string until end is reached
    int t_len = 0;

    while(*t != '\0') {
        t_len++;
        t++;
    }

    while(*s != '\0') {
        s++;
    } 

    // if all the same return 1, o/w return 0 
    while(t_len-- != 0) {
       if (*--s != *--t) {
           return 0;
       }
       // printf("s: %c\tt: %c\tt_len: %d\n", *s, *t, t_len);
    }

    return 1;
}

/* TODO
 * - error check: t longer than s
 * - error check: MAXLINE value is exceeded
 * - functionality: read and evaluate string/token pairs from stdin until EOF reached
 */
