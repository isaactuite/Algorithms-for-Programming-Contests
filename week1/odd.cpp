#include <cstdio>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    for (int i = 1; i <= t; i++) {
        int c = getchar();
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getchar();

        int last = 0;
        while (c != EOF && c != ' ' && c != '\n' && c != '\r' && c != '\t') {
            if (c >= '0' && c <= '9') last = c - '0';
            c = getchar();
        }

        if (last % 2 == 0) printf("Case #%d: This is not odd!\n", i);
        else               printf("Case #%d: This is odd...\n", i);
    }
    return 0;
}