import java.io.*;
import java.util.*;
public class Main{
	static final int N=100005;
	public class node{
		boolean operator <(node y){
			if (x<y.x)return 1;else return 0;
		}
	};
	static node p[]=new node[N];
	static int c[]=new int[N],top;
	double cha(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
	public static void main(String[] args){
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt(),l=cin.nextInt();
		for (int i=1;i<=n;++i)p[i].x=cin.nextInt(),p[i].y=cin.nextInt();
		java.sort(a,1,n);top=0;
		for (int i=1;i<=n;++i){
			while (top>1&&cha(p[i].x-p[c[top]].x,p[i].y-p[c[top]].y,p[c[top]].x-p[c[top-1]].x,p[c[top]].y-p[c[top-1]].y)>0)--top;
			c[++top]=i;
		}
		for (int i=n-1;i>0;--i){
			while (top>1&&cha(p[i].x-p[c[top]].x,p[i].y-p[c[top]].y,p[c[top]].x-p[c[top-1]].x,p[c[top]].y-p[c[top-1]].y)>0)--top;
			c[++top]=i;
		}
		double ans=0;
		for (int i=1;i<top;++i)ans+=cha(0,0,p[c[i+1]].x-p[c[i]].x,p[c[i+1]].y-p[c[i]].y);
		if (ans<0)ans=-ans;
		ans+=3.141592653589*L*L;
		System.out.println((int)ans);
	}
}


