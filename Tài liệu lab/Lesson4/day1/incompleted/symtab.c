/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO
  // Tạo 1 biến type mới cùng loại với biến Type* truyền vào
}

int compareType(Type* type1, Type* type2) {
  // TODO
  // So sánh trả ra true hay false rằng 2 type có giống nhau hay không (k thể ss ref mà phải ss từng trường)
}

void freeType(Type* type) {
  // TODO
  // giải phóng biến lưu type
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
  // Tạo ra biến int constant
}

ConstantValue* makeCharConstant(char ch) {
  // TODO
  // Tạo ra biến char constant
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
  // Tạo ra biến có type và value trùng với 1 biến truyền vào
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO
  // Tạo ra 1 object có trường name trùng với name truyền vào, khai báo cả type và attr là 1 hằng số
}

Object* createTypeObject(char *name) {
  // TODO
  // Tạo ra 1 object tương tự nhưng type là OBJ_TYPE
}

Object* createVariableObject(char *name) {
  // TODO
  // Tạo ra 1 object tương tự nhưng type là OBJ_VARIABLE
}

Object* createFunctionObject(char *name) {
  // TODO
  // Tạo ra 1 object tương tự nhưng type là OBJ_FUNCTION
}

Object* createProcedureObject(char *name) {
  // TODO
  // Tạo ra 1 object tương tự nhưng type là OBJ_PROCEDURE
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
  // Tạo ra 1 object tương tự nhưng type là OBJ_PARAMETER nhưng kind và function được truyền vào như này
}

void freeObject(Object* obj) {
  // TODO
  // giải phóng object đủ loại, VD loại OBJ_CONSTANT phải giải phóng 2 trường value và constAtts,..
}

void freeScope(Scope* scope) {
  // TODO
  // Gọi freeObjectList
}

void freeObjectList(ObjectNode *objList) {
  // TODO
  // Duyệt cái object list rồi free từng object bên trong
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  // Cho cái list này mọi node ref tới null chứ k free bộ nhớ cho từng node object như bên trên
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
  // Trả ra object là 1 node trong current list, trùng trường name là được
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


