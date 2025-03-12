#ifndef PRINTER_H
#define PRINTER_H

#include "expr.h"

class AstPrinter : public Expr<std::string>::Visitor {
	template <typename... Exprs>
	std::string parenthize(const std::string& name, const Exprs&... exprs);

public:
	std::string print(Expr<std::string>* expr);

	std::string visit_binary_expr(const Expr<std::string>::Binary& expr);
	std::string visit_grouping_expr(const Expr<std::string>::Grouping& expr);
	std::string visit_literal_expr(const Expr<std::string>::Literal& expr);
	std::string visit_unary_expr(const Expr<std::string>::Unary& expr);
};

#endif
