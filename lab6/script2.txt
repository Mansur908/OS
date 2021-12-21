#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <limits.h>

long factorial (int n)
{
  if (n > 20){
      return LONG_MAX;
  }
  long r;
  for (r = 1; n > 1; r *= (n--));
  return r;
}

float getelem(int j, int i, int N){
    float fun = 2*M_PI*i/N;
    if (j == 1){
        float ost = fmod(fun,(2*M_PI));
        float result;
        if (ost > M_PI){
            result = -1 * (ost - M_PI);
        }
        else{
            result = ost;
        }
        return result;
    }
    if (j % 4 == 3){
        float ost = fmod(fun,(2*M_PI));
        float result;
        if (ost > M_PI){
            result = -1 * (ost - M_PI);
        }
        else{
            result = ost;
        }
        result = -1 * pow(result,j)/factorial(j);
        return result ;
    }
    if (j % 4 == 1){
        float ost = fmod(fun,(2*M_PI));
        float result;
        if (ost > M_PI){
            result = -1 * (ost - M_PI);
        }
        else{
            result = ost;
        }
        result = pow(result,j)/factorial(j);
        return result;
    }
}

void write1(float e, char* filename){
    FILE *fp;
    if((fp= fopen(filename, "a"))==NULL)
    {
        printf("File error1\n");
    }
    fprintf(fp, "%f\n", e);
    fclose(fp);
}

float readandsum(char* filename){
    FILE *fp;
    char str[50];
    float sum = 0;
    if((fp= fopen(filename, "r"))==NULL)
    {
        printf("File error2\n");
    }
    while(!feof(fp)){
        fgets (str,sizeof(str),fp);
        sum += atof(str);
    }
    sum -= atof(str);
    if (-1 == remove (filename))
        printf ("Ошибка\n");
    return sum;
}

void main (int argc, char* argv[]){
    if (argc != 4){
        printf("Arguments error\n");
        exit(1);
    }
    remove ("result.txt");
    pid_t pid;
    char* filename = "out.txt";
    int N = atoi(argv[2]);
    int n = atoi(argv[3]);
    int K = atoi(argv[1]);
    if (n > 20){
        printf("n слишком большое \n");
        exit(1);
    }
    for (int i=0;i<K;i++){
        float sum = 0;
        for (int j=0;j<n*2;j++){
            if ((j % 2) != 0){
                pid = fork();
                wait(NULL);
                if (pid == 0){
                    float elem;
                    elem = getelem(j,i,N);
                    write1(elem, filename);
                    printf("Pid = %d\n", getpid());
                    printf("Element = %f\n", elem);
                    kill(getpid(), SIGKILL);
                }
            }
        }
        printf("-----------\n");
        float result = readandsum(filename);
        printf("sum = %f\n", result);
        write1(result, "result.txt");
        printf("\n");
    }
}
