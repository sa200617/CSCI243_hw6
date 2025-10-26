//
// Simple test of the Matrix ADT
//
// tests mat_mult()
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Matrix.h"

// start with two non-square matrices

void testNonSquare( void ) {

    Matrix m1 = mat_create( 3, 5 );
    if( m1 == NULL ) {
        fputs( "ERROR - create of 3x5 matrix failed!\n", stderr );
	return;
    }

    Matrix m2 = mat_create( 5, 3 );
    if( m2 == NULL ) {
        fputs( "ERROR - create of 5x3 matrix failed!\n", stderr );
	mat_destroy( m1 );
	return;
    }

    float data1[] = {
         1.0,  2.0,  3.0,  4.0,  5.0,    // r1
	 6.0,  7.0,  8.0,  9.0, 10.0,    // r2
	11.0, 12.0, 13.0, 14.0, 15.0 };  // r3

    float data2[] = {
         2.0, 2.0, 2.0,    3.0, 3.0, 3.0,     // r1, r2
	 4.0, 4.0, 4.0,    5.0, 5.0, 5.0,     // r3, r4
	 6.0, 6.0, 6.0 };                     // r5

    mat_init( m1, data1 );
    mat_init( m2, data2 );

    puts( "===========================\nNon-square test 1\n" );
    puts( "Initialized Matrix 1:" );
    mat_print( m1, stdout );
    puts( "\nInitialized Matrix 2:" );
    mat_print( m2, stdout );

    Matrix m3 = mat_mult( m1, m2 );
    if( m3 == NULL ) {
        fputs( "ERROR - 3x5 * 5x3 multiplication failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	return;
    }
    puts( "\nMatrix 3 (m1 * m2):" );
    mat_print( m3, stdout );
    mat_destroy( m3 );

    puts( "\n===========================\nNon-square test 2\n" );
    Matrix m4 = mat_mult( m2, m1 );
    if( m4 == NULL ) {
        fputs( "ERROR - 5x3 * 3x5 multiplication failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	return;
    }
    puts( "\nMatrix 4 (m2 * m1):" );
    mat_print( m4, stdout );
    mat_destroy( m4 );

    // clean up

    mat_destroy( m1 );
    mat_destroy( m2 );
}

// now, some square matrices

void testSquare( void ) {

    Matrix m1 = mat_create( 3, 3 );
    if( m1 == NULL ) {
        fputs( "ERROR - create of first 3x3 matrix failed!\n", stderr );
	return;
    }

    Matrix m2 = mat_create( 3, 3 );
    if( m2 == NULL ) {
        fputs( "ERROR - create of second 3x3 matrix failed!\n", stderr );
	mat_destroy( m1 );
	return;
    }

    float data1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    float data2[] = { 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };

    mat_init( m1, data1 );
    mat_init( m2, data2 );

    puts( "\n===========================\nSquare test 1\n" );
    puts( "Initialized Matrix 1:" );
    mat_print( m1, stdout );
    puts( "\nInitialized Matrix 2:" );
    mat_print( m2, stdout );

    Matrix m3 = mat_mult( m1, m2 );
    if( m3 == NULL ) {
        fputs( "ERROR - first M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	return;
    }
    puts( "\nMatrix 3 (m1 * m2):" );
    mat_print( m3, stdout );
    mat_destroy( m3 );

    puts( "\n===========================\nSquare test 2\n" );
    Matrix m4 = mat_mult( m2, m1 );
    if( m3 == NULL ) {
        fputs( "ERROR - second M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	return;
    }
    puts( "\nMatrix 4 (m2 * m1):" );
    mat_print( m4, stdout );
    mat_destroy( m4 );

    // clean up
    mat_destroy( m1 );
    mat_destroy( m2 );
}

// finally, some matrix/vector tests

void testVector( void ) {

    Matrix m1 = mat_create( 4, 4 );
    if( m1 == NULL ) {
        fputs( "ERROR - create of transformation matrix failed!\n", stderr );
	return;
    }

    Matrix m2 = mat_create( 4, 1 );
    if( m2 == NULL ) {
        fputs( "ERROR - create of vertex matrix failed!\n", stderr );
	mat_destroy( m1 );
	return;
    }

    // basic translation matrix
    float data1[] = {
        1.0, 0.0, 0.0, 1.3,
	0.0, 1.0, 0.0, 0.7,
	0.0, 0.0, 1.0, 1.2,
	0.0, 0.0, 0.0, 1.0
    };

    // typical 3D point location
    float data2[] = { 3.0, 7.0, 5.0, 1.0 };

    mat_init( m1, data1 );
    mat_init( m2, data2 );

    puts( "\n===========================\nM*V test 1\n" );
    puts( "Translation matrix:" );
    mat_print( m1, stdout );
    puts( "\nVertex:" );
    mat_print( m2, stdout );

    Matrix mx = mat_mult( m1, m2 );
    if( mx == NULL ) {
        fputs( "ERROR - translation M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	return;
    }
    puts( "\nTranslation result:" );
    mat_print( mx, stdout );

    // basic scale matrix
    float data3[] = {
        2.0, 0.0, 0.0, 0.0,
	0.0, 1.5, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
    };

    mat_init( m1, data3 );

    puts( "\n===========================\nM*V test 2\n" );
    puts( "Scale matrix:" );
    mat_print( m1, stdout );
    puts( "\nVertex:" );
    mat_print( m2, stdout );

    Matrix ms = mat_mult( m1, m2 );
    if( ms == NULL ) {
        fputs( "ERROR - scaling M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	mat_destroy( mx );
	return;
    }
    puts( "\nScale result:" );
    mat_print( ms, stdout );
    mat_destroy( ms );

    // combined matrix
    float data4[] = {
        2.0, 0.0, 0.0, 1.3,
	0.0, 1.5, 0.0, 0.7,
	0.0, 0.0, 1.0, 1.2,
	0.0, 0.0, 0.0, 1.0
    };

    mat_init( m1, data4 );

    puts( "\n===========================\nM*V test 3\n" );
    puts( "Combined matrix:" );
    mat_print( m1, stdout );
    puts( "\nVertex:" );
    mat_print( m2, stdout );

    Matrix mc = mat_mult( m1, m2 );
    if( mc == NULL ) {
        fputs( "ERROR - combined M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	mat_destroy( mx );
	return;
    }
    puts( "\nCombined results:" );
    mat_print( mc, stdout );
    mat_destroy( mc );

    // scale the original translation
    mat_init( m1, data3 );

    puts( "\n===========================\nM*V test 4\n" );
    puts( "Scale matrix:" );
    mat_print( m1, stdout );
    puts( "\nTranslated vertex:" );
    mat_print( mx, stdout );

    Matrix mseq = mat_mult( m1, mx );
    if( mseq == NULL ) {
        fputs( "ERROR - sequential M*M failed!\n", stderr );
	mat_destroy( m1 );
	mat_destroy( m2 );
	mat_destroy( mx );
	return;
    }
    puts( "\nTranslate, then scale, results:" );
    mat_print( mseq, stdout );
    mat_destroy( mseq );

    // clean up
    mat_destroy( m1 );
    mat_destroy( m2 );
    mat_destroy( mx );
}

// run the tests
int main( void ) {
    testNonSquare();
    testSquare();
    testVector();
    return( 0 );
}
