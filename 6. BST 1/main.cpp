#include <iostream>

struct Node {
	int val;
	Node* left;
	Node* right;

Node(int val, Node* left = nullptr, Node*right = nullptr) : val(val), left(left), right(right){}
};

void insert(Node*& root, int val)
{
	if (!root)
		root = new Node(val);
	else if (root->val < val)
		insert(root->left, val);
	else
		insert(root->right, val);
}

void inorder(Node* root)
{
	if (!root)
		return;

	inorder(root->left);
	std::cout << root->val << "\n";
	inorder(root->right);
}

Node* find(Node* root, int val)
{
	if (!root)
		return nullptr;

	if (root->val == val)
		return root;
	else if (root->val < val)
		find(root->left, val);
	else
		find(root->right, val); 
}

//do domu: poprzednik, nastepnik, usuwanie wezla

int main()
{
	Node* root = nullptr;
	for (int i = 0; i < 10; i++)
		insert(root, i + 1);

	//inorder(root);

	//Node* ten = find(root, 10);
	//if(ten)
		//std::cout << ten->val;
}