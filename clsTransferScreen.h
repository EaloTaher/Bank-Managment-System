#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber(string Prompt)
    {
        string AccountNumber = "";
        cout << "\n" << Prompt;
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Screen");

        string SourceAccountNumber = _ReadAccountNumber("Please enter Source AccountNumber? ");

        while (!clsBankClient::IsClientExist(SourceAccountNumber))
        {
            cout << "\nClient with [" << SourceAccountNumber << "] does not exist.\n";
            SourceAccountNumber = _ReadAccountNumber("Please enter Source AccountNumber? ");
        }

        clsBankClient SourceClient = clsBankClient::Find(SourceAccountNumber);
        cout << "\nSource Client:";
        _PrintClient(SourceClient);

        string DestinationAccountNumber = _ReadAccountNumber("Please enter Destination AccountNumber? ");

        while (!clsBankClient::IsClientExist(DestinationAccountNumber)
            || DestinationAccountNumber == SourceAccountNumber)
        {
            if (DestinationAccountNumber == SourceAccountNumber)
                cout << "\nDestination account cannot be the same as Source account.\n";
            else
                cout << "\nClient with [" << DestinationAccountNumber << "] does not exist.\n";

            DestinationAccountNumber = _ReadAccountNumber("Please enter Destination AccountNumber? ");
        }

        clsBankClient DestinationClient = clsBankClient::Find(DestinationAccountNumber);
        cout << "\nDestination Client:";
        _PrintClient(DestinationClient);

        float Amount = 0;
        cout << "\nPlease enter transfer amount? ";
        Amount = clsInputValidate::ReadFloatNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
            {
                cout << "\nAmount Transferred Successfully.\n";
                cout << "\nSource New Balance Is: " << SourceClient.AccountBalance;
                cout << "\nDestination New Balance Is: " << DestinationClient.AccountBalance;
            }
            else
            {
                cout << "\nCannot transfer, Insufficient Balance!\n";
                cout << "\nAmount to transfer is: " << Amount;
                cout << "\nSource Balance is: " << SourceClient.AccountBalance;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};