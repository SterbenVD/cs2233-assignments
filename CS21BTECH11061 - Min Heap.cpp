#include <iostream>
#include <vector>
using namespace std;

class Min_Heap
{
public:
    vector<int> Age_arr;
    Min_Heap()
    {
        Age_arr.push_back(0);
    }

    void swap(int pos)
    {
        Age_arr[pos] += Age_arr[pos / 2];
        Age_arr[pos / 2] = Age_arr[pos] - Age_arr[pos / 2];
        Age_arr[pos] -= Age_arr[pos / 2];
    }
    // For debugging
    void printList()
    {
        for (int i = 1; i <= Age_arr[0]; i++)
            cout << Age_arr[i] << " ";
        cout << "\n";
    }

    void insert(int Age)
    {
        Age_arr[0]++;
        int pos = Age_arr[0];
        Age_arr.push_back(Age);
        while (pos != 1)
        {
            if (Age_arr[pos] < Age_arr[pos / 2])
            {
                swap(pos);
                pos /= 2;
            }
            else
                break;
        }
    }
    int findMin()
    {
        if (Age_arr[0] == 0)
        {
            cout << "Empty\n";
            return -1;
        }
        cout << Age_arr[1] << "\n";
        return Age_arr[1];
    }
    void deleteMin()
    {
        if (findMin() != -1)
        {
            Age_arr[1] = Age_arr[Age_arr[0]];
            Age_arr.pop_back();
            int pos = 2;
            while (pos <= Age_arr[0])
            {
                if (pos != Age_arr[0])
                    pos = (Age_arr[pos] < Age_arr[pos + 1]) ? pos : pos + 1;
                if (Age_arr[pos / 2] < Age_arr[pos])
                    break;
                else
                {
                    swap(pos);
                    pos *= 2;
                }
            }
            Age_arr[0]--;
        }
    }
};

int main()
{
    Min_Heap *Fac = new Min_Heap();
    int x = 0;
    // Loop for the menu
    do
    {
        cout << "\nMenu:\n";
        // Fac->printList();
        cout << "Enter 1 to insert\nEnter 2 to find Min Element\nEnter 3 to delete Min element\nEnter 0 to Quit\n";
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
            cout << "Minimum Element: ";
            Fac->findMin();
            break;
        case 3:
            cout << "Element Deleted: ";
            Fac->deleteMin();
            break;
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
        }
    } while (x != 0);
    delete (Fac);
}