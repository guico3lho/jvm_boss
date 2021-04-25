/** @file frame.cpp
 *  @brief Inicia o Frame de execução com vetor de variáveis locais, operandos,
 *        contador de programa e ponteiro para pool de constantes.
 */

#include "frame.hpp"
#include "instructions/instructions_constant.hpp"
#include "instructions/instructions_load.hpp"
#include "instructions/instructions_store.hpp"
#include "instructions/instructions_math.hpp"
#include "instructions/instructions_stack.hpp"
#include "instructions/instructions_conversion.hpp"
#include "instructions/instructions_comparison.hpp"
#include "instructions/instructions_reference.hpp"
#include "instructions/instructions_control.hpp"
#include "instructions/instructions_extended.hpp"
#include "interpreter.hpp"

void (*func[256])(Frame *curr_frame);

/** @brief Construtor do Frame.
*   Constrói o Frame com as informações gerais da classe
*   (cp_reference), (class_file_ref), informações de método (method_info),
*   código do método (method_code), inica PC com 0 e redimensiona o vetor de variáveis locais.
*  @param method ponteiro para informações do método
*  @param cp_info ponteiro para a pool de constantes
*/
Frame::Frame(Method_Info *method, Class_File class_file) {
  cp_reference = class_file.constant_pool;
  class_file_ref = &class_file;
  method_info = method;
  pc = 0;

  // if (DEBUG) printf("Frame::Frame - Magic Number: 0x%0X\n", class_file_ref->magic_number);

  // Pega referencia do atributo de codigo do metodo
  for (int i = 0; i < method_info->attributes_count; ++i)
  {
    Attribute_Info attribute_info = method_info->attributes[i];
    std::string class_string = get_cp_info_utf8(*class_file_ref, attribute_info.attribute_name_index);

    if (class_string == "Code")
      method_code = attribute_info.code;
  }

  local_variables_array.resize(method_code->max_locals);
}

/**
 * @brief Executa Frame atual a partir do opcode armazanado no atributo de código na posição do pc do Frame
 * @param void
 * @return void
 */
void Frame::execute_frame() {
  u1 op_code = method_code->code[pc]; // NOTE: method_code armazena os opcode
  if (DEBUG)
    printf("\n[%d]", op_code); //NOTE: max_locals = 4? 4 variaveis?
  func[op_code](this);         // chama a funcao do respectivo indice opcode // seg fault aqui
}

/**
* @brief Retira um elemento do topo da pilha
* @return Operand* ponteiro para operando retirado
*/
Operand *Frame::pop_operand() {
  Operand *op = operand_stack.top();
  // printf("[operand popped]: %d\n", curr_frame->operand_stack.top()->type_int);
  operand_stack.pop();
  return op;
}

/**
* @brief Empilha um elemento na pilha de operandos
* @return Operand* ponteiro para elemento a ser inserido
* @return void
*/
void Frame::push_operand(Operand *op) {
  operand_stack.push(op);
  // printf("[operand pushed]: %d\n", curr_frame->operand_stack.top()->type_int);
}

/**
* @brief Cria um ponteiro de cópia do mesmo tipo que ele está recebendo para
* não utilizar a mesma instância.
* @param original_type ponteiro para tipo de entrada
* @return Operand* ponteiro para cópia do tipo de entrada
*/
Operand *copy_operand(Operand *original_type) {
  Operand *copy_type = (Operand *)malloc(sizeof(Operand));
  copy_type->tag = original_type->tag;

  switch (original_type->tag)
  {
  case CONSTANT_BYTE:
    copy_type->type_byte = original_type->type_byte;
    break;

  case CONSTANT_CHAR:
    copy_type->type_char = original_type->type_char;
    break;

  case CONSTANT_SHORT:
    copy_type->type_short = original_type->type_short;
    break;

  case CONSTANT_INT:
    copy_type->type_int = original_type->type_int;
    break;

  case CONSTANT_FLOAT:
    copy_type->type_float = original_type->type_float;
    break;

  case CONSTANT_LONG:
    copy_type->type_long = original_type->type_long;
    break;

  case CONSTANT_DOUBLE:
    copy_type->type_double = original_type->type_double;
    break;

  case CONSTANT_STRING:
    copy_type->type_string = new std::string(*original_type->type_string);
    break;

  case CONSTANT_CLASS:
    copy_type->class_container = (Class_Container*) malloc(sizeof(Class_Container));
    copy_type->class_container->class_file = original_type->class_container->class_file;
    copy_type->class_container->class_fields = new std::map<std::string, Operand *>();
    copy_type->class_container->class_fields = original_type->class_container->class_fields;
    break;

  case CONSTANT_ARRAY:
    copy_type->array_type = (Array_Type *)malloc(sizeof(Array_Type));
    copy_type->array_type->array = new std::vector<Operand *>();

    for (int i = 0; (unsigned)i < original_type->array_type->array->size(); i++)
    {
      Operand *aux = original_type->array_type->array->at(i);
      Operand *value = copy_operand(aux);
      copy_type->array_type->array->emplace_back(value);
    }
    break;
  }
  return copy_type;
}

