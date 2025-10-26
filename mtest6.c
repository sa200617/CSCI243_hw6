//
// Simple test of the Matrix ADT
//
// tests mat_init(), mat_set_row(), mat_get_row()
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Matrix.h"

///
// support function - convert Status value to string
///

const char *code( Status n ) {

    switch( n ) {

        case Success:
	    return( "Success" );

	case BadRowNumber:
	    return( "BadRowNumber" );

	case BadColNumber:
	    return( "BadColNumber" );

	default:
	    break;
    }

    return( "???" );
}

///
// support function:  set a row, then test it
///

void set_and_test_row( Matrix mat, size_t row, size_t cols, const float data[] ) {
    Status status;

    // first, try to set the row
    status = mat_set_row( mat, data, row );

    if( status != Success ) {

        fprintf( stderr, "SetRow(%lu) error: code %d, '%s'\n",
	         row, status, code(status) );

    } else {

	// next, retrieve the row
	float *data2 = (float *) calloc( cols, sizeof(float) );
	if( data2 == NULL ) {
	    fputs( "ERROR - can't allocate data space\n", stderr );
	    return;
	}

	status = mat_get_row( mat, data2, row );
	if( status != Success ) {

	    fprintf( stderr, "GetRow(%lu) error: code %d, '%s'\n",
	             row, status, code(status) );

	} else {

	    // now, verify that all the values in the retrieved
	    // row match the values given to use by the caller
	    int err = 0;
	    for( size_t i = 0; i < cols; ++i ) {
		if( data2[i] != data[i] ) {
		    ++err;
		    if( err == 1 ) {
	                fprintf( stderr, "Set/Get(%lu): ", row );
		    }
		    fprintf( stderr, "\n  (%lu,%lu) set %8.3f, got %8.3f\n",
		             row, i, data[i], data2[i] );
		}
	    }
	    if( err ) {
	        fputc( '\n', stderr );
	    }
	}

	free( data2 );
    }
}

int main( void ) {

    Matrix m1 = mat_create( 3, 3 );
    if( m1 == NULL ) {
        fputs( "ERROR - create of first 3x3 matrix failed!\n", stderr );
	exit( 1 );
    }

    float data1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    mat_init( m1, data1 );

    puts( "Matrix 1:" );
    mat_print( m1, stdout );

    float row1[] = { 14.25, 7.0, 33.75 };
    float row2[] = {  3.50, 2.0,  1.0  };

    set_and_test_row( m1, 2, 3, row1 );
    set_and_test_row( m1, 1, 3, row2 );
    puts( "\nModified Matrix:" );
    mat_print( m1, stdout );

    mat_destroy( m1 );

    return( 0 );

}
