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

		[[nodiscard]] const bool& IsAltPatch() const noexcept { return bAltPatch; }
		[[nodiscard]] const std::uint32_t& MaxTriangles() const noexcept { return uMaxTriangles; }
		[[nodiscard]] const std::uint32_t& MaxDraws() const noexcept { return uMaxDraws; }

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
	};
}