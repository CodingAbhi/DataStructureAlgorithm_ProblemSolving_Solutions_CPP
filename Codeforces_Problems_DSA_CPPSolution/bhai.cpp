
#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum absolute difference between two subset sums
 int minimumDifference(vector<int>& nums) {
        int n =nums.size();
        int totsum = 0;
        for(int i =0;i<n;i++){
                totsum+=nums[i];
        }
        int k  = totsum;
        vector<vector<bool>> dp(n,vector<bool>(k+1,false));
        for(int i =0;i<n;i++){
            dp[i][0]=true;
        }
        if(nums[0]<=totsum) dp[0][nums[0]] =true;
        for(int ind = 1;ind<n;ind++){
            for(int target =1;target<=k;target++){
                bool notake = dp[ind-1][target];
                bool take = false;
                if(nums[ind]<=target){
                    take = dp[ind-1][target - nums[ind]];

                }
                dp[ind][target] = take||notake;
            }
        }

        int mini = 1e9;
        for(int s1=0;s1<=totsum/2;s1++){
            if(dp[n-1][s1]==true){
                int diff = abs((totsum-s1)-s1);
                mini = min(mini,diff);
            }
        }
        return mini;

}

int main() {
    vector<int> arr = {3,9,7,3};
    int n = arr.size();

    cout << "The minimum absolute difference is: " << minimumDifference(arr);

    return 0;
}

