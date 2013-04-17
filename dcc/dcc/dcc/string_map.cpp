#include "string_map.h"

namespace dcc {

StringMap::StringMap()
	: bucket_count(2048)
{
	pages.push_back(Page(512));
	entries.reset(new Entry[bucket_count]);
}

StringMap::Entry& StringMap::find(const char* str)
{
	hash_t hash = get_hash(str);
	Entry* e = entries.get() + hash;
	while (e->ptr != nullptr) {
		if (!strcmp(str, e->ptr))
			return *e;
		if (!e->next)
			return e->next.reset(new Entry), *e->next;
	}
	return *e;
}

const char* StringMap::insert(const char* str)
{
	Entry& e = find(str);
	if (e.ptr)
		return e.ptr;
}

StringMap::hash_t StringMap::get_hash(const char* str)
{
	// djb2 hashing algorithm

	register hash_t hash = 5813;
	register char c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash % bucket_count;
}

}