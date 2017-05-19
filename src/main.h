#ifndef MAIN_H
#define MAIN_H

char *input();

unsigned int hash_f(const char *word);
void search(const char *word, const char *text);

/*int *compute_prefix_f(const char *p);
int *compute_good_suffix(const char *p);
char *revert(const char *p);
*/

#endif
