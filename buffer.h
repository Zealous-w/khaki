#ifndef KHAKI_BUFFER_H
#define KHAKI_BUFFER_H

#include <string>

namespace khaki{

	class Buffer {
	public:
		Buffer();
		~Buffer();

		void clear();
		bool empty() const;
		int size() const;
		char* begin() const;
		char* end() const;
		char* data() const;
		void move();
		void append(char* buf, int len);
		void alloc(int len);
		void addBegin(int len);
		std::string show();

	private:
		char* buf_;
		int size_, begin_, end_, cap_;
	};
}

#endif //KHAKI_BUFFER_H
