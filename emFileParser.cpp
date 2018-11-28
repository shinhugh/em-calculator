#include "emFileParser.h"

std::vector<double> parseInitY(std::string filename) {

  std::vector<std::vector<double> > initY_uf
    = parseFileDouble(filename, WORDBREAK);
  std::vector<double> initY(initY_uf.size(), 0);

  for(int i = 0; i < initY.size(); i++) {
    initY[i] = initY_uf[i][0];
  }

  return initY;
}


std::vector<std::vector<std::vector<double> > >
  parseInitX(std::string filename) {

  std::vector<std::vector<double> > initX_uf
    = parseFileDouble(filename, WORDBREAK, , ); // TODO
}


std::vector<std::vector<unsigned short> >
  parseData(std::string filename) {

  // TODO
}