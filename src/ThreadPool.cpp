/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Geyser - a simple C++ thread pool implementation
 *
 * Copyright (c) 2016 by Alexander Diemand
 * 
 * License: MIT   (see LICENSE)
 *
 * Repository: https://github.com/CodiePP/geyser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ThreadPool.hpp"

namespace geyser
{

ThreadPool::ThreadPool(int n_threads)
    : _service()
{
    _working.reset(new boost::asio::io_service::work(_service));
    for (int i=0; i<n_threads; i++)
    {
        _threads.create_thread(boost::bind(&boost::asio::io_service::run, &_service));
    }
}

ThreadPool::~ThreadPool()
{
    _service.stop();
    _threads.join_all();
    _working.reset();
}

} // namespace

