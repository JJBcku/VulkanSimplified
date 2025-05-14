#pragma once

constexpr uint32_t width = 1920U;
constexpr uint32_t height = 1080U;
constexpr float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

constexpr uint32_t framesInFlight = 3U;