#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include"MyInputLib.h"
#include"MyLib.h"
#include<algorithm>
#include<cmath>

using namespace std;

enum enChoice {Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6, Users = 7, Logout = 8};
enum enTransaction {Deposit = 1, Withdraw = 2, Balances = 3, Main = 4};
enum enUser {Show_U = 1, Add_U = 2, Delete_U = 3, Update_U = 4, Find_U = 5, Main_U = 6};
enum enPermissions { All = -1, P_Show = 1, P_Add = 2, P_Delete = 4, P_Update = 8, P_Find = 16, P_Trans = 32, P_Users = 64 };

const string File_Name = "Bank Project.txt";
const string Users_File_Name = "Users.txt";

struct stData {
	string Account_Number = "";
	string Pin_Code = "";
	string Name = "";
	string Phone = "";
	float Balance = 0;
	bool Mark_For_Delete = false;
};

struct stUser {
	string username = "";
	string password = "";
	int permissions = 0;
	bool Mark_For_Delete = false;
	
};

stUser Current_User;

void Bank_Menu();
void Back_To_Bank_Menu();
void Back_To_Transactions_Menu();
void Back_To_Users_Menu();
bool Check_Access_Permission(enPermissions perm);
void Print_Access_Denied_Screen();
void Login();

enChoice Read_Bank_Menu_Options() {
	short option;
	option = MyInputLib::Read_Digit("\n Chose what you want to do [1 - 8] : ");
	return (enChoice)option;
}

enTransaction Read_Transactions_Menu_Options() {
	short option;
	option = MyInputLib::Read_Digit(" Chose what you want to do : ");
	return (enTransaction)option;
}

enUser Read_Users_Menu_Options() {
	short mychoice = 1;
	mychoice = MyInputLib::Read_Digit(" Chose what you want to do : ");
	return (enUser)mychoice;
}

vector<string> Line_To_Vector(string line, string delim) {
	vector<string> Client_Data_Vector;
	int pos = 0;
	string word;
	while ((pos = line.find(delim)) != string::npos)
	{
		word = line.substr(0, pos);
		Client_Data_Vector.push_back(word);
		line.erase(0, pos + delim.length());
	}
	if (line != "")
		Client_Data_Vector.push_back(line);
	return Client_Data_Vector;
}

stData Vector_To_Record(vector<string> vClient_Data) {
	stData Client_Data;
	Client_Data.Account_Number = vClient_Data[0];
	Client_Data.Pin_Code = vClient_Data[1];
	Client_Data.Name = vClient_Data[2];
	Client_Data.Phone = vClient_Data[3];
	Client_Data.Balance = stof(vClient_Data[4]);
	return Client_Data;
}

stUser User_Vector_To_Record(vector<string> vUser) {
	stUser user;
	user.username = vUser[0];
	user.password = vUser[1];
	user.permissions = stoi(vUser[2]);
	return user;
}

string Record_To_Line(stData Client_Data, string delim) {
	string str = "";
	str += Client_Data.Account_Number + delim;
	str += Client_Data.Pin_Code + delim;
	str += Client_Data.Name + delim;
	str += Client_Data.Phone + delim;
	str += to_string(Client_Data.Balance);
	return str;
}

string User_Record_To_Line(stUser user, string delim) {
	string str = "";
	str += user.username + delim;
	str += user.password + delim;
	str += to_string(user.permissions);
	return str;
}

vector<stData> Load_Clients_Data_To_Vector(string file_name) {
	fstream Myfile;
	vector<stData> vClients;
	Myfile.open(file_name, ios::in);
	if (Myfile.is_open())
	{
		string Line = "";
		stData Client_Data;
		while (getline(Myfile >> ws, Line))
		{
			Client_Data = Vector_To_Record(Line_To_Vector(Line, "#//#"));
			vClients.push_back(Client_Data);
		}
		Myfile.close();
	}
	return vClients;
}

