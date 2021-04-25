/** @file instructions_reference.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo referência da JVM.
*/

#include "interpreter.hpp"
#include "instructions/instructions_reference.hpp"


/**
 * @brief 
 */

namespace patch {
  template <typename T> string to_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

/*************************** REFERENCES ***************************/

/**
 * @brief Recebe um campo estático a partir de uma classe.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void getstatic(Frame *curr_frame) {
  if (DEBUG) cout << "----------getstatic----------\n";
  curr_frame->pc++;

  u2 index = get_method_code_index(curr_frame);

  Cp_Info field_info = curr_frame->cp_reference[index];
  Cp_Info name_and_type = curr_frame->cp_reference[field_info.Fieldref.name_and_type_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, field_info.Fieldref.class_index);

  // se for a classe default do Java: System -> nao empilhar
  if (class_name == "java/lang/System") {
    if (DEBUG) cout << "Classe Default Java: java/lang/System" << "\n";
    return;
  }

  Class_File class_file = load_parent_classes(class_name);
  string var_name = get_cp_info_utf8(class_file, name_and_type.NameAndType.name_index);
  Operand *static_field = get_static_field_of_class(class_name, var_name);

  curr_frame->push_operand(static_field);
}

/** @brief ...
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void getfield(Frame *curr_frame) {
  if (DEBUG) cout << "----------getfield----------\n";
  u2 index = get_method_code_index(curr_frame);

  Cp_Info field_ref = curr_frame->cp_reference[index];
  Cp_Info name_and_type = curr_frame->cp_reference[field_ref.Fieldref.class_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, field_ref.Fieldref.class_index);
  string field_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);

  curr_frame->operand_stack.pop();
  // curr_frame->push_operand(classVariable);
}

/**
 * @brief ...
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void putfield(Frame *curr_frame) {
  if (DEBUG) cout << "----------putfield----------\n";
  curr_frame->pc++;

  u2 index = get_method_code_index(curr_frame);

  Cp_Info field_reference = curr_frame->cp_reference[index];
  Cp_Info name_and_type = curr_frame->cp_reference[field_reference.Fieldref.class_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, field_reference.Fieldref.class_index);
  string var_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);

  Operand *operand = curr_frame->pop_operand();
  Operand *class_instance = curr_frame->pop_operand();

  Operand *class_variable = class_instance->class_container->class_fields->at(var_name);

  switch (operand->tag) {
    case CONSTANT_INT:
      class_variable->type_int = operand->type_int;
      break;
    case CONSTANT_LONG:
      class_variable->type_long = operand->type_long;
      break;
    case CONSTANT_BOOL:
      class_variable->type_bool = operand->type_bool;
      break;
    case CONSTANT_CHAR:
      class_variable->type_char = operand->type_char;
      break;
    case CONSTANT_SHORT:
      class_variable->type_short = operand->type_short;
      break;
    case CONSTANT_BYTE:
      class_variable->type_byte = operand->type_byte;
      break;
    case CONSTANT_FLOAT:
      class_variable->type_float = operand->type_float;
      break;
    case CONSTANT_DOUBLE:
      class_variable->type_double = operand->type_double;
      break;
    case CONSTANT_STRING:
      class_variable->type_string = operand->type_string;
      break;
    case CONSTANT_CLASS:
      class_variable->class_container = operand->class_container;
      break;
    case CONSTANT_ARRAY:
      class_variable->array_type = operand->array_type;
      break;
  }
}

/**
 * @brief Invoca instância de método baseado na classe.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void invokevirtual(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokevirtual----------\n";
  curr_frame->pc++;

  u2 index = curr_frame->method_code->code[curr_frame->pc] << 16;
  index += curr_frame->method_code->code[++curr_frame->pc];
  curr_frame->pc++;

  Cp_Info method_ref = curr_frame->cp_reference[index];
  Cp_Info name_and_type = curr_frame->cp_reference[method_ref.Methodref.name_and_type_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, method_ref.Methodref.class_index);
  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
  string method_desc = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);
  if (DEBUG) cout << "Nome da classe: " << class_name << "\n";
  if (DEBUG) cout << "Nome do metodo: " << method_name << "\n";
  if (DEBUG) cout << "Descricao do metodo: " << method_desc << "\n";

  // Caso classe default Java
  if (strstr(class_name.c_str(), "java/")) {

    // metodos de Print
    if (class_name == "java/io/PrintStream" && (method_name == "println" || method_name == "print") ) {

      if (method_desc != "()V") {
        invokevirtual_print(curr_frame);
      } 
      if (method_name == "println") printf("\n");
      
    } 

    // metodo String length
    if (class_name == "java/lang/String" && method_name == "length") {
      if (DEBUG) cout << "Metodo string: java/lang/String\n";

      Operand *str_ref = curr_frame->pop_operand();
      Operand *str_len = (Operand*) malloc(sizeof(Operand));

      str_len->tag = CONSTANT_INT;
      str_len->type_int = str_ref->type_string->size();
      curr_frame->push_operand(str_len);
    } 
    
    // Metodo StringBuilder append
    if (class_name == "java/lang/StringBuilder" && method_name == "append") {
      invokevirtual_string_builder_append(curr_frame);
    } 

  } else { // Caso classe nao default Java
    string invoke_type = "virtual";
    class_not_default_java(curr_frame, class_name, method_name, method_desc, invoke_type);
  }
}

/**
 * @brief Função dos metodos do tipo print da instrução invokevirtual (opcode 182)
 * 
 * @param *curr_frame 
 * @param method_name 
 */
void invokevirtual_print(Frame *curr_frame) {
  if (DEBUG) cout << "Metodo Print: java/io/PrintStream\n";
  Operand *op = curr_frame->pop_operand();
  if (DEBUG) cout << "op->tag: " << (int) op->tag << "\n";

  switch(op->tag) {
    case CONSTANT_EMPTY: // 0
      printf("null");
      break;
    case CONSTANT_INT: // 3
      if (DEBUG) cout << "CONSTANT_INT: ";
      printf("%d", op->type_int);
      break;
    case CONSTANT_FLOAT: { // 4
      float float_v;
      memcpy(&float_v, &op->type_float, sizeof(float));
      if (DEBUG) cout << "CONSTANT_FLOAT: ";
      printf("%.15f", float_v); 
    }
      break;
    case CONSTANT_LONG: // 5
      if (DEBUG) cout << "CONSTANT_LONG: ";
      cout << (long) op->type_long;
      break;
    case CONSTANT_DOUBLE: { // 6
      double double_v;
      memcpy(&double_v, &op->type_double, sizeof(double));
      if (DEBUG) cout << "CONSTANT_DOUBLE: ";
      printf("%.15lf", double_v); 
    }
      break;
    case CONSTANT_CLASS: { // 7
      Class_Container *class_container = op->class_container;
      Class_File class_file = class_container->class_file;
      string this_class_name = get_cp_info_utf8(class_file, class_file.this_class);
      cout << this_class_name << "@" << class_container;
    }
      break;
    case CONSTANT_STRING: //8
      if (DEBUG) cout << "CONSTANT_STRING: ";
      cout << *op->type_string;
      break;
    case CONSTANT_BOOL: // 90
      if (DEBUG) cout << "CONSTANT_BOOL: ";
      cout << (bool) op->type_bool;
      break;
    case CONSTANT_BYTE: // 91
      if (DEBUG) cout << "CONSTANT_BYTE: ";
      cout << (int) op->type_byte;
      break;
    case CONSTANT_CHAR: // 92
      if (DEBUG) cout << "CONSTANT_CHAR: ";
      cout << (char) op->type_char;
      break;
    case CONSTANT_SHORT: //93
      if (DEBUG) cout << "CONSTANT_SHORT: ";
      cout << (short) op->type_short;
      break;
    default:
      printf("\n");
      break;
  }
}

/**
 * @brief Função do metodo StringBuilder append da instrução invokevirtual (opcode 182)
 * 
 * @param curr_frame 
 */
void invokevirtual_string_builder_append(Frame *curr_frame) {
  if (DEBUG) cout << "Metodo StringBuilder: java/lang/StringBuilder\n";

  Operand *op_append = curr_frame->pop_operand();
  Operand *str_append = copy_operand(curr_frame->pop_operand());

  // converte tipo qualquer para tipo string - toString
  switch (op_append->tag) {
    case CONSTANT_STRING:
      *str_append->type_string += (*op_append->type_string);
      break;
    case CONSTANT_INT:
      *str_append->type_string += (patch::to_string(op_append->type_int));
      break;
    case CONSTANT_LONG:
      *str_append->type_string += (patch::to_string(op_append->type_long));
      break;
    case CONSTANT_FLOAT:
      *str_append->type_string += (patch::to_string(op_append->type_float));
      break;
    case CONSTANT_DOUBLE:
      *str_append->type_string += (patch::to_string(op_append->type_double));
      break;
    case CONSTANT_SHORT:
      *str_append->type_string += (patch::to_string(op_append->type_short));
      break;
    case CONSTANT_CHAR:
      *str_append->type_string += (patch::to_string(op_append->type_char));
      break;
    case CONSTANT_BYTE:
      *str_append->type_string += (patch::to_string(op_append->type_byte));
      break;
    case CONSTANT_BOOL:
      if (op_append->type_bool == 0)
        *str_append->type_string += "false";
      else
        *str_append->type_string += "true";
      break;
    case CONSTANT_CLASS: { 
      Class_Container *class_container = op_append->class_container;
      Class_File class_file = class_container->class_file;
      string this_class_name = get_cp_info_utf8(class_file, class_file.this_class);
      cout << this_class_name << "@" << class_container;
      *str_append->type_string += this_class_name + "@";
    }
      break;
    case CONSTANT_ARRAY:
      *str_append->type_string += "Array[]";
      break;
  }

  curr_frame->push_operand(str_append);
}

/**
 * @brief Função de método não default do Java das instruções de invoke 
 * 
 * @param *curr_frame 
 * @param class_name 
 * @param method_name 
 * @param method_desc 
 * @param invoke_type 
 * @return void
 */
void class_not_default_java(
  Frame *curr_frame, 
  string class_name, 
  string method_name, 
  string method_desc,
  string invoke_type
) {

  int count_args = count_method_arguments(method_desc);
  if (DEBUG) cout << "metodo possui " << count_args << " argumentos\n";

  std::vector<Operand*> args;
  if (DEBUG) cout << "passando argumentos para o metodo " << invoke_type << "\n";

  for (int i = 0; i < count_args; ++i) {
    Operand *arg = curr_frame->pop_operand();
    if (DEBUG) cout << "operando do tipo: " <<  (int) arg->tag << "\n";

    args.insert(args.begin(), arg);

    if (arg->tag == CONSTANT_DOUBLE || arg->tag == CONSTANT_LONG)
      args.insert(args.begin() + 1, check_string_create_type("P"));
  }

  Class_Container *class_container;

  if(invoke_type == "virtual" || invoke_type == "special") {
    Operand *current_class = curr_frame->pop_operand();
    args.insert(args.begin(), current_class);
    class_container = current_class->class_container;
  }

  if(invoke_type == "static") {
    class_container = get_static_class(class_name);
  }

  // Pega informacoes do metodo
  Method_Info *method_info = find_method(class_container->class_file, method_name, method_desc);
  Frame *new_frame = new Frame(method_info, class_container->class_file);

  for (int j = 0; (unsigned)j < args.size(); ++j)
    new_frame->local_variables_array.at(j) = args.at(j);

  push_frame(new_frame);
}

/**
 * @brief Conta quantidade de argumentos do metodo chamado
 * @param string method_descriptor
 * @return int 
 */
int count_method_arguments(string method_descriptor) {
  int count_args = 0;
  u2 counter = 1;

  while (method_descriptor[counter] != ')') {
    char found_type = method_descriptor[counter];

    if (found_type == 'L') { // tipo objeto
      count_args++;
      while (method_descriptor[++counter] != ';');
    } 

    if (found_type == '[') { // tipo array
      count_args++;
      while (method_descriptor[++counter] == '[');
      if (method_descriptor[counter] == 'L')
        while (method_descriptor[++counter] != ';');
    } else {
      count_args++;
    }
    counter++;
  }

  return count_args;
}

/**
* @brief Invoca o método de instância, e trata da inicialiação da superclasse
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void invokespecial(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokespecial----------\n";
	curr_frame->pc++;

	u2 method_index = curr_frame->method_code->code[curr_frame->pc];
	method_index = (method_index << 8) + curr_frame->method_code->code[++curr_frame->pc];

	Cp_Info method_ref = curr_frame->cp_reference[method_index];
	Cp_Info name_and_type = curr_frame->cp_reference[method_ref.Methodref.name_and_type_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, method_ref.Methodref.class_index);
	string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
	string method_desc = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);
	curr_frame->pc++;

  string class_object = "java/lang/Object";
  string class_string = "java/lang/String";
  string class_string_builder = "java/lang/StringBuilder";
  string method_init = "<init>";

	if ( ((class_name == class_object || class_name == class_string) && method_name == method_init) || 
      (class_name == class_string_builder && method_name == method_init)
  ) {
		if (class_name == class_string || class_name == class_string_builder) {
			curr_frame->pop_operand();
		} else if (method_name == method_init) {
			Operand *variable_class = curr_frame->local_variables_array.at(0);
			load_class_variables(variable_class->class_container);
		}
		return;
  } else {
    string invoke_type = "special";
    class_not_default_java(curr_frame, class_name, method_name, method_desc, invoke_type);
  }

  if (class_name.find("java/") != string::npos) {
    printf("Classe java nao implementada!");
    getchar();
    exit(1); // caso tipo de classe java nao implementada
  }
}

/**
 * @brief Invoca um método estático de uma classe.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void invokestatic(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokestatic----------\n";
  curr_frame->pc++;

  u2 index = get_method_code_index(curr_frame);

  Cp_Info method_info = curr_frame->cp_reference[index];
  Cp_Info class_info = curr_frame->cp_reference[method_info.Methodref.class_index];
  Cp_Info name_and_type = curr_frame->cp_reference[method_info.Methodref.name_and_type_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);
  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
  string method_desc = get_utf8_constant_pool(curr_frame->cp_reference,name_and_type.NameAndType.descriptor_index);

  if (DEBUG) cout << "Nome do metodo a ser chamado: " << method_name << "\n";
  if (DEBUG) cout << "Nome da classe: " << class_name << "\n";

  if (class_name == "java/lang/Object" && method_name == "registerNatives") {
    printf("JVM não suporta método nativo.");
    return;
  }

  // não precisa criar frame para definir tipo Integer
  if (class_name.find("Integer") != string::npos && method_name.find("valueOf") != string::npos) {
    if (DEBUG) cout << "Ignorando Integer.valueOf\n";
    return;
  } 

  // não precisa criar frame para definir tipo float
  if (class_name.find("Float") != string::npos && method_name.find("valueOf") != string::npos) {
    if (DEBUG) cout << "Ignorando Float.valueOf\n";
    return;
  } 

  string invoke_type = "static";
  class_not_default_java(curr_frame, class_name, method_name, method_desc, invoke_type);
}

/** @brief Invoca a interface do método.
@param Frame *curr_frame ponteiro que aponta para o frame atual
@return void
*/
void invokeinterface(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokeinterface----------\n";
  curr_frame->pc++;

  u2 index = get_method_code_index(curr_frame);

  Cp_Info method_info = curr_frame->cp_reference[index];
  Cp_Info class_info = curr_frame->cp_reference[method_info.Methodref.class_index];
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);

