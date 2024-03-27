#include <iostream>

struct Node {
	int val;
	int hl = 0, hr = 0, balance = 0;
	Node* parent, * left, * right;
	Node(int val, Node* parent, Node* left = nullptr, Node* right = nullptr) 
		: val(val), parent(parent), left(left), right(right){}
};

void update_balance(Node*& recent)
{
	
	if (!recent)
		return;

	int max = recent->hr;
	if (recent->hl > max)
		max = recent->hl;

	if (recent->parent)
	{
		if (recent->parent->right == recent)
			recent->parent->hr = max + 1;
		else
			recent->parent->hl = max + 1;

		update_balance(recent->parent);
	}

	recent->balance = recent->hr - recent->hl;

}

void insert(Node*& root, int val, Node* parent = nullptr)
{
	if (!root)
	{
		root = new Node(val, parent);
		update_balance(root);
	}

	else if (val < root->val)
		insert(root->left, val, root);
	else
		insert(root->right, val, root);
}

void inorder(Node* root)
{
	if (!root)
		return;

	inorder(root->left);
	std::cout << root->val << "\thl: " << root->hl << "\thr: " << root->hr << "\tbalance: " <<root->balance << "\n";
	inorder(root->right);
}

void leftRotation(Node*& recent)
{
	Node*& parent =  recent->parent;
	if (!parent)
		return;
	
	Node*& grandpa = parent->parent;
	if (!grandpa)
		return;

	//put parent as granpda
	parent->parent = grandpa->parent;

	if (grandpa->parent->left == grandpa)
		grandpa->parent->left = parent;
	else
		grandpa->parent->right = parent;

	grandpa->parent = nullptr;

	//grandpa becomes right son of parent
	Node* tgt = nullptr;

}

int main()
{
	Node* root = nullptr;
	insert(root, 1);
	insert(root, 2);
	insert(root, 3);

	inorder(root);
}