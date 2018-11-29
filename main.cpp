#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main() {

  // initialize EM calculator with input files
  ExpMax em("initY.txt", "initX.txt", "data.txt", "meanings.txt");
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