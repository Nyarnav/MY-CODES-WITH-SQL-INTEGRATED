#include "sqlite3.h"
#include "encrypt.h"
#include "charToString.hpp"
#include<string>
#include<fstream>

using std::copy, std::string, std::cout, std::endl, std::cin, std::getline, std::to_string, std::runtime_error, std::cerr;

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
  
  Database()
  {
      openDb();
  }
  ~Database()
  {
      closeDb();
  }
  
    void openDb()
    {
        
        exit = sqlite3_open("data.db", &db);
        
        if (exit)
        throw runtime_error(error_msg);
            
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
        throw runtime_error(error_msg);
            
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
        throw runtime_error(error_msg);
        
        else
            cout << "\nSQLITE: Opened Database Successfully!\n";
            
        sql = "CREATE TABLE IF NOT EXISTS " + accounts_table + " (user_keys INTEGER PRIMARY KEY AUTOINCREMENT, password TEXT NOT NULL, username TEXT NOT NULL DEFAULT 'unknown person' );";
        
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);
        if (rc != SQLITE_OK)
        {
            throw runtime_error(error_msg);
        }
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
            
            data_username = convertCharAsString(check_username);
            
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
        throw runtime_error(error_msg);
        
        sql = "SELECT * FROM " + accounts_table + " WHERE username = '" + Username + "';";
        
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);

        if (sqlite3_column_type(stmt, 1) != SQLITE_NULL)
        {
            compare_password = sqlite3_column_text(stmt, 1);
            data_password = convertCharAsString(compare_password);
            data_password = decryptPass(data_password);
            
        }
        
        if (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
        {
            compare_username = sqlite3_column_text(stmt, 2);
            
             data_username = convertCharAsString(compare_username);
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
        throw runtime_error(error_msg);
        
        password_acc = encryptPass(password_acc);
        
        sql = "INSERT INTO " + accounts_table + "(password, username) VALUES('" + password_acc + "', '" + username_acc + "');";
        
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error_msg);

        if (rc != SQLITE_OK)
        throw runtime_error(error_msg);
            
        else
            cout << "\n[ Account added to database ]\n";
    }
    

    void closeDb()
    {
        sqlite3_close(db);
    }
    
};