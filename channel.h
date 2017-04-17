#ifndef KHAKI_CHANNEL_H
#define KHAKI_CHANNEL_H

#include "poll.h"

namespace khaki{
    class EventLoop;
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

        bool readStatus();
        bool writeStatus();

        void enableRead(bool enable);
        void enableWrite(bool enable);

        void handleRead();
        void handleWrite();
    private:
        EventLoop* loop_;
        PollBase*  poll_;
        int events_;
        int fd_;

        FunctionCallback_ readcb_, writecb_;
    };
}

#endif //KHAKI_CHANNEL_H
