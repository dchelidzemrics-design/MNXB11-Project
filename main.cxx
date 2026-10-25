#include "DataExtraction.h"
#include "Observation.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
  
  // Make a vector containing the observation data from the parsed dataset
  std::vector<Observation> observation_vector{parse_observation("datasets/ParsedData.csv")};
  
  // Add this data to a tree .root file that is created in the local 
  // directory 
  write_observation(observation_vector, "temperature_tree.root");

  return 0;

}
