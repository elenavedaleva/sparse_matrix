/**
 * Sparse Matrix Library
 * 
 * @file: sparse.c
 * @author: Elena Vedaleva
 * @date: September, 2023
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sparse.h"

void read_input(int *m, int  *n, int *num);
void fill_elements(struct Element *e, int num);
struct Sparse *calloc_sparse(struct Sparse *s1, struct Sparse *s2);


/**
 * Creates Sparse Matrix object
 * by prompting user to provide 
 * dimentions and # of elements to store.
 * 
 * @param: pointer to Sparse object
 * @return: void
*/
void Create(struct Sparse *s) {
    read_input(&s->m, &s->n, &s->num);
    assert(s->m > 0 && s->n > 0 && s->num > 0);

    s->e = (struct Element *)calloc(s->num, sizeof(struct Element));
    if (s->e == NULL) {
        printf("Error: Memory not allocated\n");
        abort();
    }
    fill_elements(s->e, s->num);
}

/**
 * Displays the original Sparse Matrix
 * by retriving all non zero elements
 * and filling the rest with zeros
 * 
 * @param: pointer to Sparse object
 * @return: void
*/
void Display(struct Sparse *s) {
    int k = 0;
    printf("\n");
    for (int i = 1; i <= s->m; i++) {
        for (int j = 1; j <= s->n; j++) {
            if (i == s->e[k].i && j == s->e[k].j) {
                printf("%d ", s->e[k].x);
                k++;
            } else printf("%c ", '0');
        }
        printf("\n");
    }
}

/**
 * Adds two Sparse matrixes 
 * with the same dimentions together.
 * 
 * @param: pointer to a first Sparse object
 * @param: pointer to a second Sparse object
 * @return: pointer to a resulted object 
*/
struct Sparse *Add(struct Sparse *s1, struct Sparse *s2) {
    struct Sparse *sum;
    int k = 0, l = 0, p = 0;
    if (s1->m != s2->m && s1->n != s2->n) {
        printf("Error: Invalid dimentions\n");
        abort();
    }

    sum = calloc_sparse(s1, s2);
    while (l < s1->num && p < s2->num) {
        if (s1->e[l].i < s2->e[p].i) {
            sum->e[k++] = s1->e[l++];
        } else if (s1->e[l].i > s2->e[p].i) {
            sum->e[k++] = s2->e[p++];
        } else {
            if (s1->e[l].j < s2->e[p].j) {
                sum->e[k++] = s1->e[l++];
            } else {
                sum->e[k++] = s2->e[p++];
            }
        }
    }
    while (l < s1->num) {
        sum->e[k++] = s1->e[l++];         
    }
    while (p < s2->num) {
        sum->e[k++] = s2->e[p++];         
    }
    return sum;
}

struct Sparse *calloc_sparse(struct Sparse *s1, struct Sparse *s2) {
    struct Sparse *sum;
    sum = (struct Sparse *)calloc(1, sizeof(struct Sparse));
    if (sum == NULL) {
        printf("Error: Memory not allocated\n");
        abort();
    }
    sum->m = s1->m;
    sum->n = s1->n;
    sum->num = s1->num + s2->num;
    sum->e = (struct Element *)calloc(sum->num, sizeof(struct Element));
    if (sum->e == NULL) {
        printf("Error: Memory not allocated\n");
        abort();
    }
    return sum;
}

void read_input(int *m, int  *n, int *num) {
    int num_items;

    printf("Enter dimentions: ");
    num_items = scanf("%d%d", m, n);
    if (num_items != 2 || *m <= 0 || *n <= 0) {
        printf("Error: Invalid input\n");
        abort();
    }

    printf("Enter # of non zero elements: ");
    num_items = scanf("%d", num);
    if (num_items != 1 || *num <= 0) {
        printf("Error: Invalid input\n");
        abort();
    }
}

void fill_elements(struct Element *e, int num) {
    int num_items;
    printf("Enter all elements:\n");
    for (int i = 0; i < num; i++) {
        num_items = scanf("%d%d%d", &e[i].i, &e[i].j, &e[i].x);
        if (num_items != 3) {
            printf("Error: Invalid input");
            abort();
        }
    }
}

