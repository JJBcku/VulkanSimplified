#pragma once

constexpr uint32_t swapchainWidth = 1920U;
constexpr uint32_t swapchainHeight = 1080U;
constexpr float aspectRatio = static_cast<float>(swapchainWidth) / static_cast<float>(swapchainHeight);

constexpr uint32_t framesInFlight = 3U;