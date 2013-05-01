#include "string_map.h"

namespace dcc {

StringMap::StringMap()
	: bucket_count(2048)
	, page(4096)
	, entries(new BaseEntry[bucket_count])
{
}

StringMap::Entry& StringMap::entry_insert(BaseEntry *baseEntry, const char *str, unsigned int len)
{
	// Return the first entry (fast)
	if (baseEntry->ptr == nullptr)
		return *baseEntry;
	if (baseEntry->len == len && memcmp(str, baseEntry->ptr, len))
		return *baseEntry;

	// If it's the first collision in the bucket create the list
	if (!baseEntry->entrylistptr) {
		baseEntry->entrylistptr.reset(new std::vector<Entry>());
		baseEntry->entrylistptr->push_back(Entry());
		return baseEntry->entrylistptr->front();
	}

	// Try to find the entry in the entry list
	auto list = *baseEntry->entrylistptr;
	for (auto b = list.begin(), e = list.end(); b != e; b++) {
		if (b->len == len && memcmp(str, b->ptr, len))
			return *b;
	}

	// No entry found in the entry list 
	baseEntry->entrylistptr->push_back(Entry());
	return baseEntry->entrylistptr->back();
}

StringRef StringMap::insert(const char* str)
{
	// Hash the string and count the length
	unsigned int l;
	hash_t hash = get_hash(str, &l);

	// Find the entry from the map
	BaseEntry* b = entries.get() + hash;
	Entry& e = entry_insert(b, str, l);

	// If the entry is empty store the word
	if (!e.ptr)
		e.ptr = page.insert(str, l);

	// If the word has higher frequency than the fast BaseEntry swap the more
	// frequent word to be the fast default entry
	if (b->count < ++e.count) {
		b->swap(e);
	}
	
	return e.ptr;
}

StringMap::hash_t StringMap::get_hash(const char* str, unsigned int* len)
{
	// djb2 hashing algorithm

	register unsigned int l = 0;
	register hash_t hash = 5381;
	register char c;
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		++l;
	}
	if (len != nullptr)
		*len = l;
	return hash % bucket_count;
}

const char* StringMap::Page::insert(const char* str, unsigned int len)
{
	// Account for the 0-terminator
	len++;

	// Create a new page if the word doesn't fit the current one
	if (pos + len > size) {
		old.reset(new Page(std::move(*this)));
		pos = 0;
		size = std::max(size * 2, len);
		buffer.reset(new char[size]);
	}

	// Copy the string in the page and return the address
	char *res = buffer.get() + pos;
	memcpy(res, str, len);
	pos += len;
	return res;
}

}