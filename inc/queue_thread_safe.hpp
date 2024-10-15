/* This file makes use of Doxygen syntax for generating documentation. */
/******************************************************************************/
/**
 *
 * @file queue_thread_safe.hpp
 * @brief Thread-safe wrapper of std::queue.
 *
 * This contains the template class definition for the thread-safe wrapper of
 * std::queue container. See std::queue documentation for implemented
 * methods.
 *
 * @author John H. Willis (willisjh)
 * @date 23 November 2021
 *
 * @bug No known bugs.
 *
 * @addtogroup QueueThreadSafe
 * @{
 *
 ******************************************************************************/

#ifndef QUEUE_THREAD_SAFE_HPP
#define QUEUE_THREAD_SAFE_HPP

/******************************** Include Files *******************************/
#include <queue>
#include <deque>
#include <mutex>

/**************************** Constant Definitions ****************************/

/****************************** Type Definitions ******************************/

/**************************** Template Definitions ****************************/

template<class T, class T_CONTAINER = std::deque<T>>
class QueueThreadSafe
{
public:
    /******************************************************************************/
    /**
     * @brief Default constructor for QueueThreadSafe.
     *
     * @return None.
     *
     * @note Using implicit default constructor.
     *
     ******************************************************************************/
    QueueThreadSafe() = default;

    /******************************************************************************/
    /**
     * @brief Copy constructor.
     *
     * @return None.
     *
     * @note Disabled implicit copy constructor.
     *
     ******************************************************************************/
    QueueThreadSafe(const QueueThreadSafe& other) = delete;

    /******************************************************************************/
    /**
     * @brief Copy assignment operator.
     *
     * @return None.
     *
     * @note Disabled implicit copy assignment operator.
     *
     ******************************************************************************/
    QueueThreadSafe& operator=(const QueueThreadSafe& other) = delete;

    /******************************************************************************/
    /**
     * @brief Move constructor.
     *
     * @return None.
     *
     * @note Disabled implicit move constructor.
     *
     ******************************************************************************/
    QueueThreadSafe(QueueThreadSafe&& other) = delete;

    /******************************************************************************/
    /**
     * @brief Move assignment operator.
     *
     * @return None.
     *
     * @note Disabled implicit move assignment operator.
     *
     ******************************************************************************/
    QueueThreadSafe& operator=(QueueThreadSafe&& other) = delete;

    /******************************************************************************/
    /**
     * @brief Deconstructor.
     *
     * @return None.
     *
     * @note None.
     *
     ******************************************************************************/
    ~QueueThreadSafe()
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);
    }


    T front()
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);

        return  q_thread_unsafe_.front();
    }

    T back()
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);

        return q_thread_unsafe_.back();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);

        return q_thread_unsafe_.empty();
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);

        return q_thread_unsafe_.size();
    }

    void push(const T& value)
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);
        q_thread_unsafe_.push(value);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(mutex_queue_thread_unsafe_);
        q_thread_unsafe_.pop();
    }

protected:
    std::queue<T, T_CONTAINER> q_thread_unsafe_;
    mutable std::mutex mutex_queue_thread_unsafe_;

};

#endif /* #ifndef QUEUE_THREAD_SAFE_HPP */
/** @} */ /* @addtogroup */
