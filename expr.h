#ifndef EXPR_H
#define RUN_H

template <typename T>
class Expr {
	class Test;
	class TestTwo;
	
public:
	class Visitor {
		virtual T visit_test_expr(Test expr);
		virtual T visit_testtwo_expr(TestTwo expr);
	};

	virtual T accept(Visitor* visitor);
};

template <typename T>
class Expr<T>::Test : public Expr<T> {
	const int hello;
	const int hi;
	const double welcome;

 public:
	Test(int hello, int hi, double welcome);

	T accept(Visitor* visitor) override;
};

template <typename T>
class Expr<T>::TestTwo : public Expr<T> {
	const double really;
	const long hope;
	const int this_works;

 public:
	TestTwo(double really, long hope, int this_works);

	T accept(Visitor* visitor) override;
};

#endif
