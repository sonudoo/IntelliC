#include <stdio.h>
using namespace std;
#include "matrix.cpp"


int main(){
	freopen("stdin.txt","r",stdin);
	int n;
	scanf("%d",&n);
	vector <vector<double> > data(n, vector <double> (n));
	for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				scanf("%lf",&data[i][j]);
			}
	}
	printf("jytf\n");
	vector <vector<double> > v1;
	vector <vector<double> > v2;
	vector <vector<double> > v3;
	Matrix m;
	try{
	m.svd(m.multiply(m.transpose(data),data), v1, v2,v3);
}
catch(const char *s){
	printf("%s\n",s);
}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%lf ",v1[i][j]);
		printf("\n");
	} 
	printf("\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%lf ",v2[i][j]);
		printf("\n");
	} 
	printf("\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%lf ",v3[i][j]);
		printf("\n");
	} 
	printf("\n");
	vector <vector<double> > v4 = m.pinverse(m.multiply(m.transpose(data),data));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%lf ",v4[i][j]);
		printf("\n");
	} 
	printf("\n");
	return 0;
}