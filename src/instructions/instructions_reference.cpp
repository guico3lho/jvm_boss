/** @file instructions_reference.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo referência da JVM.
*/

#include "interpreter.hpp"

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

    u2 index = curr_frame->method_code->code[curr_frame->pc++];
    index = (index << 8) + curr_frame->method_code->code[curr_frame->pc++];

    Cp_Info &field_info = curr_frame->cp_reference[index];
    Cp_Info &name_and_type = curr_frame->cp_reference[field_info.Fieldref.name_and_type_index];
    // string class_name = get_cp_info_utf8(*(curr_frame->class_file_ref), field_info.Fieldref.class_index);
    string class_name = get_utf8_constant_pool(curr_frame->cp_reference, field_info.Fieldref.class_index);

    // se for a classe default do Java: System -> nao empilhar
    if (class_name == "java/lang/System") {
      if (DEBUG) cout << "Java Default Class: java/lang/System" << "\n";
      return;
    }

    Class_File class_file = get_class_info_and_load_not_exists(class_name);
    string var_name = get_cp_info_utf8(class_file, name_and_type.NameAndType.name_index);
    Operand *static_field = get_static_field_of_class(class_name, var_name);

    curr_frame->push_operand(static_field);
}

/** @brief ...
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void getfield(Frame *curr_frame) {
  u1 byte1 = curr_frame->method_code->code[curr_frame->pc++];
  u1 byte2 = curr_frame->method_code->code[curr_frame->pc++];

  u2 index = (byte1 << 8) | byte2;

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
    curr_frame->pc++;

    u2 index = curr_frame->method_code->code[curr_frame->pc++];
    index = (index<<8) + curr_frame->method_code->code[curr_frame->pc++];
    Cp_Info field_reference = curr_frame->cp_reference[index];

    Cp_Info name_and_type = curr_frame->cp_reference[field_reference.Fieldref.class_index];

    string class_name = get_utf8_constant_pool(curr_frame->cp_reference, field_reference.Fieldref.class_index);
    string var_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);

    Operand *var_operand = curr_frame->pop_operand();
    Operand *class_instance = curr_frame->pop_operand();

    Operand *class_variable = class_instance->class_loader->class_fields->at(var_name);

    switch (var_operand->tag) {
        case CONSTANT_INT:
            class_variable->type_int = var_operand->type_int;
            break;
        case CONSTANT_LONG:
            class_variable->type_long = var_operand->type_long;
            break;
        case CONSTANT_BOOL:
            class_variable->type_bool = var_operand->type_bool;
            break;
        case CONSTANT_CHAR:
            class_variable->type_char = var_operand->type_char;
            break;
        case CONSTANT_SHORT:
            class_variable->type_short = var_operand->type_short;
            break;
        case CONSTANT_BYTE:
            class_variable->type_byte = var_operand->type_byte;
            break;
        case CONSTANT_FLOAT:
            class_variable->type_float = var_operand->type_float;
            break;
        case CONSTANT_DOUBLE:
            class_variable->type_double = var_operand->type_double;
            break;
        case CONSTANT_STRING:
            class_variable->type_string = var_operand->type_string;
            break;
        case CONSTANT_CLASS:
            class_variable->class_loader = var_operand->class_loader;
            break;
        case CONSTANT_ARRAY:
            class_variable->array_type = var_operand->array_type;
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

  Cp_Info &method_ref = curr_frame->cp_reference[index];
  Cp_Info &name_and_type = curr_frame->cp_reference[method_ref.Methodref.name_and_type_index];

  // * Utilizando o Cp_Info
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, method_ref.Methodref.class_index);
  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
  string method_desc = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);

  if (strstr(class_name.c_str(), "java/")) {
    if (class_name == "java/io/PrintStream" && (method_name == "println" || method_name == "print")) {
      if (method_desc != "()V") {
        if (DEBUG) cout << "CHEGOU AQUI - java/io/PrintStream\n";
        Operand *op = curr_frame->pop_operand();

        switch(op->tag) {
          case CONSTANT_BYTE:
              if (DEBUG) cout << "CONSTANT_BYTE: ";
              cout << (int) op->type_byte;
              break;
          case CONSTANT_CHAR:
              if (DEBUG) cout << "CONSTANT_CHAR: ";
              cout << (char) op->type_char;
              break;
          case CONSTANT_SHORT:
              if (DEBUG) cout << "CONSTANT_SHORT: ";
              cout << (short) op->type_short;
              break;
          case CONSTANT_BOOL:
              if (DEBUG) cout << "CONSTANT_BOOL: ";
              cout << (bool) op->type_bool;
              break;
          case CONSTANT_STRING:
              if (DEBUG) cout << "CONSTANT_STRING: ";
              cout << *op->type_string;
              break;
          case CONSTANT_INT:
              if (DEBUG) cout << "CONSTANT_INT: ";
              cout << (u4) op->type_int;
              break;
          case CONSTANT_FLOAT: {
              float float_v;
              memcpy(&float_v, &op->type_float, sizeof(float));
              if (DEBUG) cout << "CONSTANT_FLOAT: ";
              printf("%f", float_v); }
              break;
          case CONSTANT_LONG:
              if (DEBUG) cout << "CONSTANT_LONG: ";
              cout << (long) op->type_long;
              break;
          case CONSTANT_DOUBLE: {
              double double_v;
              memcpy(&double_v, &op->type_double, sizeof(double));
              if (DEBUG) cout << "CONSTANT_DOUBLE: ";
              printf("%.15lf", double_v); }
              break;
          case CONSTANT_EMPTY:
              printf("null");
              break;
          case CONSTANT_CLASS: {
              Class_Loader *class_loader = op->class_loader;
              Class_File class_file = class_loader->class_file;
              string this_class_name = get_cp_info_utf8(class_file, class_file.this_class);
              cout << this_class_name << "@" << class_loader;
          }
          break;
        }
        if (method_name == "println") {
          printf("\n");
        }
      }
    } else if (class_name == "java/lang/String" && method_name == "length") {
        if (DEBUG) cout << "CHEGOU AQUI - java/lang/String\n";

        Operand *str_ref = curr_frame->pop_operand();

        Operand *str_len = (Operand*) malloc(sizeof(Operand));
        str_len->tag = CONSTANT_INT;
        str_len->type_int = str_ref->type_string->size();
        curr_frame->push_operand(str_len);

    } else if (class_name == "java/lang/StringBuilder" && method_name == "append") {
        if (DEBUG) cout << "CHEGOU AQUI - java/lang/StringBuilder\n";

        Operand *t_append = curr_frame->pop_operand();
        Operand *str_append = copy_operand(curr_frame->pop_operand());

        switch (t_append->tag) {
            case CONSTANT_STRING:
                *str_append->type_string += (*t_append->type_string);
                break;
            case CONSTANT_INT:
                *str_append->type_string += (
                                    patch::to_string(t_append->type_int));
                break;
            case CONSTANT_LONG:
                *str_append->type_string += (
                                    patch::to_string(t_append->type_long));
                break;
            case CONSTANT_FLOAT:
                *str_append->type_string += (
                                  patch::to_string(t_append->type_float));
                break;
            case CONSTANT_DOUBLE:
                *str_append->type_string += (
                                  patch::to_string(t_append->type_double));
                break;
            case CONSTANT_SHORT:
                *str_append->type_string += (
                                    patch::to_string(t_append->type_short));
                break;
            case CONSTANT_CHAR:
                *str_append->type_string += (
                                    patch::to_string(t_append->type_char));
                break;
            case CONSTANT_BYTE:
                *str_append->type_string += (
                                    patch::to_string(t_append->type_byte));
                break;
            case CONSTANT_BOOL:
                if (t_append->type_bool == 0)
                    *str_append->type_string += "false";
                else
                    *str_append->type_string += "true";
                break;
            case CONSTANT_CLASS:
                // @TODO colocar enderec
                *str_append->type_string += *t_append->class_loader->class_name+"@";
                break;
            case CONSTANT_ARRAY:
                *str_append->type_string += "Array[]";
                break;
        }
        curr_frame->push_operand(str_append);
    } else if (class_name == "java/lang/StringBuilder") {
      // ignorando o toString;
      return;
    }
  } else {
      int qtde_arg = 0;
      u2 counter = 1;

      while (method_desc[counter] != ')') {
          char found_type = method_desc[counter];
          if (found_type == 'L') { // tipo é um objeto
              qtde_arg++;
              while (method_desc[++counter] != ';');

          } else if (found_type == '[') { // tipo é um array?
              qtde_arg++;
              while (method_desc[++counter] == '[');

              if (method_desc[counter] == 'L')
                  while (method_desc[++counter] != ';');
          } else qtde_arg++;
          counter++;
      }
      std::vector<Operand*> args;

    for (int i = 0; i < qtde_arg; ++i) {
      Operand *arg = curr_frame->pop_operand();
      args.insert(args.begin(), arg);
      if (arg->tag == CONSTANT_DOUBLE || arg->tag == CONSTANT_LONG)
          args.insert(args.begin()+1, check_string_create_type("P"));
    }

    Operand *current_class = curr_frame->pop_operand();
    args.insert(args.begin(), current_class);

    Class_Loader *class_loader = current_class->class_loader;

    Method_Info *method_info = find_method(class_loader->class_file, method_name, method_desc);
    Frame *new_frame = new Frame(method_info, (class_loader->class_file));

    for (int j = 0; (unsigned)j < args.size(); ++j)
        new_frame->local_variables_array.at(j) = args.at(j);

    push_frame(new_frame);
  }
}

/**
* @brief Invoca o método de instância, e trata da inicialiação da superclasse
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void invokespecial(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokespecial----------\n";

	//incrementa pc
	curr_frame->pc++;

	u2 index_method = curr_frame->method_code->code[curr_frame->pc];
	index_method = (index_method << 8) + curr_frame->method_code->code[++curr_frame->pc];

	Cp_Info &ref_method = curr_frame->cp_reference[index_method];
	Cp_Info &name_and_type = curr_frame->cp_reference[ref_method.Methodref.name_and_type_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, ref_method.Methodref.class_index);
	string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
	string method_descriptor = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);

  //incrementa pc
	curr_frame->pc++;

	if ( ((class_name == "java/lang/Object" || class_name == "java/lang/String")
      && method_name == "<init>") ||
		(class_name == "java/lang/StringBuilder" && method_name == "<init>")) {
		if (class_name == "java/lang/String" ||
        class_name == "java/lang/StringBuilder") {
			curr_frame->pop_operand();
		}
		else if (method_name == "<init>") {
			Operand *variable_class = curr_frame->local_variables_array.at(0);
			load_class_var(variable_class->class_loader);
		}
		return;

    } else if (class_name.find("java/") != string::npos) {
        printf("Classe java nao implementada.");
        getchar();
        exit(1); // caso seja algum outro tipo de classe java nao implementada
    } else {
        int count_args = 0;
        u2 counter = 1;

        while (method_descriptor[counter] != ')') {
            char created_type = method_descriptor[counter];
            if (created_type == 'L') { // tipo é um objeto
                count_args++;
                while (method_descriptor[++counter] != ';');
            } else if (created_type == '[') {
                count_args++;
                while (method_descriptor[++counter] == '[');
                if (method_descriptor[counter] == 'L')
                    while (method_descriptor[++counter] != ';');
            } else count_args++;
            counter++;
        }
        std::vector<Operand*> arguments;

        for (int i = 0; i < count_args; ++i) {
            Operand *argument = curr_frame->pop_operand();
            arguments.insert(arguments.begin(), argument);
            if (argument->tag == CONSTANT_DOUBLE ||
                argument->tag == CONSTANT_LONG) {
                arguments.insert(arguments.begin()+1, check_string_create_type("P"));
            }
        }

        Operand *current_class = curr_frame->pop_operand();
        arguments.insert(arguments.begin(), current_class);

        Class_Loader *reference_class = current_class->class_loader;

        Method_Info *method_info_found = find_method(reference_class->class_file, method_name, method_descriptor);
        Frame *new_frame = new Frame(method_info_found, reference_class->class_file);

        for (int j = 0; (unsigned)j < arguments.size(); ++j)
            new_frame->local_variables_array.at(j) = arguments.at(j);

        push_frame(new_frame);
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

  u2 method_index = curr_frame->method_code->code[curr_frame->pc++];
  method_index = (method_index << 8) + curr_frame->method_code->code[curr_frame->pc++];

  Cp_Info &method_info = curr_frame->cp_reference[method_index];
  Cp_Info &class_info = curr_frame->cp_reference[method_info.Methodref.class_index];

  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);

  Cp_Info &name_and_type = curr_frame->cp_reference[
                                  method_info.Methodref.name_and_type_index];

  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);

  if (DEBUG) cout << "nome do metodo a ser chamado: " << method_name << "\n";

  string method_descriptor = get_utf8_constant_pool(curr_frame->cp_reference,name_and_type.NameAndType.descriptor_index);

  if (DEBUG) cout << "nome da classe: " << class_name << "\n";
  if (class_name == "java/lang/Object" && method_name == "registerNatives") {
    printf("JVM não suporta método nativo.");
    return;
  }
  // calcula quantos argumentos o metodo tem
  int count_arguments = 0;
  u2 counter = 1;
  while (method_descriptor[counter] != ')') {
      char find_type = method_descriptor[counter];

      if (find_type == 'L') { // tipo objeto
          count_arguments++;
          while (method_descriptor[++counter] != ';');
      } else if (find_type == '[') { // tipo array
          count_arguments++;
          while (method_descriptor[++counter] == '[');
          if (method_descriptor[counter] == 'L')
              while(method_descriptor[++counter] != ';');
      } else count_arguments++;
      counter++;
  }

  if (DEBUG) cout << "metodo possui " << count_arguments << " argumentos\n";

  // não precisa criar frame para definir tipo float
  if (class_name.find("Float") != string::npos &&
      method_name.find("valueOf") != string::npos) {
        if (DEBUG) cout << "ignorar Float.valueOf\n";
        return;
  } else {
    std::vector<Operand*> arguments;

    if (DEBUG) cout << "passando argumentos para o metodo estatico\n";
    for (int i = 0; i < count_arguments; ++i) {
        Operand *argument = curr_frame->pop_operand();
        if (DEBUG) cout << "operando do tipo: " <<  (int)argument->tag << "\n";

        // passa argumento para a função
        arguments.insert(arguments.begin(), argument);
        if (argument->tag == CONSTANT_DOUBLE || argument->tag == CONSTANT_LONG)
            arguments.insert(arguments.begin() + 1,
                            check_string_create_type("P"));
    }

    Class_Loader *class_loader = get_static_class(class_name);
    Method_Info *method_finded = find_method(class_loader->class_file, method_name, method_descriptor);
    Frame *new_frame = new Frame(method_finded, class_loader->class_file);

    // vetor das variáveis locais
    for (int j = 0; (unsigned)j < arguments.size(); ++j)
        new_frame->local_variables_array.at(j) = arguments.at(j);

    push_frame(new_frame);
  }
}

/** @brief Invoca a interface do método.
@param Frame *curr_frame ponteiro que aponta para o frame atual
@return void
*/
void invokeinterface(Frame *curr_frame) {
  if (DEBUG) cout << "----------invokeinterface----------\n";

  curr_frame->pc++;

  u2 method_index = curr_frame->method_code->code[curr_frame->pc++];
  method_index = (method_index << 8) + curr_frame->method_code->code[curr_frame->pc++];

  Cp_Info &method_info = curr_frame->cp_reference[method_index];

  Cp_Info &class_info = curr_frame->cp_reference[method_info.Methodref.class_index];
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);

  Cp_Info &name_and_type = curr_frame->cp_reference[method_info.Methodref.name_and_type_index];
  string method_name = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.name_index);
  string method_descriptor = get_utf8_constant_pool(curr_frame->cp_reference, name_and_type.NameAndType.descriptor_index);
}

