#include <iostream>
#include <cstring>

using namespace std;

int getNonNegSum(int* arrPtr, int& sz, int& idx, int& count){
    int sum = 0;
    int end = idx + count;
    arrPtr += idx;
    
    while(idx != end){
        if(idx > (sz - sz) && idx <= (sz - 1) && count < (sz - idx) && count >= 0){
            if(*arrPtr >= 0)
                sum += *arrPtr;
        } else {
            sum = -1;
            break;
        }
        
        arrPtr++;
        idx++;
    }

    return sum;
}//DONE

bool isAscendingDigits(char* cStr){
    int curr, next;
    
    while(*(cStr+1) != '\0'){
        curr = (int) *(cStr)-48;
        next = (int) *(cStr+1)-48;
        
        if(curr > next)
            cStr++;
        else
            return false;
    }

    return true;
}//DONE


int len(char* cStr){
    int length = 0 ;
    while(*cStr != '\0'){
        if(*cStr != ' ')
            length++;
        cStr++;
    }
    length++;
    //cout << "length: " << length << endl;
    //cout << "*(cStr): " << *(cStr) << endl;
    
    return length;
}
/*
char* duplicateWithoutBlanks(char* cStr){
    char* cStr2 = new char[len(cStr)];
    int i=0, j=0;
    
    while(*(cStr+i) != '\0'){
        if(*(cStr+i) != ' '){
            *(cStr2+j) = *(cStr+i);
            i++;
            j++;
        } else
            i++;
    }
    *(cStr2+j) = *(cStr+i);
    
    return cStr2;
}//DONE    
*/

/*
char* duplicateWithoutBlanks(char* cStr){
    char* cStr2 = new char[len(cStr)];
    
    char* c = cStr;
    char* cc = cStr2;

    while(*c != '\0'){
        if(*c != ' ')
            *cc++ = *c++;
        else
            c++;
    }
    *cc++ = *c;

    return cStr2;
}//DONE  
*/

char* duplicateWithoutBlanks(char* cStr){
    char* cStr2 = new char[len(cStr)];
    char* pCurr = cStr2;
    
    for(; *cStr != '\0'; cStr++){
        if (*cStr != ' ')
            *pCurr++ = *cStr;
    }
    *pCurr = *cStr;
  
    return cStr2;
}//DONE    


bool hasHelpOption(int argc, char* argv[]){
    
    for(int i=1; i<argc; i++){
        string arg = argv[i];
        
        if(arg == "/help" || arg == "/?" || arg == "—help")
            return true;
    }
    
    return false;
}//DONE

int main(){//int argc, char* argv[]

    /*
    int size, index, count, val;

    cout << "Enter size of array: ";
    cin >> size;

    cout << "Provide array index to begin sum of values from: ";
    cin >> index;

    cout << "Provide number of values to sum over: ";
    cin >> count;

    int arr[size];

    for(int i=0;i<size;i++){
        cout << "Enter value: ";
        cin >> val;
        arr[i] = val;
    }

    int* ptr;
    ptr = arr;
    
    int nns = getNonNegSum(ptr, size, index, count);
    //cout << nns << endl;
    */
    
    ///*
    string cs = "";
    cout << "Enter string: "; 
    getline(cin, cs);

    char* pCstr = (char*) cs.c_str();
    
    //isAscendingDigits(pCstr);
    
    char* dwb = duplicateWithoutBlanks(pCstr);
    cout << dwb << endl;
    //*/

    //hasHelpOption(argc, argv);
    
    return 0;
}
//EXPLAIN how functions are used and tested