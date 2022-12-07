#pragma once
#include <vector>
#include "HlcDevice.hpp"
namespace hlc {
	using namespace std;
	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;

		vector<VkDynamicState> dynamicStates;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;

		VkPipelineLayout pipelineLayout = 0;
		VkRenderPass renderPass = 0;
		uint32_t subpass = 0;
	};
	class HlcPipeline {
	public:
		HlcDevice& hlcDevice;
		VkPipeline hlcGraphicsPipeline{};
		VkShaderModule vertShaderModule{};
		VkShaderModule fragShaderModule{};

		void createGraphicsPipeline(vector<char> vert_shader_code, vector<char> frag_shader_code, const PipelineConfigInfo& config_info);

		HlcPipeline(HlcDevice& device, std::vector<char> vert_shader_code, std::vector<char>
		            frag_shader_code, const PipelineConfigInfo& config_info);
		~HlcPipeline();

		HlcPipeline(const HlcPipeline&) = delete;
		HlcPipeline& operator=(const HlcPipeline&) = delete;

		void bind(VkCommandBuffer command_buffer);

		static void defaultPipelineConfigInfo(PipelineConfigInfo& config_info);

		void createShaderModule(vector<char> code, VkShaderModule* shader_module) const;
	};

}