/**
 * @brief Cria novo array podendo ser de qualquer tipo.
 * @param Frame *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void new_obj(Frame *curr_frame) {
    curr_frame->pc++;
    u2 index = curr_frame->method_code->code[curr_frame->pc];
    index = (index << 8)+curr_frame->method_code->code[++curr_frame->pc];

    Cp_Info &class_info = curr_frame->cp_reference[index];
    string utf8_constant = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);


    if (utf8_constant == "java/lang/StringBuilder") {
        Operand* string_builder = (Operand*)malloc(sizeof(Operand));
        string_builder->tag = CONSTANT_STRING;
        string_builder->type_string = new string("");
        curr_frame->push_operand(string_builder);
    }else{
        Operand *instance = check_string_create_type("L" + utf8_constant);
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
  curr_frame->pc++;

  Operand *operand_1 = curr_frame->pop_operand();
  u4 index = operand_1->type_int;

  Operand *operand_2 = check_string_create_type("[");
  u1 array_type = curr_frame->method_code->code[curr_frame->pc++];

  switch ((int)array_type) {
    case 4:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("Z"));
      }
      break;
    case 5:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("C"));
      }
      break;
    case 6:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("F"));
      }
      break;
    case 7:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("D"));
      }
      break;
    case 8:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("B"));
      }
      break;
    case 9:
      for (int i = 0; i < (int) index; i++) {
        operand_2->array_type->array->emplace_back(check_string_create_type("S"));
      }
      break;
    case 10:
      if (DEBUG) cout << "array type int\n";
      for (int i = 0; i < (int) index; i++)
        operand_2->array_type->array->emplace_back(check_string_create_type("I"));
      break;
    case 11:
      if (DEBUG) cout << "array type long\n";
      for (int i = 0; i < (int) index; i++)
        operand_2->array_type->array->emplace_back(check_string_create_type("J"));
      break;
  }

  if (DEBUG) cout << "array size "
                      << operand_2->array_type->array->size() << "\n";

  curr_frame->push_operand(operand_2);

  if (DEBUG) cout << "newarray\n";
}

/**
 * @brief Cria novo objeto array.
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void anewarray(Frame *curr_frame) {}

void arraylength(Frame* curr_frame) {
  curr_frame->pc++;

  Operand *array = curr_frame->pop_operand();

  Operand *size = check_string_create_type("I");
  size->type_int = array->array_type->array->size();
  curr_frame->push_operand(size);
}
