#include "DataExtraction.h"
#include "Analysis2.h"
#include "Observation.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
  
  // Make a vector containing the observation data from the parsed dataset
  std::vector<Observation> observation_vector{parse_observation("datasets/parseddata.csv")};
  
  // Add this data to a tree .root file that is created in the local 
  // directory 
  write_observation(observation_vector, "temperature_tree.root");

  // Run analysis 2 using a temperature threshold of 25 degrees
  analysis2(observation_vector, 25.0, "Analysis2.root");

  return 0;

}
