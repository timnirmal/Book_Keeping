#include <iostream>
#include <io.h>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main() {
    //Change this directory to project
    string dir = "C:\\Users\\timni\\Book-Keeping\\";
    string delimiter = ",";
    size_t pos = 0;
    string token;
    string s;
    int item_count=0;

    string account_name;
    string date;
    string account_balance;



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
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;

            s = output;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                if (item_count % 2 == 0){
                    date = token;
                }if (item_count % 2 == 1){
                    account_name = token;
                }
                item_count++;
                s.erase(0, pos + delimiter.length());
            }
            account_balance = s;
            cout<<date<< "  " <<account_name<< "  " <<account_balance<< endl;

            //Create text file according to the account name
            //Create + Open + Write File
            ofstream outfile (dir + "accounts\\" + account_name);
            outfile << date << ",0," << account_balance << "," << account_balance;
            outfile.close();
        }
    }
    myReadFile.close();

    ///////////////////////////////////////////////////////////// Read transaction
    myReadFile.open(dir + "transaction.txt");
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;

            s = output;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                if (item_count % 2 == 0){
                    date = token;
                }if (item_count % 2 == 1){
                    account_name = token;
                }
                item_count++;
                s.erase(0, pos + delimiter.length());
            }
            account_balance = s;
            cout<<date<< "  " <<account_name<< "  " <<account_balance<< endl;

            //Create text file according to the account name
            //Create + Open + Write File
            ofstream outfile (dir + "accounts\\" + account_name);
            outfile << date << ",0," << account_balance << "," << account_balance;
            outfile.close();
        }
    }
    myReadFile.close();


    //Create + Open + Write File
    ofstream outfile (dir + "accounts\\"+ account_name);
    outfile << "my text here!" << std::endl;
    outfile.close();


    s = "He,Yaluwe,apiawaw";

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        cout << token << endl;
        s.erase(0, pos + delimiter.length());
    }
    cout << s << endl;

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

