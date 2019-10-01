#include "array_merge.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../mergesort/mergesort.h"

int* array_merge(int num_arrays, int* sizes, int** values) {
  int flatsize = 0; // Will be size of flattened array
  
  // Loop through each array in values and add it's size to flatsize
  for(int i = 0; i < num_arrays; i++) {
    flatsize += sizes[i];
  }

  // Allocate array for flattened values + initial size int
  int* flatvalues = (int*) calloc(flatsize+1, sizeof(int));

  // Loop through each array in values and copying its values into the flatvalues array
  for(int i = 0, flatpos = 1; i < num_arrays; i++) {
    memcpy(flatvalues + flatpos, values[i], sizeof(int)*sizes[i]);
    flatpos += sizes[i]; // Incrememnt flatpos by size of current array
  }

  // Sort the portion of flatvalues except for the initial size int
  mergesort(flatsize, flatvalues + 1);

  // Keep track of deduplicated size
  int dedupsize = 1;
  
  // Loop through values in flatvalues
  for(int i = 1; i < flatsize + 1; i++) {
    // Check if not first in array and current value not equal to last value
    if(!(i > 1 && flatvalues[i-1] == flatvalues[i])) {
      // if true, not alredy in deduped values, move to current dedup position and increment dedup position/size
      flatvalues[dedupsize++] = flatvalues[i];
    }
  }

  // Set initial size int in array to number of following values
  flatvalues[0] = dedupsize - 1;

  // Reallocate flatvalues to keep just the deduplicated values, freeing the rest of the array
  flatvalues = (int*) realloc(flatvalues, sizeof(int)*(dedupsize));


  return flatvalues;

}
