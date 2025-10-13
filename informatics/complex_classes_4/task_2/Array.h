#pragma once

#include "Rac.h"

Rac* create_array(int n);
bool enter_array(Rac* array, int n);
void output_array(Rac* array, int n);
Rac* scalar_multiplication(Rac* array1, Rac* array2, int n);
void delete_array(Rac* array);
