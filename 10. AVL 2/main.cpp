#include <iostream>

struct Node
{
    int value, balance;
    Node* left, * right, * parent;

    Node(int value, Node* parent, Node* left = nullptr, Node* right = nullptr, int balance = 0)
        : value(value), parent(parent), left(left), right(right), balance(balance) {}
};


int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}

int getHeight(Node* root, int sum = 0)
{
    if (!root)
        return sum;

    sum++;
    return max(getHeight(root->left, sum), getHeight(root->right, sum));
}

void updateBalance(Node*& root)
{   
    if (!root)
        return;

    root->balance = getHeight(root->right) - getHeight(root->left);

    updateBalance(root->left);
    updateBalance(root->right);
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

void removeNode(Node*& tgt, Node*& root) {
    if (!tgt)
        return;

    if (tgt->right && tgt->left) // tgt has both children
    {
        Node* scc = successor(tgt);
        tgt->value = scc->value;

        // Recursively remove the successor
        if (scc->parent->left == scc)
            removeNode(scc->parent->left, root);
        else
            removeNode(scc->parent->right, root);
    }
    else if (tgt->left || tgt->right) // tgt has only one child
    {
        Node* child = (tgt->left) ? tgt->left : tgt->right;
        Node* to_delete = tgt;

        tgt = child;
        tgt->parent = to_delete->parent;  // Update parent pointer

        // Update parent's child pointer
        if (to_delete->parent) {
            if (to_delete->parent->left == to_delete)
                to_delete->parent->left = tgt;
            else
                to_delete->parent->right = tgt;
        }
        else {
            root = tgt;  // Update root if tgt was the root
        }

        delete to_delete;
    }
    else // tgt has no children
    {
        if (tgt->parent) // Update parent pointer for the node being deleted
        {
            if (tgt->parent->left == tgt)
                tgt->parent->left = nullptr;
            else
                tgt->parent->right = nullptr;
        }
        else {
            root = nullptr;  // tgt is the root, set root to nullptr
        }
        delete tgt;
        tgt = nullptr;
    }
}

Node* deleteNode(Node* root, int k)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of node to be deleted
    if (root->value > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->value < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // Node to be deleted is found (root->value == k)

    // If one of the children is empty
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }

    // If both children exist
    else {
        // Find successor
        Node* succ = successor(root);

        // If successor is the direct right child
        if (succ->left == NULL) {
            root->value = succ->value;  // Copy successor's value to root
            root->right = deleteNode(root->right, succ->value);  // Delete successor
        }
        else {
            // Successor is further down the right subtree
            root->value = succ->value;  // Copy successor's value to root
            deleteNode(root, succ->value);  // Delete successor
        }
        return root;
    }
}

Node* findNode(Node* root, int val)
{
    if (!root)
        return nullptr;

    if (root->value == val)
        return root;

    if (val < root->value)
        return findNode(root->left, val);
    else
        return findNode(root->right, val);
}

void rotateLeft(Node*& A, Node*& root)  //Obracanie zachodzi wokol A. Przyjmuje, ze A->right->right istnieje
{
    std::cout << "ROTATELEFT\n";
    Node* Ap = A->parent;
    Node* B = A->right, * Br = B->left;

    if (Br)  //obrot
        Br->parent = A;

    A->right = Br;
    A->parent = B;
    B->left = A;
    B->parent = Ap;


    if (Ap) //jezeli A ma rodzica to ustaw jego dziecko jako B
    {
        if (Ap->left == A)
            Ap->left = B;
        else
            Ap->right = B;
    }
    else    //jezeli A nie ma rodzica to musi byc rootem
        root = B;

    updateBalance(root);
}

