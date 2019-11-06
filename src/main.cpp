#include "commoninclude.h"
#include "problems.h"

typedef void (*pfnTest)(void);

map<string, pfnTest> tests =
{
    { "PE66", PE66 },
    { "PE68", PE68 },
    { "PE75", PE75 },
    { "PE77", PE77 },
    { "PE78", PE78 },
    { "PE83", PE83 },
    { "PE91", PE91 },
    { "PE95", PE95 },
    { "PE96", PE96 },
    { "PE100", PE100 },
    { "PE104", PE104 },
    { "PE108", PE108 },
    { "PE113", PE113 },
    { "PE116", PE116 },
    { "PE119", PE119 },
    { "PE120", PE120 },
    { "PE123", PE123 },
    { "PE124", PE124 },
    { "PE125", PE125 },
    { "PE173", PE173 },
    { "PE179", PE179 },
    { "PE187", PE187 },
    { "PE203", PE203 },
    { "PE204", PE204 },
    { "PE293", PE293 },
    { "PE313", PE313 },
    { "PE329", PE329 },
    { "PE321", PE321 },
    { "PE340", PE340 },
    { "PE348", PE348 },
    { "PE351", PE351 },
    { "PE358", PE358 },
    { "PE359", PE359 },
    { "PE401", PE401 },
    { "PE425", PE425 },
    { "PE479", PE479 },
    { "PE512", PE512 },
    { "PE516", PE516 },
    { "PE518", PE518 },
    { "PE531", PE531 },
    { "PE571", PE571 },
    { "PE577", PE577 },
    { "PE581", PE581 },
    { "PE587", PE587 },
    { "PE601", PE601 },
    { "PE607", PE607 },
    { "PE622", PE622 },
    { "SHA256", TestSHA256 }
};

void DisplayTestsAndExit()
{
    printf("Usage: ProgrammingProblems.exe <test name>");
    printf("Available Tests:\n\n");

    for (auto& test : tests) printf("%s\n", test.first.c_str());

    exit(0);
}

/**
 * main - Driver routine for math problems.
 */

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("Please specify a test.\n");
        DisplayTestsAndExit();
    }

    vector<string> args(argv + 1, argv + argc);

    if (tests.count(args[0]) == 0) DisplayTestsAndExit();

    tests[args[0]]();

    return 0;
}