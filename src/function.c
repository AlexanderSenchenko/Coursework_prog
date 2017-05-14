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
int* compute_prefix_f(const char *p)
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

/*int compute_good_suffix(const char *p)
{
	int pi = compute_prefix_f(p);
	char *revert_p = revert(p);
	int pi_rev = compute_prefix_f(revert_p);
	m = strlen(path);
	int gp[m];
	for (int k = 0; k < m; k++) {
		gp[k] = m - pi[m];
	}
	for (int k = 0; k < m; k++) {
		j = m - k;
		k_rev = 1;
		while (k_rev <= m && pi_rev[k_rev] != j) {
			k_rev = k + 1;
		}
		if (pi_rev[k_rev] == j) {
			gp[k] = k_rev - m - k;
		}
	}
	return g
}*/

/*char *revert(const char *p)
{
	int len = strlen(p);
	char *rezert_p = malloc(sizeof(char) * len);
	for (int i = 0; i < len; i++) {
		revert_p[i] = p[len - i];
	}
	return revert_p;
}*/
