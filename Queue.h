#ifndef KHAKI_QUEUE_H
#define KHAKI_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

namespace khaki {
template <typename T>
class queue {
public:
    queue() : mtx_(), cond_() {}
    ~queue(){}

    void push(const T& t) {
        std::unique_lock<std::mutex> lck(mtx_);
        m_msg_queue.push(t);
        lck.unlock();
        cond_.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lck(mtx_);
        while(m_msg_queue.empty()){
            cond_.wait(lck);
        }
        
        T t = m_msg_queue.front();
        m_msg_queue.pop_front();
        return t;
    }

    std::queue<T> popAll() {
        std::unique_lock<std::mutex> lck(mtx_);
        while(m_msg_queue.empty()){
            cond_.wait(lck);
        }

        std::queue<T> m_tmp_queue;
        m_tmp_queue.swap(m_msg_queue);
        return m_tmp_queue;
    }

    size_t size() {
        std::unique_lock<std::mutex> lck(mtx_);
        return m_msg_queue.size();
    }
private:
    std::mutex mtx_;
    std::condition_variable cond_;
    std::queue<T> m_msg_queue;
};
}
#endif