#include <iostream>
#include <io.h>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include<bits/stdc++.h>
#include <iomanip>

using namespace std;

void pres (size_t const p = 2){
    cout<< setprecision(p) <<fixed;
}

double stodpres(string const &str, size_t const p = 2) {
    stringstream sstrm;
    sstrm <<  str << endl;

    double d;
    sstrm >> d;

    double o2;

    if ( d < 2147483){
        int o1 = d *1000;
        o2 = o1 / 1000.0;
    }
    else{
        int o1 = d *100;
        o2 = o1 / 100.0;
    }

    cout<< setprecision(p) <<fixed ;
    return o2;
}

string to_string_pres(double num,  size_t const p = 2){
    ostringstream streamObj;
    streamObj << std::fixed << std::setprecision(p);
    streamObj << num;
    return streamObj.str();
}

void Chargers(vector <pair<string,string>> &account_number_list , string &dir, string &date, double &bank_Balance){

    ifstream myReadFile;
    string transaction_type = "4";

    for (int i=0; i < account_number_list.size(); i++){
        cout<<"\t"<<i<<"  " << account_number_list[i].first << "  "<< account_number_list[i].second<<endl;
        string account_number = account_number_list[i].first;

        string transaction_amount;
        double account_balance = stodpres(account_number_list[i].second);

        if (account_balance < 1000) {
            if (0 < account_balance && account_balance < 1000) {
                //Perform transaction
                account_balance -= 10;
                bank_Balance += 10;
                transaction_amount = "-10";
            } else if (account_balance < 0) {
                account_balance -= 50;
                bank_Balance += 50;
                transaction_amount = "-50";
            }
            account_number_list[i].second = to_string_pres(account_balance);

            //User Accounts
            myReadFile.open(dir + "transaction.txt");
            //Create text file according to the account name
            //Create + Open + Write File
            ofstream accounts(dir + "accounts\\" + account_number, ios_base::app);
            accounts << to_string(stoi(date)-1) << "," << transaction_type << "," << transaction_amount << "," <<
                     to_string_pres(account_balance) << endl;
            accounts.close();

            cout << to_string(stoi(date)-1) << "  " << account_number << "  " << transaction_type << "  " << account_balance << endl;

            ////bankVault
            ofstream bankVault(dir + "bankVault.txt", ios_base::app);
            bankVault << to_string(stoi(date)-1) << "," << transaction_type << ","
                      << transaction_amount << "," << to_string_pres(bank_Balance) << endl;
            bankVault.close();

        }
    }
}

void Interests(vector <pair<string,string>> &account_number_list, string &dir, string &date, double bank_Balance){

    ifstream myReadFile;
    string transaction_type = "4";

    for (int i=0; i < account_number_list.size(); i++){
        cout<<"\t"<<i<<"  " << account_number_list[i].first << "  "<< account_number_list[i].second<<endl;
        string account_number = account_number_list[i].first;

        string transaction_amount;
        double transaction = 0;
        double account_balance = stodpres(account_number_list[i].second);

        if (0 < account_balance){
            //Perform transaction
            transaction = account_balance * 0.02 / 100;
            transaction_amount = to_string_pres(transaction);
            cout << endl<< "\t" <<transaction<<endl;
            account_balance += transaction;
            bank_Balance -= transaction;

            account_number_list[i].second = to_string_pres(account_balance);

            //User Accounts
            myReadFile.open(dir + "transaction.txt");
            //Create text file according to the account name
            //Create + Open + Write File
            ofstream accounts (dir + "accounts\\" + account_number,ios_base::app);
            accounts << date << "," << transaction_type << "," << transaction_amount << "," <<
                     to_string_pres(account_balance) << endl;
            accounts.close();

            cout << date << "  " << account_number << "  " << transaction_type << "  " << account_balance << endl;

            ////bankVault
            ofstream bankVault (dir + "bankVault.txt",ios_base::app);
            bankVault << date << "," << transaction_type << ","
                      << transaction_amount << "," << to_string_pres(bank_Balance) <<endl;
            bankVault.close();

        }
    }
}

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
    string old_date = "20210100";
    string transaction_amount;
    string transaction_type;
    int position = 0;


    //Keep Account Balances in a vector to avoid read files again and again
    vector <pair<string,string>> account_number_list;
    //vector <string> account_balance_list;

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
    double bank_Balance = 0;
    double account_balance = 0;

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

            account_number_list.push_back(make_pair(account_number,transaction_amount));
        }

        ////bankVault
        ofstream bankVault (dir + "bankVault.txt",ios_base::app);
        bankVault << date << ",0," << to_string_pres(bank_Balance) << "," << to_string_pres(bank_Balance) <<endl;
        bankVault.close();
    }
    myReadFile.close();

   // cout<<endl<<endl;
   // cout << to_string_pres(4004345.88 - 500);
    //cout<<endl<<endl;

    ///////////////////////////////////////////////////////////// Read transaction
