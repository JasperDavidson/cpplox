#ifndef EXPR_H
#define RUN_H

#include "scanner.h"

template <typename T>
class Expr {
	class Binary;
	class Grouping;
	class Literal;
	class Unary;
	
public:
	class Visitor {
		virtual T visit_binary_expr(Binary expr);
		virtual T visit_grouping_expr(Grouping expr);
		virtual T visit_literal_expr(Literal expr);
		virtual T visit_unary_expr(Unary expr);
	};

	virtual T accept(Visitor* visitor);
};

template <typename T>
class Expr<T>::Binary : public Expr<T> {
	const Expr left;
	const Token operate;
	const Expr right;

 public:
	Binary(Expr left, Token operate, Expr right);

	T accept(Visitor* visitor) override;
};

template <typename T>
class Expr<T>::Grouping : public Expr<T> {
	const Expr expression;

 public:
	Grouping(Expr expression);

	T accept(Visitor* visitor) override;
};

template <typename T>
class Expr<T>::Literal : public Expr<T> {
	const std::monostate value;

 public:
	Literal(std::monostate value);

	T accept(Visitor* visitor) override;
};

template <typename T>
class Expr<T>::Unary : public Expr<T> {
	const Token operate;
	const Expr right;

 public:
	Unary(Token operate, Expr right);

	T accept(Visitor* visitor) override;
};

#endif
