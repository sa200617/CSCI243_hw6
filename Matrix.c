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
	size_t rows; // number of rows in the matrix
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

Matrix mat_create(size_t rows , size_t cols){

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
	mat -> data = calloc (rows * cols, sizeof(float));
	// if the allocation of the matrix data fails will return null
	if (mat -> data == NULL){
		free(mat);
		return NULL;
	}

	// if we have a square matrix this function will return the identity matrix, square matrix are those whose cols and rows are the same
	if (rows == cols){
		// looping through the rows and cols to change what is inside the 1D array
		for (size_t row = 0; row < rows; row++){
			for (size_t col = 0; col < cols; col++){
				// if the row number is equal to the column num -> (2,2) or (1,1)
				if (row == col){
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

/**
 * mat_destroy(Matrix mat) ->  this function is responsible for freeing all memory assosiated with the
 * Matrix that was created using mat_create(). This function will not let the Matrix pointer to be used.

 * @param mat -> the matrix that should be destroyed.
 */

void mat_destroy(Matrix mat){
	if( !mat){ // if the mat is null and doesn't have anything you just return that
		return;
	}else{ // if the mat has data you first start by freeing the mat data and then you free the mat itself after
		free(mat-> data);
		free(mat);
	}
}

/**
 * mat_init(Matix mat, const float data[]) -> this function will fill the matrix with values from the flat
 * array of data[] pased into the function. Basically in charge of loading the matrix with decided values pased in.
 *
 * @param Matrix mat -> matrix that must filled and loaded up
 * @param const float data[] -> array with the data that must be filled into the matrix
 */
void mat_init(Matrix mat, const float data[]){

	if (mat == NULL || data == NULL){// checking if both the matix and the data is null then returning an empty
		return;
	}

	// looping through the rows and cols of the mat to acess the specific elements stored in the array
	for(size_t row = 0; row < mat->rows; row++){
		for(size_t col = 0; col < mat->cols; col++){
			size_t index = row * mat->cols + col;
			mat->data[index] = data[index];// updating the mat with the data at the same index by setting both mat index equal to the element stored in that index for data
		}
	}
}