////////////////////////////////////////////////////////////
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

            //Find the position of the account number in Vector
            for (int i=0; i < account_number_list.size(); i++){
                if (account_number_list[i].first == account_number){
                    account_balance = stodpres(account_number_list[i].second);
                    position = i;
                }
            }

            cout << date << "  " << account_number << "  " << transaction_type << "  " <<
                 transaction_amount << "  " << account_balance << endl ;

            //Check beginning of the date
            if (stodpres(date) == stodpres(old_date) + 1){
                cout<<endl<<"Here  = "<< old_date << " "<<date<<endl;
                //End of the day Detected
                cout<<endl;
                Chargers(account_number_list,dir,date,bank_Balance);
                Interests(account_number_list,dir,date,bank_Balance);
            }
            else{
                int gap = stodpres(date) - stodpres(old_date);
                if (gap!=0){
                    cout<< "\t\tGap" <<  gap <<endl<<endl;
                    for (int j=0; j< gap; j++){
                        cout<<endl;
                        string old_date_cal = to_string(stoi(old_date)+1);
                        Chargers(account_number_list,dir,old_date_cal,bank_Balance);
                        Interests(account_number_list,dir,old_date_cal,bank_Balance);
                        cout<< "old date = " <<old_date<<endl<<endl;
                        old_date = old_date_cal;
                    }
                }
            }
            /*else {
                bool flag = 1;
                while (flag){
                    if (stodpres(date) == stodpres(old_date) + 1){
                        flag=0;
                    }

                    cout<<endl;
                    Chargers(account_number_list,dir,date,bank_Balance);
                    Interests(account_number_list,dir,date,bank_Balance);
                    cout<<endl<< "\t date  = "<<old_date <<endl;
                    old_date = to_string(stoi(old_date) + 1);

                    cout<<endl<< " \tdate  = "<<old_date <<endl;
                    cout<<endl<< " \tReal date  = "<<date <<endl;
                }
            }*/

            if (stoi(transaction_type) == 1){ //Deposit
                //need to read the Balance from account
                account_balance += stodpres(transaction_amount);
                bank_Balance -= stodpres(transaction_amount);
                account_number_list[position].second = to_string_pres(account_balance);
            }
            else {
                account_balance -= stodpres(transaction_amount);
                bank_Balance += stodpres(transaction_amount);
                account_number_list[position].second = to_string_pres(account_balance);
            }
            cout << date << "  " << account_number << "  " << transaction_type << "  " <<
                 transaction_amount << "  " << account_balance << endl <<endl;

            //Create text file according to the account name
            //Create + Open + Write File
            ofstream accounts (dir + "accounts\\" + account_number,ios_base::app);
            accounts << date << "," << transaction_type << "," << transaction_amount << "," <<
                     to_string_pres(account_balance) << endl;
            accounts.close();
            //cout << date << "  " << account_number << "  " << transaction_type << "  " << account_balance << endl;

            ////bankVault
            ofstream bankVault (dir + "bankVault.txt",ios_base::app);
            bankVault << date << "," << transaction_type << ","
                << transaction_amount << "," << to_string_pres(bank_Balance) <<endl;
            bankVault.close();

            //Check end of the date
            old_date = date;
        }
    }
    myReadFile.close();


    //Create + Open + Write File
    //ofstream outfile (dir + "accounts\\" + account_number);
    //outfile << "my text here!" << std::endl;
    //outfile.close();


    s = "He,Yaluwe,apiawaw\n";

    /*
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        cout << token << endl;
        s.erase(0, pos + delimiter.length());
    }
    cout << s << endl;*/


    for (auto & i : account_number_list) {
        cout <<  stodpres(i.first) << " ";
    }
    cout<<endl;
    for (auto & i : account_number_list) {
        cout << stodpres(i.second) << " ";
    }

    cout<<endl<<endl;

    /*
    double f =3.14159123;
    std::cout << std::setprecision(5) << f << '\n';
    std::cout << std::setprecision(9) << f << '\n';
    std::cout << std::setprecision(10) << f << '\n';
    std::cout << std::setprecision(19) << f << "\n\n";

    string test = "795675.12345";

    double k = stodpres(test, 2);


    cout<<"k = " << k <<endl;
    k+=5.124;
    cout<< setprecision(2) <<fixed;
    cout<<"k = " << k <<endl;
    k-=5.124;
    k+=5.128;
    cout<<"k = " << k <<endl;
    */

    /*find(account_number_list.begin(), account_number_list.end(), [&](pair<string,string> const & ref) {
        return ref.first == account_number;
    });*/

    //cout<<account_number_list[9].first<<endl<<account_number;
    //cout<<endl<<endl;
/*
    string bal;

    for (int i=0; i < account_number_list.size(); i++){
        if (account_number_list[i].first == account_number){
            setprecision(30);
            cout<<i<<endl;
            //account_balance = stod(account_number_list[i].second);
            bal = account_number_list[i].second;
            //cout<< account_balance <<endl;
            cout<< stold(bal) <<endl;
        }
    }*/

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

