////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This program takes Multiple Barcodes(Items On Sale) from user input to calculate Total to pay, Change given
// and if more money is required. The program then creates a receipt that is printed if the user chooses to print
// the receipt. After the receipt choice the program asks the user if there is a next customer.
// Developer: 18016995
// Date of creation: 14/11/2019
// Date of last modification: 15/12/2019
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**********************************************************************************************************************
// Declaration of the predefined libraries for the various streams that will be used.
// iostream is for the cout and cin functions.
// iomanip is for the manipulation of the data the user enters and predefined data (iostream objects).
// fstream is for the file manipulation to create the receipt for the user.
//**********************************************************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>

//**********************************************************************************************************************
// Declaration that the iostream objects (Cout and Cin) can be used with name collisions.
//**********************************************************************************************************************

using namespace std;

//**********************************************************************************************************************
// Defining the input and output modes for creating files and reading from the file and printing to the screen.
// ofstream allows the user to put data into an external file.
// ifstream allows the user to retrieve the data from an external file.
//**********************************************************************************************************************

ofstream outfile;
ifstream infile;

//**********************************************************************************************************************
// Declaration of all the variables in the program so that they can be used globally within the program.
//**********************************************************************************************************************

// Variables that declare the array size which remain constant integer values.
const int Size = 10; // FIXED to 10 items in the array
const int InputSize = 20; // Allows for 20 user inputs

int Point = 0; // Variable that defines the place in the arrays for the item the user entered.
float TotalBill = 0; //Stores the total amount the user has paid.
float total = 0; // Variable that stores the total amount of money.
int Count = 0; // Variable so the FOR loops can run
string NewName; // Variable that stores the name of the new item entered.
char Checker = 'F'; // Variable that is set to 'A' when the correct username and password is entered so that the discounted prices can be used.
string Username = ""; // Variable that stores the User input for the username.
string password = ""; // Variable that stores the User Input for the password.

//**********************************************************************************************************************
// Declaring all the arrays that will be for holding the information about the stores products (Barcode, Price, Name)
// Also the data from the user input including arrays for matching Barcodes, Names and Price.
// The Employee function uses the New item arrays to add items.
// The discount customer login function uses the adjusted price array.
// The Login Systems use the arrays below.
//**********************************************************************************************************************

float ItemPrice[Size] = { 10.50,5.50,8.00,12.10,6.75,5.20,2.00,4.45,20.50,10.00 };
string ItemName[Size] = { "Milk","Bread","Chocolate","Towel","Toothpaste","Soap","Pen","Biscuits","Lamp","Battery" };
string ItemBarcode[Size] = { "0120001","0120002","0120003","0120004","0120005","0120006","0120007","0120008","0120009","0120010" };
float ItemPriceArray[InputSize] = { 0.00 };
string ItemBoughtArray[InputSize] = { "" };
string ItemNameBought[InputSize] = { "" };
float NewItemPrice[InputSize] = { 0.00 };
string NewItemBarcode[InputSize] = { "" };
string NewItemName[InputSize] = { "" };
float DiscountedPrice[Size] = { 4.99 , 2.50 , 3.00 , 5.00 , 5.40 , 4.20 , 0.50 , 2.00 , 9.50 , 7.50 };
string EmployeeUserNames[5] = { "Employee1","Employee2","Employee3","Employee4","Employee5" }; // Set of employee usernames as examples for easy testing
string EmployeePassword[5] = { "Password1","Password2","Password3","Password4","Password5" }; // Passwords generated that match the usernames EXAMPLES Of Strong User Passwords "yBz4WCp","XbBDe7F","9XHsTsPp","Yr3ZnkJb","bu9hGs5G".

//**********************************************************************************************************************
// Function Prototypes of all the functions used in the System. They help the compiler
// recognise the different functions.
//**********************************************************************************************************************

void BarcodeInput();
void Total();
void Receipt();
void NextCustomer();
void EmployeeCustomer();
void Employee();
void CustomerLogin();
void CustomerDiscount();
void EmployeeLogin();


//**********************************************************************************************************************
// Function that displays Welcome Message and calls the Barcode Input function
//**********************************************************************************************************************

int main()
{
    EmployeeCustomer(); // This line of code calls the function that asks the user to enter the whether they are an Employee, Customer or if they are done using the program.
    return 0; // Success status when program ends
}