  Cp_Info name_and_type = curr_frame->cp_reference[method_info.Methodref.name_and_type_index];
  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
  string method_descriptor = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);
}

/**
 * @brief Cria novo array podendo ser de qualquer tipo.
 * @param Frame *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void new_obj(Frame *curr_frame) {
  if (DEBUG) cout << "----------new----------\n";
  curr_frame->pc++;

  u2 index = curr_frame->method_code->code[curr_frame->pc];
  index = (index << 8) + curr_frame->method_code->code[++curr_frame->pc];

  Cp_Info class_info = curr_frame->cp_reference[index];
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);

  if (class_name == "java/lang/StringBuilder") {
    Operand* string_builder = (Operand*) malloc(sizeof(Operand));
    string_builder->tag = CONSTANT_STRING;
    string_builder->type_string = new string("");
    curr_frame->push_operand(string_builder);
  } else {
    Operand *instance = check_string_create_type("L" + class_name);
    curr_frame->push_operand(instance);
  }
  curr_frame->pc++;
}

/**
 * @brief Cria novo array do tipo definido
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void newarray(Frame *curr_frame) {
  if (DEBUG) cout << "----------newarray----------\n";
  curr_frame->pc++;

  Operand *operand_1 = curr_frame->pop_operand();
  int count = operand_1->type_int;
  if (DEBUG) printf("array count: %d (0x%0X)\n", (int) count, count);

  u1 array_type = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "array_type: " << (int) array_type << "\n";

  Operand *operand_2 = check_string_create_type("[");

  switch ((int) array_type) {
    case 4:
      if (DEBUG) cout << "array type bool\n";
      set_newarray_type(operand_2, count, "Z");
      break;
    case 5:
      if (DEBUG) cout << "array type char\n";
      set_newarray_type(operand_2, count, "C");
      break;
    case 6:
      if (DEBUG) cout << "array type float\n";
      set_newarray_type(operand_2, count, "F");
      break;
    case 7:
      if (DEBUG) cout << "array type double\n";
      set_newarray_type(operand_2, count, "D");
      break;
    case 8:
      if (DEBUG) cout << "array type byte\n";
      set_newarray_type(operand_2, count, "B");
      break;
    case 9:
      if (DEBUG) cout << "array type short\n";
      set_newarray_type(operand_2, count, "S");
      break;
    case 10:
      if (DEBUG) cout << "array type int\n";
      set_newarray_type(operand_2, count, "I");
      break;
    case 11:
      if (DEBUG) cout << "array type long\n";
      set_newarray_type(operand_2, count, "J");
      break;
  }

  if (DEBUG) cout << "array size " << operand_2->array_type->array->size() << "\n";
  curr_frame->push_operand(operand_2);
}

/**
 * @brief Define o tipo de dado dos operandos do newarray 
 * 
 * @param operand_2 
 * @param index 
 */
