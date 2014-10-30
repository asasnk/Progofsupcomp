/**
 * Finalization step - write results and other computational vectors to files
 *
 * @date 22-Oct-2012
 * @author V. Petkov
 */

#include <stdio.h>
#include "util_write_files.h"
#include "vol2mesh.h"

void finalizationVTK(char* FILE_OUT, int nintci, int nintcf, int** lcc, double* var, double* cgup, double* su){
    char file_out_var_vtk[255];
    char file_out_cgup_vtk[255];
    char file_out_su_vtk[255];
    int nodeCnt;
    int** points;
    int** elems;
    
    int status = vol2mesh(nintci, nintcf, lcc, &nodeCnt, &points, &elems);
    if ( status != 0 ) fprintf(stderr, "Error when trying to call vol2mesh");
    
    status = write_result_vtk(file_out_var_vtk, nintci, nintcf, nodeCnt, points, elems, var);
    if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of var");
    
    status = write_result_vtk(file_out_cgup_vtk, nintci, nintcf, nodeCnt, points, elems, cgup);
    if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of cgup");
    
    status = write_result_vtk(file_out_su_vtk, nintci, nintcf, nodeCnt, points, elems, su);
    if ( status != 0 ) fprintf(stderr, "Error when trying to write to vtk file of su");
}

