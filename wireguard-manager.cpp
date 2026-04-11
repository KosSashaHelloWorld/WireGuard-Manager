#include "wireguard-manager.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
extern "C"
{
#include "wireguard.h"
}

const char* WGM_DEFAULT_DEVICE_NAME =	"wgm0";
const char* WGM_CONFIG =            	"/etc/wireguard-manager/wireguard-manager.conf";
const char* WGM_GROUPS_CONFIG = 		"/etc/wireguard-manager/groups.conf";
const char* WGM_GROUPS_DIR = 			"/etc/wireguard-manager/groups.d/";
const char* WGM_LOG_FILE =          	"/var/log/wireguard-manager.log";

std::string wgm_group::serialize()
{
	std::stringstream ss;

	ss << "[" << group_name << "]\n";

	ss << "AddressPool = ";
	auto pp = pool;
	while (pp)
	{
		ss << pp->ip4.s_addr << '/' << pp->cidr << ',';
		pp = pp->next_pool;
	}
	ss << std::endl;

	ss << "AllowedGroups = ";
	pp = allowed_pools;
	while (pp)
	{
		ss << pp->ip4.s_addr << '/' << pp->cidr << ',';
		pp = pp->next_pool;
	}
	ss << std::endl;

	return ss.str();
}

std::string wgm_group::deserialize(std::string content) 
{
  // TODO: implement me
}

int wgm_del_device(void) 
{
	return wg_del_device(WGM_DEFAULT_DEVICE_NAME);
}

std::vector<wgm_group> wgm_list_groups() 
{
	std::ifstream f(WGM_GROUPS_CONFIG);
	std::vector<wgm_group> groups;
	if (f.is_open())
	{
		wgm_group g;
		std::string line;
		while (std::getline(f, line))
		{
			// TODO: implement me
		}
		f.close();
	}
	return groups;
}

std::vector<wgm_peer> wgm_list_peers(const char *group_name) 
{
	std::vector<wgm_peer> peers;
	std::ifstream f(std::string(WGM_GROUPS_DIR) + group_name);
	if (f.is_open())
	{
		std::string line;
		while (std::getline(f, line))
		{
			wgm_peer p;
			std::stringstream ss(line);
			std::string key, pname;
			ss >> p.public_key >> p.peer_name;
			peers.push_back(p);
		}
	}
	return peers;
}

int wgm_add_peer(const char *group_name, const char *peer_name) 
{
  // TODO: implement me
}

int wgm_del_peer(const char *group_name, const char *peer_name) 
{
  // TODO: implement me
}

std::string wgm_get_peer_config(const char *group_name, const char *peer_name) 
{
  // TODO: implement me
}

int wgm_apply(void) 
{
	// TODO: implement me
}