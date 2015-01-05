#ifndef B_P_
#define B_P_
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

class BP
{
public:
	BP(int, int, int);
	void train(double[][64], double[][10],double eta,int);
	int test(double[64]);
private:
	double sigmoid(double);
	double sigmoid_(double);
	void randomizeWeights();
	double* hidden;
	double* output;
	double deltas[2][200];
	double weights[2][200][200];
	double eta;
	int inputSize;
	int outputSize;
	int hiddenSize;
};
#endif
