#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(int argc , char *argv[]) {
    DIR *directory;
    struct dirent *d;

    if((directory = opendir(argv[1])) == NULL) {
        printf("%s/n", "Directory open error");
        return 1;
    }
    printf("Directory %s\n", argv[1]);
    while((d = readdir(directory)) != NULL) {
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, "..")){
            continue;
        }
        printf("%s\n", d->d_name);
    }

    if (closedir(directory) != 0) {
        printf("%s/n", "Directory close error");
        return 1;
    }

    printf(" \n");

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("%s/n", "Current dir error");
        return 1;
    }

    char *current_dir = "./";
    if((directory = opendir(current_dir)) == NULL) {
        printf("%s/n", "Directory open error");
        return 1;
    }
    printf("Directory %s\n", cwd);
    while((d = readdir(directory)) != NULL) {
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, "..")){
            continue;
        }
        printf("%s\n", d->d_name);
    }

    if (closedir(directory) != 0) {
        printf("%s/n", "Directory close error");
        return 1;
    }
}
