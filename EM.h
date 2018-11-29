#ifndef EM_H
#define EM_H

#define GUARANTEED_TRUE 1.0
#define GUARANTEED_FALSE 0.0
#define LL_CHANGE_THRES 0.00001

#include <vector>
#include <cmath>

/*
 * expectation maximization calculator for model with one
 * parent Y and many children X
*/
class EM {

private:

  // # of possible Y values
  // same as size of pY
  int k;

  // # of Y's children X_c
  // upper cap on c
  // same as size of pX's middle vector
  int n;

  // # of possible X values
  // same as size of pX's innermost vector
  // must be in range of unsigned short
  int m;

  // # of samples/people in data
  int T;

  // data
  // outer vector: T samples/people
  // inner vector: n inputs on each subject/topic/title
  // value: 0 ~ (m - 1)
  //   value 0 is pre-assigned to no input
  //   assign each value 1 ~ (m - 1) to some meaning
  //   i.e. if n inputs = n movies
  //        -> 0 = not seen, 1 = dislike, 2 = like
  std::vector<std::vector<unsigned short> > data;

  // P(Y = i) values
  // i = index
  // i.e. pY[0] = P(Y = 0)
  std::vector<double> pY;

  // P(X_c = j | Y = i)
  // outermost vector: parent (Y) value
  // middle vector: child (X) #
  // innermost vector: child (X) value
  // pX[i][c][j]
  // i.e. pX[0][2][4] = P(X_2 = 4 | Y = 0)
  std::vector<std::vector<std::vector<double> > > pX;

  // # of iterations completed
  int iterCount;

  // calculate log-likelihood
  double logLikelihood();

  // calculate probability P(Y = i | sample t)
  double pYGivSample(int i, int t);

public:

  // constructor
  // initY: initial P(Y = i) values
  // initX: initial P(X = 1 | Y = i) values
  // data: all data
  // look above for format of vectors
  EM(std::vector<double> initY,
    std::vector<std::vector<std::vector<double> > > initX,
    std::vector<std::vector<unsigned short> > data);

  // set P(Y = i) values
  // resets iteration count to 0
  void setPY(std::vector<double> pYUpdate);

  // set P(X_c = j | Y = i) values
  // resets iteration count to 0
  void setPX(std::vector<std::vector<std::vector<double> > > pXUpdate);

  // set data inputs
  // resets iteration count to 0
  void setData(std::vector<std::vector<unsigned short> > dataUpdate);

  // run an expectation + maximization step once, updating the parameters
  void iterate();

  // repeatedly run iterate() until parameters are seeing minimal change
  // will iterate at least once
  // returns # of times iterate() was called
  int iterateFull();

  // calculate probability P(X_c = j | sample) for a specific sample
  // probability that sample t produces X_c = j
  // j =/= 0
  // returns 1 if data holds X_c = j
  // returns 0 if data holds X_c = some value besides 0 and j
  // returns probability if data holds X_c = 0 (no input)
  // i.e. probability that a person likes movie 4: P(X_4 = 2 | sample)
  double pSampleProduceVal(int t, int c, int j);

  // determine what value of j maximizes P(X_c = j | sample)
  // which value of j is most likely for X_c given a sample
  // use pSampleProduceVal()
  int mostProbVal(int t, int c);
};

#endif