#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlTextEventsData.h"

namespace VulkanSimplified
{
	SdlTextEditingEventData::SdlTextEditingEventData()
	{
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		padding = 0;
		text = nullptr;
		start = 0;
		length = 0;
	}

	SdlTextEditingEventData::~SdlTextEditingEventData()
	{
	}

	SdlTextInputEventData::SdlTextInputEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		text = nullptr;
	}

	SdlTextInputEventData::~SdlTextInputEventData()
	{
	}

	SdlTextEditingCandidatesEventData::SdlTextEditingCandidatesEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		candidates = nullptr;
		num_candidates = 0;
		selected_candidate = 0;
		horizontal = false;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		padding4 = 0;
	}

	SdlTextEditingCandidatesEventData::~SdlTextEditingCandidatesEventData()
	{
	}

}
