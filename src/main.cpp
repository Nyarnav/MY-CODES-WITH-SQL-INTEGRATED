#include <iostream>
#include <string>
#include "myDatabase.hpp"


using std::string, std::cout, std::endl, std::cin, std::getline, std::to_string, std::runtime_error, std::cerr;


class LoginOrRegister : public Database
{
  
  private:
  
    string input_password, input_username;

  public:
  
  LoginOrRegister()
  {
      openDb();
  }
  ~LoginOrRegister()
  {
    closeDb();
  }
    string getUsername()
    {
        return data_username;
    }


    int getPrimaryKey()
    {
        return data_key;
    }


    int chooseLoginOrRegister()
    {
        
        cout << "\nPRESS [ 1 ] AND ENTER TO LOGIN\nPRESS [ 2 ] AND ENTER TO REGISTER\nPRESS [ 0 ] AND ENTER TO EXIT\nCHOOSE: ";
        cin >> choices;
        clearBuffer();
        switch (choices)
        {
        case '0':
            return false;
            closeDb();
            break;
        case '1':
            return login();
            break;
        case '2':
            return registerAcc();
            break;
        default:
            cerr << "\nINPUT ERROR: [ PLEASE INPUT THE AVAILABLE COMMAND ]\n";
            break;
        }

        return 1;
        
    }


    int login()
    {
        
        cout << "\n\n[ Login ]\n\n";
        cout << "\nUsername: ";
        getline(cin, input_username);
        cout << "\nPassword: ";
        cin >> input_password;
        clearBuffer();

        if (checkLoginUser(input_password, input_username))
        {
            cout << "\n[ WELCOME " << getUsername() << " #" << getPrimaryKey() << " TO INVENTORY SYSTEM ]\n";
            return 2;
        }
        else
        {
            cerr << "\n\tERROR: [ Wrong password or username ]\n";
            return 1;
        }
        
    }


    int registerAcc()
    {
        
        cout << "\n\n[ Register ]\n\n";
        cout << "\nUsername: ";
        getline(cin, input_username);
        cout << "\nPassword: ";
        cin >> input_password;
        clearBuffer();

        if (checkIfAccountExists(input_username))
        {
            cerr << "\n\tERROR: [ USERNAME ALREADY EXISTS ]\n";
            return 1;
        }
        try
        {
            createNewColumnForUser(input_username, input_password);
        }
        catch (const char *column_error)
        {
            cerr << "\nSQLITE: " << column_error;
        }
        
        return 1;
        
    }
    
};


class UserInventory : public Database
{
  
  private:
  
    int item_quantity, key_item, acc_unique_key;
    string item_name, acc_username, item_category;

  public:
  
  UserInventory()
  {
      openDb();
  }
  ~UserInventory()
  {
      closeDb();
  }
  
    void setUsernameAndKey(string Account_Username, int Account_Unique_Key)
    {
        
        acc_username = Account_Username;
        acc_unique_key = Account_Unique_Key;
        
    }


    int menu()
    {
        
        setInventoryTable(acc_unique_key);
        
        try
        {
            createInventoryDatabase();
        }
        catch (const char *table_error)
        {
            cerr << "\nSQLITE ERROR: " << table_error;
            return 0;
        }
        
        cout << "\nUser Account name: " << acc_username << " #" << acc_unique_key << "\n[ Inventory Menu ] \n\nPRESS [ 1 ] AND ENTER TO ADD ITEM\nPRESS [ 2 ] AND ENTER TO UPDATE ITEM\nPRESS [ 3 ] AND ENTER TO DELETE ITEM\nPRESS [ 0 ] AND ENTER TO EXIT\nChoose: ";
        cin >> choices;
        
        switch (choices)
        {
        case '0':
            return 0;
            break;
        case '1':

            createItem();

            break;
        case '2':

            updateItem();

            break;
        case '3':
        
            deleteItem();
            
            break;
        default:
            cerr << "\n\tERROR: [ ENTER ONLY THE AVAILABLE CHOICES ]\n";
            break;
        }
        
        return 1;
    }
    

    void createItem()
    {
        
        readItemTable();
        
        cout << "\n\t++++[ CREATE/ADD ITEM ]++++\n";
        clearBuffer();
        cout << "Item Name: ";
        getline(cin, item_name);
        
        cout << "Item type: ";
        getline(cin, item_category);
        
        cout << "Item Quantity: ";
        cin >> item_quantity;
        
        clearBuffer();
        
        try
        {
            insertItemFromInventory(item_name, item_quantity, item_category);
        }
        catch (const char *sql_error)
        {
            cerr << "ERROR: " << sql_error;
        }
        
    }

    void readItemTable()
    {
        
        cout << "\n\n\t-->[ ITEM LIST ]<--\n\n";
        cout << "########################";
        try
        {
            showListOfItemsFromInventory();
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE ERROR: " << sql_error;
        }
        cout << "########################\n\n";
        
    }

