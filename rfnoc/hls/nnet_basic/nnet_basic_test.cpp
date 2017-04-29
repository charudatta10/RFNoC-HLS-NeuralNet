#include <stdio.h>
#include <math.h>

#define N_LAYER_IN 784
#define N_LAYER_OUT 10

#include "nnet_basic.h"


// int main(int argc, char **argv)
// {
//
//   // Dummy data for now
//   input_t data[N_LAYER_IN] = {0, 1, 1};
//   coeff_t coeffs[N_LAYER_IN][N_LAYER_OUT] = {{1,  0,  0},
//                                              {0,  2,  0},
//                                              {0, 10, 20}};
//   bias_t  biases[N_LAYER_OUT] = {1, 2, 3};
//   short int answer[N_LAYER_OUT] = {1, 14, 23};
//
//   // Run the basic neural net block
//   result_t res[N_LAYER_OUT];
//   nnet_basic(data, coeffs, biases, res);
//
//   // Print result vector
//   int err_cnt = 0;
//   for (int ii = 0; ii < N_LAYER_OUT; ii++) {
//     std::cout << " Expected: " << answer[ii] << "   Received: " << res[ii] << std::endl;
//     if (res[ii] != answer[ii]) err_cnt++;
//   }
//   return err_cnt;
// }


int read_file_1D(const char * filename, data_t *data, unsigned int nsamps)
{
  FILE *fp;
//  data_t datain[nsamps];

  fp = fopen(filename, "r");
  std::cout<< "Reading 1D file: " << fp << std::endl;
  if (fp == 0) {
    std::cout << "Failed to open file" << std::endl;
    return 1;
  }
  // Read data from file
  float newval;
  for (int ii = 0; ii < nsamps; ii++){
    if (fscanf(fp, "%f\n", &newval) != 0){
      data[ii] = newval;
    } else {
      std::cout << "File failed to extract data" << std::endl;
      return 2;
    }
  }
  fclose(fp);
  return 0;
}

int read_file_2D(const char * filename, data_t data[], unsigned int nrows, unsigned int ncols)
{
  FILE *fp;
//  data_t datain[ncols][nrows];

  fp = fopen(filename, "r");
  std::cout<< "Reading 2D file: " << fp << std::endl;
  if (fp == 0) {
    std::cout << "Failed to open file" << std::endl;
    return 1;
  }
  // Read data from file
  float newval;
  for (int ii = 0; ii < nrows; ii++) {
    for (int jj = 0; jj < ncols; jj++){
      if (fscanf(fp, "%f\n", &newval) != 0){
    	//std::cout<<"Reading " << ii << " " << jj << " " << newval << std::endl;
        data[ii*ncols+jj] = newval;
      } else {
        std::cout << "File failed to extract data" << std::endl;
        return 2;
      }
    }
  }
  fclose(fp);
  return 0;
}


int main(int argc, char **argv)
{
  // DATA FROM UDACITY TENSORFLOW CLASS
  // 1-Layer test

  data_t  data[N_LAYER_IN];
  coeff_t coeffs[N_LAYER_IN][N_LAYER_OUT];
  bias_t  biases[N_LAYER_OUT];

  // Load data from file
  int rval = 0;
  rval = read_file_1D("data/mnist_validation_data_784x1.dat", data, N_LAYER_IN);
  rval = read_file_2D("data/mnist_layer1_weights_784x10.dat", coeffs[0], N_LAYER_IN, N_LAYER_OUT);
  rval = read_file_1D("data/mnist_layer1_biases_10x1.dat", biases, N_LAYER_OUT);

//  int ii, jj;
//  for (ii=0; ii < N_LAYER_OUT; ii++){
//	  std::cout <<  ii << ": " << float(biases[ii]) << std::endl;
//  }
//
//  for (ii=0; ii < N_LAYER_IN; ii++){
//	  for (jj=0; jj < N_LAYER_OUT; jj++){
//		  std::cout <<  ii << "," << jj << ": " << float(coeffs[ii][jj]) << std::endl;
//	  }
//  }

  // Run the basic neural net block
  result_t res[N_LAYER_OUT];
  nnet_layer(data, coeffs, biases, res);

  // Print result vector
  int err_cnt = 0;
  for (int ii = 0; ii < N_LAYER_OUT; ii++) {
	  std::cout << "Received: " << res[ii] << std::endl;
//    std::cout << " Expected: " << answer[ii] << "   Received: " << res[ii] << std::endl;
//    if (res[ii] != answer[ii]) err_cnt++;
  }
  return err_cnt;
}


//int main () {
//  const int    SAMPLES=100;
//  FILE         *fp;
//
//  // short int taps[N] = {0,-10,-9,23,56,63,56,23,-9,-10,0,};
//
//  int i, ramp_up;
//  short int signal = 0;
//  ramp_up = 1;
//  axis in_data, out_data;
//
//  fp=fopen("out.dat","w");
//  // Stimulate with impulses
//  for (i=0;i<=SAMPLES;i++) {
//    if (ramp_up == 1)
//      signal = signal + 1;
//    else
//      signal = signal - 1;
//
//    // Populate input data
//    in_data.data = signal;
//    in_data.last = (i == SAMPLES);
//
//  // Execute the function with latest input
//    nnet_basic(in_data, out_data);
//
//   if ((ramp_up == 1) && (signal >= 75))
//    ramp_up = 0;
//   else if ((ramp_up == 0) && (signal <= -75))
//    ramp_up = 1;
//
//    // Save the results.
//     printf("In: %i    Out: %i   Last: %i \n", in_data.data, out_data.data, (int)out_data.last);
//    // fprintf(fp,"%i %i %i\n",  out_data.data.real(), out_data.data.imag(), (int)out_data.last);
//  }
//  fclose(fp);
//
// //  printf ("Comparing against output data \n");
// //  if (system("diff -w out.dat out.gold.dat")) {
//
//  // fprintf(stdout, "*******************************************\n");
//  // fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
//  // fprintf(stdout, "*******************************************\n");
// //     return 1;
// //  } else {
//  // fprintf(stdout, "*******************************************\n");
//  // fprintf(stdout, "PASS: The output matches the golden output!\n");
//  // fprintf(stdout, "*******************************************\n");
// //     return 0;
// //  }
//}