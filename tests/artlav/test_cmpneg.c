#include <stdlib.h>
#include "../testing.h"
#include "../testing80x86.h"


int main() {
    Tester tester = create_tester("Testcase CMPNEG");

    test_section("cmpneg.bin");
    test_testcase(
            &tester,
            "../tests/artlav/bins/cmpneg.bin",
            "../tests/artlav/bins/results/res_cmpneg.bin",
            true
    );

    test_summary(&tester);

    exit(tester.fail);
}
