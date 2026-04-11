// Copyright (C) Alexandr Kosolobov

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cstdint>
#include <string>
#include <cxxopts.hpp>
#include "wireguard-manager.hpp"

struct
{
	uint8_t major = 0;
	uint8_t minor = 0;
	uint8_t feature = 0;
	uint8_t patch = 0;
} WGM_VERSION;

int main(int argc, char* argv[])
{

	const char* CMD_CREATE_DEVICE =		"create-device";
	const char* CMD_CREATE_PEER =		"add-peer";
	const char* CMD_REMOVE_DEVICE =		"remove-device";
	const char* CMD_REMOVE_PEER =		"remove-peer";
	const char* CMD_LIST_DEVICES =		"list-device";
	const char* CMD_LIST_PEERS =		"list-peers";

	const char* OPT_COMMAND =           "c,command";
	const char* OPT_GROUP = 			"g,group";
	const char* OPT_PEER =              "p,peer";
	const char* OPT_HELP =              "h,help";
	const char* OPT_VERBOSE =           "v,verbose";
	const char* OPT_DEBUG =             "d,debug";
	const char* OPT_VERSION =           "V,version";

	const char* NOTICE = R"(WireGuard-Manager Copyright (C) 2026  Alexandr Kosolobov
This program comes with ABSOLUTELY NO WARRANTY;
This is free software, and you are welcome 
to redistribute it under certain conditions;
)";

	std::string command;
	std::string interface;
	std::string peer;
	bool f_verbose = false;
	bool f_debug = false;

	cxxopts::Options options("WireGuard-Manager", NOTICE);

	options.add_options()

		("c,command",   "Command (create-interface|add-peer|remove-interface|remove-peer|list-interfaces|list-peers)", 
			cxxopts::value<std::string>())

		("i,interface", "Interface name", 
			cxxopts::value<std::string>())

		("p,peer",      "Peer name", 
			cxxopts::value<std::string>())

		("h,help",      "Print this message and exit"
			)

		("v,verbose",   "Verbose output (with logs)", 
			cxxopts::value<bool>()->default_value("false"))

		("V,version",   "Print version and exit"
			)

		("d,debug",     "Very verbose output (ignore -v)", 
			cxxopts::value<bool>()->default_value("false"))
	;

	auto result = options.parse(argc, argv);

	// Help or no arguments
	if (result.count("help") || argc == 0)
	{
		printf("%s\n", options.help().c_str());
		exit(0);
	}

	// Version

	if (result.count("version"))
	{
		printf("WireGuard-Manager V%d.%d.%d.%d\n", WGM_VERSION.major, WGM_VERSION.minor, WGM_VERSION.feature, WGM_VERSION.patch);
		exit(0);
	}

	// No command

	if (!result.count("command"))
	{
		printf("\n\t--command <command> REQUIRED!\n\n%s\n", options.help().c_str());
		exit(0);
	}

	// Interface and peer

	if (result.count("interface"))
	{
		interface = result["interface"].as<std::string>();
	} 
	if (result.count("peer"))
	{
		peer = result["peer"].as<std::string>();
	}

	// Command action

	command = result["command"].as<std::string>();
	if (command == CMD_CREATE_DEVICE && !interface.empty())
	{
		wg_device dev;
		wg_generate_private_key(dev.private_key);
		wg_generate_public_key(dev.public_key, dev.private_key);

		// Do i really need it here?
		// wg_key_b64_string private_key_str;
		// wg_key_b64_string public_key_str;
		// wg_key_to_base64(private_key_str, dev.private_key);
		// wg_key_to_base64(public_key_str, dev.public_key);


	} 
	else if (command == CMD_CREATE_PEER && !interface.empty() && !peer.empty())
	{
		wg_key private_key;
		wg_key public_key;
		wg_generate_private_key(private_key);
		wg_generate_public_key(public_key, private_key);
		wg_key_b64_string private_key_str;
		wg_key_b64_string public_key_str;
		wg_key_to_base64(private_key_str, private_key);
		wg_key_to_base64(public_key_str, public_key);
	} 
	else if (command == CMD_REMOVE_DEVICE && !interface.empty())
	{

	} 
	else if (command == CMD_REMOVE_PEER && !interface.empty() && !peer.empty())
	{

	} 
	else if (command == CMD_LIST_DEVICES)
	{

	} 
	else if (command == CMD_LIST_PEERS && !interface.empty())
	{

	} 
	else 
	{
		printf("\n\tSomethins went wrong...\n");
	}

	// Flags

	f_verbose = result["verbose"].as<bool>();
	f_debug = result["debug"].as<bool>();

	// Logs

	printf("command: %s\ninterface: %s\npeer: %s\nverbose: %s\ndebug: %s\n", 
		command.c_str()
		,interface.c_str()
		,peer.c_str()
		,f_verbose ? "yes" : "no"
		,f_debug ? "yes" : "no"
	);

	return 0;
}