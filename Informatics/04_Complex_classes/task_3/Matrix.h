#pragma once

#include "Rac.h"

void delete_matrix(Rac*** matrix, int n);
Rac*** create_matrix(int n);
bool enter_matrix(Rac*** matrix, int n);
Rac*** matrix_multiplication(Rac*** matrix1, Rac*** matrix2, int n);
Rac* finding_trace_matrix(Rac*** matrix, int n);
void print_matrix(Rac*** matrix, int n);