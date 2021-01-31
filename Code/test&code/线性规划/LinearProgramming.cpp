#include <cstdio>
#include <vector>
using namespace std;
double Abs(double a){return a>=0?a:-a;}
namespace LP{
	vector<vector<double> >A;
	vector<double> R,Z,X;
	double Now;
	vector<int> I,P;
	int N,M,nn,mm;
	void subtract(vector<double> &a,double &r,vector<double> &b,double s,int c){
		double o=a[c];
		for (int i=0;i<mm;i++)a[i]-=o*b[i];
		a[c]=0;
		r-=o*s;
	}
	void exchange(int a,int b){
		P[I[a]]=-1;I[a]=b;P[b]=a;
		double o=A[a][b];
		for (int i=0;i<mm;i++)A[a][i]/=o;
		A[a][b]=1;
		R[a]/=o;
		for (int i=0;i<nn;i++)if (a!=i)subtract(A[i],R[i],A[a],R[a],b);
		subtract(Z,Now,A[a],-R[a],b);
	}
	int PIVOT(){
		int u=-1;
		int c=rand()%2;
		for (int i=0;i<mm;i++)if (P[i]==-1 && Z[i]>1e-9)
			if (u==-1 || (c?Z[i]>Z[u]:0))u=i;
		if (u==-1)return -1;
		int k=-1;
		double bound;
		for (int i=0;i<nn;i++)if (A[i][u]>1e-9){
			double h=R[i]/A[i][u];
			if (k==-1 || bound>h)k=i,bound=h;
		}
		if (k==-1)return -2;
		exchange(k,u);
		return 0;
	}
	int LP(int n,int m,vector<double> z,vector<vector<double> > a,vector<double> r){
		M=m;N=n;mm=N+M+1;nn=N;
		X.assign(M,0);
		A.assign(nn,vector<double>(mm,0));
		for (int i=0;i<N;i++)for (int j=0;j<M;j++)A[i][j]=a[i][j];
		R=r;
		I.assign(nn,0);
		P.assign(mm,-1);
		for (int i=0;i<nn;i++){
			A[i][M+i]=1;A[i][mm-1]=-1;
			I[i]=M+i;P[M+i]=i;
		}
		Z.assign(mm,0);
		Z[mm-1]=-1;
		Now=0;
		int u=0;
		for (int i=1;i<nn;i++)if (R[i]<R[u])u=i;
		if (R[u]<0){
			exchange(u,mm-1);
			while (PIVOT()==0);
			if (Now<-1e-9)return -1;//No Solution
			if (P[mm-1]!=-1){
				u=-1;
				for (int i=0;i<mm;i++)if (P[i]==-1)
					if (u==-1 || Abs(A[P[mm-1]][i])>Abs(A[P[mm-1]][u]))u=i;
				exchange(P[mm-1],u);
			}
		}
		mm--;
		for (int i=0;i<M;i++)Z[i]=z[i];
		for (int i=M;i<mm;i++)Z[i]=0;
		Now=0;
		for (int i=0;i<M;i++)if (P[i]!=-1)
			subtract(Z,Now,A[P[i]],-R[P[i]],i);
		while ((u=PIVOT())==0);
		if (u==-2)return -2;//Unbounded
		for (int i=0;i<nn;i++)if (I[i]<M)X[I[i]]=R[i];
		return 0;
	}
}
int main()
{
	int n,m;
	freopen("a.in","r",stdin);
	freopen("aline.out","w",stdout);
	int t1=clock();
	scanf("%d%d",&m,&n);
	vector<vector<double> > a(n,vector<double>(m,0));
	vector<double> r(n),z(m);
	for (int i=0;i<m;i++)scanf("%lf",&z[i]);
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)scanf("%lf",&a[i][j]);
		scanf("%lf",&r[i]);
	}
	int t=LP::LP(n,m,z,a,r);
	if (t==-1)puts("No Solution");
	else if (t==-2)puts("Un Bounded");
	else{
		printf("%f\n",LP::Now);
		for (int i=0;i<m;i++)printf("%f ",LP::X[i]);
		puts("");
	}
	printf("%d\n",clock()-t1);
	//system("pause");
	return 0;
}