//**********************************************************************************************************************
// Function that reuires use input so that the program knows if the customer is a member or not
//**********************************************************************************************************************

void CustomerDiscount()
{
    string CLogin = ""; // Varirable that stores User Input to enter login system.
    cout << "Login Into Customer Account[Y/N]: "; //Displays Message of whther the customer would like to login
    cin >> CLogin; // User Input
    char Letter = 'T'; // Initialises WHILE Loop
    while (Letter != 'F')
    {
        if ((CLogin == "Y") || (CLogin == "y")) // IF the user inputs yes then the code below runs
        {
            Letter = 'F';
            Checker = 'A';
            Username = "";
            password = "";
            CustomerLogin(); // Calls Customer login function so the user can login into the members only priced store
        }
        else if ((CLogin == "N") || (CLogin == "n")) // Otherwise IF the user enters N then the code below begins
        {
            Letter = 'F'; // BREAKS the loop
            Checker = 'F';
            BarcodeInput(); // Calls the barcode function so the program can run normally.
        }
        else // ERROR Checks the input
        {
            cout << "[!]Please Press 'Y' For Yes Or 'N' For No: ";
            cin >> CLogin;
        }
    }
}

//**********************************************************************************************************************
// Function that computes the barcode input and error checking the input
//**********************************************************************************************************************

void BarcodeInput()
{
    //**********************************************************************************************************************
    // Variables that have been declared locally so that they can be used in the function.
    //**********************************************************************************************************************
    int i = 0; // Variable that is incremented so that item barcode the user entered which has matched is stored in the new array.
    char Letter = 'T'; // Condition for the WHILE loop.
    string ItemBought; // Variable that allows the user to input a Barcode that includes the 0 at the front.
    total = 0; // Reset the total to 0.
    TotalBill = 0; // Resets the stored total to 0

    // The code below  prints the WELCOME message.
    cout << "\n**********************************************************\n";
    cout << "*      WELCOME TO HERTS SUPERMARKET CHECKOUT SYSTEM      *\n";
    cout << "*    SCAN THE BARCODE OR MANUALLY TYPE THE BARCODE ID    *\n";
    cout << "**********************************************************\n";

    for (Count = 0; Count <= 19; Count++) // Resets the array to original values.
    {
        // The code below sets each arrays values back to the original values of 0 and empty strings ("").
        ItemPriceArray[Count] = 0.00;
        ItemBoughtArray[Count] = "";
        ItemNameBought[Count] = "";
    }

    do // DO-WHILE Loop initialisation
    {
        cout << "Barcode (Type 'F' to finish): "; // Prints out statement requiring user input.
        cin >> ItemBought; // Code that retrieves user input for the Barcode.
        i++; // Incremented every time a barcode is entered.

        for (Count = 0; Count <= 9; Count++) // FOR loop that goes through array and checks for match.
        {
            if (Checker == 'A')
            {
                if (ItemBarcode[Count] == ItemBought) // IF statement that checks if the Barcode matches.
                {
                    Point = Count; //  Sets the Point Variable to the place in the array that the barcode matches.
                    // The code below stores the Matched barcodes; Name, Barcode And Price.
                    ItemBoughtArray[i] = ItemBought;
                    ItemNameBought[i] = ItemName[Point];
                    ItemPriceArray[i] = DiscountedPrice[Point];
                    break; // after storing the item Name, Price and Barcode the BREAK exits the loop.
                }
            }
            else
            {
                if (ItemBarcode[Count] == ItemBought) // IF statement that checks if the Barcode matches.
                {
                    Point = Count; //  Sets the Point Variable to the place in the array that the barcode matches.
                    // The code below stores the Matched barcodes; Name, Barcode And Price.
                    ItemBoughtArray[i] = ItemBought;
                    ItemNameBought[i] = ItemName[Point];
                    ItemPriceArray[i] = ItemPrice[Point];
                    break; // after storing the item Name, Price and Barcode the BREAK exits the loop.
                }
                else if (NewItemBarcode[Count] == ItemBought) // IF statement that checks if the barcode matches the new items entered.
                {
                    Point = Count;
                    ItemBoughtArray[i] = ItemBought;
                    ItemNameBought[i] = NewItemName[Point];
                    ItemPriceArray[i] = NewItemPrice[Point];
                    break;
                }
            }
        }

        if ((ItemBought == "F") || (ItemBought == "f")) // Checks if the user enters F to call the function that computes the total price for the users items.
        {
            for (Count = 0; Count <= 19; Count++) // FOR Loop that goes through the newly created Price array from matched barcodes that adds the prices in the array.
            {
                total += ItemPriceArray[Count]; // Addition statement that calculates the total.
            }
            Total(); // Calls TOTAL Function.
            Letter = 'F'; // Breaks the While Loop.
        }

        else if ((ItemBought.length() != 7)) // First ERROR Check that makes sure the barcode is a suitable length.
        {
            cout << "[!]This Barcode Does Not Exist! Please Try Again\n"; // Error Message if the user enters a barcode less than or more than the suitable length.
        }

        else if ((ItemBarcode[Count] != ItemBought) && (NewItemBarcode[Count] != ItemBought)) // Second ERROR Check that checks if the barcode is valid.
        {
            cout << "[!]This Barcode Does Not Exist! Please Try Again\n"; // ERROR Message if the user enters an invalid barcode.
        }
    }     while (Letter != 'F'); // WHILE Loop condition.
}

