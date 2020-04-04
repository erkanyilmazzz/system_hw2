#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include"arg.h"


int main(int argc , char ** argv){

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

  int child_pid=fork();
  if (0==child_pid){
    //this is child proccess
    printf("%s %d\n","this is child proccess pid is ",getpid() );



    exit(EXIT_SUCCESS);
  }else if (0>child_pid){
    // error
    perror("error while forking\n");
  }else {
    printf("%s %d\n","this is parant proccess pid is ",getpid() );
  }


  free(inputPath);
  free(outputPath);
  return EXIT_SUCCESS;
}
