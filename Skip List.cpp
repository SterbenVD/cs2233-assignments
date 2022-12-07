#include <iostream>
#include <cstdlib>
// Algorithm is used for some string functions
#include <algorithm>
using namespace std;

// Class for Faculty Node
class Faculty
{
public:
    string Name, Department;
    char Gender;
    int Age;
    Faculty *prev, *next, *par, *child;
    bool finite;
    // Constructor for the Node
    Faculty(int pAge, string pName, string pDepartment, char pGender)
    {
        Age = pAge;
        Gender = pGender;
        Name = pName;
        Department = pDepartment;
        next = NULL;
        prev = NULL;
        par = NULL;
        child = NULL;
        finite = 1;
    }
    Faculty()
    {
        finite = 0;
        next = NULL;
        prev = NULL;
        par = NULL;
        child = NULL;
    }
};

// Class for the Data Structure
class skip_list
{
public:
    int max_level;
    Faculty *tl;

    // Constructor for the Data Structure
    skip_list()
    {
        max_level = 1;
        tl = new Faculty();
        Faculty *tr = new Faculty();
        tl->next = tr;
    }

    // Prints Entire Skip List. Not Used in program through. Just for debugging purposes.
    void printList()
    {
        Faculty *curr = tl->child;
        while (curr != NULL)
        {
            Faculty *temp = curr;
            while (temp != NULL)
            {
                if (temp->Name == "")
                {
                    if (temp->next != NULL)
                        cout << "INF";
                    else
                        cout << ", INF";
                }
                else
                    cout << ", " << temp->Name;
                temp = temp->next;
            }
            cout << "\n";
            curr = curr->child;
        }
    }

    // Searches for the Faculty in the Data Structure by Name
    void search(string Name)
    {
        Faculty *curr = tl;
        while (curr->next != NULL)
        {
            int temp = curr->next->Name.compare(Name);
            if (!temp)
            {
                cout << "Present\n";
                cout << "Name: " << curr->next->Name << "\n";
                cout << "Department: " << curr->next->Department << "\n";
                cout << "Age: " << curr->next->Age << "\n";
                cout << "Gender: " << curr->next->Gender << "\n";
                return;
            }
            else
            {

                if (curr->next->finite == 0 || temp > 0)
                {
                    if (curr->child == NULL)
                        break;
                    else
                        curr = curr->child;
                }
                else if (curr->next->next != NULL)
                    curr = curr->next;
                else
                    break;
            }
        }
        cout << "Not Present\n";
    }

    // Checks if Faculty if present or not. If not present, inserts the Node into the Data Structure
    void insert(int Age, string Name, string Department, char Gender)
    {
        Faculty *curr = tl;
        while (curr->next != NULL)
        {
            int temp = curr->next->Name.compare(Name);
            if (!temp)
            {
                cout << "Present\n";
                cout << "Name: " << curr->Name << "\n";
                cout << "Department: " << curr->Department << "\n";
                cout << "Age: " << curr->Age << "\n";
                cout << "Gender: " << curr->Gender << "\n";
                return;
            }
            else
            {
                if (curr->next->finite == 0 || temp > 0)
                {
                    if (curr->child == NULL)
                        break;
                    else
                        curr = curr->child;
                }
                else if (curr->next->next != NULL)
                    curr = curr->next;
                else
                    break;
            }
        }
        Faculty *child = NULL;
        double random;
        int t = max_level;
        do
        {
            t--;
            random = (((double)rand()) / RAND_MAX);
            Faculty *temp = new Faculty(Age, Name, Department, Gender);
            temp->next = curr->next;
            temp->prev = curr;
            temp->child = child;
            if (child != NULL)
                child->par = temp;
            curr->next = temp;
            temp->next->prev = temp;
            while (curr->par == NULL && curr->prev != NULL)
                curr = curr->prev;
            if (curr->par == NULL)
            {
                max_level++;
                Faculty *newtl = new Faculty();
                Faculty *newtr = new Faculty();
                newtl->child = curr;
                newtl->next = newtr;
                newtr->prev = newtl;
                curr->par = newtl;
                Faculty *it = curr;
                while (it->next != NULL)
                    it = it->next;
                it->par = newtr;
                tl = newtl;
            }
            else
                curr = curr->par;
            child = temp;
        } while (random > 0.5 && t > 0);
    }

    // Removes extra layers if present
    void reorient()
    {
        while (tl->next->finite == 0)
        {
            if (tl->child != NULL && tl->child->next->finite == 0)
            {
                tl->child->par = NULL;
                tl->child->next->par = NULL;
                delete (tl->next);
                Faculty *del = tl;
                tl = tl->child;
                delete (del);
                max_level--;
            }
            else
                break;
        }
    }

    // Removes the Node if present
    void remove(string Name)
    {
        Faculty *curr = tl;
        while (curr->next != NULL)
        {
            int temp = curr->next->Name.compare(Name);
            if (!temp)
            {
                cout << "Present\n";
                cout << "Name: " << curr->next->Name << "\n";
                cout << "Department: " << curr->next->Department << "\n";
                cout << "Age: " << curr->next->Age << "\n";
                cout << "Gender: " << curr->next->Gender << "\n";
                curr = curr->next;
                while (curr != NULL)
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    Faculty *del = curr;
                    curr = curr->child;
                    delete (del);
                }
                reorient();
                return;
            }
            else
            {

                if (curr->next->finite == 0 || temp > 0)
                {
                    if (curr->child == NULL)
                        break;
                    else
                        curr = curr->child;
                }
                else if (curr->next->next != NULL)
                    curr = curr->next;
                else
                    break;
            }
        }
        cout << "Not Present\n";
    }
};

// Interactive Program to ease debugging all operations.
int main()
{
    skip_list *Fac = new skip_list();
    int x = 0;
    // Loop for the menu
    do
    {
        // Prints structure for debugging
        // Fac->printList();
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
            // Insertion of Node into the Data Structure
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
            // Searching Node in Data Structure
            cout << "Enter Name of Faculty:";
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
            Fac->search(Name);
            break;
        case 3:
            // Searching Node in Data Structure, then deleting it.
            cout << "Enter Name of Faculty:";
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
            Fac->remove(Name);
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
        }
    } while (x != 0);
    delete (Fac);
}