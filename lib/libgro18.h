#ifndef HEL_WRAPPER_H
#define HEL_WRAPPER_H

extern "C" {
void rank(void *scores, unsigned char*known_key, int nb_subkey, int bins,
          double *rank_min, double *rank_max,
          double *time_rank);
}
#endif
