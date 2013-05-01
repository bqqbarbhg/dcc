#ifndef _DCC_STRING_MAP_H
#define _DCC_STRING_MAP_H

#include <dcc/enums.h>
#include <dcc/string_ref.h>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>

namespace dcc {

class StringMap
{
public:
	StringMap();

	// Inserts the (0-terminated) string in the map and returns a reference
	// to it. Returned value is always the same for strings with the same
	// content
	StringRef insert(const char* str);
	
private:
	// Integer type that holds the hashed value of strings
	typedef unsigned int hash_t;

	// A stable buffer where the strings are stored
	// If the space runs out a new bigger Page will be allocated and will
	// replace the page for allocating. The old page will be kept alive
	// until the newer page is destroyed
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
		
		// Insert a new string to the page (a new page will be created and
		// will replace this Page if there is not enough space)
		const char* insert(const char* str, unsigned int len);

		// Pointer to the page that was allocated before this one (nullptr for first page)
		std::unique_ptr<Page> old;

		// The buffer that holds the strings (`size` sized)
		std::unique_ptr<char[]> buffer;

		// The size of `buffer`
		unsigned int size;

		// The current position for storing new strings
		unsigned int pos;
	private:
		Page(const Page&);
		Page& operator=(const Page&);
	};

	// A Hashmap entry
	class Entry
	{
	public:
		// Pointer to the stored string
		const char* ptr;

		// Length of the stored string
		unsigned int len;

		// Number of times the string has been inserted into the map
		unsigned int count;

		Entry& swap(Entry& other)
		{
			std::swap(ptr, other.ptr);
			std::swap(len, other.len);
			std::swap(count, other.count);
			return *this;
		}
	};
	// An Entry that contains a pointer to a possible list of entries
	// that share the hash with the Entry
	class BaseEntry : public Entry
	{
	public:
		std::unique_ptr<std::vector<Entry>> entrylistptr;
	};
	
	// Insert (or find) an entry in the bucket
	Entry& entry_insert(BaseEntry* entry, const char *str, unsigned int len);


	// Pointer to `bucket_count` BaseEntries
	std::unique_ptr<BaseEntry[]> entries;

	// Number of `entries`
	unsigned int bucket_count;

	// Returns a hash from the string and stores the length of the string in
	// `len` if not nullptr
	hash_t get_hash(const char* str, unsigned int *len);

	// The current Page for storing the strings
	Page page;
};

}

#endif