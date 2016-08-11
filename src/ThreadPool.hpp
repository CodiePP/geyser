/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Geyser - a simple C++ thread pool implementation
 *
 * Copyright (c) 2016 by Alexander Diemand
 * 
 * License: MIT   (see LICENSE)
 *
 * Repository: https://github.com/CodiePP/geyser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <memory>

namespace geyser
{

class ThreadPool final
{
public:
    explicit ThreadPool(int n_threads);
    virtual ~ThreadPool();

private:
    ThreadPool();
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;

private:
    boost::asio::io_service _service;
    std::unique_ptr<boost::asio::io_service::work> _working;
    boost::thread_group _threads;

public:
    template<class F>
    void enqueue(const F f)
    {
         _service.post(f);
    }

}; // class

} // namespace

