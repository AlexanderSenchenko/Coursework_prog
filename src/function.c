#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>

char *input()
{
	char *path = malloc(sizeof(char) * 20);
	if (path == NULL) {
		return NULL;
	}
	fgets(path, 20, stdin);
	return path;
}

unsigned int hash_f(const char *word)
{
	unsigned int h = 0;
	int n = strlen(word), m = n , d = 7;
	for (int i = 0; i < n; i++, m--) {
		if (word[i] == '\n') {
			continue;
		}
		h += word[i] * pow(d, m);
	}
	return h;
}

void search(const char *word, const char *text)
{
	int n_text = strlen(text) - 1, buf_hash = 0;
	int n_word = strlen(word), h_word;
	char *cpy = malloc(sizeof(char) * n_word), buf[1];

	strncpy(cpy, text, n_text);
	h_word = hash_f(word);
	//printf("%d\n", h_word);

	for (int i = 0; i < n_text - n_word; i++) {
		buf[0] = cpy[i + n_word];
		cpy[i + n_word] = '\0';
		buf_hash = hash_f(&cpy[i]);

		if (buf_hash == h_word) {
			if (strcmp(word, &cpy[i]) == 0) {
				printf("%d\n", i);
			}
		}

		cpy[i + n_word] = buf[0];
	}
	//free(cpy);
}

int crawling_dir()
{
	struct stat buf;
	DIR *dir = opendir("search");
	if (dir == NULL) {
		return 0;
	}

	stat("search", &buf);
	printf("Size of the file is: %ld\n", buf.st_size);

	closedir(dir);

	return 0;
}

/*int *compute_prefix_f(const char *p)
{
	int m = strlen(p) - 1, k = 0, *pi;
	pi = malloc(sizeof(int) * m);
	if (pi == NULL) {
		return NULL;
	}
	pi[0] = 0;
	for (int q = 1; q < m; q++) {
		while (k > 0 && p[k] != p[q]) {
			k = pi[k];
		}
		if (p[k] == p[q]) {
			k++;
		}
		pi[q] = k;
	}
	return pi;
}

char *revert(const char *p)
{
	int len = strlen(p) - 1;
	char *p_rev = malloc(sizeof(char) * len + 1);
	for (int i = 0; i < len; i++) {
		p_rev[i] = p[len - i - 1];
	}
	p_rev[len] = '\n';
	return p_rev;
}

int *compute_good_suffix(const char *p)
{
	int *pi, *pi_rev, *arr_suf, j, k_rev, len;
	char *p_rev;

	pi = compute_prefix_f(p);
	for (int i = 0; i < strlen(p) - 1; i++) {
		printf("%d ", pi[i]);
	}
	printf("\n");

	p_rev = revert(p);
	printf("%s", p_rev);

	pi_rev = compute_prefix_f(p_rev);
	for (int i = 0; i < strlen(p) - 1; i++) {
		printf("%d ", pi_rev[i]);
	}
	printf("\n");

	len = strlen(p) - 1;
	printf("%d\n", len);

	arr_suf = malloc(sizeof(int) * len);

	for (int k = 0; k < len; k++) {
		arr_suf[k] = len - pi[len - 1];
	}
	for (int k = 0; k < len; k++) {
		j = len - k - 1;
		k_rev = 0;
		while (k_rev < len && pi_rev[k_rev] != j) {
			k_rev++;
		}
		if (pi_rev[k_rev] == j) {
			arr_suf[k] = k_rev - (len - k - 1);
		}
	}
	return arr_suf;
}*/
