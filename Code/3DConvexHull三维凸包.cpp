#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define N 1005
#define eps (1e-7)
struct _3DCH{
	inline int sgn(double x){return fabs(x)<eps?0:(x<0?-1:1);}
	struct point{
		double x,y,z;
		point(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
		friend point operator -(point x,point y){return point(x.x-y.x,x.y-y.y,x.z-y.z);}
	}p[N];
	struct face{
		int a,b,c,del;
		face():del(0){}
	}f[N*N];
	int to[N][N],used[N],n,cnt;
	point cross(point x,point y){return point(x.y*y.z-y.y*x.z,x.z*y.x-y.z*x.x,x.x*y.y-y.x*x.y);}
	double dot(point x,point y){return x.x*y.x+x.y*y.y+x.z*y.z;}
	int outside(face f,point x){
		point det=cross(p[f.c]-p[f.b],p[f.b]-p[f.a]);
		return sgn(dot(det,x-p[f.a]))>0;
	}
	int go(int a,int b,int x){
		int idx=to[b][a];
		if(f[idx].del)return 0;
		if(outside(f[idx],p[x]))work(idx,x);
		else{
			f[cnt].a=a;f[cnt].b=b;f[cnt].c=x;
			to[a][b]=to[b][x]=to[x][a]=cnt++;
		}
	}
	void work(int fa,int x){
		if(f[fa].del)return;
		f[fa].del=1;
		go(f[fa].a,f[fa].b,x);
		go(f[fa].b,f[fa].c,x);
		go(f[fa].c,f[fa].a,x);
	}
	double vlen(point x){return sqrt(x.x*x.x+x.y*x.y+x.z*x.z);}
	double area(point a,point b,point c){return vlen(cross(b-a,c-a));}
	double volume(point a,point b,point c,point d){return dot(cross(b-a,c-a),d-a);}
	double volume(){
		point O(0,0,0);double ans=0.0;
		for (int i=0;i<cnt;++i)
			if (!f[i].del)ans+=volume(O,p[f[i].a],p[f[i].b],p[f[i].c]);
		return fabs(ans/6.0);
	}
	double area(){
		double ans=0.0;
		for (int i=0;i<cnt;++i)if (!f[i].del)
			ans+=area(p[f[i].a],p[f[i].b],p[f[i].c]);
		return ans/2.0;
	}
	int cnt_point(){
		int ans=0;for (int i=0;i<n;++i)used[i]=0;
		for (int i=0;i<cnt;++i)if (!f[i].del)
			used[f[i].a]=used[f[i].b]=used[f[i].c]=1;
		for (int i=0;i<n;++i)ans+=used[i];
		return ans;
	}
	int cnt_tri(){return cnt;}
	int _rand(){static int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}
	void build(){
		scanf("%d",&n);
		for (int i=0;i<n;++i)scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
		for (int i=n-1;i;--i){
			int id=_rand()%(i+1);
			point tmp=p[i];p[i]=p[id];p[id]=tmp;
		}
		cnt=0;
		for (int i=0;i<4;++i){
			int a=i,b=(i+1)&3,c=(i+2)&3,d=(i+3)&3;
			f[cnt].a=a;f[cnt].b=b;f[cnt].c=c;
			if (outside(f[cnt],p[d])){
				int tmp;tmp=a;a=b;b=tmp;
				tmp=f[cnt].a;f[cnt].a=f[cnt].b;f[cnt].b=tmp;
			}
			to[a][b]=to[b][c]=to[c][a]=cnt++;
		}
		for (int i=4;i<n;++i)
			for (int j=0;j<cnt;++j)
				if (!f[j].del&&outside(f[j],p[i])){work(j,i);break;}
	}
};
_3DCH hull;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	hull.build();
	printf("%.2lf\n",hull.volume());
	system("pause");for (;;);
	return 0;
}


