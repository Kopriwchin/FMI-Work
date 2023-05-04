#include <iostream>
#include <vector>

using std::cout;
using std::vector;

vector<int> runningSum(const vector<int>& nums) {
    int size = nums.size();
    vector<int> result(size);
    result[0] = nums[0];
    for (int i = 1;i < size;i++) {
        result[i] = result[i - 1] + nums[i];
    }

    return result;
}

int main()
{
    vector<int> nums = runningSum({ 1,1,1,1,1 });
    for (size_t i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
}