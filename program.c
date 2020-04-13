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


void handler(int sig){
  //printf("%s\n","I am in handler");
}


int main(int argc , char ** argv){

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

  //unit_test_formated_sitring_to_pair();

      /**create temp file*/
      char tmp_path[15]="/tmp/XXXXXX";
      int temp_fd=mkstemp(tmp_path);
      printf("generate temp file %s",tmp_path);



    printf("\n\n\ninput path\t\t:::%s\noutputh path\t\t:::%s\n",inputPath,outputPath );

    int child_pid=fork();
    if(child_pid==0){
      double MAE=0,MSE=0,RMSE=0;

      printf("\nchild waiting \n");

      sigset_t block,past;
      sigfillset(&block);
      signal(2,handler);
      sigprocmask(SIG_BLOCK,&block,&past);
      sigsuspend(&past);
      sigprocmask(SIG_UNBLOCK,&block,&past);
      printf("devamke ");


      /*dosya sizesı*/
      lseek(temp_fd,SEEK_SET,0);
      int size=0;
      char buf;
      while(read(temp_fd,&buf,1)==1){
        ++size;
      }

      //reading temp file
      lseek(temp_fd,SEEK_SET,0);

      printf("okunan geçici dosya:\n");
      int i=0;
      char *file=malloc(sizeof(char)*size);
      while(read(temp_fd,&buf,1)==1){
        file[i]=buf;
        ++i;
      }
      file[i-1]='\0';

printf("%s\n",file);
printf("%s\n","file basıldı" );
  struct pair pairs[10];
  int a,b;
printf("%s\n","pair oluşturuldu" );

   formated_string_to_pairs(file,pairs,&a,&b);
   print_pairs(pairs);
   printf("%dx+%d\n",a,b );

  i =0;
  int j;
  int last_newline=0;
  char str[500];
  str[0]='\0';
  while(file[i]!='\0'){
    if(file[i]=='\n'){

      printf("\n%s i=%d last_newline=%d\n","ueni stır",i,last_newline );
      //printf("\nyeni satır:::::");
      for (size_t j = 0; j < i-last_newline; j++) {
        str[j]=file[i+1+j];
        //printf("%c",str[j]);
      }
      //printf("yeni satır:::%s\n",str );
      formated_string_to_pairs(str,pairs,&a,&b);
      print_pairs(pairs);
      printf("%dx+%d\n",a,b );
      //double MAE=0,MSE=0,RMSE=0;

      MAE=get_MAE(pairs,a,b);
      MSE=get_MSE(pairs,a,b);
      RMSE=get_RMSE(pairs,a,b);

      printf("mae %lf mse%lf rmse%lf\n",MAE,MSE,RMSE);





      last_newline=i;
    }
    ++i;
  }


    printf("burdayım\n");


      printf("dosya bitti \n");


      free(file);

    exit(0);
    }



printf("\nburaya girdi 1\n");






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


printf("\nburaya girdi 2\n");
  /**init signal sets*/
  sigset_t SIGINT_wait,sigorig_wait_usr2;//SIGINT değişecek
  struct sigaction sa;

  sigemptyset(&SIGINT_wait);//burda da
  sigaddset(&SIGINT_wait, SIGINT);//burda da

  /**for sigaction*/
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = handler;



printf("\nburaya girdi 3\n");

  /**read input file*/
  while(read(input_fd,buffer,20)==20){
    buffer[20]='\0';
    string_to_pairs(buffer,pairs);
    int i;
    for(i=0;i<10;++i){
      sprintf(temp_pair,"(%d,%d),",pairs[i].x,pairs[i].y);
      strcat(temp_print_srt,temp_pair);
    }
    //printf("%s",temp_print_srt );

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



    //printf("%s\n",eq );

    /*write eq*/
    write(temp_fd,eq,strlen(eq));
    write(temp_fd,"\n",1);


  }

printf("\nburaya girdi 4\n");
printf("--%d-- \n",kill(child_pid,2) );




    close(input_fd);


    /**temp file okudum */
    /**unlink and close temp file*/
    unlink(tmp_path);
    close(temp_fd);

    free(inputPath);
    free(outputPath);

    wait(NULL);
    return EXIT_SUCCESS;
}
