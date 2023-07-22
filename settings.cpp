
#include "settings.h"

#include <SimpleIni.h>

namespace Settings {

	inline const char* GetValue(CSimpleIni& ini, const char* section, const char* key, const char* def) noexcept
	{
		auto ret = ini.KeyExists(section, key);

		if (ret)
			return ini.GetValue(section, key, def);

		ini.SetValue(section, key, def);
		ini.SaveFile(IniFile);

		return def;
	}

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
				"uMaxDraws = 4294967295\n\n"
				"iWorkshopSettlerPopulationMax = 100\n"
				"bShelteredBedsCountPatch = 1\n");

			ini.SaveFile(IniFile);
		}

		bAltPatch = std::stoi(GetValue(ini, "Main", "bAltPatch", "0"));
		uMaxTriangles = std::stoul(GetValue(ini, "Main", "uMaxTriangles", std::to_string(UINT_MAX).c_str()));
		uMaxDraws = std::stoul(GetValue(ini, "Main", "uMaxDraws", std::to_string(UINT_MAX).c_str()));
		iWorkshopSettlerPopulationMax = std::stoul(GetValue(ini, "Main", "iWorkshopSettlerPopulationMax", "100"));
		bShelteredBedsCountPatch = std::stoi(GetValue(ini, "Main", "bShelteredBedsCountPatch", "1"));
	}
}
