#include "ExpMax.h"

ExpMax::ExpMax(std::string initY_file, std::string initX_file,
  std::string data_file, std::string meaning_file) {

  // parse 4 files into vectors and pass into EM constructor

  // parse all sample, parameter, and input names
  this->parseMeanings(meaning_file);

  // parse initial P(Y = i)
  std::vector<double> initY = this->parseInitY(initY_file);
  k = initY.size();

  // parse initial P(X_c = j | Y = i)
  std::vector<std::vector<std::vector<double> > > initX
    = this->parseInitX(initX_file);

  // parse data
  std::vector<std::vector<unsigned short> > data
    = this->parseData(data_file);

  // create calculator
  calculator = new EM(initY, initX, data);

  // iterate until convergence
  calculator->iterateFull();
}

ExpMax::ExpMax(int hiddenParamCount, std::string data_file,
  std::string meaning_file) {

  k = hiddenParamCount;

  // parse meanings file
  this->parseMeanings(meaning_file);

  // create initY vector from given k
  std::vector<double> initY(k, ((double) 1) / k);

  // create initX vector from given k, n, and m
  std::vector<std::vector<std::vector<double> > > initX
    (k, std::vector<std::vector<double> >
    (n, std::vector<double>
    (m, ((double) 1) / m)));

  // parse data
  std::vector<std::vector<unsigned short> > data
    = this->parseData(data_file);

  calculator = new EM(initY, initX, data);

  calculator->iterateFull();
}



ExpMax::~ExpMax() {
  delete calculator;
}



std::pair<bool, std::string> ExpMax::mostProbVal
  (std::string sampleName, std::string paramName) {

  // translate sampleName & paramName to all upper case
  std::string sampleName_uc = toUpper(sampleName);
  std::string paramName_uc = toUpper(paramName);

  // if specified sample/param doesn't exist,
  // return INVALID_NAME
  if(sampleID.find(sampleName_uc) == sampleID.end()
    || paramID.find(paramName_uc) == paramID.end()) {
    return std::pair<bool, std::string>(DNE_BOOL, INVALID_NAME);
  }

  int t = sampleID[sampleName_uc];
  int c = paramID[paramName_uc];

  std::pair<bool, int> result = calculator->mostProbVal(t, c);
  std::string jName = inputID[ result.second - 1 ];

  return std::pair<bool, std::string>(result.first, jName);
}



std::vector<std::string> ExpMax::getSampleNames() {

  std::vector<std::string> output;

  std::map<std::string, int>::iterator iter = sampleID.begin();
  while(iter != sampleID.end()) {
    output.push_back(iter->first);
    iter++;
  }

  return output;
}



std::vector<std::string> ExpMax::getCategoryNames() {

  std::vector<std::string> output;

  std::map<std::string, int>::iterator iter = paramID.begin();
  while(iter != paramID.end()) {
    output.push_back(iter->first);
    iter++;
  }

  return output;
}



std::vector<std::string> ExpMax::getInputNames() {
  return inputID;
}



std::vector<std::string> ExpMax::noResponseList
  (std::string sampleName) {

    std::vector<int> params
      = calculator->noResponseList(sampleID[sampleName]);
    std::vector<std::string> output;
    for(int i = 0; i < static_cast<int>(params.size()); i++) {
      output.push_back(paramID_rev[params[i]]);
    }

    return output;
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

    std::string currLine = "";

    for(int j = 0; j < static_cast<int>(uf[i].size()); j++) {
      if(j > 0) {
        currLine += WORDBREAK;
      }
      currLine.append(toUpper(uf[i][j]));
    }
    allLines[i] = currLine;
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
    paramID_rev.push_back(categories[i]);
  }

  for(int i = 0; i < static_cast<int>(sampleNames.size()); i++) {
    sampleID[ sampleNames[i] ] = i;
  }

  n = categories.size();
  m = inputMeanings.size();
  T = sampleNames.size();
}