#include <vector>
#include <time.h>
#include <stdio.h>
#include <utility>
#include "Vector.cpp"
#include "Matrix.cpp"
#include "DataTransform.cpp"


class NeuralNetwork{
private:
	vector <vector <double> > Y;
	vector <vector <double> > theta1;
	vector <vector <double> > theta2;
	vector <double> theta1_bias;
	vector <double> theta2_bias;
	vector <vector <double> > input_neurons;
	vector <vector <double> > hidden_neurons;
	vector <vector <double> > output_neurons;
	vector <double> avg;
	vector <double> std;
	int n;
	int m;
	int input_layer_size;
	int hidden_layer_size;
	int output_layer_size;
	bool isNormalized;
	double cost(){
		vector <double> v1 = Matrix::sum(Matrix::prod(Y, Matrix::log(output_neurons)));
		vector <double> v2 = Matrix::sum(Matrix::prod(Matrix::diff(Matrix::ones(m, output_layer_size) , Y),Matrix::log(Matrix::diff(Matrix::ones(m, output_layer_size) , output_neurons))));
		return (-1.0/m)*Vector::sum(Vector::sum(v1,v2));
	}
	void forwardPropagate(){
		
		vector <vector <double> > v = Matrix::multiply(input_neurons,theta1);
		for(int i=0;i<hidden_layer_size;i++){
			for(int j=0;j<m;j++){
				v[j][i] += theta1_bias[i];
			}
		}
		hidden_neurons = Matrix::sigmoid(v);

		v = Matrix::multiply(hidden_neurons,theta2);
		for(int i=0;i<output_layer_size;i++){
			for(int j=0;j<m;j++){
				v[j][i] += theta2_bias[i];
			}
		}
		output_neurons = Matrix::sigmoid(v);
	}
	void backPropagate(double alpha){
		vector <vector <double> > d_output = Matrix::prod(Matrix::diff(Y,output_neurons),Matrix::prod(output_neurons, Matrix::diff(Matrix::ones(m,output_layer_size),output_neurons)));
		vector <vector <double> > d_hidden = Matrix::prod(Matrix::multiply(d_output, Matrix::transpose(theta2)), Matrix::prod(hidden_neurons, Matrix::diff(Matrix::ones(m,hidden_layer_size),hidden_neurons)));
		theta2 = Matrix::sum(theta2, Matrix::prod(Matrix::multiply(Matrix::transpose(hidden_neurons),d_output), alpha));
		theta2_bias = Vector::sum(theta2_bias, Vector::prod(Matrix::sum(d_output), alpha));
		theta1 = Matrix::sum(theta1, Matrix::prod(Matrix::multiply(Matrix::transpose(input_neurons),d_hidden), alpha));
		theta1_bias = Vector::sum(theta1_bias, Vector::prod(Matrix::sum(d_hidden), alpha));
	}
public:
	NeuralNetwork(const vector <vector <double> > &data, const vector <vector<double> > &label, int hidden, bool normalize = false){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		if(!Matrix::isMatrix(label))	throw "Y must be a matrix (i.e double dimensional vector)\n";

		m = data.size();
		n = data[0].size();
		input_layer_size = n;
		output_layer_size = label[0].size();
		hidden_layer_size = hidden;

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
			input_neurons = Matrix::normalize(data);
			isNormalized = true;
		}
		else{
			input_neurons = data;
			isNormalized = false;
		}

		Y = label;
	}
	double trainByGradientDescent(double alpha, int loop, bool printCost = false){
		if(!isNormalized){
			printf("Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.\n");
		}

		theta1 = Matrix::random(input_layer_size, hidden_layer_size, true);
		theta2 = Matrix::random(hidden_layer_size, output_layer_size, true);
		theta1_bias = Vector::random(hidden_layer_size, true);
		theta2_bias = Vector::random(output_layer_size, true);

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
		X_p = Matrix::multiply(X_p, theta1);
		for(int i=0;i<hidden_layer_size;i++){
			for(int j=0;j<X_p.size();j++){
				X_p[j][i] += theta1_bias[i];
			}
		}
		X_p = Matrix::sigmoid(X_p);
		X_p = Matrix::multiply(X_p,theta2);
		for(int i=0;i<output_layer_size;i++){
			for(int j=0;j<X_p.size();j++){
				X_p[j][i] += theta2_bias[i];
			}
		}

		return Matrix::sigmoid(X_p);
	}
};