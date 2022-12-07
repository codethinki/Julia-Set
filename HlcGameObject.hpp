#pragma once
#include "HlcModel.hpp"

#include <memory>
namespace hlc {
	using namespace std;
	class HlcGameObject {
	public:
		using id_t = unsigned int;
		static HlcGameObject createGameObject() {
			static id_t currentId = 0;
			return HlcGameObject{ currentId++ };
		}
		HlcGameObject(const HlcGameObject&) = delete;
		HlcGameObject& operator=(const HlcGameObject&) = delete;
		HlcGameObject(HlcGameObject&&) = default;
		HlcGameObject& operator=(HlcGameObject&&) = default;

		id_t getId() { return id; };
		shared_ptr<HlcModel> model;

	private:
		HlcGameObject(const id_t objId) : id{ objId } {}
		const id_t id;
	};
}
