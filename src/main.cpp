#include <iostream>
#include <sqlite3.h>
#include <string>
#include "encrypt.h"
#include <algorithm>
#include<fstream>
#include<random>
using std::copy, std::string, std::cout, std::endl, std::cin, std::getline, std::to_string, std::runtime_error, std::cerr, std::ios, std::fstream,  std::random_device, std::uniform_int_distribution;
class Database
{
  
  private:
  
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *error_msg;
    string sql, accounts_table = "accounts", inventory_table, current_item, current_category, data_password;
    int exit = sqlite3_open("data.db", &db), rc, current_quantity;

  protected:
  
    string data_username;
    int data_key;
    char choices;


    void clearBuffer()
    {
        
        int clear;
        while ((clear = getchar()) != '\n' && clear != EOF)
            ;
            
    }


  public:
  
    void openDb()
    {
        
        exit = sqlite3_open("data.db", &db);
        if (exit)
            throw runtime_error(error_msg);

        else
            cout << "\nSQLITE: Opened Database Successfully!\n";
            
    }

    //database logic for inventory
    //     |
    //    \/

    void setInventoryTable(int account_unique_key)
    {
        
        inventory_table = "inventory" + to_string(account_unique_key);
        
    }


    void createInventoryDatabase()
    {
        
        if (exit)
            throw runtime_error(error_msg);

        sql = "CREATE TABLE IF NOT EXISTS " + inventory_table + " (item_keys INTEGER PRIMARY KEY AUTOINCREMENT, item TEXT NOT NULL DEFAULT 'Unidentified Item', quantity INTEGER NOT NULL DEFAULT 0, item_category TEXT NOT NULL DEFAULT 'Unidentfied Category' );";

        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);
        if (rc != SQLITE_OK)
            throw runtime_error(error_msg);
            
    }


    void insertItemFromInventory(string item_name, int quantity_item, string category)
    {
        if (exit)
            throw runtime_error(error_msg);

        sql = "INSERT INTO " + inventory_table + " (item, quantity, item_category ) VALUES('" + item_name + "', " + to_string(quantity_item) + ", '" + category + "');";

        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);

        if (rc != SQLITE_OK)
            throw runtime_error(error_msg);
        else
            cout << "\n[ ITEM ADDED ]\n";
    }


    void deleteItem(int key)
    {
        
        if (exit)
            throw runtime_error(error_msg);

        switch (choices)
        {
        case '1':

            sql = "DELETE FROM " + inventory_table + " WHERE item_keys = " + to_string(key) + ";";

            break;
        case '2':

            sql = "DELETE FROM " + inventory_table + " WHERE item = '" + current_item + "';";

            break;
        case '3':

            sql = "DELETE FROM " + inventory_table + " WHERE item_category = '" + current_category + "';";

            break;
        case '4':

            sql = "DELETE FROM " + inventory_table + " WHERE quantity = " + to_string(current_quantity) + ";";

            break;
        }
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);

        if (rc != SQLITE_OK)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
        cout << "\n [ DELETE PROCESS DONE! ]\n";
        
    }


    void setItemName(string item_name)
    {
        current_item = item_name;
    }
    void setItemQuantity(int item_quantity)
    {
        current_quantity = item_quantity;
    }
    void setItemCategory(string item_category)
    {
        current_category = item_category;
    }


    void updateItemFromInventory(int key)
    {
        
        if (exit)
            throw runtime_error(error_msg);
        switch (choices)
        {
        case '1':

            sql = "UPDATE " + inventory_table + " SET item = '" + current_item + "' WHERE item_keys = " + to_string(key) + ";";

            break;
        case '2':

            sql = "UPDATE " + inventory_table + " SET quantity = " + to_string(current_quantity) + " WHERE item_keys = " + to_string(key) + ";";

            break;
        case '3':

            sql = "UPDATE " + inventory_table + " SET item_category = '" + current_category + "' WHERE item_keys = " + to_string(key) + ";";

            break;
        }

        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);

        if (rc != SQLITE_OK)
            throw runtime_error(error_msg);
        else
            cout << "\n[ ITEM UPDATED! ]\n";
            
    }


    void showListOfItemsFromInventory()
    {
        
        const unsigned char *item = NULL;
        const unsigned char *category = NULL;
        int quantity = NULL;
        int keys = NULL;
        
        if (exit)
            throw runtime_error(error_msg);
        sql = "SELECT * FROM " + inventory_table + ";";

        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

        while (sqlite3_step(stmt) != SQLITE_DONE)
        {
            if (sqlite3_column_type(stmt, 0) != SQLITE_NULL)
            {
                keys = sqlite3_column_int(stmt, 0);
                cout << "\n\nitem_key = " << keys;
            }
            else
            {
                cerr << "[ NO DATA EXISTS! ]";
            }
            if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
            {
                item = sqlite3_column_text(stmt, 1);
                cout << "\nitem = " << item;
            }
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
            {
                quantity = sqlite3_column_int(stmt, 2);
                cout << "\nquantity = " << quantity;
            }
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL)
            {
                category = sqlite3_column_text(stmt, 3);
                cout << "\nitem_category = " << category << "\n\n";
            }
        }
    }


    int showSpecificListOfItem(int key)
    {
        
        const unsigned char *item = NULL;
        const unsigned char *category = NULL;
        int quantity = NULL;
        
        if (exit)
            throw runtime_error(error_msg);
            
        sql = "SELECT * FROM " + inventory_table + " WHERE item_keys = " + to_string(key) + "; ";
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
        
        if (sqlite3_column_type(stmt, 0) != SQLITE_NULL)
        {
            item = sqlite3_column_text(stmt, 1);
            quantity = sqlite3_column_int(stmt, 2);
            category = sqlite3_column_text(stmt, 3);
            cout << "\nitem = " << item << "\nquantity = " << quantity << "\nitem_category = " << category;
            sqlite3_finalize(stmt);
            return 1;
        }
        
        sqlite3_finalize(stmt);
        return 0;
        
    }

    //database logic for accounts
    //     |
    //    \/
    void createAccountDatabase()
    {
        
        if (exit)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
        else
            cout << "\nSQLITE: Opened Database Successfully!\n";
        sql = "CREATE TABLE IF NOT EXISTS " + accounts_table + " (user_keys INTEGER PRIMARY KEY AUTOINCREMENT, password TEXT NOT NULL, username TEXT NOT NULL DEFAULT 'unknown person' );";
        
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);
        if (rc != SQLITE_OK)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
    }


    void convertPasswordAsString(const unsigned char *passed_password)
    {
        string get_string_data;
        copy(passed_password, passed_password + strlen((const char *)passed_password), back_inserter(get_string_data));
        data_password = get_string_data;
    }


    void convertUsernameAsString(const unsigned char *passed_username)
    {
        string get_string_data;
        copy(passed_username, passed_username + strlen((const char *)passed_username), back_inserter(get_string_data));
        data_username = get_string_data;
    }


    bool checkIfAccountExists(string Username)
    {
        
        const unsigned char *check_username = NULL;
        sql = "SELECT * FROM " + accounts_table + " WHERE username = '" + Username + "';";
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);

        if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
        {
            check_username = sqlite3_column_text(stmt, 2);
            convertUsernameAsString(check_username);
            
            if (Username == data_username)
            {
                sqlite3_finalize(stmt);
                return true;
            }
        }
        
        sqlite3_finalize(stmt);
        
        return false;
        
    }
    

    int checkLoginUser(string Password, string Username)
    {
        const unsigned char *compare_password = NULL;
        const unsigned char *compare_username = NULL;
        
        if (exit)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
        
        sql = "SELECT * FROM " + accounts_table + " WHERE username = '" + Username + "';";
        
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);

        if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
        {
            compare_password = sqlite3_column_text(stmt, 1);
            convertPasswordAsString(compare_password);
            data_password = decryptPass(data_password);
            
        }
        
        if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
        {
            compare_username = sqlite3_column_text(stmt, 2);
             convertUsernameAsString(compare_username);
        }
        
            if(Username == data_username && Password == data_password)
            {
                data_key = (sqlite3_column_int(stmt, 0));
                
                sqlite3_finalize(stmt);
                sqlite3_busy_timeout(db, 3000);
                return true;
            }
        
        sqlite3_finalize(stmt);
        return false;
        
    }
    
    
    
    string getEncryptKey()
    {
        string decryptionKey;
        
        fstream key;
        
        key.open("config.txt", ios::in);
        
        if(key.is_open())
        {
            key >> decryptionKey;
        }
        
        return decryptionKey; 
    }
    
    string encryptPass(string Password)
    {
        string encrypt_pass;
        string encryption_key = getEncryptKey();
        encrypt_pass = encrypt(Password, encryption_key);
        
        return encrypt_pass;
    }
    
    string decryptPass(string encrypted_pass)
    {
        string decrypt_pass;
        string encryption_key = getEncryptKey();
        decrypt_pass = decrypt(encrypted_pass, encryption_key);
        
        return decrypt_pass;
    }
    
    
    
    void createNewColumnForUser(string username_acc, string password_acc)
    {
        if (exit)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
        
        password_acc = encryptPass(password_acc);
        
        sql = "INSERT INTO " + accounts_table + "(password, username) VALUES('" + password_acc + "', '" + username_acc + "');";
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);

        if (rc != SQLITE_OK)
        {
            closeDb();
            throw runtime_error(error_msg);
        }
        else
            cout << "\n[ Account added to database ]\n";
    }
    

    void closeDb()
    {
        sqlite3_close(db);
    }
    
};



class LoginOrRegister : public Database
{
  
  private:
  
    string input_password, input_username;

  public:
  
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
            closeDb();
            cerr << "\nSQLITE: " << column_error;
        }
        
        return 1;
        
    }
    
};

class Inventory : public Database
{
  
  private:
  
    int item_quantity, key_item, acc_unique_key;
    string item_name, acc_username, item_category;

  public:
  
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
            closeDb();
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
    Inventory manage_inventory;

    try
    {
        manage_db.createAccountDatabase();
    }
    catch (const char *error)
    {
        cerr << error;
        manage_db.closeDb();
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
            manage_db.closeDb();
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
            manage_db.closeDb();
            return 0;
        }
    }

    manage_db.closeDb();
    return 0;
    
}