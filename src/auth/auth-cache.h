#ifndef __AUTH_CACHE_H
#define __AUTH_CACHE_H

struct auth_cache;
struct auth_request;

/* Parses all %x variables from query and compresses them into tab-separated
   list, so it can be used as a cache key. */
char *auth_cache_parse_key(const char *query);

/* Create a new cache. max_size specifies the maximum amount of memory in
   bytes to use for cache (it's not fully exact). ttl_secs specifies time to
   live for cache record, requests older than that are not used. */
struct auth_cache *auth_cache_new(size_t max_size, unsigned int ttl_secs);
void auth_cache_free(struct auth_cache *cache);

/* Clear the cache. */
void auth_cache_clear(struct auth_cache *cache);

/* Look key from cache. key should be the same string as returned by
   auth_cache_parse_key(). */
const char *auth_cache_lookup(struct auth_cache *cache,
			      const struct auth_request *request,
			      const char *key, int *expired_r);
/* Insert key => value into cache. */
void auth_cache_insert(struct auth_cache *cache,
		       const struct auth_request *request,
		       const char *key, const char *value);

#endif
