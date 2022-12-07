#include "HlcModel.hpp"
#include <cassert>
#include <cstring>
namespace hlc {

	using namespace std;
	HlcModel::HlcModel(HlcDevice& device, const vector<Vertex>& vertices) : hlcDevice{ device } {
		createVertexBuffers(vertices);

	} HlcModel::~HlcModel() {
		vkDestroyBuffer(hlcDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(hlcDevice.device(), vertexBufferMemory, nullptr);
	}

	void HlcModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3");
		const VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		hlcDevice.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);
		void *data;
		vkMapMemory(hlcDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), bufferSize);
		vkUnmapMemory(hlcDevice.device(), vertexBufferMemory);
	}

	void HlcModel::draw(const VkCommandBuffer command_buffer) const {
		vkCmdDraw(command_buffer, vertexCount, 1, 0, 0);
	}

	void HlcModel::bind(const VkCommandBuffer command_buffer) const {
		const VkBuffer buffers[] = {vertexBuffer};
		const VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(command_buffer, 0, 1, buffers, offsets);
	}

	vector<VkVertexInputBindingDescription> HlcModel::Vertex::getBindingDescriptions() {
		vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescriptions;
	}

	vector<VkVertexInputAttributeDescription> HlcModel::Vertex::getAttributeDescriptions() {
		vector<VkVertexInputAttributeDescription> attributeDescriptions(1);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);
		return attributeDescriptions;
	}

}