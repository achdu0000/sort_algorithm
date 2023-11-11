这是封装的面向对象实现的不同的排序算法，包括测试的随机数据的排序性能的比较，由于计时是通过Windows API函数实现的，故在除Windows平台外编译前需要重写计时函数。其中排序算法包括：

- INSERTION_SORT - 插入排序
- BUBBLE_SORT - 冒泡排序
- SELECTION_SORT - 选择排序
- SHELL_SORT - 希尔排序
- MERGE_SORT - 归并排序
- QUICK_SORT - 快速排序
- BUCKET_SORT - 桶排序
- COUNTING_SORT - 计数排序
- RADIX_SORT - 基数排序
- HEAP_SORT - 堆排序

其中，不同排序算法的复杂度、稳定性以及其他关键信息，均在`CSort.h`中函数定义时以注释的形式给出。具体算法执行过程的可视化模拟，可在 [旧金山大学搭建的Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html) 网站进行体验和进一步学习。

在`test_result.txt`中，随机生成了1024个范围在`[0,1000]` 内的整数进行测试，保存了输入数据和不同算法的性能指标，由于数据分布具有特殊性，其中性能测试的结果不太满意，另外可能有算法的实现的进一步优化的问题（如快速排序算法枢轴pivot的选取策略等），如果您有问题和更好的建议，欢迎通过issue交流讨论。
