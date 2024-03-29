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

Node* removeNode(Node* root, int val)
{
    if (!root)
        return root;

    if (root->value > val)
    {
        root->left = removeNode(root->left, val);
        if (root->left) root->left->parent = root;  
        return root;
    }
    else if (root->value < val)
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
            root->value = succ->value;
            root->right = removeNode(root->right, succ->value);
            if (root->right) root->right->parent = root;  
        }
        else
        {
            root->value = succ->value;
            root->right = removeNode(root->right, succ->value);  // Powtórzone usuwanie
            if (root->right) root->right->parent = root;  
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
    int bf = tgt->balance;

    if (bf == -2)
    {
        int lbf = tgt->left->balance;
        if (lbf == 0 || lbf == -1)  //RR
        {
            rotateRight(tgt, root);
            return;
        }
        else //LR
        {
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
            rotateLeft(tgt, root);
            return;
        }
        else //RL
        {
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

    Node* leftImbalance = findImbalance(root->left); //Sprawdz lewe poddrzewo
    if (leftImbalance)
        return leftImbalance;

    int bf = root->balance; //Sprawdz obecny wezel
    if (bf < -1 || bf > 1)
        return root;

    return findImbalance(root->right); //Sprawdz prawe poddrzewo
}

void removeAVL(Node*& root, int val)
{
    root = removeNode(root, val);
    updateBalance(root);
;
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
    Node* recent = recInsert(root, val)->parent;
    updateBalance(root);

    //szukaj braku balansu
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
    int inputA[] = {
        8, 3, 10, 1, 6, 14, 4, 7, 13, 15, 2, 5, 9, 12, 16, 11, 17, 18, 20, 25,
        180, 185, 190, 195, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290,
        22, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105,
        440, 450, 460, 470, 480, 490, 500,510, 520, 530, 540, 550, 560, 570,
        670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800,
        110,115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175,
        300, 310, 320, 330, 340,350, 360, 370, 380, 390, 400, 410, 420, 430,
    };

    int inputB[] = {
        10, 5, 20, 25, -10
    };

    for (int i : inputA)
        insertAVL(root, i);

    print(root);

    for (int i : inputA)
        removeAVL(root, i);

    std::cout << "PO USUNIECIU:\n";
    print(root);
}
