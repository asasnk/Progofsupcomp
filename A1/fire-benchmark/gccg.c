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

#define NUMEVENT1 4
#define NUMEVENT2 2

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
    
    /*variables required for VTK files */
    int nodeCnt, ** points, ** elems;
 
    char file_out_cgup_vtk[255];
    char file_out_su_vtk[255];
    char file_out_var_vtk[255];
    char *file_in = argv[2]; // argv[1] or argv[2] ???
    char output_name[255];
    char *file_out = output_name;
    /* Write File for PAPI counter values */
    int Events1[NUMEVENT1] = {PAPI_L2_TCM, PAPI_L3_TCM, PAPI_L2_TCA, PAPI_L3_TCA};
    int Events2[NUMEVENT2] = {PAPI_DP_OPS, PAPI_SP_OPS};
    
    long_long Value1[NUMEVENT1], Value2[NUMEVENT2]; 
    long_long start_time, end_time;
    double time_initial, time_comp, time_final, time_total;
    
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
    
    /* Write file for required output */ 

    strcpy( output_name, argv[3] );

    strcpy( file_out_su_vtk, argv[3] );
    strcat( file_out_su_vtk, ".SU.vtk" );

    strcpy( file_out_var_vtk, argv[3] );
    strcat( file_out_var_vtk, ".VAR.vtk" );

    strcpy( file_out_cgup_vtk, argv[3] );
    strcat( file_out_cgup_vtk, ".CGUP.vtk" );
    
    // Create file for writing values of PAPI counters
    char filename[255];
    strcpy( filename, "Papi_dat" );
    strcat( filename, ".dat" );
    FILE *papi_dat;
    papi_dat = fopen( filename, "w" );
    
    /* Creating two event sets for PAPI */
    for( int idx = 0; idx < 2; idx++ ) {
        /********** START INITIALIZATION **********/
        /* Start PAPI counters */
        if( idx == 0 ) {
            if(PAPI_start_counters(Events1,NUMEVENTS1) != PAPI_OK) {
                handle_error(1);
            }
        } else {
            if(PAPI_start_counters(Events2,NUMEVENT2) != PAPI_OK) {
                handle_error(1);
            }
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            start_time = PAPI_get_real_usec();
        }
        // read-in the input file
        if( strcmp(argv[1], "text" )== 0)
            init_status = initialization(file_in, &nintci, &nintcf, &nextci, &nextcf, &lcc,
                                     &bs, &be, &bn, &bw, &bl, &bh, &bp, &su, &var, &cgup, &oc, 
                                     &cnorm);
        else if (strcmp(argv[1], "bin") == 0)
            init_status = initializationBin(file_in, &nintci, &nintcf, &nextci, &nextcf, &lcc,
                                     &bs, &be, &bn, &bw, &bl, &bh, &bp, &su, &var, &cgup, &oc, 
                                     &cnorm);
        else
            fprintf(stderr, "Failed to initialize data!\n");

        if ( init_status != 0 ) {
            fprintf(stderr, "Failed to initialize data!\n");
            abort();
        } 
        /* Read PAPI counters for initialization */
        if( idx == 0 ) {
            if(PAPI_read_counters(Value1, NUMEVENTS1) != PAPI_OK ) {
                handle_error(1);
            }
            fprintf( papi_dat, "Initial PAPI_L2_TCM %lld\n", Value1[0] );
            fprintf( papi_dat, "Initial PAPI_L3_TCM %lld\n", Value1[1] );
            fprintf( papi_dat, "Initial PAPI_L2_TCA %lld\n", Value1[2] );
            fprintf( papi_dat, "Initial PAPI_L3_TCA %lld\n", Value1[3] );
            fprintf( papi_dat, "Initial L2_Miss_Rate %.5f \n",((double)Value1[0] / (double)Value1[2]) *100);
            fprintf( papi_dat, "Initial L3_Miss_Rate %.5f \n",((double)Value1[1] / (double)Values[3]) *100);
        } else {
        
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            end_time = PAPI_get_real_usec();
            time_initial = (double)(end_time - start_time)/1000000;
            if( PAPI_read_counters(Value2, NUMEVENT2) != PAPI_OK ) {
                handle_error(1);
            }    char output_name[255];
    strcpy( output_name, argv[3] );int nodeCnt;
    int** points;
    int** elems;
    strcat( output_name, "." );
    strcat( output_name, "txt" );
    char *file_out = output_name;

    char file_out_su_vtk[255];
    strcpy( file_out_su_vtk, argv[3] );
    strcat( file_out_su_vtk, "_SU.vtk" );
    char file_out_var_vtk[255];
    strcpy( file_out_var_vtk, argv[3] );
    strcat( file_out_var_vtk, "_VAR.vtk" );
    char file_out_cgup_vtk[255];
    strcpy( file_out_cgup_vtk, argv[3] );
    strcat( file_out_cgup_vtk, "_CGUP.vtk" );
            fprintf( papi_dat, "Initial PAPI_DP_OPS %lld\n", Value2[0] );
            fprintf( papi_dat, "Initial PAPI_SP_OPS %lld\n", Value2[1] );
            fprintf( papi_dat, "Initial Mflops %.5f\n",((double)Value2[0] + (double)Value2[1]/1000000/time_initial );
            fprintf( papi_dat, "Initial Utilization %.5f \n",((((double)Value2[0]+ (double)Value2[1])/1000000/time_initial)/21600)*100);
            fprintf( papi_dat, "Initial ExecutionTime %.5f\n", time_initial );
        }
   
        /********** END INITIALIZATION **********/

        /********** START COMPUTATIONAL LOOP **********/
        /* Reset PAPI counters for Computation phase */
        if( idx == 0 ) {
            if(PAPI_read_counters(Events1,NUMEVENTS1) != PAPI_OK) {
                handle_error(1);
            }
        } else {
            if(PAPI_read_counters(Events2,NUMEVENT2) != PAPI_OK) {
                handle_error(1);
            }
            
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            start_time = PAPI_get_real_usec();
        }
    
        int total_iters = compute_solution(max_iters, nintci, nintcf, nextcf, lcc, bp, bs, bw, bl, bn,
                                       be, bh, cnorm, var, su, cgup, &residual_ratio);
        
        /* Read PAPI counters for computation phase */
        if( idx == 0 ) {
            if(PAPI_read_counters(Value1, NUMEVENTS1) != PAPI_OK ) {
                handle_error(1);
            }
            fprintf( papi_dat, "Compute PAPI_L2_TCM %lld\n", Value1[0] );
            fprintf( papi_dat, "Compute PAPI_L3_TCM %lld\n", Value1[1] );
            fprintf( papi_dat, "Compute PAPI_L2_TCA %lld\n", Value1[2] );
            fprintf( papi_dat, "Compute PAPI_L3_TCA %lld\n", Value1[3] );
            fprintf( papi_dat, "Compute L2_Miss_Rate %.5f \n",((double)Value1[0] / (double)Value1[2]) *100);
            fprintf( papi_dat, "Compute L3_Miss_Rate %.5f \n",((double)Value1[1] / (double)Values[3]) *100);
        } else {
            
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            end_time = PAPI_get_real_usec();
            time_comp = (double)(end_time - start_time)/1000000;
            if( PAPI_read_counters(Value2, NUMEVENT2) != PAPI_OK ) {
                handle_error(1);
            }
            fprintf( papi_dat, "Compute PAPI_DP_OPS %lld\n", Value2[0] );
            fprintf( papi_dat, "Compute PAPI_SP_OPS %lld\n", Value2[1] );
            fprintf( papi_dat, "Compute Mflops %.5f\n",((double)Value2[0] + (double)Value2[1]/1000000/time_comp );
            fprintf( papi_dat, "Compute Utilization %.5f \n",((((double)Value2[0]+ (double)Value2[1])/1000000/time_comp)/21600)*100);
            fprintf( papi_dat, "Compute ExecutionTime %.5f\n", time_comp );
        }
        /********** END COMPUTATIONAL LOOP **********/

        /********** START FINALIZATION **********/
        /* Reset PAPI counters for Computation phase */
        if( idx == 0 ) {
            if(PAPI_read_counters(Events1,NUMEVENTS1) != PAPI_OK) {
                handle_error(1);
            }
        } else {
            if(PAPI_read_counters(Events2,NUMEVENT2) != PAPI_OK) {
                handle_error(1);
            }
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            start_time = PAPI_get_real_usec();
        }
        
        finalization(file_in, total_iters, residual_ratio, nintci, nintcf, var, cgup, su);
        int status = vol2mesh(nintci, nintcf, lcc, &nodeCnt, &points, &elems); 
        if ( status != 0 ) fprintf(stderr, "Error when trying to call vol2mesh");
    
        status = write_result_vtk(file_out_var_vtk, nintci, nintcf, nodeCnt, points, elems, var);
        if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of var");
    
        status = write_result_vtk(file_out_cgup_vtk, nintci, nintcf, nodeCnt, points, elems, cgup);
        if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of cgup");
    
        status = write_result_vtk(file_out_su_vtk, nintci, nintcf, nodeCnt, points, elems, su);
        if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of su");
        
        if( idx == 0 ) {
            if(PAPI_stop_counters(Value1, NUMEVENTS1) != PAPI_OK ) {
                handle_error(1);
            }
            fprintf( papi_dat, "Final PAPI_L2_TCM %lld\n", Value1[0] );
            fprintf( papi_dat, "Final PAPI_L3_TCM %lld\n", Value1[1] );
            fprintf( papi_dat, "Final PAPI_L2_TCA %lld\n", Value1[2] );
            fprintf( papi_dat, "Final PAPI_L3_TCA %lld\n", Value1[3] );
            fprintf( papi_dat, "Final L2_Miss_Rate %.5f \n",((double)Value1[0] / (double)Value1[2]) *100);
            fprintf( papi_dat, "Final L3_Miss_Rate %.5f \n",((double)Value1[1] / (double)Values[3]) *100);
        } else {
            
            if (PAPI_library_init( PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
            end_time = PAPI_get_real_usec();
            time_final = (double)(end_time - start_time)/1000000;
            if( PAPI_stop_counters(Value2, NUMEVENT2) != PAPI_OK ) {
                handle_error(1);
            }
            fprintf( papi_dat, "Final PAPI_DP_OPS %lld\n", Value2[0] );
            fprintf( papi_dat, "Final PAPI_SP_OPS %lld\n", Value2[1] );
            fprintf( papi_dat, "Final Mflops %.5f\n",((double)Value2[0] + (double)Value2[1]/1000000/time_final );
            fprintf( papi_dat, "Final Utilization %.5f \n",((((double)Value2[0]+ (double)Value2[1])/1000000/time_final)/21600)*100);
            fprintf( papi_dat, "Final ExecutionTime %.5f \n", time_final );
            
            time_total = time_initial + time_comp + time_final;
        }
        
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
    }
    
    for ( i = 0; i < 6; ++i){
    printf("lcc[1][%d] = %d\n", i, lcc[1][i] );
    }

    for ( i = nintci; i <= nintcf; i++ ) {
        free(lcc[i]);
    }
    free(lcc);
    
    fprintf(papi_dat, "Initialization ExecutionTime %.5f \n", (time_initial / time_total) * 100);
    fprintf(papi_dat, "Computation ExecutionTime %.5f \n", (time_comp / time_total) * 100);
    fprintf(papi_dat, "Finalization ExecutionTime %.5f \n", (time_final / time_total) * 100);
    fprintf(papi_dat, "Total ExecutionTime %.5f \n", time_total);
    fclose(papi_dat);
    return 0;
}

void handle_error( int err_code ) {
    switch( err_code ) {
        case 0:
            printf( "Error code 0\n" );
            break;
        case 1:
            printf( "Error code 1\n" );
            break;
}
