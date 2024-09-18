BGreen='\033[1;32m'
BIRed='\033[1;91m'
BIPurple='\033[1;35m'
NC='\033[0m'

# NOTE: This script is only intended to test the functionality of the red-black tree data structure itself, not the gui. When running this
#       script, gui related functions should be commented out of red_black_tree.c

echo -e "${BIPurple}Running static analysis suite...\n"

echo -e "${NC}Running cppcheck static analysis..."
cppcheck -v --platform=unix64 --std=c11 --output-file=cppcheck_report.txt unit_tests/. src/. > /dev/null # report should be blank if passed
if [ -s cppcheck_report.txt ]; then
    echo -e "${BIRed}Issues found by cppcheck."
    cat cppcheck_report.txt
else
    echo -e "${BGreen}cppcheck static analysis passed."
    rm cppcheck_report.txt
fi

echo -e "${NC}Running flawfinder static analysis..."
flawfinder --minlevel=1 unit_tests/. src/. > flawfinder_report.txt # report should include "no hits found" if passed
if grep -Fq "No hits found" flawfinder_report.txt; then
    echo -e "${BGreen}flawfinder static analysis passed."
    rm flawfinder_report.txt
else
    echo -e "${BIRed}Issues found by flawfinder."
    cat flawfinder_report.txt
fi

echo -e "${NC}Running lizard static analysis..."
lizard -V -o lizard_report.txt unit_tests/. src/. # report should include "No thresholds exceeded" if passed
if grep -Fq "No thresholds exceeded" lizard_report.txt; then
    echo -e "${BGreen}lizard static analysis passed."
    rm lizard_report.txt
else
    echo -e "${BIRed}Issued found by lizard"
    cat lizard_report.txt
fi

echo -e "${NC}Running scan-build static analysis..."
scan-build gcc -g3 ./unit_tests/*.c ./src/red_black_tree.c ./src/gtkBackend.c -I./src `pkg-config --cflags --libs gtk+-3.0` > scan-build_report.txt # report should include "No bugs found" if passed
if grep -Fq "No bugs found" scan-build_report.txt; then
    echo -e "${BGreen}scan-build static analysis passed."
    rm scan-build_report.txt
else
    echo -e "${BIRed}Issues found by scan-build."
    cat scan-build_report.txt
fi

echo -e "${BIPurple}\nRunning dynamic analysis suite...\n"

echo -e "${NC}Running valgrind dynamic analysis..."
gcc -g3 ./unit_tests/*.c ./src/red_black_tree.c -I./src `pkg-config --cflags --libs gtk+-3.0`
valgrind -s --log-file=valgrind_report.txt --leak-check=full --show-reachable=yes --track-origins=yes ./a.out > /dev/null
if grep -Fq "no leaks are possible" valgrind_report.txt  && grep -Fq "0 errors from 0 contexts" valgrind_report.txt; then
    echo -e "${BGreen}valgrind dynamic analysis passed."
    rm valgrind_report.txt
else
    echo -e "${BIRed}Issues found by valgrind."
    cat valgrind_report.txt
fi

echo -e "${NC}Running address and leak sanitizer dynamic analysis..."
gcc -fsanitize=address -fsanitize=leak ./unit_tests/*.c src/red_black_tree.c -g3 -I./src `pkg-config --cflags --libs gtk+-3.0`
if [ -s sanitizer_report.txt ]; then
    echo -e "${BIRed}Issues found by sanitizers."
    cat sanitizer_report.txt
else
    echo -e "${BGreen}sanitizer dynamic analysis passed."
fi

echo -e "${BIPurple}\nRunning unit tests..."
echo -e "${NC}"
gcc ./unit_tests/*.c ./src/red_black_tree.c -I./src `pkg-config --cflags --libs gtk+-3.0` > /dev/null
./a.out

echo -e "${BIPurple}\nTest suite finished"
