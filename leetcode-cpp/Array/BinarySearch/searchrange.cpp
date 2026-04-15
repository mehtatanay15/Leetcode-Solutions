class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1, last = -1;
        int l = 0, r = nums.size() - 1;

        // find first occurrence
        while(l <= r)
        {
            int mid = (l + r) / 2;

            if(nums[mid] == target)
            {
                first = mid;
                r = mid - 1;  // go left
            }
            else if(nums[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        l = 0, r = nums.size() - 1;

        // find last occurrence
        while(l <= r)
        {
            int mid = (l + r) / 2;

            if(nums[mid] == target)
            {
                last = mid;
                l = mid + 1;  // go right
            }
            else if(nums[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return {first, last};
    }
};