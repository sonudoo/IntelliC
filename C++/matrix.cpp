class Matrix{
private:
	bool isMatrix(const vector <vector <double> > &data){
		if(data.size()==0)	return true;
		int n = data[0].size();
		for(int i=1;i<data.size();i++){
			if(data[i].size()!=n)	return false;
		}
		return true;
	}
public:
	vector <vector <double> > identity(int n){
		vector <vector<double> > res;
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				if(i==j){
					row.push_back(1);
				}
				else{
					row.push_back(0);
				}
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > zeros(int n, int m){
		vector <vector<double> > res;
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<m;j++){
				row.push_back(0);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > ones(int n, int m){
		vector <vector<double> > res;
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<m;j++){
				row.push_back(1);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > random(int n, int m){
		vector <vector<double> > res;
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<m;j++){
				row.push_back(0);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > transpose(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the double dimension vector for dimension consistency\n";
		}
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		vector <vector <double> > v;
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<m;j++){
				row.push_back(data[j][i]);
			}
			v.push_back(row);
		}
		return v;
	}
	vector <vector <double> > sum(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the double dimension vector for dimension consistency\n";
		}
		if(data1.size()!=data2.size()){
			throw "Matrix dimensions must match for addition\n";
		}
		if(data1.size()==0)	return data1;
		if(data1[0].size()!=data2[0].size()){
			throw "Matrix dimensions must match for addition\n";
		}
		int m = data1.size();
		int n = data1[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(data1[i][j]+data2[i][j]);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > difference(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the double dimension vector for dimensional consistency\n";
		}
		if(data1.size()!=data2.size()){
			throw "Matrix dimensions must match for subtraction\n";
		}
		if(data1.size()==0)	return data1;
		if(data1[0].size()!=data2[0].size()){
			throw "Matrix dimensions must match for subtraction\n";
		}
		int m = data1.size();
		int n = data1[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(data1[i][j]-data2[i][j]);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > product(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the double dimension vector for dimensional consistency\n";
		}
		if(data1.size()!=data2.size()){
			throw "Matrix dimensions must match for subtraction\n";
		}
		if(data1.size()==0)	return data1;
		if(data1[0].size()!=data2[0].size()){
			throw "Matrix dimensions must match for subtraction\n";
		}
		int m = data1.size();
		int n = data1[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(data1[i][j]*data2[i][j]);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > multiply(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the double dimension vector for dimension consistency\n";
		}
		if(data1.size()==0)	return data1;
		if(data2.size()==0)	return data2;
		int m1 = data1.size();
		int n1 = data1[0].size();
		int m2 = data2.size();
		int n2 = data2[0].size();
		if(n1!=m2){
			throw "Matrix dimensions are incorrect for multiplication\n";
		}
		vector <vector <double> > res = zeros(m1,n2);
		for(int i=0;i<m1;i++){
			for(int j=0;j<n2;j++){
				for(int k=0;k<n1;k++){
					res[i][j] += data1[i][k]*data2[k][j];
				}
			}
		}
		return res;
	}
	vector <vector <double> > inverse(vector <vector <double> > data){// Here we copy the argument to parameter instead of reference. This is because we need to modify the data to calculate its inverse
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		if(m!=n){
			throw "Only square matrices are invertible\n";
		}
		vector <vector <double> > res = identity(n);

		//Gaussian elimination

		for(int j=0;j<n;j++){
			// Go Columnwise
			for(int i=0;i<n;i++){
				//For each element in the column
				if(i<j){
					if(data[i][j]==0)	continue;
					//If the current element is non-zero then search for the next non-zero element from (j+1)th row
					int exr = -1;
					for(int k=j;k<n;k++){
						if(data[k][j]!=0){
							exr = k;
							break;
						}
					}
					if(exr==-1){
						// All the rows in a column are zeroes.
						throw "The matrix is singular. Inverse doesn't exists\n";
					}
					//Subtract next non-zero row multiplied by required constant..
					double multiplier = data[i][j]/data[exr][j];
					for(int k=0;k<n;k++){
						data[i][k] = data[i][k] - (data[exr][k]*multiplier);
						res[i][k] = res[i][k] - (res[exr][k]*multiplier);
					}
				}
				else if(i>j){
					// There must be a element (j,j) which must be one already
					double multiplier = data[i][j];
					for(int k=0;k<n;k++){
						data[i][k] = data[i][k] - data[j][k]*multiplier;
						res[i][k] = res[i][k] - res[j][k]*multiplier;
					}
				}
				else{
					// i==j
					if(data[i][j]==0){
						// We need to exchange this row with some bottom row below the jth row as all the row above are already zeroes.
						int exr = -1;
						for(int k=j;k<m;k++){
							if(data[k][j]!=0){
								exr = k;
								break;
							}
						}
						if(exr==-1){
							// All the rows in a column are zeroes.
							throw "The matrix is singular. Inverse doesn't exists\n";
						}
						for(int k=0;k<n;k++){
							//Add row
							data[i][k] += data[exr][k];
							res[i][k] += res[exr][k];
						}
					}
					double multiplier = 1/data[i][j];
					for(int k=0;k<n;k++){
						data[i][k] *= multiplier;
						res[i][k] *= multiplier;
					}
				}
				
			}
		}
		return res;
	}
};