#pragma once
#include "HlcDevice.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
namespace hlc {
	using namespace std;

	class HlcModel {
	public:
		struct Vertex {
			glm::vec2 position;
			glm::vec3 color;
			Vertex(glm::vec2 pos, glm::vec3 col) : position{ pos }, color{ col } {}
			Vertex(glm::vec2 pos) : position{ pos }, color{ 0.f, 0.f, 0.f } {}

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};
		HlcModel(HlcDevice& device, const vector<Vertex>& vertices);
		~HlcModel();

		HlcModel(const HlcModel&) = delete;
		HlcModel& operator=(const HlcModel&) = delete;

		void bind(VkCommandBuffer command_buffer) const;
		void draw(VkCommandBuffer command_buffer) const;
	private:
		HlcDevice& hlcDevice;
		VkBuffer vertexBuffer{};
		VkDeviceMemory vertexBufferMemory{};
		uint32_t vertexCount{};

		void createVertexBuffers(const std::vector<Vertex>& vertices);
	};

}
