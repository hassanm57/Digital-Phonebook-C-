#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <string>
#include <iomanip>  // For formatting output

using namespace std;

// Node structure for a contact
struct ContactNode {
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
    ContactNode* next;
};

// Function declarations
void addContact();
void searchContact();
void displayContacts();
void editContact();
void deleteContact();
void selfExit();
void displayMenu();
bool checkDigits(const string&);
bool checkNumbers(const string&);
void binarySearchByName(const string&);
void searchByPhoneNumber(const string&);
int hashFunction(const string&);
void sortContacts();
void importContactsFromFile();
void exportContactsToFile();




// Global variables
ContactNode* contactList = nullptr;
const int hashTableSize = 26;
ContactNode* hashTable[hashTableSize] = {nullptr};

int main() {
    short int choice;

    do {
        system("cls");
        system("color 0A");
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                displayContacts();
                break;
            case 4:
                editContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                sortContacts();
                break;
            case 7:
                exportContactsToFile();
                break;
            case 8:
                importContactsFromFile();
                break;
            case 9:
                selfExit();
                break;
            default:
                cout << "\n\n\tInvalid Input!";
                cout << "\n\tPress Any Key To Continue..";
                getch();
        }

     } while (choice != 9);

    return 0;
}


void selfExit() {
   exit(0);
}

void addContact() {
    system("cls");
    cout << "\n\n\t\tAdd a New Contact\n";

    string fname, lname, phoneNum, email;

    cout << "\n\tEnter First Name : ";
    cin >> fname;

    // Check if the first name is empty or contains spaces
    if (fname.empty() || fname.find(' ') != string::npos) {
        cout << "\n\tInvalid First Name!";
        cout << "\n\tPress Any Key To Continue..";
        getch();
        return;
    }

    cout << "\tEnter Last Name  : ";
    cin >> lname;

    // Check if the last name is empty or contains spaces
    if (lname.empty() || lname.find(' ') != string::npos) {
        cout << "\n\tInvalid Last Name!";
        cout << "\n\tPress Any Key To Continue..";
        getch();
        return;
    }

    // Check if the first and last name are the same
    if (fname == lname) {
        cout << "\n\tFirst Name and Last Name cannot be the same!";
        cout << "\n\tPress Any Key To Continue..";
        getch();
        return;
    }

    cout << "\tEnter Phone Number : ";
    cin >> phoneNum;
    cout << "\tEnter Email      : ";
    cin >> email;

    if (checkDigits(phoneNum) && checkNumbers(phoneNum)) {
        // Create a new contact node
        ContactNode* newContact = new ContactNode{fname, lname, phoneNum, email, nullptr};

        // Add the new contact to the linked list
        if (contactList == nullptr) {
            contactList = newContact;
        } else {
            ContactNode* current = contactList;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newContact;
        }

        // Add the new contact to the hash table
        int hashValue = hashFunction(fname);
        if (hashTable[hashValue] == nullptr) {
            hashTable[hashValue] = newContact;
        } else {
            newContact->next = hashTable[hashValue];
            hashTable[hashValue] = newContact;
        }

        cout << "\n\tContact Saved Successfully!";
    } else {
        cout << "\n\tInvalid Phone Number!";
    }

    cout << "\n\tPress Any Key To Continue..";
    getch();
}



void searchContact() {
    system("cls");
    int searchChoice;
    cout << "\n\tSearch Contact By:\n\t1. Name\n\t2. Phone Number\n\t3. Back\n\t> ";
    cin >> searchChoice;

    switch (searchChoice) {
        case 1:
            {
                string keyword;
                cout << "\n\tEnter Name To Search : ";
                cin.ignore();  // Ignore the newline character in the buffer
                getline(cin, keyword);
                binarySearchByName(keyword);
            }
            break;
        case 2:
            {
                string phoneNumber;
                cout << "\n\tEnter Phone Number To Search : ";
                cin >> phoneNumber;
                searchByPhoneNumber(phoneNumber);
            }
            break;
        case 3:
            return;  // Go back to the main menu
        default:
            cout << "\n\tInvalid Choice!";
    }

    cout << "\n\tPress Any Key To Continue..";
    getch();
}


