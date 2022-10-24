// Original code by Vincent Grosso + Some parts from HEL
// Modified by Giovanni Camurati to make it into a library and to expose it
// to Python

#include <NTL/ZZXFactoring.h>
#include <NTL/RR.h>
#include "libgro18.h"

using namespace std;
using namespace NTL;

void rank(void *scores, unsigned char*known_key, int nb_subkey, int bins,
          double *rank_min, double *rank_max,
          double *time_rank) {

  // Initialization
  int i, j;
  int size_subkey = 1<<8;
  int nb_bin2 = bins; //1<<12;

  double log_proba_key=0;
  
  double **log_proba = NULL; // will contain the initial log probas
  int *real_key =
      NULL; // will contain the real key (optional for key enumeration)

  real_key = (int *)malloc(nb_subkey * sizeof(int));
  for (i = 0; i < nb_subkey; i++) {
    real_key[i] = (int)known_key[i];
  }
  
  log_proba = (double **)malloc(nb_subkey * sizeof(double *));

  for (i = 0; i < nb_subkey; i++) {
    log_proba[i] = (double *)malloc(size_subkey * sizeof(double));
  }

  for (int i = 0; i < nb_subkey; i++)
    for (int j = 0; j < size_subkey; j++)
      log_proba[i][j] = ((double *)scores)[i * size_subkey + j];

  ///search for min
  double mini=0;
  double maxi=log_proba[0][0];

  for (i = 0 ; i < nb_subkey ; i++)
  {
    for(j=0; j<size_subkey; j++)
    {
      if(!isinf(log_proba[i][j]))
      {
        if(log_proba[i][j]<mini)
          mini=log_proba[i][j];
        if(maxi<log_proba[i][j])
          maxi=log_proba[i][j];
      }
    }
  }

  ZZ max_rank,min_rank;
  
  ZZ two;
  two = 2; // used to compute the bound_start and bound_end using two^(integer)
  // note that the bounds can be any number (not especially a power of two)
  RR rval_to_print; // to convert some ZZ to RR
  RR rr_log2 = log(conv<RR>(two)); // log2 as RR
  
  //OURS [CARDIS18]
  double step2=(maxi-mini)/(nb_bin2-1);
  ///build histograms
  ZZX* hists2 = new ZZX[nb_subkey*2 -1];
  for (i = 0 ; i < nb_subkey ; i++)
  {
    for(j=0; j<size_subkey; j++)
    {
      if(!isinf(log_proba[i][j]))
      {
        uint64_t index=(uint64_t)floor((log_proba[i][j]-mini+step2/2)/step2);
        SetCoeff(hists2[i],index,coeff(hists2[i],index)+1);
      }
    }
    log_proba_key+=(log_proba[i][real_key[i]]-mini);
  }
  cout << log_proba_key/step2<<"\n";

  int start=0;
  int stop=nb_subkey;
  int current_hist=nb_subkey;
  clock_t start_time=clock();
  while(stop>1)
  {
    for( i = start ; i < start+stop ; i+=2)
    {
      ZZX tmp_hist = hists2[start+i]*hists2[start+i+1]; //next convolutions
      for(int j=0; j<deg(tmp_hist); j+=2)
        SetCoeff(hists2[current_hist], j/2, coeff(tmp_hist, j)+coeff(tmp_hist, j+1) );
      if(deg(tmp_hist)%2==0)
        SetCoeff(hists2[current_hist], deg(tmp_hist)/2, coeff(tmp_hist, deg(tmp_hist)));
      current_hist++;
    }
    start+=stop/2;
    stop/=2;
  }
  int64_t bin_upper=round((log_proba_key+(nb_subkey*log2(nb_subkey)+2*nb_subkey)*step2/4)/(step2*nb_subkey))+1;
  int64_t bin_lower=round((log_proba_key-(nb_subkey*log2(nb_subkey)+2*nb_subkey)*step2/4)/(step2*nb_subkey));
  if(bin_upper>deg(hists2[2*nb_subkey-2 ]))///the upper bin is higher than the number of bins
  {
    min_rank=1;
  }
  else
  {
    min_rank=0;
    for(int64_t lo=bin_upper; lo<=deg(hists2[2*nb_subkey-2 ]); lo++)
      min_rank+=coeff(hists2[2*nb_subkey-2 ],lo);
    if(min_rank==0)
      min_rank=1;
  }
  if(bin_lower<0)
  {
    bin_lower=0;
  }
  max_rank=0;
  for(int64_t lo=bin_lower; lo<=deg(hists2[2*nb_subkey-2 ]); lo++)
    max_rank+=coeff(hists2[2*nb_subkey-2 ],lo);
  clock_t stop_time=clock();
  double seconds = (double)(stop_time - start_time) / CLOCKS_PER_SEC;
  *time_rank = seconds;
        
  double x;
  double &xref = x;
  conv(xref, conv<RR>(log(min_rank)) / rr_log2);
  *rank_min = x;
  conv(xref, conv<RR>(log(max_rank)) / rr_log2);
  *rank_max = x;

  rval_to_print = conv<RR>(min_rank);
  cout << "min: 2^" << log(rval_to_print) / rr_log2 << endl;
  rval_to_print = conv<RR>(max_rank);
  cout << "max: 2^" << log(rval_to_print) / rr_log2 << endl;
  cout << "time enum: " << *time_rank << " seconds" << endl;
  cout << endl
       << endl;

  delete[] hists2;
  delete[] log_proba;
  
  return;
}
