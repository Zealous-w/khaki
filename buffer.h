#ifndef KHAKI_BUFFER_H
#define KHAKI_BUFFER_H

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

	private:
		char* buf_;
	};
}

#endif //KHAKI_BUFFER_H
