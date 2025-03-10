template <typename T>
class Expr {
	class Test;

public:
	class Visitor {
		T virtual visit_test_expr(Test expr);
	};
};

template <typename T>
class Expr<T>::Test : public Expr<T> {
	const int hello;
	const int hi;
	const double welcome;

 public:
	Test(int hello, int hi, double welcome);
};