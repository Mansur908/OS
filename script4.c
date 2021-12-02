#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]) {
        FILE *fout;
        fout=fopen(argv[1], "r");
        FILE *fin;
        fin=fopen(argv[2], "wt");
        if (!fout || !fin) {
                printf("%s", "File open error\n");
                return 1;
        }
        int s;
        while ((s=getc(fout)) != EOF) {
            fputc(s, fin);
        }

        if ((fclose(fout) == -1) || (fclose(fin) == -1)) {
                printf("%s", "File close error\n");
                return 1;
        }
        return 0;
}
