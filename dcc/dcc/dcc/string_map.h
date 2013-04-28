#ifndef _DCC_STRING_MAP_H
#define _DCC_STRING_MAP_H

#include <dcc/enums.h>
#include <dcc/string_ref.h>
#include <memory>
#include <utility>
#include <vector>

namespace dcc {

class StringMap
{
public:
	StringMap();
	const char* insert(const char* str);
	
private:
	typedef unsigned int hash_t;

	class Page
	{
	public:
		Page(unsigned int size)
			: size(size), pos(0), buffer(new char[size]), old(nullptr)
		{
		}
		Page(Page&& p)
			: buffer(std::move(p.buffer))
			, old(std::move(p.old))
			, pos(pos), size(size) { }
		Page& operator=(Page&& p) {
			buffer = std::move(p.buffer);
			old = std::move(p.old);
			pos = p.pos; size = p.size;
		}
		
		const char* insert(const char* str, unsigned int len);

		std::unique_ptr<Page> old;
		std::unique_ptr<char[]> buffer;
		unsigned int pos, size;
	private:
		Page(const Page&);
		Page& operator=(const Page&);
	};
	class Entry
	{
	public:
		const char* ptr;
		unsigned int len;
		unsigned int count;

		Entry& swap(Entry& other);
	};
	class EntryList
	{
	public:
		std::vector<Entry> entries;
	};
	class BaseEntry : public Entry
	{
		public:
		std::unique_ptr<EntryList> entrylistptr;
	};
	

	Entry& find(const char* ptr, BaseEntry **base);

	std::unique_ptr<BaseEntry[]> entries;

	hash_t get_hash(const char* str, unsigned int *len);

	unsigned int bucket_count;
	Page page;
};

}

#endif