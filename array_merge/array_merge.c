#include "array_merge.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../mergesort/mergesort.h"

int* array_merge(int num_arrays, int* sizes, int** values) {
  // This is obviously broken. It has the right type, though, eh?
  int flatsize = 0;
  for(int i = 0; i < num_arrays; i++) {
    flatsize += sizes[i];
  }

  int* flatvalues = (int*) calloc(flatsize+1, sizeof(int));

  for(int i = 0, flatpos = 1; i < num_arrays; i++) {
    memcpy(flatvalues + flatpos, values[i], sizeof(int)*sizes[i]);
    flatpos += sizes[i];
    // for(int j = 0; j < sizes[i]; j++) { //TODO use memcpy instead
    //   flatvalues[flatpos++] = values[i][j];
    // }
  }

  mergesort(flatsize, flatvalues + 1);

  int dedupsize = 1;
  
  for(int i = 1; i < flatsize + 1; i++) {
    if(!(i > 1 && flatvalues[i-1] == flatvalues[i])) {
      flatvalues[dedupsize++] = flatvalues[i];
    }
  }

  flatvalues[0] = dedupsize - 1;

  flatvalues = (int*) realloc(flatvalues, sizeof(int)*(dedupsize));


  return flatvalues;

}
