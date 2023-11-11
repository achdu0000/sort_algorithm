#include"CSort.h"
#define MAX_SIZE 4096

void input(char* str, int* nums, int* plen)
{
	int s = sizeof(str);
	scanf_s("%s", str, sizeof(char) * MAX_SIZE);
	int i = 0, count = 0, temp = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',') {
			nums[count++] = temp;
			temp = 0;
		}
		else {
			temp *= 10;
			temp += str[i] - '0';
			if (str[i + 1] == '\0')
				nums[count++] = temp;
		}
		i++;
	}
	*plen = count;
	printf("\n==========[Input N=%d]==========\n", count);
}

int main()
{
	char str[MAX_SIZE];
	int nums[MAX_SIZE];
	int len;
	input(str, nums, &len);
	CSort s(nums, len);

	for (int i = 0; i < 2; i++)
	{
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

		s.sort(CSort::Type::INSERTION_SORT);
		s.refresh_result();
		s.sort(CSort::Type::SHELL_SORT);
		s.refresh_result();
		s.sort(CSort::Type::BUBBLE_SORT);
		s.refresh_result();
		s.sort(CSort::Type::QUICK_SORT);
		s.refresh_result();
		s.sort(CSort::Type::SELECTION_SORT);
		s.refresh_result();
		s.sort(CSort::Type::HEAP_SORT);
		s.refresh_result();
		s.sort(CSort::Type::MERGE_SORT);
		s.refresh_result();
		s.sort(CSort::Type::COUNTING_SORT);
		s.refresh_result();
		s.sort(CSort::Type::BUCKET_SORT);
		s.refresh_result();

		s.set_sort_increasing(false);

	}

	return 0;
}
