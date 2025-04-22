//
// Created by Chiradip Mandal on 4/12/25.
//

#include <catch2/catch_test_macros.hpp>
#include "../Calculator.h"

Calculator calc = Calculator();

TEST_CASE( "Statements are evaluated", "[calculator]" ) {

    REQUIRE( calc.statement("0+1;") == 1 );
    REQUIRE( calc.statement("1+1;") == 2 );
    REQUIRE( calc.statement("(1-2-3);") == -4 );
    REQUIRE( calc.statement("1+2*3;") == 7 );
    REQUIRE( calc.statement("(1+2)*3;") == 9 );
    REQUIRE( calc.statement("let a = 9;") );
    REQUIRE( calc.statement("let b = 10;") );
    REQUIRE( calc.statement("let c = a + b;") );
    REQUIRE( calc.statement("let d = c + b;") );
    REQUIRE( calc.statement("d*c;") == 551 );
}
