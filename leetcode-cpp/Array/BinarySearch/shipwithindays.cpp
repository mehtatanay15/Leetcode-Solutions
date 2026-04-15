class Solution {
public:
    int calcidays(vector<int> &temp, int capacity){
        int w =0;
        int day = 1;
        for(int i =0; i< temp.size();i++)
        {   
            if(w + temp[i] <= capacity)
            {
               w+= temp[i];
            }
            else{
                day++;
                w = temp[i];
            }
        }
        return day;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int maxi = -1;
        int sum = 0;

        for(int i =0; i< weights.size(); i++)
        {
            sum += weights[i];
            if(weights[i] > maxi)
            {
                maxi = weights[i];
            }
        }

        int low = maxi;
        int high = sum;
        int ans;

        while(low<=high)
        {
            int mid = (low + high)/2;

            int no_days = calcidays(weights,mid);

            if(no_days <= days)
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