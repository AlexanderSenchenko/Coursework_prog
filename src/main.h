#ifndef MAIN_H
#define MAIN_H

unsigned int hash_f(const char *word);
void search(const char *word, const char *text);
void input(const char *file, const char *word);
char *create_new_path(const char *external_dir, const char *interior_dir);
int crawling_dir(const char *direct, const char *word);

#endif
