#ifndef PAIR__
#define PAIR__

struct pair{
  int x;
  int y;
};

void string_to_pairs(char *,struct pair *);
void unit_test_string_to_pair();

void formated_string_to_pairs(char * str ,struct pair *pairs,int *a,int *b);
void unit_test_formated_sitring_to_pair();

/**it hast to be in critical section*/
void pairs_to_line_eq(struct pair*,char *);


void print_pairs(struct pair* pairs);






double get_MAE(struct pair *pairs,double a ,double b);
double get_MSE(struct pair *pairs,double a ,double b);
double get_RMSE(struct pair *pairs,double a ,double b);
#endif
