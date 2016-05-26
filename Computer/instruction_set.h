/* plik włączający wszystkie dostępne instrukcje w języku PROSTAK */

#include "instruction.h"
/* przed plikiem "instruction.h" nie może zostać włączona klasa "computer.h" */
#include "computer.h"
#include "instruction_set/one_arg_instr.h"
#include "instruction_set/two_arg_instr.h"
#include "instruction_set/reg_reg_instr.h"
#include "instruction_set/set_instr.h"
#include "instruction_set/load_instr.h"
#include "instruction_set/store_instr.h"
#include "instruction_set/add_instr.h"
#include "instruction_set/sub_instr.h"
#include "instruction_set/mul_instr.h"
#include "instruction_set/div_instr.h"
#include "instruction_set/println_instr.h"