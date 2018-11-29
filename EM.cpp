#include "EM.h"

EM::EM(std::vector<double> initY,
  std::vector<std::vector<std::vector<double> > > initX,
  std::vector<std::vector<unsigned short> > data) {

  k = static_cast<int>(initY.size());
  n = static_cast<int>(initX[0].size());
  m = static_cast<int>(initX[0][0].size()) + 1;
  T = data.size();

  pY = initY;

  std::vector<std::vector<std::vector<double> > > initX_f
    (k, std::vector<std::vector<double> >
    (n, std::vector<double>
    (m + 1, 0)));
  for(int i = 0; i < k; i++) {
    for(int c = 0; c < n; c++) {
      for(int j = 1; j < m; j++) {
        initX_f[i][c][j] = initX[i][c][j - 1];
      }
    }
  }

  pX = initX_f;

  this->data = data;

  iterCount = 0;
}



void EM::setPY(std::vector<double> pYUpdate) {

  for(int i = 0; i < k; i++) {
    pY[i] = pYUpdate[i];
  }

  iterCount = 0;
}



void EM::setPX(std::vector<std::vector<std::vector<double> > >
  pXUpdate) {

  for(int i = 0; i < k; i++) {
    for(int c = 0; c < n; c++) {
      for(int j = 1; j < m; j++) {
        pX[i][c][j] = pXUpdate[i][c][j - 1];
      }
    }
  }

  iterCount = 0;
}



void EM::setData(std::vector<std::vector<unsigned short> > dataUpdate) {

  for(int t = 0; t < T; t++) {
    for(int c = 0; c < n; c++) {
      data[t][c] = dataUpdate[t][c];
    }
  }

  iterCount = 0;
}



void EM::iterate() {

  // updated pY and pX vectors
  std::vector<double> updatedPY(k, 0);
  std::vector<std::vector<std::vector<double> > >
    updatedPX(k, std::vector<std::vector<double> >
    (n, std::vector<double>(m, 0)));

  // update pY
  for(int i = 0; i < k; i++) {

    double sum = 0;
    for(int t = 0; t < T; t++) {
      sum += pYGivSample(i, t);
    }
    updatedPY[i] = sum / T;
  }

  // update pX
  for(int i = 0; i < k; i++) {

    for(int c = 0; c < n; c++) {

      for(int j = 1; j < m; j++) {

        double sum1 = 0;
        double sum2 = 0;
        for(int t = 0; t < T; t++) {

          if(data[t][c] != 0) {
            if(data[t][c] == j) {
              sum1 += pYGivSample(i, t);
            }
          }

          else {
            sum1 += (pYGivSample(i, t) * pX[i][c][j]);
          }

          sum2 += pYGivSample(i, t);
        }

        updatedPX[i][c][j] = sum1 / sum2;
      }
    }
  }

  // publish updated probabilities to object
  pY = updatedPY;
  pX = updatedPX;
}



int EM::iterateFull() {

  // repeatedly call iterate() until parameters see minimal
  // change
  // gauge by calculating log-likelihood
  int count = 0;
  bool done = false;
  double lastLL = this->logLikelihood();

  // TODO REMOVE BELOW
  std::cout << __PRETTY_FUNCTION__ << ":\n";
  std::cout << "CHECKPOINT A" << "\n\n";
  // TODO REMOVE ABOVE

  while(!done) {
    this->iterate();
    double newLL = this->logLikelihood();

    // TODO REMOVE BELOW
    std::cout << __PRETTY_FUNCTION__ << ":\n";
    std::cout << lastLL << ", " << newLL << "\n";
    std::cout << std::abs(lastLL - newLL) << "\n\n";
    // TODO REMOVE ABOVE

    if(std::abs(lastLL - newLL) < LL_CHANGE_THRES) {
      done = true;

      // TODO REMOVE BELOW
      std::cout << __PRETTY_FUNCTION__ << ":\n";
      std::cout << "CHECKPOINT B" << "\n\n";
      // TODO REMOVE ABOVE
    }
    lastLL = newLL;
    count++;
  }

  // TODO REMOVE BELOW
  std::cout << __PRETTY_FUNCTION__ << ":\n";
  std::cout << "CHECKPOINT C" << "\n\n";
  // TODO REMOVE ABOVE

  // return # of iterations done by this call
  return count;
}



/*
double EM::logLikelihood() {
  double sum1 = 0;
  for(int t = 0; t < T; t++) {

    double sum2 = 0;
    for(int i = 0; i < k; i++) {

      double product = 1;
      for(int c = 0; c < n; c++) {

        if(data[t][c] != 0) {
          product *= pX[c][i][ data[t][c] ];
        }
      }

      product *= pY[i];
      sum2 += product;
    }

    sum1 += log(sum2);
  }

  return sum1 / T;
}
*/



double EM::logLikelihood() {
  double sum1 = 0;
  for(int t = 0; t < T; t++) {

    double product1 = 1;
    for(int c = 0; c < n; c++) {

      if(data[t][c] != 0) {

        double sum2 = 0;
        for(int i = 0; i < k; i++) {
          sum2 += pY[i] * pX[i][c][ data[t][c] ];
        }

        product1 *= sum2;
      }
    }

    sum1 += log(product1);
  }

  return sum1 / T;
}



double EM::pSampleProduceVal(int t, int c, int j) {

  // j = 0 -> no input
  // probability of producing no input doesn't make sense
  if(j == 0) {
    return INVALID_INPUT;
  }

  // if sample holds input for specified X_c and it matches j,
  // return 100%
  if(data[t][c] == j) {
    return GUARANTEED_TRUE;
  }

  // if sample doesn't hold input for specified X_c, calculate
  // probability that the sample would generate X_c = j
  else if(data[t][c] == 0) {
    double sum1 = 0;
    for(int i = 0; i < k; i++) {

      double denominator = 0;
      double numerator = 0;

      for(int ii = 0; ii < k; ii++) {

        double product = 1;
        for(int cc = 0; cc < n; cc++) {

          product *= pX[ii][cc][ data[t][cc] ];
        }
        product *= pY[ii];

        denominator += product;

        if(ii == i) {
          numerator = product;
        }
      }

      double fraction1 = numerator / denominator;

      sum1 += fraction1 * pX[i][c][j];
    }

    return sum1;
  }

  // if sample holds input for specified X_c and it doesn't match
  // j, return 0%
  else {
    return GUARANTEED_FALSE;
  }
}



int EM::mostProbVal(int t, int c) {

  double maxP = 0;
  int maxJ = -1;
  for(int j = 1; j < m; j++) {
    double currP = this->pSampleProduceVal(t, c, j);
    if(currP > maxP) {
      maxP = currP;
      maxJ = j;
    }
  }

  return maxJ;
}



double EM::pYGivSample(int i, int t) {

  double denominator = 0;
  double numerator = 0;
  for(int ii = 0; ii < k; ii++) {

    double product = 1;
    for(int c = 0; c < n; c++) {

      if(data[t][c] != 0) {
        product *= pX[ii][c][ data[t][c] ];
      }
    }

    product *= pY[ii];

    denominator += product;

    if(ii == i) {
      numerator = product;
    }
  }

  return numerator / denominator;
}