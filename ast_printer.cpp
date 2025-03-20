#include "ast_printer.h"
#include <string>
#include <variant>

std::string AstPrinter::print(Expr<std::string>* expr) {
	return expr->accept(*this);
}

template <typename... Exprs>
std::string AstPrinter::parenthesize(const std::string& name, const Exprs&... exprs) {
	return "Hello";
}

std::string AstPrinter::visit_binary_expr(const Expr<std::string>::Binary& expr) {	
	return parenthesize(expr.operate->get_lexeme(), *expr.left, *expr.right);
}

std::string AstPrinter::visit_grouping_expr(const Expr<std::string>::Grouping& expr) {
	return parenthesize("group", *expr.expression);
}

std::string AstPrinter::visit_literal_expr(const Expr<std::string>::Literal& expr) {
	if (std::holds_alternative<std::monostate>(*expr.value)) {
		return "nil";
	}
	
	return std::visit([](const auto& arg) { return std::format("{}", arg); }, *expr.value);
}

std::string AstPrinter::visit_unary_expr(const Expr<std::string>::Unary& expr) {
	return parenthesize(expr.operate->get_lexeme(), expr.right);
}