void binarySearchByName(const string& name) {
    int arraySize = 0;
    ContactNode* sortedArray[100]; 

    for (int i = 0; i < hashTableSize; ++i) {
        ContactNode* current = hashTable[i];
        while (current != nullptr) {
            sortedArray[arraySize++] = current;
            current = current->next;
        }
    }

    for (int i = 0; i < arraySize - 1; ++i) {
        for (int j = 0; j < arraySize - i - 1; ++j) {
            if (sortedArray[j]->firstName > sortedArray[j + 1]->firstName) {
                swap(sortedArray[j], sortedArray[j + 1]);
            }
        }
    }

    // Binary search
    int low = 0, high = arraySize - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (sortedArray[mid]->firstName == name) {
            // Contact found
            cout << "\n\n\n\t\tContact Details\n";
            cout << setw(20) << left << "\n\tFirst Name:" << sortedArray[mid]->firstName;
            cout << setw(20) << left << "\n\tLast Name:" << sortedArray[mid]->lastName;
            cout << setw(20) << left << "\n\tPhone Number:" << sortedArray[mid]->phoneNumber;
            cout << setw(20) << left << "\n\tEmail:" << sortedArray[mid]->email;
            return;
        } else if (sortedArray[mid]->firstName < name) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << "\n\tNo Such Contact Found";
}

int hashFunction(const string& name) {
    char firstChar = toupper(name[0]);  // Convert to uppercase for case-insensitive hashing
    int index = int(firstChar) - int('A');
    return index >= 0 && index < hashTableSize ? index : -1;
}

bool checkDigits(const string& str) {
    return str.length() == 11 && all_of(str.begin(), str.end(), ::isdigit);
}

bool checkNumbers(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}
void displayContacts() {
    system("cls");
    cout << "\n\n\t\tContact List\n\n";

    // Display contacts from the linked list
    ContactNode* current = contactList;
    while (current != nullptr) {
        cout << setw(20) << left << "\n\tFirst Name:" << current->firstName;
        cout << setw(20) << left << "\n\tLast Name:" << current->lastName;
        cout << setw(20) << left << "\n\tPhone Number:" << current->phoneNumber;
        cout << setw(20) << left << "\n\tEmail:" << current->email << "\n\n";
        current = current->next;  // Move to the next contact
    }

    cout << "\n\tPress Any Key To Continue..";
    getch();
}