    void updateItemName()
    {
        
        clearBuffer();
        cout << "enter the updated ( item ): ";
        getline(cin, item_name);
        
        setItemName(item_name);
        
        try
        {
            updateItemFromInventory(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE: " << sql_error;
        }
        
    }
    
    
    void updateItemQuantity()
    {
        
        clearBuffer();
        
        cout << "enter the updated ( quantity ): ";
        cin >> item_quantity;
        
        setItemQuantity(item_quantity);
        
        try
        {
            updateItemFromInventory(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE: " << sql_error;
        }
        
    }
    
    
    void updateItemCategory()
    {
        
        clearBuffer();
        
        cout << "enter the updated ( item_category ): ";
        getline(cin, item_category);
        
        setItemCategory(item_category);
        
        try
        {
            updateItemFromInventory(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE: " << sql_error;
        }
        
    }


    void updateItem()
    {
        
        readItemTable();
        
        cout << "\n\t#####[ UPDATE SPECIFIC ITEM ]####\n";
        cout << "Enter the key: ";
        cin >> key_item;

        if (showSpecificListOfItem(key_item) == 1)
        {
            while (true)
            {
                cout << "\n===>Choose which to edit<===\n\nPRESS [ 1 ] AND ENTER TO UPDATE ( item )\nPRESS [ 2 ] AND ENTER TO UPDATE ( quantity )\nPRESS [ 3 ] AND ENTER TO UPDATE ( item_category )\nPRESS [ 0 ] TO CANCEL\nchoose: ";
                cin >> choices;
                switch (choices)
                {
                case '0':
                    return;
                    break;
                case '1':

                    updateItemName();

                    break;
                case '2':

                    updateItemQuantity();

                    break;
                case '3':

                    updateItemCategory();

                    break;
                default:
                    cerr << "\n[ INVALID CHOICES, CHOOSE THE AVAILABLE OPTIONS ]\n";
                }
            }
        }
        else
            cerr << "\n[ INVALID KEY ]\n";
            
    }
    

    void deleteSpecificColumn()
    {
        
        clearBuffer();
        cout << "\nEnter the key to delete a specific column: ";
        cin >> key_item;
        
        try
        {
            Database::deleteItem(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE ERROR: " << sql_error;
        }
        
    }


    void deleteColumnsByItemName()
    {
        
        clearBuffer();
        cout << "\nEnter the ( item ) to delete wite the same name of other columns: ";
        getline(cin, item_name);
        
        setItemName(item_name);
        
        try
        {
            Database::deleteItem(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE ERROR: " << sql_error;
        }
        
    }


    void deleteColumnsByCategory()
    {
        
        clearBuffer();
        cout << "\nEnter the ( item_category ) to delete wite the same name of other columns: ";
        getline(cin, item_category);
        
        setItemCategory(item_category);
        
        try
        {
            Database::deleteItem(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE ERROR: " << sql_error;
        }
        
    }


    void deleteColumnsByQuantity()
    {
        
        clearBuffer();
        
        cout << "\nEnter the ( quantity ) to delete with the same value of other columns: ";
        cin >> item_quantity;
        setItemQuantity(item_quantity);
        
        try
        {
            Database::deleteItem(key_item);
        }
        catch (const char *sql_error)
        {
            cerr << "SQLITE ERROR: " << sql_error;
        }
        
    }


    void deleteItem()
    {
        
        readItemTable();

        cout << "\n\t####[ REMOVE ITEM FROM TABLE ]####\n";
        while (true)
        {
            cout << "\nPRESS [ 1 ] AND ENTER TO DELETE A SPECIFIC COLUMN\nPRESS [ 2 ] AND ENTER TO DELETE A WHOLE GROUP OF COLUMN WITH THE SAME ( item )\nPRESS [ 3 ] AND ENTER TO DELETE A WHOLE GROUP OF COLUMN WITH THE SAME ( item_category )\nPRESS [ 4 ] AND ENTER TO DELETE A WHOLE GROUP OF COLUMN WITH THE QUANTITY PROVIDED\nPRESS [ 0 ] TO GO BACK TO MENU\nchoose: ";
            cin >> choices;

            switch (choices)
            {
            case '0':
                return;
                break;
            case '1':

                deleteSpecificColumn();

                break;
            case '2':

                deleteColumnsByItemName();

                break;
            case '3':

                deleteColumnsByCategory();

                break;
            case '4':

                deleteColumnsByQuantity();

                break;
            default:

                cerr << "\n[ INVALID INPUT PLEASE CHOOSE THE AVAILABLE OPTIONS ]\n";

                break;
            }
        }
    }
    
};

int main(int argc, char *argv[])
{
    cout << "[ WITH SQLITE DATABASE! ]\n\n\t###[ WELCOME TO VAN RYAN'S INVENTORY SYSTEM ]###\n\n";
    int dont_want_to_exit = 1;
    
    Database manage_db;
    LoginOrRegister open_account;
    UserInventory manage_inventory;
    
    try
    {
        manage_db.createAccountDatabase();
    }
    catch (const char *error)
    {
        cerr << error;
        return -1;
    }

    //if 1 then still continue and choose if you want to login or register, if it's 2 then the user already logged in, if 0 then the user exit the program
    while (dont_want_to_exit == 1)
    {
        dont_want_to_exit = open_account.chooseLoginOrRegister();
        if (dont_want_to_exit == 2)
            manage_inventory.setUsernameAndKey(open_account.getUsername(), open_account.getPrimaryKey());

        if (dont_want_to_exit == 0)
        {
            return 0;
        }
    }
    
    dont_want_to_exit = 1;
    // almost same process at the first while loop, if 1 then user still did not choose to exit or if the there's an unexpected runtime error happened to the code
    while (dont_want_to_exit == 1)
    {
        dont_want_to_exit = manage_inventory.menu();
        if (dont_want_to_exit == 0)
        {
            return 0;
        }
    }

    return 0;
    
}