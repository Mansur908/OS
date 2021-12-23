#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>


void gettime(){
    struct timespec mt1;
    clock_gettime (CLOCK_REALTIME, &mt1);
    //Переменная для системного времени
    long int s_time;
    //Указатель на структуру с локальным временем
    struct tm *m_time;
    //Строка для сохранения преобразованного времени
    char str_t[128]="";
    //Считываем системное время
    s_time = time (NULL);
    //Преобразуем системное время в локальное
    m_time = localtime (&s_time);
    //Преобразуем локальное время в текстовую строку
    strftime (str_t, 128, "Время: %T", m_time);
    printf ("%s",str_t);
    printf (":%.3ld\n", mt1.tv_nsec / 1000000);
}

void main ()
{
    if(fork()){
        //wait(NULL);
        if(fork()){
            //wait(NULL);
            printf("Parent\n");
            printf ("Pid процесса = %d\n", getpid());
            printf ("Pid родителя = %d\n", getppid());
            gettime();
            printf("\n");
            system("ps -x | grep script1 -m 3");
        }
        else{
            printf("Child2\n");
            printf ("Pid процесса = %d\n", getpid());
            printf ("Pid родителя = %d\n", getppid());
            gettime();
            printf("\n");
        }
    }
    else{
        printf("Child1\n");
        printf ("Pid процесса = %d\n", getpid());
        printf ("Pid родителя = %d\n", getppid());
        gettime();
        printf("\n");
    }
}
