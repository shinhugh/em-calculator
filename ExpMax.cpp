#include "ExpMax.h"

ExpMax::ExpMax(std::string initY_file, std::string initX_file,
  std::string data_file) {

  // parse 3 files into vectors and pass into EM constructor

  // TODO: parse initY
  // TODO: parse initX
  // TODO: parse data

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