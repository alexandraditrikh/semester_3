#include <iostream>
#include <fstream>
#include <cctype>

#define SIZE_DIGIT 5

using namespace std;

bool task (ifstream& in, int m) {
    char c;
    int s = 0;
    int count = 0;
    int count_dig = 0;

    while (in.get(c)) {
        if (isspace(c)) continue;

        switch (s) {
        case 0: {  
            if (isalpha(c)) {
                s = 1;
                count = 1;
            } 

            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 1: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            } 
            else if (c == '=') s = 2;  
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 2: {  
            if (c == '+' || c == '-') { 
                s = 20;  
            }
            else if (isdigit(c)) {
                count_dig = 1;
                s = 3;
            } 
            else if (isalpha(c)) {
                count = 1;
                s = 4;
            } 

            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 20: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 3;
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 3: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            } 
            else {  
                if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
                if (c == '>' || c == '<' || c == '=') s = 5; 

                else { cout << "false in " << s << endl; return false; } 
            }
            break;
        }

        case 4: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            } 
            else if (c == '>' || c == '<' || c == '=') s = 5; 

            else { cout << "false in " << s << endl; return false; } 
            break;
        }
         
        case 5: {  
            if (c == '=') s = 6;  
            
            else {
                in.unget();
                s = 6;  
            }
            break;
        }

        case 6: {  
            if (c == '+' || c == '-') {
                s = 21;  
            }
            else if (isdigit(c)) {
                count_dig = 1;
                s = 7;  
            } 
            else if (isalpha(c)) {
                count = 1;
                s = 8;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 21: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 7;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 7: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            }
            else if (c == '?') {
                if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; }  
                s = 9;  
            }

            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 8: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            }
            else if (c == '?') s = 9;  

            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 9: {  
            if (c == '+' || c == '-') {
                s = 22;  
            }
            else if (isdigit(c)) {
                count_dig = 1; 
                s = 10;  
            } 
            else if (isalpha(c)) {
                count = 1; 
                s = 11;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 22: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 10;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 10: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            }
            else {  
                 if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
                 
                 if (c == '+' || c == '-' || c == '*' || c == '/') s = 12;  
                 else if (c == ':') s = 15;  

                 else { cout << "false in " << s << endl; return false; }
            }
            break;
        }

        case 11: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') s = 12;  
            else if (c == ':') s = 15;  

            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 12: {  
            if (c == '+' || c == '-') {
                s = 23;  
            }
            else if (isdigit(c)) {
                count_dig = 1; 
                s = 13;  
            } 
            else if (isalpha(c)) {
                count = 1; 
                s = 14;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 23: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 13;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 13: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            }
            else if (c == ':') {
                if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; } 
                s = 15;  
            }

            else { cout << "false in " << s << endl; return false; }
            break;      
        }

        case 14: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            }
            else if (c == ':') s = 15;  

            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 15: {  
            if (c == '+' || c == '-') {
                s = 24;  
            }
            else if (isdigit(c)) {
                count_dig = 1; 
                s = 16;  
            } 
            else if (isalpha(c)) {
                count = 1; 
                s = 17;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 24: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 16;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 16: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            }
            else {  
                 if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
                 
                 if (c == '+' || c == '-' || c == '*' || c == '/') s = 18;  
                 else if (c == ';') s = 25;  
                 
                 else { cout << "false in " << s << endl; return false; }
            }
            break;
        }

        case 17: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') s = 18;  
            else if (c == ';') s = 25;  

            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 18: {  
            if (c == '+' || c == '-') {
                s = 26;  
            }
            else if (isdigit(c)) {
                count_dig = 1; 
                s = 19;  
            } 
            else if (isalpha(c)) {
                count = 1; 
                s = 27;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 26: {  
            if (isdigit(c)) {
                count_dig = 1;
                s = 19;  
            } 
            
            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 19: {  
            if (isdigit(c)) {
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { cout << "false in " << s << endl; return false; }
            }
            else if (c == ';') {
                if (count_dig != SIZE_DIGIT) { cout << "false in " << s << endl; return false; } 
                s = 25;  
            }

            else { cout << "false in " << s << endl; return false; }
            break;
        }

        case 27: {  
            if (isalpha(c) || isdigit(c)) {
                count++; 
                if (count > m) { cout << "false in " << s << endl; return false; }
            }
            else if (c == ';') s = 25;  

            else { cout << "false in " << s << endl; return false; }
            break;
        }
        
        case 25: {  
            in.unget(); 
            s = 0;  
            break;
        }
        
        default:
            cout << "false in default " << s << endl;
            return false;

        }  
    }  

    return s == 25;
}


int main() {
    int m;
    cout << "enter m\n";
    if (!(cin >> m)) {
        cerr << "m is not entered\n";
        return 1;
    }
    if (m < 2 || m > 4) {
        cerr << "m = 2 or 3 or 4\n";
        return 1;
    }

    ifstream in ("operator.txt");
    if (!in.is_open()) {
        cerr << "err: open input file" << endl;
        return 1;
    }

    cout << (task(in, m) ? "expr is valid\n" : "expr is not valid\n");
    in.close();

    return 0;
}