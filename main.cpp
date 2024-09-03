//Restaurant Management System 
//Ayush Srivastava
//21HCH10093
//Indian Institute of Technology

#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string foodname;
    int quantity;
    float price;
    int data;
    Node* prev;
    Node* next;
};

Node* headc = nullptr;
Node* newnode;
Node* tailc = nullptr;
Node* heada = nullptr;
Node* taila = nullptr;
Node* head_s = nullptr;

void adminmenu()
{
    cout << "\n\t\t\t\t\t\t\t1. View total sales\n";
    cout << "\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout << "\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout << "\t\t\t\t\t\t\t4. Display order menu\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\t   Enter Your Choice --->";
}

void customermenu()
{
    cout << "\n\t\t\t\t\t\t\t1. Place your order\n";
    cout << "\t\t\t\t\t\t\t2. View your ordered items\n";
    cout << "\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t\t\t\t\t4. Display final bill\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\t   Enter Your Choice --->";
}

Node* createadmin(Node* head, int data, string foodname, float price)
{
    newnode = new Node;

    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    newnode->foodname = foodname;
    newnode->next = nullptr;
    newnode->prev = nullptr;

    Node* temp = head;

    if (temp == nullptr)
        heada = taila = newnode;
    else
    {
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

Node* createcustomer(Node* head, int data, int quantity)
{
    newnode = new Node;

    Node* temp1 = heada;
    int flag = 0;
    while (temp1 != nullptr)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newnode->data = data;
        newnode->price = quantity * (temp1->price);
        newnode->quantity = quantity;
        newnode->foodname = temp1->foodname;
        newnode->next = nullptr;
        newnode->prev = nullptr;

        Node* temp = head;

        if (temp == nullptr)
            headc = tailc = newnode;
        else
        {
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
    return headc;
}

void displayList(Node* head)
{
    Node* temp1 = head;
    if (temp1 == nullptr)
    {
        cout << "\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }
    else
    {
        cout << "\n";
        while (temp1 != nullptr)
        {
            if (temp1->quantity == 0)
                cout << "\t\t\t\t\t\t\t" << temp1->data << "\t" << temp1->foodname << "\t" << temp1->price << endl;
            else
            {
                cout << "\t\t\t\t\t\t\t" << temp1->data << "\t" << temp1->foodname << "\t" << temp1->quantity << "\t" << temp1->price << endl;
            }

            temp1 = temp1->next;
        }
        cout << endl;
    }
}

Node* totalsales(int data, int quantity)
{
    newnode = new Node;
    int flag = 0;

    Node* temp1 = heada;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity * (temp1->price);
    newnode->quantity = quantity;
    newnode->foodname = temp1->foodname;
    newnode->next = nullptr;
    newnode->prev = nullptr;

    Node* temp = head_s;

    if (temp == nullptr)
        head_s = newnode;
    else
    {
        while (temp->next != nullptr)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    Node* temp = headc;
    while (temp != nullptr)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

Node* deleteNode(int data, Node* head, Node* tail)
{
    if (head == nullptr)
    {
        cout << "\n\t\t\t\t\t\t\tList is empty\n";
    }
    else
    {
        Node* temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != nullptr)
                head->prev = nullptr;
            delete temp;
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            delete temp;
        }
    }
    return head;
}

int deleteadmin()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node* temp = heada;
    while (temp != nullptr)
    {
        if (temp->data == num)
        {
            heada = deleteNode(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

int deletecustomer()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node* temp = headc;
    while (temp != nullptr)
    {
        if (temp->data == num)
        {
            headc = deleteNode(num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    Node* temp = headc;
    float total_price = 0;
    while (temp != nullptr)
    {
        total_price += temp->price;
        temp = temp->next;
    }

    cout << "\t\t\t\t\t\t\tTotal price: " << total_price << endl;
}

Node* deleteList(Node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
            delete temp->prev;
        }
        delete temp;
        head = nullptr;
    }

    return head;
}

void admin()
{
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    ADMIN SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    int opt, num, flag = 0;
    string name;
    float price;
    Node* temp;
    while (true)
    {
        adminmenu();
        cin >> opt;

        if (opt == 5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:
                cout << "\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
                cin >> num;
                temp = heada;
                flag = 0;
                while (temp != nullptr)
                {
                    if (temp->data == num)
                    {
                        cout << "\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                cout << "\t\t\t\t\t\t\tEnter food item name: ";
                cin >> name;
                cout << "\t\t\t\t\t\t\tEnter price: ";
                cin >> price;
                heada = createadmin(heada, num, name, price);
                cout << "\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
                break;
            case 3:
                if (deleteadmin())
                {
                    cout << "\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                    displayList(heada);
                }
                else
                    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";

                break;
            case 4:
                cout << "\n\t\t\t\t\t\t\t   ### Order menu ###\n";
                displayList(heada);
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch;
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while (true)
    {
        customermenu();

        int opt;
        cin >> opt;

        if (opt == 5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                cout << "\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                int n;
                cin >> n;
                cout << "\t\t\t\t\t\tEnter quantity: ";
                int quantity;
                cin >> quantity;
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                cout << "\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
                displayList(headc);
                break;
            case 3:
                if (deletecustomer())
                {
                    cout << "\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                    displayList(headc);
                }
                else
                    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
                break;
            case 4:
                calculatetotsales();
                cout << "\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
                displaybill();
                headc = deleteList(headc);
                cout << "\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                cin.ignore();
                cin.get(ch);
                flag = 1;
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
        if (flag == 1)
            break;
    }
}

void mainmenu()
{
    cout << "\n                                 **************************************************************************\n";
    cout << "                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout << "                                 **************************************************************************\n\n\n";
    cout << "\t\t\t\t\t\t\t1. ADMIN SECTION--> \n";
    cout << "\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n";
    cout << "\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}

int main()
{
    heada = createadmin(heada, 1, "Hot and Sour Soup", 100);
    heada = createadmin(heada, 2, "Manchow Soup", 200);
    heada = createadmin(heada, 3, "Manchurian Noodles", 150);
    heada = createadmin(heada, 4, "Fried Rice", 180);
    heada = createadmin(heada, 5, "Hakka Noodles", 80);

    while (true)
    {
        mainmenu();
        int choice;
        cin >> choice;

        if (choice == 3)
        {
            cout << "\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}
