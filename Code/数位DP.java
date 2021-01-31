import java.io.*;
import java.util.*;
public class Main{
	static int f[][]=new int[15][205],a[]=new int[15];
	static int work(int x){
		if (x<=0)return 0;
		int l=0,sum=0,ans=0;
		while (x>0){a[++l]=x%10;x/=10;}
		for (int i=l;i>0;--i){
			for (int j=0;j<a[i];++j)
				if ((i&1)!=0)ans+=f[i-1][101-sum+j];
				else ans+=f[i-1][101-sum-j];
			if ((i&1)!=0)sum-=a[i];
				else sum+=a[i];
		}
		if (sum==1)return ans+1;
			else return ans;
	}
	public static void main(String[] args){
		Scanner cin=new Scanner(System.in);
		f[0][100]=1;
		for (int i=1;i<=9;++i)
			for (int k=100-45;k<=100+45;++k)
				for (int j=0;j<=9;++j)
					if ((i&1)!=0)f[i][k]+=f[i-1][k+j];
						else f[i][k]+=f[i-1][k-j];
		int T=cin.nextInt(),l,r;
		while (T>0){
			--T;
			l=cin.nextInt();r=cin.nextInt();
			System.out.println(work(r)-work(l-1));
		}
	}
}


