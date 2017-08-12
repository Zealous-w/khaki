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
		uint32_t size() const;
		char* begin() const;
		char* end() const;
		char* data();
		void move();
		void append(const char* buf, uint32_t len);
		void alloc(uint32_t len);
		void addBegin(uint32_t len);
		
		uint8_t checkInt8()
		{
			if (size() < sizeof(uint8_t)) {
				return false;
			}
			uint8_t data8 = 0;
			::memcpy(&data8, begin(), sizeof data8);
			return data8;
		}

		uint16_t checkInt16()
		{
			if (size() < sizeof(uint16_t)) {
				return false;
			}
			uint16_t data16 = 0;
			::memcpy(&data16, begin(), sizeof data16);
			return data16;
		}

		uint32_t checkInt32()
		{
			if (size() < sizeof(uint32_t)) {
				return false;
			}
			uint32_t data32 = 0;
			::memcpy(&data32, begin(), sizeof data32);
			return data32;
		}

		uint64_t checkInt64()
		{
			if (size() < sizeof(uint64_t)) {
				return false;
			}
			uint64_t data64 = 0;
			::memcpy(&data64, begin(), sizeof data64);
			// if (data64 <= size()) {
			// 	return true;
			// }
			// return false;
			return data64;
		}

		uint8_t readInt8()
		{
			assert(size() >= sizeof(uint8_t));
			uint8_t data8 = 0;
			::memcpy(&data8, begin(), sizeof data8);
			addBegin(sizeof(uint8_t));
			return data8;
		}

		uint16_t readInt16()
		{
			assert(size() >= sizeof(uint16_t));
			uint16_t data16 = 0;
			::memcpy(&data16, begin(), sizeof data16);
			addBegin(int(sizeof(uint16_t)));
			return data16;
		}

		uint32_t readInt32()
		{
			assert(size() >= sizeof(uint32_t));
			uint32_t data32 = 0;
			::memcpy(&data32, begin(), sizeof data32);
			addBegin(sizeof(uint32_t));
			return data32;
		}

		uint64_t readInt64()
		{
			assert(size() >= sizeof(uint64_t));
			uint64_t data64 = 0;
			::memcpy(&data64, begin(), sizeof data64);
			addBegin(sizeof(uint64_t));
			return data64;
		}

		std::string readStringByLen(uint32_t len) 
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
