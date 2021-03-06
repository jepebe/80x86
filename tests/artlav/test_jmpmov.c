#include <stdlib.h>
#include "../testing.h"
#include "../testing80x86.h"


int main() {
    Tester tester = create_tester("Testcase JMPMOV");

    test_section("jmpmov.bin");
    test_testcase(
            &tester,
            "../tests/artlav/bins/jmpmov.bin",
            "../tests/artlav/bins/results/res_jmpmov.bin",
            true
    );

    test_summary(&tester);

    exit(tester.fail);
}
