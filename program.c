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


void critical(){
  int i=0;
  for(i=0;i<0;++i){
    printf("%d\n",i);
    sleep(1);
  }
}

int main(int argc , char ** argv){
  //unit_test_string_to_pair();

  char *inputPath;
  char *outputPath;

  /*checking and setting arguments*/
  int errno=argHandler(argc,argv,&inputPath,&outputPath);
  if(USAGE_ERROR==errno){
      printf("usage:::: ./programA -i <<inputPathA>> -o <<outputPathA>> -t <<time>>\n");
      exit(EXIT_FAILURE);
  }else if(ARG_NOT_IN_RANGE_ERROR==errno){
      printf("time has to be range in 0-50\n");
      exit(EXIT_FAILURE);
  }else if(INVALID_PATH_ERROR==errno){
      printf("invalid path\n"); //
      exit(EXIT_FAILURE);
  }


  printf("input path\t\t:::%s\noutputh path\t\t:::%s\n",inputPath,outputPath );


      /**create temp file*/
      char tmp_path[15]="/tmp/XXXXXX";
      int temp_fd=mkstemp(tmp_path);
      printf("generate temp file %s",tmp_path);
      write(temp_fd,"erkan",strlen("erkan"));



      /**do some stuf read write whatever*/

        /**opening the input file*/
        int input_fd=open(inputPath,O_RDWR|O_SYNC,0666);
        if(input_fd<0){
          perror("error while opening file");
          exit(-1);
        }

        printf("\n");

        char buffer[21];
        struct pair pairs[10];
        char eq[15];
        while(read(input_fd,buffer,20)==20){
          buffer[20]='\0';
          string_to_pairs(buffer,pairs);
          int i;
          for(i=0;i<10;++i){
              printf("%d nin x i:%d y si %d\n",i,pairs[i].x,pairs[i].y);
          }
          pairs_to_line_eq(pairs,eq);
          printf("qeuation is %s\n",eq );


        }


        close(input_fd);
      /**calculation step it is critacal */
      sigset_t blocking_signals;
      sigemptyset(&blocking_signals);
      sigfillset(&blocking_signals);
      sigprocmask(SIG_BLOCK,&blocking_signals,NULL);

      critical();

      sigprocmask(SIG_UNBLOCK,&blocking_signals,NULL);


      /*create temprorary file */



      /**fork and create other  process*/
  int child_pid=fork();
  if (0==child_pid){
    //this is child proccess
    printf("%s %d\n","this is child proccess pid is ",getpid() );







    exit(EXIT_SUCCESS);
  }else if (0>child_pid){
    // error
    perror("error while forking\n");
  }else {/**parent process*/
    int buffer;
    wait(&buffer);
    printf("%s %d\n","this is parant proccess pid is ",getpid() );

  }


        lseek(temp_fd,SEEK_SET,0);


        char buf[15];
        read(temp_fd,&buf,6);
        printf("\nyazılan mesaj %s\n",buf );
        /**unlink and close temp file*/
        unlink(tmp_path);
        close(temp_fd);


  free(inputPath);
  free(outputPath);
  return EXIT_SUCCESS;
}
