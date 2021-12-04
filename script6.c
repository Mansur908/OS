#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#define STR_SIZE 512

char *resultpath;
int dir_count = 0;
int file_count = 0;
bool findf = false;

int find(char *folder, char *filename){
    DIR *directory;
    struct dirent *d;
    char *filepath=(char *)malloc(sizeof(char)*STR_SIZE);

    if((directory = opendir(folder)) == NULL) {
        printf("%s/n", "Directory open error");
        return 1;
    }

    while(d = readdir(directory)) {
        if (d->d_type != DT_DIR){
            file_count++;
            if (strcmp(filename,d->d_name) == 0){
                findf = true;
                if (realpath(folder, filepath) != NULL) {
                    resultpath = filepath;
                }
                else{printf("The file was found, but an error occurred\n");}
            }
        }
        else {
            if (((d->d_type == DT_DIR)) && ((strcmp(d->d_name,".")) != 0) && ((strcmp(d->d_name,"..")) != 0)){
                dir_count++;
                if (realpath(folder, filepath) != NULL){
                    strcat(filepath,"/");
                    strcat(filepath,d->d_name);
                }
                find(filepath, filename);
            }
        }
    }

    if (closedir(directory) != 0) {
        printf("%s/n", "Directory close error");
        return 1;
    }
}

void filedata(struct stat buf, char *filepath)
{
        char *string;
        struct  tm lt;
        string=(char *)malloc(sizeof(char)*STR_SIZE);
        localtime_r(&buf.st_mtime,&lt);
        strftime(string, sizeof(char*)*STR_SIZE, "%d %b %Y", &lt);
        printf("%ld %lo %ld %s\n", buf.st_size, (long)buf.st_mode, (long)buf.st_ino, string);
}

int main(int argc , char *argv[]) {
    struct stat buf;
    find(argv[1], argv[2]);
    if (findf){
        printf("%s %s ", resultpath, argv[2]);
    }
    else{
        printf("File not found\n");
        return 1;
    }
    strcat(resultpath, "/");
    strcat(resultpath, argv[2]);
    stat(resultpath, &buf);
    filedata(buf, resultpath);

    printf("dir - %d\n",dir_count);
    printf("file - %d\n",file_count);
}