vector<stUser> Load_Users_Data_To_Vector(string file_name) {
	vector<stUser> vUsers;
	fstream Myfile;
	Myfile.open(file_name, ios::in);

	if (Myfile.is_open())
	{
		string Line = "";
		stUser user;
		while (getline(Myfile >> ws, Line))
		{
			user = User_Vector_To_Record(Line_To_Vector(Line, "#//#"));
			vUsers.push_back(user);
		}
		Myfile.close();
	}
	return vUsers;
}

void Save_Clients_Data_To_File(vector<stData>& vClients, string file_name) {
	fstream Myfile;
	Myfile.open(file_name, ios::out);
	if (Myfile.is_open())
	{
		for (stData& Client : vClients)
		{
			if (Client.Mark_For_Delete == false)
				Myfile << Record_To_Line(Client, "#//#") << endl;
		}
		Myfile.close();
	}
}

void Save_Users_Data_To_File(vector<stUser>& vUsers, string file_name) {
	fstream Myfile;
	Myfile.open(file_name, ios::out);
	if (Myfile.is_open())
	{
		for (stUser& u : vUsers)
		{
			if (u.Mark_For_Delete == false)
				Myfile << User_Record_To_Line(u, "#//#") << endl;
		}
		Myfile.close();
	}
}

void Read_Data(stData& Client_Data) {
	cout << "\n Enter Pin Code : ";
	Client_Data.Pin_Code = MyInputLib::Read_Word("");
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Client_Data.Name = MyInputLib::Read_Line("\n Enter Name : ");
	cout << "\n Enter Phone : ";
	Client_Data.Phone = MyInputLib::Read_Word("");
	cout << "\n Enter Account Balance : ";
	Client_Data.Balance = (float)MyInputLib::Read_Positif_Number("");
}

void Read_User_Permissions(stUser& user) {
	char choice = 'y';
	cout << "\n Do you want to give access to : \n";
	cout << "\n Show Clients List : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Show : 0);
	cout << "\n Add New Clients : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Add : 0);
	cout << "\n Delete Clients : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Delete : 0);
	cout << "\n Update Clients : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Update : 0);
	cout << "\n Find Client : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Find : 0);
	cout << "\n Transactions : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Trans : 0);
	cout << "\n Manage Users : ";
	cin >> choice;
	user.permissions += ((choice == 'y' || choice == 'Y') ? enPermissions::P_Users : 0);
}

void Add_Data_Line_To_File(string File_Name, string Line) {
	fstream Myfile;
	Myfile.open(File_Name, ios::app | ios::out);

	if (Line != "")
	{
		Myfile << Line << endl;

	}
	Myfile.close();
}

bool Search_Client_By_Number(vector<stData> vClients, string Account_Number, stData& Client) {
	for (stData Client_Data : vClients)
	{
		if (Client_Data.Account_Number == Account_Number)
		{
			Client = Client_Data;
			return true;
		}
	}
	return false;
}

bool Mark_Client_For_Delete(vector<stData>& vClients, string Account_Number) {
	for (stData& Client : vClients)
	{
		if (Client.Account_Number == Account_Number)
		{
			Client.Mark_For_Delete = true;
			return true;
		}
	}
	return false;
}

bool Mark_User_For_Delete(vector<stUser>& vUsers, stUser user) {
	for (stUser& u : vUsers)
	{
		if (u.username == user.username)
		{
			u.Mark_For_Delete = true;
			return true;
		}
	}
	return false;
}

void Print_Client_Record(stData Client_Data) {
	cout << "\n The Following is the client's details :";
	cout << "\n__________________________________________\n";
	cout << "\n Account Number  : " << Client_Data.Account_Number;
	cout << "\n Pin Code        : " << Client_Data.Pin_Code;
	cout << "\n Name            : " << Client_Data.Name;
	cout << "\n Phone           : " << Client_Data.Phone;
	cout << "\n Account Balance : " << Client_Data.Balance;
	cout << "\n__________________________________________\n";
}

