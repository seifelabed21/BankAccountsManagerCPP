#pragma once

#include<iostream>
#include<string>

using namespace std;

namespace MyInputLib
{

    int Read_Number(int& Number)
    {
        cin >> Number;
        while (cin.fail())
        {
            // user didn't input a number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one : ";
            cin >> Number;
        }
        return Number;
    }

    int Read_Positif_Number(string message)
    {
        int number;
        cout << message;
        do
        {
            Read_Number(number);
        } while (number < 0);
        return number;
    }

    int Read_Number_In_Range(int From, int To)
    {
        int number = 0;
        cout << "Enter a number from " << From << " to " << To << " : ";
        do
        {
            Read_Number(number);
        } while (number < From || number > To);
        return number;
    }

    short int Read_Digit(string message) 
    {
        int n = 0;
        do
        {
            cout << message;
            cin >> n;
        } while (!(n >= 0 && n <= 9));
        return n;
    }

    void Read_Array_Of_Int(int T[], int& length) 
    {
        cout << "Enter the array length : ";
        cin >> length;
        cout << "Enter the array elements :" << endl;
        for (int i = 0; i < length; i++)
        {
            cout << "Element [" << i + 1 << "] : ";
            T[i] = Read_Positif_Number("");
        }
    }

    string Read_Line(string message)
    {
        string line = "";
        cout << message;
        getline(cin,line);
        return line;
    }

    string Read_Word(string message)
    {
        string word = "";
        cout << message;
        cin >> word;
        return word;
    }
    
    char Read_Char(string message) {
        char c;
        cout << message;
        cin >> c;
        return c;
    }

}