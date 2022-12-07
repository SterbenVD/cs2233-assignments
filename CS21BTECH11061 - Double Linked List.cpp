#include <iostream>
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
    Faculty *next, *prev;
    // Constructor for the Node
    Faculty(int pAge, string pName, string pDepartment, char pGender)
    {
        Age = pAge;
        Gender = pGender;
        Name = pName;
        Department = pDepartment;
        next = NULL;
        prev = NULL;
    }
};

// Class for the Data Structure
class linked_List
{
public:
    Faculty *head;

    // Constructor for the Data Structure
    linked_List()
    {
        head = NULL;
    }

    // Prints Entire Linked List. Not Used in program through. Just for debugging purposes.
    void printList()
    {
        Faculty *curr = head;
        if (curr == NULL)
            cout << "Empty\n";
        else
        {
            do
            {
                cout << curr->Name << "\n";
                curr = curr->next;
            } while (curr != NULL);
        }
    }

    // Searches for the Faculty in the Data Structure by Name
    int search(string Name)
    {
        int pos = 1;
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
                return pos;
            }
            else
            {
                pos++;
                curr = curr->next;
            }
        }
        cout << "Not Present\n";
        return -1;
    }

    // Checks if Faculty if present or not. If not present, inserts the Node into the Data Structure
    void insert(int Age, string Name, string Department, char Gender)
    {
        Faculty *temp = new Faculty(Age, Name, Department, Gender);
        int pres = this->search(Name);
        if (pres == -1)
        {
            if (head == NULL)
                head = temp;
            else
            {
                temp->next = head;
                head->prev = temp;
                head = temp;
            }
            cout << "Inserted Faculty into Linked List\n";
        }
        else
            cout << "Cannot Insert Faculty\n";
    }

    // Removes the Node if present
    int remove(string Name)
    {
        int pos = 1;
        Faculty *curr = head;
        while (curr != NULL)
        {
            if (!curr->Name.compare(Name))
            {
                if (curr->prev == NULL)
                {
                    head = head->next;
                    head->prev = NULL;
                }
                else
                    curr->prev->next = curr->next;
                delete (curr);
                cout << "Removed\n";
                return pos;
            }
            else
            {
                pos++;
                curr = curr->next;
            }
        }
        cout << "Not Present\n";
        return -1;
    }
};

// Interactive Program to ease debugging all operations.
int main()
{
    linked_List *Fac = new linked_List();
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
            pos = Fac->search(Name);
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