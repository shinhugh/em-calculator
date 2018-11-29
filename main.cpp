#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main() {

  ExpMax em("initY.txt", "initX.txt", "data.txt", "meanings.txt");

  std::string name1 = "David";
  std::string category1 = "Book1";
  std::string category2 = "Book2";
  std::string category3 = "Book3";

  // David dislikes Book1
  std::cout << name1 << " is most likely to "
    << em.mostProbVal(name1, category1) << " " << category1 << ".\n";

  // David likes Book2
  std::cout << name1 << " is most likely to "
    << em.mostProbVal(name1, category2) << " " << category2 << ".\n";

  // David hasn't read Book3
  std::cout << name1 << " is most likely to "
    << em.mostProbVal(name1, category3) << " " << category3 << ".\n";

  return 0;
}