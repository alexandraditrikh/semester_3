#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

#include "List.h" 

#define SIZE_DIGIT 5
#define MAX_SIZE_COND 20
#define MAX_SIZE_EXPR 20
#define MAX_IDENT_LENGTH 5
#define MAX_VARIABLES 10

using namespace std;


int calculate_expression(char* expr, int m, VariableNode*& top) {
    int result = 0;
    char operation = '+';
    int i = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || (expr[i] == '-' && isdigit(expr[i + 1]))) {
            int num_val = 0;
            bool is_negative = false;
            if (expr[i] == '-') {
                is_negative = true;
                i++;
            }
            
            while (isdigit(expr[i]) && expr[i] != '\0') {
                num_val = num_val * 10 + (expr[i] - '0');
                i++;
            }
            if (is_negative) {
                num_val = -num_val;
            }
            
            switch (operation) {
                case '+': result += num_val; break;
                case '-': result -= num_val; break;
                case '*': result *= num_val; break;
                case '/': if (num_val != 0) result /= num_val; break;
                default: {
                    cerr << "Err: Operation is not + or - or * or /\n";
                    return result;
                }
            }
        
        } 
        else if (isalpha(expr[i])) {
            char current_ident[MAX_IDENT_LENGTH + 1] = {0};
            int ident_idx = 0;
            
            while ((isalpha(expr[i]) || isdigit(expr[i])) && expr[i] != '\0' && ident_idx < m) {
                current_ident[ident_idx++] = expr[i];
                i++;
            }
            current_ident[ident_idx] = '\0';
            
            int ident_val = get_variable_value(top, current_ident, m);
            switch (operation) {
                case '+': result += ident_val; break;
                case '-': result -= ident_val; break;
                case '*': result *= ident_val; break;
                case '/': if (ident_val != 0) result /= ident_val; break;
            }
        } 
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operation = expr[i];
            i++;
        } 
        else i++;
    }
    return result;
}

bool calculate_condition(char* cond, int m, VariableNode*& top) {
    char left[MAX_SIZE_EXPR] = {0};
    char right[MAX_SIZE_EXPR] = {0};
    char op = '\0';
    bool is_sost = false;

    int i = 0, left_idx = 0, right_idx = 0;
    bool in_left = true;

    while (cond[i] != '\0') {
        if (cond[i] == '>' || cond[i] == '<' || cond[i] == '=') {
            if (op == '\0') {
                op = cond[i];
                in_left = false;
            } else if (cond[i] == '=' && (op == '>' || op == '<')) {
                is_sost = true;
            }
            i++;
        } else {
            if (in_left) {
                left[left_idx++] = cond[i];
            } else {
                right[right_idx++] = cond[i];
            }
            i++;
        }
    }
    
    left[left_idx] = '\0';
    right[right_idx] = '\0';
    
    int left_val = calculate_expression(left, m, top);
    int right_val = calculate_expression(right, m, top);
    
    switch (op) {
        case '>': {
            if (is_sost) return left_val >= right_val;
            return left_val > right_val;
        }
        case '<': {
            if (is_sost) return left_val <= right_val;
            return left_val < right_val;
        }
        case '=': return left_val == right_val;
        default: return false; 
    }
}

