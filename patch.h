#pragma once

#include "settings.h"

namespace Patch {

	static inline REL::Relocation<std::uintptr_t> GetBudgetFraction_void{ REL::ID(1282871) };

	void write_value(std::uint32_t value, std::uintptr_t offset)
	{
		// mov eax, 0x00000000
		// nop
		std::uint8_t mov[]{ 0xb8, 0x00, 0x00, 0x00, 0x00, 0x90 }; 

		std::memcpy(&mov[1], &value, 4);

		REL::safe_write(GetBudgetFraction_void.address() + offset, mov, sizeof mov);
	}

	void write_nop(std::uintptr_t offset)
	{
		// nop x 5
		std::uint8_t nop[]{ 0x90, 0x90, 0x90, 0x90, 0x90 };

		REL::safe_write(GetBudgetFraction_void.address() + offset, nop, sizeof nop);
	}

	void Install() noexcept
	{
		static bool installed{};

		if (installed)
			return;

		auto& settings = Settings::Manager::GetSingleton();

		if (settings.IsAltPatch()) {

			write_nop(0x0f);
			write_nop(0x25);

			logger::info("Alternative Patch successfully installed!");
		}
		else {

			write_value(settings.MaxTriangles(), 0x14); // max triangles
			write_value(settings.MaxDraws(), 0x2a); // max draws

			logger::info("Patch successfully installed!");
		}

		installed = true;
	}
}
