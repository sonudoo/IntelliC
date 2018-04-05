IntelliC is a Machine Learning library written in C++. It is easy to use and doesn't have any dependencies.

##### Remember: Matrix is nothing but double dimensional Vector.

## Kaggle Data Downloader

A python script has been included to let you download Kaggle data directly from the terminal. This would be useful in case you want to deploy your model on cloud; you won't have to download from Kaggle and upload it to cloud, instead, you can directly download from Kaggle on cloud itself.

#### Version: > 3.4
#### Dependency: requests 
#### Usage: 

* Run the script using Python 3.4 or above.
```
	python3 kaggle_data_downloader.py
```


* Enter the complete URL of the file (Ex: https://www.kaggle.com/c/3136/download/train.csv) to be downloaded and then enter the Username and Password. Your download will start if login was successful.

## CSV Handler

This tool is used to handle CSV files. It can read directly from CSV file into a C++ Vector object. 

#### Dependency: None
#### Usage: 

* First include the file.

```
	#include "CSVHandler.cpp"
```

* Create an object of Class CSVHandler.
```
	CSVHandler c(const char *filename);
```

* Load the file into a Vector object. The first parameter can be Vector of type int, double, long long or string. The second parameter (label) is optional. 
```
	c.readCSV(vector <vector<string> > data, vector <string> label);
```

## DataAnalyzer

This tool is used to analyze the data. It can print the statistical information of data contained in a Vector (single-feature) or a Matrix (multiple-feature). In case of Matrix, each row must represent a data and each column must represent a feature.

#### Dependency: None
#### Usage: 

* First include the file.

```
	#include "DataAnalyzer.cpp"
```

* Create an object of Class DataAnalyzer. The parameter 'data' may be of type int, double, long long or string. Incase of string make sure that each element is parseable to double.
```
	DataAnalyzer <double> d(vector <vector <double> > data); // data may be Vector or Matrix. 
```

* Use the various methods of the object.
```
	d.printStats(int X); // Prints statitical information of column specified by X.
	d.printStats(int X, int Y); // Prints statitical information of column from X to Y.
	d.printAllStats(); // Prints statitical information of all columns.
	d.correlate(int X, int Y); // Returns the correlation between column X and Y.
	d.preview(); // Preview the data stored.
	d.printData(); // Prints the entire data in tabular form.
```


## DataTransform

This tool is used to transform data stored in Vectors. It can extract specific rows/columns and append/prepend rows/columns from/to Matrices (i.e double dimensional Vectors).

#### Dependency: None
#### Usage: 

* First include the file.

```
	#include "DataTransform.cpp"
```

* Create an object of Class DataTransform. The template parameter may be of type int, double, long long or string.
```
	DataTransform <double> dt;
```

* Use the various methods of the object. 'data' is a double dimensional Vector on which operation needs to be performed. It is passed as the first parameter of all the below mentioned functions. Its type must be same as that of template parameter. 
```
	dt.sliceColumn(vector <vector <double> > data, int start, int end); // Returns a Matrix containing columns from start till end (end is excluded).
	dt.sliceRow(vector <vector <double> > data, int start, int end);
	dt.slice(vector <vector <double> > data, int start_row, int end_row, int start_column, int end_column);
	dt.extractColumn(vector <vector <double> > data, int column_number); // Returns a single dimensional Vector containing the specified column data.
	dt.extractRow(vector <vector <double> > data, int row_number);
	dt.appendColumn(vector <vector <double> > data, int column); // Appends a column (Vector or Matrix) at the end. Number of rows must match.
	dt.prependColumn(vector <vector <double> > data, int column); // Prepends a column (single dimensional Vector only) at the beginning. Number of rows must match.
	dt.appendRow(vector <vector <double> > data, int rows);
	dt.parseDouble(vector <vector <double> > data); // Returns a Matrix with all elements converted to double. 
```

## Matrix

This is one of the most important library and supports Matrix (double dimensional Vector object) operations similar to MATLAB. Unlike others, it only supports double data type (i.e all operations can be performed on Matrix of type double). All functions are static.

#### Dependency: None
#### Usage: 

* Use the various operations directly. Here 'data' is a Matrix of type double.
```
	Matrix.isMatrix(vector <vector <double> > data); // Checks if all the rows have same number of column and vice-versa.
	Matrix.identity(int n); // Returns an identity matrix of dimensions NxN.
	Matrix.ones(int n, int m); // Returns Matrix of 1's of dimensions NxM.
	Matrix.zeros(int n, int m); // Returns Matrix of 0's of dimensions NxM.
	Matrix.random(int n, int m); // Returns Matrix of random doubles between -1 and 1 of dimensions NxM.
	Matrix.random(int n, int m, true); // Returns Matrix of random doubles between 0 and 1 of dimensions NxM.
	Matrix.transpose(vector <vector <double> > data); // Returns transpose of Input Matrix.
	Matrix.sum(vector <vector <double> > data); // Returns a vector containing column-wise sum of Input Matrix.
	Matrix.avg(vector <vector <double> > data); // Returns a vector containing column-wise mean of Input Matrix.
	Matrix.std(vector <vector <double> > data); // Returns a vector containing column-wise standard deviation of Input Matrix.
	Matrix.max(vector <vector <double> > data); // Returns a vector containing column-wise maximum of Input Matrix.
	Matrix.min(vector <vector <double> > data); // Returns a vector containing column-wise minimum of Input Matrix.
	Matrix.log(vector <vector <double> > data); // Return a Matrix with natural logarithm applied to each element.
	Matrix.sigmoid(vector <vector <double> > data); // Returns a Matrix with sigmoid function applied to each element.
	Matrix.normalize(vector <vector <double> > data); // Returns a Matix with all the elements normalized column-wise.
	Matrix.sum(vector <vector <double> > data, double c); // Returns a Matrix with 'c' added to each element.
	Matrix.prod(vector <vector <double> > data, double c); // Returns a Matrix with 'c' multiplied to each element.
	Matrix.pow(vector <vector <double> > data, int c); // Returns a Matrix with each element raised to 'c'.
	Matrix.sum(vector <vector <double> > data1, vector <vector <double> > data2); // Returns a Matrix with element-wise sum of two Matrix.
	Matrix.diff(vector <vector <double> > data1, data2); // Returns a Matrix with element-wise difference of two Matrix.
	Matrix.prod(vector <vector <double> > data1, vector <vector <double> > data2); // Returns a Matrix with element-wise product of two Matrix.
	Matrix.multiply(vector <vector <double> > data1, vector <vector <double> > data2); // Returns a Matrix which is the multiplication of two Input Matrix.
	Matrix.multiply(vector <vector <double> > data1, vector <double> data2); // Returns a Matrix which is the multiplication of a Matrix (data1) and Vector (data2).
	Matrix.upgrade(vector <vector <double> > data); // Converts a Vector to a single-columned Matrix.
	Matrix.determinant(vector <vector <double> > data); // Returns determinant of the Input Matrix.
	Matrix.inverse(vector <vector <double> > data); // Returns a Matrix which is the Inverse of the Input Matrix.
	Matrix.isSymmetric(vector <vector <double> > data); // Checks if the Input Matrix is Symmetric.
	Matrix.eig(vector <vector <double> > data, vector <vector <double> > eigen_vectors, vector <double> eigen_values); // Calculates the Eigen vectors and Eigen values of 'data' Matrix and stores them in eigen_vectors (Matrix) and eigen_values (Vector). Works only for Symmetric and Normal Input Matrix.
	Matrix.svd(vector <vector <double> > data, vector <vector <double> > U, vector <vector <double> > E, vector <vector <double> > V); // Calculates the Left Singular Vectors, Eigen values Matrix and Right Singular Vectors of 'data' Matrix and stores them in U (Matrix), E (Matrix) and V (Matrix). Works only for Symmetric and Normal Input Matrix.
	Matrix.pinverse(vector <vector <double> > data); // Returns a Matrix which is the pseudo-inverse of the Input Matrix.

```



## Vector

It supports operations on single dimensional Vectors (vector <double> data). Unlike others, it only supports double data type (i.e all operations can be performed on Matrix of type double). All functions are static.

#### Dependency: None
#### Usage: 

* Use the various operations directly. Here 'data' is a Vector of type double.
```
	Vector.ones(int n); // Returns Vector of 1's of dimension N.
	Vector.zeros(int n); // Returns Vector of 0's of dimension N.
	Vector.random(int n); // Returns Matrix of random doubles between -1 and 1 of dimension N.
	Vector.random(int n, true); // Returns Matrix of random doubles between 0 and 1 of dimension N.
	Vector.sum(vector <double> data); // Returns sum of all the elements
	Vector.avg(vector <double> data); // Returns average of all the elements
	Vector.max(vector <double> data); // Returns maximum of all the elements
	Vector.min(vector <double> data); // Returns minimum of all the elements
	Vector.log(vector <double> data); // Return a Vector with natural logarithm applied to each element.
	Vector.sigmoid(vector <double> data); // Returns a Vector with sigmoid function applied to each element.
	Vector.normalize(vector <double> data); // Returns a Vector with all the elements normalized.
	Vector.random_permutation(n); // Returns a Vector containing permuation of numbers from 1 to N.
	Vector.sum(vector <double> data, double c); // Returns a Vector with 'c' added to each element.
	Vector.prod(vector <double> data, double c); // Returns a Vector with 'c' multiplied to each element.
	Vector.pow(vector <double> data, int c); // Returns a Vector with each element raised to 'c'.
	Vector.sum(vector <double> data1, vector <double> data2); // Returns a Vector with element-wise sum of two Vector.
	Vector.diff(vector <double> data1, vector <double> data2); // Returns a Vector with element-wise difference of two Vector.
	Vector.prod(vector <double> data1, vector <double> data2); // Returns a Vector with element-wise product of two Vector.
	Vector.upgrade(vector <double> data); // Converts a Vector to a single-columned Matrix.
```

## Linear Regression

This is the library for Linear Regression model. It supports Gradient Descent with/without Regularization and Normal Equation with/without Normalization. 

#### Dependency: Vector.cpp, Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "LinearRegression.cpp"
```

* Create an object of Class LinearRegression. The third parameter is optional. Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.
```
	LinearRegression model(vector <vector <double> > X, vector <double> y, bool normalize); // X is the feature Matrix where each column is a feature. y is a Vector of predictions.
```

* Train the model by various methods.
```
	model.trainByGradientDescent(double alpha, bool printCost); // Trains the model by Gradient Descent algorithm. The first parameter is the learning rate and the second parameter is optional to check for convergence.
	model.trainByRegularizedGradientDescent(double alpha, double lambda, bool printCost); // The second parameter is the regularization parameter.
	model.trainByNormalEquation(); // Trains the model using Normal Equation method.
	model.trainByRegularizedNormalEquation(double lambda); // The only parameter is the regularization parameter.
	model.trainByRegularizedNormalEquation(); // Trains the model using Regularized Normal Equation. It automatically determines the best regularization parameter.
```

* Finally predict.
```
	model.predict(vector <vector <double> > X_p); // Returns a Vector containing prediction of y_p for each record in X_p.
```
## Logistic Regression

This is the library for Logistic Regression model. It supports Gradient Descent with/without Regularization. 

#### Dependency: Vector.cpp, Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "LogisticRegression.cpp"
```

* Create an object of Class LogisticRegression. The third parameter is optional.
```
	LogisticRegression model(vector <vector <double> > X, vector <double> y, bool normalize); // X is the feature Matrix where each column is a feature. y is a Vector of predictions.
```

* Train the model by various methods.
```
	model.trainByGradientDescent(double alpha, bool printCost); // Trains the model by Gradient Descent algorithm. The first parameter is the learning rate and the second parameter is optional to check for convergence.
	model.trainByRegularizedGradientDescent(double alpha, double lambda, bool printCost); // The second parameter is the regularization parameter.
```

* Finally predict.
```
	model.predict(vector <vector <double> > X_p); // Returns a Vector containing prediction of y_p for each record in X_p.
```

## Neural Network

This is the library for Neural Network model. It supports one input layer, one hidden layer and one output layer. It uses Backpropagation algorithm to train the model.

#### Dependency: Vector.cpp, Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "NeuralNetwork.cpp"
```

* Create an object of Class NeuralNetwork. The fourth parameter is optional.
```
	NeuralNetwork model(vector <vector <double> > X, vector <double> y, int H, bool normalize); // X is the feature Matrix where each column is a feature. y is a Vector of predictions. H is the number of activation units in the hidden layer.
```

* Train the model.
```
	model.trainByGradientDescent(double alpha, int loop, bool printCost); // Trains the model by Gradient Descent algorithm. The first parameter is the learning rate, the second parameter specifies number of loops of Gradient Descent the third parameter is optional to check for convergence.
```

* Finally predict.
```
	model.predict(vector <vector <double> > X_p); // Returns a Vector containing prediction of y_p for each record in X_p.
```

## Deep Neural Network

It is the extension of Neural Network model and supports multiple hidden layers. It also uses Backpropagation algorithm to train the model.

#### Dependency: Vector.cpp, Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "DeepNeuralNetwork.cpp"
```

* Create an object of Class DeepNeuralNetwork. The fourth parameter is optional.
```
	DeepNeuralNetwork model(vector <vector <double> > X, vector <double> y, vector <int> H, bool normalize); // X is the feature Matrix where each column is a feature. y is a Vector of predictions. H is a vector whose each element represents the number of activation units in each hidden layers.
```

* Train the model.
```
	model.trainByGradientDescent(double alpha, int loop, bool printCost); // Trains the model by Gradient Descent algorithm. The first parameter is the learning rate, the second parameter specifies number of loops of Gradient Descent the third parameter is optional to check for convergence.
```

* Finally predict.
```
	model.predict(vector <vector <double> > X_p); // Returns a Vector containing prediction of y_p for each record in X_p.
```

## Cluster

This is the library for K-Means Clustering algorithm.

#### Dependency: Vector.cpp, Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "Cluster.cpp"
```

* Create an object of Class Cluster.
```
	Cluster model(vector <vector <double> > X); // X is the feature Matrix where each column is a feature.
```

* Run the K-Means Clustering algorithm.
```
	model.cluster(int k, vector <vector <double> > centroids, vector <int> assigned_centroid, bool printCost); // 'k' is the number of clusters to divide the Input points into. The centroid's location is stored in 'centroids' Matrix. The idex of centroid assigned to each Input points is stored in Vector 'assigned_centroid'. The fourth parameter is optional to check for convergence.
```


## Anomaly Detection

This is the library for Anomaly Detection using Gaussian Distribution.

#### Dependency: Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "AnomalyDetection.cpp"
```

* Create an object of Class AnomalyDetection.
```
	AnomalyDetection model(vector <vector <double> > X); // X is the feature Matrix where each column is a feature.
```

* Predict the anomalies.
```
	model.predict(vector <vector <double> > X_p); // Returns a Vector containing the probabilities of each record being an anomaly.
	model.predict(vector <vector <double> > X_p, double threshold); // Provide a threshold between 0 and 1. Returns a binary Vector specifying whether a record is anomaly or not.
```


## Principal Component Analysis

This is the library for Principal Component Analysis. The library automatically normalizes the Input Matrix. So it is advised to apply PCA to the entire dataset (i.e training, validation and test set) at the same time. This will not cause any issues due to normalization.

#### Dependency: Matrix.cpp and DataTransform.cpp
#### Usage: 

* First include the file.

```
	#include "PCA.cpp"
```

* Create an object of Class PCA.
```
	PCA model(vector <vector <double> > X); // X is the feature Matrix where each column is a feature.
```

* Get the reduced dimensions.
```
	model.reduce(int k); // Returns a Matrix having K reduced features.
	model.getReduceMatrix(int k); // Returns the Matrix that was used for reduction to K features.
	model.retainedVariance(int k); // Returns the variance that is retained when the Matrix is reduced to K features.
```



