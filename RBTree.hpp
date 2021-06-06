#include<iostream>

enum Color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;


	enum Color _col;

	//非要选择破坏性质3和4里面的一个的时候，选择3比较好---  一个红结点他的两个孩子结点是黑色的
	RBTreeNode(const pair<K,V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
		, _kv(kv)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	pair<Node*,bool> Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK; //必须满足红黑树的性质，根结点为黑色
			return make_pair(_root, true);
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}

		cur = new Node(kv); //RED
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		Node* newnode = cur;
		//因为新节点的默认颜色是红色，因此：如果其双亲节点的颜色是黑色，没有违反红黑树任何性质，则不需要调整
		while (parent && parent->_col == RED) //parent不为空这个不是很明白
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况一
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
			}
		}

		_root->_col = BLACK;//始终把根变为黑色
		return maka_pair(newnode, bool);
	}
private:
	Node* _root;
};