/**
 * Initialization step - parse the input file, compute data distribution, initialize LOCAL computational arrays
 *
 * @date 22-Oct-2012
 * @author V. Petkov
 */

#ifndef INITIALIZATIONBIN_H_
#define INITIALIZATIONBIN_H_

int initializationBin(char* file_in, int* nintci, int* nintcf, int* nextci,
                   int* nextcf, int*** lcc, double** bs, double** be, double** bn, double** bw,
                   double** bl, double** bh, double** bp, double** su, double** var, double** cgup, 
                   double** oc, double** cnorm);

#endif /* INITIALIZATION_H_ */

