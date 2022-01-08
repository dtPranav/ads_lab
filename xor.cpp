#include <iostream>
#include <bits/stdc++.h>
#include <cinttypes>
using namespace std;
class node
{
public:
    int data;
    node *xr = NULL;
    // node(int key)
    // {
    //     data = key;
    // }
};
node *Xor(node *a, node *b)
{
    return reinterpret_cast<node *>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

node *insert_front(node *head, int data)
{
    node *newNode = new node();
    newNode->data = data;
    newNode->xr = head;
    if (head != nullptr)
    {
        head->xr = Xor(head->xr, newNode);
    }
    head = newNode;
    return head;
}
node *insert_rear(node *head, int data)
{
    node *prev = nullptr;
    node *temp = head;
    node *next;
    while (temp->xr != prev)
    {
        next = Xor(temp->xr, prev);
        prev = temp;
        temp = next;
    }
    node *newNode = new node();
    newNode->data = data;
    temp->xr = Xor(prev, newNode);
    newNode->xr = Xor(temp, nullptr);
    return head;
}
node *delete_front(node *head)
{
    node *temp = head->xr;
    temp->xr = Xor(head, temp->xr);
    return head = temp;
}
node *deleterear(node *head)
{
    node *prev = nullptr;
    node *temp = head;
    node *next;
    while (temp->xr != prev)
    {
        next = Xor(temp->xr, prev);
        prev = temp;
        temp = next;
    }
    prev->xr = Xor(prev->xr, temp);
    return head;
}
void print(node *head)
{
    node *prev = nullptr;
    node *temp = head;
    node *next = temp;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        next = Xor(temp->xr, prev);
        prev = temp;
        temp = next;
    }
}
int main()
{
    node *head = nullptr;
    int n;
    while (true)
    {
        cout << "1-Insert Front\n"
             << "2-Insert Rear\n"
             << "3-Delete Front\n"
             << "4-Delete Rear\n"
             << "5-Print Nodes\n"
             << "6-Exit" << endl;
        int ch;
        cout << "Enter the choice" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            int data;
            cout << "Enter the data to insert front" << endl;
            cin >> data;
            head = insert_front(head, data);
            break;
        case 2:
            int data1;
            cout << "Enter the data to insert rear" << endl;
            cin >> data1;
            head = insert_rear(head, data1);
            break;
        case 3:
            head = delete_front(head);
            break;
        case 4:
            head = deleterear(head);
            break;
        case 5:
            print(head);
            break;
        case 6:
            exit(0);
        }
    }
    return 0;
}