// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 16

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 192

#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE 4

#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE 4

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
