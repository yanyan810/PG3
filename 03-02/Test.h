#pragma once
#include <type_traits>

// 2つの型を受け取れるクラステンプレート
template <class T1, class T2>
class Test {
public:
    using ResultType = std::common_type_t<T1, T2>;

    Test(T1 a, T2 b) : a_(a), b_(b) {}

    // 小さい方を返す
    ResultType Min() const {
        return (a_ < b_) ? static_cast<ResultType>(a_)
            : static_cast<ResultType>(b_);
    }

private:
    T1 a_;
    T2 b_;
};
