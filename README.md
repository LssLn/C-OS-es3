# C-OS-es3
Un padre genera 2 figli p1 p2, il padre esegue 10 volte le operazioni : sleep(1), genera n tra 1 e 100, se è pari invia SIGUSR1 a p1, se dispari SIGUSR2 a p2. Infine SIGKILL a entrambi i figli. Ogni figlio in un loop infinito attende l’arrivo di un segnale e ogni volta stampa il pid e il segnale ricevuto