//**********************************************************************************************************************
// Function that computes the total price for the items the user bought and error checking the input.
//**********************************************************************************************************************

void Total()
{
    //**********************************************************************************************************************
    // Variables that have been declared locally so that they can be used in the function.
    //**********************************************************************************************************************

    float Cash = 0.00; // Variable that the user inputs a value in to which can use decimal points. Also numbers represented up to 32 bits can be entered
    float CashRequired = 0; // Variable that stores the cash left to be paid. Stored as FLOAT variable as the Cash left could require decimal points and is single precision
    float Change = 0; // Variable that stores the change given when the total left is less than the cash entered. Stored as FLOAT variable so decimal points can be used. It is likely for the user to input a number larger than 32 bit representation.
    char Letter = 'T'; // WHILE Loop declaration

    TotalBill += total; // Stores the caculated total in a new variable that is not affected if the total is more than the users cash input which subtracts the total from the user input changing the value.
    cout << "\nAmount Total: $" << setprecision(2) << fixed << total << endl; // Codeblocks does not allow for the pound sign hence the dollar sign is used.
    cout << "Cash Required: $"; // Prints message for user to input the cash they can use to purchase the items.
    cin >> Cash; // Asks for FLOAT number input.

    do // DO WHILE LOOP to continue asking for user input if incorrect data is entered
    {
        if (cin.fail()) // Error Checks user input to make sure the user doesnt enter a value other than an float number
        {
            cin.clear(); // Repairs the instream Which allows for input
            cin.ignore(100, '\n'); // Clears the buffer
            cout << "[!]Incorrect Input: "; // Prints error message
            cin >> Cash; // Asks for another user input
        }
        else // IF the user input is correct
        {
            if (total < Cash) // IF the User input is greater than the total of the products bought.
            {
                Change = Cash - total; // Calculation of the change.
                cout << "Change Given: $" << setprecision(2) << fixed << Change << endl; // Displays change given to the customer.
                Letter = 'F'; // Breaks the Loop
                Receipt(); // Calls the RECEIPT function
            }
            else if (total > Cash) // ELSE IF the user input is less than the total of the products bought.
            {
                CashRequired = total - Cash; // Calculates the amount left to pay.
                total -= Cash; // changes the total to the original total to the total subtract the User input.
                cout << "[!]More Cash Needed: $" << setprecision(2) << fixed << CashRequired << endl;
                cout << "Cash Required: $";
                cin >> Cash;
            }
            else if (total == Cash) // ELSE IF the total is equal to the user input.
            {
                cout << "Change Given: $" << (total - Cash) << endl;
                Letter = 'F';
                Receipt();
            }
        }
    }     while (Letter != 'F');
}

//**********************************************************************************************************************
// Function that asks if there is a next customer and error checking the input
// If there is a next customer the program while restart otherwise it will print a Thank you message and end.
//**********************************************************************************************************************

