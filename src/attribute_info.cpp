#include "file_reader.hpp"

Attribute_Info get_attribute_info(FILE *fp, Class_File_Format *class_file, Attribute_Info attribute_info) {
    if (DEBUG) std::cout << "reading basic attribute info\n";
    attribute_info.attribute_name_index = read_2_bytes(fp);
    attribute_info.attribute_length = read_4_bytes(fp);

    std::string attribute_name =get_cp_info_utf8(class_file->constant_pool, attribute_info.attribute_name_index - 1);
    if (DEBUG) std::cout << "read basic info\n";
    if (DEBUG) std::cout << "attribute_name: " << attribute_name << std::endl;

    // if (attribute_name == "Code") {
    //   if (DEBUG) std::cout << "reading code\n";
    //   attribute_info.code = code_info->read(class_file, fp, attribute_info);
    //   return attribute_info;
    // }
    // else if (attribute_name == "ConstantValue") {
    //   if (DEBUG) std::cout << "reading constant value\n";
    //   attribute_info.constant_value = constant_info->read(class_file, fp,attribute_info);
    // }
    // else if (attribute_name == "Exceptions") {
    //   if (DEBUG) std::cout << "exception\n";
    //   attribute_info.execptions = exp_info->read(fp, attribute_info);
    // }
    // else if (attribute_name =="InnerClasses") {
    //   if (DEBUG) std::cout << "reading inner classes\n";
    //   attribute_info.inner_class = inner_info->read(fp, attribute_info);
    // }
    // else if (attribute_name == "Synthetic") {
    //   if (DEBUG) std::cout << "reading Synthetic\n";
    //   // fazer nada
    // }
    // else if (attribute_name =="SourceFile") {
    //   if (DEBUG) std::cout << "reading source file\n";
    //   attribute_info.source_file = source_info->read(fp, attribute_info);
    // }
    // else if (attribute_name == "LineNumberTable") {
    //   if (DEBUG) std::cout << "line number table\n";
    //   attribute_info.line_number_table = line_number_info->read(fp, attribute_info);
    // }
    // else if (attribute_name == "LocalVariableTable") {
    //   if (DEBUG) std::cout << "LocalVariableTable \n";
    //   attribute_info.local_variable_table = local_info->read(fp, attribute_info);
    // }
    // else {
    //   if (DEBUG) std::cout << "ELSE\n";
    //   if (DEBUG) std::cout << "Attribute Lenght: " << attribute_info.attribute_length << "\n" ;

    //   // ignora silenciosamente os outros atributos
    //   attribute_info.info = (u1*)malloc(attribute_info.attribute_length * sizeof(u1));
    //   for (int j = 0; (unsigned)j < attribute_info.attribute_length; j++) {
    //       if (DEBUG) std::cout << "reading byte " << j << std::endl;
    //       attribute_info.info[j] = read_1_byte(fp);
    //       if (DEBUG) std::cout << "read byte\n";
    //   }
    // }

    return attribute_info;
}