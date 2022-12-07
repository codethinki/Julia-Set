#include "HlcSimpleRS.hpp"

#include <glm/glm.hpp>

#include <stdexcept>
#include <fstream>

#include "MyApp.hpp"

namespace hlc {
	struct SimplePushConstantData {
		SimplePushConstantData(const glm::vec3 general, const glm::vec4 edges, const glm::vec2 cOffset) : general{ general }, edges{ edges }, cOffset{cOffset} {}
		SimplePushConstantData() = default;
		alignas(16) glm::vec3 general{ MyApp::WIDTH, MyApp::HEIGHT, 75.f };
		alignas(16) glm::vec4 edges{ -2.f, 2.f, -2.f, 2.f };
		alignas(8) glm::vec2 cOffset{ -2.f, 2.f};
	};

	SimpleRenderSystem::SimpleRenderSystem(HlcDevice& device, VkRenderPass render_pass, const bool wide_shaders) : hlcDevice{ device } , wideShaders{wide_shaders}{
		createPipelineLayout();
		createPipeline(render_pass);
	}
	SimpleRenderSystem::~SimpleRenderSystem() {
		vkDestroyPipelineLayout(hlcDevice.device(), pipelineLayout, nullptr);
	}

	void SimpleRenderSystem::createPipelineLayout() {
		VkPushConstantRange pushConstantRange;
		pushConstantRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);


		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(hlcDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) throw std::runtime_error("failed to create pipeline layout");
	}

	void SimpleRenderSystem::createPipeline(VkRenderPass render_pass) {
		assert(pipelineLayout != NULL && "create Pipeline: Cannot create pipeline without a layout");
		PipelineConfigInfo pipelineConfig{};
		HlcPipeline::defaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = render_pass;
		pipelineConfig.pipelineLayout = pipelineLayout;
		hlcPipeline = std::make_unique<HlcPipeline>(hlcDevice, readShaderFile(MyApp::VERT_SHADER_PATH),
		                                            wideShaders
			                                            ? readShaderFile(MyApp::FRAG_SHADER_PATH)
			                                            : readShaderFile(MyApp::FRAG_SHADER32_PATH), pipelineConfig);
	}

	void SimpleRenderSystem::renderSquare(const VkCommandBuffer command_buffer, const HlcGameObject& game_object) const {
		hlcPipeline->bind(command_buffer);

		const SimplePushConstantData push{ glm::vec3(windowSize.width, windowSize.height, detail), extent,  cOffset};
			vkCmdPushConstants(command_buffer, pipelineLayout,
							   VK_SHADER_STAGE_FRAGMENT_BIT, 0,
							   sizeof(SimplePushConstantData), &push);
			game_object.model->bind(command_buffer);
			game_object.model->draw(command_buffer);
	}

	vector<char> SimpleRenderSystem::readShaderFile(const string& filepath) {

		ifstream file{ filepath, ios::ate | ios::binary };
		if (!file.is_open()) throw runtime_error("readShaderFile: failed to open file: " + filepath);
		size_t fileSize = file.tellg();
		vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}
}
