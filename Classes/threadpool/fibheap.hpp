#ifndef __FIBHEAP_HPP__
#define __FIBHEAP_HPP__

#include <cstdlib>

/* 
 * 쳲������ѽ�㶨��
 * 
 * ��Ա����
 *  key���ؼ���
 *  degree����㺢�������еĺ�����Ŀ
 *  mark����ǽڵ����ϴγ�Ϊ��һ�����ĺ��Ӻ��Ƿ�ʧȥ������
 *  parent��ָ��˫�׽���ָ��
 *  child��ָ���ӽ���ָ��
 *  left��ָ�����ֵܵ�ָ��
 *  right��ָ�����ֵܵ�ָ��
 */
template<typename Key, typename Value>
struct FibHeapNode 
{
	Key key;
	Value val;
	size_t degree;
	bool mark;
	FibHeapNode<Key, Value>* parent;
	FibHeapNode<Key, Value>* child;
	FibHeapNode<Key, Value>* left;
	FibHeapNode<Key, Value>* right;
};

/*
 * 쳲�������
 *
 * ģ�����
 *  Key��쳲������ѵĹؼ���
 *  Compare���ؼ��ֵıȽϺ�������
 *    �������ͣ�int Compare(Key k1, Key k2){ //... };
 *    ����ֵ���� k1<k2,����ֵ <0; �� k1==k2,����ֵ =0; �� k1>k2,����ֵ >0
 *
 * ��Ա����
 *  m_min��쳲������ѵ���С��㣨����Ϊ�գ���ΪNULL��
 *  m_count����ǰ쳲��������еĽ�����
 *  m_minKey���û��涨����С�Ĺؼ��ֵ�ֵ
 *  compare���ؼ��ֵıȽϺ���ָ��
 */
template<typename Key, typename Value, typename Compare>
class FibHeap
{
public:
	FibHeap(Compare cmp, Key minKey);
	~FibHeap();

	virtual void Insert(FibHeapNode<Key, Value>* x);
	virtual void Delete(FibHeapNode<Key, Value>* x);
	virtual void DecreaseKey(FibHeapNode<Key, Value>* x, Key _newKey);
	virtual FibHeapNode<Key, Value>* ExtractMin();
	virtual const size_t Size() { return m_count; }

protected:
	typedef FibHeapNode<Key, Value> __fib_heap_node;
	typedef Key __fib_key;

	void consolidate();
	void heap_link(__fib_heap_node* y, __fib_heap_node* x);

	void cut(__fib_heap_node* x, __fib_heap_node* y);
	void cascading_cut(__fib_heap_node* y);

private:
	__fib_heap_node* m_min;
	size_t m_count;
	Key m_minKey;
	Compare compare;
};

/*
 * ���캯��
 *
 * ����
 *  cmp���ؼ��� Key �ıȽϺ���
 *  minKey����С�Ĺؼ���ֵ
 */
template<typename Key, typename Value, typename Compare>
inline FibHeap<Key, Value, Compare>::FibHeap(Compare cmp, Key minKey)
{
	m_count = 0;
	m_min = NULL;
	compare = cmp;
	m_minKey = minKey;
}

template<typename Key, typename Value, typename Compare>
inline FibHeap<Key, Value, Compare>::~FibHeap()
{
	__fib_heap_node* x = NULL;
	while (m_min){
		x = ExtractMin();
		if (x) {
			delete x;
		}
	}
}

/*
 * ����һ�����
 *
 * ����
 *  x��������Ľ�������
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::Insert(FibHeapNode<Key, Value>* x)
{
	x->degree = 0;
	x->parent = NULL;
	x->child = NULL;
	x->mark = false;

	if (m_min == NULL) {
		x->left = x;
		x->right = x;
		m_min = x;
	}
	else {
		x->left = m_min->left;
		x->right = m_min;
		m_min->left->right = x;
		m_min->left = x;
		if (compare(x->key, m_min->key) < 0) {
			m_min = x;
		}
	}

	m_count++;
}

/*
 * ɾ��һ�����
 *
 * ����
 *  x����ɾ���Ľ��ָ�루�ýڵ���Ҫ���Ѿ���쳲��������е�����
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::Delete(FibHeapNode<Key, Value>* x)
{
	DecreaseKey(x, m_minKey);
	__fib_heap_node* y = ExtractMin();
	if (y) {
		delete y;
	}
}

/*
 * �ؼ��ּ�ֵ
 *
 * ����
 *  x����ֵ�Ľ��
 *  _newKey���µĹؼ���ֵ
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::DecreaseKey(FibHeapNode<Key, Value>* x, Key _newKey)
{
	if (compare(_newKey, x->key) > 0) {
		// error: new key is greater than current key
		return;
	}

	__fib_heap_node* y = NULL;

	x->key = _newKey;
	y = x->parent;
	if (y != NULL && compare(x->key, y->key) < 0) {
		cut(x, y);
		cascading_cut(y);// x �������丸�ڵ� y �����ӵ���һ�������е��ĵڶ�������
	}

	if (compare(x->key, m_min->key) < 0) {
		m_min = x;
	}
}

/*
 * ��ȡ��С���
 *
 * ����ֵ
 *  FibHeapNode<Key>*����쳲������Ѳ�Ϊ�գ��򷵻�ָ����С����ָ�룻��쳲�������Ϊ�գ��򷵻� NULL
 */