bool task(ifstream& in, int m, char* ident, bool& condition_val, int& expr1_value, int& expr2_value, VariableNode*& top) {
    char c;

    int s = 25; 
    int count = 0;
    int count_dig = 0;
    
    int ident_idx = 0;
    int condition_idx = 0;
    int expr1_idx = 0;
    int expr2_idx = 0;
    
    char condition_str[MAX_SIZE_COND] = {0}; 
    char expr1_str[MAX_SIZE_EXPR] = {0};
    char expr2_str[MAX_SIZE_EXPR] = {0};

    char current_op = '\0';

    int err_case = 0; 
    
    while (in.get(c) || s == 25) {
        // Если предыдущее состояние было 25, а символ не был прочитан,
        // это означает, что нам нужно выполнить сброс и попробовать прочитать снова
        if (s == 25) {
            
            // Если символ не был прочитан (EOF), выходим
            if (in.eof()) break; 
            
            // Символ был прочитан (или мы вернули его unget'ом на прошлой итерации), 
            // но мы еще не обработали его. Мы его потеряли, но это нормально, 
            // так как в case 25 мы сбрасываем и переходим в s=0.
            
            // Сброс всех переменных для новой команды
            ident_idx = 0;
            condition_idx = 0;
            expr1_idx = 0;
            expr2_idx = 0;
            count = 0;
            count_dig = 0;
            current_op = '\0';
            
            // Очистка буферов
            memset(ident, 0, MAX_IDENT_LENGTH + 1);
            memset(condition_str, 0, MAX_SIZE_COND);
            memset(expr1_str, 0, MAX_SIZE_EXPR);
            memset(expr2_str, 0, MAX_SIZE_EXPR);

            s = 0; // Переход в начальное состояние для нового идентификатора
            
            // Прочитанный символ (c) будет обработан на следующей итерации цикла
            // (или мы прочитаем новый, если текущий был пробелом)
            
            if (isspace(c)) continue; // Если прочитанный символ был пробелом, читаем следующий
        }
        
        if (isspace(c)) continue; // Игнорируем пробелы, если не в состоянии 25

        switch (s) {
        case 0: {
            if (isalpha(c)) {
                ident[ident_idx++] = c;
                s = 1;
                count = 1;
            } else { 
                err_case = 0;
                s = 100;
            }
            break;
        }
        case 1: {
            if (isalpha(c) || isdigit(c)) {
                ident[ident_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 1;
                    s = 100;
                }
            } 
            else if (c == '=') {
                ident[ident_idx] = '\0';
                s = 2; 
            } 
            else { 
                err_case = 1;
                s = 100;
            }
            break;
        }
        case 2: { 
            condition_str[condition_idx++] = c;
            if (c == '+' || c == '-') {
                s = 20; 
            } else if (isdigit(c)) {
                count_dig = 1;
                s = 3;
            } else if (isalpha(c)) {
                count = 1;
                s = 4;
            } else { 
                err_case = 2;
                s = 100;
            }
            break;
        }
        case 20: {
            condition_str[condition_idx++] = c; 
            if (isdigit(c)) {
                count_dig = 1;
                s = 3;
            } else { 
                err_case = 20;
                s = 100;
            }
            break;
        }
        case 3: {
            if (isdigit(c)) {
                condition_str[condition_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 3;
                    s = 100;
                }
            } else {
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 3;
                    s = 100;
                    break;
                }
                if (c == '>' || c == '<' || c == '=') {
                    if (in.peek() == '=') {
                        condition_str[condition_idx++] = c;
                        c = in.get(); 
                        condition_str[condition_idx++] = c;

                        s = 6;
                        break;
                    } else {
                        condition_str[condition_idx++] = c;

                        s = 6; 
                        break;
                    }
                }
                else { 
                    err_case = 3;
                    s = 100;
                } 
            }
            break;
        }
        case 4: {
        if (c == '>' || c == '<' || c == '=') {
            if (in.peek() == '=') {
                condition_str[condition_idx++] = c;
                c = in.get(); 
                condition_str[condition_idx++] = c;

                s = 6;
                break;
            } else {
                condition_str[condition_idx++] = c;

                s = 6; 
                break;
            }
        } 
        else if (isalpha(c) || isdigit(c)) {
            condition_str[condition_idx++] = c;
            count++; 
            if (count > m) { 
                err_case = 4;
                s = 100;
            }
            break;
        }
        else { 
            err_case = 4;
            s = 100;
            break;
        }
        }
        case 6: {
            condition_str[condition_idx++] = c;
            if (c == '+' || c == '-') {
                s = 21; 
            } else if (isdigit(c)) {
                count_dig = 1;
                s = 7; 
            } else if (isalpha(c)) {
                count = 1;
                s = 8; 
            } else { 
                err_case = 6;
                s = 100;
            }
            break;
        }
        case 21: { 
            condition_str[condition_idx++] = c;
            if (isdigit(c)) {
                count_dig = 1;
                s = 7; 
            } else { 
                err_case = 21;
                s = 100;
            }
            break;
        }
        case 7: { 
            if (isdigit(c)) {
                condition_str[condition_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 7;
                    s = 100;
                }
            } else if (c == '?') {
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 7;
                    s = 100;
                    break;
                } 
                condition_str[condition_idx] = '\0';
                condition_val = calculate_condition(condition_str, m, top);
                s = 9; 
            } else { 
                err_case = 7;
                s = 100;
            }
            break;
        }
        case 8: { 
            if (isalpha(c) || isdigit(c)) {
                condition_str[condition_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 8;
                    s = 100; 
                }
            } else if (c == '?') {
                condition_str[condition_idx] = '\0';
                condition_val = calculate_condition(condition_str, m, top);
                s = 9; 
            } else { 
                err_case = 8;
                s = 100;
            }
            break;
        }
        case 9: { 
            expr1_str[expr1_idx++] = c;
            if (c == '+' || c == '-') {
                current_op = c;
                s = 22; 
            } else if (isdigit(c)) {
                count_dig = 1; 
                s = 10; 
            } else if (isalpha(c)) {
                count = 1;
                s = 11; 
            } else { 
                err_case = 9;
                s = 100;
            }
            break;
        }
        case 22: { 
            if (isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count_dig = 1;
                s = 10; 
            }
            else { 
                err_case = 22;
                s = 100; 
            }
            break;
        }
        case 10: { 
            if (isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 10;
                    s = 100;
                }
            } 
            else { 
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 10;
                    s = 100;
                    break;
                }
                
                if (c == '+' || c == '-' || c == '*' || c == '/'){
                    expr1_str[expr1_idx++] = c;
                    current_op = c;
                    s = 12; 
                } 
                else if (c == ':') {
                    expr1_str[expr1_idx] = '\0';
                    expr1_value = calculate_expression(expr1_str, m, top);
                    s = 15; 
                }
                else { 
                    err_case = 10;
                    s = 100;
                }
            }
            break;
        }
        case 11: { 
            if (isalpha(c) || isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 11;
                    s = 100; 
                }
            } else if (c == '+' || c == '-' || c == '*' || c == '/') {
                expr1_str[expr1_idx++] = c;
                current_op = c;
                s = 12; 
            } else if (c == ':') {
                expr1_str[expr1_idx] = '\0';
                expr1_value = calculate_expression(expr1_str, m, top);
                s = 15; 
            } else { 
                err_case = 11;
                s = 100;
            }
            break;
        }
        case 12: {
            expr1_str[expr1_idx++] = c;
            if (c == '+' || c == '-') {
                current_op = c;
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
            else { 
                err_case = 12;
                s = 100;
            }
            break;
        }
        case 23: { 
            if (isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count_dig = 1;
                s = 13; 
            } 
            else { 
                err_case = 23;
                s = 100;
            }
            break;
        }
        case 13: { 
            if (isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 13;
                    s = 100;
                }
            }
            else if (c == ':') {
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 13;
                    s = 100;
                    break;
                } 
                expr1_str[expr1_idx] = '\0';
                expr1_value = calculate_expression(expr1_str, m, top);
                s = 15; 
            }
            else { 
                err_case = 13;
                s = 100;
            }
            break; 
        }
        case 14: { 
            if (isalpha(c) || isdigit(c)) {
                expr1_str[expr1_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 14;
                    s = 100;
                }
            }
            else if (c == ':') {
                expr1_str[expr1_idx] = '\0';
                expr1_value = calculate_expression(expr1_str, m, top);
                s = 15; 
            }
            else { 
                err_case = 14;
                s = 100;
            }
            break;
        } 
        case 15: { 
            expr2_str[expr2_idx++] = c;
            if (c == '+' || c == '-') {
                current_op = c;
                s = 24; 
            } else if (isdigit(c)) { 
                count_dig = 1; 
                s = 16; 
            } else if (isalpha(c)) {
                count = 1; 
                s = 17; 
            } else { 
                err_case = 15;
                s = 100;
            }
            break;
        }
        case 24: {
            if (isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count_dig = 1;
                s = 16; 
            } else { 
                err_case = 24;
                s = 100;
            }
            break;
        }
        case 16: { 
            if (isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 16;
                    s = 100;
                }
            }
            else { 
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 16;
                    s = 100;
                    break;
                }
                
                if (c == '+' || c == '-' || c == '*' || c == '/') {
                    expr2_str[expr2_idx++] = c;
                    current_op = c;
                    s = 18; 
                }
                else if (c == ';') {
                    expr2_str[expr2_idx] = '\0';
                    expr2_value = calculate_expression(expr2_str, m, top);
                    s = 25; 
                }
                else { 
                    err_case = 16;
                    s = 100;
                }
            }
            
            break;
        }
        case 17: { 
            if (isalpha(c) || isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 17;
                    s = 100;
                }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                expr2_str[expr2_idx++] = c;
                current_op = c;
                s = 18; 
            }
            else if (c == ';') {
                expr2_str[expr2_idx] = '\0';
                expr2_value = calculate_expression(expr2_str, m, top);
                s = 25; 
            }
            else { 
                err_case = 17;
                s = 100;
            }
            break;
        }
        case 18: { 
            expr2_str[expr2_idx++] = c;
            if (c == '+' || c == '-') {
                current_op = c;
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
            else { 
                err_case = 18;
                s = 100;
            }
            break;
        }
        case 26: { 
            if (isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count_dig = 1;
                s = 19; 
            } 
            else { 
                err_case = 26;
                s = 100;
            }
            break;
        }
        case 19: { 
            if (isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count_dig++; 
                if (count_dig > SIZE_DIGIT) { 
                    err_case = 19;
                    s = 100;
                }
            }
            else if (c == ';') {
                if (count_dig != SIZE_DIGIT) { 
                    err_case = 19;
                    s = 100;
                    break;
                } 
                expr2_str[expr2_idx] = '\0';
                expr2_value = calculate_expression(expr2_str, m, top);
                s = 25; 
            }
            else { 
                err_case = 19;
                s = 100;
            }
            break;
        }
        case 27: {
            if (isalpha(c) || isdigit(c)) {
                expr2_str[expr2_idx++] = c;
                count++; 
                if (count > m) { 
                    err_case = 27;
                    s = 100;
                }
            }
            else if (c == ';') {
                expr2_str[expr2_idx] = '\0';
                expr2_value = calculate_expression(expr2_str, m, top);
                s = 25; 
            }
            else { 
                err_case = 27;
                s = 100;
            }
            break;
        }
       
        case 25: {
            // Если мы сюда дошли, значит предыдущая команда успешно завершилась
            // и был прочитан символ 'c' (который уже обработан в начале цикла).
            
            // Если достигнут конец файла, завершаем успешно
            if (in.eof()) return true; 
            
            // Если s=25, но in.get(c) не вернул EOF,
            // мы вернемся в начало цикла, где s=25 сбросится в s=0
            
            break;
        }  
        case 100: {
            cout << "false in " << err_case << endl;
            return false;
        }
        default: {
            cout << "false in default " << s << endl;
            return false;
        }

        }
    }
    
    // Если цикл завершился (EOF), проверяем, была ли последняя команда завершена
    return s == 25;
}

