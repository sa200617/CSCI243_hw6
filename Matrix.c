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
};



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


/**
 * mat_duplicate( const Matrix mat ) -> this function will clone the matrix that was pased making a new copy.
 *
 * @param mat -> the matrix that we have to duplicate
 * @return matrix pointer to the new matrix created
 */
Matrix mat_duplicate(const Matrix mat){
	if (mat == NULL){ //if the matrix is empty or null you will just return NULL for the copy
		return NULL;
	}

	else{
		Matrix newCopy = mat_create(mat->rows, mat->cols);//creating the newCopy matrix which is passed in with the rows and cols of the orginal matrix
		if (newCopy == NULL){// if the copy ends up being empty you will just return null
			return NULL;
		}
		else{
			//looping through the rows and cols in order to set all of indexs in the newCopy to the corresponding index in the orginal matrix
			for(size_t row = 0; row < mat->rows; row++){
				for(size_t col = 0; col < mat->cols; col++){
					size_t index = row * mat->cols + col;
					newCopy->data[index] = mat->data[index];
				}
			}
		}
		 return newCopy; // returing the copied matrix that we made
	}
}

/**
 * mat_equals(m1,m2) -> this function will check is two matrices that are passed in are equal to one another,
 * by checking if the sizes of the matrices are the same, and then checking if every index of the data of both
 * are equal to each other.
 *
 * @param const Matrix m1 -> the first matrix passed to check
 * @param const Matrix m2 -> the second matrix to check to compare to first
 * @return bool true/false -> representing if both matrixs are equal or not
 */
bool mat_equals(const Matrix m1, const Matrix m2){
	if (m1 == NULL || m2 == NULL){ // if both the matrix are null return false
		return false;
	}

	if ( m1->rows != m2->rows || m1->cols != m2->cols){ // if the cols and rows of both the matrix's don't match return false
		return false;
	}

	// looping through the rows and cols of m1 in order to acess the elements of that array
	for (size_t row = 0; row < m1->rows; row++){
		for(size_t col = 0; col < m1->cols; col++){
			size_t index = row * m1->cols + col;
			if (m1->data[index] != m2->data[index]){ // if any of the index's of m1 and m2 are not equal to each other return false
				return false;
			}
		}
	}
	return true; // both matrices are equal returning true
}
/**
 * mat_scalar_mult(Matrix mat, float data) -> this function will perform the scalor multiplication of all of the elements of
 * mat with the value for float data that is pased inside the function. It will mutuate and change each value by a const.
 *
 * @param Matrix mat -> this is the matrix that will be multiplied
 * @param float data -> this is the const that you are going to multiply with.
 */
void mat_scalar_mult( Matrix mat, float data ){
	// if the matrix we passed in is null we have nothing to do so just return
	if (mat ==  NULL){
		return;
	}

	else{
		//looping through the rows and cols of the mat
		for(size_t row = 0; row < mat->rows; row++){
			for(size_t col =0; col < mat->cols;col++){
				size_t index = row * mat-> cols + col;// this fun is going to the correct index in the array
				float oldVal = mat->data[index];// here we are storing the old value
				float newVal = oldVal * data; // here we are storing the new value updated after multiplied by the scalor
				mat->data[index] = newVal; // now we are updating the value in the mat with the new value calculated
			}
		}
	}
}
/**
 * mat_mult(const Matrix m1, const Matrix m2) -> takes two matrices and performs matrix multiplication with
 * ,the requriement for matrix multiplication is that the number of cols in m1 must be equal to the rows in
 * m2. If that condition is met true the matrix multuplication is newMatrix[row][col] = sum(m1[row][c] * m2[c]
 * [col]).
 *
 * @param m1 -> one the matrix being multiplied
 * @param m2 -> the other matrix multiplied
 * @return newMatrix -> this is a new matrix that has the m1*m2 matrix, returning NULL if the intial condition
 * to perform matrix multiplication is not passed/
 */
