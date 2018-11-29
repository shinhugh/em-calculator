#include "ExpMax.h"

ExpMax::ExpMax(std::string initY_file, std::string initX_file,
  std::string data_file, std::string meaning_file) {

  // parse 4 files into vectors and pass into EM constructor

  // parse all sample, parameter, and input names
  // store all sample and parameter names in upper case
  this->parseMeanings(meaning_file);

  std::vector<double> initY = this->parseInitY(initY_file);
  k = initY.size();

  std::vector<std::vector<std::vector<double> > > initX
    = this->parseInitX(initX_file);

  std::vector<std::vector<unsigned short> > data
    = this->parseData(data_file);

  calculator = new EM(initY, initX, data);

  calculator->iterateFull();
}



ExpMax::~ExpMax() {
  delete calculator;
}



std::string ExpMax::mostProbVal(std::string sampleName,
  std::string paramName) {

  // translate sampleName & paramName to all upper case
  std::string sampleName_uc = toUpper(sampleName);
  std::string paramName_uc = toUpper(paramName);

  // if specified sample/param doesn't exist,
  // return INVALID_NAME
  if(sampleID.find(sampleName_uc) == sampleID.end()
    || paramID.find(paramName_uc) == paramID.end()) {
    return INVALID_NAME;
  }

  int t = sampleID[sampleName_uc];
  int c = paramID[paramName_uc];

  return inputID[ calculator->mostProbVal(t, c) ];
}



std::vector<double> ExpMax::parseInitY(std::string filename) {

  std::vector<std::vector<double> > initY_uf
    = parseFileDouble(filename, WORDBREAK);
  std::vector<double> initY(initY_uf.size(), 0);

  for(int i = 0; i < static_cast<int>(initY.size()); i++) {
    initY[i] = initY_uf[i][0];
  }

  return initY;
}



std::vector<std::vector<std::vector<double> > >
  ExpMax::parseInitX(std::string filename) {

  std::vector<std::vector<double> > initX_uf
    = parseFileDouble(filename, WORDBREAK);
  std::vector<std::vector<std::vector<double> > >
    initX(k, std::vector<std::vector<double> >
    (n, std::vector<double>(m, 0)));

  for(int i = 0; i < k; i++) {
    for(int c = 0; c < n; c++) {
      for(int j = 0; j < m; j++) {
        initX[i][c][j] = initX_uf[(i * n) + c][j];
      }
    }
  }

  return initX;
}



std::vector<std::vector<unsigned short> > ExpMax::parseData
  (std::string filename) {

  std::vector<std::vector<int> > data_uf
    = parseFileInt(filename, WORDBREAK);

  // convert to unsigned short
  std::vector<std::vector<unsigned short> >
    data(data_uf.size(),
    std::vector<unsigned short>(data_uf[0].size(), 0));

  for(int t = 0; t < static_cast<int>(data_uf.size()); t++) {
    for(int c = 0; c < static_cast<int>(data_uf[0].size()); c++) {
      data[t][c] = (unsigned short) data_uf[t][c];
    }
  }

  return data;
}



void ExpMax::parseMeanings(std::string filename) {

  // order: categories, input meanings, sample names
  std::vector<std::vector<std::string> > uf
    = parseFileStr(filename, WORDBREAK);
  std::vector<std::string> allLines(uf.size(), "");
  for(int i = 0; i < static_cast<int>(uf.size()); i++) {
    allLines[i] = toUpper(uf[i][0]);
  }

  // search allLines for empty line: signifies end of segment
  int lineInd = 0;
  bool endOfSegment = false;

  std::vector<std::string> categories;
  std::vector<std::string> inputMeanings;
  std::vector<std::string> sampleNames;

  while(!endOfSegment) {
    categories.push_back(allLines[lineInd]);
    lineInd++;
    if(allLines[lineInd] == "") {
      endOfSegment = true;
      lineInd++;
    }
  }

  endOfSegment = false;

  while(!endOfSegment) {
    inputMeanings.push_back(allLines[lineInd]);
    lineInd++;
    if(allLines[lineInd] == "") {
      endOfSegment = true;
      lineInd++;
    }
  }

  endOfSegment = false;

  while(!endOfSegment) {
    sampleNames.push_back(allLines[lineInd]);
    lineInd++;
    if(lineInd == static_cast<int>(allLines.size())) {
      endOfSegment = true;
    }
  }

  // vectors categories, inputMeanings, and sampleNames are complete

  inputID = inputMeanings;

  for(int i = 0; i < static_cast<int>(categories.size()); i++) {
    paramID[ categories[i] ] = i;
  }

  for(int i = 0; i < static_cast<int>(sampleNames.size()); i++) {
    sampleID[ sampleNames[i] ] = i;
  }

  n = categories.size();
  m = inputMeanings.size();
  T = sampleNames.size();
}