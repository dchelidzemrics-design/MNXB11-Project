#include "DataExtraction.h"
#include "Observation.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
  std::cout << "I am just a code template, you need to implement the "
               "functionality you want to use yourself!"
            << std::endl;

  std::cout << "We were passed " << argc
            << " command line arguments, the first of which was " << argv[0]
            << std::endl;
  std::cout << "With a good CLI library, we could use the command line "
               "arguments to make a useful program."
            << std::endl;

  // Make a vector containing the observation data from the parsed dataset
  std::vector<Observation> observation_vector{parse_observation("datasets/ParsedData.csv")};
  
  // Add this data to a tree .root file that is created in the local 
  // directory 
  write_observation(observation_vector, "temperature_tree.root");

  return 0;

}
