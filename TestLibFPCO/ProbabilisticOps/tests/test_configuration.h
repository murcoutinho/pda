//
//  test_configuration.h
//  ProbabilisticOps

#ifndef test_configuration_h
#define test_configuration_h

#define INIT_TEST(name) printf("Initializing test %s.\n", name);
#define END_TEST(rv, name) do {\
        if(rv) printf("ERROR!\n");\
        printf("Test %s completed.\n\n", name);\
} while(0);

#define GENERAL_NUMBER_OF_TEST_ITERATIONS 100

#define SIZE_OF_TEST_ARRAY 32

#define ACCEPTABLE_ERROR 0.001

#endif /* test_configuration_h */
