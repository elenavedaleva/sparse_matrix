/**
 * Sparse Matrix Library
 * 
 * @file: sparse.h
 * @author: Elena Vedaleva
 * @date: September, 2023
 * 
*/

/**
 * Defines an element of 
 * a matrix
*/

struct Element {
    int i;  /** row number */
    int j;  /** column number */
    int x;  /** value */
};

/**
 * Defines m x n matrix   
*/
struct Sparse {
    int m;  /** number of rows */ 
    int n;  /** number of columns */
    int num;  /** number of non zero elements */ 
    struct Element *e;  /** array of elements */ 
};

void Create(struct Sparse *s);
void Display(struct Sparse *s); 
struct Sparse *Add(struct Sparse *s1, struct Sparse *s2);
