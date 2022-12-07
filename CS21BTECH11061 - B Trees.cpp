#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define SIZE 5
using namespace std;

class Faculty
{
public:
    int Age[SIZE];
    int keys;
    Faculty *parent;
    Faculty *children[SIZE + 1];
    // Constructor for the Faculty
    Faculty()
    {
        keys = 0;
        parent = NULL;
        for (int i = 0; i <= SIZE; i++)
        {
            if (i != SIZE)
                Age[i] = -1;
            children[i] = NULL;
        }
    }

    int insert(int pAge)
    {
        for (int i = 0; i <= keys; i++)
        {
            if (i == keys)
            {
                Age[keys] = pAge;
                keys++;
                return i;
            }
            else if (pAge < Age[i])
            {
                for (int j = keys; j >= i; j--)
                {
                    if (j != i)
                        Age[j] = Age[j - 1];
                    children[j + 1] = children[j];
                }
                keys++;
                Age[i] = pAge;
                return i;
            }
        }
        return -1;
    }

    int remove(int pAge)
    {
        for (int i = 0; i < keys; i++)
        {
            if (pAge == Age[i])
            {
                for (int j = i; j <= keys; j++)
                {
                    if (j != keys)
                        Age[j] = Age[j + 1];
                    children[j] = children[j + 1];
                }
                Age[keys - 1] = -1;
                children[keys] == NULL;
                keys--;
                return i;
            }
        }
        return -1;
    }
};

class BTree
{
public:
    Faculty *head;

    // Constructor for the Data Structure
    BTree()
    {
        head = NULL;
    }

    // Displays the tree
    void display()
    {
        int l1 = 1, l2 = 0;
        queue<Faculty *> q;
        if (head != NULL)
            q.push(head);
        while (!q.empty())
        {
            Faculty *curr = q.front();
            q.pop();
            for (int i = 0; i <= curr->keys; i++)
            {
                if (i != curr->keys)
                    cout << curr->Age[i];
                if (i < curr->keys - 1)
                    cout << ",";
                if (curr->children[i] != NULL)
                {
                    q.push(curr->children[i]);
                    l2++;
                }
            }
            cout << ";";
            l1--;
            if (l1 == 0)
            {
                l1 = l2;
                cout << "\n";
                l2 = 0;
            }
        }
    }

    // Searches for the Faculty in the Data Structure by Age
    int search(int pAge)
    {
        Faculty *curr = head;
        while (curr != NULL)
        {
            for (int i = 0; i < curr->keys; i++)
            {
                int Age = curr->Age[i];
                if (Age == pAge)
                {
                    cout << "Present\n";
                    cout << "Age: " << Age << "\n";
                    return 1;
                }
                else if (pAge < Age)
                {
                    curr = curr->children[i];
                    break;
                }
                else if (i == curr->keys - 1)
                {
                    curr = curr->children[i + 1];
                    break;
                }
            }
        }
        cout << "Not Present\n";
        return -1;
    }

    // Check if Node has 5 elements
    void check_insertion(Faculty *Node)
    {
        Faculty *temp = Node;
        if (temp->keys == SIZE)
        {
            Faculty *left = new Faculty();
            for (int i = 0; i <= SIZE / 2; i++)
            {
                if (i != SIZE / 2)
                    left->insert(temp->Age[i]);
                left->children[i] = temp->children[i];
                if (temp->children[i] != NULL)
                    temp->children[i]->parent = left;
            }

            Faculty *right = new Faculty();
            for (int i = SIZE / 2 + 1; i <= SIZE; i++)
            {
                if (i != SIZE)
                    right->insert(temp->Age[i]);
                right->children[i - 1 - SIZE / 2] = temp->children[i];
                if (temp->children[i] != NULL)
                    temp->children[i]->parent = right;
            }

            Faculty *par;
            if (temp->parent == NULL)
            {
                par = new Faculty();
                head = par;
            }
            else
                par = temp->parent;
            int pos = par->insert(temp->Age[SIZE / 2]);
            left->parent = par;
            right->parent = par;
            par->children[pos] = left;
            par->children[pos + 1] = right;
            check_insertion(par);
        }
    }
    // Inserts the Node into the Data Structure
    int insert(int pAge)
    {
        Faculty *curr = head;
        if (head == NULL)
        {
            Faculty *temp = new Faculty();
            temp->insert(pAge);
            head = temp;
        }
        else
        {
            while (curr != NULL)
            {
                for (int i = 0; i < curr->keys; i++)
                {
                    int Age = curr->Age[i];
                    if (Age == pAge)
                    {
                        cout << "Already Present\n";
                        cout << "Age: " << Age << "\n";
                        cout << "Cannot Insert Faculty\n";
                        return -1;
                    }
                    else if (pAge < Age && curr->children[i] != NULL)
                    {
                        curr = curr->children[i];
                        break;
                    }
                    else if (i == curr->keys - 1 && curr->children[i + 1] != NULL)
                    {
                        curr = curr->children[i + 1];
                        break;
                    }
                    else if (pAge < Age || i == curr->keys - 1)
                    {
                        curr->insert(pAge);
                        check_insertion(curr);
                        curr = NULL;
                        break;
                    }
                }
            }
        }
        cout << "Inserted Faculty into Binary Search Tree\n";
        return 1;
    }

