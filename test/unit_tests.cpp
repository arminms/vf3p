//
// Copyright (c) 2024 Armin Sobhani
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <vf3p/color>

constexpr auto test = 0x1a2b3c4d_rgba;
constexpr std::array<uint8_t,4> a{ 0, 1, 2, 3 };
constexpr vf3p::generic_color<uint8_t> c(a);
constexpr vf3p::generic_color<uint8_t> d(0x1a2b3c4d_rgba);
constexpr vf3p::generic_color<uint8_t> e(test);
// constexpr vf3p::generic_color<uint8_t> b{ 0, 1, 2, 3 };

TEMPLATE_TEST_CASE( "vf3p::color", "[class]", uint8_t, uint16_t, uint32_t, float)
{   typedef TestType T;
    vf3p::generic_color<T> c{ T(0), T(1), T(2), T(3) };

// -- comparison operators -----------------------------------------------------

    SECTION( "comparison operators" )
    {   REQUIRE(  c == vf3p::generic_color<T>{ T(0), T(1), T(2), T(3) } );
        REQUIRE(!(c == vf3p::generic_color<T>{ T(4), T(1), T(2), T(3) }));
        REQUIRE(!(c == vf3p::generic_color<T>{ T(0), T(4), T(2), T(3) }));
        REQUIRE(!(c == vf3p::generic_color<T>{ T(0), T(1), T(4), T(3) }));
        REQUIRE(!(c == vf3p::generic_color<T>{ T(0), T(1), T(2), T(4) }));
        REQUIRE(  c != vf3p::generic_color<T>{ T(4), T(1), T(2), T(3) } );
        REQUIRE(  c != vf3p::generic_color<T>{ T(0), T(4), T(2), T(3) } );
        REQUIRE(  c != vf3p::generic_color<T>{ T(0), T(1), T(4), T(3) } );
        REQUIRE(  c != vf3p::generic_color<T>{ T(0), T(1), T(2), T(4) } );
        REQUIRE(!(c != vf3p::generic_color<T>{ T(0), T(1), T(2), T(3) }));
    }

// -- ctors --------------------------------------------------------------------

    SECTION( "aggregate initialization" )
    {   vf3p::generic_color<T> zero2three{ T(0), T(1), T(2), T(3) };
        CHECK(c == zero2three);
        vf3p::generic_color<T> black{};
        CHECK(black == vf3p::generic_color<T>{ T(0), T(0), T(0), T(0) });
    }
    SECTION( "iterator constructor" )
    {   std::vector<T> zero2three{ T(0), T(1), T(2), T(3) };
        vf3p::generic_color<T> d(std::begin(zero2three), std::end(zero2three));
        CHECK(c == d);
        std::vector<T> zero2four{ T(0), T(1), T(2), T(3), T(4) };
        vf3p::generic_color<T> e(std::begin(zero2four), std::end(zero2four));
        CHECK(c == e);
        // vf3p::generic_color<T> zero2one{ T(0), T(1) };
        // std::vector<T> zero2two{ T(0), T(1), T(2), T(3) };
        // vf3p::generic_color<T> e(std::begin(zero2two), std::end(zero2two));
    }
    SECTION( "copy constructor" )
    {   vf3p::generic_color<T> d(c);
        CHECK(d == c);
    }
    SECTION( "move constructor" )
    {   vf3p::generic_color<T> m(std::move(c));
        CHECK(m == vf3p::generic_color<T>{ T(0), T(1), T(2), T(3) });
    }
    SECTION( "initializer list" )
    {   vf3p::generic_color<T> d{ T(0), T(1), T(2), T(3) };
        CHECK(d == c);
    }

// -- copy assignment operators ------------------------------------------------

    SECTION( "copy assignment operator" )
    {   vf3p::generic_color<T> d = c;
        CHECK(d == c);
    }
    SECTION( "move constructor" )
    {   vf3p::generic_color<T> m = vf3p::generic_color<T>{T(0),T(1),T(2),T(3)};
        CHECK(m == c);
    }
    SECTION( "initializer list" )
    {   vf3p::generic_color<T> d = { T(0), T(1), T(2), T(3) };
        CHECK(d == c);
        CHECK(0x883a1215_rgba == 2'285'507'093);
        CHECK(0x883a12_rgb == 0x883a12ff);
    }

// -- iterators ----------------------------------------------------------------

    SECTION( "begin/end" )
    {   vf3p::generic_color<T> t{ T(2), T(2), T(2), T(2) };
        for (auto a : t)
            CHECK(a == T(2));
        for (auto& a : t)
            a = T(3);
        CHECK(t == vf3p::generic_color<T>{ T(3), T(3), T(3), T(3) });
        auto c_it = c.cbegin();
        for
        (   auto t_it = t.begin()
        ;   t_it != t.end()
        ;   ++t_it, ++c_it
        )
            *t_it = *c_it;
        CHECK(t == vf3p::generic_color<T>{ T(0), T(1), T(2), T(3) });
    }
    SECTION( "cbegin/cend" )
    {   const vf3p::generic_color<T> t{ T(2), T(2), T(2), T(2) };
        auto c_it = c.begin();
        for
        (   auto t_it = t.cbegin()
        ;   t_it != t.cend()
        ;   ++t_it, ++c_it
        )
            *c_it = *t_it;
        CHECK(c == vf3p::generic_color<T>{ T(2), T(2), T(2), T(2) });
    }
    SECTION( "rbegin/rend" )
    {   vf3p::generic_color<T> t;
        auto c_it = c.cbegin();
        for
        (   auto t_it = t.rbegin()
        ;   t_it != t.rend()
        ;   ++t_it, ++c_it
        )
            *t_it = *c_it;
        CHECK(t == vf3p::generic_color<T>{ T(3), T(2), T(1), T(0) });
    }
    SECTION( "crbegin/crend" )
    {   const vf3p::generic_color<T> t{ T(0), T(1), T(2), T(3) };
        auto c_it = c.begin();
        for
        (   auto t_it = t.crbegin()
        ;   t_it != t.crend()
        ;   ++t_it, ++c_it
        )
            *c_it = *t_it;
        CHECK(c == vf3p::generic_color<T>{ T(3), T(2), T(1), T(0) });
    }

// -- capacity -----------------------------------------------------------------

    SECTION( "empty()" )
    {   vf3p::generic_color<T, 0> e;
        CHECK(e.empty());
        CHECK(c.empty() == false);
    }
    SECTION( "size()" )
    {   vf3p::generic_color<T, 0> e;
        CHECK(0 == e.size());
        CHECK(4 == c.size());
    }

// -- subscript operator -------------------------------------------------------

    SECTION( "subscript/array index operator" )
    {   CHECK(T(0) == c[0]);
        CHECK(T(1) == c[1]);
        CHECK(T(2) == c[2]);
        CHECK(T(3) == c[3]);
        c[3] = T(4);
        CHECK(T(4) == c[3]);
    }
}

TEST_CASE("uint32_t converting ctor 8-bits per channel", "[color][ctor][uint8_t]")
{   vf3p::generic_color<uint8_t> c(0x1a2b3c4d);
    CHECK(0x1a == c[0]);
    CHECK(0x2b == c[1]);
    CHECK(0x3c == c[2]);
    CHECK(0x4d == c[3]);
    CHECK(c == 0x1a2b3c4d_rgba);
}

TEST_CASE("uint32_t converting ctor 16-bits per channel", "[color][ctor][uint16_t]")
{   vf3p::generic_color<uint16_t> c(0x1a2b3c4d);
    CHECK(0x1a * 0xFF == c[0]);
    CHECK(0x2b * 0xFF == c[1]);
    CHECK(0x3c * 0xFF == c[2]);
    CHECK(0x4d * 0xFF == c[3]);
    CHECK(c == 0x1a2b3c4d_rgba);
}

TEST_CASE("uint32_t converting ctor 32-bits per channel", "[color][ctor][uint32_t]")
{   vf3p::generic_color<uint32_t> c(0x1a2b3c4d);
    CHECK(0x1a * 0xFFFF == c[0]);
    CHECK(0x2b * 0xFFFF == c[1]);
    CHECK(0x3c * 0xFFFF == c[2]);
    CHECK(0x4d * 0xFFFF == c[3]);
    CHECK(c == 0x1a2b3c4d_rgba);
}

TEST_CASE("uint32_t converting ctor 64-bits per channel", "[color][ctor][uint64_t]")
{   vf3p::generic_color<uint64_t> c(0x1a2b3c4d);
    CHECK(0x1a * 0xFFFFFF == c[0]);
    CHECK(0x2b * 0xFFFFFF == c[1]);
    CHECK(0x3c * 0xFFFFFF == c[2]);
    CHECK(0x4d * 0xFFFFFF == c[3]);
    CHECK(c == 0x1a2b3c4d_rgba);
}

TEST_CASE("uint32_t converting ctor float per channel", "[color][ctor][float]")
{   vf3p::generic_color<float> c(0x1a2b3c4d);
    REQUIRE_THAT(c[0], Catch::Matchers::WithinRel(0.101961, 0.0001));
    REQUIRE_THAT(c[1], Catch::Matchers::WithinRel(0.168627, 0.0001));
    REQUIRE_THAT(c[2], Catch::Matchers::WithinRel(0.235294, 0.0001));
    REQUIRE_THAT(c[3], Catch::Matchers::WithinRel(0.301961, 0.0001));
    CHECK(c == 0x1a2b3c4d_rgba);
}

TEST_CASE("uint32_t converting ctor double per channel", "[color][ctor][double]")
{   vf3p::generic_color<double> c(0x1a2b3c4d);
    REQUIRE_THAT(c[0], Catch::Matchers::WithinRel(0.101961, 0.0001));
    REQUIRE_THAT(c[1], Catch::Matchers::WithinRel(0.168627, 0.0001));
    REQUIRE_THAT(c[2], Catch::Matchers::WithinRel(0.235294, 0.0001));
    REQUIRE_THAT(c[3], Catch::Matchers::WithinRel(0.301961, 0.0001));
    CHECK(c == 0x1a2b3c4d_rgba);
}
