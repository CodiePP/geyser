/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Geyser - a simple C++ thread pool implementation
 *
 * Copyright (c) 2016 by Alexander Diemand
 * 
 * License: MIT   (see LICENSE)
 *
 * Repository: https://github.com/CodiePP/geyser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "boost/test/unit_test.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <iostream>
#include <thread>
#include <mutex>

#include "ThreadPool.hpp"

using namespace boost::posix_time;

BOOST_AUTO_TEST_SUITE( GeyserUT )

const int thr_n { 10 };
//const int thr_sleep { 20 }; // ms
const int job_n { 1000 };
const int rep_n { 1000000 };

static double thr_time[thr_n] = { 0 };
static int thr_count[thr_n] = { 0 };

static int jobs_running { 0 };

std::mutex mtx;

struct thr_proc
{
    void thread_process(int thr_num)
    {
        ptime t0(microsec_clock::universal_time());
        long y=0;
        for (int i=0; i<rep_n; i++) {
            y += thr_num;
        }
        //boost::this_thread::sleep( milliseconds(thr_sleep) );
        ptime t1(microsec_clock::universal_time());

        std::lock_guard<std::mutex> lck (mtx);
        thr_time[thr_num] += double( (t1 - t0).total_microseconds() ) / 1000.0;
        thr_count[thr_num] += 1;
        jobs_running -= 1;
    }
};

BOOST_AUTO_TEST_CASE( Timing )
{
    srand((unsigned)time(0));

    struct thr_proc _proc;

    geyser::ThreadPool _pool(thr_n);

    // initialize
    for (int i=0; i<thr_n; i++) {
        thr_count[i] = 0;
        thr_time[i] = 0.0; }

    {
    // queue some work
    for (int i=0; i<job_n; i++) {
        for (int j=0; j<thr_n; j++) {
            jobs_running += 1;
            _pool.enqueue(boost::bind(&thr_proc::thread_process, _proc, j)); } }
    }

    while (jobs_running > 0) {
        boost::this_thread::sleep(milliseconds(500)); }

    double t_sum = 0.0;
    for (int i=0; i<thr_n; i++) {
        t_sum += thr_time[i]; }

    std::cout << "thread count = " << thr_n << " jobs = " << job_n << " total time used = " << t_sum << " ms." << std::endl;
    for (int i=0; i<thr_n; i++) {
        std::cout << "   " << i << " " << thr_count[i] << " " << thr_time[i] << " ms" << std::endl; }

}

BOOST_AUTO_TEST_SUITE_END()

