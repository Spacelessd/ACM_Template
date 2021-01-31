import java.io.*;
import java.util.*;
public class Main{
	static final int N=100005;
	static long sum[]=new long[N],
	x[]=new long[N],y[]=new long[N];
	static int q[]=new int[N];
	static int h,t,i,j;
	static double ans;
	static double max(double x,double y){return x>y?x:y;}
	static long cross(int a,int b,int c){
		return (x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a]);
	}
	static void add(int p){
		while (t>h&&cross(q[t-1],p,q[t])>=0)--t;
		q[++t]=p;
	}
	static int query(int p){
		while (h<t&&cross(q[h],q[h+1],p)>=0)++h;
		return q[h];
	}
	public static void main(String[] args){
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt(),m=cin.nextInt();
		sum[0]=0;x[0]=0;y[0]=0;
		for (i=1;i<=n;++i){
			int X=cin.nextInt();
			sum[i]=sum[i-1]+X;
			x[i]=i;y[i]=sum[i];
		}
		ans=0;h=1;t=0;
		for (i=m;i<=n;++i){
			add(i-m);j=query(i);
			ans=max(ans,(sum[i]-sum[j])/double(i-j));
		}
		System.out.println((int)(ans*1000));
    }
}



