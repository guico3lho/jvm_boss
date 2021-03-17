#ifndef __ATTRIBUTE_INFO_H__
#define __ATTRIBUTE_INFO_H__

#include "file_reader.hpp"

#define SAME 0
#define SAME_LOCALS_1_STACK_ITEM 64
#define CHOP 248
#define SAME_LOCALS_1_STACK_ITEM_EXTENDED 247
#define SAME_FRAME_EXTENDED 251
#define APPEND 252
#define FULL_FRAME 255

#define ITEM_Top 0
#define ITEM_Integer 1
#define ITEM_Float 2
#define ITEM_Double 3
#define ITEM_Long 4
#define ITEM_Null 5
#define ITEM_UninitializedThis 6
#define ITEM_Object 7
#define ITEM_Uninitialized 8

typedef struct same_frame {
  u1 frame_type = SAME; /* 0-63 */
} same_frame;

typedef struct same_locals_1_stack_item_frame {
  u1 frame_type = SAME_LOCALS_1_STACK_ITEM; /* 64-127 */
  verification_type_info stack[1];
} same_locals_1_stack_item_frame;

typedef struct chop_frame {
  u1 frame_type = CHOP; /* 248-250 */
  u2 offset_delta;
} chop_frame;

typedef struct same_locals_1_stack_item_frame_extended {
  u1 frame_type = SAME_LOCALS_1_STACK_ITEM_EXTENDED; /* 247 */
  u2 offset_delta;
  verification_type_info stack[1];
} same_locals_1_stack_item_frame_extended;

typedef struct same_frame_extended {
  u1 frame_type = SAME_FRAME_EXTENDED; /* 251 */
  u2 offset_delta;
}same_frame_extended;

typedef struct append_frame {
  u1 frame_type = APPEND; /* 252-254 */
  u2 offset_delta;

  // verification_type_info locals[frame_type - 251];
} append_frame;

typedef struct full_frame {
u1 frame_type = FULL_FRAME; /* 255 */
u2 offset_delta;

u2 number_of_locals;
verification_type_info *locals;

u2 number_of_stack_items;
verification_type_info *stack;
} full_frame;

typedef struct StackMapTable_attribute {
  u2 attribute_name_index;
  u4 attribute_length;
  u2 number_of_entries;
  stack_map_frame* entries;
} StackMapTable_attribute;

union stack_map_frame {
  same_frame same_frame;
  same_locals_1_stack_item_frame same_locals_1_stack_item_frame;
  same_locals_1_stack_item_frame_extended same_locals_1_stack_item_frame_extended;
  chop_frame chop_frame;
  same_frame_extended same_frame_extended;
  append_frame append_frame;
  full_frame full_frame;
};

typedef struct Top_variable_info {
  u1 tag = ITEM_Top; /* 0 */
} Top_variable_info;

typedef struct Integer_variable_info {
  u1 tag = ITEM_Integer; /* 1 */
} Integer_variable_info;

typedef struct Float_variable_info {
  u1 tag = ITEM_Float; /* 2 */
} Float_variable_info;

typedef struct Double_variable_info {
  u1 tag = ITEM_Double; /* 3 */
} Double_variable_info;

typedef struct Long_variable_info {
  u1 tag = ITEM_Long; /* 4 */
} Long_variable_info;

typedef struct Null_variable_info {
  u1 tag = ITEM_Null; /* 5 */
} Null_variable_info;

typedef struct UninitializedThis_variable_info {
  u1 tag = ITEM_UninitializedThis; /* 6 */
} UninitializedThis_variable_info;

typedef struct Object_variable_info {
  u1 tag = ITEM_Object; /* 7 */
  u2 cpool_index;
} Object_variable_info;

typedef struct Uninitialized_variable_info {
  u1 tag = ITEM_Uninitialized; /* 8 */
  u2 offset;
} Uninitialized_variable_info;

union verification_type_info {
  Top_variable_info Top_variable_info;
  Integer_variable_info Integer_variable_info;
  Float_variable_info Float_variable_info;
  Long_variable_info Long_variable_info;
  Double_variable_info Double_variable_info;
  Null_variable_info Null_variable_info;
  UninitializedThis_variable_info UninitializedThis_variable_info;
  Object_variable_info Object_variable_info;
  Uninitialized_variable_info Uninitialized_variable_info;
};

#endif