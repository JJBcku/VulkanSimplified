#pragma once

#include "VSAttachmentReferenceDef.h"

#include <CustomLists/IDObject.h>

namespace VulkanSimplified
{
	struct SubpassCreationDataWithResolving
	{
		std::vector<AttachmentReference> inputAttachments;
		std::vector<std::pair<AttachmentReference, AttachmentReference>> colorAttachments;
		AttachmentReference depthStencilAttachment;
		std::vector<uint32_t> preserveAttachment;

		SubpassCreationDataWithResolving() = default;
	};
}