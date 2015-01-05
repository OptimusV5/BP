#include <iostream>
#include <fstream>
#include "BP.h"
#define INSIZE 64
double inputs[3900][INSIZE];
double outputs[3900][10];
double testin[1517][INSIZE];
vector<int> testout;
int inputSize = 0;
int testinSize = 0;
void read_and_normalization(FILE*,int flag);
int main()
{
	
	FILE* fp;
	if ((fp = fopen("E:\\digitstra.txt", "r")) == NULL) {
		printf("cannot open file: digitstra.txt\n");
		exit(0);
	}
	read_and_normalization(fp,1);
	fclose(fp);
	if ((fp = fopen("E:\\digitstest.txt", "r")) == NULL) {
		printf("cannot open file: digitstes.txt\n");
		exit(0);
	}
	read_and_normalization(fp,2);
	fclose(fp);
	BP bp(64, 21, 10);
	for (int i = 0; i < 500; i++)
		bp.train(inputs, outputs, 1.4, inputSize - 1);
	int total = 0;
	for (int i = 0; i < testinSize; i++)
	{
		int out = bp.test(testin[i]);
		if (out == testout[i])
		total++;
	}
	cout << static_cast<double>(total) / testinSize << " " << total << " / " << testinSize << endl;
}

void read_and_normalization(FILE* fp,int flag)
{
	while (!feof(fp)) {
		for (int i = 0; i < INSIZE; i++)
		{
			if (flag == 1)
				fscanf(fp, "%lf,", &inputs[inputSize][i]);
			else
			{
				fscanf(fp, "%lf,", &testin[testinSize][i]);
			}
		}
		double max = 0;
		double min = 16;
		if (flag == 1) {
			for (int i = 0; i < 64; i++)
			{
				if (max < inputs[inputSize][i])
					max = inputs[inputSize][i];
				if (min > inputs[inputSize][i])
					min = inputs[inputSize][i];
			}
			if (max != min)
			{
				for (int i = 0; i < 64; i++)
				{
					inputs[inputSize][i] = (inputs[inputSize][i] - min) / (max - min);
				}
			}
			else if (max != 0)
			{
				for (int i = 0; i < 64; i++)
				{
					inputs[inputSize][i] /= max;
				}
			}

		} else
		{
			for (int i = 0; i < 64; i++)
			{
				if (max < testin[testinSize][i])
					max = testin[testinSize][i];
				if (min > testin[testinSize][i])
					min = testin[testinSize][i];
			}
			if (max != min)
			{
				for (int i = 0; i < 64; i++)
				{
					testin[testinSize][i] = (testin[testinSize][i] - min) / (max - min);
				}
			}
			else if (max != 0)
			{
				for (int i = 0; i < 64; i++)
				{
					testin[testinSize][i] /= max;
				}
			}
			testinSize++;
		}
		int temp;
		fscanf(fp, "%d", &temp);
		if (flag == 1) {
			for (int i = 0; i < 10; i++)
			{
				if (i == static_cast<int>(temp)) {
					outputs[inputSize][i] = 1;
				}
				else
				{
					outputs[inputSize][i] = 0;
				}
			}
			inputSize++;
		} else
		{
			testout.push_back(temp);
		}
	}
}