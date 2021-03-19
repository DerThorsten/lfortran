#include <tests/doctest.h>
#include <iostream>

#include <lfortran/stacktrace.h>
#include <lfortran/pickle.h>
#include <lfortran/ast_to_src.h>
#include <lfortran/parser/parser.h>


TEST_CASE("Address to line number"){
    Allocator al(4*1024);

    std::vector<std::string> filenames = {
        "foo",
        "foo1",
        "foo2",
        "foo3"
    };
    std::vector<uint64_t> addresses = {
        // address, line_number, filename_id
        123, 45, 0,
        456, 50, 1,
        789, 1, 3,
        1000, 15, 2,
        1200, 20, 1
    };
    std::string filename = "";
    int line_number = -1;

    LFortran::address_to_line_number(filenames, addresses, 500, filename, line_number ); //addresses[8], filename=filenames[7]=bar, line_number=890
    CHECK(filename=="bar1");
    CHECK(line_number==901);

    //when address is not in addresses vector
    LFortran::address_to_line_number(filenames, addresses, 1500, filename="", line_number=-1);
    CHECK(filename=="");
    CHECK(line_number==-1);

}