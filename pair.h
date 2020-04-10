#ifndef PAIR__
#define PAIR__

struct pair{
  int x;
  int y;
};

void string_to_pairs(char *,struct pair *);
void unit_test_string_to_pair();

void pairs_to_line_eq(struct pair*,char *);
#endif
