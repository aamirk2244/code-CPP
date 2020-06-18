// build heap and hepify
#include<iostream>
class Max_Heap{
public:
	void heapify(int *h, int len, int root);
	void build_heap(int *h, int len);
	void heap_sort(int *h, int len);
	void print(int *h, int len);

};
void Max_Heap::heapify(int *h, int len, int root)
{
	int left =  (2 * root) + 1;
	int right =  (2 * root) + 2;
	int max = root;
	int swap;	// finding maximum in three ndoes
	if(left < len && h[left] > h[max])
		max = left;
	if(right < len && h[right] > h[max])
		max = right;
	if(max != root)
	{
		swap  = h[max];
		h[max] = h[root];
		h[root] = swap;
		heapify(h, len, max);
	}
}
void Max_Heap::build_heap(int *h, int len)
{
	
	// starting from end and heapify every element from end to top
	// I do len/2 because ist half of the complete binary tree nodes have childs
	// and end half are leaf nodes
	for(int i = len/2; i >= 0; i-- )
	{
		heapify(h, len , i);
	}
}
void Max_Heap::heap_sort(int *h, int len)
{
	build_heap(h, len);
	print(h, len);
	int swap;
	for(int i = len-1; i >= 0; i--)
	{
		swap = h[0];
		h[0] = h[i];
		h[i] = swap;
		len--;
		heapify(h, len, 0);
	}
	
}
void Max_Heap::print(int *h, int len)
{
	std::cout << std::endl;
	for(int i = 0 ; i < len; i++)
	{
		std::cout << h[i] << " ";
	}
	std::cout << std::endl;
}
int main()
{
	Max_Heap h;
	int len = 8;
	int arr[len] = {100, 5, 3, 2, 8, 15, 6, 102};
//	h.build_heap(arr, len);
	h.heap_sort(arr, len);
	h.print(arr, len);
}
