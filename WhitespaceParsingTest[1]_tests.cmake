add_test([=[HelloTest.BasicAssertions]=]  /Users/gavinhulvey/Documents/GitHub/mipscript/WhitespaceParsingTest [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /Users/gavinhulvey/Documents/GitHub/mipscript SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  WhitespaceParsingTest_TESTS HelloTest.BasicAssertions)
