/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // TODO
  // Tìm 1 object ở trong scope hiện tại. Duyệt mọi list của nó lấy ra object. 
  // Nếu k tìm thấy thì tìm tiếp trong globalObjectList
}

void checkFreshIdent(char *name) {
  // TODO
}

Object* checkDeclaredIdent(char* name) {
  // TODO
}

Object* checkDeclaredConstant(char* name) {
  // TODO
}

Object* checkDeclaredType(char* name) {
  // TODO
}

Object* checkDeclaredVariable(char* name) {
  // TODO
}

Object* checkDeclaredFunction(char* name) {
  // TODO
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
}