Matrix mat_mult( const Matrix m1, const Matrix m2 ){
	if (m1==NULL || m2 == NULL){ // if both of matrixes are NULL return NULL
		return NULL;
	}

	if(m1->cols != m2->rows ){ // if the cols of M1 is not equal to the rows of M2 return NULL
		return NULL;
	}

	Matrix newMatrix = mat_create(m1->rows, m2-> cols);// creating a brand new matrix to hold the multiplication
	if (newMatrix == NULL){
		return NULL;
	}
	else{
		// looping through the rows and colums of the new matrix to update and add values
		for(size_t row = 0; row < m1->rows; row++){
			for (size_t col = 0; col < m2->cols; col++){
				float total = 0.0f;// creating acculator to store total
				for(size_t c =0; c < m1->cols; c++){//computing the dot product from m1 and the column from m2 

					int indexM1 = row *m1->cols + c;//index value of m1
					float valM1 = m1->data[indexM1];// value of m2

					int indexM2 = c *  m2->cols + col;//index value of m2
					float valM2 = m2->data[indexM2]; // value of m2

					total += valM1 * valM2;// adding the product of those values into the accumelator total
				}
			newMatrix->data[row * newMatrix->cols + col] = total;// storing that total value into the matrix
			}
		}
	}
	return newMatrix;// returning the product matrix that we made
}

/**
 * mat_get_cell -> returns the contents of the cell that is at the specific row and column of the mat that is passed in
 *
 * @param mat -> this the matrix you are reading from in order to get data.
 * @param float *data -> pointer to a float where we will store the cells infomation
 * @param row -> this is the index of the row you want to get
 * @param col -> this is the desired col index
 *
 * @return Status -> returns a static code checking if value was receieved or not received correctly. The status
 * will fail if the matrix is NULL, data pointer is NULL, or the matrix values are out of range.
 *
 */
Status mat_get_cell( const Matrix mat, float *data, size_t row, size_t col ){

	// this will return failure if the mat is NULL or if the data is null
	if(mat == NULL || data == NULL){
		return FAILURE;
	}
	// this will return FAILURE, if the cols and rows that are passed into the function are our of bounds
	if ( row >= mat->rows || col >= mat->cols){
		return FAILURE;
	}
	size_t index = row * mat->cols + col;// computing the index
	*data = mat->data[index];// storing the mat data value to the pointer
	return SUCCESS;// returning sucess
}
/**
 * mat_get_row -> returns the contents and all the values from a matrix at its specified row.
 *
 * @param mat -> the matrix where it reads data from
 * @param data -> this is the array that will store the values of the row
 * @param row -> the index of the row to receieve information from
 *
 * @return -> this function will return a status code
 *     Sucess will tell us that the row was sucessfully retrived
 *     Failure if the matrix is null or row out of range
 */
Status mat_get_row( const Matrix mat, float data[], size_t row){

	// here basically saying that if the data and mat are NULL return FAILURE
	if (mat == NULL || data ==  NULL){
		return FAILURE;
	}
	// if the row is out of the valid index set you would return failurre
	if (row >=  mat->rows){
		return FAILURE;
	}
	else{
		//here you are looping through the cols of the mat pased in
		for(size_t col = 0; col < mat->cols; col++){
			size_t index =  row * mat->cols + col; // calculating the index from which to get the data from
			data[col] = mat->data[index]; // storing inside the data[] array the value receieved from mat with the index
		}
	}
	return SUCCESS;
}
/**
 * mat_set_cell -> this function is responsible for assigning a specific value in the matrix given a
 * specific cell and a float data num to change it to.
 *
 * @param mat -> the matrix passed in that you want to update
 * @param data -> the value you are going to assign that specific cell
 * @param row -> the row index of the element that you want to update.
 * @param col -> the column index of the element that you want to update
 *
 * @return -> Status code if the element was updated or not
 *     Success if the matrix cell was successfully updated.
 *     Failure if the matrix is null or if the cell pased in is out of bounds in the matrix
 */