void Print_User_Record(stUser user) {
	cout << "\n The Following is the user's details :";
	cout << "\n__________________________________________\n";
	cout << "\n Username    : " << user.username;
	cout << "\n Password    : " << user.password;
	cout << "\n Permissions : " << user.permissions;
	cout << "\n__________________________________________\n";
}

void Print_Search_Result(bool found, stData Client, string Account_Number) {
	if (found)
		Print_Client_Record(Client);
	else
		cout << "\n Client with account number (" << Account_Number << ") not found ! \n";
}

void Print_Search_Result(bool found, stUser user) {
	if (found)
		Print_User_Record(user);
	else
		cout << "\n User with username (" << user.username << ") not found ! \n";
}

void Update_Client_In_Vector(vector<stData>& vClients, string Account_Number, string file_name) {
	fstream Myfile;
	Myfile.open(file_name, ios::out);
	if (Myfile.is_open())
	{
		for (stData& Client : vClients)
		{
			if (Client.Account_Number == Account_Number)
			{
				cout << "\n Enter Pin Code : ";
				Client.Pin_Code = MyInputLib::Read_Word("");
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				Client.Name = MyInputLib::Read_Line("\n Enter Name : ");
				cout << "\n Enter Phone : ";
				Client.Phone = MyInputLib::Read_Word("");
				cout << "\n Enter Account Balance : ";
				Client.Balance = (float)MyInputLib::Read_Positif_Number("");
				break;
			}
		}
		Myfile.close();
	}
}

void Update_User_In_Vector(vector<stUser>& vUsers, stUser user, string file_name) {
	fstream Myfile;
	Myfile.open(file_name, ios::out);
	if (Myfile.is_open())
	{
		for (stUser& u : vUsers)
		{
			if (u.username == user.username)
			{
				char choice = 'y';
				cout << "\n Enter Password : ";
				user.password = MyInputLib::Read_Word("");
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n Do you want to give full access (Y/N) : ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
					u.permissions = -1;
				else
					Read_User_Permissions(u);
				break;
			}
		}
		Myfile.close();
	}
}

void Show_End_Screen() {
	cout << "\n____________________________________\n";
	cout << "\n\tProgram Ends ";
	cout << "\n____________________________________\n";
}

void Show_Clients(vector<stData> vClients) {

	if (!Check_Access_Permission(enPermissions::P_Show))
	{
		Print_Access_Denied_Screen();
		return;
	}

	cout << "\n                           Client List (" << vClients.size() << ") Client(s)\n";
	cout << "_______________________________________________________________________________________\n";
	cout << "\n| Account Number  | Pin Code  | Client Name                   | Phone    | Balance   \n";
	cout << "_______________________________________________________________________________________\n";
	for (stData Client_Data : vClients)
	{
		cout << "\n| " << setw(16) << left << Client_Data.Account_Number;
		cout << "| " << setw(10) << left << Client_Data.Pin_Code;
		cout << "| " << setw(30) << left << Client_Data.Name;
		cout << "| " << setw(9) << left << Client_Data.Phone;
		cout << "| " << setw(8) << left << Client_Data.Balance;
	}
	cout << "\n_______________________________________________________________________________________\n";
}

