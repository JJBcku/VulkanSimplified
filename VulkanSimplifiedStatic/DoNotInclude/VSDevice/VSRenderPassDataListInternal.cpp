#include "VSDeviceNIpch.h"
#include "VSRenderPassDataListInternal.h"

#include "VSAutoCleanupRenderPass.h"

#include "../VSSharedData/VSSharedRenderPassDataInternal.h"

#include "../../Include/VSDevice/VSRenderPassListInitialCapacities.h"
#include "../../Include/VSDevice/VSSubpassCreationDataWithoutResolving.h"
#include "../../Include/VSDevice/VSSubpassCreationDataWithResolving.h"

namespace VulkanSimplifiedInternal
{
	RenderPassListInternal::RenderPassListInternal(const SharedRenderPassDataListInternal& sharedRenderPassData, VkDevice device,
		const VulkanSimplified::RenderPassDataListsInitialCapacities& initialCapacities) : _sharedRenderPassData(sharedRenderPassData), _device(device),
		_renderPassList(initialCapacities.renderPassListInitialCapacity)
	{
	}

	RenderPassListInternal::~RenderPassListInternal()
	{
	}

	IDObject<AutoCleanupRenderPass> RenderPassListInternal::AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<VulkanSimplified::SubpassCreationDataWithoutResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies,
		size_t addOnReserve)
	{
		VkRenderPass add = VK_NULL_HANDLE;
		VkRenderPassCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		std::vector<VkAttachmentDescription> attachmentData;

		if (!attachments.empty())
		{
			attachmentData = _sharedRenderPassData.GetRenderPassAttachmentDescriptors(attachments);
			createInfo.attachmentCount = static_cast<std::uint32_t>(attachmentData.size());
			createInfo.pAttachments = attachmentData.data();
		}

		std::vector<VkSubpassDescription> subpassDataList;
		std::vector<std::vector<VkAttachmentReference>> inputAttachments;
		std::vector<std::vector<VkAttachmentReference>> colorAttachments;
		std::vector<std::optional<VkAttachmentReference>> depthStencilAttachments;

		if (!subpasses.empty())
		{
			subpassDataList.reserve(subpasses.size());
			inputAttachments.resize(subpasses.size());
			colorAttachments.resize(subpasses.size());
			depthStencilAttachments.resize(subpasses.size());

			for (size_t i = 0; i < subpasses.size(); i++)
			{
				VkSubpassDescription subpassAdd{};
				subpassAdd.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

				if (!subpasses[i].inputAttachments.empty())
				{
					inputAttachments[i] = _sharedRenderPassData.GetRenderPassAttachmentReferences(subpasses[i].inputAttachments);
					subpassAdd.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments[i].size());
					subpassAdd.pInputAttachments = inputAttachments[i].data();
				}

				if (!subpasses[i].colorAttachments.empty())
				{
					colorAttachments[i] = _sharedRenderPassData.GetRenderPassAttachmentReferences(subpasses[i].colorAttachments);
					subpassAdd.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments[i].size());
					subpassAdd.pColorAttachments = colorAttachments[i].data();
				}

				if (subpasses[i].depthStencilAttachment.has_value())
				{
					depthStencilAttachments[i] = _sharedRenderPassData.GetRenderPassAttachmentReference(subpasses[i].depthStencilAttachment);
					subpassAdd.pDepthStencilAttachment = &depthStencilAttachments[i].value();
				}

				if (!subpasses[i].preserveAttachment.empty())
				{
					subpassAdd.preserveAttachmentCount = static_cast<std::uint32_t>(subpasses[i].preserveAttachment.size());
					subpassAdd.pPreserveAttachments = subpasses[i].preserveAttachment.data();
				}

				subpassDataList.push_back(subpassAdd);
			}

			createInfo.subpassCount = static_cast<std::uint32_t>(subpassDataList.size());
			createInfo.pSubpasses = subpassDataList.data();
		}

		std::vector<VkSubpassDependency> subpassDependenciesData;

		if (!subpassDependencies.empty())
		{
			subpassDependenciesData = _sharedRenderPassData.GetSubpassDependencies(subpassDependencies);
			createInfo.dependencyCount = static_cast<std::uint32_t>(subpassDependenciesData.size());
			createInfo.pDependencies = subpassDependenciesData.data();
		}

		if (vkCreateRenderPass(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("RenderPassListInternal::AddRenderPassWithoutResolveAttachments Error: Program failed to create the render pass!");

		return _renderPassList.AddObject(AutoCleanupRenderPass(_device, add), addOnReserve);
	}

	IDObject<AutoCleanupRenderPass> RenderPassListInternal::AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
		const std::vector<VulkanSimplified::SubpassCreationDataWithResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserve)
	{
		VkRenderPass add = VK_NULL_HANDLE;
		VkRenderPassCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		std::vector<VkAttachmentDescription> attachmentData;

		if (!attachments.empty())
		{
			attachmentData = _sharedRenderPassData.GetRenderPassAttachmentDescriptors(attachments);
			createInfo.attachmentCount = static_cast<std::uint32_t>(attachmentData.size());
			createInfo.pAttachments = attachmentData.data();
		}

		std::vector<VkSubpassDescription> subpassDataList;
		std::vector<std::vector<VkAttachmentReference>> inputAttachments;
		std::vector<std::vector<VkAttachmentReference>> colorAttachments;
		std::vector<std::vector<VkAttachmentReference>> resolveAttachments;
		std::vector<std::optional<VkAttachmentReference>> depthStencilAttachments;

		if (!subpasses.empty())
		{
			subpassDataList.reserve(subpasses.size());
			inputAttachments.resize(subpasses.size());
			colorAttachments.resize(subpasses.size());
			resolveAttachments.resize(subpasses.size());
			depthStencilAttachments.resize(subpasses.size());

			for (size_t i = 0; i < subpasses.size(); i++)
			{
				VkSubpassDescription subpassAdd{};
				subpassAdd.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

				if (!subpasses[i].inputAttachments.empty())
				{
					inputAttachments[i] = _sharedRenderPassData.GetRenderPassAttachmentReferences(subpasses[i].inputAttachments);
					subpassAdd.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments[i].size());
					subpassAdd.pInputAttachments = inputAttachments[i].data();
				}

				if (!subpasses[i].colorAttachments.empty())
				{
					colorAttachments[i].resize(subpasses[i].colorAttachments.size());
					resolveAttachments[i].resize(subpasses[i].colorAttachments.size());

					for (size_t j = 0; j < subpasses[i].colorAttachments.size(); j++)
					{
						colorAttachments[i][j] = _sharedRenderPassData.GetRenderPassAttachmentReference(subpasses[i].colorAttachments[j].first);
						resolveAttachments[i][j] = _sharedRenderPassData.GetRenderPassAttachmentReference(subpasses[i].colorAttachments[j].second);
					}

					subpassAdd.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments[i].size());
					subpassAdd.pColorAttachments = colorAttachments[i].data();
					subpassAdd.pResolveAttachments = resolveAttachments[i].data();
				}

				if (subpasses[i].depthStencilAttachment.has_value())
				{
					depthStencilAttachments[i] = _sharedRenderPassData.GetRenderPassAttachmentReference(subpasses[i].depthStencilAttachment);
					subpassAdd.pDepthStencilAttachment = &depthStencilAttachments[i].value();
				}

				if (!subpasses[i].preserveAttachment.empty())
				{
					subpassAdd.preserveAttachmentCount = static_cast<std::uint32_t>(subpasses[i].preserveAttachment.size());
					subpassAdd.pPreserveAttachments = subpasses[i].preserveAttachment.data();
				}

				subpassDataList.push_back(subpassAdd);
			}

			createInfo.subpassCount = static_cast<std::uint32_t>(subpassDataList.size());
			createInfo.pSubpasses = subpassDataList.data();
		}

		std::vector<VkSubpassDependency> subpassDependenciesData;

		if (!subpassDependencies.empty())
		{
			subpassDependenciesData = _sharedRenderPassData.GetSubpassDependencies(subpassDependencies);
			createInfo.dependencyCount = static_cast<std::uint32_t>(subpassDependenciesData.size());
			createInfo.pDependencies = subpassDependenciesData.data();
		}

		if (vkCreateRenderPass(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("RenderPassListInternal::AddRenderPassWithResolveAttachments Error: Program failed to create the render pass!");

		return _renderPassList.AddObject(AutoCleanupRenderPass(_device, add), addOnReserve);
	}

	VkRenderPass RenderPassListInternal::GetRenderPass(IDObject<AutoCleanupRenderPass> renderPassID) const
	{
		return _renderPassList.GetConstObject(renderPassID).GetRenderPass();
	}

}