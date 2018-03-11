
#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _TIME_H_
	#include <time.h>
	#define _TIME_H_
#endif

#ifndef _STDIO_H_
	#include <stdio.h>
	#define _STDIO_H_
#endif

#ifndef _UTILITY_
	#include <utility>
	#define _UTILITY_
#endif


#include "Vector.cpp"
#include "Matrix.cpp"
#include "Datatransform.cpp"


class DeepNeuralNetwork{
private:
	vector <vector <double> > X;
	vector <vector <double> > X_t;
	vector <vector <double> > Y;
	vector <vector <vector <double> > > theta;
	vector <vector <double> > theta_bias;
	vector <vector <vector <double> > > neurons; //Triple dimension: This is because there are 'm' neural network each having same theta.
	/*
		0th layer is the Matrix A itself. 
		Total number of layers = hidden layer count + 2
		theta[i][j][k] = Between the ith and (i+1)th layer. j is in (i+1)th layer. k is in ith layer.
		neurons[i][j][k] = i is the ith layer. 0th layer is A itself. j is the training data number and k is the feature number
	*/
	vector <double> avg;
	vector <double> std;
	int n;
	int m;
	int input_layer_size;
	int output_layer_size;
	int hidden_layer_count;
	int layer_count;
	int input_layer;
	int output_layer;
	bool isNormalized;
	DataTransform <double> _d;
	double sigmoid(double z){
		return 1.0/(1+exp(-z));
	}
	static double randDouble(bool positiveOnly = false){
		if(rand()%2==0 || positiveOnly)
			return (double)rand()/(double)RAND_MAX;
		else
			return -(double)rand()/(double)RAND_MAX;
	}
	double cost(){
		vector <double> v1 = Matrix::sum(Matrix::prod(Y, Matrix::log(neurons[output_layer])));
		vector <double> v2 = Matrix::sum(Matrix::prod(Matrix::diff(Matrix::ones(Y.size(), Y[0].size()) , Y),Matrix::log(Matrix::diff(Matrix::ones(m, output_layer_size) , neurons[output_layer]))));
		return (-1.0/m)*Vector::sum(Vector::sum(v1,v2));
	}
	void forwardPropagate(){
		for(int l=1;l<=output_layer;l++){
			neurons[l] = Matrix::multiply(neurons[l-1], theta[l-1]);
			for(int i=0;i<neurons[l][0].size();i++){
				for(int j=0;j<m;j++){
					neurons[l][j][i] += theta_bias[l-1][i];
				}
			}
			neurons[l] = Matrix::sigmoid(neurons[l]);
		}
	}
	void backPropagate(double alpha){
		vector <vector <vector <double> > > d; vector <vector<double> > d_output, d_hidden;
		d_output = Matrix::prod(Matrix::diff(Y,neurons[output_layer]),Matrix::prod(neurons[output_layer],Matrix::diff(Matrix::ones(m,output_layer_size),neurons[output_layer])));
		d.push_back(d_output);
		int last_d = 0;
		for(int j=output_layer-1;j>=1;j--){
			d_hidden = Matrix::prod(Matrix::multiply(d[last_d], Matrix::transpose(theta[j])),Matrix::prod(neurons[j],Matrix::diff(Matrix::ones(m, neurons[j][0].size()),neurons[j])));
			d.push_back(d_hidden);
			last_d++;
		}
		last_d = 0;
		for(int j=output_layer-1;j>=0;j--){
			theta[j] = Matrix::sum(theta[j], Matrix::prod(Matrix::multiply(Matrix::transpose(neurons[j]),d[last_d]), alpha));
			theta_bias[j] = Vector::sum(theta_bias[j], Vector::prod(Matrix::sum(d[last_d]), alpha));
			last_d++;
		}
	}
public:
	DeepNeuralNetwork(const vector <vector <double> > &data, const vector <vector<double> > &label, const vector <int> &hidden_units, bool normalize = false){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		if(!Matrix::isMatrix(label))	throw "Y must be a matrix (i.e double dimensional vector)\n";

		m = data.size();
		n = data[0].size();
		input_layer_size = n;
		output_layer_size = label[0].size();
		hidden_layer_count = hidden_units.size();
		layer_count = hidden_layer_count + 2;
		input_layer = 0;
		output_layer = layer_count-1;

		for(int i=0;i<m;i++){
			for(int j=0;j<output_layer_size;j++){
				if(fabs(label[i][j]-1)>0.000001 && fabs(label[i][j])>0.000001){
					throw "Y must be either 0 or 1.\n";
				}
			}
		}
		if(normalize){
			avg = Matrix::avg(data);
			std = Matrix::std(data);
			neurons.push_back(Matrix::normalize(data));
			isNormalized = true;
		}
		else{
			neurons.push_back(data);
			isNormalized = false;
		}

		Y = label;


		//Initialize everything to random values
		int curr = input_layer_size;
		for(int l=0;l<hidden_layer_count;l++){
			theta.push_back(Matrix::random(curr, hidden_units[l], true));
			theta_bias.push_back(Vector::random(hidden_units[l], true));
			curr = hidden_units[l];
		}
		theta_bias.push_back(Vector::random(output_layer_size, true));
		theta.push_back(Matrix::random(curr, output_layer_size, true));


		vector <vector<double> > v;
		for(int i=1;i<=hidden_layer_count;i++){
			v = Matrix::sigmoid(Matrix::multiply(neurons[i-1], theta[i-1]));
			neurons.push_back(v);
		}
		v = Matrix::sigmoid(Matrix::multiply(neurons[output_layer-1], theta[output_layer-1]));
		neurons.push_back(v);
	}
	double trainByGradientDescent(double alpha,  int loop, bool printCost = false){
		if(!isNormalized){
			printf("Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.\n");
		}
		srand(time(0));
		for(int i=0;i<theta.size();i++){
			for(int j=0;j<theta[i].size();j++){
				for(int k=0;k<theta[i][j].size();k++){
					theta[i][j][k] = randDouble(true);
				}
			}
		}
		double prev_cost = 1000000*m, curr_cost;
		while(loop--){

			forwardPropagate();
			backPropagate(alpha);

			curr_cost = cost();
			if(printCost)
				printf("Cost: %lf Difference: %lf\n",curr_cost,prev_cost-curr_cost);
			prev_cost = curr_cost;
		}
		return prev_cost;
	}

	vector <vector<double> > predict(vector <vector<double> > X_p){ //Pass a copy since we will modify it.
		// The matrix is automatically verified by rest of the functions.
		if(isNormalized){
			// Renormalize using the same mean and standard deviation.
			for(int i=0;i<n;i++){
				for(int j=0;j<X_p.size();j++){
					X_p[j][i] -= avg[i];
					X_p[j][i] /= std[i];
				}
			}
		}
		for(int l=1;l<=output_layer;l++){
			X_p = Matrix::multiply(X_p, theta[l-1]);
			for(int i=0;i<neurons[l][0].size();i++){
				for(int j=0;j<X_p.size();j++){
					X_p[j][i] += theta_bias[l-1][i];
				}
			}
			X_p = Matrix::sigmoid(X_p);
		}
		return X_p;
	}
};