void Add_Clients(vector<stData>& vClients) {

	if (!Check_Access_Permission(enPermissions::P_Add))
	{
		Print_Access_Denied_Screen();
		return;
	}

	char choice = 'y';
	do
	{
		cout << "\n____________________________________\n";
		cout << "\n\tAdd Client Screen";
		cout << "\n____________________________________\n";
		cout << "\n Adding New Client : \n";
		cout << "\n Enter Account Number : ";
		string Account_Number = "";
		getline(cin >> ws, Account_Number);
		stData Client;
		if (Search_Client_By_Number(vClients, Account_Number, Client))
		{
			cout << "\n Client with Account Number (" << Account_Number << ") Already Exists ! \n";
		}
		else
		{
			stData Client_Data;
			Client_Data.Account_Number = Account_Number;
			Read_Data(Client_Data);
			string Line = Record_To_Line(Client_Data, "#//#");
			Add_Data_Line_To_File(File_Name, Line);
			vClients = Load_Clients_Data_To_Vector(File_Name);
			cout << "\n Client Added Successfully, do you want to add more clients (Y/N) : ";
		}
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}

void Delete_Client(vector<stData>& vClients) {

	if (!Check_Access_Permission(enPermissions::P_Delete))
	{
		Print_Access_Denied_Screen();
		return;
	}

	cout << "\n____________________________________\n";
	cout << "\n\tDelete Client Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string Account_Number = MyInputLib::Read_Line("\n Enter the account Number You Want to delete : ");
	stData Client;
	bool found = Search_Client_By_Number(vClients, Account_Number, Client);
	Print_Search_Result(found, Client, Account_Number);
	if (found)
	{
		char choice = 'y';
		cout << "\n Are you sure you wanna delete this client (Y/N) : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			Mark_Client_For_Delete(vClients, Account_Number);
			Save_Clients_Data_To_File(vClients, File_Name);

			vClients = Load_Clients_Data_To_Vector(File_Name);

			cout << "\n Client Successfully deleted ! ";
		}
		else
			return;
	}
}

void Update_Client(vector<stData>& vClients) {

	if (!Check_Access_Permission(enPermissions::P_Update))
	{
		Print_Access_Denied_Screen();
		return;
	}

	cout << "\n____________________________________\n";
	cout << "\n\tUpdate Client Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string Account_Number = MyInputLib::Read_Line("\n Enter the account Number You Want to search : ");
	stData Client;
	bool found = Search_Client_By_Number(vClients, Account_Number, Client);
	Print_Search_Result(found, Client, Account_Number);
	if (found)
	{
		char choice = 'y';
		cout << "\n Are you sure you wanna update this client (Y/N) : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			Update_Client_In_Vector(vClients, Account_Number, File_Name);
			Save_Clients_Data_To_File(vClients, File_Name);

			cout << "\n Client Successfully Updated ! ";
		}
		else
			return;
	}
}

void Find_Client(vector<stData> vClients) {

	if (!Check_Access_Permission(enPermissions::P_Find))
	{
		Print_Access_Denied_Screen();
		return;
	}

	cout << "\n____________________________________\n";
	cout << "\n\tFind Client Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string Account_Number = MyInputLib::Read_Line("\n Enter the account Number You Want to search : ");
	stData Client;
	bool found = Search_Client_By_Number(vClients,Account_Number, Client);
	Print_Search_Result(found, Client, Account_Number);
}

void Total_Balances(vector<stData> vClients) {
	float Total_Balances = 0;
	cout << "\n                           Client List (" << vClients.size() << ") Client(s)\n";
	cout << "_______________________________________________________________________________________\n";
	cout << "\n| Account Number  | Client Name			  | Balance   \n";
	cout << "_______________________________________________________________________________________\n";
	for (stData Client_Data : vClients)
	{
		cout << "\n| " << setw(16) << left << Client_Data.Account_Number;
		cout << "| " << setw(30) << left << Client_Data.Name;
		cout << "| " << setw(17) << left << Client_Data.Balance;
		Total_Balances += Client_Data.Balance;
	}
	cout << "\n_______________________________________________________________________________________\n";
	cout << "\n\t\t\tTotal Balances = " << Total_Balances;
}

void Deposit_Balance_To_Client(vector<stData>& vClients, string Account_Number, float deposit) {
	for (stData& Client : vClients)
	{
		if (Client.Account_Number == Account_Number)
		{
			char choice = 'y';
			cout << "\n Are you sure you want to perform this transaction (Y/N) : ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				Client.Balance += deposit;
				cout << "\n Done Successfully, new account balance = " << Client.Balance;
				Save_Clients_Data_To_File(vClients, File_Name);
				break;
			}
			else
				break;
		}
	}
}

