#ifndef KHAKI_CHANNEL_H
#define KHAKI_CHANNEL_H
#include "poll.h"
#include "EventLoop.h"

namespace khaki{

    class Channel : public noncopyable {
    public:
        typedef std::function<void()> FunctionCallback_;

        Channel(EventLoop* loop, int fd, int event);

        ~Channel();
        EventLoop* getEventLoop();
        int getEvents();
        int fd();

        void OnRead(const FunctionCallback_& readcb);
        void OnWrite(const FunctionCallback_& writecb);

        void enableRead();
        void enableWrite();

        void handleRead();
        void handleWrite();
    private:
        EventLoop* loop_;
        PollBase*  poll_;
        int events;
        int fd_;

        FunctionCallback_ readcb_, writecb_;
    };
}

#endif //KHAKI_CHANNEL_H
