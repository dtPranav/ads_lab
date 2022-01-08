#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

Node *newNode(int key)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node *rightRotate(Node *root)
{
    if (!root)
        return nullptr;
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height(root->left),
                       height(root->right)) +
                   1;
    temp->height = max(height(temp->left),
                       height(temp->right)) +
                   1;
    return temp;
    // Node *r = node->left;
    // Node *t = r->right;
    // r->right = node;
    // node->left = t;

    // node->height = max(height(node->left),
    //                    height(node->right)) +
    //                1;
    // r->height = max(height(r->left),
    //                 height(r->right)) +
    //             1;

    // return r;
}

Node *leftRotate(Node *root)
{
    // Node *r = node->right;
    // Node *t = r->left;
    // r->left = node;
    // node->right = t;

    // node->height = max(height(node->left),
    //                    height(node->right)) +
    //                1;
    // r->height = max(height(r->left),
    //                 height(r->right)) +
    //             1;

    // return r;
    if (!root)
        return nullptr;
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(height(root->left),
                       height(root->right)) +
                   1;
    temp->height = max(height(temp->left),
                       height(temp->right)) +
                   1;
    return temp;
}

int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *insert(Node *root, int key)
{
    if (!root)
        return (newNode(key));
    if (root->key > key)
        root->left = insert(root->left, key);
    else if (root->key < key)
        root->right = insert(root->right, key);
    else
        return root;
    root->height = max(height(root->left), height(root->right)) + 1;
    int b = getBalance(root);
    if (b < -1 && key > root->right->key)
        return leftRotate(root);
    if (b > 1 && key < root->left->key)
        return rightRotate(root);
    if (b < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    if (b > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
    // if (node == NULL)
    //     return (newNode(key));

    // if (key < node->key)
    //     node->left = insert(node->left, key);
    // else if (key > node->key)
    //     node->right = insert(node->right, key);
    // else
    //     return node;

    // node->height = 1 + max(height(node->left), height(node->right));
    // int balance = getBalance(node);

    // if (balance > 1 && key < node->left->key)
    //     return rightRotate(node);

    // if (balance < -1 && key > node->right->key)
    //     return leftRotate(node);

    // if (balance > 1 && key > node->left->key)
    // {
    //     node->left = leftRotate(node->left);
    //     return rightRotate(node);
    // }

    // if (balance < -1 && key < node->right->key)
    // {
    //     node->right = rightRotate(node->right);
    //     return leftRotate(node);
    // }

    // return node;
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = NULL;
    int n, key;
    cout << "Enter the number of nodes: " << endl;
    cin >> n;
    cout << "Enter the node values" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> key;
        root = insert(root, key);
    }

    cout << "Preorder traversal of the AVL tree is: " << endl;
    preOrder(root);
    cout << endl;
    cout << "Enter the node value to be deleted: " << endl;
    cin >> key;
    root = deleteNode(root, key);
    cout << "Preorder traversal of the AVL tree after deletion is: " << endl;
    preOrder(root);
    cout << endl;

    return 0;
}