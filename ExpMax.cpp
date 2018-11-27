#include "ExpMax.h"

ExpMax::ExpMax(std::string initY_file, std::string initX_file,
  std::string data_file) {

  // parse 3 files into vectors and pass into EM constructor

  std::vector<std::vector<double> > initY_uf
    = parseFileDouble(initY_file, WORDBREAK);
  std::vector<double> initY(initY_uf.size(), 0);
  for(int i = 0; i < initY.size(); i++) {
    initY[i] = initY_uf[i][0];
  }

  std::vector<std::vector<double> > initX_uf
    = parseFileDouble(initY_file, WORDBREAK);
  // TODO

  std::vector<std::string> data_uf
    = parseFileStr(data_file, POST_NAME);
  // TODO

  // TODO: parse all sample, parameter, and input names
  // store all sample and paarameter names in upper case

  calculator(initY, initX, data);
  calculator.iterateFull();
}



std::string ExpMax::mostProbVal(std::string sampleName,
  std::string paramName) {

  // translate sampleName & paramName to all upper case
  std::string sampleName_uc = toUpper(sampleName);
  std::string paramName_uc = toUpper(paramName);

  // if specified sample/param doesn't exist,
  // return INVALID_NAME
  if(sampleID.find(sampleName_uc) == std::map::end
    || paramID.find(paramName_uc) == std::map::end) {
    return INVALID_NAME;
  }

  int t = sampleID[sampleName_uc];
  int c = paramID[paramName_uc];

  return inputID[ calculator.mostProbVal(t, c) ];
}