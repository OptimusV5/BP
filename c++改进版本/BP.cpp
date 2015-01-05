#include "BP.h"
#include <ostream>
#include <iostream>

BP::BP(int inputSize, int hiddenSize, int outputSize)
{
	this->inputSize = inputSize;
	this->hiddenSize = hiddenSize;
	this->outputSize = outputSize;
	hidden = new double[hiddenSize];
	output = new double[outputSize];
	randomizeWeights();
}

void BP::train(double input[][64], double output[][10], double eta,int size)
{
	this->eta = eta;
	for (int t = 0; t < size; t++)
	{
		double sums[2][200];
		for (int i = 0; i < hiddenSize; i++)
		{
			sums[0][i] = 0;
			for (int j = 0; j < inputSize; j++)
			{
				sums[0][i] += weights[0][j][i] * input[t][j];
			}
			hidden[i] = sigmoid(sums[0][i]);			
		}
		for (int i = 0; i < outputSize; i++)
		{
			sums[1][i] = 0;
			for (int j = 0; j < hiddenSize; j++)
			{
				sums[1][i] += weights[1][j][i] * hidden[j];
			}
			this->output[i] = sigmoid(sums[1][i]);
		}
		for (int i = 0; i <outputSize; i++)
		{
			deltas[1][i] = this->sigmoid_(sums[1][i]) * (output[t][i] - this->output[i]);
			//cout << deltas[1][i] << " " << output[t][i] << " " << this->output[i] << endl;
		}
		for (int i = 0; i < hiddenSize; i++)
		{
			double sum = 0;
			for (int j = 0; j < outputSize; j++)
			{
				sum += weights[1][i][j] * deltas[1][j];
			}
			deltas[0][i] = this->sigmoid_(sums[0][i]) * sum;
		}
		for (int i = 0; i < hiddenSize; i++)
		{
			for (int j = 0; j < outputSize; j++)
			{
				weights[1][i][j] = weights[1][i][j] + eta * hidden[i] * deltas[1][j];
			}
		}
		for (int i = 0; i < inputSize; i++)
		{
			for (int j = 0; j < hiddenSize; j++)
			{
				weights[0][i][j] = weights[0][i][j] + eta * input[t][i] * deltas[0][j];
			}
		}
	}
}

int BP::test(double inData[64])
{
	for (int i = 0; i < hiddenSize; i++)
	{
		double sum = 0;
		for (int j = 0; j < inputSize; j++)
		{
			sum += weights[0][j][i] * inData[j];
		}
		hidden[i] = sigmoid(sum);
	}
	for (int i = 0; i < outputSize; i++)
	{
		double sum = 0;
		for (int j = 0; j < hiddenSize; j++)
		{
			sum += weights[1][j][i] * hidden[j];
		}
		output[i] = sigmoid(sum);
	}
	int temp = 0;
	for (int j = 0; j < 10; j++)
	{
		if (output[temp] < output[j])
			temp = j;
	}
	return temp;
}
double BP::sigmoid(double val)
{
	return 1.0 / (1.0 + exp(-val));
}

double BP::sigmoid_(double x)
{
	return exp(-x) / ((1 + exp(-x)) * (1 + exp(-x)));
}

void BP::randomizeWeights()
{
	srand((int)time(0));
	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < hiddenSize; j++) {
			weights[0][i][j] = static_cast<double>(rand()) / RAND_MAX;	
	}
	}
	for (int i = 0; i < hiddenSize; i++) {
		for (int j = 0; j < outputSize; j++)
			weights[1][i][j] = static_cast<double>(rand()) / RAND_MAX;
	}
}