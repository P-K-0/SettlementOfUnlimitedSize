#pragma once

#include "PCH.h"

namespace Settings {

	constexpr auto IniFile = "Data\\F4SE\\Plugins\\SettlementOfUnlimitedSize.ini";

	class Manager {

	public:

		[[nodiscard]] static Manager& GetSingleton() noexcept
		{
			static Manager instance;
			return instance;
		}

		[[nodiscard]] const auto& IsAltPatch() const noexcept { return bAltPatch; }
		[[nodiscard]] const auto& MaxTriangles() const noexcept { return uMaxTriangles; }
		[[nodiscard]] const auto& MaxDraws() const noexcept { return uMaxDraws; }
		[[nodiscard]] const auto& WorkshopSettlerPopulationMax() const noexcept { return iWorkshopSettlerPopulationMax; }
		[[nodiscard]] const auto& ShelteredBedsCountPatch() const noexcept { return bShelteredBedsCountPatch; }

		void Read() noexcept;

	private:

		Manager() = default;
		~Manager() = default;

		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;

		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;

		bool bAltPatch{};
		std::uint32_t uMaxTriangles{};
		std::uint32_t uMaxDraws{};

		std::uint32_t iWorkshopSettlerPopulationMax{};

		bool bShelteredBedsCountPatch{};
	};
}