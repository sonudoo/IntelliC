IntelliC is a Machine Learning library written in C++. It is easy to use and doesn't have any dependencies.

#### Remember: Matrix is nothing but double dimensional Vector.

# Kaggle Data Downloader

A python script has been included to let you download Kaggle data directly from the terminal. This would be useful in case you want to deploy your model on cloud; you won't have to download from Kaggle and upload it to cloud, instead, you can directly download from Kaggle on cloud itself.

### Version: > 3.4
### Dependency: requests 
### Usage: 

* Run the script using Python 3.4 or above.
```
	python3 kaggle_data_downloader.py
```


* Enter the complete URL of the file (Ex: https://www.kaggle.com/c/3136/download/train.csv) to be downloaded and then enter the Username and Password. Your download will start if login was successful.

# CSV Handler

This tool is used to handle CSV files. It can read directly from CSV file into a C++ Vector object. 

### Dependency: None
### Usage: 

* First include the file.

```
	#include "CSVHandler.cpp"
```

* Create an object of Class CSVHandler.
```
	CSVHandler c("sample.csv");
```

* Load the file into a Vector object.
```
	vector <string> label;
	vector <vector<string> > data;
	c.readCSV(data, label);
```

* The second parameter (label) is optional. The first parameter can be Vector of type int, double, long long or string.

# DataAnalyzer

This tool is used to analyze the data. It can print the statistical information of data contained in a Vector (single-feature) or a Matrix (multiple-feature). In case of Matrix, each row must represent a data and each column must represent a feature.

### Dependency: None
### Usage: 

* First include the file.

```
	#include "DataAnalyzer.cpp"
```

* Create an object of Class DataAnalyzer. The parameter 'data' may be of type int, double, long long or string. Incase of string make sure that each element is parseable to double.
```
	DataAnalyzer <double> d(data); // data may be Vector or Matrix. 
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


# DataTransform

This tool is used to transform data stored in Vectors. It can extract specific rows/columns and append/prepend rows/columns from/to Matrices (i.e double dimensional Vectors).

### Dependency: None
### Usage: 

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
	dt.sliceColumn(data, start, end); // Returns a Matrix containing columns from start till end (end is excluded).
	dt.sliceRow(data, start, end);
	dt.slice(data, start_row, end_row, start_column, end_column);
	dt.extractColumn(data, column_number); // Returns a single dimensional Vector containing the specified column data.
	dt.extractRow(data, row_number);
	dt.appendColumn(data, column); // Appends a column (Vector or Matrix) at the end. Number of rows must match.
	dt.prependColumn(data, column); // Prepends a column (single dimensional Vector only) at the beginning. Number of rows must match.
	dt.appendRow(data, rows);
	dt.parseDouble(data); // Returns a Matrix with all elements converted to double. 
```





