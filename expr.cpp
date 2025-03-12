#include "expr.h"

template <typename T>
Expr<T>::Binary::Binary(const Expr* left, const Token* operate, const Expr* right) : left(left), operate(operate), right(right) {};

template <typename T>
T Expr<T>::Binary::Binary::accept(const Visitor& visitor) {
	visitor->visit_binary_expr(this);
};

template <typename T>
Expr<T>::Grouping::Grouping(const Expr* expression) : expression(expression) {};

template <typename T>
T Expr<T>::Grouping::Grouping::accept(const Visitor& visitor) {
	visitor->visit_grouping_expr(this);
};

template <typename T>
Expr<T>::Literal::Literal(const std::monostate* value) : value(value) {};

template <typename T>
T Expr<T>::Literal::Literal::accept(const Visitor& visitor) {
	visitor->visit_literal_expr(this);
};

template <typename T>
Expr<T>::Unary::Unary(const Token* operate, const Expr* right) : operate(operate), right(right) {};

template <typename T>
T Expr<T>::Unary::Unary::accept(const Visitor& visitor) {
	visitor->visit_unary_expr(this);
};
