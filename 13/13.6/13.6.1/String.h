#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>
 
class String
{
	public:
		String() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
		String(const char*);
		String(const String&); 
		~String();
		String& operator=(const String&);
		size_t size() const
		{
			return first_free - elements;
		}
		size_t capacity() const
		{
			return cap - elements;
		}
	private:
		static std::allocator<char> alloc;
		void chk_n_alloc()
		{
			if(size() == capacity())
			{
				reallocate();
			}
		}
		std::pair<char*, char*> alloc_n_copy(const char*, const char*);
		void free();
		void reallocate();
		char *elements;
		char *first_free;
		char *cap;
};

std::allocator<char> String::alloc;

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e)
{
	auto data = alloc.allocate(e - b);
	return {data, std::uninitialized_copy(b, e, data)};
}

void String::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](const char &rhs){alloc.destroy(&rhs);});
		alloc.deallocate(elements, cap - elements);
	}
}

String::String(const char* s)
{
	char* s1 = const_cast<char*>(s);
	while(*s1)
	{
		++s1;
	}
	auto newdata = alloc_n_copy(s, s1);
	elements = newdata.first;
	first_free = cap = newdata.second;
}

String::String(const String &sv)
{
	auto newdata = alloc_n_copy(sv.elements, sv.first_free);
	elements = newdata.first;
	first_free = cap = newdata.second;
	std::cout << "�������캯��" << std::endl;
}

String& String::operator=(const String &sv)
{
	auto newdata = alloc_n_copy(sv.elements, sv.first_free);
	elements = newdata.first;
	first_free = cap = newdata.second;
	std::cout << "������ֵ�����" << std::endl;
}

String::~String()
{
	free();
}

void String::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for(size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
