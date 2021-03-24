#include "../include/cp_info.hpp"

std::string get_utf8(Class_File class_file, u2 index)
{

    std::string utf8_text;
    u2 index_aux;

    switch (class_file.constant_pool[index].tag)
    {
    case CONSTANT_CLASS:
        index = class_file.constant_pool[index].Class_Info.class_name; // # 23
        utf8_text = get_utf8(class_file, index);                       // # <java/lag/System>
        break;

    case CONSTANT_FIELD_REF:
        index = class_file.constant_pool[index].Fieldref_Info.field_ref_class_ref; // 16
        utf8_text = get_utf8(class_file, index);                                   //

        break;

    case CONSTANT_METHOD_REF:

        break;

    case CONSTANT_INTERFACE_METHOD_REF:

        break;

    case CONSTANT_STRING:

        break;

    case CONSTANT_INT:

        break;

    case CONSTANT_FLOAT:

        break;

    case CONSTANT_LONG:

        break;

    case CONSTANT_DOUBLE:

        break;

    case CONSTANT_NAME_TYPE:
        index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_index;            
        utf8_text = get_utf8(class_file, index_aux);                                             
        index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_descriptor_index; 
        utf8_text += get_utf8(class_file, index_aux);                                            // # <Ljava/io/PrintStream;>

        break;

    case CONSTANT_UTF8:

        utf8_text = (char *)class_file.constant_pool[index].Utf8_Info.UTF8_bytes; //javaLangObject

        //
        break;
    }
    return utf8_text;
}
void print_cp_info(Class_File class_file)
{
    // 2 bugs
    // FIXME: índice ficando 0
    // FIXME: recebendo lixo na string da constant_pool[7]
    int count = class_file.constant_pool_count;
    for (int i = 1; i < count; i++) //7
    {

        std::string utf8_text;
        PRINT("\n-------------------------------------------------------------------\n");
        std::cout << "CP_INFO[" << i << "]" << std::endl;
        switch (class_file.constant_pool[i].tag)
        {
        case CONSTANT_CLASS:
            PRINT("CONSTANT_CLASS");
            std::cout << "Class index: #" << class_file.constant_pool[i].Class_Info.class_name << "\t\t"; // #21
            PRINT(get_utf8(class_file, class_file.constant_pool[i].Class_Info.class_name));               // HelloJava

            // i = class_file.constant_pool[i].Class_Info.class_name - 1;

            break;

        case CONSTANT_FIELD_REF:
            PRINT("CONSTANT_FIELD_REF");
            std::cout << "Class index: #" << class_file.constant_pool[i].Fieldref_Info.field_ref_class_ref << "\t\t"; // #16
            PRINT(get_utf8(class_file, class_file.constant_pool[i].Fieldref_Info.field_ref_class_ref));

            std::cout << "Name and Type: #" << class_file.constant_pool[i].Fieldref_Info.field_ref_name_type_descriptor << "\t\t";
            PRINT(get_utf8(class_file, class_file.constant_pool[i].Fieldref_Info.field_ref_name_type_descriptor));
            break;

        case CONSTANT_METHOD_REF:
            PRINT("CONSTANT_METHOD_REF");

            std::cout << "Class name index: #" << class_file.constant_pool[i].Methodref_Info.method_ref_index << "\t\t"; //19
            PRINT(get_utf8(class_file, class_file.constant_pool[i].Methodref_Info.method_ref_index));                    // java/lang/Object

            std::cout << "Name and Type: #" << class_file.constant_pool[i].Methodref_Info.method_ref_name_and_type << "\t\t"; //20
            PRINT(get_utf8(class_file, class_file.constant_pool[i].Methodref_Info.method_ref_name_and_type));                 // ()V
            //  i = class_file.constant_pool[i].Methodref_Info.method_ref_index - 1; //6
            // int index =

            //class_file.constant_pool[6]." ".classname = 22
            //class_File.constant_pool[22]." ".string = java/lang/Object
            break;

        case CONSTANT_INTERFACE_METHOD_REF:
            PRINT("CONSTANT_METHOD_REF");

            break;

        case CONSTANT_STRING:
            PRINT("CONSTANT_STRING");
            std::cout << "String: #" << class_file.constant_pool[i].String_Info.string_bytes << "\t\t"; // #18
            PRINT(get_utf8(class_file, class_file.constant_pool[i].String_Info.string_bytes));          // # Hello Java!

            break;

        case CONSTANT_INT:
            PRINT("CONSTANT_INT");

            std::cout << "Bytes: 0x" << intToHex(class_file.constant_pool[i].Integer_Info.int_bytes) << std::endl;
            std::cout << "Integer: " << class_file.constant_pool[i].Integer_Info.int_bytes << std::endl;

            break;

        case CONSTANT_FLOAT:
            PRINT("CONSTANT_FLOAT");
            std::cout << "Bytes: 0x" << intToHex(class_file.constant_pool[i].Float_Info.float_bytes) << std::endl;
            float float_num;
            memcpy(&float_num, &class_file.constant_pool[i].Float_Info.float_bytes, sizeof(float));
            std::cout << "Float: " << float_num << std::endl;
            break;

        case CONSTANT_LONG:
            PRINT("CONSTANT_LONG");
            std::cout << "High: 0x" << intToHex(class_file.constant_pool[i].Long_Info.long_high_bytes) << std::endl;
            std::cout << "Low: 0x" << intToHex(class_file.constant_pool[i].Long_Info.long_low_bytes) << std::endl;

            // u8 long_info;
            uint64_t long_value;
            long_value =
                ((uint64_t)class_file.constant_pool[i].Long_Info.long_high_bytes << 32) |
                class_file.constant_pool[i].Long_Info.long_low_bytes;

            long long_info;

            memcpy(&long_info, &long_value, sizeof(long));
            std::cout << "Long value:" << long_info << std::endl;

            break;

        case CONSTANT_DOUBLE:
            PRINT("CONSTANT_DOUBLE");
            std::cout << "High: 0x" << intToHex(class_file.constant_pool[i].Double_Info.double_high_bytes) << std::endl;
            std::cout << "Low: 0x" << intToHex(class_file.constant_pool[i].Double_Info.double_low_bytes) << std::endl;
            uint64_t double_value;
            double_value = ((uint64_t)class_file.constant_pool[i].Double_Info.double_high_bytes << 32) |
                           class_file.constant_pool[i].Double_Info.double_low_bytes;

            double double_info;
            memcpy(&double_info, &double_value, sizeof(long));

            std::cout << "Double value:" << double_info << std::endl;

            //TODO: Converter bytes para o número verdadeiro double
            //TODO: Converter número para hexadecimal
            break;

        case CONSTANT_NAME_TYPE:
            PRINT("CONSTANT_NAME_TYPE");

            std::cout << "Name:  " << class_file.constant_pool[i].NameAndType_Info.name_type_index << "\t\t"; // Name: #7
            PRINT(get_utf8(class_file, class_file.constant_pool[i].NameAndType_Info.name_type_index));

            std::cout << "Descriptor:  " << class_file.constant_pool[i].NameAndType_Info.name_type_descriptor_index << "\t\t"; // Descriptor: #8
            PRINT(get_utf8(class_file, class_file.constant_pool[i].NameAndType_Info.name_type_descriptor_index));

            break;

        case CONSTANT_UTF8:
            PRINT("CONSTANT_UTF8");
            std::cout << "Length:  " << class_file.constant_pool[i].Utf8_Info.UTF8_size << std::endl; // #6
            std::cout << "String: " << class_file.constant_pool[i].Utf8_Info.UTF8_bytes << std::endl; // #6
            break;

        default:
            PRINT("(large numeric continued)");

            break;
        }
    }
}
void cp_info_reader(Class_File class_file, FILE *file)
{
    int count = class_file.constant_pool_count;
    for (int i = 1; i < count; i++)
    {
        // tenho o constant pool count, quero ler de cada um, pra isso preciso ler o próximo?
        u2 tag = read_1_byte(file);
        class_file.constant_pool[i].tag = tag;

        switch (tag)
        {
        case CONSTANT_CLASS:
            class_file.constant_pool[i].Class_Info.class_name = read_2_bytes(file);
            break;

        case CONSTANT_FIELD_REF:
            class_file.constant_pool[i].Fieldref_Info.field_ref_class_ref = read_2_bytes(file);
            class_file.constant_pool[i].Fieldref_Info.field_ref_name_type_descriptor = read_2_bytes(file);
            break;

        case CONSTANT_METHOD_REF:
            class_file.constant_pool[i].Methodref_Info.method_ref_index = read_2_bytes(file);

            class_file.constant_pool[i].Methodref_Info.method_ref_name_and_type = read_2_bytes(file);
            break;

        case CONSTANT_INTERFACE_METHOD_REF:
            class_file.constant_pool[i].InterfaceMethodref_Info.interface_method_ref_index = read_2_bytes(file);
            class_file.constant_pool[i].InterfaceMethodref_Info.interface_method_ref_name_type = read_2_bytes(file);
            break;

        case CONSTANT_STRING:
            class_file.constant_pool[i].String_Info.string_bytes = read_2_bytes(file);
            break;

        case CONSTANT_INT:
            class_file.constant_pool[i].Integer_Info.int_bytes = read_4_bytes(file);
            break;

        case CONSTANT_FLOAT:
            class_file.constant_pool[i].Float_Info.float_bytes = read_4_bytes(file);
            break;

        case CONSTANT_LONG:
            class_file.constant_pool[i].Long_Info.long_high_bytes = read_4_bytes(file);
            class_file.constant_pool[i].Long_Info.long_low_bytes = read_4_bytes(file);
            i++;
            break;

        case CONSTANT_DOUBLE:
            class_file.constant_pool[i].Double_Info.double_high_bytes = read_4_bytes(file);
            class_file.constant_pool[i].Double_Info.double_low_bytes = read_4_bytes(file);
            i++;
            break;

        case CONSTANT_NAME_TYPE:
            class_file.constant_pool[i].NameAndType_Info.name_type_index = read_2_bytes(file);
            class_file.constant_pool[i].NameAndType_Info.name_type_descriptor_index = read_2_bytes(file);
            break;

        case CONSTANT_UTF8:
            // Talvez precise de '/0' no final e o +1 no size do malloc
            class_file.constant_pool[i].Utf8_Info.UTF8_size = read_2_bytes(file);
            class_file.constant_pool[i].Utf8_Info.UTF8_bytes = (u1 *)malloc((class_file.constant_pool[i].Utf8_Info.UTF8_size + 1) * sizeof(u1));
            fread(class_file.constant_pool[i].Utf8_Info.UTF8_bytes, 1, class_file.constant_pool[i].Utf8_Info.UTF8_size, file);
            class_file.constant_pool[i].Utf8_Info.UTF8_bytes[class_file.constant_pool[i].Utf8_Info.UTF8_size] = '\0';

            break;
        }
    }
}
// * Verifica se o this_class é igual ao nome do arquivo fonte
void get_cp_info_class_name(std::string filename, Class_File class_file)
{
    std::string class_name = get_utf8(class_file, class_file.this_class);
    class_name += ".class";
    if (DEBUG)
        std::cout << "This Class:           " << class_name << std::endl;

    std::size_t backslash_index = filename.find_last_of("/\\");
    std::string class_filename = filename.substr(backslash_index + 1);
    if (DEBUG)
        std::cout << "Source File Name:     " << class_filename << std::endl;

    if (class_filename != class_name)
    {
        printf("O nome do arquivo nao corresponde ao da classe!\n");
        exit(1);
    }
}