void NextCustomer()
{
    string NxtCustomer; // Declaration of the VARIABLE that requires an input from the user whether or not there is a next customer
    char Letter = 'T'; // WHILE Loop condition reset.

    cout << "\nNext Customer[Y/N]: "; // Prints out message that prompts the user to input there decision of if there is a next customer or not.
    cin >> NxtCustomer; // Asks for user input

    while (Letter != 'F') // WHILE LOOP to continue asking for user input if incorrect data is entered
    {
        if ((NxtCustomer == "Y") || (NxtCustomer == "y")) // Decisional statement that executes the below code if Y or y is entered
        {
            Letter = 'F';
            CustomerDiscount(); // Calls customer discount function to restart the program as there is a next customer and ask whether or not the customer will login into the discount account.
        }
        else if ((NxtCustomer == "N") || (NxtCustomer == "n")) // Decisional Statement that executes the code below if the user enters N or n.
        {
            cout << "\nThank You For Shopping With Us\n"; // Prints thank you message.
            Letter = 'F'; // Breaks the WHILE LOOP
            Checker = 'F'; // Sets the Checker variable to 'F' so that the next customer can not misuse the discount the registered customer receives.
            EmployeeCustomer(); // Calls the Function that asks if the user is an employee or customer or if they want to finish
        }
        else // ERROR checking the input from the user
        {
            cout << "[!]Please press Y for Yes or N for No: "; // ERROR Message that classifies what the user has to enter
            cin >> NxtCustomer; // Asking for correct input from user.
        }
    }
}

//**********************************************************************************************************************
// Function that displays the receipt and calls the NEXT CUSTOMER Function.
//**********************************************************************************************************************

void Receipt()
{
    char Letter = 'T';
    string ReceiptInput; // Declares the variable that asks for a user input for whether the user wants a receipt or not.

    cout << "\nPrint Receipt[Y/N]: "; // Prints out message that prompts the user to input there decision of if they want  receipt or not
    cin >> ReceiptInput; // Asks for user input for whether or not the user wants a receipt

    while (Letter != 'F')
    {
        if ((ReceiptInput == "Y") || (ReceiptInput == "y")) // IF the user enters Y or y which is YES the code below is executed.
        {
            outfile.open("Receipt.txt"); // Creates a text file for the receipt.
            for (Count = 0; Count <= 19; Count++) // FOR Loop to go through the created arrays to create a receipt file.
            {
                if (ItemPriceArray[Count] != 0) // Checks through the price array for non zero values as the user could have entered a false value for which the code leaves a place value of 0 at that point.
                {
                    Point = Count; // sets the Pointer Variable to the place in the price array that is non zero
                    // The code below formats the spacing between the elements for the Name, Barcode and Price before inputting into the receipt file created.
                    outfile << setw(10) << ItemNameBought[Point];
                    outfile << setw(12) << ItemBoughtArray[Point];
                    outfile << setw(10) << setprecision(2) << fixed << ItemPriceArray[Point]; // Formats the price before being put into the file to be fixed to 2 decimal points.
                    outfile << "\n"; // Seperates the different items with a line space.
                }
            }
            outfile.close(); // Closes the file
            // The code below prints the receipt to the screen.
            // The code below also prints and formats the position of the HEADERs.
            cout << "--------------------------------\n";
            cout << setw(22) << "RECEIPT\n\n";
            cout << setw(10) << "Item";
            cout << setw(12) << "Barcode";
            cout << setw(11) << "Price\n";
            ifstream openfile("Receipt.txt"); // Opens the file and uses openfile as a variable name to be used throughout the program
            char Check[255]; // Variable that Retrieves each line
            while (openfile) // WHILE Loop for during the outputting process which ends when the file has no more lines.
            {
                openfile.getline(Check, 255); // Gets the individual lines from the file when \n is found
                cout << Check << "\n"; // Prints the retrieved line from the file
            }
            cout << setw(27) << "Total: $" << TotalBill << endl; // Formats the position of the total price of the items bought.
            cout << "--------------------------------\n"; // Improves the aesthetic of the Formatted output
            openfile.close();
            NextCustomer(); // Calls the Next Customer function.
            Letter = 'F'; // Breaks the loop.
        }
        else if ((ReceiptInput == "N") || (ReceiptInput == "n")) // IF the user enters N or n for NO the code below is executed.
        {
            NextCustomer();
            Letter = 'F';
        }
        else // Error checks the Receipt input for non relevant values that are not Y or y or N or n.
        {
            cout << "[!]Please Press Y for Yes or N for No: "; // User Clarification of what should be entered
            cin >> ReceiptInput; // Requires user input after be presented with the Error message.
        }
    }
}

