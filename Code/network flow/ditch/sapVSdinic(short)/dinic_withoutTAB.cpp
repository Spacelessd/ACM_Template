inline int min(int x,int y){return x<y?x:y;}
bool build(){
int h=0,t=1,i,j,p; memset(d,-1,sizeof(d)); d[S]=0,f[1]=S;
while (h<t){
i=f[++h];
for (p=son[i];p;p=next[p]){
j=ed[p]; if (!data[p]||d[j]!=-1) continue;
d[j]=d[i]+1,f[++t]=j; if (j==T) return 1;}}
return 0;}
double dinic(int i,int low){
if (i==T) return low; int w=0,res,p,j;
for (p=son[i];p&&w<low;p=next[p]){
j=ed[p];
if (data[p]>eps&&d[j]==d[i]+1&&(res=dinic(j,min(low-w,data[p]))))
data[p]-=res,data[p^1]+=res,w+=res;}
if (!w) d[i]=-1; return w;}
while (build()) while (flow=dinic(S,oo)) ans+=flow;
