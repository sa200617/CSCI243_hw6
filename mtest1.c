//
// Simple test of the Matrix ADT
//
// tests mat_create(), mat_init(), mat_print(), mat_destroy()
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Matrix.h"

int main( void ) {
    Matrix m1;

    m1 = mat_create( 3, 3 );

    if( m1 == NULL ) {

        fputs( "ERROR create of 3x3 matrix failed!\n", stderr );

    } else {

	puts( "Matrix 1 contains:" );
	mat_print( m1, stdout );
        mat_destroy( m1 );
    }

    return( 0 );

}
