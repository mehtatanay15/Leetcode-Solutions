class Solution {
public:

    int smalldiv(vector<int> &temp, int divi)
    {
        long long total = 0;
        for(int i = 0;i< temp.size();i++)
        {
            total += ceil((double)temp[i] / (double)divi);
        }
        return (int)total;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {

        int n = nums.size();

        int maxi = -1;

        for(int i =0; i<n; i++)
        {
             if(nums[i]> maxi)
             {
                maxi = nums[i];
             }
        }
        
        int low = 1;
        int high = maxi;

        int ans = 0;

        while(low<=high)
        {
            int mid = (low + high)/2;

            int total = smalldiv(nums,mid);

            if(total<=threshold)
            {
                ans = mid;
                high = mid -1;
            }

            else{
                low = mid +1;
                
            }
        }

        return ans;
    }
};