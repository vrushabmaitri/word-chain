#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
int i, j, k, l, n, l1, l2;
vector<int> g[1005];
vector<string> ans;
string start, tgt, t1, t2, s[1005];
int org, fin, res, dp[1005][1005][2], par[1005], tf;
int vis[1005];
queue<int> q;
map<string, int> ms;

int go(int i, int j, int ch) 
{
    if(i > l1 || i > l2 || ch > 1) return 0;	//base case
    if(i == l1 && j == l2 && ch <= 1) return 1; //base case
    int ans = 0;
    if(t1[i] == t2[j]) 
	{
        ans = ans || go(i+1, j+1, ch);
    }
    if(dp[i][j][ch] != -1) return dp[i][j][ch]; //recurion to check the difference of characters
    ans = ans || go(i+1, j, ch+1);
    ans = ans || go(i, j+1, ch+1);
    ans = ans || go(i+1,j+1, ch+1);
    return dp[i][j][ch] = ans;
}

bool match(string s1, string s2) 
{
    l1 = s1.length();
    l2 = s2.length();
    t1 = s1;
	t2 = s2;
    if(abs(l1 - l2) > 1) return false;
    memset(dp, -1, sizeof dp);
    res = go(0, 0, 0);
    if(res) return true;
    return false;
}

int main() 
{  
	cout<<"Enter the starting word"<<endl;
 	cin>>start;
	cout<<"Enter the target word"<<endl;
    cin>>tgt;
	
	freopen("input.txt","r",stdin);	//open txt file and scan words
    cin>>n;
    
    for(i = 0; i < n; i++) 
	{
        cin>>s[i];
        ms[s[i]] = i;	//hash map
    }

    org = ms[start];	//start index 
    fin = ms[tgt];		//target index
    
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) 
		{
            if(match(s[i], s[j])) //finding the difference in number of characters
			{
                g[i].push_back(j);	//adding edge
                g[j].push_back(i);
            }
            
        }
    }
    
    //applying BFS
    memset(vis, 0, sizeof vis);
    memset(par, -1, sizeof par);
    
    q.push(org);
    vis[org] = 1;
    par[org] = -1;
    while(org != fin && !q.empty()) 
	{
        i = q.front();
        q.pop();
        for(j = 0; j < g[i].size(); j++) 
		{
            if(!vis[g[i][j]]) {
           
                q.push(g[i][j]);
                par[g[i][j]] = i;
                vis[g[i][j]] = 1;
            }
        }
    }
    tf = fin;
    while(tf != -1) 
	{
        ans.push_back(s[tf]);	//strorin gthe parent nodes
        tf = par[tf];
    }
    
    reverse(ans.begin(), ans.end());
    if(ans.size()<=1)
    {
    	cout<<"Not possible to build a path"<<endl;
	}
	else
	{
	
    	for(i = 0; i < ans.size(); i++) //output array
		{
			if(i!=ans.size()-1)
        	cout<<ans[i]<<" --> ";
        	else
        	cout<<ans[i];
   	 	}
    cout<<endl;
	}
	fclose(stdin);

    return 0;
}

