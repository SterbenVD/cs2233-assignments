#include <iostream>
// Algorithm is used for some string functions
#include <algorithm>
using namespace std;

// Class for Faculty Faculty
class Faculty
{
public:
    string Name, Department;
    char Gender;
    int Age;
    Faculty *left, *right;
    // Constructor for the Faculty
    Faculty(int pAge, string pName, string pDepartment, char pGender)
    {
        Age = pAge;
        Gender = pGender;
        Name = pName;
        Department = pDepartment;
        left = NULL;
        right = NULL;
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
                if (curr->Name.compare(Name) > 0)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
        }
        cout << "Not Present\n";
        return -1;
    }

    // Inserts the Node into the Data Structure
    void insert(int Age, string Name, string Department, char Gender)
    {
        int pres = this->search(Name);
        if (pres == -1)
        {
            Faculty *temp = new Faculty(Age, Name, Department, Gender);
            if (head == NULL)
                head = temp;
            else
            {
                Faculty *curr = head;
                while (curr != NULL)
                {
                    if (curr->Name.compare(Name) > 0)
                    {
                        if (curr->left == NULL)
                        {
                            curr->left = temp;
                            break;
                        }
                        else
                            curr = curr->left;
                    }
                    else
                    {
                        if (curr->right == NULL)
                        {
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
        s = s->right;
        while ((s != NULL) && (s->left != NULL))
            s = s->left;
        return s;
    }

    // Remove the required node if it exists
    Faculty *remove(Faculty *s, string pName)
    {
        if (s == NULL)
        {
            cout << "Not Present\n";
        }
        else if (s->Name > pName)
            s->left = remove(s->left, pName);
        else if (s->Name < pName)
            s->right = remove(s->right, pName);
        else
        {
            if (s->left == NULL)
            {
                Faculty *temp = s->right;
                delete (s);
                return temp;
            }
            else if (s->right == NULL)
            {
                Faculty *temp = s->left;
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
                s->right = remove(s->right, successor->Name);
            }
        }
        return s;
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
        cout << "Enter 1 to insert\nEnter 2 to search\nEnter 3 to delete\nEnter 0 to Quit\n";
        cin >> x;
        string Name, Department;
        char Gender;
        int Age, pos;
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
            Fac->remove(Fac->head, Name);
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
            break;
        }
    } while (x != 0);
    delete (Fac);
}