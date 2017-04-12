#ifndef KHAKI_TIME_WHEEL_H
#define KHAKI_TIME_WHEEL_H

#include "net.h"
#include "log.h"

#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>

namespace khaki {

	typedef std::weak_ptr<TcpClient> TcpWeakPtr;

	class TimeWheel {
	public:
		
		TimeWheel(int size);
		~TimeWheel();

		int getTimeFd();
		void addTcpClient(const TcpClientPtr& con);
		void handlerRead();
	private:
		std::vector<std::unordered_map<int, TcpWeakPtr>> vWheel_;
		int timefd_;
		int index_;
		int size_;
	};
}

#endif // KHAKI_TIME_WHEEL_H