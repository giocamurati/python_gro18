#!/usr/bin/python3

# Giovanni Camurati
# camurati@eurecom.fr

import ctypes
import numpy as np
lib = ctypes.cdll.LoadLibrary('libgro18.so')

def rank(scores, knownkey, bins):

    # conversion to be sure about types
    scores = np.array(scores).flatten()
    scores = np.nan_to_num(scores)
    scores_p = ctypes.c_void_p(scores.ctypes.data)
    
    knownkey = np.array(knownkey, dtype=ctypes.c_ubyte)
    nb_subkey = np.zeros((1), dtype=ctypes.c_int)
    nb_subkey = len(knownkey)

    nb_bins = np.zeros((1), dtype=ctypes.c_int)
    nb_bins = bins

    rank_min = np.zeros((1), dtype=ctypes.c_double)
    rank_rounded = np.zeros((1), dtype=ctypes.c_double)
    rank_max = np.zeros((1), dtype=ctypes.c_double)
    time_rank = np.zeros((1), dtype=ctypes.c_double)

    # call to the library function
    lib.rank(scores_p, knownkey.ctypes,
            nb_subkey, nb_bins, rank_min.ctypes, rank_max.ctypes,
            time_rank.ctypes)

    return rank_min, rank_max, time_rank

def example():
    # example mainly taken from ../hel_lib/main_example.cpp
    from example_data import scores, pt1, pt2, ct1, ct2
   
    knownkey = [0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f]

    bins = 4096

    print("")
    rank_min, rank_max, time_rank = rank(scores, knownkey, bins)
    print(f"rank_min: {rank_min}, rank_max: {rank_max}, time_rank: {time_rank} (s)")
  
if __name__ == "__main__":
    example()
    
