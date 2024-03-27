#include <iostream>

struct Node {
	int val;
	Node* left;
	Node* right;
	Node* parent;

	Node(int val, Node* parent, Node* left = nullptr, Node* right = nullptr)
		: val(val), parent(parent), left(left), right(right) {}
};

void insert(Node*& root, int val, Node* parent = nullptr)
{
	if (!root)
		root = new Node(val, parent);

	else if (root->val > val)
		insert(root->left, val, root);
	else
		insert(root->right, val, root);
}

void inorder(Node* root)
{
	if (!root)
		return;

	inorder(root->left);
	std::cout << root->val << "\n";
	inorder(root->right);
}

Node* min(Node* root)	//przyjmuje, ze root != NULL
{
	if (root->left)
		return min(root->left);

	return root;
}

Node* max(Node* root)
{
	if (root->right)
		return max(root->right);

	return root;
}

Node* successor(Node* origin)
{
	if (origin->right)
		return min(origin->right);

	while (origin->parent)
	{
		if (origin->parent->left == origin)
			return origin->parent;

		origin = origin->parent;
	}

	return nullptr;
}

Node* predecesor(Node* origin)
{
	if (origin->left)
		return max(origin->left);

	while (origin->parent)
	{
		if (origin->parent->right == origin)
			return origin->parent;

		origin = origin->parent;
	}

	return nullptr;
}

Node*& find(Node* root, int val)
{
	if (!root)
		return root;

	if (root->val == val)
		return root;
	else if (val < root->val)
		return find(root->left, val);
	else
		return find(root->right, val);
}

Node* removeNode(Node* root, int val)
{
	if (!root)
		return root;

	if (root->val > val)
	{
		root->left = removeNode(root->left, val);
		if (root->left) root->left->parent = root;
		return root;
	}
	else if (root->val < val)
	{
		root->right = removeNode(root->right, val);
		if (root->right) root->right->parent = root;
		return root;
	}

	if (!root->left)
	{
		Node* tgt = root->right;
		if (tgt) tgt->parent = root->parent;
		delete root;
		return tgt;
	}
	else if (!root->right)
	{
		Node* tgt = root->left;
		if (tgt) tgt->parent = root->parent;
		delete root;
		return tgt;
	}
	else
	{
		Node* succ = successor(root);

		if (!succ->left)
		{
			root->val = succ->val;
			root->right = removeNode(root->right, succ->val);
			if (root->right) root->right->parent = root;
		}
		else
		{
			root->val = succ->val;
			root->right = removeNode(root->right, succ->val);  // Powtórzone usuwanie
			if (root->right) root->right->parent = root;
		}
		return root;
	}
}

int main()
{
	Node* root = nullptr;

	int inputs[] = { 10, 20, 15, 25};
	for (int i = 0; i < sizeof(inputs) / sizeof(int); i++)
		insert(root, inputs[i]);

	//inorder(root);

	//Node* x = find(root, 5);
	//if (x)
	//{
		//Node* succ = predecesor(x);
		//if (succ)
			//std::cout << succ->val;
	//}

	root = removeNode(root, 15);

	inorder(root);
}