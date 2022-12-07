#include <iostream>
#include <algorithm>
using namespace std;

class Queue
{
public:
    int size, start, end;
    int *Age_arr;
    // Constructor for the Queue
    Queue()
    {
        size = 4;
        start = 0;
        end = 0;
        Age_arr = new int[4];
    }

    // For debugging
    void printList()
    {
        if (end >= start)
        {
            for (int i = start; i < end; i++)
                cout << Age_arr[i] << " ";
        }
        else
        {
            for (int i = start; i < size; i++)
                cout << Age_arr[i] << " ";

            for (int i = 0; i < end; i++)
                cout << Age_arr[i] << " ";
        }
        cout << "\n";
    }

    // Inserts the "Node" in the array :). If filled, shifts the array into another array then inserts the element.
    void insert(int pAge)
    {
        if (end == start - 1)
        {
            int *new_arr = new int[size + 4];
            int counter = 0;
            for (int i = start; i < size; i++)
                new_arr[counter++] = Age_arr[i];
            for (int i = 0; i < end; i++)
                new_arr[counter++] = Age_arr[i];
            int *temp = Age_arr;
            Age_arr = new_arr;
            delete (temp);
            start = 0;
            end = size - 1;
            size += 4;
        }
        else if (end == size - 1 && start == 0)
        {
            int *new_arr = new int[size + 4];
            for (int i = 0; i < size - 1; i++)
                new_arr[i] = Age_arr[i];
            int *temp = Age_arr;
            Age_arr = new_arr;
            delete (temp);
            start = 0;
            end = size - 1;
            size += 4;
        }
        Age_arr[end] = pAge;
        end++;
        if (end == size)
            end = 0;
    }

    // Removes the element that came in the DS first
    int remove()
    {
        if (end == start)
        {
            cout << "Empty Queue\n";
            return -1;
        }
        else
        {
            cout << Age_arr[start] << " is removed from the queue\n";
            start++;
            if (start >= size)
                start = 0;
            return 1;
        }
    }
};

int main()
{
    Queue *Fac = new Queue();
    int x = 0;
    // Loop for the menu
    do
    {
        cout << "\nMenu:\n";
        //Fac->printList();
        cout << "Enter 1 to insert\nEnter 2 to delete\nEnter 0 to Quit\n";
        cin >> x;
        int Age;
        switch (x)
        {
        case 0:
            // To quit program
            break;
        case 1:
            // Insertion of Node into the Data Structure
            cout << "Enter Age of Faculty:";
            cin >> Age;
            Fac->insert(Age);
            break;
        case 2:
            Fac->remove();
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
        }
    } while (x != 0);
    delete (Fac);
}