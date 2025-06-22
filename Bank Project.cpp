#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include"MyInputLib.h"
#include<algorithm>

using namespace std;

enum enChoice {Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6, Exit = 7};
enum enTransaction {Deposit = 1, Withdraw = 2, Balances = 3, Main = 4};

const string File_Name = "Bank Project.txt";

void Bank();

struct stData {
	string Account_Number = "";
	string Pin_Code = "";
	string Name = "";
	string Phone = "";
	float Balance = 0;
	bool Mark_For_Delete = false;
};

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

string Record_To_Line(stData Client_Data, string delim) {
	string str = "";
	str += Client_Data.Account_Number + delim;
	str += Client_Data.Pin_Code + delim;
	str += Client_Data.Name + delim;
	str += Client_Data.Phone + delim;
	str += to_string(Client_Data.Balance);
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

void Print_Client_Record(stData Client_Data) {
	cout << "\n The Following is the client's details :";
	cout << "\n__________________________________________\n";
	cout << "\n Account Number : " << Client_Data.Account_Number;
	cout << "\n Pin Code : " << Client_Data.Pin_Code;
	cout << "\n Name : " << Client_Data.Name;
	cout << "\n Phone : " << Client_Data.Phone;
	cout << "\n Account Balance : " << Client_Data.Balance;
	cout << "\n__________________________________________\n";
}

void Print_Search_Result(bool found, stData Client, string Account_Number) {
	if (found)
		Print_Client_Record(Client);
	else
		cout << "\n Client with account number (" << Account_Number << ") not found ! \n";
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

void Show_End_Screen() {
	cout << "\n____________________________________\n";
	cout << "\n\tProgram Ends ";
	cout << "\n____________________________________\n";
}

void Show_Clients(vector<stData> vClients) {
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
	cout << "\n____________________________________\n";
	cout << "\n\tDelete Client Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string Account_Number = MyInputLib::Read_Line("\n Enter the account Number You Want to search : ");
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
	cout << "\n____________________________________\n";
	cout << "\n\tFind Client Screen";
	cout << "\n____________________________________\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string Account_Number = MyInputLib::Read_Line("\n Enter the account Number You Want to search : ");
	stData Client;
	bool found = Search_Client_By_Number(vClients,Account_Number, Client);
	Print_Search_Result(found, Client, Account_Number);
}

void Print_Transactions_Screen() {
	cout << "\n===============================================\n";
	cout << "\tTransactions Menu Screen";
	cout << "\n===============================================\n";
	cout << "\t[1] Deposit\n";
	cout << "\t[2] Withdraw\n";
	cout << "\t[3] Total Balances\n";
	cout << "\t[4] Main Menu";
	cout << "\n===============================================\n";
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
		cout << "\n Enter account number for deposit : ";
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
	system("cls");
	vector<stData> vClients = Load_Clients_Data_To_Vector(File_Name);
	switch (trans)
	{
		case (enTransaction::Deposit):
			Balance_Deposit(vClients);
			break;
		case (enTransaction::Withdraw):
			Balance_Withdraw(vClients);
			break;
		case (enTransaction::Balances):
			Total_Balances(vClients);
			break;
		case (enTransaction::Main):
			system("cls");
			Bank();
			break;
		default:
			system("pause");
			system("cls");
			Bank();
			break;
	}
}

void Transaction() {
	short choice = 0;
	choice = MyInputLib::Read_Digit(" Chose what you want to do : ");
	Perform_Transaction((enTransaction)choice);
}

void Perform_Operation(enChoice choice) {
	system("cls");
	vector<stData> vClients = Load_Clients_Data_To_Vector(File_Name);
	switch (choice)
	{
		case (enChoice::Show):
			Show_Clients(vClients);
			break;
		case (enChoice::Add):
			Add_Clients(vClients);
			break;
		case (enChoice::Delete):
			Delete_Client(vClients);
			break;
		case (enChoice::Update):
			Update_Client(vClients);
			break;
		case (enChoice::Find):
			Find_Client(vClients);
			break;
		case (enChoice::Transactions):
			do
			{
				system("cls");
				Print_Transactions_Screen();
				Transaction();
				cout << "\n\n\n Press any key to go back to Transactions Menu...";
				system("pause>0");
			} while (true);
			break;
		case (enChoice::Exit):
			Show_End_Screen();
			exit(1);
			break;
		default:
			break;
	}
}

void Print_Main_Menu() {
	cout << "\n===============================================\n";
	cout << "\t\tMain Menu Screen";
	cout << "\n===============================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Exit";
	cout << "\n===============================================\n";
}

void Bank() {
	short choice = 0;
	Print_Main_Menu();
	choice = MyInputLib::Read_Digit(" Chose what you want to do : ");
	Perform_Operation((enChoice)choice);
	cout << "\n\n\n Press any key to go back to Main Menu...";
}

int main() {
	do
	{
		system("cls");
		Bank();
		system("pause>0");
	} while (true);
	
	return 0;
}