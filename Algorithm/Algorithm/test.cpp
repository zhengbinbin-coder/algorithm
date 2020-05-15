#if 0
//查找数组(无序)中指定值的元素，返回下标
#include<iostream>
using namespace std;

//非递归写法
int FindValue(const int* br, int n, int val)
{
	int pos = -1;
	for (int i = 0; i < n; ++i)
	{
		if (br[i] == val)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

//递归写法
int FindValue_r(const int* br, int n, int val)
{
	if (n <= 0 || br[n - 1] == val)
	{
		return n - 1;
	}
	else
	{
		return FindValue_r(br, n - 1, val);
	}
}

int main()
{
	int arr[] = { 12, 34, 90, 87, 15, 100, 46, 58, 25 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int val = 46;
	int pos1 = FindValue(arr, n, val);
	int pos2 = FindValue_r(arr, n, val);
	printf("%d \n", pos1);
	printf("%d \n", pos2);
	system("pause");
	return 0;
}

//二分查找(要求数组有序)
#include<iostream>
using namespace std;

//递归写法
int FindValue_r(const int* br, int left, int right, int val)
{
	int pos = -1;
	if (NULL == br)	//安全检查
	{
		return pos;
	}
	if (left <= right)
	{
		int mid = (right - left + 1) / 2 + left;
		if (val < br[mid])
		{
			pos = FindValue_r(br, left, mid - 1, val);
		}
		else if (val>br[mid])
		{
			pos = FindValue_r(br, mid + 1, right, val);
		}
		else
		{
			//数组有重复元素并且要求返回最左边的元素下标
			while (pos > left&&br[mid - 1] == val)
			{
				--mid;
			}
			pos = mid;
		}
	}
	return pos;
}

//非递归写法
int FindValue(const int* br, int n, int val)
{
	int pos = -1;
	int left = 0, right = n - 1;
	if (NULL == br || n < 1)	//安全检查
	{
		return pos;
	}
	while (left <= right)	//要保证查询完所有元素，必须使left和right发生错位
	{						//如果只是left<right,可能会有一个元素查不到
		//int mid = (left + right) / 2;				//left加right大于整形时会发生整形溢出
		int mid = left + (right - left + 1) / 2;	//可以防止数组过大时left加right发生整形溢出
		if (val < br[mid])
		{
			right = mid - 1;
		}
		else if (val>br[mid])
		{
			left = mid + 1;
		}
		else
		{
			//数组有重复元素并且要求返回最左边的元素下标
			while (mid > left&&br[mid - 1] == val)
			{
				--mid;
			}
			////数组有重复元素并且要求返回最右边的元素下标
			//while (mid < right&&br[mid + 1] == val)
			//{
			//	++mid;
			//}
			pos = mid;
			break;
		}
	}
	return pos;
}

int main()
{
	int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int val = 50;
	int pos1 = FindValue(arr, n, val);
	int left = 0, right = n - 1;
	int pos2 = FindValue_r(arr, left, right, val);
	printf("%d \n", pos1);
	printf("%d \n", pos2);
	system("pause");
	return 0;
}

//全排列(排列树)
#include<iostream>
using namespace std;

void Swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

void Perm(int* br, int k, int m)
{
	if (k == m)//只有一个数据
	{
		for (int i = 0; i <= m; ++i)
		{
			cout << br[i] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int j = k; j <= m; ++j)
		{
			Swap(br[j], br[k]);
			Perm(br, k + 1, m);
			Swap(br[j], br[k]);
		}
	}
}

int main()
{
	int arr[] = { 1, 2, 3/*, 4, 5*/ };
	int n = sizeof(arr) / sizeof(arr[0]);
	Perm(arr, 0, n - 1);
	system("pause");
	return 0;
}

//子集树
#include<iostream>
using namespace std;

//递归实现
void fun_r(int* arr, int* brr, int i, int n)
{
	if (i >= n)
	{
		for (int j = 0; j < n; ++j)
		{
			if (brr[j])
			{
				cout << arr[j] << " ";
			}
		}
		cout << endl;
	}
	else
	{
		brr[i] = 1;
		fun_r(arr, brr, i + 1, n);
		brr[i] = 0;
		fun_r(arr, brr, i + 1, n);
	}
}

int main()
{
	int arr[] = { 1, 2, 3, 4 };
	int brr[] = { 0, 0, 0, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);

	fun_r(arr, brr, 0, n);	//递归实现

	//int i = 0;
	//brr[i] = -1;
	//while (i >= 0)
	//{
	//	brr[i] += 1;
	//	if (i >= n)
	//	{
	//		//print arr;
	//		--i;
	//	}
	//	else if (brr[i] == 2)
	//	{
	//		--i;
	//	}
	//	else
	//	{
	//		++i;
	//		brr[i] = -1;
	//	}
	//}

	system("pause");
	return 0;
}

//腾讯面试题:贪吃的小Q----利用二分查找降低时间复杂度
#include<iostream>
using namespace std;

int Sum(int n, int mid)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += mid;
		mid = (mid + 1) / 2;
	}
	return sum;
}

int Get_Max(int n, int m)
{
	int left = 1, right = m;
	while (left <= right)
	{
		int mid = (right + left) / 2;
		int sum = Sum(n, mid);
		bool tag = sum > m;
		if (tag)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return right;
}

int main()
{
	int nday, mcandy;
	while (cin >> nday >> mcandy, nday != -1 && mcandy > 0)
	{
		int maxcandy = Get_Max(nday, mcandy);
		cout << maxcandy << endl;
	}

	system("pause");
	return 0;
}

//归并排序
#include<iostream>

using namespace std;

template<class Type>
void print_arr(Type *arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class Type>
void Copy(Type *dest, Type *src, int left, int right)	//拷贝函数
{
	for (int i = left; i <= right; ++i)
	{
		dest[i] = src[i];
	}
}

template<class Type>
void merge(Type *dest, Type *src, int left, int m, int right)	//归并函数
{
	int i = left, j = m + 1;
	int k = left;
	while (i <= m && j <= right)
	{
		dest[k++] = src[i] < src[j] ? src[i++] : src[j++];
	}
	while (i <= m)
	{
		dest[k++] = src[i++];
	}
	while (j <= right)
	{
		dest[k++] = src[j++];
	}
}

template<class Type>
void merge_pass_r(Type *brr, Type *arr, int left, int right)	//递归划分
{
	if (left < right)
	{
		int m = (right - left) / 2 + left;
		merge_pass_r(brr, arr, left, m);
		merge_pass_r(brr, arr, m + 1, right);
		merge(brr, arr, left, m, right);
		Copy(arr, brr, left, right);
	}
}

template<class Type>
void merge_sort_r(Type *arr, int n)		//递归排序
{
	if (nullptr == arr || n <= 1)
	{
		return;
	}
	Type *brr = new Type[n];
	merge_pass_r(brr, arr, 0, n - 1);
	delete[]brr;

}

template<class Type>
void merge_pass(Type *dest, Type *src, int s, int n)	//非递归划分
{
	int i = 0;
	cout << "s : " << s << endl;		//查看
	for (i = 0; i + 2 * s - 1 <= n - 1; i = i + 2 * s)
	{
		merge(dest, src, i, i + s - 1, i + 2 * s - 1);
		cout << i << " " << i + s - 1 << " " << i + 2 * s - 1 << endl;	//查看
	}
	if (n - 1 > i + s - 1)
	{
		merge(dest, src, i, i + s - 1, n - 1);
		cout << i << " " << i + s - 1 << " " << n - 1 << endl;	//查看
	}
	else
	{
		for (int j = i; j < n; ++j)
		{
			dest[j] = src[j];
		}
	}
}

template<class Type>
void merge_sort(Type *arr, int n)	//非递归排序
{
	if (nullptr == arr || n <= 1)
	{
		return;
	}
	Type *brr = new Type[n];
	int s = 1;
	while (s < n)
	{
		merge_pass(brr, arr, s, n);
		s += s;
		merge_pass(arr, brr, s, n);
		s += s;
	}
	delete[]brr;
}

int main()
{
	int arr[] = { 34, 56, 78, 12, 23, 92, 86, 100, 45, 67 };
	int n = sizeof(arr) / sizeof(arr[0]);
	print_arr(arr, n);
	//merge_sort_r(arr, n);		//归并排序--递归
	merge_sort(arr, n);			//归并排序--非递归
	print_arr(arr, n);
	system("pause");
	return 0;
}
#endif

//快速排序
#include<iostream>
#include<time.h>
#include<stack>
#include<assert.h>

using namespace std;

template<class Type>
void print_arr(Type *arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class T>
int partition(T *arr, int left, int right)
{
	int i = left, j = right;
	T temp = arr[i];
	while (i < j)
	{
		while (i < j && arr[j] > temp)	--j;
		if (i < j)	arr[i] = arr[j];
		while (i < j && arr[i] <= temp)	++i;
		if (i < j)	arr[j] = arr[i];
	}
	arr[i] = temp;
	return i;
}

template<class T>
int one_partition(T *arr, int left, int right)
{
	int i = left + 1, j = i;
	while (j <= right)
	{
		if (arr[j] <= arr[left])
		{
			swap(arr[j], arr[i]);
			++j;
			++i;
		}
		++j;
	}
	i = i - 1;
	swap(arr[i], arr[left]);
	return i;
}

template<class T>
int rand_partition(T *arr, int left, int right)
{
	//随机划分法
	srand(time(NULL));
	int pos = rand() % (right - left + 1) + left;
	swap(arr[pos], arr[left]);
	//三位取中划分法
	//int mid = (right - left + 1) / 2 + left;
	return partition(arr, left, right);
}

template<class T>
void quick_pass(T *arr, int left, int right)
{
	if (left < right)
	{
		int mid = partition(arr, left, right);
		print_arr(arr, 10);		//看过程
		quick_pass(arr, left, mid - 1);
		quick_pass(arr, mid + 1, right);
	}
}

template<class T>
void nice_quick_pass(T *arr, int left, int right)
{
	stack<int> st;
	st.push(left);
	st.push(right);
	while (!st.empty())
	{
		right = st.top();	st.pop();
		left = st.top();	st.pop();
		int mid = partition(arr, left, right);
		if (left < mid - 1)
		{
			st.push(left);
			st.push(mid - 1);
		}
		if (mid + 1 < right)
		{
			st.push(mid + 1);
			st.push(right);
		}
	}
}

template <class T>
void quick_sort(T *arr, int n)		
{
	if (nullptr == arr || n <= 1)
		return;
	//quick_pass(arr, 0, n - 1);
	nice_quick_pass(arr, 0, n - 1);
}

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	Node* next;
}Node;

typedef struct
{
	Node* head;
	int cursize;
}LinkList;

Node* Buynode()
{
	Node* s = (Node*)malloc(sizeof(*s));
	if (NULL == s)	exit(EXIT_FAILURE);
	memset(s, 0, sizeof(Node));
	return s;
}

void Init_List(LinkList* plist)
{
	assert(plist != NULL);
	plist->head = Buynode();
	plist->cursize = 0;
}

void Print_List(LinkList* plist)
{
	assert(plist != NULL);
	Node* p = plist->head->next;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void push_front(LinkList* plist, ElemType val)
{
	assert(plist != NULL);
	Node* s = Buynode();
	s->data = val;
	s->next = plist->head->next;
	plist->head->next = s;
	plist->cursize += 1;
}

Node* ListPartition(Node* begin, Node* end)
{
	Node* i = begin, *j = i->next;
	while (j != end)
	{
		if (j->data < begin->data)
		{
			swap(i->next->data, j->data);
			i = i->next;
			j = j->next;
		}
		else
			j = j->next;
	}
	swap(begin->data, i->data);
	return i;
}

void ListQuickSort(Node* begin, Node* end)
{
	if (begin != end)
	{
		Node* mid = ListPartition(begin, end);
		ListQuickSort(begin, mid);
		ListQuickSort(mid->next, end);
	}
}

int main()
{
	LinkList mylist;
	Init_List(&mylist);
	for (int i = 0; i < 13; ++i)
	{
		push_front(&mylist, rand() % 100);
	}
	Print_List(&mylist);
	ListQuickSort(mylist.head->next, NULL);
	Print_List(&mylist);

	/*int arr[] = { 56, 34, 78, 12, 23, 92, 86, 100, 45, 67 };
	int n = sizeof(arr) / sizeof(arr[0]);
	print_arr(arr, n);
	quick_sort(arr, n);
	print_arr(arr, n);*/

	system("pause");
	return 0;
}














