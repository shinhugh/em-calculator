#define IN_DIR "/"
#define INIT_Y "_initY.txt"
#define INIT_X "_initX.txt"
#define DATA "_data.txt"
#define MEANINGS "_meanings.txt"

#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main(int argc, char** argv) {

  // must specify file names prefix
  if(argc == 1) {
    std::cout << "Specify name of file set." << std::endl;
    return 0;
  }

  // file names prefix
  std::string fileSetName(argv[1]);
  // file location directory
  std::string fileDir("./sampleinput"); // <- change if necessary

  // setting up file names
  std::string initY_file = fileDir + IN_DIR + fileSetName
    + INIT_Y;
  std::string initX_file = fileDir + IN_DIR + fileSetName
    + INIT_X;
  std::string data_file = fileDir + IN_DIR + fileSetName
    + DATA;
  std::string meanings_file = fileDir + IN_DIR + fileSetName
    + MEANINGS;

  // initialize EM calculator with input files
  ExpMax em(initY_file, initX_file, data_file, meanings_file);

  // pull the people/sample names and category names
  std::vector<std::string> names = em.getSampleNames();
  std::vector<std::string> categories = em.getCategoryNames();

  std::cout << std::endl;

  // list all people/sample names
  std::cout << "Names:\n";
  for(int i = 0; i < static_cast<int>(names.size()); i++) {
    std::cout << "- " << names[i] << std::endl;
  }

  std::cout << std::endl;

  // list all category names
  std::cout << "Categories:\n";
  for(int i = 0; i < static_cast<int>(categories.size()); i++) {
    std::cout << "- " << categories[i] << std::endl;
  }

  std::cout << std::endl;

  // feel free to change person number, as long as index
  // isn't out of bounds
  std::string currName = names[2];

  // categories person did not respond to
  std::vector<std::string> noResponses = em.noResponseList(currName);
  std::cout << currName << " did not respond to:\n";
  for(int i = 0; i < static_cast<int>(noResponses.size()); i++) {
    std::cout << noResponses[i] << std::endl;
  }
  std::cout << std::endl;

  // print given response/most likely response for all categories
  for(int i = 0; i < static_cast<int>(categories.size()); i++) {
    std::pair<bool, std::string> result
      = em.mostProbVal(currName, categories[i]);
    if(result.first) {
      std::cout << currName << " responded that " << categories[i]
        << " goes well with " << result.second << " moods.\n";
    } else {
      std::cout << currName << " is most likely to feel that "
        << categories[i] << " goes well with " << result.second
        << " moods.\n";
    }
  }

  return 0;
}