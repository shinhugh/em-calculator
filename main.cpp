#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main() {

  ExpMax em("initY.txt", "initX.txt", "data.txt", "meanings.txt");
  std::cout << "David is most likely to "
    << em.mostProbVal("David", "Book3") << " Book 3.\n";

  return 0;
}