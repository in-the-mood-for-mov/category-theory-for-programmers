#include <iostream>

// 1. Show that the terminal object is unique up to unique isomorphism.

// Let f1, f2 be two final objects. Because f1 is final there is a unique morphism g from f2 to f1 and because f2 is
// final, there is a unique morphism h from f1 to f2. Because g . h goes to f1 to itself, it must be equal to id<f1>.
// This means that g and h must be the inverse of each other, proving that f1 and f2 are isomorphic.

// 2. What is the product of two objects in a poset?

// Let a and b be two objects, min(a, b) is their product.
//
// Any other object c smaller that both a and b is a candidate for the product, but min(a, b) is the "best" product
// because you can factorize the projections with either c <= a or c <= b.

// 3. What is the coproduct of two objects in a poset?

// Let a and b be two objects, max(a, b) is their coproduct.

// 4. Implement the equivalent of Haskell's Either as a generic type in your favourite language.

template<typename L, typename R>
class either {
    bool is_left_;
    union {
        L l_;
        R r_;
    };

    either() = default;

public:
    static auto left(const L &l) -> either<L, R> {
        either e{};
        e.is_left_ = true;
        e.l_ = l;
        return e;
    }

    static auto left(L &&l) -> either<L, R> {
        either e{};
        e.is_left_ = true;
        e.l_ = l;
        return e;
    }

    static auto right(const R &r) -> either<L, R> {
        either e{};
        e.is_left_ = false;
        e.r_ = r;
        return e;
    }

    static auto right(R &&r) -> either<L, R> {
        either e{};
        e.is_left_ = false;
        e.r_ = r;
        return e;
    }

    bool is_left() const {
        return is_left_;
    }

    const L &l() const {
        return l_;
    }

    const R &r() const {
        return r_;
    }
};

// 5. Show that Either is a better coproduct that int equipped with the following injections.
//
// auto i(int n) -> int { return n; }
// auto j(bool b) -> int { return b ? 0 : 1; }

// Given m defined as follows,

auto m(const either<int, bool> &e) -> int {
    if (e.is_left()) {
        return e.l();
    } else if (e.r()) {
        return 1;
    } else {
        return 0;
    }
}

// either is a better coproduct, because m "factors" the injections like this
//
// i = m . left
// j = m . right

// 6. How would you argue that int with the two injections i and j cannot be "better" that either?

// int with i and j contains less information because it cannot distinguish between 0 and false and 1 and true, i.e. it
// acts more like a regular union rather than a disjointed union.

// 7. What about int and these injections.
//
// auto i(int n) -> int {
//     if n > 0 {
//         return n + 2;
//     } else {
//         return n;
//     }
// }
// auto j(bool b) -> int { return b ? 0 : 1; }

// Assuming that int is the (infinite) set of the whole numbers, this product is isomorphic to either, because
// injections to either can be factored with the following morphism.

auto n(int n) -> either<int, bool> {
    if (n == 0) {
        return either<int, bool>::right(false);
    } else if (n == 1) {
        return either<int, bool>::right(true);
    } else if (n < 0) {
        return either<int, bool>::left(n);
    } else {
        return either<int, bool>::left(n + 2);
    }
}

// i.e. n . m = id<either<int, bool>> and m . n = id<int>

// If int is instead a machine int, then i is partial since it does not give a (valid) result for the maximum value of
// an integer and for one less that this value. If i is partial, it is not a morphism is the categories of sets.

// 8. Come up with an inferior candidate for a coproduct of int and bool that cannot be better than either because it
//    allows multiple acceptable morphisms from it to either.

// data Inferior = A Int | B (Int, Bool)
// m1 (A n) = Left n
// m1 (B (n, _)) = Left n
// m2 (A n) = Left n
// m2 (B (_, b)) = Right b

auto main(int argc, char *argv[]) -> int {
    (void)argc;
    (void)argv;

    auto l = either<int, bool>::left(44);
    std::cout << l.is_left() << " " << l.l() << std::endl;

    auto r = either<int, bool>::right(true);
    std::cout << r.is_left() << " " << r.r() << std::endl;

    std::cout << m(r) << std::endl;

    return 0;
}
