#pragma once

#include<iostream>
#include<iomanip>

using namespace std;

struct stDate{ 
	short year; 
	short month;
	short day; 
};

struct stPeriod {
	stDate start;
	stDate end;
};

enum enCompDates { Before = -1, Equal = 0, After = 1 };

namespace MyLib
{
	char Invert_Character_Case(char c) {
		if (isupper(c))
			return tolower(c);
		else
			return toupper(c);
	}

	string String_To_Upper(string str) {
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = toupper(str[i]);
		}
		return str;
	}

	string String_To_Lower(string str) {
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = tolower(str[i]);
		}
		return str;
	}

	string To_Upper_First_Letters(string str) {
		bool is_first = true;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ' && is_first)
				str[i] = toupper(str[i]);
			is_first = (str[i] == ' ') ? true : false;
		}
		return str;
	}

	void Print_First_Letters_Of_String(string str) {
		bool is_first_letter = true;
		cout << "\n First letters of this string :\n";
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ' && is_first_letter)
				cout << str[i] << endl;
			is_first_letter = (str[i] == ' ') ? true : false;
		}
		cout << endl;
	}

	bool Check_Palindrome_Matrix(int arr[3][3], int rows, int cols) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols / 2; j++)
			{
				if (arr[i][j] != arr[i][cols - j - 1])
					return false;
			}
		}
		return true;
	}

	int Min_Matrix(int arr[3][3], int rows, int cols) {
		int min = arr[0][0];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (arr[i][j] < min)
					min = arr[i][j];
			}
		}
		return min;
	}

	int Max_Matrix(int arr[3][3], int rows, int cols) {
		int max = arr[0][0];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (arr[i][j] > max)
					max = arr[i][j];
			}
		}
		return max;
	}


	bool Check_Number_Existance_In_Matrix(int arr1[3][3], int rows, int cols, int number) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (arr1[i][j] == number)
					return true;
			}
		}
		return false;
	}

	void Print_Intersected_Numbers(int arr1[3][3], int arr2[3][3], int rows, int cols) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (Check_Number_Existance_In_Matrix(arr2, 3, 3, arr1[i][j]))
					cout << setw(3) << arr1[i][j] << "\t";
			}
		}
	}

	int Count_Number_In_Matrix(int arr1[3][3], int rows, int cols, int number) {
		int counter = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (arr1[i][j] == number)
					counter++;
			}
		}
		return counter;
	}

	bool Check_Sparce_Matrix(int arr1[3][3], int rows, int cols) {
		int Matrix_Size = rows * cols;
		return Count_Number_In_Matrix(arr1, 3, 3, 0) >= (Matrix_Size / 2);
	}

	bool Check_Scalar_Matrix(int arr1[3][3], int rows, int cols) {
		int First_Diag_Element = arr1[0][0];

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// Check if diagonal is first element
				if (i == j && arr1[i][j] != First_Diag_Element)
					return false;
				// Check if non diagonal is 0
				else if (i != j && arr1[i][j] != 0)
					return false;
			}
		}
		return true;
	}

	bool Check_Identity_Matrix(int arr1[3][3], int rows, int cols) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// Check if diagonal is 1
				if (i == j && arr1[i][j] != 1)
					return false;
				// Check if non diagonal is 0
				else if (i != j && arr1[i][j] != 0)
					return false;
			}
		}
		return true;
	}

	bool Check_Matrix_Typical(int arr1[3][3], int arr2[3][3], int rows, int cols) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (arr1[i][j] != arr2[i][j])
					return false;
			}
		}
		return true;
	}

	int Calculate_Sum_Matrix(int arr[3][3], int rows, int cols) {
		int sum = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				sum += arr[i][j];
			}
		}
		return sum;
	}

	bool Check_Matrix_Sum_Equality(int arr1[3][3], int arr2[3][3], int rows, int cols) {
		return Calculate_Sum_Matrix(arr1, rows, cols) == Calculate_Sum_Matrix(arr2, rows, cols);
	}

	stDate GetSystemDate() {
		stDate Date;
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);
		Date.year = now.tm_year + 1900;
		Date.month = now.tm_mon + 1;
		Date.day = now.tm_mday;
		return Date;
	}

	stDate Read_Date() {
		stDate date;
		date.year = MyInputLib::Read_Positif_Number("\n Enter a year : ");
		date.month = MyInputLib::Read_Positif_Number(" Enter a month : ");
		date.day = MyInputLib::Read_Positif_Number(" Enter a day : ");
		cout << endl;
		return date;
	}

	bool Check_Leap_Year(int year) {
		return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
	}

	int Get_Number_Of_Days_In_Year(int year) {
		return Check_Leap_Year(year) ? 365 : 366;
	}

	int Get_Number_Of_Days_In_Month(int month, int year) {
		if ((month < 1 || month > 12))
			return 0;
		int arrNumber_Of_Days[12] = { 31,28,31,30 ,31,30 ,31,31,30,31,30,31 };
		return	(month == 2) ? (Check_Leap_Year(year) ? 29 : 28) : arrNumber_Of_Days[month - 1];
	}

	bool Last_Day_In_Month(stDate date) {
		if (date.day == Get_Number_Of_Days_In_Month(date.month, date.year))
			return true;
		return false;
	}

	bool Last_Month_In_Year(stDate date) {
		return date.month == 12;
	}

	bool Date1_Before_Date2(stDate date1, stDate date2) {
		return (date1.year < date2.year) || (date1.year == date2.year && ((date1.month < date2.month)
			|| (date1.month == date2.month && date1.day <= date2.day)));
	}

	int Calculate_Number_Of_Days_Since_Beginning(stDate date) {
		int result = 0;
		for (int i = 1; i < date.month; i++)
		{
			result += Get_Number_Of_Days_In_Month(i, date.year);
		}
		return result + date.day;
	}

	int Calculate_Difference(stDate date1, stDate date2) {
		int result = 0;
		if (date1.year < date2.year)
		{
			for (int i = date1.year; i < date2.year; i++)
			{
				result += Get_Number_Of_Days_In_Year(i);
			}
		}
		result += Calculate_Number_Of_Days_Since_Beginning(date2) - Calculate_Number_Of_Days_Since_Beginning(date1);
		return result;
	}

	void Add_Day_To_Date(stDate& date) {
		if (Last_Day_In_Month(date))
		{
			if (Last_Month_In_Year(date))
			{
				date.day = 1;
				date.month = 1;
				date.year++;
			}
			else
			{
				date.day = 1;
				date.month++;
			}
		}
		else
		{
			date.day++;
		}
	}

	void Add_Days_To_Date(stDate date, int to_add) {
		int remaining_days = Calculate_Number_Of_Days_Since_Beginning(date) + to_add;
		date.month = 1;
		while (true)
		{
			int days_in_next_month = Get_Number_Of_Days_In_Month(date.month, date.year);
			if (remaining_days > days_in_next_month)
			{
				date.month++;
				remaining_days -= days_in_next_month;
				if (date.month > 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day = remaining_days;
				break;
			}
		}
	}

	void Add_Week_To_Date(stDate& date) {
		Add_Days_To_Date(date, 7);
	}

	void Add_Weeks_To_Date(stDate& date, int nb_weeks) {
		for (int i = 0; i < nb_weeks; i++)
		{
			Add_Week_To_Date(date);
		}
	}

	void Add_Month_To_Date(stDate& date) {
		if (date.month == 12)
			date.month = 1;
		else
			date.month++;
		int nb_days_in_month = Get_Number_Of_Days_In_Month(date.month, date.year);
		if (date.day > nb_days_in_month)
			date.day = nb_days_in_month;
	}

	void Add_Months_To_Date(stDate& date, int nb_months) {
		for (int i = 0; i < nb_months; i++)
		{
			Add_Month_To_Date(date);
		}
	}

	void Add_Year_To_Date(stDate& date) {
		date.year++;
	}

	void Add_Years_To_Date(stDate& date, int nb_years) {
		for (int i = 0; i < nb_years; i++) {
			Add_Year_To_Date(date);
		}
	}

	void Add_Years_To_Date_Faster(stDate& date, int nb_years) {
		date.year += nb_years;
	}

	void Add_Decade_To_Date(stDate& date) {
		Add_Years_To_Date_Faster(date, 10);
	}

	void Add_Decades_To_Date(stDate& date, int nb_decades) {
		for (int i = 0; i < nb_decades; i++)
		{
			Add_Decade_To_Date(date);
		}
	}

	void Add_Decades_To_Date_Faster(stDate& date, int nb_decades) {
		date.year += 10 * nb_decades;
	}

	void Add_Century_To_Date(stDate& date) {
		date.year += 100;
	}

	void Add_Millenium_To_Date(stDate& date) {
		date.year += 1000;
	}

	void Print_Date(stDate date) {
		cout << to_string(date.day) << "/" << to_string(date.month) << "/" << to_string(date.year) << endl;
	}

	int Get_Day_Order(stDate date) {
		int a = 0, m = 0, y = 0;
		a = (14 - date.month) / 12;
		y = date.year - a;
		m = date.month + 12 * a - 2;
		return (date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	string Get_Day_Name(stDate date) {
		string arrDay_Name[7] = { "Sunday", "Monday", "Tuesday","Wednesday","Thursday","Friday","Saturday" };
		return arrDay_Name[Get_Day_Order(date)];
	}

	
	bool Check_Week_End(stDate date) {
		return (Get_Day_Order(date) == 0 || Get_Day_Order(date) == 6);
	}

	bool Check_Business_Day(stDate date) {
		return (!Check_Week_End(date));
	}

	bool Equal_Dates(stDate date1, stDate date2) {
		return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
	}

	bool Date1_After_Date2(stDate date1, stDate date2) {
		return (!MyLib::Date1_Before_Date2(date1, date2) && !(Equal_Dates(date1, date2)));
	}

	enCompDates Compare_Dates(stDate date1, stDate date2) {
		if (MyLib::Date1_Before_Date2(date1, date2))
			return enCompDates::Before;
		else if (MyLib::Equal_Dates(date1, date2))
			return enCompDates::Equal;
		return enCompDates::After;
	}

	stPeriod Read_Period() {
		stPeriod period;
		cout << "\n Enter start date :";
		period.start = MyLib::Read_Date();
		cout << "\n Enter end date :";
		period.end = MyLib::Read_Date();
		return period;
	}

	bool Period_Overlap(stPeriod period1, stPeriod period2) {
		return ((Compare_Dates(period1.end, period2.start) == enCompDates::Before
			|| Compare_Dates(period1.start, period2.end) == enCompDates::After)) ? false : true;
	}

	int Period_Length(stPeriod period) {
		return MyLib::Calculate_Difference(period.start, period.end);
	}

	bool Check_Date_In_Period(stPeriod period, stDate date) {
		return !((MyLib::Compare_Dates(period.start, date) == enCompDates::After)
			|| (MyLib::Compare_Dates(period.end, date) == enCompDates::Before));
	}

	string To_Upper(string str) {
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = toupper(str[i]);
		}
		return str;
	}

	vector<string> Split(string str, string delim) {
		int pos = 0;
		string word = "";
		vector<string> vStrings;
		while ((pos = str.find(delim)) != string::npos)
		{
			word = str.substr(0, pos);
			vStrings.push_back(word);
			str.erase(0, pos + delim.length());
		}
		if (str != "")
			vStrings.push_back(str);
		return vStrings;
	}

	string Join(vector<string> vStrings, string delim) {
		string str = "";
		for (string& s : vStrings)
			str += s + delim;
		return str.substr(0, str.length() - delim.length());
	}

	string Replace(string str, string before, string after, string delim, bool match_case = true) {
		vector<string> vStrings = Split(str, delim);
		for (string& s : vStrings)
		{
			if (match_case && s == before)
				s = after;
			else if (!match_case && To_Upper(s) == To_Upper(before))
				s = after;
		}
		return Join(vStrings, delim);
	}

	string Trim_Left(string str) {
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
				return str.substr(i, str.length() - 1);
		}
		return str;
	}

	string Trim_Right(string str) {
		for (int i = str.length() - 1; i >= 0; i--)
		{
			if (str[i] != ' ')
				return str.substr(0, i + 1);
		}
		return str;
	}



	string Trim(string str) {
		return Trim_Left(Trim_Right(str));
	}

	bool Vowel_Check(char c) {
		const string vowels = "aeiou";
		for (int i = 0; i < vowels.length(); i++)
		{
			if (toupper(vowels[i]) == toupper(c))
				return true;
		}
		return false;
	}

	int Count_Vowels(string str) {
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (Vowel_Check(str[i]))
				counter++;
		}
		return counter;
	}

	int Count_Character_In_String(string str, char c, bool case_sensitive = true) {
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (case_sensitive && str[i] == c)
				counter++;
			else if (!case_sensitive && toupper(str[i]) == toupper(c))
				counter++;
		}
		return counter;
	}


}