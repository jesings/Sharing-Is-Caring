#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
int main(){
    key_t key = ftok("sharing.c",'R');
    int shmem;
    char just_created = 0;
    if((shmem = shmget(key,200,0644))==-1){
        shmem = shmget(key,200,0644 | IPC_CREAT);
        just_created = 1;
    }
    char* strmem = shmat(shmem,NULL,0);
    if(just_created) printf("Just created the memory\n");
    else printf("The data is: %s\n",strmem);
    printf("Insert data? (y/n) ");
    fflush(stdout);
    char confirmation[2], appendstr[200];
    fgets(confirmation,2,stdin);
    getchar();
    if(!strcmp(confirmation,"y")||!strcmp(confirmation,"Y")){
        printf("Insert your text please: ");
        fflush(stdout);
        fgets(appendstr,200,stdin);
        strcat(strmem,appendstr);
    }
    
    shmdt(strmem);
    printf("Delete shared memory? (y/n) ");
    fflush(stdout);
    fgets(confirmation,2,stdin);
    if(!strcmp(confirmation,"y")||!strcmp(confirmation,"Y"))
        shmctl(shmem, IPC_RMID, NULL);
}
