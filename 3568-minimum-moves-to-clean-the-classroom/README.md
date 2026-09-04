# 3568. Minimum Moves to Clean the Classroom

- Difficulty: Medium
- Topics: BFS, Bit Manipulation, Array, Matrix
- Language: C++
- 题目链接: https://leetcode.cn/problems/minimum-moves-to-clean-the-classroom/

## 题目

在一个 m x n 的教室网格中，学生从起点 'S' 出发，每次向上下左右移动一步会消耗 1 点能量。'L' 是需要收集的垃圾，'R' 可以把能量恢复为最大能量 energy，'X' 是障碍，'.' 是空地。求收集完所有垃圾所需的最少移动次数，若无法完成则返回 -1。

## 我的思路

- 核心思想：BFS 求最短路，用位掩码压缩"已收集的垃圾集合"，同时把能量作为状态的一部分。
- 使用的数据结构：队列 `queue<Point>` 做 BFS；二维数组 `lid` 记录每个 'L' 的编号；三维数组 `maxE[x][y][mask]` 记录到达 (x, y) 且已收集集合为 mask 时见过的最大能量。
- 算法流程：
  1. 扫描网格，给每个 'L' 编号（0 到 l-1），并记录起点 'S' 的坐标。
  2. 初始状态为 (x, y, energy, mask=0, steps=0)，入队。
  3. 出队时若 `mask == fullMask` 直接返回 steps；否则若当前能量不优于 `maxE[x][y][mask]` 就剪枝，否则更新它。
  4. 向四个方向扩展：越界、撞 'X'、能量为 0 时跳过；走进 'L' 就置位对应比特，走进 'R' 就把能量回满，其余情况能量减 1，步数加 1。
- 为什么这样做：BFS 按步数逐层扩展，第一次扩展到"收集完全部垃圾"的状态时就是最少步数；同一 (x, y, mask) 下能量越高越优，所以只保留最大能量即可剪枝。
- 关键状态 / 变量：`mask`（哪些垃圾已收集）、`fullMask = (1 << l) - 1`、`maxE`（能量最大化剪枝）、`lid`（垃圾编号）。
- 为什么能够得到正确答案：能量是一个单调的资源，同一位置和同一收集进度下，能量更多的状态能模拟能量更少状态的一切后续走法，因此按最大能量剪枝不会漏掉最优解。

## 代码

```cpp
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
```

## 代码分析

- 正确性：正确。
- 关键实现：用位掩码 `mask` 表示垃圾收集进度；用 `maxE[x][y][mask]` 做"最大能量"剪枝，避免四维 visited；走进 'R' 时把 `ne` 直接置为 `energy`。
- 潜在 Bug：没有发现明显错误。唯一要注意的是当网格中没有 'L' 时 `l == 0`、`fullMask == 0`，初始状态会立即返回 0，这是符合题意的。
- 可以改进的地方：可以把步数从状态里去掉，改用按层 BFS；也可以改用四维 `visited[x][y][e][mask]`，思路更直白，但空间会更大。

## 复杂度

- 时间复杂度：O(m * n * 2^l * energy)。每个 (x, y, mask) 状态最多以严格递增的能量出队 energy+1 次，每次扩展 4 个方向。
- 空间复杂度：O(m * n * 2^l)。主要是 `maxE` 三维数组；队列在最坏情况下可能达到 O(m * n * 2^l * energy)。

## 易错点

- 能量为 0 时不能再移动，必须先判断 `e == 0`，否则会把非法状态继续扩展。
- 垃圾编号 `lid` 和掩码位的对应关系要一致，`fullMask = (1 << l) - 1` 不能写错。
- `maxE` 剪枝必须是"严格大于才更新"，否则可能丢解或重复扩展。
- 别漏掉边界和 'X' 障碍的判断。
- 没有 'L' 时应该返回 0，而不是 -1。

## 总结

这道题是多资源（能量）+ 多目标（收集全部垃圾）的最短路问题：用 BFS + 位掩码表示收集进度，并利用"同一位置、同一收集进度下能量越高越优"的性质做最大能量剪枝，既保证正确性又压缩了状态。

## 复盘

- 我哪里容易想错：一开始容易想到贪心先收最近的垃圾，但能量限制会迫使绕路去 'R' 回能，贪心不成立。
- 关键突破点：把能量和已收集集合一起纳入状态，并发现能量更高时支配能量更低的状态。
- 下次看到什么特征应该想到这个算法：网格 + 收集若干目标 + 有限资源/步数的最短路径，可以往状态压缩 BFS 或 Dijkstra 方向想。
