import java.io.*;
import java.util.*;
public class Main{
	static final int N=1005;
	static final double eps=1e-6;
	static int n,m,i;
	static double a[],A[],B[],tmpa[],tmpb[];
	public static void main(String[] args) {
		Scanner cin=new Scanner(System.in);
		a=new double[N];A=new double[N];B=new double[N];
		tmpa=new double[N];tmpb=new double[N];
		double tmp;
		while (true){
			n=cin.nextInt();m=cin.nextInt();
			if (n==0)return;
			for (i=1;i<=n;++i)
				A[i]=cin.nextInt();
			for (i=1;i<=n;++i)
				B[i]=cin.nextInt();
			double sum,pre=1,ans=0;
			while (pre!=ans){
				pre=ans;
				for (i=1;i<=n;++i)a[i]=A[i]-B[i]*ans;
				for (i=1;i<=n;++i)tmpa[i]=A[i];
				for (i=1;i<=n;++i)tmpb[i]=B[i];
				for (int i=1;i<n;++i)
					for (int j=i+1;j<=n;++j)
						if (a[i]<a[j]){
							tmp=a[i];a[i]=a[j];a[j]=tmp;
							tmp=tmpa[i];tmpa[i]=tmpa[j];tmpa[j]=tmp;
							tmp=tmpb[i];tmpb[i]=tmpb[j];tmpb[j]=tmp;
						}
				//for (int i=1;i<=n;++i)
				//	System.out.println(a[i]);
				double sa=0,sb=0;
				for (i=1;i<=n-m;++i){sa+=tmpa[i];sb+=tmpb[i];}
				ans=sa/sb;
				//System.out.println("ans="+ans);
				//for (int i=1;i<=100000000;++i);
			}
			System.out.println((int)(ans*100+0.5));
		}
	}
}


