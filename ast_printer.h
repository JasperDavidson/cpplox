#ifndef PRINTER_H
#define PRINTER_H

#include "expr.h"

template <typename T>
class AstPrinter : public Expr<T>::Visitor {

};

#endif
