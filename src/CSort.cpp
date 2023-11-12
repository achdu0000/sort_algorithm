#include "CSort.h"

CSort::CSort(int* nums, int len)
{
	this->nums = nums;
	this->len = len > 0 ? len : 0;
	results = (int*)malloc(sizeof(int) * len);
	if (results) 
		memcpy(results, nums, sizeof(int) * len);
	QueryPerformanceFrequency(&this->freq);
	this->dqFreq = (double)freq.QuadPart;
	sort_increasing = true;
}

CSort::~CSort()
{
	free(results);
}

void CSort::refresh_result()
{
	if (results)
		memcpy(results, nums, sizeof(int) * len);
}

void CSort::sort(Type type)
{
	void(CSort::*sort_func)(void) = nullptr;

	if (type == Type::INSERTION_SORT)
	{
		printf(">>>Insertion_sort begin...(%s)\n",get_sort_increasing_str());
		sort_func = &CSort::insertion_sort;
	}else if (type == Type::BUBBLE_SORT)
	{
		printf(">>>Bubble_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::bubble_sort;
	}else if (type == Type::BUCKET_SORT)
	{
		printf(">>>Bucket_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::bucket_sort;
	}else if (type == Type::COUNTING_SORT)
	{
		printf(">>>Counting_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::counting_sort;
	}else if (type == Type::HEAP_SORT)
	{
		printf(">>>Heap_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::heap_sort;
	}else if (type == Type::INSERTION_SORT)
	{
		printf(">>>Insertion_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::insertion_sort;
	}else if (type == Type::MERGE_SORT)
	{
		printf(">>>Merge_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::merge_sort;
	}else if (type == Type::QUICK_SORT)
	{
		printf(">>>Quick_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::quick_sort;
	}else if (type == Type::RADIX_SORT)
	{
		printf(">>>Radix_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::radix_sort;
	}else if (type == Type::SELECTION_SORT)
	{
		printf(">>>Selection_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::selection_sort;
	}else if (type == Type::SHELL_SORT)
	{
		printf(">>>Shell_sort begin...(%s)\n", get_sort_increasing_str());
		sort_func = &CSort::shell_sort;
	}

	if (sort_func)
	{
		QueryPerformanceCounter(&time_start);
		for (int i = 0; i < REPEAT_TIMES; i++)
		{
			_sort(sort_func);
		}
		QueryPerformanceCounter(&time_over);
		double run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / REPEAT_TIMES / dqFreq;
		printf("run_time=%f us\n", run_time);
#ifdef SHOW_RESULT_INFO
		print_results();
#endif // SHOW_RESULT_INFO
	}
}

void CSort::print_nums()
{
	if (len > 0)
	{
		printf("nums[]=%d", nums[0]);
		for (int i = 1; i < len; i++)
			printf(",%d", nums[i]);
		putchar('\n');
	}
}
void CSort::print_results()
{
	if (len > 0)
	{
		printf("results[]=%d", results[0]);
		for (int i = 1; i < len; i++)
			printf(",%d", results[i]);
		putchar('\n');
	}
}

void CSort::_sort(void(CSort::*sort_func)(void))
{
	(this->*sort_func)();
}

bool CSort::compare(int a, int b)
{
	return this->sort_increasing ? a > b:a < b;
}

void CSort::insertion_sort()
{
	if (len == 0)return;
	int i, j, temp;
	for (i = 1; i < len; i++)
	{
		temp = results[i];
		for (j = i - 1; j > -1 && compare(results[j], temp); j--)
			results[j + 1] = results[j];
		results[j+1] = temp;
	}
}

void CSort::bubble_sort()
{
	if (len == 0)return;
	int i, j, temp;
	bool exchange_flag;
	for (i = 0; i < len - 1; i++)
	{
		exchange_flag = false;
		for (j = len - 1; j > i; j--)
		{
			if (compare(results[j - 1],results[j]))
			{
				//swap results[j-1] and results[j]
				temp = results[j - 1];
				results[j - 1] = results[j];
				results[j] = temp;
				exchange_flag = true;
			}
		}
		if (!exchange_flag) //not exchange means we get the results, no need to go on
			return;
	}
}

void CSort::selection_sort()
{
	if (len == 0)return;
	int i, j, min_pos, temp;
	for (i = 0; i < len - 1; i++)
	{
		min_pos = i;
		for (j = i + 1; j < len; j++)
		{
			if (compare(results[min_pos], results[j]))
				min_pos = j;
		}
		//swap results[i] and results[min_pos]
		temp = results[i];
		results[i] = results[min_pos];
		results[min_pos] = temp;
	}
}

void CSort::shell_sort()
{
	if (len == 0)return;
	int d, i, j,temp;
	for (d = len / 2; d >= 1; d /= 2) //step length
	{
		for (i = d; i < len; i++)
		{
			temp = results[i];
			for (j = i - d; j > -1 && compare(results[j], temp); j -= d)
				results[j + d] = results[j];
			results[j + d] = temp;
		}
	}
}

void CSort::merge_sort()
{
	if (len == 0)return;
	int* assistant = (int*)malloc(sizeof(int) * len);
	_merge_sort_recursion(assistant, 0, len - 1);
	free(assistant);
}

void CSort::_merge_sort_recursion(int* assistant, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		_merge_sort_recursion(assistant, low, mid);
		_merge_sort_recursion(assistant, mid + 1, high);
		_merge_sort_kernel(assistant, low, mid, high);
	}
}

void CSort::_merge_sort_kernel(int* assistant, int low, int mid, int high)
{
	int i, j, k;
	for (k = low; k <= high; k++)
		assistant[k] = results[k];
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
	{
		if (!compare(assistant[i], assistant[j]))
			results[k] = assistant[i++];
		else
			results[k] = assistant[j++];
	}
	while (i <= mid) results[k++] = assistant[i++];
	while (j <= high) results[k++] = assistant[j++];
}

void CSort::quick_sort()
{
	if (len == 0)return;
	_quick_sort_recursion(0, len - 1);
}

void CSort::_quick_sort_recursion(int low, int high)
{
	if (low < high)
	{
		int pivot_pos = _quick_sort_partition(low, high);
		_quick_sort_recursion(low, pivot_pos - 1);
		_quick_sort_recursion(pivot_pos + 1, high);
	}
}

int CSort::_quick_sort_partition(int low, int high)
{
	int pivot = results[low];
	while (low < high)
	{
		while (low < high && (!compare(pivot, results[high])))
			--high;
		results[low] = results[high];
		while (low < high && (!compare(results[low], pivot)))
			++low;
		results[high] = results[low];
	}
	results[low] = pivot;
	return low;
}

void CSort::heap_sort()
{
	if (len == 0)return;
	_heap_sort_build_heap(); // T(N)=O(N)
	int temp;
	//T(N)=O(N*log N)
	for (int i = len-1; i >-1; i--)
	{
		temp = results[0];
		results[0] = results[i];
		results[i] = temp;
		_heap_sort_adjust(0, i-1);
	}

}

void CSort::_heap_sort_build_heap()
{
	for (int i = len / 2 - 1; i > -1; i--)
		_heap_sort_adjust(i, len);
}

void CSort::_heap_sort_adjust(int k, int heap_len)
{
	int temp = results[k];
	// results start at results[0] 
	// results[i] leftchild: 2*i+1,rightchild:2*i+2
	for (int i = 2 * k + 1; i < heap_len; i = 2 * i + 1) // init i is the leftchild of k
	{
		if (i + 1 < heap_len && compare(results[i + 1], results[i])) 
		// rightchild exist &&
		//	rightchild is bigger than leftchild(sort_increasing)
		//	or rightchild is smaller than leftchild(!sort_increasing)
			i++;
		if (!compare(results[i], temp)) // the child satisfy the condition of heap
			break;
		// the child not satisfy the condition of heap
		// make the child to be the parent
		// then down to check
		results[k] = results[i];
		k = i;
	}
	results[k] = temp;
}

//typedef struct radix_sort_queue
//{
//	int data;
//	struct radix_sort_queue* next;
//}radix_queue;
//
//radix_queue* init_queue(const int*nums,int n)
//{
//	radix_queue* head = (radix_queue*)malloc(sizeof(radix_queue));
//	radix_queue* p = head;
//	for (int i = 0; i < n; i++)
//	{
//		radix_queue* q = (radix_queue*)malloc(sizeof(radix_queue));
//		q->data = nums[i];
//		q->next = NULL;
//		p->next = q;
//		p = q;
//	}
//	return head;
//}
//
//void free_queue(radix_queue* head)
//{
//	if (!head)return;
//	radix_queue* p = head->next;
//	while (p)
//	{
//		head->next = p->next;
//		free(p);
//		p = head->next;
//	}
//	free(head);
//}
//
//radix_queue* init_queue_array(int n)
//{
//	radix_queue* queue_array = (radix_queue*)malloc(sizeof(radix_queue) * n);
//	for (int i = 0; i < n; i++)
//		queue_array[i].next = NULL;
//	return queue_array;
//}
//void free_queue_array(radix_queue* queue_array,int n)
//{
//	if (!queue_array)return;
//	for (int i = 0; i < n; i++)
//	{
//		free_queue(queue_array + i);
//	}
//	free(queue_array);
//}
void CSort::radix_sort()
{
	//if (len == 0)return;
	//int r = 10; // radix default is 10
	//int d = _radix_sort_get_d(r);
	//radix_queue* queue_array = init_queue_array(r);
	////results[] array to queue 
	//radix_queue* queue = init_queue(results, len);

	//free_queue(queue);
	//free_queue_array(queue_array, r);

}

int CSort::_radix_sort_get_d(int radix)
{
	int max = results[0];
	for (int i = 1; i < len; i++)
		if (results[i] > max)
			max = results[i];
	int d = 0;
	while (max)
	{
		max /= radix;
		d++;
	}
	return d;
}

void CSort::counting_sort()
{
	if (len == 0)return;
	int min = results[0], max = results[0];
	for (int i = 1; i < len; i++)
	{
		if (results[i] < min)min = results[i];
		if (results[i] > max)max = results[i];
	}
	int n = max - min + 1;
	int* assistant = (int*)malloc(sizeof(int) * n);
	if(assistant)memset(assistant, 0, sizeof(int) * n);
	int i, j, k = 0;
	for (i = 0; i < len; i++)
		assistant[results[i] - min] += 1;
	if (sort_increasing)
	{
		for (i = 0; i < n; i++)
		{
			for (j = assistant[i]; j > 0; j--)
			{
				results[k++] = min + i;
			}
		}
	}
	else
	{
		for (i = n-1; i >-1; i--)
		{
			for (j = assistant[i]; j > 0; j--)
			{
				results[k++] = min + i;
			}
		}
	}

	free(assistant);
}

void CSort::bucket_sort()
{
	if (len == 0)return;
	//n=1, bucket[i]=min+[i], min->max
	counting_sort();
}
