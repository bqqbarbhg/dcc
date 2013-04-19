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
			: size(size), pos(0), buffer(new char[size])
		{
		}
		Page(Page&& p)
			: buffer(std::move(p.buffer))
			, pos(pos), size(size) { }
		Page& operator=(Page&& p) {
			buffer = std::move(p.buffer);
			pos = p.pos; size = p.size;
		}
		
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
		std::vector<Entry> entries;
	};
	class BaseEntry : public Entry
	{
		std::unique_ptr<EntryList> entrylistptr;
	};
	

	Entry& find(const char* ptr);

	std::unique_ptr<Entry[]> entries;

	hash_t get_hash(const char* str);

	unsigned int bucket_count;
	std::vector<Page> pages;
};

}

#endif