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

  if(argc == 1) {
    std::cout << "Specify name of file set." << std::endl;
    return 0;
  }

  // file names
  std::string fileSetName(argv[1]);
  std::string fileDir("./inputfiles");

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



  // initialize strings for testing
  std::string name1 = names[3]; // David
  std::string category1 = categories[0];
  std::string category2 = categories[1];
  std::string category3 = categories[2];



  std::cout << std::endl;



  // David dislikes Book1
  std::pair<bool, std::string> book1 = em.mostProbVal(name1, category1);
  if(book1.first == true) {
    // if David already gave an input
    std::cout << name1 << " responded that he/she did " << book1.second
      << " " << category1 << ".\n";
  }
  else {
    // if David gave no input
    std::cout << name1 << " is most likely to "
      << book1.second << " " << category1 << ".\n";
  }



  // David likes Book2
  std::pair<bool, std::string> book2 = em.mostProbVal(name1, category2);
  if(book2.first == true) {
    // if David already gave an input
    std::cout << name1 << " responded that he/she did " << book2.second
      << " " << category2 << ".\n";
  }
  else {
    // if David gave no input
    std::cout << name1 << " is most likely to "
      << book2.second << " " << category2 << ".\n";
  }



  // David hasn't read Book3
  std::pair<bool, std::string> book3 = em.mostProbVal(name1, category3);
  if(book3.first == true) {
    // if David already gave an input
    std::cout << name1 << " responded that he/she did " << book3.second
      << " " << category3 << ".\n";
  }
  else {
    // if David gave no input
    std::cout << name1 << " is most likely to "
      << book3.second << " " << category3 << ".\n";
  }

  return 0;
}