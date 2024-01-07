#include<iostream>

#include<fstream>

#include<cctype>

#include<iomanip>

#include<string>

using namespace std;

class account

{

int acno;

string name;

int deposit;

char type;

public:

void create_account();

void show_account() const;

void modify();

void dep(int);

void draw(int);

void report() const;

int retacno() const;

int retdeposit() const;

char rettype() const;

//Overloading insertion operator

friend ofstream& operator<<(ofstream& ofs, const account& acc) {

ofs.write(reinterpret_cast<const char*>(&acc), sizeof(account));

return ofs;

}

// Overloading extraction operator for reading from file

friend ifstream& operator>>(ifstream& ifs, account& acc) {

ifs.read(reinterpret_cast<char*>(&acc), sizeof(account));

return ifs;

}

};

void account::create_account()

{

cout<<"Enter The account No. :"<<endl;

cin>>acno;

cout<<"Enter The Name of The account Holder : "<<endl;

cin.ignore();

cin.getline(cin,name);

cout<<"Enter Type of The account (C/S) : "<<endl;
cin>>type;

type=toupper(type);

cout<<"Enter The Initial amount(>=500 for Saving and >=1000 for current ) :

"<<endl;

cin>>deposit;

cout<<"Account Created.."<<endl;

}

void account::show_account() const

{

cout<<"Account No. : "<<acno<<endl;

cout<<"Account Holder Name : "<<endl;

cout<<name;

cout<<"Type of Account : "<<type<<endl;

cout<<"Balance amount : "<<deposit<<endl;

}

void account::modify()

{

cout<<"Account No. : "<<acno<<endl;

cout<<"Modify Account Holder Name : "<<endl;

cin.ignore();

cin.getline(name,50);

cout<<"Modify Type of Account : "<<endl;

cin>>type;

type=toupper(type);

cout<<"Modify Balance amount : "<<endl;

cin>>deposit;

}

void account::dep(int x)

{

deposit+=x;

}

void account::draw(int x)

{

deposit-=x;

}

void account::report() const

{cout<<acno<<setw(10)<<" "<<name<<setw(10)<<"

"<<type<<setw(6)<<deposit<<endl;

}

int account::retacno() const

{

return acno;

}

int account::retdeposit() const

{

return deposit;

}

char account::rettype() const

{

return type;

}

void write_account();

void display_sp(int);

void modify_account(int);

void delete_account(int);

void display_all();

void deposit_withdraw(int, int);

void intro();

int main()

{

char ch;

int num;

intro(); //Display introductory message

do

{

system("cls"); //Clear the console screen

cout<<"MAIN MENU"<<endl;

cout<<"01. NEW ACCOUNT"<<endl;

cout<<"02. DEPOSIT AMOUNT"<<endl;

cout<<"03. WITHDRAW AMOUNT"<<endl;

cout<<"04. BALANCE ENQUIRY"<<endl;

cout<<"05. ALL ACCOUNT HOLDER LIST"<<endl;
cout<<"06. CLOSE AN ACCOUNT"<<endl;

cout<<"07. MODIFY AN ACCOUNT"<<endl;

cout<<"08. EXIT"<<endl;

cout<<"Select Your Option (1-8) "<<endl;

cin>>ch; //Taking input from user

system("cls");

switch(ch) //Switch case inside do while loop

{

case '1':

write_account();

break;

case '2':

cout<<"Enter The account No. : "<<endl;

cin>>num;

deposit_withdraw(num, 1);

break;

case '3':

cout<<"Enter The account No. : "<<endl;

cin>>num;

deposit_withdraw(num, 2);

break;

case '4':

cout<<"Enter The account No. : "<<endl;

cin>>num;

display_sp(num);

break;

case '5':

display_all();

break;

case '6':

cout<<"Enter The account No. : "<<endl;

cin>>num;

delete_account(num);

break;

case '7':

cout<<"Enter The account No. : "<<endl;

cin>>num;

modify_account(num);

break;

case '8':

cout<<"Thanks for using bank management system"<<endl;

break;

default :cout<<"\a"; //Beep for invalid input

}
cin.ignore(); //Clearing the input buffer

cin.get(); // Wait for the user to press enter before continuing

}while(ch!='8'); // Condition for loop

return 0;

}

