/*
Program name: InventoryStack.cpp
Programmer: Tyler Davies
Date: 11-7-21
Version: 1.0
Description: This program contains two classes: an Inventory class, and an InventoryStack class.
             The Inventory class is used to create an object which stores the serial number,
             manufactured date, and lot number of a part. The InventoryStack class holds objects of
             the Inventory class. The main function creates and tests an InventoryStack class object.
*/

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

//Inventory class has three private members: serialNumber, manufactDate, and LotNum. Its member
//functions store and retrieve these data members.
class Inventory
{
private:
    int serialNumber;       //Part's serial number
    string manufactDate;    //Date the part was manufactured (string allows for any date format)
    int LotNum;             //Part’s lot number
public:
    Inventory(int, string, int);
    void setSerialNumber(int num)
        { serialNumber = num; }
    void setManufactDate(string date)
        { manufactDate = date; }
    void setLotNum(int num)
        { LotNum = num; }
    int getSerialNumber()
        { return serialNumber; }
    string getManufactDate()
        { return manufactDate; }
    int getLotNum()
        { return LotNum; }
};

//Inventory constructor with default arguments.
Inventory::Inventory(int num1 = 0, string date = "##-##-##", int num2 = 0)
{
    serialNumber = num1;
    manufactDate = date;
    LotNum = num2;
}

//InventoryStack class sets-up a dynamic stack using the structure StackNode; each node holds an
//Inventory object, and a pointer to the next node. The class also has a pointer to the top node.
class InventoryStack
{
private:
    struct StackNode
    {
        Inventory part;
        StackNode *next;
    };
    StackNode *top;
public:
    InventoryStack()
        { top = NULL; }
    void push(Inventory);
    void pop(Inventory &);
    bool isEmpty() const;
    void print() const;
    ~InventoryStack();
};

/*
The push function adds a part to the InventoryStack. It prompts the user for the part's serial
number, date of manufacture, and lot number; then it stores the data in an Inventory object.
Thereafter, the object is stored into a newNode and pushed onto the stack.
*/
void InventoryStack::push(Inventory obj)
{
    int serial, lot;
    string date;
    StackNode *newNode;
    newNode = new StackNode;

    cout << "\nEnter the part's serial number: ";
    cin >> serial;
    newNode->part.setSerialNumber(serial);

    cin.ignore(10, '\n');    //Cleans buffer in prep for the getline function
    cout << "Enter the part's date of manufacture: ";
    getline(cin, date);
    newNode->part.setManufactDate(date);

    cout << "Enter the part's lot number: ";
    cin >> lot;
    newNode->part.setLotNum(lot);

    if (isEmpty())
    {
        top = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}

//The pop function pops the top part off of the InventoryStack, and displays its Inventory object's
//member data. If it is empty, a message will display for the user.
void InventoryStack::pop(Inventory& obj)
{
    StackNode *temp;
    if (isEmpty())
        cout << "Inventory is empty.\n";
    else
    {
        obj = top->part;
        temp = top->next;
        delete top;
        top = temp;
        cout << left << setw(21) << "\nSerial Number: " << obj.getSerialNumber() << endl;
        cout << setw(20) << "Manufactured Date: " << obj.getManufactDate() << endl;
        cout << setw(20) << "Lot Number: " << obj.getLotNum() << endl;
    }
}

//The isEmpty function checks if there is a top node. If there is, the stack is not empty.
bool InventoryStack::isEmpty() const
{
    if (!top)
        return true;
    else
        return false;
}

//The print function traverses the InventoryStack, printing all of the parts stored on the stack;
//starting with the last part entered.
void InventoryStack::print() const
{
    int partCount = 1;
    StackNode *nodePtr;
    nodePtr = top;
    while (nodePtr != NULL)
    {
        cout << left << "\nPart " << partCount << endl;
        cout << setw(20) << "Serial Number: " << nodePtr->part.getSerialNumber() << endl;
        cout << setw(20) << "Manufactured Date: " << nodePtr->part.getManufactDate() << endl;
        cout << setw(20) << "Lot Number: " << nodePtr->part.getLotNum() << endl;
        nodePtr = nodePtr->next;
        partCount += 1;
    }
    cout << endl;
}

//The ~InventoryStack destructor traverses the stacked linked list, deleting each node.
InventoryStack::~InventoryStack()
{
    StackNode *nodePtr, *next;
    nodePtr = top;
    while (nodePtr != NULL)
    {
        next = nodePtr->next;
        delete nodePtr;
        nodePtr = next;
    }
}

/*
The main function acts as a driver program for the InventoryStack class. It initializes an
InventoryStack object and displays a menu which asks the user if they want to add a part to
inventory, take a part from inventory, or exit the program. The loop will repeat until the user is
finished/chooses to exit the program. Before the program ends, it will automatically print a list
of all the parts left in the inventory.
*/
int main()
{
    InventoryStack inventory;
    Inventory part;
    int choice;

    cout << "Please enter your choice using 1, 2, or 3\n\n";
    cout << "1) add a part to inventory \n2) take a part from inventory \n3) exit program\n\n";
    cin >> choice;

    if (!cin)
    {
        cout << "\nError: choice entered not valid.\nProgram will now terminate.\n";
        exit(0);
    }

    while (choice != 3)
    {
        if (choice == 1)
            inventory.push(part);
        else if (choice == 2)
            inventory.pop(part);
        else
        {
            cout << "\nError: choice entered not valid.\nProgram will now terminate.\n";
            exit(0);
        }

        cout << "\nPlease enter another choice using 1, 2, or 3\n\n";
        cout << "1) add a part to inventory \n2) take a part from inventory \n3) exit program\n\n";
        cin >> choice;
    }

    inventory.print();
    exit(0);
}