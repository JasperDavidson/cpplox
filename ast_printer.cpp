#include "ast_printer.h"

std::string AstPrinter::print(Expr<std::string>* expr) {
	return expr->accept(this);
}

std::string AstPrinter::visit_binary_expr(Expr<std::string>::Binary expr) {

}