void set_newarray_type(Operand *operand, u4 count, string array_type) {
  for (int i = 0; i < (int) count; i++) {
    operand->array_type->array->emplace_back(check_string_create_type(array_type));
  }
}

/**
 * @brief Cria novo objeto array.
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void anewarray(Frame *curr_frame) {
  if (DEBUG) cout << "----------anewarray----------\n";
  curr_frame->pc++;

  Operand *operand_1 = curr_frame->pop_operand();
  int count = operand_1->type_int;
  if (DEBUG) printf("array count: %d (0x%0X)\n", (int) count, count);

  u2 array_type = get_method_code_index(curr_frame);
  if (DEBUG) cout << "array_type: " << (int) array_type << "\n";

  Operand *operand = check_string_create_type("[");
  switch ((int) array_type) {
    case 0:
      // if (DEBUG) cout << "array type bool\n";
      // set_newarray_type(operand, count, "Z");
      break;
    case 1:
      // if (DEBUG) cout << "array type char\n";
      // set_newarray_type(operand, count, "C");
      break;
    case 2: // Caso tipo Classe
      if (DEBUG) cout << "array type Class\n";
      set_newarray_type(operand, count, "Ljava/lang/String;");
      break;
    case 3:
      // if (DEBUG) cout << "array type float\n";
      // set_newarray_type(operand, count, "F");
      break;
  }

  if (DEBUG) cout << "array size " << operand->array_type->array->size() << "\n";
  curr_frame->push_operand(operand);
}

void arraylength(Frame* curr_frame) {
  if (DEBUG) cout << "----------arraylength----------\n";
  curr_frame->pc++;

  Operand *array = curr_frame->pop_operand();

  Operand *size = check_string_create_type("I");
  size->type_int = array->array_type->array->size();
  curr_frame->push_operand(size);
}