
#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _TIME_H_
	#include <time.h>
	#define _TIME_H_
#endif

#ifndef _LIMITS_
	#include <limits>
	#define _LIMITS_
#endif

#ifndef _MATH_H_
	#include <math.h>
	#define _MATH_H_
#endif


#ifndef _STDLIB_H_
	#include <stdlib.h>
	#define _STDLIB_H_
#endif

class Matrix{
private:
	double randDouble(bool positiveOnly){
		if(rand()%2==0 || positiveOnly)
			return (double)rand()/(double)RAND_MAX;
		else
			return -(double)rand()/(double)RAND_MAX;
	}
	double power(double x, int n){
		double res = 1;
		while(n){
			if(n&1)
				res = res*x;
			x = x*x;
			n >>= 1;
		}
		return res;
	}
	double max(double x, double y){
		if(x>y)	return x;
		return y;
	}
	double min(double x, double y){
		if(x<y)	return x;
		return y;
	}
public:
	bool isMatrix(const vector <vector <double> > &data){
		if(data.size()==0)	return true;
		int n = data[0].size();
		for(int i=1;i<data.size();i++){
			if(data[i].size()!=n)	return false;
		}
		return true;
	}
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
	vector <vector <double> > random(int n, int m, bool positiveOnly = false){
		vector <vector<double> > res;
		srand(time(0));
		for(int i=0;i<n;i++){
			vector <double> row;
			for(int j=0;j<m;j++){
				row.push_back(randDouble(positiveOnly));
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > transpose(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
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
	vector <double> sum(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data.size()==0)	return res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<n;i++){
			double s = 0;
			for(int j=0;j<m;j++){
				s += data[j][i];
			}
			res.push_back(s);
		}
		return res;
	}
	vector <double> avg(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data.size()==0)	return res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<n;i++){
			double s = 0;
			for(int j=0;j<m;j++){
				s += data[j][i];
			}
			res.push_back(s/m);
		}
		return res;
	}
	vector <double> max(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data.size()==0)	return res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<n;i++){
			double s = -std::numeric_limits<double>::max();
			for(int j=0;j<m;j++){
				s = max(s, data[j][i]);
			}
			res.push_back(s);
		}
		return res;
	}
	vector <double> min(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data.size()==0)	return res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<n;i++){
			double s = std::numeric_limits<double>::max();
			for(int j=0;j<m;j++){
				s = min(s, data[j][i]);
			}
			res.push_back(s);
		}
		return res;
	}
	vector <double> std(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data.size()==0)	return res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<n;i++){
			double s = 0;
			double ss = 0;
			for(int j=0;j<m;j++){
				s += data[j][i];
				ss += data[j][i]*data[j][i];
			}
			res.push_back(sqrt((ss/m) - ((s*s)/(m*m))));
		}
		return res;
	}
	vector <vector <double> > normalize(const vector <vector <double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		if(data.size()==0)	return data;
		vector <double> sd = std(data);
		vector <double> ag = avg(data);
		vector <vector <double> > res;
		int n = data[0].size();
		int m = data.size();
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				if(sd[j]==0){
					throw "Normalization failed as all the rows in a column is same.\n";
				}
				row.push_back((data[i][j]-ag[j])/(sd[j]));
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > sum(const vector <vector <double> > &data, double c){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(data[i][j]+c);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > prod(const vector <vector <double> > &data, double c){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(data[i][j]*c);
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > pow(const vector <vector <double> > &data, int c){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		vector <vector <double> > res;
		for(int i=0;i<m;i++){
			vector <double> row;
			for(int j=0;j<n;j++){
				row.push_back(power(data[i][j], c));
			}
			res.push_back(row);
		}
		return res;
	}
	vector <vector <double> > sum(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
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
	vector <vector <double> > diff(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
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
	vector <vector <double> > prod(const vector <vector <double> > &data1, const vector <vector <double> > &data2){
		if(!isMatrix(data1) || !isMatrix(data2)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
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
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
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
	vector <double> multiply(const vector <vector <double> > &data1, const vector <double> &data2){
		if(!isMatrix(data1)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		vector <double> res;
		if(data1.size()==0)	return res;
		if(data2.size()==0)	return res;
		int m1 = data1.size();
		int n1 = data1[0].size();
		int m2 = data2.size();
		if(n1!=m2){
			throw "Matrix and vector dimensions are incorrect for multiplication\n";
		}
		for(int i=0;i<m1;i++){
			double s = 0;
			for(int j=0;j<n1;j++){
				s += data1[i][j]*data2[j];
			}
			res.push_back(s);
		}
		return res;
	}
	vector <vector <double> > upgrade(const vector <double> &data){
		vector <vector <double> > res;
		for(int i=0;i<data.size();i++){
			vector <double> row;
			row.push_back(data[i]);
			res.push_back(row);
		}
		return res;
	}
	double determinant(vector <vector <double> > data){// Here we copy the argument to parameter instead of reference. This is because we need to modify the data to calculate its inverse
		if(data.size()==0)	return 0;
		int m = data.size();
		int n = data[0].size();
		if(m!=n){
			throw "Determinants of square matrices can only be calculated.\n";
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%lf ",data[i][j]);
			}
			printf("\n");
		}
		//Gaussian jordan row-reduction elimination to form an upper-triangular matrix

		double det = 1;
		for(int j=0;j<n;j++){
			// Go Columnwise
			//Exchange jth row with the highest element row in the column. If exchanged det = -det
			int m = data[j][j];
			int midx = j;
			for(int i=j+1;i<n;i++){
				if(data[i][j]>m){
					m = data[i][j];
					midx = i;
				}
			}
			if(midx!=j){
				for(int i=0;i<n;i++){
					double temp = data[j][i];
					data[j][i] = data[midx][i];
					data[midx][i] = temp;
				}
				det = -det;
			}

			for(int i=j+1;i<n;i++){
				// There must be a element (j,j) which must be one already
				double multiplier = data[i][j]/data[j][j];
				for(int k=0;k<n;k++){
					data[i][k] = data[i][k] - data[j][k]*multiplier;
				}	
			}
			det *= data[j][j];
		}
		return det;
	}
	vector <vector <double> > inverse(vector <vector <double> > data){// Here we copy the argument to parameter instead of reference. This is because we need to modify the data to calculate its inverse
		if(data.size()==0)	return data;
		int m = data.size();
		int n = data[0].size();
		if(m!=n){
			throw "Only square matrices are invertible\n";
		}
		printf("det - %.20lf\n",determinant(data));
		if(fabs(determinant(data))<0.00000001){
			throw "The matrix is singular. Inverse doesn't exists\n";
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
	bool isSymmetric(const vector <vector<double> > &data){
		if(!isMatrix(data)){
			throw "All the rows must have same number of columns in a Matrix. Check the matrix (i.e double dimension vector) for dimensional consistency\n";
		}
		if(data.size()==0)	return true;
		int m = data.size();
		int n = data[0].size();
		if(m!=n)	return false;
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(data[i][j]!=data[j][i]){
					return false;
				}
			}
		}
		return true;
	}
	void eig(vector <vector<double> > data, vector <vector <double> > &eigen_vectors, vector <double> &eigen_values){
		if(data.size()==0)	return;
		if(!isSymmetric(data))
			throw "Eigens of only symmetric matrices can be calculated using this function.\n";
		int n = data.size();
		/*for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%lf ",data[i][j]);
			}
			printf("\n");
		}
		printf("\n");*/
		for(int loop=0;loop<n;loop++){
			double c[n];
			vector <double> x(n);
			for(int i=0;i<n;i++){
				x[i] = 1;
			}
			double y,k=0;
			do{
		    	y=k;
		    	k = 0;          
		    	for(int i=0;i<n;i++){   
		    		c[i]=0;
		    		for (int j=0;j<n;j++){
		                c[i]+=data[i][j]*x[j];
		            }
		            k += c[i]*c[i];
				}
				k = sqrt(k);
		        for(int i=0;i<n;i++)
		            x[i]=c[i]/k;
		    }while (fabs(k-y)>0.000001);
		    /*printf("\nA*X gives\n");
		    for(int i=0;i<n;i++){   
		        c[i]=0;
		        for(int j=0;j<n;j++){
		            c[i]+=data[i][j]*x[j];
		        }
		        printf("%lf\n",c[i]);
		    }
		    printf("\n");
		    printf("\nx gives\n");
		    for(int i=0;i<n;i++){   
		        printf("%lf\n",x[i]);
		    }
		    printf("\n");*/
		    //Determine the sign of k first
		    if((x[0]<0 && c[0]>0) || (x[0]>0 && c[0]<0)){
		    	k = -k;
		    }
		    //Determine the sign of vectors by using the fact that all eigen-vectors are Orthogonal for square matrices.

		    

		    eigen_values.push_back(k);
		    eigen_vectors.push_back(x);
			double v[n][n];
		    for(int i=0;i<n;i++){
		    	for(int j=0;j<n;j++){
		    		v[i][j] = x[i]*x[j];
		    	}
		    }
		    for(int i=0;i<n;i++){
		    	for(int j=0;j<n;j++){
		    		data[i][j] = data[i][j] - k*v[i][j];
		    	}
		    }
		}
	}
	void svd(const vector <vector<double> > &data, vector <vector <double> > &U, vector <vector<double> > &E, vector <vector <double> > &V_t){
		if(data.size()==0)	return;
		if(!isSymmetric(data))
			throw "SVD of only symmetric matrices can be calculated using this function.\n";
		int m = data.size();
		int n = data[0].size();
		vector <vector <double> > A_t_A = multiply(transpose(data),data);
		vector <vector <double> > A_A_t = multiply(data,transpose(data));
		vector <double> e_val_1,e_val_2;
		eig(A_t_A, V_t, e_val_1);
		eig(A_A_t, U, e_val_2);
		U = transpose(U);
		V_t = transpose(V_t);
		E = zeros(m,n);
		for(int i=0;i<min(m,n);i++){
			E[i][i] = sqrt(e_val_1[i]);
		}
	}
	vector <vector <double> > pinverse(const vector <vector<double> > &data){
		if(data.size()==0)		return data;
		if(!isSymmetric(data))
			throw "Pseudo inverse of only symmetric matrices can be calculated using this function.\n";
		int m = data.size();
		int n = data[0].size();
		if(m!=n){
			throw "Only square matrices are invertible\n";
		}
		vector <vector<double> > U,E,V_t;
		svd(data, U, E, V_t);
		for(int i=0;i<n;i++){
			if(fabs(E[i][i])>0.000001){
				E[i][i] = 1/E[i][i];
			}
		}
		return multiply(V_t,multiply(transpose(E),transpose(U)));
	}
};