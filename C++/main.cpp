#include <iostream>
#include "DecisionTreeClassifier.cpp"
#include "CSVHandler.cpp"
#include "DataAnalyzer.cpp"
#include "Vector.cpp"
int main(){
	vector <vector <double> > data;
	CSVHandler c("data_banknote_authentication.csv");
	c.readCSV(data);
	DataTransform <double> dt;
	vector <vector <double> > X = dt.sliceColumn(data, 0, 4);
	vector <double> y = dt.extractColumn(data, 4);

	vector <int> rand = Vector::random_permutation(1371);
	vector <vector <double> > X_train;
	vector <double> y_train;
	vector <vector <double> > X_val;
	vector <double> y_val;

	for(int i=0;i<1200;i++){
		X_train.push_back(X[rand[i]-1]);
		y_train.push_back(y[rand[i]-1]);
	}
	for(int i=1200;i<1300;i++){
		X_val.push_back(X[rand[i]-1]);
		y_val.push_back(y[rand[i]-1]);
	}
	DecisionTreeClassifier model(X_train,y_train);
	model.train(5, 10);
	vector <double> y_p = model.predict(X_val);
	double cnt = 0;
	for(int i=0;i<y_p.size();i++){
		printf("%lf %lf\n",y_val[i],y_p[i]);
		if(y_val[i]==y_p[i]){
			cnt += 1;
		}
	}
	printf("Accuracy: %lf\n",cnt/y_p.size());
	return 0;
}