//**********************************************************************************************************************
// Function that Asks if the user is an employee or a customer or if they would like to finish.
//**********************************************************************************************************************

void EmployeeCustomer()
{
    string CustomerEmployee;
    char Letter = 'T';

    cout << "\nAre You An Employee or Customer or Would You Like To Finish[E/C/F]: "; // Message asking USER if they are an employee or a customer or would like to end the program.
    cin >> CustomerEmployee;

    while (Letter != 'F')
    {

        if ((CustomerEmployee == "E") || (CustomerEmployee == "e"))
        {
            EmployeeLogin(); // Calls Employee function so new items can be added.
            Letter = 'F'; // Breaks LOOP
        }
        else if ((CustomerEmployee == "C") || (CustomerEmployee == "c"))
        {
            CustomerDiscount(); // Calls Barcode function so the customer functions can run.
            Letter = 'F';
        }
        else if ((CustomerEmployee == "F") || (CustomerEmployee == "f"))
        {
            cout << "\nThank You For Using The Program.\n";
            Letter = 'F'; // Breaks LOOP
        }
        else // ERROR Check
        {
            cout << "[!]Please Enter Either E for Employee or C for Customer or F for Finish: "; // ERROR Message that defines what should be entered.
            cin >> CustomerEmployee;
        }
    }
}

//**********************************************************************************************************************
// Function that allows the user to enter employee mode and create new items.
//**********************************************************************************************************************

void Employee()
{
    string NB[10] = { "","1","2","3","4","5","6","7","8","9" }; // Array that contains the ends of the barcodes to be generated. Empty string at the start because the when retrieving information from the array the place value is 1 so the first value is ignored.
    string NewBarcode; // String that stores the newly created barcode.
    float NewPrice = 0.00; // Variable that allows the user to enter the price for the new item
    int k = 0; // Variable that is incremented so that the new item barcode, name and price created is stored in the new arrays.
    char Letter = 'T'; // Initialisation of WHILE LOOP.
    while (Letter != 'F') // While Loop for continuous input
    {
        if (cin.fail()) // ERROR Checks Price Input. There is a problem with cin.fail() and white space when something is entered that has a space such as "Dairy Milk" Hence it is required that the user is required to enter an underscore with two word or more items for example "Dairy_Milk".
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "[!]Incorrect Input: ";
            cin >> NewPrice;
        }
        else // If the input is correct the program continues
        {
            cout << "\nItem Name (Type 'F' to Finish): "; // Displays message asking for the name of the new item
            cin >> NewName; // Asks for user input. CIN Ignores whitespace.
            k++; // Incremented each loop so that each place in the array has a value
            if ((NewName == "F") || (NewName == "f")) // ends if the user enters 'f'.
            {
                EmployeeCustomer();
                Letter = 'F';
            }
            else // Otherwise the price is asked for the item entered.
            {
                cout << "Item Price: $";
                cin >> NewPrice;
            }
        }
        for (Count = 0; Count <= 19; Count++) // FOR LOOP going through the new arrays assigning values after every input
        {
            NewBarcode = "012001" + NB[k]; // Concatenation of two strings
            // The code below stores the new item barcode, name and price to the respective position in the Array.
            NewItemBarcode[k] = NewBarcode;
            NewItemName[k] = NewName;
            NewItemPrice[k] = NewPrice;
            break; // BREAKS LOOP when new barcode name and price are stored.
        }
    }
}

//**********************************************************************************************************************
// Function that allows the user to enter discount mode and buy cheaper items.
//**********************************************************************************************************************

