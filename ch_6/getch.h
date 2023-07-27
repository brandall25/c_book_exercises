#define BUFSIZE 100

char getch_buf[BUFSIZE];
int getch_bufp = 0;

int getch(void) {
    return (getch_bufp > 0) ? getch_buf[--getch_bufp] : getchar();
}

void ungetch(int c) {
    if (getch_bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        getch_buf[getch_bufp++] = c;
    }
}
