// auto-generated by yaml_to_cxx.py from test/upstream/regression/2774.yaml
#include "testlib.h"
void test_upstream_regression_2774() {
    enter_section("test_upstream_regression_2774: Tests key sorting of all usable types in secondary indexes");
    temp_table tbl_table;
    R::Query tbl = tbl_table.table();
    auto binary_a = R::Binary("");
    auto binary_trunc1 = R::Binary("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    auto binary_trunc2 = R::Binary("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567891");
    auto binary_b = R::Binary("5aurhbviunr");
    auto str_trunc1 = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    auto str_trunc2 = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567891";
    auto trows = R::Array{R::Object{{"id",0}, {"idx",R::Array{0}}}, R::Object{{"id",1}, {"idx",R::Array{1, 2, 3, 4, 5, 6, 7, 0}}}, R::Object{{"id",2}, {"idx",R::Array{1, 2, 3, 4, 5, 6, 7, 4}}}, R::Object{{"id",3}, {"idx",R::Array{1, 2, 3, 4, 5, 6, 7, 4, 5}}}, R::Object{{"id",4}, {"idx",R::Array{1, 2, 3, 4, 5, 6, 7, 8, 1}}}, R::Object{{"id",5}, {"idx",R::Array{1, 3, binary_trunc1}}}, R::Object{{"id",6}, {"idx",R::Array{1, 3, binary_trunc2}}}, R::Object{{"id",7}, {"idx",R::Array{1, 3, R::epoch_time(0), R::epoch_time(0), R::epoch_time(0)}}}, R::Object{{"id",8}, {"idx",R::Array{1, 3, R::epoch_time(0), R::epoch_time(0), R::epoch_time(0), R::epoch_time(0)}}}, R::Object{{"id",9}, {"idx",R::Array{1, 3, R::epoch_time(0), R::epoch_time(0), R::epoch_time(0), R::epoch_time(1)}}}, R::Object{{"id",10}, {"idx",R::Array{1, 3, str_trunc1, str_trunc1}}}, R::Object{{"id",11}, {"idx",R::Array{1, 3, str_trunc1, str_trunc2}}}, R::Object{{"id",12}, {"idx",R::Array{1, 4, 3, 4, 5, 6, 7, 8, 2}}}, R::Object{{"id",13}, {"idx",R::Array{binary_trunc1}}}, R::Object{{"id",14}, {"idx",R::Array{binary_trunc2}}}, R::Object{{"id",15}, {"idx",false}}, R::Object{{"id",16}, {"idx",true}}, R::Object{{"id",17}, {"idx",-500}}, R::Object{{"id",18}, {"idx",500}}, R::Object{{"id",19}, {"idx",binary_a}}, R::Object{{"id",20}, {"idx",binary_trunc1}}, R::Object{{"id",21}, {"idx",binary_trunc2}}, R::Object{{"id",22}, {"idx",binary_b}}, R::Object{{"id",23}, {"idx",R::epoch_time(0)}}, R::Object{{"id",24}, {"idx",""}}, R::Object{{"id",25}, {"idx"," str"}}, R::Object{{"id",26}, {"idx",str_trunc1}}, R::Object{{"id",27}, {"idx",str_trunc2}}};
    auto expected = R::range(tbl.count()).coerce_to("array");
    TEST_EQ(tbl.insert(trows)["inserted"].run(*conn), (28));
    TEST_EQ(tbl.index_create("idx").run(*conn), (R::Object{{"created",1}}));
    TEST_EQ(tbl.index_wait("idx").pluck("index", "ready").run(*conn), (R::Array{R::Object{{"index","idx"}, {"ready",true}}}));
    TEST_EQ(tbl.order_by(R::OptArgs{{"index", R::expr("idx")}}).map(R::row["id"]).coerce_to("array").eq(expected).run(*conn), (true));
    TEST_EQ(tbl.order_by(R::OptArgs{{"index", R::expr("idx")}}).between(R::minval, R::maxval).map(R::row["id"]).coerce_to("array").eq(expected).run(*conn), (true));
    TEST_EQ(tbl.order_by(R::OptArgs{{"index", R::expr("idx")}}).between(R::array(1, 2, 3, 4, 5, 6, 7, 4), R::array(1, 2, 3, 4, 5, 6, 8)).map(R::row["id"]).coerce_to("array").run(*conn), (R::Array{2, 3, 4}));
    TEST_EQ(tbl.order_by(R::OptArgs{{"index", R::expr("idx")}}).between(R::array(1, 2, 3, 4, 5, 6, 7, 4, R::minval), R::array(1, 2, 3, 4, 5, 6, 7, 4, R::maxval)).map(R::row["id"]).coerce_to("array").run(*conn), (R::Array{3}));
}