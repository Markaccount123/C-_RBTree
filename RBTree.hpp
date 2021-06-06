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

	//��Ҫѡ���ƻ�����3��4�����һ����ʱ��ѡ��3�ȽϺ�---  һ�����������������ӽ���Ǻ�ɫ��
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
			_root->_col = BLACK; //�����������������ʣ������Ϊ��ɫ
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
		//��Ϊ�½ڵ��Ĭ����ɫ�Ǻ�ɫ����ˣ������˫�׽ڵ����ɫ�Ǻ�ɫ��û��Υ��������κ����ʣ�����Ҫ����
		while (parent && parent->_col == RED) //parent��Ϊ��������Ǻ�����
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���һ
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
			}
		}

		_root->_col = BLACK;//ʼ�հѸ���Ϊ��ɫ
		return maka_pair(newnode, bool);
	}
private:
	Node* _root;
};