#include <stdio.h>
#include <dirent.h>

int main(int argc , char *argv[]) {
    DIR *directory;
    struct dirent *d;

    if((directory = opendir(argv[1])) == NULL) {
        printf("%s/n", "Directory open error");
        return 1;
    }
    printf("Directory %s\n", argv[1]);
    while(d = readdir(directory)) {
        printf("%s\n", d->d_name);
    }

    if (closedir(directory) != 0) {
        printf("%s/n", "Directory close error");
        return 1;
    }

    printf(" \n");

    char *current_dir = "./";
    if((directory = opendir(current_dir)) == NULL) {
        printf("%s/n", "Directory open error");
        return 1;
    }
    printf("Directory %s\n", current_dir);
    while(d = readdir(directory)) {
        printf("%s\n", d->d_name);
    }

    if (closedir(directory) != 0) {
        printf("%s/n", "Directory close error");
        return 1;
    }
}
