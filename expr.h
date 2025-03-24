#ifndef EXPR_H
#define EXPR_H

#include "scanner.h"
#include <variant>

using expr_variant = std::variant<std::monostate, double, std::string>;

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

	virtual T accept(const Visitor& visitor) const;
};

template <typename T>
class Expr<T>::Binary : public Expr<T> {
public:
	const Expr* left;
	const Token* operate;
	const Expr* right;

	Binary(const Expr* left, const Token* operate, const Expr* right);

	T accept(const Visitor& visitor) const override;
};

template <typename T>
class Expr<T>::Grouping : public Expr<T> {
public:
	const Expr* expression;

	Grouping(const Expr* expression);

	T accept(const Visitor& visitor) const override;
};

template <typename T>
class Expr<T>::Literal : public Expr<T> {
public:
	const expr_variant* value;

	Literal(const expr_variant* value);

	T accept(const Visitor& visitor) const override;
};

template <typename T>
class Expr<T>::Unary : public Expr<T> {
public:
	const Token* operate;
	const Expr* right;

	Unary(const Token* operate, const Expr* right);

	T accept(const Visitor& visitor) const override;
};

#endif