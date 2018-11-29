#include <iostream>
#include "ExpMax.h"

/*
 * Command line interface for expecation-maximization utility.
 * Only use the ExpMax interface.
 */
int main() {

  ExpMax em("temporary", "temporary", "temporary", "temporary");
  em.mostProbVal("temporary", "temporary");

  return 0;
}