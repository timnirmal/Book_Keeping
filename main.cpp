#include <iostream>
#include <io.h>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main() {
    //Change this directory to project
    string dir = "C:\\Users\\timni\\Book-Keeping\\";
    string delimiter = ",";
    size_t pos = 0;
    string token;
    string s;
    int item_count=0;

    string account_number;
    string date;
    string transaction_amount;
    string transaction_type;


    //Keep Account Balances in a vector to avoid read files again and again
    vector <string> account_number_list;
    vector <string> account_balance_list;


    //////////////////////////////////////// Need find solution for non empty folders. But this will still do the work.
    //Delete Folder
    _rmdir("C:\\Users\\timni\\Book-Keeping\\accounts");
    //remove("C:\\Users\\timni\\Book-Keeping\\accounts");

    //Create Folder
    _mkdir("C:\\Users\\timni\\Book-Keeping\\accounts");

    ///////////////////////////////////////////////////////////// Read balance
    ifstream myReadFile;
    myReadFile.open(dir+"balance.txt");
    string output;

    //Delete any content exists (change later)
    ofstream bankVault (dir + "bankVault.txt");
    bankVault.close();
    int bank_Balance = 0;

    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;

            s = output;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                if (item_count % 2 == 0){
                    date = token;
                }if (item_count % 2 == 1){
                    account_number = token;
                }
                item_count++;
                s.erase(0, pos + delimiter.length());
            }
            transaction_amount = s;
            bank_Balance += stoi(transaction_amount);
            cout << date << "  " << account_number << "  " << transaction_amount << endl;

            //Create text file according to the account name
            //Create + Open + Write File
            ofstream outfile (dir + "accounts\\" + account_number);
            outfile << date << ",0," << transaction_amount << "," << transaction_amount <<endl;
            outfile.close();

            account_number_list.push_back(account_number);
            account_balance_list.push_back(transaction_amount);
        }

        ////bankVault
        ofstream bankVault (dir + "bankVault.txt",ios_base::app);
        bankVault << date << ",0," << transaction_amount << "," << bank_Balance <<endl;
        bankVault.close();
    }
    myReadFile.close();


    ///////////////////////////////////////////////////////////// Read transaction
    myReadFile.open(dir + "transaction.txt");
    item_count = 0;

    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;

            s = output;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                if (item_count % 3 == 0){
                    date = token;
                }if (item_count % 3 == 1){
                    account_number = token;
                }if (item_count % 3 == 2){
                    transaction_type = token;
                }
                item_count++;
                s.erase(0, pos + delimiter.length());
            }
            transaction_amount = s;
            cout << date << "  " << account_number << "  " << transaction_type << "  " << transaction_amount << endl;

            //Create text file according to the account name
            //Create + Open + Write File
            ofstream accounts (dir + "accounts\\" + account_number,ios_base::app);
            if (stoi(transaction_type) == 1){
                //need to read the Balance from account

            }

            accounts << date << "," << transaction_type << ","
                << transaction_amount << "," << transaction_amount <<endl;
            accounts.close();
            ////bankVault
            ofstream bankVault (dir + "bankVault.txt",ios_base::app);
            bankVault << date << "," << transaction_type << ","
                << transaction_amount << "," << transaction_amount <<endl;
            bankVault.close();
        }
    }
    myReadFile.close();


    //Create + Open + Write File
    //ofstream outfile (dir + "accounts\\" + account_number);
    //outfile << "my text here!" << std::endl;
    //outfile.close();


    s = "He,Yaluwe,apiawaw";

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        cout << token << endl;
        s.erase(0, pos + delimiter.length());
    }
    cout << s << endl;

    for (int i =0; i< account_number_list.size() ; i++) {
        cout <<  account_balance_list[i] << " ";
    }
    cout<<endl;
    for (int i =0; i< account_number_list.size() ; i++) {
        cout << account_number_list[i] << " ";
    }
    return 0;
}

/*
 Delete all text files except balance.txt and transactino.txt

 Read balance.txt
*/

/*
 * balance.txt - sample balance sheet
     cash balance of all the customers and cash in the bank’s vault.
 * transaction.txt - transaction log sheet
     monthly interest calculation and account keeping charges are not indicated in the transaction logs

*/

