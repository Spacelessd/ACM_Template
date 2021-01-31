inline int min(int a,int b){return a<b?a:b;}
int aug(int x,int flow){
int i,j,delta,now=flow,mind=n-1; if (x==T) return flow;
for (j=son[x];j!=-1;j=next[j]){
i=link[j];
if (cap[j]>0){
if (d[x]==d[i]+1){
delta=aug(i,min(now,cap[j]));
cap[j]-=delta,cap[opp[j]]+=delta,now-=delta;
if (d[S]>=n) return flow-now; if (!now) break;}
if (mind>d[i]) mind=d[i];}}
if (flow==now){
vd[d[x]]--; if (!vd[d[x]]) d[S]=n;
d[x]=mind+1,vd[d[x]]++;}
return flow-now;}
memset(vd,0,sizeof(int)*(n+5));vd[0]=n;
while(d[S]<n) ans+=aug(S,oo);
