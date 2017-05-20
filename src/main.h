#ifndef MAIN_H
#define MAIN_H

unsigned int hash_f(const char *word);
void search(const char *word, const char *text);
void input(const char *file, const char *word);
int crawling_dir(const char *direct, const char *word);

/*int *compute_prefix_f(const char *p);
int *compute_good_suffix(const char *p);
char *revert(const char *p);
*/

#endif
