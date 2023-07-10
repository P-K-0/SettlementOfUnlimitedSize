#pragma once

namespace Patch {

	void write_value(std::uint32_t value, std::uintptr_t offset)
	{
		REL::Relocation<std::uintptr_t> GetBudgetFraction_void{ REL::ID(1282871) };

		// mov eax, 0x00000000
		// nop
		std::uint8_t mov[]{ 0xb8, 0x00, 0x00, 0x00, 0x00, 0x90 }; 

		std::memcpy(&mov[1], &value, 4);

		REL::safe_write(GetBudgetFraction_void.address() + offset, mov, 6);
	}

	void Install() noexcept
	{
		static bool installed{};

		if (installed)
			return;

		write_value(0xffffffff, 0x14); // max triangles
		write_value(0xffffffff, 0x2a); // max draws

		logger::info("Patch successfully installed!");

		installed = true;
	}
}
