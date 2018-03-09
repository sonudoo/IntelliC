#include "csv_handler.cpp"
#include "data_analyzer.cpp"
#include "data_transform.cpp"
#include "LogisticRegression.cpp"
#include "vector.cpp"
#include "matrix.cpp"
using namespace std;
int main(){
	CSVHandler c("train.csv");
	vector <vector <double> > data;
	c.readCSV(data);
	vector <vector <double> > X_train;
	vector <double> y_train;
	vector <vector <double> > X_val;
	int m_train = data.size();
	for(int i=0;i<m_train;i++){
		X_train.push_back(data[i]);
		y_train.push_back(data[i][0]);
	}
	DataTransform <double> dt;
	X_train = dt.sliceColumn(X_train,1,6);
	X_val = dt.sliceColumn(X_val,1,6);

	LogisticRegression model(X_train, y_train, true);
	model.trainByRegularizedGradientDescent(0.001,0);


	
	CSVHandler c1("test.csv");
	vector <vector <double> > data1;
	c1.readCSV(data1);
	for(int i=0;i<data1.size();i++){
		X_val.push_back(data1[i]);
	}

	printf("sdsvd\n");

	vector <double> y_p = model.predict(X_val);

	freopen("stdout.txt","w",stdout);

	for(int i=0;i<y_p.size();i++){
		printf("%d,%d\n",i+892,(int)y_p[i]);
	}

	return 0;
}