void Balance_Deposit(vector<stData>& vClients) {
	cout << "\n____________________________________\n";
	cout << "\n\tDeposit Screen";
	cout << "\n____________________________________\n";
	string Account_Number = "";
	stData Client;
	do
	{
		cout << "\n Enter account number for deposit : ";
		cin >> Account_Number;
		if (Search_Client_By_Number(vClients, Account_Number, Client))
			break;
		cout << "\n Client with account number (" << Account_Number << ") doesn't exist !\n";
	} while (true);

	Print_Client_Record(Client);
	float deposit = 0;
	cout << "\n Enter deposit amount : ";
	cin >> deposit;
	Deposit_Balance_To_Client(vClients, Account_Number, deposit);
}

void Balance_Withdraw(vector<stData>& vClients) {
	cout << "\n____________________________________\n";
	cout << "\n\tWithdraw Screen";
	cout << "\n____________________________________\n";
	string Account_Number = "";
	stData Client;
	do
	{
		cout << "\n Enter account number for withdrawal : ";
		cin >> Account_Number;
		if (Search_Client_By_Number(vClients, Account_Number, Client))
			break;
		cout << "\n Client with account number (" << Account_Number << ") doesn't exist !\n";
	} while (true);

	Print_Client_Record(Client);
	float withdraw = 0;
	cout << "\n Enter withdraw amount : ";
	cin >> withdraw;
	for (stData& Client : vClients)
	{
		if (Client.Account_Number == Account_Number)
		{
			if (Client.Balance < withdraw)
			{
				cout << "\n Amount Exceeds the balance, you can withdraw up to : " << Client.Balance << endl;
			}
			else
			{
				char choice = 'y';
				cout << "\n Are you sure you want to perform this transaction (Y/N) : ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
				{
					Client.Balance -= withdraw;
					cout << "\n New account balance = " << Client.Balance;
					break;
				}
				else
					break;
			}
		}
	}
	Save_Clients_Data_To_File(vClients, File_Name);
}

void Perform_Transaction(enTransaction trans) {
	vector<stData> vClients = Load_Clients_Data_To_Vector(File_Name);
	switch (trans)
	{
		case (enTransaction::Deposit):
			system("cls");
			Balance_Deposit(vClients);
			Back_To_Transactions_Menu();
			break;
		case (enTransaction::Withdraw):
			system("cls");
			Balance_Withdraw(vClients);
			Back_To_Transactions_Menu();
			break;
		case (enTransaction::Balances):
			system("cls");
			Total_Balances(vClients);
			Back_To_Transactions_Menu();
			break;
		case (enTransaction::Main):
			system("cls");
			Back_To_Bank_Menu();
			break;
		default:
			system("cls");
			Back_To_Bank_Menu();
			break;
	}
}

void Transactions_Menu() {

	if (!Check_Access_Permission(enPermissions::P_Trans))
	{
		Print_Access_Denied_Screen();
		Back_To_Bank_Menu();
		return;
	}

	system("cls");
	cout << "\n===============================================\n";
	cout << "\tTransactions Menu Screen";
	cout << "\n===============================================\n";
	cout << "\t[1] Deposit\n";
	cout << "\t[2] Withdraw\n";
	cout << "\t[3] Total Balances\n";
	cout << "\t[4] Main Menu";
	cout << "\n===============================================\n";
	Perform_Transaction(Read_Transactions_Menu_Options());
}

bool Search_And_Load_User(vector<stUser> vUsers, stUser user, stUser& current_user) {
	for (stUser& u : vUsers)
	{
		if (u.username == user.username && u.password == user.password)
		{
			current_user = u;
			return true;
		}
	}
	return false;
}

bool Search_User(vector<stUser>& vUsers, stUser& user) {
	for (stUser& u : vUsers)
	{
		if (u.username == user.username)
		{
			user = u;
			return true;
		}
	}
	return false;
}

