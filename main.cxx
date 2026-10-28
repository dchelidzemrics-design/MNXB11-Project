#include "DataExtraction.h"
#include "Analysis2.h"
#include "Observation.h"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
  
  // Make a vector containing the observation data from the parsed dataset
  std::vector<Observation> observation_vector{parse_observation("datasets/parseddata.csv")};

  if (argc < 2) {

    std::cout << "Creating temperature_tree.root..." << std::endl;

    // Add this data to a tree .root file that is created in the local 
    // directory 
    write_observation(observation_vector, "temperature_tree.root");

    std::cout << "Done" << std::endl;

  }

  if (argc > 1) {

    if (std::string(argv[1]) == "1") {

      std::cout << "Performing analysis 1..." << std::endl;

      // Analysis 1 code here 
      // Run analysis 2 using a temperature threshold of 25 degrees
      analysis2(observation_vector, 25.0, "Analysis2.root");

    } else if (std::string(argv[1]) == "2") {

      std::cout << "Performing analysis 2..." << std::endl;

      // Analysis 2 code here 

    } else if (std::string(argv[1]) == "3") {

      std::cout << "Performing analysis 3..." << std::endl;

      // Analysis 3 code here 

    } else if (std::string(argv[1]) == "4") {

      std::cout << "Performing analysis 4..." << std::endl;

      // Analysis 4 code here 

    } else {

      std::cout << "Input must be 1, 2, 3 or 4..." << std::endl;
      std::cout << "Exiting..." << std::endl;

    }

  }

  return 0;

}
