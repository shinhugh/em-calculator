#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main() {

  // TODO REMOVE BELOW
  std::cout << "\n\n\n\n\nENTERING MAIN\n\n";
  // TODO REMOVE ABOVE

  ExpMax em("initY.txt", "initX.txt", "data.txt", "meanings.txt");

  // TODO REMOVE BELOW
  std::cout << __PRETTY_FUNCTION__ << ":\n";
  std::cout << "CHECKPOINT A" << "\n\n";
  // TODO REMOVE ABOVE

  std::cout << "David is most likely to "
    << em.mostProbVal("David", "Book3") << " Book 3.\n";

  return 0;
}