template<typename Key, typename Value, typename Compare>
inline FibHeapNode<Key, Value>* FibHeap<Key, Value, Compare>::ExtractMin()
{
	__fib_heap_node* z = m_min;

	if (z != NULL) {
		// add each child x of z to the root list
		if (z->child) {
			__fib_heap_node* p = NULL;
			__fib_heap_node* x = z->child;
			do 
			{
				p = x->right;
				x->left = m_min->left;
				x->right = m_min;
				x->parent = NULL;
				m_min->left->right = x;
				m_min->left = x;
				x = p;
			} while (x != z->child);
		}
		
		// remove z from the root list
		z->left->right = z->right;
		z->right->left = z->left;
		m_count--;

		if (z == z->right) {
			m_min = NULL;
		}
		else {
			m_min = z->right;
			consolidate();
		}
	}

	// �ж� z ������������ϵ���Է�ֹ�û��������ڵ�����޸Ķ��ƻ�쳲������ѵ�����
	if (z) {
		z->parent = NULL;
		z->child = NULL;
		z->left = NULL;
		z->right = NULL;
	}

	return z;
}

template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::consolidate()
{
	__fib_heap_node** A = NULL; 
	__fib_heap_node* x = NULL;
	__fib_heap_node* y = NULL;
	__fib_heap_node* w = NULL;
	__fib_heap_node* p = NULL;
	int d = 0;
	int count = 0;

	A = new __fib_heap_node*[m_count]();
	for (size_t i = 0; i < m_count; ++i) {
		A[i] = NULL;
	}

	p = m_min;
	do 
	{
		count++;
		p = p->right;
	} while (p != m_min);

	w = m_min;
	while (count > 0){
		x = w;
		w = w->right;
		d = x->degree;
		while (A[d] != NULL) {
			y = A[d];// another node with the same degree as x
			if (compare(x->key, y->key) > 0) {
				p = y;
				y = x;
				x = p;
			}
			heap_link(y, x);
			A[d] = NULL;
			d = d + 1;
		}
		A[d] = x;

		count--;
	}

	m_min = NULL;
	for (size_t i = 0; i < m_count; ++i){
		if (A[i] != NULL) {
			if (m_min == NULL) {
				m_min = A[i];
			}
			else {
				if (compare(A[i]->key, m_min->key) < 0) {
					m_min = A[i];
				}
			}
		}
	}

	delete[] A;
}

/*
 * �� y ���ӵ� x
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::heap_link(__fib_heap_node * y, __fib_heap_node * x)
{
	// remove y from the root list
	y->right->left = y->left;
	y->left->right = y->right;

	// make y a child of x, incrementing x.degree
	__fib_heap_node* c = x->child;
	if (c == NULL) {
		y->left = y;
		y->right = y;
		x->child = y;
	}
	else {
		y->left = c->left;
		y->right = c;
		c->left->right = y;
		c->left = y;
	}

	y->parent = x;
	y->mark = false;
	x->degree++;
}

/*
 * �ж� x �븸�ڵ� y ֮������ӣ�ʹ x ��Ϊ���ڵ�
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::cut(__fib_heap_node * x, __fib_heap_node * y)
{
	// remove x from the child list of y, decrementing y.degree
	if (x->left != x /* || x->right != x*/){
		x->left->right = x->right;
		x->right->left = x->left;
		y->child = x->left;
	}
	else {
		y->child = x->child;
		if (x->child){
			x->child->parent = y;
		}
	}
	y->degree--;

	// add x to the root list
	x->left = m_min->left;
	x->right = m_min;
	m_min->left->right = x;
	m_min->left = x;
	x->parent = NULL;
	x->mark = false;
}

/*
 * �����ж�
 */
template<typename Key, typename Value, typename Compare>
inline void FibHeap<Key, Value, Compare>::cascading_cut(__fib_heap_node * y)
{
	__fib_heap_node* z = NULL;
	z = y->parent;
	if (z) {
		if (y->mark == false) {
			y->mark = true;
		}
		else {
			cut(y, z);
			cascading_cut(z);// �ݹ�����
		}
	}
}

#endif //! __FIBHEAP_HPP__