/** @brief Inicia vetor de funções das instruções assembly.
*  @return void
*/
void Frame::set_instructions_functions() {

  /* CONSTANTS */
  func[0] = nop;
  func[1] = aconst_null;
  func[2] = iconst_m1;
  func[3] = iconst_0;
  func[4] = iconst_1;
  func[5] = iconst_2;
  func[6] = iconst_3;
  func[7] = iconst_4;
  func[8] = iconst_5;
  func[9] = lconst_0;
  func[10] = lconst_1;
  func[11] = fconst_0;
  func[12] = fconst_1;
  func[13] = fconst_2;
  func[14] = dconst_0;
  func[15] = dconst_1;
  func[16] = bipush;
  func[17] = sipush;
  func[18] = ldc;
  func[19] = ldc_w;
  func[20] = ldc2_w;

  /* LOADS */
  func[21] = iload;
  func[22] = lload;
  func[23] = fload;
  func[24] = dload;
  func[25] = aload;
  func[26] = iload_0;
  func[27] = iload_1;
  func[28] = iload_2;
  func[29] = iload_3;
  func[30] = lload_0;
  func[31] = lload_1;
  func[32] = lload_2;
  func[33] = lload_3;
  func[34] = fload_0;
  func[35] = fload_1;
  func[36] = fload_2;
  func[37] = fload_3;
  func[38] = dload_0;
  func[39] = dload_1;
  func[40] = dload_2;
  func[41] = dload_3;
  func[42] = aload_0;
  func[43] = aload_1;
  func[44] = aload_2;
  func[45] = aload_3;
  func[46] = iaload;
  func[47] = laload;
  func[48] = faload;
  func[49] = daload;
  func[50] = aaload;
  func[51] = baload;
  func[52] = caload;
  func[53] = saload;

  /* STORES */
  func[54] = istore;
  func[55] = lstore;
  func[56] = fstore;
  func[57] = dstore;
  func[58] = astore;
  func[59] = istore_0;
  func[60] = istore_1;
  func[61] = istore_2;
  func[62] = istore_3;
  func[63] = lstore_0;
  func[64] = lstore_1;
  func[65] = lstore_2;
  func[66] = lstore_3;
  func[67] = fstore_0;
  func[68] = fstore_1;
  func[69] = fstore_2;
  func[70] = fstore_3;
  func[71] = dstore_0;
  func[72] = dstore_1;
  func[73] = dstore_2;
  func[74] = dstore_3;
  func[75] = astore_0;
  func[76] = astore_1;
  func[77] = astore_2;
  func[78] = astore_3;
  func[79] = iastore;
  func[80] = lastore;
  func[81] = fastore;
  func[82] = dastore;
  func[83] = aastore;
  func[84] = bastore;
  func[85] = castore;
  func[86] = sastore;

  /* STACK */
  func[87] = pop;
  func[88] = pop2;
  func[89] = dup;
  func[90] = dup_x1;
  func[91] = dup_x2;
  func[92] = dup2;
  func[93] = dup2_x1;
  func[94] = dup2_x2;
  func[95] = swap;

  /* MATH */
  func[96] = iadd;
  func[97] = ladd;
  func[98] = fadd;
  func[99] = dadd;
  func[100] = isub;
  func[101] = lsub;
  func[102] = fsub;
  func[103] = dsub;
  func[104] = imul;
  func[105] = lmul;
  func[106] = fmul;
  func[107] = dmul;
  func[108] = idiv;
  func[109] = ldiv;
  func[110] = fdiv;
  func[111] = ddiv;
  func[112] = irem;
  func[113] = lrem;
  func[114] = frem;
  func[115] = drem;
  func[116] = ineg;
  func[117] = lneg;
  func[118] = fneg;
  func[119] = dneg;
  func[120] = ishl;
  func[121] = lshl;
  func[122] = ishr;
  func[123] = lshr;
  func[124] = iushr;
  func[125] = lushr;
  func[126] = iand;
  func[127] = land;
  func[128] = ior;
  func[129] = lor;
  func[130] = ixor;
  func[131] = lxor;

  /* CONVERSIONS */
  func[132] = iinc;
  func[133] = i2l;
  func[134] = i2f;
  func[135] = i2d;
  func[136] = l2i;
  func[137] = l2f;
  func[138] = l2d;
  func[139] = f2i;
  func[140] = f2l;
  func[141] = f2d;
  func[142] = d2i;
  func[143] = d2l;
  func[144] = d2f;
  func[145] = i2b;
  func[146] = i2c;
  func[147] = i2s;

  /* COMPARISONS */
  // func[148] = lcmp;
  // func[149] = fcmpl;
  // func[150] = fcmpg;
  // func[151] = dcmpl;
  // func[152] = dcmpg;
  func[153] = ifeq;
  func[154] = ifne;
  func[155] = iflt;
  func[156] = ifge;
  func[157] = ifgt;
  func[158] = ifle;
  func[159] = if_icmpeq;
  func[160] = if_icmpne;
  func[161] = if_icmplt;
  func[162] = if_icmpge;
  func[163] = if_icmpgt;
  func[164] = if_icmple;
  func[165] = if_acmpeq;
  func[166] = if_acmpne;

  /* CONTROL */
  func[167] = ins_goto;
  // func[168] = jsr;
  func[169] = ret;
  func[170] = tableswitch;
  func[171] = lookupswitch;
  func[172] = ireturn;
  func[173] = lreturn;
  func[174] = freturn;
  func[175] = dreturn;
  func[176] = areturn;
  func[177] = void_return;

  /* REFERENCES */
  func[178] = getstatic;
  // func[179] = putstatic;
  func[180] = getfield;
  func[181] = putfield;
  func[182] = invokevirtual;
  func[183] = invokespecial;
  func[184] = invokestatic;
  func[185] = invokeinterface;
  //func[186] = invokedynamic;
  func[187] = new_obj; //* new
  func[188] = newarray;
  func[189] = anewarray; 
  func[190] = arraylength;
  //func[191] = athrow;
  // func[192] = checkcast;
  // func[193] = instanceof;
  //func[194] = monitorenter;
  //func[195] = monitorexit;

  /* EXTENDED */
  // func[196] = wide;
  func[197] = multianewarray; // TODO
  func[198] = ifnull;
  func[199] = ifnonnull;
  // func[200] = goto_w;
  // func[201] = jsr_w;
}