#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,dista,distb,ans,delta,P,Q,R,D1,D2;
double D(double Ax,double Ay,double Bx,double By){
	return sqrt((Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By));
}
double calc(){
	double time=0;
	double x1,y1,x2,y2;
	if (dista<1e-10){
		x1=Ax;y1=Ay;
	}
	else {
		x1=Ax+(Bx-Ax)*D1/dista;
		y1=Ay+(By-Ay)*D1/dista;
	}
	if (distb<1e-5){
		x2=Dx;y2=Dy;
	}
	else {
		x2=Dx+(Cx-Dx)*D2/distb;
		y2=Dy+(Cy-Dy)*D2/distb;
	}
	time+=D1/P;
	time+=D2/Q;
	time+=D(x1,y1,x2,y2)/R;
	return time;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	scanf("%lf%lf%lf%lf",&Ax,&Ay,&Bx,&By);
	scanf("%lf%lf%lf%lf",&Cx,&Cy,&Dx,&Dy);
	scanf("%lf%lf%lf",&P,&Q,&R);
	delta=10000;
	dista=sqrt((Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By));
	distb=sqrt((Cx-Dx)*(Cx-Dx)+(Cy-Dy)*(Cy-Dy));
	D1=0;D2=0;ans=calc();
	while (delta>1e-15){
		int s=0;
		while (s<100){
			if (rand()%2==0){
				double tmp=D1;
				if (rand()%2==0)D1+=delta;
					else D1-=delta;
				if (D1>=0&&D1<=dista+1e-6&&calc()<ans){
					ans=calc();s=0;
				}
				else {
					D1=tmp;++s;
				}
			}
			else {
				double tmp=D2;
				if (rand()%2==0)D2+=delta;
					else D2-=delta;
				if (D2>=0&&D2<=distb+1e-6&&calc()<ans){
					ans=calc();s=0;
				}
				else {
					D2=tmp;++s;
				}
			}
		}
		delta*=0.9;
	}
	printf("%.2lf\n",ans);
	//printf("%.10lf %.10lf\n",D1,D2);
	system("pause");for (;;);
	return 0;
}


