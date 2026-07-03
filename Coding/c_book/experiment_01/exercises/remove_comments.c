#include <stdio.h>

#define NORMAL 0
#define STRING 1
#define CHARACTER 2
#define LINE_COMMENT 3
#define BLOCK_COMMENT 4

int main(void) {
    int c, next;
    int state = NORMAL;
    /* some commenting */
    while ((c = getchar()) != EOF) {
        if (state == NORMAL) {
            if (c == '"') {
                state = STRING;
                putchar(c);
            } else if (c == '\'') {
                state = CHARACTER;
                putchar(c);
            } else if (c == '/') {
                next = getchar();

                if (next == '/') {
                    state = LINE_COMMENT;
                } else if (next == '*') {
                    state = BLOCK_COMMENT;
                    putchar(' ');
                } else {
                    putchar(c);
                    if (next != EOF) {
                        ungetc(next, stdin);
                    }
                }
            } else {
                putchar(c);
            }
        } else if (state == STRING) {
            putchar(c);

            if (c == '\\') {
                next = getchar();

                if (next != EOF) {
                    putchar(next);
                }
            } else if (c == '"') {
                state = NORMAL;
            }
        } else if (state == CHARACTER) {
            putchar(c);

            if (c == '\\') {
                next = getchar();

                if (next != EOF) {
                    putchar(next);
                }
            } else if (c == '\'') {
                state = NORMAL;
            }
        } else if (state == LINE_COMMENT) {
            if (c == '\n') {
                putchar(c);
                state = NORMAL;
            }
        } else if (state == BLOCK_COMMENT) {
            if (c == '*') {
                next = getchar();

                if (next == '/') {
                    state = NORMAL;
                } else if (next != EOF) {
                    ungetc(next, stdin);
                }
            }
        }
    }

    return 0;
}
