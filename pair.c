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


void formated_string_to_pairs(char * str ,struct pair *pairs,int *a,int *b){

    sscanf(str,"(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),(%d,%d),%dx + %d\n",
      &(pairs[0].x),&(pairs[0].y),
      &(pairs[1].x),&(pairs[1].y),
      &(pairs[2].x),&(pairs[2].y),
      &(pairs[3].x),&(pairs[3].y),
      &(pairs[4].x),&(pairs[4].y),
      &(pairs[5].x),&(pairs[5].y),
      &(pairs[6].x),&(pairs[6].y),
      &(pairs[7].x),&(pairs[7].y),
      &(pairs[8].x),&(pairs[8].y),
      &(pairs[9].x),&(pairs[9].y),
      a,b
    );
}
void unit_test_formated_sitring_to_pair(){
/*

printf("I am in unit_test_formated_sitring_to_pair\n");
char str[500]="(49,50),(51,52),(53,54),(55,56),(57,57),(56,55),(54,53),(52,51),(50,49),(49,50),1x + 1(51,52),(53,54),(55,56),(57,57),(56,55),(52,53),(54,51),(50,49),(49,50),(51,52),1x + 1";
  //88
  struct pair pairs[10];
  formated_string_to_pairs(str,&pairs[2]);
  int j;
  for (j = 0; j < 10; j++) {
    printf("x=%d,y=%d\n",pairs[j].x,pairs[j].y );
  }

**/
}

void print_pairs(struct pair* pairs){
  for (size_t i = 0; i < 10; i++) {
    printf("x:%d y:%d\n",pairs[i].x,pairs[i].y);
  }
}


double get_MAE(struct pair *pairs,double a ,double b){
  return 10;
}

double get_MSE(struct pair *pairs,double a ,double b){
  return 10;
}

double get_RMSE(struct pair *pairs,double a ,double b){
  return 10;
}