Status mat_set_cell( Matrix mat, float data, size_t row, size_t col ){

	// this is checking if the mat is NULL and then returning FAILURE
	if (mat == NULL){
		return FAILURE;
	}
	// this checking if the mat cell that is passed in is out of bounds then returning FAILURE.
	if (row >=  mat->rows || col >=  mat->cols){
		return FAILURE;
	}
	else{
		size_t index = row * mat->cols + col; // accessing the index of the mat with the rows and col passed in
		mat->data[index] = data;// going into the mat and updating it with the value passed in by the func
		return SUCCESS; // returning success
	}
}
/**
 * mat_set_row -> this function is responsible for assigning an entire row in a matrix from an array.
 *
 * @param mat -> this is the matrix we need to modify
 * @param data -> array with the values that you have to assign to the specific row.
 * @param row -> the row that you have to modify
 *
 * @return Status of the opperation ->
 *        Success if the whole row was updated
 *        Failure if the row failed to update bc the matrix or data was null or the row was out of bound.
 */
Status mat_set_row( Matrix mat, const float data[], size_t row ){

	// Return failure if the data or the matrix is NULL.
	if (mat == NULL || data == NULL){
		return FAILURE;
	}
	// Return Failure if the row pased in is out of bounds
	if (row >= mat->rows){
		return FAILURE;
	}
	else{
		// looping through the cols of the matrix
		for(size_t col = 0; col < mat->cols; col++){
			size_t index = row * mat->cols + col;// finding out the index we are at
			mat->data[index] = data[col]; // updating that matrix index with the data index
		}
		return SUCCESS; // return SUCCESS
	}
}
/**
 * mat_transpose -> this creates and returns the transpose of a matrix that is passed through the function.
 * the transpose is basically created by swapping a matrixs rows and columns. Basically flipping the matrix
 * on its main  diagonol. Think about it that instead of (row,col) you have (col, row)
 *
 * @param mat -> this is the matrix that has to be transposed.
 * @return trans which is the transposed matrix that this function works on computing.
 */
Matrix mat_transpose( const Matrix mat ){

	//if we pass through a NULL matrix it will return NULL
	if (mat == NULL){
		return NULL;
	}

	// this is creating an empty trans (which is the transpose matrix). Flipping the rows and cols.
	Matrix trans = mat_create(mat->cols, mat->rows);
	if (trans == NULL){
		return NULL;
	}
	// looping through the rows and cols of the orginal matrix
	for (size_t row = 0; row < mat->rows; row++){
		for(size_t col = 0; col < mat->cols; col++){
			size_t index  = row * mat->cols + col;// storing the index of the orginal matrix
			size_t transI = col * trans->cols + row;// storing the index of the transpose matrix
			trans->data[transI] = mat->data[index];// this will basically do the switching and adding to the transpose
		}
	}
	return trans;// returning the trans
}
/**
 * mat_print -> this function is reponsible for printing out the matrix
 * in to the steam, using the matrix that is provided. Prints the row and
 * col numbers and then the matrix cell by cell.
 *
 * @param Matrix mat -> matrix passed in that is printed.
 * @param FILE stream -> pointer to the file stream
 */
void mat_print( const Matrix mat, FILE *stream){

	// if the mat is NULL it will print an error in the stream
	if (mat == NULL || stream == NULL){
		fprintf(stderr ,"Error: matrix is NULL\n");
		return;
	}
	else{
		// printing out the rows by cols at the top of the matrix
		fprintf(stream, "%zu rows. %zu columns:\n", mat-> rows, mat->cols);
		for (size_t row = 0; row < mat->rows; row++){
			for(size_t col = 0; col < mat->cols; col++){
				size_t index = row * mat->cols + col;// getting the index of one cell
				fprintf(stream, "%8.3f", mat->data[index]);// printing the cell
			}
			fprintf(stream ,"\n");
		}
	}
}
