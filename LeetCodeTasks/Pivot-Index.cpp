#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::endl;

int pivotIndex(const vector<int>& nums) {
	int rightSum = 0;
	int numsSize = nums.size();

	for (size_t i = 0; i < numsSize; i++)
	{
		rightSum += nums[i];
	}

	int leftSum = 0;

	for (int i = 0; i < numsSize; i++)
	{
		rightSum -= nums[i];

		if (rightSum == leftSum)
		{
			return i;
		}

		leftSum += nums[i];
	}
	
	return -1;
	
	/*int numsSize = nums.size();

	if (numsSize == 1)
		return 0;

	int leftSum = 0;
	int rightSum = 0;

	for (int i = 0; i < numsSize - 1; i++)
	{
		rightSum += nums[i + 1];
	}

	if (rightSum == 0)
		return 0;

	rightSum = 0;

	for (int i = 1; i < numsSize - 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			leftSum += nums[j];
		}
		for (int k = i + 1; k < numsSize; k++)
		{
			rightSum += nums[k];
		}

		if (leftSum == rightSum)
		{
			return i;
		}

		leftSum = 0;
		rightSum = 0;
	}

	for (int i = 0; i < numsSize - 1; i++)
	{
		leftSum += nums[i];
	}

	if (leftSum == 0)
		return numsSize - 1;


	return -1;*/
}

int main()
{
	cout << pivotIndex({ 2,1,-1 }) << endl;
	cout << pivotIndex({ 1,7,3,6,5,6 }) << endl;
}