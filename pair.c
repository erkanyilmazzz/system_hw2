#include"pair.h"
#include<stdio.h>
#include<string.h>

void string_to_pairs(char *b,struct pair *p){
  int size=strlen(b);
  //printf("\nsize:%d\n",size);
  int i;
  for(i=0;i<size;++i){
    if(i==0){
      p[i].x=b[i];
    }else {
      if(i%2==0){
        p[i/2].x=b[i];
      }else if(i%2==1){
        p[i/2].y=b[i];
      }
    }
  }

}

void unit_test_string_to_pair(){
  printf("test\n");
  char buffer[10]="0123456789";
  struct pair pairs[5];
  string_to_pairs(buffer,pairs);
  printf("buffer is %s\n",buffer );
  int i;
  for(i=0;i<strlen(buffer)/2;++i){
    printf("%d nin x i:%d y si %d\n",i,pairs[i].x,pairs[i].y);
  }

}


void pairs_to_line_eq(struct pair* p,char *eq){
  sprintf(eq,"%dx + %d",1,1);
}
