
#include "test.h"

BOOST_AUTO_TEST_CASE(optional_t) {
    optional<int> o;
    BOOST_CHECK_EQUAL(bool(o), false);
    BOOST_CHECK_EQUAL(o.value_or(2), 2);

    int i = 1;
    o = i;
    BOOST_CHECK(bool(o));
    BOOST_CHECK_EQUAL(o.value(), 1);
    BOOST_CHECK_EQUAL(o.value_or(2), 1);

    o.value() = 2;  // check reference
    BOOST_CHECK_EQUAL(i, 1);
    BOOST_CHECK_EQUAL(o.value(), 2);

    int j = 3;
    o = j;
    BOOST_CHECK_EQUAL(o.value(), 3);
    BOOST_CHECK_EQUAL(i, 1);

    optional<Widget> o2;
    BOOST_CHECK_EQUAL(bool(o2), false);
    BOOST_CHECK_EQUAL(o2.value_or(Widget(1)), Widget(1));
    o2 = Widget(2);
    BOOST_CHECK(bool(o2));
    BOOST_CHECK_EQUAL(o2.value(), Widget(2));
    BOOST_CHECK_EQUAL(o2.value_or(Widget(1)), Widget(2));

    int i3 = 4;
    optional<const int> o3(i3);
    BOOST_CHECK(bool(o3));
    BOOST_CHECK_EQUAL(o3.value(), 4);
    BOOST_CHECK_EQUAL(o3.value_or(1), 4);

    Widget w(1);
    optional<Widget> o4(w);
    BOOST_CHECK(bool(o4));
    BOOST_CHECK_EQUAL(o4->_value, 1);
    BOOST_CHECK_EQUAL(*o4, Widget(1));

    w.set_value(0); // not a reference
    BOOST_CHECK_EQUAL(o4->_value, 1);
    BOOST_CHECK_EQUAL(*o4, Widget(1));

    o4->set_value(3);
    BOOST_CHECK_EQUAL(o4->_value, 3);
    BOOST_CHECK_EQUAL(*o4, Widget(3));
    BOOST_CHECK_EQUAL(w, Widget(0));
}

BOOST_AUTO_TEST_CASE(optional_ref_t) {
    optional<int&> o;
    BOOST_CHECK_EQUAL(bool(o), false);
    BOOST_CHECK_EQUAL(o.value_or(2), 2);

    int i = 1;
    o = i;
    BOOST_CHECK(bool(o));
    BOOST_CHECK_EQUAL(o.value(), 1);
    BOOST_CHECK_EQUAL(o.value_or(2), 1);

    o.value() = 2;  // check reference
    BOOST_CHECK_EQUAL(i, 2);
    BOOST_CHECK_EQUAL(o.value(), 2);

    int j = 3;
    o = j;
    BOOST_CHECK_EQUAL(o.value(), 3);
    BOOST_CHECK_EQUAL(i, 2);

    optional<Widget&> o2;
    BOOST_CHECK_EQUAL(bool(o2), false);
    BOOST_CHECK_EQUAL(o2.value_or(Widget(1)), Widget(1));
    Widget a(2);
    o2 = a;
    BOOST_CHECK(bool(o2));
    BOOST_CHECK_EQUAL(o2.value(), Widget(2));
    BOOST_CHECK_EQUAL(o2.value_or(Widget(1)), Widget(2));

    int i3 = 4;
    optional<const int&> o3(i3);
    BOOST_CHECK(bool(o3));
    BOOST_CHECK_EQUAL(o3.value(), 4);
    BOOST_CHECK_EQUAL(o3.value_or(1), 4);

    Widget w(1);
    optional<Widget&> o4(w);
    BOOST_CHECK(bool(o4));
    BOOST_CHECK_EQUAL(o4->_value, 1);
    BOOST_CHECK_EQUAL(*o4, Widget(1));

    w.set_value(0);
    BOOST_CHECK_EQUAL(o4->_value, 0);
    BOOST_CHECK_EQUAL(*o4, Widget(0));

    o4->set_value(3);
    BOOST_CHECK_EQUAL(o4->_value, 3);
    BOOST_CHECK_EQUAL(*o4, Widget(3));
    BOOST_CHECK_EQUAL(w, Widget(3));
}
