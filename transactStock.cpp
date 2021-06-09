#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class StockException : public runtime_error {
    private:
        int badNumShares;
        double badPrice;
    
    public:
        StockException(string errMsg, int _badNumShares) :
        runtime_error::runtime_error(errMsg), badNumShares(_badNumShares){}
        
        StockException(string errMsg, double _badPrice) :
        runtime_error::runtime_error(errMsg), badPrice(_badPrice){}

        StockException(string errMsg, int _badNumShares, double _badPrice) :
        runtime_error::runtime_error(errMsg), badNumShares(_badNumShares), badPrice(_badPrice){}

        int getBadNumShares(){
            return badNumShares;
        }
        double getBadPrice(){
            return badPrice;
        }
};

class Stock {
    private:
        double price;
        int numShares;
        string company;

    public:
        Stock(){}
        Stock(int _numShares, double _price, string _company) :
        numShares(_numShares), price(_price), company(_company){
            if(_numShares < 0){
                StockException errObj("Invalid quantity. Ignored.", _numShares);
                throw errObj;
            }
            else if(_price < 0){
                StockException errObj("Invalid price. Ignored.", _price);
                throw errObj;
            }
        }

        int getNumShares(){
            return numShares;
        }
        double getPrice(){
            return price;
        }
        string getCompany(){
            return company;
        }

        virtual string toString(){
            stringstream ss;
            ss << fixed;
            ss << "SYMBOL(" << company << ") " 
               << "PRICE($" << setprecision(2) << price << ") "
               << "QUANTITY(" << numShares << ") "
               << "TOTAL($" << setprecision(2) << (numShares * price) << ")" << endl;

            return ss.str();
        }

        void help(){
            cout <<
            "\"buy\"     buy a stock by asking for the stock symbol, quantity and share price\n"
            "\"sell\"    sell a stock by asking for the stock symbol, quantity and share price\n"
            "\"display\" display all purchases \n"
            "\"summary\" display only the summary of purchase total and number of purchases\n"
            "\"exit\"    exit the program after the confirmation \n";
        }
};

class BuyTransaction : public Stock {
    public:
        BuyTransaction(int _nShares, double _pri, string _comp) : 
        Stock::Stock(_nShares, _pri, _comp){}

        string toString(){
            stringstream ss;

            ss << "TYPE(buy) " << Stock::toString();

            return ss.str();
        }
};

class SellTransaction : public Stock {
    public:
        SellTransaction(int _nShares, double _pri, string _comp) : 
        Stock::Stock(_nShares, _pri, _comp){}

        string toString(){
            stringstream ss;

            ss << "TYPE(sell) " << Stock::toString();

            return ss.str();
        }
};

void buy(vector<Stock*>& hist){
    double pri;
    int numSh;
    string comp;
    Stock* bt = nullptr;

    cout << "Please enter the company name: ";
    cin >> comp;
    
    do {
        try {
            cout << "Please enter the number of shares: ";
            cin >> numSh;

            cout << "Please enter the share price: ";
            cin >> pri;

            bt = new BuyTransaction(numSh, pri, comp);
        }
        catch(StockException& se){
            // prints the error message passed by throw statement
            if(numSh < 0)
                cout << "Error: " << se.getBadNumShares() << " " << se.what() << endl;
            else if(pri < 0)
                cout << "Error: " << se.getBadPrice() << " " << se.what() << endl;
        }
    }
    while(numSh < 0 || pri < 0 || (numSh < 0 && pri < 0));

    hist.push_back(bt);
}

void sell(vector<Stock*>& hist){
    double pri;
    int numSh;
    string comp;
    Stock* st = nullptr;

    cout << "Please enter the company name: ";
    cin >> comp;
    
    do {
        try {
            cout << "Please enter the number of shares: ";
            cin >> numSh;

            cout << "Please enter the share price: ";
            cin >> pri;

            st = new SellTransaction(numSh, pri, comp);
        }
        catch(StockException& se){
            // prints the error message passed by throw statement
            if(numSh < 0)
                cout << "Error: " << se.getBadNumShares() << " " << se.what() << endl;
            else if(pri < 0)
                cout << "Error: " << se.getBadPrice() << " " << se.what() << endl;
            else if(numSh < 0 && pri < 0)
                cout << "Error: " << se.getBadNumShares() << se.getBadPrice() << " "
                     << " " << se.what() << endl;
        }
    }
    while(numSh < 0 || pri < 0 || (numSh < 0 && pri < 0));

    hist.push_back(st);
}

string display(vector<Stock*>& hist){
    stringstream ss;

    if(!hist.empty()){
        for(int i = 0; i < hist.size(); i++){
            ss << fixed;
            ss << hist[i]->toString();//CHECK IF CORRECT!!
        }
    }

    return ss.str();
}

