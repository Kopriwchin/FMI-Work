#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

// Time compexity - O(n) solution
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;

    for (int i = 0; i < nums.size(); i++) {
        if (map.find(target - nums[i]) == map.end())
            map[nums[i]] = i;
        else
        {
            cout << map[target - nums[i]] << ',' << i;
            return { map[target - nums[i]], i };
        }
    }

    return { -1, -1 };
}

int main()
{
	vector<int> nums = { 2,5,8,7 };
	twoSum(nums, 9); 
}