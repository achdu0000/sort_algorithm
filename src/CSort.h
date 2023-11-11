#ifndef _CSORT_H_
#define _CSORT_H_

#include<stdio.h>
#include<Windows.h>

#define ENUM_NUM 10
#define REPEAT_TIMES 10000
//#define SHOW_RESULT_INFO

class CSort
{
public:
	enum class Type
	{
		INSERTION_SORT = 1,
		BUBBLE_SORT,
		SELECTION_SORT,
		SHELL_SORT,
		MERGE_SORT,
		QUICK_SORT,
		BUCKET_SORT,
		COUNTING_SORT,
		RADIX_SORT,
		HEAP_SORT,
	};
	CSort(int* nums, int len);
	~CSort();
	bool is_sort_increasing() { return this->sort_increasing; }
	const char* get_sort_increasing_str() { return this->sort_increasing ? "<" : ">"; }
	void set_sort_increasing(bool sort_increasing) {this->sort_increasing=sort_increasing; }
	int get_length() { return len; }
	int* get_results() { return this->results; }
	void refresh_result();
	void sort(Type type);
	void print_nums();
	void print_results();
private:
	int* nums;
	int* results;
	int len;
	bool sort_increasing;

	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER freq;

	// choose diffirent sort algorithm
	void _sort(void(CSort::*sort_func)(void));
	
	// this->sort_increasing? a>b:a<b
	bool compare(int a, int b);
	
	// T(N)=O(N^2)
	// S(N)=O(1)
	// stable
	void insertion_sort();
	
	// T(N)=O(N^2)
	// S(N)=1
	// stable
	void bubble_sort();
	
	// T(N)=O(N^2) (always)
	// S(N)=1
	// not stable
	void selection_sort();

	// T(N)=O(N^2) (for some N and step length d, T(N)=O(N^1.3))
	// S(N)=1
	// not stable
	// works not well for link list
	void shell_sort();
	
	// T(N)=O(N*log N)
	// S(N)=O(N)
	// stable
	void merge_sort();
	// for recursion
	// merge sort results[low...high]
	// assistant[] is for help space nums
	void _merge_sort_recursion(int* assistant,int low,int high);
	// kernel for merge
	// results[low...mid] and results[mid+1...high] is OK, just merge them
	// assistant[] is for help space nums
	void _merge_sort_kernel(int* assistant, int low, int mid, int high);

	// T(N)=O(N*h) (best h=log N, worse h=N (BiTree))
	// S(N)=O(h) (best h=log N,worse h=N (BiTree))
	// stable
	void quick_sort();
	// for recursion
	void _quick_sort_recursion(int low, int high);
	// return : int - the pivot position
	// partition results[] two part by the pivot(resuts[low])
	int _quick_sort_partition(int low, int high);

	// T(N)=O(N*log N)
	// S(N)=O(1)
	// not stable
	void heap_sort();
	// T(N)=O(N)
	void _heap_sort_build_heap();
	// the index of current root is k
	// the whole handling heap length is heap_len
	void _heap_sort_adjust(int k,int heap_len);

	// T(N)=O(d(N+r)) (r is radix, d=log_r max{a_i})
	// S(N)=O(r) (r is radix)
	// stable
	// difficult to generalize, but the design ideas of the algorithm can be flexibly uses
	// especially when r and d is small which will lead good efficiency
	void radix_sort();
	// use parameter  radix to get d
	int _radix_sort_get_d(int radix);

	// T(N)=O(N)
	// S(N)=O(a_max-a_min)
	// no stable to discuss
	// need too much space
	void counting_sort();

	// actually, a type of counting_sort just to save space
	// reduce the [a_min,a_max] to [a_min/n,a_max/n] as bucket
	// in each bucket, can sort use any sort algirothm above...
	// which reach a balance
	void bucket_sort();

};
#endif // !_CSORT_H_
