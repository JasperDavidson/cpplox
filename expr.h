#ifndef EXPR_H
#define EXPR_H

#include "scanner.h"

template <typename T>
class Expr {
public:
	class Binary;
	class Grouping;
	class Literal;
	class Unary;
	
	class Visitor {
		virtual T visit_binary_expr(const Binary& expr);
		virtual T visit_grouping_expr(const Grouping& expr);
		virtual T visit_literal_expr(const Literal& expr);
		virtual T visit_unary_expr(const Unary& expr);
	};

	virtual T accept(const Visitor& visitor);
};

template <typename T>
class Expr<T>::Binary : public Expr<T> {
	const Expr* left;
	const Token* operate;
	const Expr* right;

public:
	Binary(const Expr* left, const Token* operate, const Expr* right);

	T accept(const Visitor& visitor) override;
};

template <typename T>
class Expr<T>::Grouping : public Expr<T> {
	const Expr* expression;

public:
	Grouping(const Expr* expression);

	T accept(const Visitor& visitor) override;
};

template <typename T>
class Expr<T>::Literal : public Expr<T> {
	const std::monostate* value;

public:
	Literal(const std::monostate* value);

	T accept(const Visitor& visitor) override;
};

template <typename T>
class Expr<T>::Unary : public Expr<T> {
	const Token* operate;
	const Expr* right;

public:
	Unary(const Token* operate, const Expr* right);

	T accept(const Visitor& visitor) override;
};

#endif
