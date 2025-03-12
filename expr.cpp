#include "expr.h"

template <typename T>
Expr<T>::Test::Test(int hello, int hi, double welcome) : hello(hello), hi(hi), welcome(welcome) {};

template <typename T>
T Expr<T>::Test::Test::accept(Visitor* visitor) {
	visitor->visit_test_expr(this);
};

template <typename T>
Expr<T>::TestTwo::TestTwo(double really, long hope, int this_works) : really(really), hope(hope), this_works(this_works) {};

template <typename T>
T Expr<T>::TestTwo::TestTwo::accept(Visitor* visitor) {
	visitor->visit_testtwo_expr(this);
};
