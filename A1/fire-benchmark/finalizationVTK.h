/**
 * Finalization step - write results and other computational vectors to files
 *
 * @date 22-Oct-2012
 * @author V. Petkov
 */

#ifndef FINALIZATIONVTK_H_
#define FINALIZATIONVTK_H_

void finalizationVTK(int nintci, int nintcf, int** lcc, double* var, double* cgup, double* su);

#endif /* FINALIZATION_H_ */

