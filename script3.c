#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]) {
        FILE *fout;
        fout=fopen(argv[1], "r");
        int n = atoi(argv[2]);
        if (!fout) {
                printf("%s", "File open error\n");
                return 1;
        }
        if (n == 0){
            n = 2147483646;
        }
        char s;
        int count = 1;
        while ((s=getc(fout)) != EOF) {
            if (count <= n){
                printf("%c", s);
            }
            if (count == n){
                count = 0;
                getc(stdin);
            }
            if ( s == '\n'){
                count++;
            }
        }

        if (fclose(fout) == -1) {
                printf("%s", "File close error\n");
                return 1;
        }
        return 0;
}
