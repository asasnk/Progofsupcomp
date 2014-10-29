/**
 * Main GCCG program
 *
 * @author E. Xue, V. Petkov
 * @date 22-May-2009, 22-Oct-2012
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "mpi.h"

#include "initialization.h"
#include "initializationBin.h"
#include "compute_solution.h"
#include "finalization.h"
#include "finalizationVTK.h"

#define NUMEVENT0 4
#define NUMEVENT1 1

// call error code here
int main(int argc, char *argv[]) {
    
    int i;
    int init_status;
    
    const int max_iters = 10000;    /// maximum number of iteration to perform

    /** Simulation parameters parsed from the input datasets */
    int nintci, nintcf;    /// internal cells start and end index
    /// external cells start and end index. The external cells are only ghost cells.
    /// They are accessed only through internal cells
    int nextci, nextcf;
    int **lcc;    /// link cell-to-cell array - stores neighboring information
    /// Boundary coefficients for each volume cell (South, East, North, West, High, Low)
    double *bs, *be, *bn, *bw, *bh, *bl;
    double *bp;    /// Pole coefficient
    double *su;    /// Source values

    double residual_ratio;    /// the ratio between the reference and the current residual
    double *var;    /// the variation vector -> keeps the result in the end

    /** Additional vectors required for the computation */
    double *cgup, *oc, *cnorm;
 
    char file_out_cgup_vtk[255];
    char file_out_su_vtk[255];
    char file_out_var_vtk[255];
    char *file_in = argv[2]; // argv[1] or argv[2] ???
    char output_name[255];
    char *file_out = output_name;
    /* Write File for PAPI counter values */
    /* not sure if required */
    char filename[255];
    
    /* Check whether right number of arguments have been passed */
    if( argc < 4) {
        printf( "Need 4 arguments\nUse : %s <format> <input file> <output prefix> \n", argv[0]);
        return EXIT_FAILURE ;
    }
    /* Check whether input is only text or binary */ 
    if( strcmp( argv[1], "text" ) != 0 && strcmp( argv[1], "bin" ) != 0 ) {
        printf( "<format> must be 'text' or 'bin' only\n" );
        return EXIT_FAILURE;
    } 
    
    strcpy( filename, "pstats" );
    strcat( filename, ".dat" );
    FILE *open;
    open = fopen( filename, "w" );
    
    /* Write file for required output */ 

    strcpy( output_name, argv[3] );

    strcpy( file_out_su_vtk, argv[3] );
    strcat( file_out_su_vtk, ".SU.vtk" );

    strcpy( file_out_var_vtk, argv[3] );
    strcat( file_out_var_vtk, ".VAR.vtk" );

    strcpy( file_out_cgup_vtk, argv[3] );
    strcat( file_out_cgup_vtk, ".CGUP.vtk" );
    
    /* Creating two event sets for PAPI */

 
    /********** START INITIALIZATION **********/
    // read-in the input file
    if( strcmp(argv[1], "text" )!= 0)
        init_status = initialization(file_in, &nintci, &nintcf, &nextci, &nextcf, &lcc,
                                     &bs, &be, &bn, &bw, &bl, &bh, &bp, &su, &var, &cgup, &oc, 
                                     &cnorm);
    else if (strcmp(argv[1], "bin") != 0)
        init_status = initializationBin(file_in, &nintci, &nintcf, &nextci, &nextcf, &lcc,
                                     &bs, &be, &bn, &bw, &bl, &bh, &bp, &su, &var, &cgup, &oc, 
                                     &cnorm);
    else
        fprintf(stderr, "Failed to initialize data!\n");

    if ( init_status != 0 ) {
        fprintf(stderr, "Failed to initialize data!\n");
        abort();
    } 

   
    /********** END INITIALIZATION **********/

    /********** START COMPUTATIONAL LOOP **********/
 //   int total_iters = compute_solution(max_iters, nintci, nintcf, nextcf, lcc, bp, bs, bw, bl, bn,
//                                       be, bh, cnorm, var, su, cgup, &residual_ratio);
    /********** END COMPUTATIONAL LOOP **********/

    /********** START FINALIZATION **********/
  //  finalization(file_in, total_iters, residual_ratio, nintci, nintcf, var, cgup, su);
    finalizationVTK(file_out, nintci, nintcf, lcc, var, cgup, su);
    /********** END FINALIZATION **********/


    free(cnorm);
    free(var);
    free(cgup);
    free(su);
    free(bp);
    free(bh);
    free(bl);
    free(bw);
    free(bn);
    free(be);
    free(bs);

for ( i = 0; i < 6; ++i)
{
   printf("lcc[1][%d] = %d\n", i, lcc[1][i] );
}

   for ( i = nintci; i <= nintcf; i++ ) {
        free(lcc[i]);
    }
   free(lcc);
 
    return 0;
}

