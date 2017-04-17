#include "time_wheel.h"
#include "util.h"
#include "log.h"

namespace khaki {

		TimeWheel::TimeWheel(int size) : index_(0), size_(size) 
		{
			timefd_ = timerfd_create(CLOCK_REALTIME, 0);

			struct timespec now;
			clock_gettime(CLOCK_REALTIME, &now);

			struct itimerspec to;
			to.it_value.tv_sec = now.tv_sec + 1;
			to.it_value.tv_nsec = now.tv_nsec;
			to.it_interval.tv_sec = 1;
			to.it_interval.tv_nsec = 0;
			timerfd_settime(timefd_, TFD_TIMER_ABSTIME, &to, NULL);

			vWheel_.resize(size_);
		}

		TimeWheel::~TimeWheel()
		{
			close(timefd_);
		}

		int TimeWheel::getTimeFd()
		{
			return timefd_;
		}

		void TimeWheel::addTcpClient(const TcpClientPtr& con)
		{
			TcpWeakPtr wCliPtr(con);
			int pos = index_ == 0 ? size_ - 1 : index_ - 1;
			vWheel_[pos].insert( std::make_pair(con->getFd(), wCliPtr));
		}

		void TimeWheel::showTimeWheel()
		{
			int index = 0;
			std::string str;
			str += "\n   ----------------\n";
			for ( auto vMp : vWheel_ )
			{
				if ( index == index_ ) str += "==>";
				else str += "   ";

				str = util::string_format("%s[%d] : ", str.c_str(), index );
				for ( auto mIn : vMp )
				{
					str += "->*";
				}
				str += "\n";
				index++;
			}
			str +="   ----------------\n";
			klog_debg(str.c_str());
		}

		void TimeWheel::handlerRead()
		{
			uint64_t exp; 
			read(timefd_, &exp, sizeof(uint64_t) );

			showTimeWheel();
			int now = util::getTime();
			for ( auto wp : vWheel_[index_] )
			{	
				if ( !wp.second.expired() )
				{
					TcpClientPtr con = wp.second.lock();
					klog_info("time wheel, lasttime = %d, size = %d, now=%d", con->getLastTime(), size_, now);
					if (con->getLastTime() + size_ - 1 <= now) con->closeClient(con);
				} 
			}

			vWheel_[index_].clear();

			index_++;
			if ( index_ == size_ ) index_ = 0;
		}
}