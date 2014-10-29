#include <stdio.h>
#include <stdlib.h>

/* This file converts acii input file into binary files */
int binconv(char *asciiFile, char *binFile);

int main(int argc, char *argv[]) 
{

	if( argc == 3 )
  	{
      	printf("The argument supplied is %s\n", argv[2]);
   	}
   	else if( argc > 3 )
   	{
      	printf("Too many arguments supplied.\n");
   	}
   	else
   	{
      	printf("Three argument expected.\n");
   	}

	char *asciiFile = argv[1];
	char *binFile  = argv[2];

        int return_status = binconv(asciiFile, binFile); /* assumes a value for successful completion, i.e. 0 in case of success and 1 in
 	case of failure */

        if ( return_status !=0 ){

               printf("Data file to Binary file conversion failed \n");
               return EXIT_FAILURE; 
	    }

       return EXIT_SUCCESS; 

}


int binconv(char *asciiFile, char *binFile)
{

       int i;

	/* Open a data file for Reading */
	FILE *fp_dat = fopen(asciiFile, "r");
        /* Open a binary file for Writing */
        FILE *fp_bin = fopen(binFile, "wb"); 

	if ( fp_dat == NULL ){
		printf("Error opening DATA file %s \n", asciiFile);
		return -1;
	}

        if( fp_bin == NULL ){
                printf("Error opening BINARY file %s \n", binFile);
        }


       
       /*The type used taken from read_f*/
    
       int *nintci = (int *) malloc(1 * sizeof(int) ); 
       int *nintcf = (int *) malloc(1 * sizeof(int) );
       int *nextci = (int *) malloc(1 * sizeof(int) ); 
       int *nextcf = (int *) malloc(1 * sizeof(int) );    
       int ***lcc = (int ***) malloc (6 * (*nintcf + 1) * sizeof(int**) );
       double **bs = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );
       double **be = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );
       double **bn = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );
       double **bw = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );
       double **bl = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );
       double **bh = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) ); 
       double **bp = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) ); 
       double **su = (double **) malloc(1 * (*nextcf + 1) * sizeof(double*) );

       /* Reading DATA file */
       fscanf(fp_dat, "%d", nintci);
       fscanf(fp_dat, "%d", nintcf);
       fscanf(fp_dat, "%d", nextci);
       fscanf(fp_dat, "%d", nextcf);

       /* Writing the data from DATA file to BINARY file */
       fwrite(nintci, sizeof(int), 1, fp_bin);
       fwrite(nintcf, sizeof(int), 1, fp_bin);
       fwrite(nextci, sizeof(int), 1, fp_bin);
       fwrite(nintcf, sizeof(int), 1, fp_bin); 
       if ( (*lcc = (int**) malloc(6 * sizeof(int*))) == NULL ) {
       		printf("Malloc failed to allocate first dimension of lcc (6)");
       		return -1;
       }

	for ( i = 0; i < 6; i++ ){
		if ( ((*lcc)[i] = (int *) malloc((*nintcf + 1) * sizeof(int))) == NULL ){
			printf("Malloc(lcc) failed \n");
			return -1;
		}
	}

	for ( i = (*nintci); i <= *nintcf; i++ ){

        /* Reading DATA file */
        fscanf(fp_dat, "%d", &(*lcc)[0][i]);
	fscanf(fp_dat, "%d", &(*lcc)[1][i]);
	fscanf(fp_dat, "%d", &(*lcc)[2][i]);
	fscanf(fp_dat, "%d", &(*lcc)[3][i]);
	fscanf(fp_dat, "%d", &(*lcc)[4][i]);
	fscanf(fp_dat, "%d", &(*lcc)[5][i]);

         /* Writing the data from DATA file to BINARY file */
         fwrite(&(*lcc)[0][i], sizeof(int), 1, fp_bin);
         fwrite(&(*lcc)[1][i], sizeof(int), 1, fp_bin);
         fwrite(&(*lcc)[2][i], sizeof(int), 1, fp_bin);
         fwrite(&(*lcc)[3][i], sizeof(int), 1, fp_bin);
         fwrite(&(*lcc)[4][i], sizeof(int), 1, fp_bin);
         fwrite(&(*lcc)[5][i], sizeof(int), 1, fp_bin);
	}


	if ( (*bs = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*be = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*bn = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*bw = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*bl = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*bh = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*bp = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*su = (double *) malloc((*nextcf + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	
	for ( i = (*nintci); i <= *nintcf; i++ ){

         /* Reading DATA file */
	 fscanf(fp_dat, "%lf", &((*bs)[i]));
	 fscanf(fp_dat, "%lf", &((*be)[i]));
	 fscanf(fp_dat, "%lf", &((*bn)[i]));
	 fscanf(fp_dat, "%lf", &((*bw)[i]));
	 fscanf(fp_dat, "%lf", &((*bl)[i]));
	 fscanf(fp_dat, "%lf", &((*bh)[i]));
	 fscanf(fp_dat, "%lf", &((*bp)[i]));
	 fscanf(fp_dat, "%lf", &((*su)[i]));

         /* Writing the data from DATA file to BINARY file */
         fwrite(&((*bs)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*be)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*bn)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*bw)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*bl)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*bh)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*bp)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*su)[i]), sizeof(double), 1, fp_bin);
	}




       /* Close DATA File */
       fclose(fp_dat);
       /* Close BINARY File */
       fclose(fp_bin);

       printf("\n");
       printf("Converted DATA File into BINARY File successfully \n");
      
	return 0;
}
