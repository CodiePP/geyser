/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Geyser - a simple C++ thread pool implementation
 *
 * Copyright (c) 2016 by Alexander Diemand
 * 
 * License: MIT   (see LICENSE)
 *
 * Repository: https://github.com/CodiePP/geyser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE GeyserUT

#include "boost/test/unit_test.hpp"
#include <iostream>

static struct GlobalDisableBufferingStdCout
{
    GlobalDisableBufferingStdCout()
    {
        std::cout.setf(std::ios_base::unitbuf);
    }
} imp_globaldisablebufferingstdcout;

#include "ThreadPool.hpp"

BOOST_AUTO_TEST_SUITE( GeyserUT )

BOOST_AUTO_TEST_CASE( Sizing )
{
    std::clog << "sizeof(geyser::ThreadPool) = " << sizeof(geyser::ThreadPool) << std::endl;
    BOOST_CHECK( sizeof(geyser::ThreadPool) > 1 );
}

BOOST_AUTO_TEST_SUITE_END()
