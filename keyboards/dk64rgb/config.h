// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Would be much faster on SPI (1500 vs 1100 scan rate when toggling RGB rapidly),
// but it's unstable.
// Typing with twinkle effect on max speed would freeze the keyboard, for example.
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 5
