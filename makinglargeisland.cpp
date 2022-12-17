class Solution {
/*
Overall steps 
1. use variable islandId to keep track of all groups of connected island and
give them an index
2. calculate the area and keep track of the maximum
3. use hashmap to store two integers, which are the index and the area. 
4. loop the matrix again, use BFS to get the max by changing zero to one. 
*/

    
        int islandId = 2; // 0 and 1 are used, so start with 2. 
        unordered_map<int,int> mp; // map to store index and area. 

        //directions that will be used to find out conntected island. 
        vector<pair<int,int>> direction{{1,0},{-1,0},{0,1},{0,-1}};
        
        int max_area = 0; // variable to keep track of max area
        
        //function that will assign each connected island an index 
        void dfs(int i,int j,vector<vector<int>> &grid)
        {
            if(i<0 or i>=size(grid) or j<0 or j>=size(grid) or grid[i][j]!=1)
            return;
             mp[islandId]++; // move to the next key 
             grid[i][j]=islandId;
         for(auto dir:direction)
         {
            dfs(i+dir.first,j+dir.second,grid);
         }
        }
        
        //function that keep track of all the connected components. 
        void markAllTheConnectedComponents(vector<vector<int>>& grid)
        {
             int n=size(grid);
             mp.clear();
             islandId=2;
             for(int i=0;i<n;i++)
             {
                for(int j=0;j<n;j++)
                {
                    if(grid[i][j])
                    {
                         dfs(i,j,grid);
                        // use max() to get the maximum area 
                         max_area=max(max_area,mp[islandId]); 
                         islandId++; // increase index number for next connected island 
                     }
                }
            }
        }
        
    //when 0 changed to 1, find the max area 
    void findMaxArea(vector<vector<int>>& grid)
    {
        int n=size(grid);
        queue<pair<int,int>> q;
    
        //push all to the queue when the grid is 0. 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==0)
                {
                     q.push({i,j});
                 }
             }
        }
        
        //verify if the grid is valid 
         auto isValid = [&](int i,int j){
            return (i>=0 and i<n and j>=0 and j<n and grid[i][j]!=0);
        };

    while(!q.empty()) // loop through all the element in queue. 
    {
        auto front = q.front();
        q.pop();
        int i = front.first;
        int j = front.second;
        
        unordered_set<int> vis;
        int curr = 0;
        for(auto dir:direction)
        {
            int newi = i+dir.first;
            int newj = j+dir.second;
            // if it's connected after flipped to one, calculate the new area. 
            if(isValid(newi,newj) and !vis.count(grid[newi][newj]))
            {
                vis.insert(grid[newi][newj]);
                curr += mp[grid[newi][newj]];
            }
        }
        // plus one because need to consider the zero that changed to one.  
        max_area = max(curr+1,max_area);
    }
}
    
public:
    int largestIsland(vector<vector<int>>& grid) 
    {
        
        //mark all connected island. 
        markAllTheConnectedComponents(grid);
        //find the max area when 0 changed to 1. 
        findMaxArea(grid);
        return max_area;
    }

        
    };
