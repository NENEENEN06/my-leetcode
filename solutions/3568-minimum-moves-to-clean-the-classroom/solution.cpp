class Solution {
public:
   int minMoves(vector<string>& classroom, int energy) {
       const int dx[]={0,0,1,-1};
       const int dy[]={1,-1,0,0};
       int l=0,x,y;
       const int m = classroom.size();
       const int n = classroom.front().size();
       struct Point{
           int x;
           int y;
           int e;
           int mask;
           int steps;
       };
       vector<vector<int>>lid(m,vector<int>(n,0));
       for(int i = 0 ; i < m ; ++i){
           for(int j = 0 ; j < n ; ++j){
               if(classroom[i][j]=='L'){lid[i][j]=l++;}
               if(classroom[i][j]=='S'){x=i;y=j;}
           }
       }

       int fullMask = (1 << l) -1;
       vector<vector<vector<int>>>maxE(m,vector<vector<int>>(n,vector<int>(fullMask+1,-1)));
       queue<Point>q;
       q.push({x,y,energy,0,0});
       while(!q.empty()){
           auto [x,y,e,mask,steps] = q.front();q.pop();
           if(mask==fullMask){return steps;}
           if(e<=maxE[x][y][mask]){continue;}
           else{maxE[x][y][mask]=e;}
           for(int i = 0 ; i < 4 ; ++i){
               int nx=x+dx[i];
               int ny=y+dy[i];
               if(nx<0||nx>=m||ny<0||ny>=n){continue;}
               if(classroom[nx][ny]=='X'){continue;}
               if(e==0){continue;}
               int ne=e-1;
               int nmask=mask;
               if(classroom[nx][ny]=='L'){nmask = mask | (1 << lid[nx][ny]);}
               if(classroom[nx][ny]=='R'){ne=energy;}
               q.push({nx,ny,ne,nmask,steps+1});
           }
       }
       return -1;
   }
};
