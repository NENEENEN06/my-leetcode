class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        struct Node{
            int x;
            int y;
            int l;
        };
        queue<Node>q;
        if(grid[0][0]==')'){
            return false;
        }
        q.push({0,0,1});
        int m=grid.size();
        int n=grid[0].size();
        int dx[]={0,1};
        int dy[]={1,0};
        vector<vector<vector<bool>>>vis(m,vector<vector<bool>>(n,vector<bool>(m+n,false)));
        vis[0][0][1]=true;
        while(!q.empty()){
            auto [x,y,l]=q.front();
            q.pop();          
            for(int i=0;i<2;i++){
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(nx>=m||ny>=n){continue;}
                int nl=l+(grid[nx][ny]=='('?1:-1);
                if(nl<0){continue;}
                if(nx==m-1&&ny==n-1&&nl==0){
                    return true;
                }
                else if(!vis[nx][ny][nl]){
                    q.push({nx,ny,nl});
                    vis[nx][ny][nl]=true;
                }
            }
        }
        return false;
    }
};