    int successor(Faculty *s, int index)
    {
        if (s->children[index + 1] == NULL)
            return -1;
        else
        {
            s = s->children[index + 1];
            while (s->children[0] != NULL)
                s = s->children[0];
            return s->Age[0];
        }
    }
    int predessor(Faculty *s, int index)
    {
        if (s->children[index] == NULL)
            return -1;
        else
        {
            s = s->children[index];
            while (s->children[s->keys] != NULL)
                s = s->children[s->keys];
            return s->Age[s->keys - 1];
        }
    }

    void check_deletion(Faculty *s)
    {
        if (s == head)
        {
            if (s->keys == 0)
                head = NULL;
        }
        else if (s->keys == 1)
        {
            int pos;
            Faculty *par = s->parent;
            for (int i = 0; i <= par->keys; i++)
            {
                if (s == par->children[i])
                {
                    pos = i;
                    break;
                }
            }
            int keyarr[2] = {-1, -1};
            if (pos != 0 && par->children[pos - 1] != NULL)
                keyarr[0] = par->children[pos - 1]->keys;

            if (pos != par->keys && par->children[pos + 1] != NULL)
                keyarr[1] = par->children[pos + 1]->keys;
            int ind = (keyarr[0] > keyarr[1]) ? 0 : 1;
            int par_index = (ind == 0) ? pos - 1 : pos;
            if (keyarr[ind] > SIZE / 2)
            {
                s->insert(par->Age[par_index]);
                if (ind == 0)
                {
                    s->children[0] = par->children[pos - 1]->children[par->children[pos - 1]->keys];
                    par->Age[par_index] = par->children[pos - 1]->Age[par->children[pos - 1]->keys - 1];
                    par->children[pos - 1]->keys--;
                    if (s->children[0] != NULL)
                        s->children[0]->parent = s;
                }
                else if (ind == 1)
                {
                    s->children[s->keys] = par->children[pos + 1]->children[0];
                    par->Age[par_index] = par->children[pos + 1]->Age[0];
                    par->children[pos + 1]->remove(par->children[pos + 1]->Age[0]);
                    if (s->children[s->keys] != NULL)
                        s->children[s->keys]->parent = s;
                }
            }
            else
            {
                Faculty *temp = new Faculty();
                if (ind == 0)
                    ind--;
                Faculty *mix = par->children[pos + ind];
                for (int i = 0; i <= mix->keys; i++)
                {
                    if (i != mix->keys)
                        temp->insert(mix->Age[i]);
                    temp->children[i] = mix->children[i];
                    if (mix->children[i] != NULL)
                        mix->children[i]->parent = temp;
                }
                temp->insert(par->Age[par_index]);
                int ke = temp->insert(s->Age[0]);
                for (int i = 0; i < 2; i++)
                {
                    temp->children[ke + i] = s->children[i];
                    if (s->children[i] != NULL)
                        s->children[i]->parent = temp;
                }
                temp->parent = par;
                par->remove(par->Age[par_index]);
                par->children[par_index] = temp;
                if (par->keys == 0)
                {
                    head = temp;
                    temp->parent = NULL;
                }
                else if (par != head && par->keys == 1)
                    check_deletion(par);
            }
        }
    }

    // Remove the required node if it exists
    int remove(Faculty *curr, int pAge)
    {
        if (curr != NULL)
        {
            int ans = 0;
            for (int i = 0; i < curr->keys; i++)
            {
                int Age = curr->Age[i];
                if (Age == pAge)
                {
                    if (curr->children[i] == NULL && curr->children[i + 1] == NULL)
                    {
                        curr->remove(Age);
                        check_deletion(curr);
                        return 1;
                    }
                    else
                    {
                        curr->Age[i] = successor(curr, i);
                        return remove(curr->children[i + 1], curr->Age[i]);
                    }
                }
                else if (pAge < Age)
                    return remove(curr->children[i], pAge);
                else if (i == curr->keys - 1)
                    return remove(curr->children[i + 1], pAge);
            }
        }
        return -1;
    }
};

// Interactive Program to ease debugging all operations.
int main()
{
    BTree *Fac = new BTree();
    int x = 0;
    // Loop for the menu
    do
    {
        // Fac->display();
        cout << "\nMenu:\n";
        cout << "Enter 1 to insert\nEnter 2 to search\nEnter 3 to delete\nEnter 0 to Quit\n";
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
            Fac->insert(Age);
            break;
        case 2:
            // Searching Faculty in Data Structure
            cout << "Enter Age of Faculty:";
            cin >> Age;
            pos = Fac->search(Age);
            break;
        case 3:
            // Deleting of Element from the Data Structure
            cout << "Enter Age of Faculty:";
            cin >> Age;
            if (Fac->remove(Fac->head, Age) == -1)
                cout << "Not found\n";
            else
                cout << "Deleted " << Age << " from BTree\n";
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
            break;
        }
    } while (x != 0);
    delete (Fac);
}