void rotateRight(Node*& A, Node*& root)  //Obracanie zachodzi wokol A. Przyjmuje, ze A->left->left istnieje
{
    std::cout << "ROTATERIGHT\n";
    Node* Ap = A->parent;
    Node* B = A->left, * Br = B->right;

    if (Br)  //obrot
        Br->parent = A;

    A->left = Br;
    A->parent = B;
    B->right = A;
    B->parent = Ap;

    if (Ap) //jezeli A ma rodzcica to ustaw jego dziecko jako B
    {
        if (Ap->left == A)
            Ap->left = B;
        else
            Ap->right = B;
    }
    else    //jezeli A nie ma rodzica to musi byc rootem
        root = B;

    updateBalance(root);
}

void rebalance(Node*& tgt, Node*& root)
{
    std::cout << "REBALANCE\n";

    int bf = tgt->balance;

    if (bf == -2)
    {
        int lbf = tgt->left->balance;
        if (lbf == 0 || lbf == -1)  //RR
        {
            std::cout << "RR\n";
            rotateRight(tgt, root);
            return;
        }
        else //LR
        {
            std::cout << "LR\n";
            rotateLeft(tgt->left, root);
            rotateRight(tgt, root);
            return;
        }
    }
    else if (bf == 2)
    {
        int rbf = tgt->right->balance;
        if (rbf == 1 || rbf == 0)   //LL
        {
            std::cout << "LL\n";
            rotateLeft(tgt, root);
            return;
        }
        else //RL
        {
            std::cout << "RL\n";
            rotateRight(tgt->right, root);
            rotateLeft(tgt, root);
            return;
        }
    }
}

Node* findImbalance(Node* root) //Zwraca pierwszy niezbalansowany wezel jaki znajdzie
{
    if (!root) 
        return nullptr;

    //Sprawdz lewe poddrzewo
    Node* leftImbalance = findImbalance(root->left);
    if (leftImbalance) 
        return leftImbalance;

    //Sprawdz obecny wezel
    int bf = root->balance;
    if (bf < -1 || bf > 1)
        return root;

    //Sprawdz prawe poddrzewo
    return findImbalance(root->right);
}

void removeAVL(Node*& root, int val)
{
    std::cout << "REMOVEAVL\n";
    root = deleteNode(root, val);
    updateBalance(root);
    std::cout << "BALANCE AFTER REMOVAL:\n";
    //Zbalansuj drzewo
    Node* bad = findImbalance(root);
    while (bad)
    {
        rebalance(bad, root);
        bad = findImbalance(root);
    }
}

Node* recInsert(Node*& root, int val, Node* parent = nullptr)
{
    if (!root) 
    {
        root = new Node(val, parent);
        return root;
    }

    else if (val < root->value)  // smaller
        return recInsert(root->left, val, root);
    else if (val >= root->value)  // larger
        return recInsert(root->right, val, root);
}

void insertAVL(Node*& root, int val)
{
    Node* recent = recInsert(root, val);
    updateBalance(root);

    std::cout << "INSERT\n";

    //look up for inbalance
    while (recent)
    {
        int bf = recent->balance;
        if (bf > 1 || bf < -1)
            rebalance(recent, root);

        recent = recent->parent;
    }
}

void print(Node* root)
{
    if (!root)
        return;

    print(root->left);
    std::cout << "V:" << root->value << "\tB:" << root->balance << "\n";
    print(root->right);
}


int main()
{
    Node* root = nullptr;
    int input[] = { 
        8, 3, 10, 1, 6, 14, 4, 7, 13, 15, 2, 5, 9, 12, 16, 11, 17, 18, 20, 25,
        22, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 
        110,115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 
        180, 185, 190, 195, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290,
        300, 310, 320, 330, 340,350, 360, 370, 380, 390, 400, 410, 420, 430, 
        440, 450, 460, 470, 480, 490, 500,510, 520, 530, 540, 550, 560, 570,
        670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800,
    };

    for (auto i : input)
        insertAVL(root, i);

    print(root);

    for(auto i : input)
        removeAVL(root, i);

    print(root);
}
