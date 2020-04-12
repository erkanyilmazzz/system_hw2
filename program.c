#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include"arg.h"
#include"pair.h"
#include <errno.h>


void critical(){
  int i=0;
  for(i=0;i<0;++i){
    printf("%d\n",i);
    sleep(1);
  }
}

void handler(int sig){
printf("%s\n","I am in handler");
}


int main(int argc , char ** argv){
  //unit_test_string_to_pair();

  char *inputPath;
  char *outputPath;

  /*checking and setting arguments*/
  int my_errno=argHandler(argc,argv,&inputPath,&outputPath);
  if(USAGE_ERROR==my_errno){
      printf("usage:::: ./programA -i <<inputPathA>> -o <<outputPathA>> -t <<time>>\n");
      exit(EXIT_FAILURE);
  }else if(ARG_NOT_IN_RANGE_ERROR==my_errno){
      printf("time has to be range in 0-50\n");
      exit(EXIT_FAILURE);
  }else if(INVALID_PATH_ERROR==my_errno){
      printf("invalid path\n"); //
      exit(EXIT_FAILURE);
  }



        /**create temp file*/
        char tmp_path[15]="/tmp/XXXXXX";
        int temp_fd=mkstemp(tmp_path);
        printf("generate temp file %s",tmp_path);
        //write(temp_fd,"erkan",strlen("erkan"));





  /**fork and create other  process*/
int child_pid=fork();
if (0==child_pid){
//this is child proccess
//p2

printf("%s %d\n","this is child proccess pid is ",getpid() );











exit(EXIT_SUCCESS);
}else if (0>child_pid){
// error
perror("error while forking\n");
}else {/**parent process*/
  //p1
printf("%s %d\n","this is parant proccess pid is ",getpid() );

}







  printf("input path\t\t:::%s\noutputh path\t\t:::%s\n",inputPath,outputPath );



      /**do some stuf read write whatever*/

        /**opening the input file*/
        int input_fd=open(inputPath,O_RDWR|O_SYNC,0666);
        if(input_fd<0){
          perror("error while opening file");
          exit(-1);
        }

        printf("\n");

        /*declare what I use*/
        char buffer[21];
        char temp_print_srt[200];
        temp_print_srt[0]='\0';
        char temp_pair[20];
        temp_pair[0]='\0';
        struct pair pairs[10];
        char eq[15];


        /**init signal sets*/
        sigset_t sigusr2_wait,sigorig_wait_usr2;
        struct sigaction sa;

        sigemptyset(&sigusr2_wait);
        sigaddset(&sigusr2_wait, SIGUSR2);



        /**for sigaction*/
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = handler;





        /**read input file*/
        while(read(input_fd,buffer,20)==20){
          buffer[20]='\0';
          string_to_pairs(buffer,pairs);
          int i;
          for(i=0;i<10;++i){
              sprintf(temp_pair,"(%d,%d),",pairs[i].x,pairs[i].y);
              strcat(temp_print_srt,temp_pair);
          }
          printf("%s",temp_print_srt );

          /*write pairs*/
          write(temp_fd,temp_print_srt,strlen(temp_print_srt));
          temp_print_srt[0]='\0';


          sigset_t blocking_signals;
          sigemptyset(&blocking_signals);
          sigfillset(&blocking_signals);
          sigprocmask(SIG_BLOCK,&blocking_signals,NULL);

          /**critical section find eq*/
          pairs_to_line_eq(pairs,eq);

          sigprocmask(SIG_UNBLOCK,&blocking_signals,NULL);



          printf("%s\n",eq );

          /*write eq*/
          write(temp_fd,eq,strlen(eq));
          write(temp_fd,"\n",1);

          kill( child_pid,SIGUSR2);//I wrote signal

          /*blocking for wait**/
          if (sigprocmask(SIG_BLOCK, &sigusr2_wait, &sigorig_wait_usr2) == -1)
            perror("sigprocmask - SIG_BLOCK");


          if (sigaction(SIGUSR2, &sa, NULL) == -1)
            perror("sigaction");
          if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction");


            /*waiting*/
            printf("sigusr2 bekleniyor\n");
            if (sigsuspend(&sigorig_wait_usr2) == -1 && errno != EINTR)
              perror("sigsuspend");


            if (sigprocmask(SIG_SETMASK, &sigorig_wait_usr2, NULL) == -1)
              perror("sigprocmask - SIG_SETMASK");

            printf("%s\n","devamke" );


        }


        close(input_fd);
        /**bütün satırlar bitti p2 ye signyal yolla */








        /**temp file okudum */
        lseek(temp_fd,SEEK_SET,0);
        char buf;
        printf("okunan geçici dosya:\n");
        while(read(temp_fd,&buf,1)==1){
          printf("%c",buf);
        }
        printf("dosya bitti \n");

        /**unlink and close temp file*/
        unlink(tmp_path);
        close(temp_fd);


  free(inputPath);
  free(outputPath);
  return EXIT_SUCCESS;
}
