#include <stdlib.h>
#include "testing.h"
#include "testing80x86.h"


int main() {
    Tester tester = create_tester("Testcase BCDCNV");

    test_section("bcdcnv.bin");
    test_testcase(
            &tester,
            "../tests/bins/bcdcnv.bin",
            "../tests/bins/results/res_bcdcnv.bin",
            true
    );

    test_summary(&tester);

    exit(tester.fail);
}
