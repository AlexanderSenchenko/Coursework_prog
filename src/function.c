#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *input()
{
	char *path = malloc(sizeof(char) * 20);
	if (path == NULL) {
		return NULL;
	}
	fgets(path, 20, stdin);
	return path;
}

//wtf? почему не работает, если это дано как теория для курсовой
//найс ошибки в примере + я даун
int *compute_prefix_f(const char *p)
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
	char *p_rev = malloc(sizeof(char) * len);
	for (int i = 0; i < len; i++) {
		p_rev[i] = p[len - i - 1];
	}
	p_rev[len + 1] = '\n';
	return p_rev;
}

int *compute_good_suffix(const char *p)
{
	int *pi, *pi_rev, *arr_suf, j, k_rev, len;
	char *p_rev;

	pi = compute_prefix_f(p);
	p_rev = revert(p);
	pi_rev = compute_prefix_f(p_rev);
	len = strlen(p) - 1;
	arr_suf = malloc(sizeof(int) * len);

	for (int k = 0; k < len; k++) {
		arr_suf[k] = len - pi[k];
	}
	for (int k = 0; k < len; k++) {
		j = len - k;
		k_rev = 1;
		while (k_rev <= len && pi_rev[k_rev] != j) {
			k_rev++;
		}
		if (pi_rev[k_rev] == j) {
			arr_suf[k] = k_rev - len - k;
		}
	}
	return arr_suf;
}
