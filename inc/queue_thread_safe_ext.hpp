/* This file makes use of Doxygen syntax for generating documentation. */
/******************************************************************************/
/**
 *
 * @file queue_thread_safe_ext.hpp
 * @brief Extension of QueueThreadSafe.
 *
 * This contains the template class definition for an extension of the
 * QueueThreadSafe class. This extends the class by providing additional
 * features that are useful for threaded use of std::queue.
 * methods.
 *
 * @author John H. Willis (willisjh)
 * @date 24 November 2021
 *
 * @bug No known bugs.
 *
 * @addtogroup QueueThreadSafeExt
 * @{
 *
 ******************************************************************************/

#ifndef QUEUE_THREAD_SAFE_EXT_HPP
#define QUEUE_THREAD_SAFE_EXT_HPP

/******************************** Include Files *******************************/
#include <deque>
#include <condition_variable>

#include "common/thread_safe_container/queue_thread_safe.hpp"

/**************************** Constant Definitions ****************************/

/****************************** Type Definitions ******************************/

/**************************** Template Definitions ****************************/

template<class T, class T_CONTAINER = std::deque<T>>
class QueueThreadSafeExt : public QueueThreadSafe<T, T_CONTAINER>
{
public:
    /******************************************************************************/
    /**
     * @brief Method for waiting current thread until queue reaches requested size.
     *
     * @return None.
     *
     * @note Thread wake ups occur at every push().
     *
     ******************************************************************************/
    size_t sizeWait(size_t cElementReq) const
    {
        std::unique_lock<std::mutex> lock(QueueThreadSafe<T, T_CONTAINER>::m_mutexQueueThreadUnsafe);

        while (QueueThreadSafe<T, T_CONTAINER>::m_qThreadUnsafe.size() < cElementReq)
        {
            cond_size_wait_.wait(QueueThreadSafe<T, T_CONTAINER>::m_mutexQueueThreadUnsafe, [this] { return f_push_; });
            f_push_ = false;
        } 

        auto cElementLast = QueueThreadSafe<T, T_CONTAINER>::m_qThreadUnsafe.size();
        lock.unlock();
        return cElementLast;
    }

    /******************************************************************************/
    /**
     * @brief Overriding method for push() necessary for sizeWait().
     *
     * @return None.
     *
     * @note This method will only notify ONE thread of any pushes.
     *
     ******************************************************************************/
    void push(const T& value)
    {
        std::lock_guard<std::mutex> lock(QueueThreadSafe<T, T_CONTAINER>::m_mutexQueueThreadUnsafe);

        QueueThreadSafe<T, T_CONTAINER>::m_qThreadUnsafe.push(value);

        f_push_ = true;
        cond_size_wait_.notify_one();
    }

    /******************************************************************************/
    /**
     * @brief Method for combining front() and pop() for same element.
     *
     * @return None.
     *
     * @note This method is necessary to guarantee that front() and pop() operation
     * occurs for the same element.
     *
     ******************************************************************************/
    T frontAndPop()
    {
        std::lock_guard<std::mutex> lock(QueueThreadSafe<T, T_CONTAINER>::m_mutexQueueThreadUnsafe);

        auto elementFront = QueueThreadSafe<T, T_CONTAINER>::m_qThreadUnsafe.front();
        QueueThreadSafe<T, T_CONTAINER>::m_qThreadUnsafe.pop();

        return elementFront;
    }

private:
    std::condition_variable cond_size_wait_;
    bool f_push_;

};

#endif /* #ifndef QUEUE_THREAD_SAFE_EXT_HPP */
/** @} */ /* @addtogroup */