void write_account() {

account ac;

ofstream outFile;

outFile.open("account1.dat", ios::binary | ios::app);

ac.create_account();

outFile << ac; // Using overloaded insertion operator

outFile.close();

}

void display_sp(int n) {

account ac;

bool flag = false;

ifstream inFile;

inFile.open("account1.dat", ios::binary);

if (!inFile) {

cout << "File could not be open !! Press any Key...";

return;

}

cout << "\nBALANCE DETAILS\n";

while (inFile >> ac) { // Using overloaded extraction operator

if (ac.retacno() == n) {

ac.show_account();

flag = true;

break; // Exit loop after finding the account

}

}

inFile.close();

if (!flag) {

cout << "Account number does not exist" << endl;

}

}

void modify_account(int n)
{

bool found=false;

account ac;

fstream File;

File.open("account1.dat",ios::binary|ios::in|ios::out);

if(!File)

{

cout<<"File could not be open !! Press any Key...";

return;

}

while(!File.eof() && found==false)

{

File.read(reinterpret_cast<char *> (&ac), sizeof(account));

if(ac.retacno()==n)

{

ac.show_account();

cout<<"\n\nEnter The New Details of account"<<endl;

ac.modify();

int pos=(-1)*static_cast<int>(sizeof(account));

File.seekp(pos,ios::cur);

File.write(reinterpret_cast<char *> (&ac), sizeof(account));

cout<<"\n\n\t Record Updated";

found=true;

}

}

File.close();

if(found==false)

cout<<"\n\n Record Not Found ";

}

void delete_account(int n) {

account ac;

ifstream inFile;

ofstream outFile;

inFile.open("account1.dat", ios::binary);

if (!inFile) {

cout << "File could not be open !! Press any Key...";

return;

}

outFile.open("Temp1.dat", ios::binary);

inFile.seekg(0, ios::beg);

bool found = false;
while (inFile >> ac) { // Using overloaded extraction operator
if (ac.retacno() != n) {
outFile << ac; // Using overloaded insertion operator
} else {
found = true;
}
}
inFile.close();
outFile.close();
if (found) {
remove("account1.dat");
rename("Temp1.dat", "account1.dat");
cout << "\n\n\tRecord Deleted ..";
} else {
remove("Temp1.dat"); // Delete the temporary file if account not found
cout << "\n\n\tAccount not found!";
}
}
void display_all() {
account ac;
ifstream inFile;
inFile.open("account1.dat", ios::binary);
if (!inFile) {
cout << "File could not be open !! Press any Key...";
return;
}
cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
cout << "====================================================\n";
cout << "A/c no. NAME Type Balance\n";
cout << "====================================================\n";
while (inFile >> ac) { // Using overloaded extraction operator
ac.report();
}
inFile.close();
}
//function to deposit and withdraw amounts
void deposit_withdraw(int n, int option) {

int amt;

bool found = false;

account ac;

fstream File;

File.open("account1.dat", ios::binary | ios::in | ios::out);

if (!File) {

cout << "File could not be open !! Press any Key...";

return;

}

while (File.read(reinterpret_cast<char*>(&ac), sizeof(account))) {

if (ac.retacno() == n) {

ac.show_account();

if (option == 1) {

cout << "\n\n\tTO DEPOSIT AMOUNT ";

cout << "\n\nEnter The amount to be deposited: ";

cin >> amt;

ac.dep(amt);

} else if (option == 2) {

cout << "\n\n\tTO WITHDRAW AMOUNT ";

cout << "\n\nEnter The amount to be withdrawn: ";

cin >> amt;

int bal = ac.retdeposit() - amt;

if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C')) {

cout << "Insufficient balance";

} else {

ac.draw(amt);

}

}

int pos = File.tellp() - static_cast<int>(sizeof(ac));

File.seekp(pos, ios::beg);

File.write(reinterpret_cast<char*>(&ac), sizeof(account));

cout << "\n\n\t Record Updated";

found = true;

break; // Exit loop after updating the account

}

}

File.close();

if (!found) {

cout << "\n\n Record Not Found ";

}

}
void intro()

{

cout<<"\n\n\n\t BANK";

cout<<"\n\n\tMANAGEMENT";

cout<<"\n\n\t SYSTEM";

cout<<"\n\n\n\n STUDIED AND MADE BY: ";

cout<<"\n\nGarv Anand";

cin.get();

}
