#include <iostream>
using namespace std;
// Class for Faculty Faculty
class Faculty
{
public:
    int Age;
    bool red;
    Faculty *left, *right, *parent;
    // Constructor for the Faculty
    Faculty(int pAge)
    {
        Age = pAge;
        left = NULL;
        right = NULL;
        parent = NULL;
        red = 1;
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

    // Searches for the Faculty in the Data Structure by Age
    int search(int Age)
    {
        Faculty *curr = head;
        while (curr != NULL)
        {
            if (curr->Age == Age)
            {
                cout << "Present\n";
                cout << "Age: " << curr->Age << "\n";
                string s = (curr->red) ? "Red" : "Black";
                cout << "Color of Node: " << s << "\n";
                return 1;
            }
            else
            {
                if (curr->Age > Age)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
        }
        cout << "Not Present\n";
        return -1;
    }

    // Prints the tree in 2D with lines separating
    void print2D(Faculty *Node, int horlevel)
    {
        int space = 8;
        if (Node == NULL)
            return;
        horlevel += space;
        print2D(Node->right, horlevel);
        cout << "\n";
        for (int i = space; i < horlevel; i++)
            cout << " ";
        char s = (Node->red) ? 'R' : 'B';
        cout << Node->Age << s << "\n";
        print2D(Node->left, horlevel);
    }

    // Calls print2D()
    void treeview()
    {
        print2D(head, 0);
    }

    // Rotates the subtree in anti-clockwise orientation
    void leftRotate(Faculty *Node)
    {
        Faculty *temp = Node->right;
        Node->right = Node->right->left;
        if (Node->right != NULL)
            Node->right->parent = Node;
        temp->left = Node;
        temp->parent = Node->parent;
        Node->parent = temp;
        if (temp->parent != NULL)
        {
            bool Node_is_right_child = (temp->parent->right == Node);
            if (Node_is_right_child)
                temp->parent->right = temp;
            else
                temp->parent->left = temp;
        }
        if (Node == head)
            head = temp;
    }

    // Rotates the subtree in clockwise orientation
    void rightRotate(Faculty *Node)
    {
        Faculty *temp = Node->left;
        Node->left = Node->left->right;
        if (Node->left != NULL)
            Node->left->parent = Node;
        temp->right = Node;
        temp->parent = Node->parent;
        Node->parent = temp;
        if (temp->parent != NULL)
        {
            bool Node_is_right_child = (temp->parent->right == Node);
            if (Node_is_right_child)
                temp->parent->right = temp;
            else
                temp->parent->left = temp;
        }
        if (Node == head)
            head = temp;
    }

    // Fixes the red node's parent should be black node property
    void insertFix(Faculty *Node)
    {
        Faculty *par = Node->parent;
        Faculty *gpar = par->parent;
        bool gpar_right_is_par = (gpar->right == par);
        Faculty *un = (gpar_right_is_par) ? gpar->left : gpar->right;
        if (par->red == 1 && (un != NULL && un->red == 1))
        {
            par->red = 0;
            un->red = 0;
            gpar->red = 1;
            if (gpar->parent != NULL && gpar->parent->red == 1)
                insertFix(gpar);
        }
        else
        {
            if (gpar_right_is_par && par->left == Node)
            {

                rightRotate(par);
                leftRotate(gpar);
                Node->red = 0;
            }
            else if (!gpar_right_is_par && par->right == Node)
            {
                leftRotate(par);
                rightRotate(gpar);
                Node->red = 0;
            }
            else if (gpar_right_is_par && par->right == Node)
            {
                leftRotate(gpar);
                par->red = 0;
            }
            else if (!gpar_right_is_par && par->left == Node)
            {
                rightRotate(gpar);
                par->red = 0;
            }
            gpar->red = 1;
        }
    }

    // Inserts the Node into the Data Structure
    void insert(int Age)
    {
        int pres = this->search(Age);
        if (pres == -1)
        {
            Faculty *temp = new Faculty(Age);
            Faculty *curr = head;
            if (curr == NULL)
                head = temp;
            else
            {
                while (curr != NULL)
                {
                    if (curr->Age > Age)
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
                temp->parent = curr;
                if (curr->red == 1)
                    insertFix(temp);
            }
            head->red = 0;
            cout << "Inserted Faculty into Red-Black Tree\n";
        }
        else
            cout << "Cannot Insert Faculty\n";
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
        // cout << "Tree:\n";
        // Fac->treeview();
        cout << "\nMenu:\n";
        cout << "Enter 1 to insert\nEnter 2 to search\nEnter 0 to Quit\n";
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
        default:
            // If input is some random integer
            cout << "Wrong Choice\n";
            break;
        }
    } while (x != 0);
    delete (Fac);
}