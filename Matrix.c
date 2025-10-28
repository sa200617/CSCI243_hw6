#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Matrix.h"

/**
 * struct matrix_st -> this a struct representing the matrix with
 * rows and columns that store the float data.
 */
struct matrix_st{
	size_t row; // number of rows in the matrix
	size_t cols;// number of columns in the matrix
	float *data; // pointer to the dynamically stored data
}

/**
 * mat_create(row,col) -> this function creates a new matrix, given
 * the rows and columns. If the matrix is a square it is intialized as
 * an identity matrix, but if not it is initialized as a zero matrix.
 *
 * @ param size_t rows -> number of rows
 * @ param size_t_cols -> number of columns
 * @ return pointer to new matrix
 */

Matrix mat_create(size_t row, size_t cols){

	Matrix mat;// declaring the pointer that is storing the matrix
	size_t sizeStruct = sizeof(struct matrix_st); // this is calculating the size of the struct
	mat= malloc(sizeStruct); // this is allocating the intial memory for the struct
	// if the memory allocation for the struct failed return null
	if (mat == NULL){
		return NULL;
	}

	// this stores the row and col in the struct
	mat -> rows = rows;
	mat -> cols = cols;

	// this allocates the memory for the data araray
	mat -> data = calloc (row * col, sizeof(float));
	// if the allocation of the matrix data fails will return null
	if (mat -> data = NULL){
		free(mat);
		return NULL;
	}

	// if we have a square matrix this function will return the identity matrix, square matrix are those whose cols and rows are the same
	if (rows = cols){
		// looping through the rows and cols to change what is inside the 1D array
		for (size_t row = 0; row < rows; row++){
			for (size_t col = 0; col < cols; col++){
				// if the row number is equal to the column num -> (2,2) or (1,1)
				if (row = col){
					// going to that place in the 1D array and setting that to one
					mat->data[row*cols + col] = 1.0;
				//then the rest of the data will be set to 0
				} else{
					mat->data[ row * cols + col] = 0.0;
				}
			}
		}
	}
	// if we have a nonsquare matrix we are suppose to return the 0 matrix of that size
	else{
		for (size_t row = 0; row < rows; row++){
			for (size_t col = 0; col < cols; col++){
				mat->data[row *cols + col] = 0.0;// this is basically setting every position in that matrix to 0.
			}
		}
	}
	return mat;// returning the pointer to the new matrix
}

