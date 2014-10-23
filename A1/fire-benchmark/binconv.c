#include <stdio.h>
#include <stdlib.h>

/* 
 need to add a description according to doxygen
*/

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
               return EXIT_FAILURE; //we can use return 1 here
	     
        }

       return EXIT_SUCCESS; //we can use return 0 here

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


       
       /*The type used taken from read_formatted- xread.c */
    
       int *NINTCI = (int *) malloc(1 * sizeof(int) ); 
       int *NINTCF = (int *) malloc(1 * sizeof(int) );
       int *NEXTCI = (int *) malloc(1 * sizeof(int) ); 
       int *NEXTCF = (int *) malloc(1 * sizeof(int) );    

       int ***LCC = (int ***) malloc (6 * (*NINTCF + 1) * sizeof(int**) );

       double **BS = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );
       double **BE = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );
       double **BN = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );
       double **BW = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );
       double **BL = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );
       double **BH = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) ); 
       double **BP = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) ); 
       double **SU = (double **) malloc(1 * (*NEXTCF + 1) * sizeof(double*) );

       int **NBOARD = (int **) malloc(1 * (*NINTCF + 1) * sizeof(int) );
       


       /* Reading DATA file */
       fscanf(fp_dat, "%d", NINTCI);
       fscanf(fp_dat, "%d", NINTCF);
       fscanf(fp_dat, "%d", NEXTCI);
       fscanf(fp_dat, "%d", NEXTCF);

       /* Writing the data from DATA file to BINARY file */
       fwrite(NINTCI, sizeof(int), 1, fp_bin);
       fwrite(NINTCF, sizeof(int), 1, fp_bin);
       fwrite(NEXTCI, sizeof(int), 1, fp_bin);
       fwrite(NINTCF, sizeof(int), 1, fp_bin);
	

	if ( (*LCC = (int**) malloc(6 * sizeof(int*))) == NULL ){
		printf("Malloc failed to allocate first dimension of LCC (6)");
		return -1;
	}

	for ( i = 0; i < 6; i++ ){
		if ( ((*LCC)[i] = (int *) malloc((*NINTCF + 1) * sizeof(int))) == NULL ){
			printf("Malloc(LCC) failed \n");
			return -1;
		}
	}

	for ( i = (*NINTCI); i <= *NINTCF; i++ ){

        /* Reading DATA file */
        fscanf(fp_dat, "%d", &(*LCC)[0][i]);
	fscanf(fp_dat, "%d", &(*LCC)[1][i]);
	fscanf(fp_dat, "%d", &(*LCC)[2][i]);
	fscanf(fp_dat, "%d", &(*LCC)[3][i]);
	fscanf(fp_dat, "%d", &(*LCC)[4][i]);
	fscanf(fp_dat, "%d", &(*LCC)[5][i]);

         /* Writing the data from DATA file to BINARY file */
         fwrite(&(*LCC)[0][i], sizeof(int), 1, fp_bin);
         fwrite(&(*LCC)[1][i], sizeof(int), 1, fp_bin);
         fwrite(&(*LCC)[2][i], sizeof(int), 1, fp_bin);
         fwrite(&(*LCC)[3][i], sizeof(int), 1, fp_bin);
         fwrite(&(*LCC)[4][i], sizeof(int), 1, fp_bin);
         fwrite(&(*LCC)[5][i], sizeof(int), 1, fp_bin);
	}


	if ( (*BS = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BE = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BN = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BW = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BL = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BH = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*BP = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	if ( (*SU = (double *) malloc((*NEXTCF + 1) * sizeof(double))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	
	for ( i = (*NINTCI); i <= *NINTCF; i++ ){

         /* Reading DATA file */
	 fscanf(fp_dat, "%lf", &((*BS)[i]));
	 fscanf(fp_dat, "%lf", &((*BE)[i]));
	 fscanf(fp_dat, "%lf", &((*BN)[i]));
	 fscanf(fp_dat, "%lf", &((*BW)[i]));
	 fscanf(fp_dat, "%lf", &((*BL)[i]));
	 fscanf(fp_dat, "%lf", &((*BH)[i]));
	 fscanf(fp_dat, "%lf", &((*BP)[i]));
	 fscanf(fp_dat, "%lf", &((*SU)[i]));

         /* Writing the data from DATA file to BINARY file */
         fwrite(&((*BS)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BE)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BN)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BW)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BL)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BH)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*BP)[i]), sizeof(double), 1, fp_bin);
         fwrite(&((*SU)[i]), sizeof(double), 1, fp_bin);
	}


	if ( (*NBOARD = (int *) malloc((*NINTCF + 1) * sizeof(int))) == NULL ){
		printf("Malloc() failed \n");
		return -1;
	}

	for ( i = (*NINTCI); i <= *NINTCF; i++ ){

        /* Reading DATA file */
	fscanf(fp_dat, "%d", &((*NBOARD)[i]));

        /* Writing the data from DATA file to BINARY file */
        fwrite(&((*NBOARD)[i]), sizeof(int), 1, fp_bin);
        }

       /* Close DATA File */
       fclose(fp_dat);
       /* Close BINARY File */
       fclose(fp_bin);

       printf("\n");
       printf("Converted DATA File into BINARY File successfully \n");
      
	return 0;
}
