inline void Read(int &x){
	char ch; x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}



for (int i=1;i<=n;i++) Read(a[i]);