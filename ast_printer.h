#ifndef PRINTER_H
#define PRINTER_H

#include "expr.h"

// Class that implements the visitor interface, meaning that it has functions to parse the tree
// Specifically, this class prints the AST
// Assumes the generic type for this visitor is strings (which makes sense, since it's a printer)
class AstPrinter : public Expr<std::string>::Visitor {

	// Accepts a variadic number of argument types, and accepts a variadic number of arguments that fit those types
	// Important because we need to be able to pass in different kinds of expressions, and varying numbers of those expressions
	template <typename... Exprs>
	std::string parenthesize(const std::string& name, const Exprs*... exprs) const;

public:

	// Given an expr pointer, prints the contents of it by *visiting* the expression (as described in the methods below)
	std::string print(Expr<std::string>* expr);

	std::string visit_binary_expr(const Expr<std::string>::Binary& expr);
	std::string visit_grouping_expr(const Expr<std::string>::Grouping& expr);
	std::string visit_literal_expr(const Expr<std::string>::Literal& expr);
	std::string visit_unary_expr(const Expr<std::string>::Unary& expr);
};

#endif
