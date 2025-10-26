//
// Simple test of the Matrix ADT
//
// tests mat_duplicate(), mat_equals()
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Matrix.h"

int main( void ) {
    Matrix m1, m2;

    m1 = mat_create( 3, 3 );
    if( m1 == NULL ) {
        fputs( "ERROR - create of first 3x3 matrix failed!\n", stderr );
	exit( 1 );
    }

    puts( "Matrix 1:" );
    mat_print( m1, stdout );

    m2 = mat_duplicate( m1 );
    if( m2 == NULL ) {
        fputs( "ERROR - create of second 3x3 matrix failed!\n", stderr );
	mat_destroy( m1 );
	exit( 1 );
    }

    puts( "\nMatrix 2:" );
    mat_print( m2, stdout );
    putchar( '\n' );

    if( mat_equals(m1,m2) ) {
        fputs( "SUCCESS - matrices are equal\n", stdout );
    } else {
        fputs( "ERROR - matrices are NOT equal\n", stdout );
    }

    mat_destroy( m1 );
    mat_destroy( m2 );

    return( 0 );

}