void editContact() {
    system("cls");
    string nameToEdit;
    cout << "\n\tEnter Name to Edit : ";
    cin.ignore();
    getline(cin, nameToEdit);

    // Search for the contact to edit
    int hashValue = hashFunction(nameToEdit);
    ContactNode* current = hashTable[hashValue];
    ContactNode* prev = nullptr;

    while (current != nullptr) {
        if (current->firstName == nameToEdit) {
            // Display the contact details
            cout << "\n\tContact Details\n";
            cout << setw(20) << left << "\n\tFirst Name:" << current->firstName;
            cout << setw(20) << left << "\n\tLast Name:" << current->lastName;
            cout << setw(20) << left << "\n\tPhone Number:" << current->phoneNumber;
            cout << setw(20) << left << "\n\tEmail:" << current->email;

            // Ask the user what information to edit
            cout << "\n\n\tSelect information to edit:";
            cout << "\n\t1. First Name";
            cout << "\n\t2. Last Name";
            cout << "\n\t3. Phone Number";
            cout << "\n\t4. Email";
            cout << "\n\t5. Cancel";
            cout << "\n\t> ";

            int editChoice;
            cin >> editChoice;

            switch (editChoice) {
                case 1:
                    cout << "\n\tEnter New First Name : ";
                    cin >> current->firstName;
                    break;
                case 2:
                    cout << "\n\tEnter New Last Name  : ";
                    cin >> current->lastName;
                    break;
                case 3:
                    cout << "\n\tEnter New Phone Number : ";
                    cin >> current->phoneNumber;
                    break;
                case 4:
                    cout << "\n\tEnter New Email      : ";
                    cin >> current->email;
                    break;
                case 5:
                    // Cancel editing
                    cout << "\n\tEditing canceled.";
                    cout << "\n\tPress Any Key To Continue..";
                    getch();
                    return;
                default:
                    cout << "\n\tInvalid Choice!";
                    cout << "\n\tPress Any Key To Continue..";
                    getch();
                    return;
            }

            cout << "\n\tContact Edited Successfully!";
            cout << "\n\tPress Any Key To Continue..";
            getch();
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "\n\tNo Such Contact Found";
    cout << "\n\tPress Any Key To Continue..";
    getch();
}


void deleteContact() {
    system("cls");
    string nameToDelete;
    cout << "\n\tEnter Name to Delete : ";
    cin.ignore();
    getline(cin, nameToDelete);

    // Search for the contact to delete in the hash table
    int hashValue = hashFunction(nameToDelete);
    ContactNode* current = hashTable[hashValue];
    ContactNode* prevHash = nullptr;

    while (current != nullptr) {
        if (current->firstName == nameToDelete) {
            // Delete the contact from the hash table
            if (prevHash == nullptr) {
                hashTable[hashValue] = current->next;
            } else {
                prevHash->next = current->next;
            }

            // Search for the contact to delete in the linked list
            ContactNode* currentList = contactList;
            ContactNode* prevList = nullptr;

            while (currentList != nullptr) {
                if (currentList == current) {
                    // Delete the contact from the linked list
                    if (prevList == nullptr) {
                        contactList = currentList->next;
                    } else {
                        prevList->next = currentList->next;
                    }

                    delete currentList;  // Delete the contact node

                    cout << "\n\tContact Deleted Successfully!";
                    cout << "\n\tPress Any Key To Continue..";
                    getch();
                    return;
                }

                prevList = currentList;
                currentList = currentList->next;
            }
        }

        prevHash = current;
        current = current->next;
    }

    cout << "\n\tNo Such Contact Found";
    cout << "\n\tPress Any Key To Continue..";
    getch();
}


void displayMenu() {
    cout << "\n\n\n\t\t\tDigital Phonebook";
    cout << "\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. Display Contacts\n\t4. Edit Contact\n\t5. Delete Contact\n\t6. Sort Contacts\n\t7. Export Contacts to File\n\t8. Import Contacts from file\n\t9. Exit\n\tEnter choice: ";
}
void sortContacts() {
    system("cls");

      if (contactList == nullptr) {
        cout << "\n\tNo contacts available. Add contacts before using the sort function.";
       getch();
    } else {
    
    // Create an array to store contacts
    ContactNode* sortedArray[100];
    int arraySize = 0;

    // Populate the array with contacts from the hash table
    for (int i = 0; i < hashTableSize; ++i) {
        ContactNode* current = hashTable[i];
        while (current != nullptr) {
            sortedArray[arraySize++] = current;
            current = current->next;
        }
    }

    // Sort the array based on first names
    for (int i = 0; i < arraySize - 1; ++i) {
        for (int j = 0; j < arraySize - i - 1; ++j) {
            if (sortedArray[j]->firstName > sortedArray[j + 1]->firstName) {
                swap(sortedArray[j], sortedArray[j + 1]);
            }
        }
    }

    // Display the sorted contacts, avoiding duplicates
    cout << "\n\n\t\tSorted Contact List\n\n";
    for (int i = 0; i < arraySize; ++i) {
        // Check for duplicates before displaying
        if (i == 0 || sortedArray[i]->firstName != sortedArray[i - 1]->firstName) {
            cout << setw(20) << left << "\n\tFirst Name:" << sortedArray[i]->firstName;
            cout << setw(20) << left << "\n\tLast Name:" << sortedArray[i]->lastName;
            cout << setw(20) << left << "\n\tPhone Number:" << sortedArray[i]->phoneNumber;
            cout << setw(20) << left << "\n\tEmail:" << sortedArray[i]->email << "\n\n";
        }
    }

    cout << "\n\tPress Any Key To Continue..";
    
    getch();
}
}
#include <fstream>

void exportContactsToFile() {
    system("cls");

    // Check if there are contacts to export
    if (contactList == nullptr) {
        cout << "\n\tNo contacts available to export.";
    } else {
        // Prompt user for the file name
        string fileName;
        cout << "\n\tEnter the file name to export contacts (include extension, e.g., contacts.txt): ";
        cin >> fileName;

        // Open the file for writing
        ofstream outputFile(fileName);

        // Check if the file is successfully opened
        if (!outputFile.is_open()) {
            cout << "\n\tError opening the file. Contacts not exported.";
        } else {
            // Write contacts to the file
            ContactNode* current = contactList;
           while (current != nullptr) {
                outputFile << "Name: " << current->firstName << " " << current->lastName << "\n";
                outputFile << "Phone: " << current->phoneNumber << "\n";
                outputFile << "Email: " << current->email << "\n\n";
                current = current->next;
            }

            outputFile.close();

            cout << "\n\tContacts exported to " << fileName << " successfully.";
        }
    }

    // Delay before returning to the main menu
    cout << "\n\tPress Any Key To Continue..";
    getch();
}
void importContactsFromFile() {
    system("cls");

    // Prompt user for the file name
    string fileName;
    cout << "\n\tEnter the file name to import contacts (include extension, e.g., contacts.txt): ";
    cin >> fileName;

    // Open the file for reading
    ifstream inputFile(fileName);

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cout << "\n\tError opening the file. Contacts not imported.";
    } else {
        // Read contacts from the file
        string line;
        while (getline(inputFile, line)) {
            // Extract contact information from the line
            string firstName, lastName, phone, email;
            if (line.find("Name: ") == 0) {
                // Assume the name is in the format "First Last"
                string fullName = line.substr(6);

                // Find the position of the first space to split first and last name
                size_t spacePos = fullName.find(' ');
                if (spacePos != string::npos) {
                    firstName = fullName.substr(0, spacePos);
                    lastName = fullName.substr(spacePos + 1);
                } else {
                    // If there's only one word, consider it as the first name
                    firstName = fullName;
                }

                getline(inputFile, line);
                if (line.find("Phone: ") == 0) {
                    phone = line.substr(7);
                    getline(inputFile, line);
                    if (line.find("Email: ") == 0) {
                        email = line.substr(7);

                        // Create a new contact node
                        ContactNode* newContact = new ContactNode{firstName, lastName, phone, email, nullptr};

                        // Add the new contact to the linked list
                        if (contactList == nullptr) {
                            contactList = newContact;
                        } else {
                            ContactNode* current = contactList;
                            while (current->next != nullptr) {
                                current = current->next;
                            }
                            current->next = newContact;
                        }

                        // Add the new contact to the hash table
                        int hashValue = hashFunction(firstName);
                        if (hashTable[hashValue] == nullptr) {
                            hashTable[hashValue] = newContact;
                        } else {
                            newContact->next = hashTable[hashValue];
                            hashTable[hashValue] = newContact;
                        }
                    } else {
                        cout << "\n\tError reading contact information from the file. Contacts not imported.";
                        return;
                    }
                } else {
                    cout << "\n\tError reading contact information from the file. Contacts not imported.";
                    return;
                }
            }
        }

        inputFile.close();

        cout << "\n\tContacts imported from " << fileName << " successfully.";
    }

    // Delay before returning to the main menu
    cout << "\n\tPress Any Key To Continue..";
    getch();
}
void searchByPhoneNumber(const string& phoneNumber) {
    system("cls");

    // Iterate through the hash table to find the contact with the given phone number
    for (int i = 0; i < hashTableSize; ++i) {
        ContactNode* current = hashTable[i];
        while (current != nullptr) {
            if (current->phoneNumber == phoneNumber) {
                // Contact found
                cout << "\n\n\n\t\tContact Details\n";
                cout << setw(20) << left << "\n\tFirst Name:" << current->firstName;
                cout << setw(20) << left << "\n\tLast Name:" << current->lastName;
                cout << setw(20) << left << "\n\tPhone Number:" << current->phoneNumber;
                cout << setw(20) << left << "\n\tEmail:" << current->email;
                return;
            }
            current = current->next;
        }
    }

    cout << "\n\tNo Such Contact Found";
}