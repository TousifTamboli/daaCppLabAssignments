// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solveMem(vector<int>& weight, vector<int>& value, int index, int capacity, vector<vector<int>>& dp){
        
        //base case
        //if only one item is present compare its weight with knapsack
        if(index == 0){
            if(weight[0] <= capacity){
                return value[0];
            }
            else
                return 0;
        }
        
        if(dp[index][capacity] != -1)
            return dp[index][capacity];
        
        //ya include karo ya exclude karo
        
        //include
        int include = 0;
        if(weight[index] <= capacity)
            include = value[index] + solveMem(weight, value, index - 1, capacity - weight[index], dp);
        
        //exclude        
        int exclude = 0 + solveMem(weight, value, index - 1, capacity, dp);
        
        //index aur capacity ki value change hori hai
        dp[index][capacity] = max(exclude, include);
        
        return dp[index][capacity];
        
    }

int main() {
    
    vector<int> weight = {10, 20, 30}; 
    vector<int> value = {60, 100, 120}; 
    
    
    int n = weight.size(); 
    int capacity = 50; 
    
    // 2D dp array banao
    vector<vector<int>> dp(n, vector<int>(capacity+1, -1));
    
    
    int maxValue = solveMem(weight, value, n - 1, capacity, dp);
    
    //final output
    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
