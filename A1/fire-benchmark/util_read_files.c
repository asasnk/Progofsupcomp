/**
 * Helper functions for reading from input data file
 *
 * @author E. Xue, V. Petkov
 * @date 22-May-2009, 22-Oct-2012
 */
#include <stdio.h>
#include <stdlib.h>
#include "util_read_files.h"

int read_formatted(char *filename, int *nintci, int *nintcf, int *nextci,
        int *nextcf, int ***lcc, double **bs, double **be, double **bn,
        double **bw, double **bl, double **bh, double **bp, double **su)
{
    int i;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    //4 variables in total!!!
    fscanf(fp, "%d", nintci);
    fscanf(fp, "%d", nintcf);
    fscanf(fp, "%d", nextci);
    fscanf(fp, "%d", nextcf);

    //allocating lcc
    if ((*lcc = (int**) malloc( ( (*nintcf) - (*nintci) + 1) * sizeof(int*) )) == NULL)
    {
        printf("malloc failed to allocate first dimension of lcc (nintcf)");
        return -1;
    }
    for (i = (*nintci); i <= (*nintcf); i++)
    {
        if (((*lcc)[i] = (int *) malloc( 6 * sizeof(int) )) == NULL)
        {
            printf("malloc(lcc) failed\n");
            return -1;
        }
    }

    //start reading lcc
    //note that c array index starts from 0 while fortran starts from 1!
    for (i = (*nintci); i <= (*nintcf); i++)
    {
        fscanf(fp, "%d", &(*lcc)[i][0]);
        fscanf(fp, "%d", &(*lcc)[i][1]);
        fscanf(fp, "%d", &(*lcc)[i][2]);
        fscanf(fp, "%d", &(*lcc)[i][3]);
        fscanf(fp, "%d", &(*lcc)[i][4]);
        fscanf(fp, "%d", &(*lcc)[i][5]);
    }

    // allocate other arrays
    if ((*bs = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*be = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*bn = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*bw = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*bl = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*bh = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*bp = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }
    if ((*su = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL)
    {
        printf("malloc() failed\n");
        return -1;
    }

    // read the other arrays
    for (i = (*nintci); i <= *nintcf; i++)
    {
        fscanf(fp, "%lf", &((*bs)[i]));
        fscanf(fp, "%lf", &((*be)[i]));
        fscanf(fp, "%lf", &((*bn)[i]));
        fscanf(fp, "%lf", &((*bw)[i]));
        fscanf(fp, "%lf", &((*bl)[i]));
        fscanf(fp, "%lf", &((*bh)[i]));
        fscanf(fp, "%lf", &((*bp)[i]));
        fscanf(fp, "%lf", &((*su)[i]));
    }

    fclose(fp);

    return 0;
}


/**
 * Function to read binary file
 * @param nintci, nintcf internal cells start and end index
 * @param nextci, nextcf external cells start and end index.
 * @param lcc link cell-to-cell array. Stores topology information
 * @param bs, be, bn, bw, bl, bh, bp, su boundary coefficients for each volume cell
 */
int read_binary(char *filename, int *nintci, int *nintcf, int *nextci,
        int *nextcf, int ***lcc, double **bs, double **be, double **bn,
        double **bw, double **bl, double **bh, double **bp, double **su) 
{
    /* Open binary file read */
    int i;
    FILE *fp_bin = fopen( filename, "rb" );

    if( fp_bin == NULL ){
        printf( "Error while opening BINARY file %s \n", filename );
    }
    /*The type used taken from read_formatted- util_read_files.c */

    fread( nintci, sizeof(int), 1, fp_bin );
    fread( nintcf, sizeof(int), 1, fp_bin );
    fread( nextci, sizeof(int), 1, fp_bin );
    fread( nextcf, sizeof(int), 1, fp_bin );
    if( ( *lcc = ( int** ) malloc( 6 * sizeof( int* ) ) ) == NULL ) {
        printf( "Malloc failed to allocate first dimension of lcc (6)" );
        return -1;
    }


    for( i = 0; i < 6; i++ ){
        if( ( ( *lcc )[i] = ( int * ) malloc( ( *nintcf + 1 ) * sizeof( int ) ) ) == NULL ) {
            printf( "Malloc(lcc) failed \n" );
            return -1;
        }
    }

    for( i = ( *nintci ); i <= *nintcf; i++ ) {
        fread( &( *lcc )[0][i], sizeof( int ), 1, fp_bin );
        fread( &( *lcc )[1][i], sizeof( int ), 1, fp_bin );
        fread( &( *lcc )[2][i], sizeof( int ), 1, fp_bin );
        fread( &( *lcc )[3][i], sizeof( int ), 1, fp_bin );
        fread( &( *lcc )[4][i], sizeof( int ), 1, fp_bin );
        fread( &( *lcc )[5][i], sizeof( int ), 1, fp_bin );
    }

    if( ( *bs = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *be = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *bn = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *bw = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *bl = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *bh = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *bp = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    if( ( *su = (double *) malloc(( *nextcf + 1) * sizeof(double))) == NULL ) {
        printf("Malloc() failed \n");
        return -1;
    }

    for( i = ( *nintci ); i <= *nintcf; i++ ) {
        fread( &( ( *bs )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *be )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *bn )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *bw )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *bl )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *bh )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *bp )[i] ), sizeof( double ), 1, fp_bin );
        fread( &( ( *su )[i] ), sizeof( double ), 1, fp_bin );
    }

    
    /* Closing BINARY File */
    fclose( fp_bin );
    printf( "\n" );
    printf( "Read BINARY File successfully \n" );

    return 0;
}
