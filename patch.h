#pragma once

#include "settings.h"

namespace Patch {

	constexpr auto GetBudgetFractionID = REL::ID(1282871);
	constexpr auto GetAvailableCountID = REL::ID(1583245);

	static inline REL::Relocation<std::uint32_t*> iWorkshopSettlerPopulationMax{ REL::ID(325973) };

	struct GetActorValue {

		static float thunk(RE::ActorValueOwner* a_this, RE::ActorValueInfo* a_info)
		{
			auto value = func(a_this, a_info);

			if (a_this && a_info && a_info->GetFormID() == 0x334)
				value = a_this->GetBaseActorValue(*a_info);

			return value;
		}

		static inline REL::Relocation<decltype(thunk)> func;

		static inline std::uintptr_t index = 0xf5;
		static inline auto vtbl = RE::TESObjectREFR::VTABLE;
	};

	void Install() noexcept
	{
		static bool installed{};

		if (installed)
			return;

		auto& settings = Settings::Manager::GetSingleton();

		if (settings.ShelteredBedsCountPatch()) {

			stl::write_vfunc<GetActorValue>();
		
			logger::info("Sheltered Beds count Patch successfully installed!");
		}

		if (settings.IsAltPatch()) {

			// nop x 5
			std::uint8_t nop[]{ 0x90, 0x90, 0x90, 0x90, 0x90 };

			stl::write_value(GetBudgetFractionID, 0x0f, nop, sizeof nop); // max triangles
			stl::write_value(GetBudgetFractionID, 0x25, nop, sizeof nop); // max draws

			logger::info("Alternative Patch successfully installed!");
		}
		else {

			// mov eax, 0x00000000
			// nop
			std::uint8_t mov[]{ 0xb8, 0x00, 0x00, 0x00, 0x00, 0x90 };

			stl::write_value(GetBudgetFractionID, 0x14, settings.MaxTriangles(), mov, sizeof mov, 1); // max triangles
			stl::write_value(GetBudgetFractionID, 0x2a, settings.MaxDraws(), mov, sizeof mov, 1); // max draws

			logger::info("Patch successfully installed!");
		}

		if (iWorkshopSettlerPopulationMax.get()) {

			*iWorkshopSettlerPopulationMax = settings.WorkshopSettlerPopulationMax();
		
			logger::info("Settler Population Max : {}", *iWorkshopSettlerPopulationMax);
		}

		installed = true;
	}
}
