#include "expr.h"

template <typename T>
Expr<T>::Binary::Binary(Expr left, Token operate, Expr right) : left(left), operate(operate), right(right) {};

template <typename T>
T Expr<T>::Binary::Binary::accept(Visitor* visitor) {
	visitor->visit_binary_expr(this);
};

template <typename T>
Expr<T>::Grouping::Grouping(Expr expression) : expression(expression) {};

template <typename T>
T Expr<T>::Grouping::Grouping::accept(Visitor* visitor) {
	visitor->visit_grouping_expr(this);
};

template <typename T>
Expr<T>::Literal::Literal(std::monostate value) : value(value) {};

template <typename T>
T Expr<T>::Literal::Literal::accept(Visitor* visitor) {
	visitor->visit_literal_expr(this);
};

template <typename T>
Expr<T>::Unary::Unary(Token operate, Expr right) : operate(operate), right(right) {};

template <typename T>
T Expr<T>::Unary::Unary::accept(Visitor* visitor) {
	visitor->visit_unary_expr(this);
};
