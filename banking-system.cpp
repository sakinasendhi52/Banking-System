//Banking System Project

//Overdraft limit is the maximum negative balance a bank permits in a customer’s account under an overdraft facility.

//header files
#include<iostream>
#include<cstring>
using namespace std;

//base class
class BankAccount{
    private:    //private attributes
        int accountNumber;
        char accountHolderName[50],type[25];
        double balance;

    public:     
        static int totalAccounts;    //static variable

        //Parameterized Constructor
        BankAccount(int accountNumber, const char* name, const char* type, double balance){
            this->accountNumber = accountNumber;
            strcpy(this->accountHolderName, name);
            strcpy(this->type, type);
            this->balance = balance;
        }

        //Adds funds to the account
        void deposit(double amount){
            balance=getBalance() + amount;
            setBalance(balance);
        }

        //Withdraws funds from the account
        virtual void withdraw(double amount){
            if(getBalance()-amount>=0){
                balance=getBalance() - amount;
                setBalance(balance);
                cout<<"               |   BALANCE AFTER WITHDRAW  : "<<balance<<"   |"<<endl;
                cout<<"--------------------- W I T H D R A W   D O N E --------------------"<<endl<<endl;
            }
            else{
                cout<<"------------- W I T H D R A W   N O T   P O S S I B L E ------------"<<endl<<endl;
            }
        }

        //Set the account number
        void setAccountNumber(int num){
            this->accountNumber=num;
        }

        //Returns the account number
        int getAccountNumber(){
            return accountNumber;
        }

        //Set account type
        void setType(const char* type){
            strcpy(this->type,type);
        }

        //Set account holder name
        void setAccountHolderName(const char* name){
            strcpy(this->accountHolderName,name);
        }

        //Returns account holder name
        string getAccountHolderName(){
            return accountHolderName;
        }

        //Set balance after deposit or withdraw
        void setBalance(double balance){
            this->balance=balance;
        }

        //Returns the current balance
        double getBalance(){
            return balance;
        }

        //Returns the Account type
        string getType(){
            return type;
        }

        //Displays account details
        void displayAccountInfo(){
            cout<<"--------------------------------------------------------------------"<<endl;
            cout<<"ACCOUNT NUMBER         : "<<accountNumber<<endl;
            cout<<"ACCOUNT HOLDER NAME    : "<<accountHolderName<<endl;
            cout<<"TYPE                   : "<<type<<endl;
            cout<<"BALANCE                : "<<balance<<endl;
        }

        virtual void getOverdraftLimit(){}
        virtual void calculateInterest() {}

        //Destructor
        virtual ~BankAccount(){}
};

//derived class
class SavingsAccount : public BankAccount{
    private:    //private attribute
        float interestRate=3;

    public:     //public method
        //Parameterized Constructor
        SavingsAccount(int accountNumber,char accountHolderName[],char type[],double balance):BankAccount(accountNumber, accountHolderName, type, balance){};

        //Calculates interest based on the balance and interest rate
        void calculateInterest() override{
            double interestAmount;
            interestAmount=getBalance()*(interestRate/100);
            
            cout<<"INTEREST PERCENTAGE    : "<<interestRate<<"%"<<endl;
            cout<<"INTEREST AMOUNT        : "<<interestAmount<<endl;
            cout<<"BALANCE AFTER INTEREST : "<<getBalance()+interestAmount<<endl;
        }
};

//derived class
class CheckingAccount : public BankAccount{
    private:    //private attribute
        double overdraftLimit=30000;

    public:     //public method
        //Parameterized Constructor
        CheckingAccount(int accountNumber,char accountHolderName[],char type[],double balance):BankAccount(accountNumber, accountHolderName, type, balance){};

        //Checks if a withdrawal exceeds the overdraft limit
        void withdraw(double amount) override {
            if(getBalance() + overdraftLimit >= amount){
                setBalance(getBalance() - amount);
                cout<<"              |   BALANCE AFTER WITHDRAW  : "<<getBalance()<<"   |"<<endl;
                cout<<"--------------------- W I T H D R A W   D O N E --------------------"<<endl<<endl;
            }
            else{
                cout<<endl<<"   W I T H D R A W   E X C E E D S   O V E R D R A F T   L I M I T   "<<endl<<endl;
            }
        }
        //Display Overdraft Limit
        void getOverdraftLimit() override{
            cout<<"OVERDRAFT LIMIT        : "<<overdraftLimit<<endl;
        }
};

//derived class
class FixedDepositAccount : public BankAccount{
    private:    //private attribute
        int terms;     //duration in months
        float interestRate=6;      //per year 6% interest
        float monthInterestRate=6.0/12;      //per month 0.5% interest

