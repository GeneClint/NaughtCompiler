#include <string>

#include "FuncDeclList.h"
#include "VarDeclList.h"
#include "FuncDefList.h"

#ifndef __MODULE_H
#define __MODULE_H

class Module {
  public:
    Module(const FuncDeclList *fdcl, 
           const VarDeclList *vdl, 
           const FuncDefList *fdnl) : 
           funcDeclList(fdcl), varDeclList(vdl), funcDefList(fdnl) {};
    virtual ~Module() {};
    
    Module(const Module &other);
    Module& operator=(const Module &other);
    Module (Module &&other) noexcept;
    Module& operator=(Module &&other) noexcept;

    bool hasFuncDecls() const;
    bool hasVarDecls() const;
    bool hasFuncDefs() const;
    
    FuncDeclList* getFuncDecls() const;
    VarDeclList* getVarDecls() const;
    FuncDefList* getFuncDefs() const;

    std::string toString() const;

    friend ostream& operator<<(ostream &os, Module &m) {
      os << m.toString();
      return os;
    }

  private:
    const FuncDeclList* funcDeclList;
    const VarDeclList* varDeclList;
    const FuncDefList* funcDefList;
};

#endif