int main() {
    int m;
    cout << "Enter m (2-4): \n";
    if (!(cin >> m)) {
        cerr << "Err: m is not entered\n";
        return 1;
    }
    if (m < 2 || m > 4) {
        cerr << "Err: m must be 2 or 3 or 4\n";
        return 1;
    }

    ifstream in("operator.txt"); 
    if (!in.is_open()) {
        cerr << "Err: open input file (operator.txt)\n" << endl;
        return 1;
    }

    char ident[MAX_IDENT_LENGTH + 1] = {0}; 
    bool condition_val = false;
    int expr1_value = 0;
    int expr2_value = 0;

    VariableNode* top = nullptr; // Инициализация списка переменных

    bool isValid = true;
    while (isValid && !in.eof()) {
        if (task(in, m, ident, condition_val, expr1_value, expr2_value, top)) {
            cout << "\n--- Command successful ---" << endl;
            
            int final_result = condition_val ? expr1_value : expr2_value;
            
            // Установка значения переменной, если команда была валидна
            set_variable_value(top, ident, final_result, m); // Обновляем значение

            cout << "Condition result: " << (condition_val ? "true" : "false") << endl;
            cout << "Expression 1 value: " << expr1_value << endl;
            cout << "Expression 2 value: " << expr2_value << endl;
            cout << "Final result for " << ident << ": " << final_result << endl; 
            
        } else {
            isValid = false;
        }
    }

    cout << (isValid ? "\n All expressions are valid" : "\n Expression is not valid");

    if (isValid) {
        cout << "\n\n=== Final State of Variables ===" << endl;
        VariableNode* current = top;
        if (current == nullptr) {
            cout << "No variables assigned." << endl;
        } else {
            while(current != nullptr) {
                cout << "**" << current->name << "** = " << current->value << endl;
                current = current->next;
            }
        }
        cout << "======================================" << endl;
    }

    in.close();
    clear_variable_list(top);

    return 0;
}