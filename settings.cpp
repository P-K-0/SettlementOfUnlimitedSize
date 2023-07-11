
#include "settings.h"

namespace Settings {

	void Manager::Read() noexcept
	{
		CSimpleIni ini;

		ini.SetUnicode();
		auto error = ini.LoadFile(IniFile);

		if (error != SI_OK) {

			ini.LoadData(
				"[Main]\n\n"
				"; enable the alternative patch that allows you to exceed the limit of 4294967295 imposed by the game (disabled by default)\n"
				"bAltPatch = 0\n\n"
				"; only used if the alternate patch is disabled\n"
				"uMaxTriangles = 4294967295\n"
				"uMaxDraws = 4294967295\n");

			ini.SaveFile(IniFile);
		}

		bAltPatch = std::stoi(ini.GetValue("Main", "bAltPatch", "0"));

		uMaxTriangles = std::stoul(ini.GetValue("Main", "uMaxTriangles", std::to_string(0xffffffff).c_str()));
		uMaxDraws = std::stoul(ini.GetValue("Main", "uMaxDraws", std::to_string(0xffffffff).c_str()));
	}
}
