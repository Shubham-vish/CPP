#include<bits/stdc++.h>
using namespace std;		
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define dbg(x) cout<<#x<<" : "<<x<<"\n";
#define dbg2(x, y) cout<<#x<<" : "<<x<<" , "<<#y<<" : "<<y<<"\n";
#define dbg3(x, y, z) cout<<#x<<" : "<<x<<" , "<<#y<<" : "<<y<<" , "<<#z<<" : "<<z<<"\n";
#define dbg4(x, y, z, w) cout<<#x<<" : "<<x<<" , "<<#y<<" : "<<y<<" , "<<#z<<" : "<<z<<" , "<<#w<<" : "<<w<<"\n";

int n;
int INF=9999999;
int adj[1000][1000];
int dp[1000][1000];
int parentt[1000][1000];

int lim;

int getMinCost(int vertex, int setMask){

	dbg2(vertex , setMask);
	int cost;
	int parent;
	int minParentVertex;
	
	int minCost = INF;
	
	if(setMask == lim){
	    setMask = setMask & (~(1 << (0)));
	    
    	for (int j = 1 ; j < n ; j++) {
    	     dbg4("for of 1st if " , j  , vertex, setMask);
    	    if( ((1<<(j)) & setMask) && adj[vertex][j]  ){
    	        cost = adj[j][vertex] + getMinCost(j, setMask & (~(1 << (j))));
    	        parent = j;
    	        
    	        dbg4(vertex, j, cost, parent);
    	        if(cost<minCost){
    	            minCost = cost;
    	            minParentVertex = parent;
    	            dbg4(vertex, setMask, cost, parent);
    	        }
    	    }
    	}
	}else{
	    for (int j = 1 ; j < n ; j++) {
    	  if( ((1<<j) & setMask) && adj[vertex][j]  ){
    	       if((setMask & (~(1 << (j))))==0){
    	           if(adj[0][j]){
                    
    	               dp[vertex][setMask] = adj[j][vertex] + adj[0][j];
	                   parentt[vertex][setMask] = j;
	                   parent = parentt[vertex][setMask];
	                   dbg4(j, dp[vertex][setMask], parent,vertex);
	                   return dp[vertex][setMask];
    	           }
    	           return INF;
    	       } 
    	       cost = adj[j][vertex] + getMinCost(j, setMask & (~(1 << (j))));
    	       parent = j;
    	       
    	       if(cost<minCost){          
    	           minCost = cost;
    	           minParentVertex = parent;
    	       }
    	  }
        }
	}
	dp[vertex][setMask] = minCost;
	dbg3(vertex, setMask,minParentVertex);
	parentt[vertex][setMask] = minParentVertex;
	
	return minCost;
}

int main(){
    cout<<(1<<4);
    memset(dp, -1, sizeof(dp));
	cin>>n;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cin>>adj[i][j];
		}
	}
	lim = (1<<(n)) - 1;
    int ans = getMinCost(0,lim);
    cout<<ans<<"\n"<<dp[0][lim-1]<<"\n";
    int p = parentt[0][lim-1];
    lim = lim-1;
    dbg(lim);
    while(lim){
        lim = (lim)&(~(1<<p));
        dbg2(p, lim);
        p = parentt[p][lim];
    }
	return 0;
}