string summary(vector<Stock*>& hist){// DYNAMIC CASTING
    int countTransBT = 0;
    double sumTotalBT = 0.0;
    int countTransST = 0;
    double sumTotalST = 0.0;
    stringstream ss;
        
    for(int i=0; i<hist.size(); i++){
        //i.e. IntVar *pNumObj = dynamic_cast<IntVar*> (pVar);
        //CHECK IF NULL, IF NOT, IT's pointing to correct obj;
        //NEED to make parent class contain at least one virtual method
        //to be polymorphic, to make dynamic casting work 
        BuyTransaction* bt = dynamic_cast<BuyTransaction*> (hist[i]);
        
        if(bt != nullptr){//NULL
            countTransBT += hist[i]->getNumShares();
            sumTotalBT += hist[i]->getNumShares()*hist[i]->getPrice();
        }
        else
            countTransST += hist[i]->getNumShares();
            sumTotalST += hist[i]->getNumShares()*hist[i]->getPrice();
    }

    ss << fixed;
    ss << "BUY-transactions(" << countTransBT << ") "
       << "BUY-total(" << setprecision(2) << sumTotalBT << ") "
       << "SELL-transactions(" << countTransST << ") "
       << "SELL-total(" << setprecision(2) << sumTotalST << ")";

    return ss.str();
}

/*
string find(vector<Stock*>& hist, string company){
    stringstream ss;
    
    for(int i=0; i<hist.size(); i++){
        if(hist[i]->getCompany().find(company) != string::npos){// could use substring method to match
            ss << fixed;
            ss << "SYMBOL(" << hist[i]->getCompany() << ") " 
                << "PRICE($" << setprecision(2) << hist[i]->getPrice() << ") "
                << "QUANTITY(" << hist[i]->getNumShares() << ") "
                << "TOTAL($" << setprecision(2) << (hist[i]->getNumShares() * hist[i]->getPrice()) << ")" << endl;
        }
        else
            ss << "No stock purchase with greater or equal amount is found." << endl;
    }

    return ss.str();
}


string amount(vector<Stock*>& hist, double cutoff){
    stringstream ss;
    
    for(int i=0; i<hist.size(); i++){
        if(hist[i]->getPrice()*hist[i]->getNumShares() >= cutoff){
            ss << fixed;
            ss << "SYMBOL(" << hist[i]->getCompany() << ") " 
                << "PRICE($" << setprecision(2) << hist[i]->getPrice() << ") "
                << "QUANTITY(" << hist[i]->getNumShares() << ") "
                << "TOTAL($" << setprecision(2) << (hist[i]->getNumShares() * hist[i]->getPrice()) << ")" << endl;
        }
    }

    return ss.str();
}
*/

vector<Stock*> fileInitList(int argc, char* argv[], vector<Stock*>& fileStocks){// TRY & CATCH

    if(argc < 2)
        cout << "No argument provided on command line." << endl;
    else if (argc == 2){
        string file = argv[1];
        ifstream fin(file);

        if(fin.is_open() == false)
            cout << "File not found. Please enter valid file as argument on cmd line." << endl;
        else {
            while(fin.eof() == false){
                int transactionType;
                string comp = "";
                int numSh = 0;
                double pri = 0.0;
                Stock* stockPtr = nullptr;

                fin >> transactionType;
                fin >> numSh;//order of fin matters
                fin >> comp;//fin knows hows to find string, data types
                fin >> pri;

                try {
                    if(transactionType == 1){
                        stockPtr = new BuyTransaction(numSh, pri, comp);
                        fileStocks.push_back(stockPtr);
                    }
                    else if(transactionType == 2){
                        stockPtr = new SellTransaction(numSh, pri, comp);
                        fileStocks.push_back(stockPtr);
                    }
                }
                catch(StockException& se){
                    // prints the error message passed by throw statement
                    if(numSh < 0)
                        cout << "Error: " << se.getBadNumShares() << " " << se.what() << endl;
                    else if(pri < 0)
                        cout << "Error: " << se.getBadPrice() << " " << se.what() << endl;
                }
                
                string oneLine;
                getline(fin, oneLine); 
            }
        }
    }

    return fileStocks;
}


int main(int argc, char* argv[]){
    ///*
    vector<Stock*> fileHist;    
    string cmd;
    char answer;
    Stock st;

    fileInitList(argc, argv, fileHist);
    
    if(argc < 2)
        cout << "Restart program." << endl;
    else {
        do {
            cout << "Please enter a command: ";
            getline(cin, cmd);

            if(cmd == "buy"){
                buy(fileHist);
                cin.ignore();
            }
            else if(cmd == "sell"){
                sell(fileHist);
                cin.ignore();
            }
            else if(cmd == "display"){
                cout << display(fileHist);
            }
            else if(cmd == "summary"){
                cout << summary(fileHist) << endl;
            }
            else if(cmd == "help"){
                st.help();
            }
            /*
            else if(cmd == "exit"){
                cin.ignore();
            } 
            else {
                stringstream sin(cmd);
                string arg;
                sin >> arg;

                if(arg == "find"){
                    string symbol;
                    sin >> symbol;
                    cout << find(fileHist, symbol);
                }
                else if(arg == "amount>="){
                    double amt;
                    sin >> amt;
                    cout << amount(fileHist, amt);
                } else
                    cout << "Invalid command." << endl;
            }
            */
            cin.clear();
        }
        while(cmd != "exit");   
    }

    cout << "Goodbye." << endl;
    //*/

    return 0;
}