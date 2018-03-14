#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _LIMITS_
	#include <limits>
	#define _LIMITS_
#endif

#include "Matrix.cpp"
#include "Vector.cpp"
#include "DataTransform.cpp"

class Cluster{
private:
	vector <vector <double> > X;
	vector <double> std;
	vector <double> avg;
	DataTransform <double> _d;
	int m;
	int n;
public:
	Cluster(const vector <vector <double> > &data){
		if(data.size()==0) throw "Data must not be empty";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		X = Matrix::normalize(data);
		std = Matrix::std(data);
		avg = Matrix::avg(data);
	}
	void cluster(int k, vector <vector<double> > &ret_centroids, vector <int> &ret_assigned_centroid, bool printCost = false){
		if(k>m){
			throw "Number of clusters must be less than number of rows in the dataset.\n";
		}
		vector <vector <double> > centroids; //Vector containing list of centroids
		vector <vector <double> > previous_centroids;
		for(int i=0;i<k;i++){
			centroids.push_back(Vector::random(n));
			previous_centroids.push_back(Vector::prod(Vector::ones(n), 100));
		}

		vector <int> assigned_centroid (m); //Centriod assigned to each point
		vector <vector<int> > assigned_node (k); //List of points assigned to each centroid
		double c;

		while(true){
			for(int i=0;i<k;i++){
				assigned_node[i].clear();
			}

			c = 0;

			//Cluster assignment
			for(int i=0;i<m;i++){
				int a = -1;
				double m = std::numeric_limits<double>::max();
				for(int j=0;j<k;j++){
					double x = Vector::sum(Vector::pow(Vector::diff(centroids[j], X[i]),2));
					if(x < m){
						m = x;
						a = j;
					}
				}
				c += m;
				assigned_centroid[i] = a;
				assigned_node[a].push_back(i);
			}

			//Cluster movement
			for(int i=0;i<k;i++){
				for(int j=0;j<n;j++){
					if(assigned_node[i].size()==0)	continue;
					double s = 0;
					for(int l=0;l<assigned_node[i].size();l++){
						s += X[assigned_node[i][l]][j];
					}
					s /= assigned_node[i].size();
					centroids[i][j] = s;
				}
			}
			//Check for convergence
			bool converged = true;
			for(int i=0;i<k;i++){
				for(int j=0;j<n;j++){
					if(fabs(previous_centroids[i][j]-centroids[i][j])>0.00001){
						converged = false;
					}
					previous_centroids[i][j] = centroids[i][j];

				}
			}
			
			if(converged)	break;

			if(printCost)
				printf("Cost - %lf\n",c);
		}
		//Denormalize
		for(int i=0;i<k;i++){
			for(int j=0;j<n;j++){
				centroids[i][j] = (centroids[i][j]*std[j])+avg[j];
			}
		}
		ret_centroids = centroids;
		ret_assigned_centroid = assigned_centroid;
	}
};