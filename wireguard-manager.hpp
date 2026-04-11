#include "wireguard.h"
#include <cstdint>
#include <netinet/in.h>
#include <vector>
#include <string>

typedef struct wgm_pool
{
	uint16_t family;
	union {
		struct in_addr ip4;
		struct in6_addr ip6;
	};
	uint8_t cidr;
	struct wgm_pool *next_pool;
} wgm_pool; // The same as wg_allowedip

typedef struct wgm_peer
{
	std::string peer_name;
	std::string public_key;
} wgm_peer;

typedef struct wgm_group
{
	std::string group_name;
	wgm_pool* pool;
	wgm_pool* allowed_pools;
	std::vector<wgm_peer*> peers;

	std::string serialize();
	std::string deserialize(std::string content);
} wgm_group;

typedef struct wgm_device
{
	wg_device* dev;
	std::vector<wgm_group*> groups;
} wgm_device;

int wgm_del_device(void);
std::vector<wgm_group> wgm_list_groups(); 
std::vector<wgm_peer> wgm_list_peers(const char* group_name);
int wgm_add_peer(const char* group_name, const char* peer_name);
int wgm_del_peer(const char* group_name, const char* peer_name);
std::string wgm_get_peer_config(const char* group_name, const char* peer_name);
int wgm_apply(void);