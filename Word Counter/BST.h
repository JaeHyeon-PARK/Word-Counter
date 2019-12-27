#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>

using std::string;

template <typename KeyT, typename ValueT>
class BST {
	int node_count = 0;
	int node_level = 0;
	template <typename KeyT, typename ValueT>
	struct node {
		KeyT key;
		ValueT value;
		struct node *llink;
		struct node *rlink;
	};

	struct node<KeyT, ValueT> *root;

public:
	BST();
	int getValue(const KeyT&, ValueT&);
	void insertNode(const KeyT&, const ValueT&);
	void updateNode(const KeyT&, const ValueT&);
	void printTree();
	void inorder();

	int getNodeCount(struct node<KeyT, ValueT> *);
	int getTreeLevel(struct node<KeyT, ValueT> *);
};

template <typename KeyT, typename ValueT>
BST <KeyT, ValueT>::BST() {
	root = NULL;
}

template <typename KeyT, typename ValueT>
int BST <KeyT, ValueT>::getValue(const KeyT& token, ValueT& count) {
	struct node<KeyT, ValueT> *ptr;
	string charToStr(token);

	if (root == NULL)
		return -1;

	for (ptr = root; ptr != NULL;) {
		if (ptr->key == charToStr) {
			count = ptr->value;
			return 0;
		}
		else if (charToStr < ptr->key)
			ptr = ptr->llink;
		else
			ptr = ptr->rlink;
	}
	return -1;
}

template <typename KeyT, typename ValueT>
void BST <KeyT, ValueT>::insertNode(const KeyT& token, const ValueT& count) {
	struct node<KeyT, ValueT> *ptr;
	struct node<KeyT, ValueT> *parent = NULL;
	string charToStr(token);

	for (ptr = root; ptr != NULL; ) {
		if (ptr->key == charToStr)
			parent = NULL;
		if (charToStr < ptr->key) {
			if (ptr->llink == NULL) {
				parent = ptr; break;
			}
			else ptr = ptr->llink;
		}
		else {
			if (ptr->rlink == NULL) {
				parent = ptr; break;
			}
			else ptr = ptr->rlink;
		}
	}

	if (parent || (root == NULL)) {
		ptr = new struct node<KeyT, ValueT>;
		ptr->key = charToStr;
		ptr->value = count;
		ptr->llink = ptr->rlink = NULL;

		if (root) {
			if (charToStr < parent->key)
				parent->llink = ptr;
			else
				parent->rlink = ptr;
		}
		else root = ptr;
	}
}

template <typename KeyT, typename ValueT>
void BST <KeyT, ValueT>::updateNode(const KeyT& token, const ValueT& count) {
	struct node<KeyT, ValueT> *ptr;
	string charToStr(token);

	for (ptr = root; ptr != NULL;) {
		if (ptr->key == charToStr) {
			ptr->value = count;
			break;
		}
		else if (charToStr < ptr->key)
			ptr = ptr->llink;
		else
			ptr = ptr->rlink;
	}
}

template <typename KeyT, typename ValueT>
void BST <KeyT, ValueT>::printTree() {
	node_count = getNodeCount(root);
	node_level = getTreeLevel(root);
	printf(" - 트리의 깊이 = %d\n", node_level);
	printf(" - 트리의 노드 수 = %d\n", node_count);
}

template <typename KeyT, typename ValueT>
void BST <KeyT, ValueT>::inorder() {
	struct node<KeyT, ValueT> *ptr = root;

	struct node<KeyT, ValueT> *current, *prev;
	if (root == NULL)
		return;

	current = root;
	while (current != NULL) {
		if (current->llink == NULL) {
			std::cout << "[ " << current->key << ", " << current->value << " ]" << std::endl;
			current = current->rlink;
		}
		else {
			prev = current->llink;
			while (prev->rlink != NULL && prev->rlink != current)
				prev = prev->rlink;
			if (prev->rlink == NULL) {
				prev->rlink = current;
				current = current->llink;
			}
			else {
				prev->rlink = NULL;
				std::cout << "[ " << current->key << ", " << current->value << " ]" << std::endl;
				current = current->rlink;
			}
		}
	}
}

template <typename KeyT, typename ValueT>
int BST <KeyT, ValueT>::getNodeCount(struct node<KeyT, ValueT> *root) {
	int count = 0;
	if (root != NULL)
		count = 1 + getNodeCount(root->llink) + getNodeCount(root->rlink);
	return count;
}

template <typename KeyT, typename ValueT>
int BST <KeyT, ValueT>::getTreeLevel(struct node<KeyT, ValueT> *root) {
	int count = 0;
	int highNode;

	if (root != NULL)
		count = 1 + (highNode = getTreeLevel(root->llink) > getTreeLevel(root->rlink) ? getTreeLevel(root->llink) : getTreeLevel(root->rlink));
	return count;
}

#endif