#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void put_pull_rod(int signum);
void fish_eating();
void exit_game(int signum);

int fishNum = 0;        // counting fish number
int boolean = 0;        // used as a boolean
int check = 1;          //not get the fish

int main(void){

        srand(time(NULL));
        struct sigaction sig_put_pull_rod;
        sig_put_pull_rod.sa_handler = put_pull_rod;

        struct sigaction sig_exit_game;
        sig_exit_game.sa_handler = exit_game;

        //write your code here
        write(STDOUT_FILENO,"fishing rod is ready\n",22);
        while(1){
        if(check == 1){
                sigaction(SIGINT,&sig_put_pull_rod,NULL);
                sigaction(SIGTSTP,&sig_put_pull_rod,NULL);
        }
        sigaction(SIGTSTP,&sig_exit_game,NULL);
        }
        return 0;
}


void put_pull_rod(int signum){
        if(boolean==0){
                write(STDOUT_FILENO,"Put the fishing rod\n",21);

                write(STDOUT_FILENO,"Bait into water, waiting fish\n",31);
                boolean++;
        }
        else if (boolean==1)
        {
                int nunf = rand() % 2 + 1;
                write(STDOUT_FILENO,"Pull the fishing rod\n",22);
                signal(SIGALRM,fish_eating);                      //wait to pull rod 
                alarm(nunf);
                boolean--;
        }

}

void fish_eating(){


        int num = rand() % 2+1;
        int numt = rand() % 2+1;
        if(num==1){
        write(STDOUT_FILENO,"fishing rod is ready\n",22);
        }
        else{
                if(numt==1){
                        write(STDOUT_FILENO,"catch a fish!\n",14);      //in time limit
                        fishNum++;
                        check=0;
                }
                else{                           //not in time limit
                        write(STDOUT_FILENO,"the bait was eaten\n",19);

                }
        }
}

void exit_game(int signum){
        printf("\nTotally caught fishes: %d\n", fishNum);
        exit(0);
}
