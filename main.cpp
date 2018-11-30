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


  // USING ALL 4 FILES
  std::cout << "\nUsing all 4 files:\n";

  // initialize EM calculator with input files
  ExpMax em1(initY_file, initX_file, data_file, meanings_file);

  // pull the people/sample names and category names
  std::vector<std::string> names1 = em1.getSampleNames();
  std::vector<std::string> categories1 = em1.getCategoryNames();

  std::cout << std::endl;

  // list all people/sample names
  std::cout << "Names:\n";
  for(int i = 0; i < static_cast<int>(names1.size()); i++) {
    std::cout << "- " << names1[i] << std::endl;
  }

  std::cout << std::endl;

  // list all category names
  std::cout << "Categories:\n";
  for(int i = 0; i < static_cast<int>(categories1.size()); i++) {
    std::cout << "- " << categories1[i] << std::endl;
  }

  std::cout << std::endl;

  // feel free to change person number, as long as index
  // isn't out of bounds
  std::string currName = names1[2];

  // categories person did not respond to
  std::vector<std::string> noResponses1 = em1.noResponseList(currName);
  std::cout << currName << " did not respond to:\n";
  for(int i = 0; i < static_cast<int>(noResponses1.size()); i++) {
    std::cout << noResponses1[i] << std::endl;
  }
  std::cout << std::endl;

  // print given response/most likely response for all categories
  for(int i = 0; i < static_cast<int>(categories1.size()); i++) {
    std::pair<bool, std::string> result
      = em1.mostProbVal(currName, categories1[i]);
    if(result.first) {
      std::cout << currName << " responded that " << categories1[i]
        << " goes well with " << result.second << " moods.\n";
    } else {
      std::cout << currName << " is most likely to feel that "
        << categories1[i] << " goes well with " << result.second
        << " moods.\n";
    }
  }

  std::cout << "\n\n";



  // USING JUST MEANINGS & DATA FILES
  std::cout << "Using just meanings and data files:\n";

  // initialize EM calculator with input files
  ExpMax em2(4, data_file, meanings_file);

  // pull the people/sample names and category names
  std::vector<std::string> names2 = em2.getSampleNames();
  std::vector<std::string> categories2 = em2.getCategoryNames();

  std::cout << std::endl;

  // list all people/sample names
  std::cout << "Names:\n";
  for(int i = 0; i < static_cast<int>(names2.size()); i++) {
    std::cout << "- " << names2[i] << std::endl;
  }

  std::cout << std::endl;

  // list all category names
  std::cout << "Categories:\n";
  for(int i = 0; i < static_cast<int>(categories2.size()); i++) {
    std::cout << "- " << categories2[i] << std::endl;
  }

  std::cout << std::endl;

  // feel free to change person number, as long as index
  // isn't out of bounds
  currName = names2[2];

  // categories person did not respond to
  std::vector<std::string> noResponses2 = em2.noResponseList(currName);
  std::cout << currName << " did not respond to:\n";
  for(int i = 0; i < static_cast<int>(noResponses2.size()); i++) {
    std::cout << noResponses2[i] << std::endl;
  }
  std::cout << std::endl;

  // print given response/most likely response for all categories
  for(int i = 0; i < static_cast<int>(categories2.size()); i++) {
    std::pair<bool, std::string> result
      = em2.mostProbVal(currName, categories2[i]);
    if(result.first) {
      std::cout << currName << " responded that " << categories2[i]
        << " goes well with " << result.second << " moods.\n";
    } else {
      std::cout << currName << " is most likely to feel that "
        << categories2[i] << " goes well with " << result.second
        << " moods.\n";
    }
  }

  return 0;
}