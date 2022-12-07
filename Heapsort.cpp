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

    int findMin()
    {
        if (Age_arr[0] == 0)
        {
            cout << "Empty\n";
            return -1;
        }
        cout << Age_arr[1];
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

    void Heapify()
    {
        
    }
};

int main()
{
    Min_Heap *Fac = new Min_Heap();
    cout << "Input number of elements: ";
    int n;
    cin >> n;
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        Fac->Age_arr.push_back(x);
    }
    Fac->Age_arr[0] = Fac->Age_arr.size() - 1;
    Fac->Heapify();
    cout << "\nSorted Array: ";
    for (int i = 1; i <= n; i++)
    {
        Fac->deleteMin();
        if (i != n)
            cout << " , ";
    }
    cout << "\n";
}