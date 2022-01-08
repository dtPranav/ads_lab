#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node **forward;
    Node(int key, int level)
    {
        this->key = key;
        forward = new Node *[level + 1];
        memset(forward, 0, sizeof(Node *) * (level + 1));
    }
};

class SkipList
{

    int MAXLVL;
    float P;
    int level;
    Node *header;

public:
    SkipList(int, float);
    int randomLevel();
    Node *createNode(int, int);
    void insertElement(int);
    void displayList();
    void delete_ele(int key);
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    header = new Node(-1, MAXLVL);
};

int SkipList::randomLevel()
{
    // float r = (float)rand() / RAND_MAX;
    // int lvl = 0;
    // while (r < P && lvl < MAXLVL)
    // {
    //     lvl++;
    //     r = (float)rand() / RAND_MAX;
    // }
    // return lvl;
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

Node *SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

void SkipList::insertElement(int key)
{
    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node *) * (MAXLVL + 1));
    Node *curr = header;
    for (int i = level; i >= 0; i--)
    {
        while (curr->forward[i] && curr->forward[i]->key < key)
            curr = curr->forward[i];
        update[i] = curr;
    }
    if (!curr->forward || curr->key != key)
    {
        int r = randomLevel();
        Node *temp = new Node(key, r);
        int j = r;
        while (j >= 0)
        {
            if (j > level)
                header->forward[j] = temp;
            else
            {
                temp->forward[j] = update[j]->forward[j];
                update[j]->forward[j] = temp;
            }
            j--;
        }
        if (r > level)
            level = r;
        cout << "Successfully Inserted key " << key << "\n";
    }
    // Node *current = header;
    // Node *update[MAXLVL + 1];
    // memset(update, 0, sizeof(Node *) * (MAXLVL + 1));
    // for (int i = level; i >= 0; i--)
    // {
    //     while (current->forward[i] != NULL &&
    //            current->forward[i]->key < key)
    //         current = current->forward[i];
    //     update[i] = current;
    // }
    // if (current == NULL || current->key != key)
    // {
    //     int rlevel = randomLevel();
    //     Node *newNode = createNode(key, rlevel);
    //     int j = rlevel;
    //     while (j >= 0)
    //     {
    //         if (j > level)
    //             header->forward[j] = newNode;
    //         else
    //         {
    //             newNode->forward[j] = update[j]->forward[j];
    //             update[j]->forward[j] = newNode;
    //         }
    //         j--;
    //     }
    //     if (rlevel > level)
    //         level = rlevel;
    //     cout << "Successfully Inserted key " << key << "\n";
    // }
};

void SkipList::displayList()
{
    cout << "\n*****Skip List*****"
         << "\n";
    for (int i = level; i >= 0; i--)
    {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};
void SkipList::delete_ele(int key)
{
    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(MAXLVL + 1));
    Node *curr = header;
    for (int i = level; i >= 0; i--)
    {
        while (curr->forward[i] && curr->forward[i]->key < key)
            curr = curr->forward[i];
        update[i] = curr;
    }
    curr = curr->forward[0];
    if (curr && curr->key == key)
    {
        for (int i = 0; i <= level; i++)
        {
            if (update[i]->forward[i]->key != key)
                break;
            else
                update[i]->forward[i] = curr->forward[i];
        }
    }
};
int main()
{
    srand((unsigned)time(0));

    SkipList lst(3, 0.5);

    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
    lst.insertElement(9);
    lst.insertElement(12);
    lst.insertElement(19);
    lst.insertElement(17);
    lst.insertElement(26);
    lst.insertElement(21);
    lst.insertElement(21);
    lst.displayList();
    lst.delete_ele(19);
    lst.displayList();
}