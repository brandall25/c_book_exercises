#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getch.h"

#define MAXWORD 100
#define MAXLINES 10

typedef struct tnode *Tptr;

typedef struct tnode {
    char word[MAXWORD + 1];
    int line_count;
    int lines[MAXLINES];
    Tptr left;
    Tptr right;

} Tnode;

int getword(char *, int);
int addnode(Tptr, char *, int);
Tptr talloc(char *);
void printtree(Tptr);
void freetree(Tptr);
int is_article(char *);

int main() {

/* 
 * 1. Read a word
 * 2. Find/Add word to tree 
 * 3. Add line number to list in tree node
 * 4. Print out 
 */

    int line = 0;
    char word[MAXWORD + 1];
    Tptr bptr;

    while(getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !is_article(word)) {
            if (!bptr) {
                bptr = talloc(word);
            }
            if (addnode(bptr, word, line)) {
                return -1;
            }
        } else if (word[0] == '\n') {
            line++;
        }
    } 

    printtree(bptr);
    freetree(bptr);
}

int getword(char *word, int lim) {

    int c; 
    char *w = word;

    while(isspace(c = getch()) && c != '\n');

    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    } 

    *(w-1) = tolower(c);
    for (; --lim > 0; w++) {
        if (!isalnum(*w = tolower(getch())) && *w != '\'') {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int addnode(Tptr node, char *word, int current_line) {

    int cmp = strcmp(word, node->word);

    if (!cmp) { // If found, add current_line to line_count
        if (node->line_count == MAXLINES) {
            fprintf(stderr, "Error: Exceeded max lines (%d) for one node\n", MAXLINES);
            return -1;
        }

        if (!node->line_count || node->lines[node->line_count - 1] < current_line) {
            node->lines[node->line_count++] = current_line;
        }

        return 0;
    } else if (cmp < 0) { // If less than, look left
        if (!node->left) {
            node->left = talloc(word);
        }
        return addnode(node->left, word, current_line);
    } else if (cmp > 0) { // If greater than, look right
        if (!node->right) {
            node->right = talloc(word);
        }
        return addnode(node->right, word, current_line);
    }

}

Tptr talloc(char *word) { // allocate and initialize a treenode
    Tptr t = (Tptr) malloc(sizeof(Tnode));
    t->line_count = 0;
    strcpy(t->word, word);
    return t;
}

void printtree(Tptr node) {

    if (node->left) {
        printtree(node->left);
    }

    printf("%s: ", node->word);
    for (int i = 0; i < node->line_count; i++) {
        printf("%d ", node->lines[i]);
    }
    printf("\n");
    
    if (node->right) {
        printtree(node->right);
    }

}

void freetree(Tptr node) {

    if (node->left) {
        freetree(node->left);
    }
    
    if (node->right) {
        freetree(node->right);
    }

    free(node);

}

int is_article(char *word) {
    if (!strcmp(word, "the") || !strcmp(word, "a") || !strcmp(word, "an")) {
        return 1;
    }
    return 0;
}
