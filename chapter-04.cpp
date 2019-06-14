#include <iostream>
#include <optional>
#include <cmath>
#include <type_traits>

auto const compose = [](auto l, auto r) {
    return [l, r](auto x) {
        auto a = r(x);
        if (a.has_value()) {
            return l(a.value());
        } else {
            using tt = typename std::invoke_result<decltype(r), decltype(x)>::type::value_type;
            return std::optional<typename std::invoke_result<decltype(l), tt>::type::value_type>{};
        }
    };
};

template<typename T>
auto identity(T t) -> std::optional<T> {
    return std::optional{t};
}

auto safe_root(double x) -> std::optional<double> {
    if (x > 0) {
        return std::optional{std::sqrt(x)};
    } else {
        return std::optional<double>{};
    }
}

auto safe_reciprocal(double x) -> std::optional<double> {
    if (x != 0) {
        return std::optional{1 / x};
    } else {
        return std::optional<double>{};
    }
}

int main() {
    auto r = compose(safe_reciprocal, compose(identity<double>, safe_root))(4.0);
    std::cout << "safe_reciprocal . id . safe_root) 4 = " << r.value() << std::endl;
    return 0;
}