void Show_Users(vector<stUser> vUsers) {
	cout << "\n                           Users List (" << vUsers.size() << ") Client(s)\n";
	cout << "_______________________________________________________________________________________\n";
	cout << "\n| Username  | Password  | Permissions\n";
	cout << "_______________________________________________________________________________________\n";
	for (stUser user : vUsers)
	{
		cout << "\n| " << setw(10) << left << user.username;
		cout << "| " << setw(10) << left << user.password;
		cout << "| " << setw(25) << left << user.permissions;
	}
	cout << "\n_______________________________________________________________________________________\n";
}

void Add_User(vector<stUser>& vUsers) {
	char choice = 'y';
	do
	{
		stUser user;
		cout << "\n Enter username : ";
		getline(cin >> ws, user.username);
		while (Search_User(vUsers, user))
		{
			cout << "\n User with username (" << user.username << ") Already Exists ! Enter another : ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin >> ws, user.username);
		}
		cout << "\n Enter password : ";
		getline(cin, user.password);
		cout << "\n Do you want to give full access (Y/N) : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			user.permissions = -1;
		}
		else
		{
			Read_User_Permissions(user);
		}
		string Line = User_Record_To_Line(user, "#//#");
		Add_Data_Line_To_File(Users_File_Name, Line);
		vUsers = Load_Users_Data_To_Vector(Users_File_Name);
		cout << "\n User Added Successfully, do you want to add more users (Y/N) : ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}

void Add_User_Menu(vector<stUser>& vUsers) {
	cout << "\n____________________________________\n";
	cout << "\n\tAdd User Screen";
	cout << "\n____________________________________\n";
	cout << "\n Adding New User : \n";
	Add_User(vUsers);
}

void Delete_User(vector<stUser>& vUsers) {
	cout << "\n____________________________________\n";
	cout << "\n\tDelete User Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	stUser user;
	user.username = MyInputLib::Read_Line("\n Enter the username you want to delete: ");
	bool found = Search_User(vUsers, user); // Now loads full user

	Print_Search_Result(found, user);

	if (found)
	{
		char choice = 'y';
		cout << "\n Are you sure you want to delete this user (Y/N) : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			Mark_User_For_Delete(vUsers, user);
			Save_Users_Data_To_File(vUsers, Users_File_Name);

			vUsers = Load_Users_Data_To_Vector(Users_File_Name);
			cout << "\n User Successfully deleted!";
		}
	}
}

void Update_User(vector<stUser>& vUsers) {
	cout << "\n____________________________________\n";
	cout << "\n\tUpdate User Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	stUser user;
	user.username = MyInputLib::Read_Line("\n Enter the username You Want to search : ");
	bool found = Search_User(vUsers, user);
	Print_Search_Result(found, user);
	if (found)
	{
		char choice = 'y';
		cout << "\n Are you sure you wanna update this user (Y/N) : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			Update_User_In_Vector(vUsers, user, Users_File_Name);
			Save_Users_Data_To_File(vUsers, Users_File_Name);

			cout << "\n User Successfully Updated ! ";
		}
		else
			return;
	}
}

void Find_User(vector<stUser> vUsers) {
	cout << "\n____________________________________\n";
	cout << "\n\tFind User Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	stUser user;
	user.username = MyInputLib::Read_Line("\n Enter the username You Want to search : ");
	bool found = Search_User(vUsers, user);
	Print_Search_Result(found, user);
}

bool Check_Access_Permission(enPermissions perm) {
	return (Current_User.permissions == enPermissions::All ||
		(perm & Current_User.permissions) == perm);
}

void Print_Access_Denied_Screen() {
	cout << "\n____________________________________________________\n";
	cout << "\n\tAccess Denied !";
	cout << "\n\tYou don't have permission to do this !";
	cout << "\n\tPlease contact your admin !";
	cout << "\n____________________________________________________\n";
}

