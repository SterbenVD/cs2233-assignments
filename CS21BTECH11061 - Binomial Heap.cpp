#include <iostream>
#include <algorithm>
using namespace std;

// Class for Faculty
class Faculty
{
public:
    int Age, order;
    Faculty *childlist;
    Faculty *sibling;
    // Constructor for the Faculty
    Faculty(int pAge)
    {
        Age = pAge;
        order = 0;
        childlist = NULL;
        sibling = NULL;
    }
};

// Merges two trees and returns root of tree
Faculty *BinoTreeUnion(Faculty *bt1, Faculty *bt2)
{
    if (bt1->Age > bt2->Age)
        swap(bt1, bt2);

    bt2->sibling = bt1->childlist;
    bt1->childlist = bt2;
    bt1->order++;

    return bt1;
}

// Class for Binomial Heap
class BinoHeap
{
public:
    Faculty *first, *last;
    // Constructor for the Data Structure
    BinoHeap()
    {
        first = NULL;
        last = NULL;
    }

    // Constructor for the Data Structure, if one root is passed
    BinoHeap(Faculty *Node)
    {
        first = Node;
        last = Node;
    }

    // Function Declaration
    BinoHeap *insertElement(int Age);
    void insertTreeAtEnd(Faculty *tree);
    void insertTreeAtStart(Faculty *tree);
    BinoHeap *deleteMin();
    void removeTree(Faculty *Node);

    // Sorts Trees in Heap in Ascending order, and merges them if order of 2 trees are same.
    void adjustTrees()
    {
        Faculty *prev, *curr, *next;
        if (first != NULL && last != NULL && last != first)
        {
            prev = NULL;
            curr = first;
            next = first->sibling;
            while (next != NULL)
            {
                Faculty *temp = next->sibling;
                if (curr->order < next->order)
                {

                    prev = curr;
                    curr = next;
                }
                else
                {
                    if (curr->order > next->order)
                    {
                        curr->sibling = temp;
                        if (prev != NULL)
                            prev->sibling = next;
                        else
                            first = next;
                        next->sibling = curr;
                        prev = next;
                    }
                    else if (curr->order == next->order)
                    {
                        curr = BinoTreeUnion(curr, next);
                        if (prev != NULL)
                            prev->sibling = curr;
                        else
                            first = curr;
                        curr->sibling = temp;
                    }
                    if (temp == NULL)
                        last = curr;
                }
                next = temp;
            }
        }
    }

    // Prints a Binomial Tree
    void printBinoTree(Faculty *Node)
    {
        while (Node != NULL)
        {
            cout << Node->Age << " ";
            printBinoTree(Node->childlist);
            Node = Node->sibling;
        }
    }

    // Prints a Binomial Heap
    void display()
    {
        Faculty *temp = first;
        if (temp == NULL)
            cout << "Empty\n";
        else
        {
            cout << "Root Nodes of Heap:-\n";
            while (temp != NULL)
            {
                cout << temp->Age;
                if (temp->sibling != NULL)
                    cout << "-->";
                temp = temp->sibling;
            }
            cout << "\n";
            temp = first;
            cout << "\nIndividual trees:\n";
            while (temp != NULL)
            {
                cout << temp->Age << " ";
                printBinoTree(temp->childlist);
                temp = temp->sibling;
                cout << "\n";
            }
        }
    }
};

// Inserts Tree at end of Binomial Heap
void BinoHeap::insertTreeAtEnd(Faculty *tree)
{
    if (first == NULL && last == NULL)
        first = tree;
    else
        last->sibling = tree;

    last = tree;
    tree->sibling = NULL;
}

// Inserts Tree at start of Binomial Heap
void BinoHeap::insertTreeAtStart(Faculty *tree)
{
    if (first == NULL && last == NULL)
    {
        last = tree;
        tree->sibling = NULL;
    }
    else
        tree->sibling = first;

    first = tree;
}

// Merges two binomial heaps and returns the resultant heap
BinoHeap *BinoHeapUnion(BinoHeap *bh1, BinoHeap *bh2)
{
    BinoHeap *newHeap = new BinoHeap();
    Faculty *it1 = bh1->first;
    Faculty *it2 = bh2->first;
    while (it1 != NULL && it2 != NULL)
    {
        if (it1->order < it2->order)
        {
            Faculty *temp = it1->sibling;
            newHeap->insertTreeAtEnd(it1);
            it1 = temp;
        }
        else
        {
            Faculty *temp = it2->sibling;
            newHeap->insertTreeAtEnd(it2);
            it2 = temp;
        }
    }

    Faculty *it = (it1 == NULL) ? it2 : it1;
    while (it != NULL)
    {
        Faculty *temp = it->sibling;
        newHeap->insertTreeAtEnd(it);
        it = temp;
    }
    newHeap->adjustTrees();
    return newHeap;
}

// Inserts the Node into the Data Structure
BinoHeap *BinoHeap::insertElement(int Age)
{
    Faculty *temp = new Faculty(Age);
    BinoHeap *newtree = new BinoHeap(temp);
    return BinoHeapUnion(newtree, this);
}

// Removes a tree from the heap(Only removes root)
void BinoHeap::removeTree(Faculty *Node)
{
    Faculty *temp = this->first;
    if (Node == temp)
    {
        this->first = temp->sibling;
        if (first == NULL)
            last = NULL;
    }
    else
    {
        while (temp != NULL)
        {
            if (Node == temp->sibling)
                break;
            temp = temp->sibling;
        }
        temp->sibling = temp->sibling->sibling;
        if (this->last == Node)
        {
            if (temp->sibling != NULL)
                this->last = temp->sibling;
            else
                this->last = temp;
        }
    }
    Node->sibling = NULL;
}

// Remove the min Node then rearranges the data structure (Children of min are inserted as trees to the heap)
BinoHeap *BinoHeap::deleteMin()
{
    Faculty *temp = this->first;
    if (temp == NULL)
        cout << "Empty Heap\n";
    else
    {
        Faculty *min = temp;
        while (temp != NULL)
        {
            if (temp->Age < min->Age)
                min = temp;
            temp = temp->sibling;
        }
        cout << "Min Element: " << min->Age << "\n";
        Faculty *curr = min->childlist;
        this->removeTree(min);
        if (curr == NULL)
            return this;
        else
        {
            BinoHeap *tempheap = new BinoHeap();
            while (curr != NULL)
            {
                Faculty *sib = curr->sibling;
                tempheap->insertTreeAtStart(curr);
                curr = sib;
            }
            if (this->first == NULL)
                return tempheap;
            else
                return BinoHeapUnion(tempheap, this);
        }
    }
    return NULL;
}

// Interactive Program to ease debugging all operations.
int main()
{
    BinoHeap *Fac = new BinoHeap();
    int x = 0;
    // Loop for the menu
    do
    {
        if (Fac == NULL)
            Fac = new BinoHeap();
        // Displays the Tree for easy
        // Fac->display();
        cout << "\nMenu:\n";
        cout << "Enter 1 to insert\nEnter 2 to delete min\nEnter 0 to Quit\n";
        cin >> x;
        int Age, pos;
        switch (x)
        {
        case 0:
            // To quit program
            break;
        case 1:
            // Insertion of Faculty into the Data Structure
            cout << "Enter Age of Faculty:";
            cin >> Age;
            Fac = Fac->insertElement(Age);
            break;
        case 2:
            // Deleting of Minimum Element from the Data Structure
            Fac = Fac->deleteMin();
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
            break;
        }
    } while (x != 0);
    delete (Fac);
}