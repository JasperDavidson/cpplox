#include "ast_printer.h"
#include <string>
#include <variant>

struct LiteralVisitor {
	std::string operator()(const std::string& literal) {
		return literal;
	}

	std::string operator()(const double& literal) {
		return std::to_string(literal);
	}

	std::string operator()(std::monostate literal) {
		return "nil";
	}
};

std::string AstPrinter::print(Expr<std::string>* expr) {
	return expr->accept(*this);
}

template <typename... Exprs>
std::string AstPrinter::parenthesize(const std::string& name, const Exprs*... exprs) const {
	// Start off the string to return
	std::string parenthesized = "(" + name;

	// Iterate over and unpack the variadic arguments using a fold expression with a lambda expression
	([&] {
		parenthesized += " ";
		parenthesized += exprs->accept(static_cast<const Visitor&>(*this));
	} (), ...);

	parenthesized += ")";

	return parenthesized;
}

std::string AstPrinter::visit_binary_expr(const Expr<std::string>::Binary& expr) {	
	return parenthesize(expr.operate->get_lexeme(), expr.left, expr.right);
}

std::string AstPrinter::visit_grouping_expr(const Expr<std::string>::Grouping& expr) {
	return parenthesize("group", expr.expression);
}

std::string AstPrinter::visit_literal_expr(const Expr<std::string>::Literal& expr) {
	return std::visit(
		LiteralVisitor{},
		*expr.value
	);
}

std::string AstPrinter::visit_unary_expr(const Expr<std::string>::Unary& expr) {
	return parenthesize(expr.operate->get_lexeme(), expr.right);
}