void Perform_User(enUser choice) {
	vector<stUser> vUsers = Load_Users_Data_To_Vector(Users_File_Name);
	switch (choice)
	{
		case enUser::Show_U:
			system("cls");
			Show_Users(vUsers);
			Back_To_Users_Menu();
			break;
		case enUser::Add_U:
			system("cls");
			Add_User_Menu(vUsers);
			Back_To_Users_Menu();
			break;
		case enUser::Delete_U:
			system("cls");
			Delete_User(vUsers);
			Back_To_Users_Menu();
			break;
		case enUser::Update_U:
			system("cls");
			Update_User(vUsers);
			Back_To_Users_Menu();
			break;
		case enUser::Find_U:
			system("cls");
			Find_User(vUsers);
			Back_To_Users_Menu();
			break;
		case enUser::Main_U:
			system("cls");
			Back_To_Bank_Menu();
			break;
		default:
			system("cls");
			Back_To_Bank_Menu();
			break;
	}
}

void Users_Menu() {

	if (!Check_Access_Permission(enPermissions::P_Users))
	{
		Print_Access_Denied_Screen();
		Back_To_Bank_Menu();
		return;
	}

	system("cls");
	cout << "\n===============================================\n";
	cout << "\tManage Users Menu Screen";
	cout << "\n===============================================\n";
	cout << "\t[1] List Users\n";
	cout << "\t[2] Add New User\n";
	cout << "\t[3] Delete User\n";
	cout << "\t[4] Update User\n";
	cout << "\t[5] Find User\n";
	cout << "\t[6] Main Menu";
	cout << "\n===============================================\n";
	Perform_User(Read_Users_Menu_Options());
}

void Perform_Operation(enChoice choice) {
	vector<stData> vClients = Load_Clients_Data_To_Vector(File_Name);
	switch (choice)
	{
		case (enChoice::Show):
			system("cls");
			Show_Clients(vClients);
			Back_To_Bank_Menu();
			break;
		case (enChoice::Add):
			system("cls");
			Add_Clients(vClients);
			Back_To_Bank_Menu();
			break;
		case (enChoice::Delete):
			system("cls");
			Delete_Client(vClients);
			Back_To_Bank_Menu();
			break;
		case (enChoice::Update):
			system("cls");
			Update_Client(vClients);
			Back_To_Bank_Menu();
			break;
		case (enChoice::Find):
			system("cls");
			Find_Client(vClients);
			Back_To_Bank_Menu();
			break;
		case (enChoice::Transactions):
			system("cls");
			Transactions_Menu();
			break;
		case (enChoice::Users):
			system("cls");
			Users_Menu();
			break;
		case (enChoice::Logout):
			system("cls");
			//Show_End_Screen();
			//exit(1);
			Login();
			break;
		default:
			Login();
			break;
	}
}

void Back_To_Bank_Menu() {
	cout << "\n\n\n Press any key to go back to Main Menu...";
	system("pause>0");
	Bank_Menu();
}

void Back_To_Transactions_Menu() {
	cout << "\n\n\n Press any key to go back to Transactions Menu...";
	system("pause>0");
	Transactions_Menu();
}

void Back_To_Users_Menu() {
	cout << "\n\n\n Press any key to go back to Users Menu...";
	system("pause>0");
	Users_Menu();
}

void Bank_Menu() {
	system("cls");
	cout << "\n===============================================\n";
	cout << "\t\tMain Menu Screen";
	cout << "\n===============================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Manage Users\n";
	cout << "\t[8] Logout";
	cout << "\n===============================================\n";
	Perform_Operation(Read_Bank_Menu_Options());
}

void Login() {
	vector<stUser> vUsers = Load_Users_Data_To_Vector(Users_File_Name);
	stUser user;
	bool login_fail = false;
	do 
	{
		system("cls");
		cout << "\n____________________________________\n";
		cout << "\n\t   Login Screen";
		cout << "\n____________________________________\n";
		if (login_fail)
			cout << " \n Invalid Username/Password ! \n";
		cout << "\n Enter username : ";
		cin >> user.username;
		cout << " Enter password : ";
		cin >> user.password;
		login_fail = !Search_And_Load_User(vUsers, user, Current_User);
	} while (login_fail);
	Bank_Menu();
	}

int main() {
	Login();
	return 0;
}