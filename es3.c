/*Un padre genera 2 figli p1 p2, il padre esegue 10 volte le operazioni : sleep(1), genera n tra 1 e 100, se è pari invia SIGUSR1 a p1, se dispari SIGUSR2 a p2.
Infine SIGKILL a entrambi i figli
Ogni figlio in un loop infinito attende l’arrivo di un segnale e ogni volta stampa il pid e il segnale ricevuto */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 2

void fSIGUSR(int sig){
    printf("Signal received number : %d\n",sig);
    pause(); //metto di nuovo in attesa di un segnale
}

//siccome devo stampare anche il pid, devo fare 2 funzioni

int main(){
    pid_t pid[N];
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    act.sa_handler=fSIGUSR;
    sigaction(SIGUSR1,&act,0);
    sigaction(SIGUSR2,&act,0);

    for(int i=0;i<N;i++){
        pid[i]=fork();
        switch(pid[i]){
            case -1:
                //
                break;
            case 0:
                printf("Child %d here, waiting for a signal endlessly ...\n",i);
                while(1){
                    pause();
                }
                break;
            default:
                break;
        }
    }

    //padre
    int n;
    for(int i=0;i<10;i++){
        sleep(1);
        n=rand()%100 +1;
        if(n%2 ==0) {
            //pari
            kill(SIGUSR1,pid[0]);
        }else
            kill(SIGUSR2,pid[1]);
    }

    kill(SIGKILL,pid[0]);
    kill(SIGKILL,pid[1]);


}
