#include"arg.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<getopt.h>


int argHandler(int __argc,char ** __argv,char ** _inputPath, char ** _outputPath){
    int option;
    int iflag=0,oflag=0,tflag=0;
    int outputlen;
    int inputlen;

    while((option=getopt(__argc,__argv,"i: o: t:"))!=-1){
        switch (option)
        {
        case 'i':
            ++iflag;
            inputlen=strlen(optarg);
            if(NULL==(*_inputPath=malloc(sizeof(char)*inputlen))){
               perror("malloc");
            exit(-1);
            }
            strcpy(*_inputPath,optarg);
            //printf("i:::::%s\n",*_inputPath);
            break;
        case 'o':
            ++oflag;
            outputlen=strlen(optarg);
            if(NULL==(*_outputPath=malloc(sizeof(char)*outputlen))){
                perror("malloc");
                exit(-1);
            }
            strcpy(*_outputPath,optarg);
            //printf("i:::::%s\n",*_outputPath);
            break;

        case '?':
            break;
        default:

            break;
        }
    }
    if(iflag==0|oflag==0){
        return USAGE_ERROR;
    }






}
