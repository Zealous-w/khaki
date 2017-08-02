#ifndef KHAKI_BUFFER_H
#define KHAKI_BUFFER_H

#include <string>
#include <string.h>
#include <assert.h>

namespace khaki{

	class Buffer {
	public:
		Buffer();
		Buffer(std::string& str);
		Buffer(const Buffer& buf);
		~Buffer();

		void clear();
		bool empty() const;
		int size() const;
		char* begin() const;
		char* end() const;
		char* data() const;
		void move();
		void append(const char* buf, int len);
		void alloc(int len);
		void addBegin(int len);
		
		bool checkInt8()
		{
			if (size() < sizeof(int8_t)) {
				return false;
			}
			int8_t data8 = 0;
			::memcpy(&data8, begin(), sizeof data8);
			if (data8 <= size()) {
				return true;
			}
			return false;
		}

		bool checkInt16()
		{
			if (size() < sizeof(int16_t)) {
				return false;
			}
			int16_t data16 = 0;
			::memcpy(&data16, begin(), sizeof data16);
			if (data16 <= size()) {
				return true;
			}
			return false;
		}

		bool checkInt32()
		{
			if (size() < sizeof(int32_t)) {
				return false;
			}
			int32_t data32 = 0;
			::memcpy(&data32, begin(), sizeof data32);
			if (data32 <= size()) {
				return true;
			}
			return false;
		}

		bool checkInt64()
		{
			if (size() < sizeof(int64_t)) {
				return false;
			}
			int64_t data64 = 0;
			::memcpy(&data64, begin(), sizeof data64);
			if (data64 <= size()) {
				return true;
			}
			return false;
		}

		int32_t readInt8()
		{
			assert(size() >= sizeof(int8_t));
			int8_t data8 = 0;
			::memcpy(&data8, begin(), sizeof data8);
			addBegin(sizeof(int8_t));
			return data8;
		}

		int32_t readInt16()
		{
			assert(size() >= sizeof(int16_t));
			int16_t data16 = 0;
			::memcpy(&data16, begin(), sizeof data16);
			addBegin(int(sizeof(int16_t)));
			return data16;
		}

		int32_t readInt32()
		{
			assert(size() >= sizeof(int32_t));
			int32_t data32 = 0;
			::memcpy(&data32, begin(), sizeof data32);
			addBegin(sizeof(int32_t));
			return data32;
		}

		int32_t readInt64()
		{
			assert(size() >= sizeof(int64_t));
			int64_t data64 = 0;
			::memcpy(&data64, begin(), sizeof data64);
			addBegin(sizeof(int64_t));
			return data64;
		}

		std::string readStringByLen(int len) 
		{
			assert(size() >= len);
			std::string buf(begin(), len);
			addBegin(len);
			return buf;
		}

		std::string show();

	private:
		char* buf_;
		int size_, begin_, end_, cap_;
	};
}

#endif //KHAKI_BUFFER_H
