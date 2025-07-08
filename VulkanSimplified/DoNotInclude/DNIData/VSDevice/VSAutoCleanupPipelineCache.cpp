#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupPipelineCache.h"

namespace VulkanSimplified
{
	AutoCleanupPipelineCache::AutoCleanupPipelineCache(VkDevice device, VkPipelineCache pipelineCache) : _device(device), _pipelineCache(pipelineCache)
	{
	}

	AutoCleanupPipelineCache::~AutoCleanupPipelineCache()
	{
		DestroyCache();
	}

	AutoCleanupPipelineCache::AutoCleanupPipelineCache(AutoCleanupPipelineCache&& rhs) noexcept : _device(rhs._device), _pipelineCache(rhs._pipelineCache)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._pipelineCache = VK_NULL_HANDLE;
	}

	AutoCleanupPipelineCache& AutoCleanupPipelineCache::operator=(AutoCleanupPipelineCache&& rhs) noexcept
	{
		DestroyCache();

		_device = rhs._device;
		_pipelineCache = rhs._pipelineCache;

		rhs._device = VK_NULL_HANDLE;
		rhs._pipelineCache = VK_NULL_HANDLE;
		return *this;
	}

	VkPipelineCache AutoCleanupPipelineCache::GetPipelineCache() const
	{
		return _pipelineCache;
	}

	void AutoCleanupPipelineCache::DestroyCache()
	{
		if (_pipelineCache != VK_NULL_HANDLE)
		{
			vkDestroyPipelineCache(_device, _pipelineCache, nullptr);
			_pipelineCache = VK_NULL_HANDLE;
		}
	}

}