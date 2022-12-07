#include <iostream>
// Algorithm is used for some string functions
#include <algorithm>
using namespace std;

// Class for Faculty
class Faculty
{
public:
    string Name, Department;
    char Gender;
    int Age;
    Faculty *left, *right;
    bool cLeft, cRight;
    // Constructor for the Faculty
    Faculty(int pAge, string pName, string pDepartment, char pGender)
    {
        Age = pAge;
        Gender = pGender;
        Name = pName;
        Department = pDepartment;
        left = NULL;
        cLeft = 0;
        right = NULL;
        cRight = 0;
    }
};

class BST
{
public:
    Faculty *head;

    // Constructor for the Data Structure
    BST()
    {
        head = NULL;
    }

    // Searches for the Faculty in the Data Structure by Name
    int search(string Name)
    {
        Faculty *curr = head;
        while (curr != NULL)
        {
            if (!curr->Name.compare(Name))
            {
                cout << "Present\n";
                cout << "Name: " << curr->Name << "\n";
                cout << "Department: " << curr->Department << "\n";
                cout << "Age: " << curr->Age << "\n";
                cout << "Gender: " << curr->Gender << "\n";
                return 1;
            }
            else
            {
                if (curr->Name.compare(Name) > 0 && curr->cLeft == 1)
                    curr = curr->left;
                else if (curr->Name.compare(Name) < 0 && curr->cRight == 1)
                    curr = curr->right;
                else
                    break;
            }
        }
        cout << "Not Present\n";
        return -1;
    }

    // Inserts the Node into the Data Structure
    void insert(int Age, string Name, string Department, char Gender)
    {
        if (search(Name) == -1)
        {
            Faculty *temp = new Faculty(Age, Name, Department, Gender);
            if (head == NULL)
            {
                head = temp;
            }
            else
            {
                Faculty *curr = head;
                while (curr != NULL)
                {
                    if (curr->Name.compare(Name) > 0)
                    {
                        if (curr->cLeft == 0)
                        {
                            temp->left = curr->left;
                            temp->right = curr;
                            curr->cLeft = 1;
                            curr->left = temp;
                            break;
                        }
                        else
                            curr = curr->left;
                    }
                    else
                    {
                        if (curr->cRight == 0)
                        {
                            temp->left = curr;
                            temp->right = curr->right;
                            curr->cRight = 1;
                            curr->right = temp;
                            break;
                        }
                        else
                            curr = curr->right;
                    }
                }
            }
            cout << "Inserted Faculty into Binary Search Tree\n";
        }
        else
            cout << "Cannot Insert Faculty\n";
    }

    // Returns right successor if it exists.
    Faculty *getSuccessor(Faculty *s)
    {
        if (s->cRight == 1)
        {
            s = s->right;
            while (s->cLeft == 1 && s->left != NULL)
                s = s->left;
            return s;
        }
        else
            return NULL;
    }

    // Remove the required node if it exists
    Faculty *remove(Faculty *s, string pName, char lrpos)
    {
        if (s == NULL)
            cout << "Not Present\n";
        else if (s->Name > pName)
            s->left = remove(s->left, pName, 'L');
        else if (s->Name < pName)
            s->right = remove(s->right, pName, 'R');
        else
        {
            if (s->cLeft == 0 && s->cRight == 0)
            {
                Faculty *temp = NULL;
                if (lrpos == 'L')
                {
                    temp = s->left;
                    s->right->cLeft = 0;
                }
                else if (lrpos == 'R')
                {
                    temp = s->right;
                    s->left->cRight = 0;
                }
                delete (s);
                return temp;
            }
            else if (s->cLeft == 0)
            {
                Faculty *temp = s->right;
                Faculty *tempnode = temp;
                while (tempnode->cLeft == 1)
                    tempnode = tempnode->left;
                tempnode->left = s->left;
                delete (s);
                return temp;
            }
            else if (s->cRight == 0)
            {
                Faculty *temp = s->left;
                Faculty *tempnode = temp;
                while (tempnode->cRight == 1)
                    tempnode = tempnode->right;
                tempnode->right = s->right;
                delete (s);
                return temp;
            }
            else
            {
                // Copies Left most child of right child of the Node, then deletes that node in the tree.
                Faculty *successor = getSuccessor(s);
                s->Name = successor->Name;
                s->Age = successor->Age;
                s->Department = successor->Department;
                s->Gender = successor->Gender;
                s->right = remove(s->right, successor->Name, 'R');
            }
        }
        return s;
    }

    // Inorder Traversal
    void traverse()
    {
        Faculty *curr = head;
        if (curr == NULL)
            cout << "Empty\n";
        else
        {
            while (curr != NULL)
            {
                if (curr->cLeft == 0)
                {
                    cout << curr->Name << "\n";
                    while (curr->right != NULL && curr->cRight == 0)
                    {
                        curr = curr->right;
                        cout << curr->Name << "\n";
                    }
                    curr = curr->right;
                }
                else
                    curr = curr->left;
            }
        }
    }
};

// Interactive Program to ease debugging all operations.
int main()
{
    BST *Fac = new BST();
    int x = 0;
    // Loop for the menu
    do
    {
        cout << "\nMenu:\n";
        cout << "Enter 1 to insert\nEnter 2 to search\nEnter 3 to delete\nEnter 4 for in-order Traversal\nEnter 0 to Quit\n";
        cin >> x;
        string Name, Department = "CSE";
        char Gender = 'M';
        int Age = 19, pos;
        switch (x)
        {
        case 0:
            // To quit program
            break;
        case 1:
            // Insertion of Faculty into the Data Structure
            cout << "Enter Name of Faculty:";
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
            cout << "Enter Department of Faculty:";
            cin >> Department;
            transform(Department.begin(), Department.end(), Department.begin(), ::toupper);
            cout << "Enter Age of Faculty:";
            cin >> Age;
            cout << "Enter Gender of Faculty(M for male, F for Female):";
            cin >> Gender;
            Gender = (Gender == 'M' || Gender == 'm') ? 'M' : 'F';
            Fac->insert(Age, Name, Department, Gender);
            break;
        case 2:
            // Searching Faculty in Data Structure
            cout << "Enter Name of Faculty:";
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
            pos = Fac->search(Name);
            break;
        case 3:
            // Searching Faculty in Data Structure, then deleting it.
            cout << "Enter Name of Faculty:";
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
            Fac->head = Fac->remove(Fac->head, Name, 'H');
            break;
        case 4:
            Fac->traverse();
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
            break;
        }
    } while (x != 0);
    delete (Fac);
}