void CustomerLogin()
{
    Username = ""; // Variable that stores the User input for the username.
    password = ""; // Variable that stores the User Input for the password.
    string UserNames[5] = { "Customer1","Customer2","Customer3","Customer4","Customer5" }; // Set of customer usernames as examples for easy testing
    string Password[5] = { "Password1","Password2","Password3","Password4","Password5" }; // Passwords generated that match the usernames EXAMPLES Of Strong User Passwords "yBz4WCp","XbBDe7F","9XHsTsPp","Yr3ZnkJb","bu9hGs5G".
    Count = 0; // This line of code is reset so the program can run.
    int Counter = 0;
    char Letter = 'T'; // Intialisation of while loop
    cout << "Username[Type 'X' To Enter Scanning Process]: "; // Message Requiring User Input for the username
    cin >> Username;
    if ((Username == "X") || (Username == "x") || (password == "X") || (password == "x")) // Incase user decides not to login in
    {
        BarcodeInput(); // Calls barcode Function to begin scanning barcodes (inputting barcodes).
        Letter = 'F';
    }
    else
    {
        cout << "Password[Type 'X' To Enter Scanning Process]: "; // Message Requiring User Input for the password
        cin >> password;
    }
    while (Letter != 'F') // WHILE LOOP Initialisation
    {
        for (Counter = 0; Counter <= 4; Counter++) // For LOOP Goes through the ARRAY of Usernames and Passwords
        {
            if (UserNames[Counter] == Username) // If the username is a match
            {
                if (Password[Counter] == password) // IF the Password matches the usernames password.
                {
                    Letter = 'F'; // Breaks Loop
                    Username = "";
                    password = "";
                    BarcodeInput(); // Calls the barcode function to carry out calculations.
                }
                else if (Password[Counter] != password) // IF the password is not equal
                {
                    cout << "[!]Incorrect Password[Type 'X' To Enter Scanning Process]: "; // ERROR Message
                    cin >> password; // Requires input from user for the correct password
                    if ((password == "X") || (password == "x")) // IF the customer wants to exit
                    {
                        BarcodeInput();
                        Letter = 'F';
                    }
                }
            }
            else if (UserNames[Counter] != Username) // IF the username does not match
            {
                cout << "[!]Incorrect Username[Type 'X' To Enter Scanning Process]: "; // ERROR Message
                cin >> Username; // Requires User Input for the correct User Name
                if ((Username == "X") || (Username == "x"))
                {
                    BarcodeInput();
                    Letter = 'F';
                }
            }
        }
    }
}

//**********************************************************************************************************************
// Function that allows the asks for the employee to login so that they are able
// to enter employee mode and add new items.
//**********************************************************************************************************************

void EmployeeLogin()
{
    Username = ""; // Resets the Variable that stores the User input for the username.
    password = ""; // Resets the Variable that stores the User Input for the password.
    char Letter = 'T';
    Count = 0;
    cout << "Employee Username[Type 'X' To Exit]: "; // Message Requiring User Input for the username
    cin >> Username;
    if ((Username == "X") || (Username == "x") || (password == "X") || (password == "x")) // Incase user decides not to login in
    {
        EmployeeCustomer(); // Calls EMployee customer function if the user wants to exit.
        Letter = 'F';
    }
    else
    {
        cout << "Employee Password[Type 'X' To Exit]: "; // Message Requiring User Input for the password
        cin >> password;
    }
    while (Letter != 'F') // WHILE LOOP Initialisation
    {
        if (EmployeeUserNames[Count] == Username) // If the username is a match
        {
            if (EmployeePassword[Count] == password) // IF the Password matches the usernames password.
            {
                Employee();
                Letter = 'F'; // Breaks Loop
            }
            else if (EmployeePassword[Count] != password) // IF the password is not equal
            {
                cout << "[!]Incorrect Password[Type 'X' To Exit]: "; // ERROR Message
                cin >> password; // Requires input from user for the correct password
                if ((password == "X") || (password == "x")) // IF the customer wants to exit
                {
                    Checker = 'A';
                    EmployeeCustomer();
                    Letter = 'F';
                }
            }
        }
        else if (EmployeeUserNames[Count] != Username) // IF the username does not match
        {
            cout << "[!]Incorrect Username[Type 'X' To Exit]: "; // ERROR Message
            cin >> Username; // Requires User Input for the correct User Name
            if ((Username == "X") || (Username == "x"))
            {
                EmployeeCustomer();
                Letter = 'F';
            }
        }
    }
    for (Count = 0; Count <= 4; Count++) // For LOOP Goes through the ARRAY of Usernames and Passwords
    {
    }
}

