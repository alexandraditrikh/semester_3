#include <iostream>
#include "Stack.h"
using namespace std;

// Создание нового узла стека
StackNode* create_new_stack_node(T node) {
    StackNode* new_node = new StackNode;
    new_node->elem = node;
    new_node->next = nullptr;
    return new_node;
}

// Инициализация стека (возвращает nullptr)
StackNode* init_stack() {
    return nullptr;
}

// Добавление элемента в стек (возвращает новый top)
void push_stack(StackNode*& top, T node) {  // Ссылка на указатель
    StackNode* new_stack_node = create_new_stack_node(node);
    new_stack_node->next = top;
    top = new_stack_node;  // Меняем оригинальный указатель
}

// Извлечение элемента из стека (возвращает новый top и элемент через ссылку)
T pop_stack(StackNode*& top) {  // Ссылка на указатель
    if (top == nullptr) return nullptr;
    
    StackNode* temp = top;
    T popped_element = top->elem;
    top = top->next;  // Меняем оригинальный top
    delete temp;
    return popped_element;
}

// Просмотр верхнего элемента без извлечения
T peek_stack(StackNode* top) {
    if (top == nullptr) {
        return nullptr;
    }
    return top->elem;
}

// Вывод содержимого стека (для отладки)
void print_stack(StackNode* top) {
    StackNode* current = top;
    cout << "Stack (top to bottom): ";
    while (current != nullptr) {
        cout << current->elem->value << " ";
        current = current->next;
    }
    cout << endl;
}
