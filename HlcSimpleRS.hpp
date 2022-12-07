#pragma once

#include  "HlcDevice.hpp"
#include "HlcModel.hpp"
#include "HlcGameObject.hpp"
#include "HlcPipeline.hpp"

#include <memory>
#include <vector>
namespace hlc {
	using namespace std;
	class SimpleRenderSystem {
	public:

		SimpleRenderSystem(HlcDevice& device, VkRenderPass render_pass, bool wide_shaders);
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		double detail = 75;
		glm::vec2 cOffset = glm::vec2(0, 0);
		glm::vec4 extent = { -2, 2, -2, 2 };
		VkExtent2D windowSize = { 1000, 1000 };
		void renderSquare(VkCommandBuffer command_buffer, const HlcGameObject& game_objects) const;

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass render_pass);
		static vector<char> readShaderFile(const string& filepath);

		bool wideShaders = true;
		HlcDevice& hlcDevice;
		unique_ptr<HlcPipeline> hlcPipeline;
		VkPipelineLayout pipelineLayout;
	};
}
