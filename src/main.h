#ifndef MAIN_H
#define MAIN_H

typedef struct {
	int line;
	int n_column;
	int *column;
} Results;

unsigned int hash_f(const char *word);
int search(const char *word, const char *text, int line, int all_search, const char *file);
void output_search(Results *res, const char *text, int n_word, const char *file);
Results *create_res(int n);
void free_res(Results *res);
int input(const char *file, const char *word);
char *create_new_path(const char *external_dir, const char *interior_dir);
int crawling_dir(const char *direct, const char *word, int all_search);

#endif