    public:     //public method
        //Set terms for fixed deposit account
        void setTerms(int terms){
            this->terms=terms;
        }
        //Returns the terms for fixed deposit account
        int getTerms(){
            return terms;
        }
        //Parameterized Constructor
        FixedDepositAccount(int accountNumber,char accountHolderName[],char type[],double balance,int terms):BankAccount(accountNumber, accountHolderName, type, balance){
            setTerms(terms);
        };
        //Calculates fixed deposit interest
        void calculateInterest() override{
            double interestAmount;
            terms=getTerms();
            interestAmount=(getBalance()*monthInterestRate*terms)/100;

            cout<<"TERMS                  : "<<terms<<" Months"<<endl;
            cout<<"INTEREST PERCENTAGE    : "<<interestRate<<"%"<<endl;
            cout<<"PER MONTH INTEREST     : "<<monthInterestRate<<"%"<<endl;
            cout<<"INTEREST AMOUNT        : "<<interestAmount<<endl;
            cout<<"BALANCE AFTER INTEREST : "<<getBalance()+interestAmount<<endl;
        }
};

int BankAccount::totalAccounts=0;      //static variable initialization

//main function
int main(){
    BankAccount* bankAccounts[100];      //base class pointer

    int choice;       //variables

    //heading
    cout<<"--------------------------------------------------------------------"<<endl;
    cout<<"-------------------- B A N K I N G  S Y S T E M --------------------"<<endl;
    cout<<"--------------------------------------------------------------------"<<endl<<endl;

    //do while loop for account management
    do{
        cout<<"----------------------------- M E N U ------------------------------"<<endl;
        cout<<"1 . ADD ACCOUNT"<<endl;
        cout<<"2 . DEPOSIT"<<endl;
        cout<<"3 . WITHDRAW"<<endl;
        cout<<"4 . GET BALANCE"<<endl;
        cout<<"5 . DISPLAY ACCOUNT INFORMATION"<<endl;
        cout<<"6 . EXIT"<<endl<<endl;

        cout<<"Enter your choice : ";     
        cin>>choice;                   //input choice
        cout<<endl;

        //switch case to match the choice
        switch(choice){
            //add account
            case 1:{
                int accountChoice;
                cout<<"---------------------- A D D  A C C O U N T ------------------------"<<endl;
                cout<<"--------------------------------------------------------------------"<<endl<<endl;
                cout<<"-------------------- A C C O U N T   T Y P E S ---------------------"<<endl;
                cout<<"1. SAVINGS ACCOUNT   2.  CHECKING ACCOUNT   3. FIXED DEPOSIT ACCOUNT"<<endl;    //Account types
                cout<<"Enter Type of Account you want to open : ";
                cin>>accountChoice;            //input account choice
                cout<<endl<<endl;

                int accountNumber;
                char accountHolderName[50],type[25];
                double balance;
                //switch case to match the account type choice
                switch(accountChoice){
                    
                    //savings account
                    case 1:{
                        cout<<"Enter Account Number          : ";
                        cin>>accountNumber;
                        cin.ignore();
                        cout<<"Enter Account Holder Name     : ";
                        cin.getline(accountHolderName,50);
                        cout<<"Enter Balance                 : ";
                        cin>>balance;
                        strcpy(type,"Savings Account");
                        
                        bankAccounts[BankAccount::totalAccounts]=new SavingsAccount(accountNumber,accountHolderName,type,balance);
                        BankAccount::totalAccounts++;
                        cout<<"-------------------- A C C O U N T   A D D E D ---------------------"<<endl<<endl;
                        break;
                    }

                    //checking account
                    case 2:{
                        cout<<"Enter Account Number          : ";
                        cin>>accountNumber;
                        cin.ignore();
                        cout<<"Enter Account Holder Name     : ";
                        cin.getline(accountHolderName,50);
                        cout<<"Enter Balance                 : ";
                        cin>>balance;
                        strcpy(type,"Checking Account");
                        bankAccounts[BankAccount::totalAccounts]=new CheckingAccount(accountNumber,accountHolderName,type,balance);
                        BankAccount::totalAccounts++;
                        cout<<"-------------------- A C C O U N T   A D D E D ---------------------"<<endl<<endl;
                        break;
                    }

                    //fixed deposit account
                    case 3:{
                        int terms;
                        cout<<"Enter Account Number          : ";
                        cin>>accountNumber;
                        cin.ignore();
                        cout<<"Enter Account Holder Name     : ";
                        cin.getline(accountHolderName,50);
                        cout<<"Enter Balance                 : ";
                        cin>>balance;
                        strcpy(type,"Fixed Deposit Account");
                        cout<<"Enter Terms in Months         : ";
                        cin>>terms;
                        bankAccounts[BankAccount::totalAccounts]=new FixedDepositAccount(accountNumber,accountHolderName,type,balance,terms);
                        BankAccount::totalAccounts++;
                        cout<<"-------------------- A C C O U N T   A D D E D ---------------------"<<endl<<endl;
                        break;
                    }

                    //default case
                    default:{
                        cout<<"------------------- I N V A L I D   C H O I C E --------------------"<<endl<<endl;
                        break;
                    }
                }
                break;
            }

            //deposit
            case 2:{
                int accountNumber,match=0;
                double balance,deposit;
                cout<<"-------------------------- D E P O S I T ---------------------------"<<endl;
                cout<<"--------------------------------------------------------------------"<<endl;
                cout<<"Enter Account Number          : ";
                cin>>accountNumber;
                for(int i=0; i<BankAccount::totalAccounts; i++){
                    if(bankAccounts[i]->getAccountNumber()==accountNumber){
                        cout<<"Your Current Balance  : "<<bankAccounts[i]->getBalance()<<endl;
                        cout<<"Enter Deposit Amount  : ";
                        cin>>deposit;               //deposit input
                        bankAccounts[i]->deposit(deposit);
                        cout<<"              |   BALANCE AFTER DEPOSIT  : "<<bankAccounts[i]->getBalance()<<"   |"<<endl;
                        cout<<"---------------------- D E P O S I T   D O N E ---------------------"<<endl<<endl;
                        match=1;
                    }
                }
                if(match==0){
                    cout<<"------------------ N O   S U C H   A C C O U N T -------------------"<<endl<<endl;
                }
                break;
            }

            //withdraw
            case 3:{
                int accountNumber,match=0;
                double balance,withdraw;
                cout<<"------------------------- W I T H D R A W --------------------------"<<endl;
                cout<<"--------------------------------------------------------------------"<<endl;
                cout<<"Enter Account Number          : ";
                cin>>accountNumber;

                for(int i=0; i<BankAccount::totalAccounts; i++){
                    if(bankAccounts[i]->getAccountNumber()==accountNumber){
                        cout<<"Your Current Balance  : "<<bankAccounts[i]->getBalance()<<endl;
                        cout<<"Enter Withdraw Amount : ";
                        cin>>withdraw;               //withdraw input

                        bankAccounts[i]->withdraw(withdraw);
                        match=1;
                    }
                }
                if(match==0){
                    cout<<"------------------ N O   S U C H   A C C O U N T -------------------"<<endl<<endl;
                }
                break;
            }

            //get balance
            case 4:{
                int accountNumber,match=0;
                double balance;
                cout<<"--------------------- C H E C K  B A L A N C E ---------------------"<<endl;
                cout<<"--------------------------------------------------------------------"<<endl<<endl;
                cout<<"Enter Account Number          : ";
                cin>>accountNumber;
                for(int i=0; i<BankAccount::totalAccounts; i++){
                    if(bankAccounts[i]->getAccountNumber()==accountNumber){
                        cout<<"             |   YOUR CURRENT BALANCE  : "<<bankAccounts[i]->getBalance()<<"   |"<<endl;
                        cout<<"--------------------------------------------------------------------"<<endl<<endl;
                        match=1;
                    }
                }
                if(match==0){
                    cout<<"------------------ N O   S U C H   A C C O U N T -------------------"<<endl<<endl;
                }
                break;
            }

            //display account information
            case 5:{
                int accountNumber,match=0;
                cout<<"--------------- A C C O U N T   I N F O R M A T I O N --------------"<<endl;
                cout<<"--------------------------------------------------------------------"<<endl;
                cout<<"Enter Account Number          : ";
                cin>>accountNumber;

                for(int i=0; i<BankAccount::totalAccounts; i++){
                    if(bankAccounts[i]->getAccountNumber()==accountNumber){
                        bankAccounts[i]->displayAccountInfo();
                        bankAccounts[i]->calculateInterest();     //calculateInterest() for Savings and Fixed Deposit Account
                        bankAccounts[i]->getOverdraftLimit();     //getOverdraftLimit() for Checking Account
                        cout<<"--------------------------------------------------------------------"<<endl<<endl;
                        match=1;
                    }
                }
                if(match==0){
                    cout<<"------------------ N O   S U C H   A C C O U N T -------------------"<<endl<<endl;
                }
                break;
            }

            //exit case
            case 6:{
                cout<<"------------------------ T H A N K   Y O U -------------------------";
                break;
            }

            //default case
            default:{
                cout<<"--------------- E N T E R   V A L I D   C H O I C E ----------------"<<endl<<endl;
                break;
            }
        }
    }
    while(choice!=6);

    //Free the space
    for(int i=0; i<BankAccount::totalAccounts; i++){
        delete bankAccounts[i];
    }
    
    return 0;
}