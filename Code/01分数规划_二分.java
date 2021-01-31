import java.io.*;
import java.util.*;
public class Main{
	static final int N=1005;
	static final double eps=1e-6;
	static int n,m,i;
	static double a[],A[],B[];
	public static void main(String[] args) {
		Scanner cin=new Scanner(System.in);
		a=new double[N];A=new double[N];B=new double[N];
		while (true){
			n=cin.nextInt();m=cin.nextInt();
			if (n==0)return;
			for (i=1;i<=n;++i){
				int tmp=cin.nextInt();
				A[i]=tmp;
			}
			for (i=1;i<=n;++i){
				int tmp=cin.nextInt();
				B[i]=tmp;
			}
			double sum,l=0,r=1,mid;
			while (r-l>eps){
				mid=(l+r)/2;
				for (i=1;i<=n;++i)a[i]=B[i]*mid-A[i];
				for (int i=1;i<n;++i)
					for (int j=i+1;j<=n;++j)
						if (a[i]>a[j]){
							double tmp=a[i];
							a[i]=a[j];a[j]=tmp;
						}
				//for (int i=1;i<=n;++i)
					//System.out.println(a[i]);
				sum=0;
				for (i=1;i<=n-m;++i)sum+=a[i];
				if (sum>0)r=mid;
					else l=mid;
			}
			System.out.println((int)(l*100+0.5));
		}
	}
}


