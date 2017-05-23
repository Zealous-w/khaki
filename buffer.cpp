#include "buffer.h"
#include "util.h"
#include <algorithm>
#include <cstring>
#include <iostream>

namespace khaki{

Buffer::Buffer() : buf_(NULL), begin_(0), end_(0), cap_(0), size_(0) {

}

Buffer::Buffer(const Buffer& buf)
{
	buf_ = new char[buf.size()];
	memcpy(buf_, buf.buf_, (size_t)buf.size());
	begin_ = 0;
	end_ = buf.size();
	cap_ = buf.size();
	size_ = buf.size();
}

Buffer::~Buffer() {
	if (buf_) delete[] buf_;
}

void Buffer::clear() {
	size_ = 0;
	begin_ = 0;
	end_ = 0;
}

bool Buffer::empty() const {
	return (end_ - begin_ > 0) ? false : true;
}

int Buffer::size() const {
	return end_ - begin_;
}

char* Buffer::begin() const {
	return buf_ + begin_;
}

char* Buffer::end() const {
	return buf_ + end_;
}

char* Buffer::data() const {
	return buf_ + begin_;
}

void Buffer::move()
{
	std::copy(begin(), end(), buf_);
	end_ -= begin_;
	begin_ = 0;
}

void Buffer::append(char* buf, int len)
{
	move();
	if (end_ + len > cap_) alloc(end_ + len);
	std::copy(buf, buf + len, end());
	end_ += len;
}

void Buffer::alloc(int len)
{
	//std::cout << len << std::endl;
	char* bufTemp = new char[2 * len];
	memset(bufTemp, 0, 2 * len);
	std::copy(begin(), end(), bufTemp);
	delete[] buf_;
	buf_ = bufTemp;
	end_ -= begin_;
	begin_ = 0;
	cap_ = 2 * len;
}

void Buffer::addBegin(int len)
{	
	begin_ += len;
}

std::string Buffer::show()
{
	return util::string_format("[%d %d %d]", begin_, end_, cap_);
}
}
