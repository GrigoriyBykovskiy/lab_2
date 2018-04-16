#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "time.h"
#include "matrix.h"

void mx_free(TMatrix *m) {
	if (m != NULL)
		if (m->a != NULL) {
			free(m->a);
			free(m);
		}
}

void mx_print(TMatrix *m) {
	unsigned int i, j;

	if (m != NULL) {
		if (m->a != NULL) {
			for (i = 0; i < m->m; i++) {
				for (j = 0; j < m->n; j++)
					printf("%8.2lf", m->a[i * m->n + j]);
				printf("\n");
			}
		}
	}
}

TMatrix *mx_identity(unsigned int n) {
	unsigned int i, j;
	TMatrix *m = NULL;

	m = (TMatrix*)malloc(sizeof(TMatrix));
	if (m != NULL) {
		m->a = (double*)malloc(n * n * sizeof(double));
		if (m->a != NULL) {
			m->n = m->m = n;
			for (i = 0; i < m->m; i++)
				for (j = 0; j < m->n; j++)
					m->a[i * n + j] = i == j ? 1 : 0;
		}
		else {
			free(m);
			m = NULL;
		}
	}
	return m;
}
TMatrix *mx_custom_identify(unsigned int m, unsigned int n) {
	unsigned int i, j;
	TMatrix *t = NULL;
	t = (TMatrix*)malloc(sizeof(TMatrix));
	if (t != NULL) {
		t->a = (double*)malloc(m * n * sizeof(double));
		if (t->a != NULL) {
			t->m = m;
			t->n = n;
			srand(time(NULL));
				for (i = 0; i < t->m; i++)
					for (j = 0; j < t->n; j++)
						t->a[i * n + j] = rand() % 50 + 1;
		}
		else {
			free(t);
			t = NULL;
		}
	}
	return t;
}
TMatrix *mx_pow(TMatrix *m, double s) {
	if (m->m != m->n) {
		printf("************ERROR!************\n****Matrix must be square!****\n");
		return NULL;
	}
	if (s<2) {
		printf("***********ERROR!***********\n****Step is not correct!****\n");
		return NULL;
	}
	else {
		TMatrix *rez=NULL;
		TMatrix *copy=NULL;
		rez = (TMatrix*)malloc(sizeof(TMatrix));
		copy = (TMatrix*)malloc(sizeof(TMatrix));
		if ((rez != NULL) && (copy != NULL)) {
			rez->a = (double*)malloc((m->n) * (m->n) * sizeof(double));
			copy->a = (double*)malloc((m->n) * (m->n) * sizeof(double));
			if (((rez->a) != NULL) && ((copy->a) != NULL)) {
				copy->m = copy->n = m->n;
				rez->m = rez->n = m->n;
				for (int i = 0; i < m->n; i++) {
					for (int j = 0; j < m->n; j++) {
						(copy->a[i * (m->n) + j]) = (m->a[i * (m->n) + j]);
					}
				}
				for (int pow = 1; pow <= s; pow++) {
					for (int k = 0; k < (m->n); k++) {
						for (int i = 0; i < (m->n); i++) {
							double sum_of_elements = 0;
							for (int j = 0; j < (m->n); j++) {
								sum_of_elements += (copy->a[k*(copy->n) + j])*(m->a[j*(copy->n) + i]);
							}
							rez->a[k*(rez->n) + i] = sum_of_elements;
						}
					}
				}
			}
			free(copy);
			return rez;
		}
		else {
			free(rez);
			free(copy);
			printf("********ERROR!********\n******Low memory******\n");
			return NULL;
		}
	}
}