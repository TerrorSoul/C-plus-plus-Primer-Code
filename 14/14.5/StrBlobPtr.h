#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include "..\14.3\14.3.2\StrBlob.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::initializer_list;
using std::runtime_error;
using std::out_of_range;

class StrBlobPtr
{
	friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
	public:
		StrBlobPtr() : curr(0) { }
		StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) { }
		string& deref() const;
		StrBlobPtr& incr();
		std::string& operator[](std::size_t);
		const std::string& operator[](std::size_t) const;
	private:
		shared_ptr<vector<string>> check(size_t, const string&) const;
		weak_ptr<vector<string>> wptr;
		size_t curr;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
	{
		throw runtime_error("unbound StrBlobPtr");
	}
	if(i >= ret->size())
	{
		throw out_of_range(msg);
	}
	return ret;
}

string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

std::string& StrBlobPtr::operator[](std::size_t n)
{
	auto p = check(n, "dereference out of range");
	return p->at(n);
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return lhs.curr == rhs.curr;
}
bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return !(lhs == rhs);
}

bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return lhs.curr < rhs.curr;
}
bool operator>(const StrBlobPtr &lhs, const StrBlobPtr&rhs)
{
	return lhs.curr > rhs.curr;
}
bool operator<=(const StrBlobPtr &lhs, const StrBlobPtr&rhs)
{
	return lhs.curr <= rhs.curr;
}
bool operator>=(const StrBlobPtr &lhs, const StrBlobPtr&rhs)
{
	return lhs.curr >= rhs.curr;
}
