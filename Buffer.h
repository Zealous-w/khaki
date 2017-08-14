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
		std::string show();

	private:
		char* buf_;
		int size_, begin_, end_, cap_;
	};
}

#endif //KHAKI_BUFFER_H
