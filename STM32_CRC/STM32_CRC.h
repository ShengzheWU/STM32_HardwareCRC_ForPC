/*
 *         _____          ___           ___           ___           ___                       ___           ___
 *        /  /::\        /  /\         /  /\         /  /\         /__/\          ___        /  /\         /__/|
 *       /  /:/\:\      /  /::\       /  /:/_       /  /::\        \  \:\        /  /\      /  /:/_       |  |:|
 *      /  /:/  \:\    /  /:/\:\     /  /:/ /\     /  /:/\:\        \  \:\      /  /:/     /  /:/ /\      |  |:|
 *     /__/:/ \__\:|  /  /:/  \:\   /  /:/ /::\   /  /:/  \:\   _____\__\:\    /  /:/     /  /:/ /:/_   __|  |:|
 *     \  \:\ /  /:/ /__/:/ \__\:\ /__/:/ /:/\:\ /__/:/ \__\:\ /__/::::::::\  /  /::\    /__/:/ /:/ /\ /__/\_|:|____
 *      \  \:\  /:/  \  \:\ /  /:/ \  \:\/:/~/:/ \  \:\ /  /:/ \  \:\~~\~~\/ /__/:/\:\   \  \:\/:/ /:/ \  \:\/:::::/
 *       \  \:\/:/    \  \:\  /:/   \  \::/ /:/   \  \:\  /:/   \  \:\  ~~~  \__\/  \:\   \  \::/ /:/   \  \::/~~~~
 *        \  \::/      \  \:\/:/     \__\/ /:/     \  \:\/:/     \  \:\           \  \:\   \  \:\/:/     \  \:\
 *         \__\/        \  \::/        /__/:/       \  \::/       \  \:\           \__\/    \  \::/       \  \:\
 *                       \__\/         \__\/         \__\/         \__\/                     \__\/         \__\/
 *
 *
 * @ ����: STM32_CRC.h
 * @ ����:
 * @ ����: Tomy
 * @ ����: 2020��3��17��
 * @ �汾: V1.0
 * @ ��ʷ: V1.0 2020��3��17�� Summary
 *
 * Copyright (c) 2020 DosonTek Electronics Co., Ltd. All rights reserved.
 */

#pragma once
#ifndef STM32_CRC_H_
#define STM32_CRC_H_

#include "STM32_ADC.h"

 /* ��ͬ������ 4 �ֽڶ������� */
#if defined (__MINGW32__) /* MINGW32 Compiler */

#ifndef __ALIGN_END
#define __ALIGN_END    __attribute__ ((aligned (4)))
#endif

#ifndef __ALIGN_BEGIN  
#define __ALIGN_BEGIN
#endif

#elif defined (_MSC_VER) /* MSVC Compiler */

#ifndef __ALIGN_END
#define __ALIGN_END
#endif

#ifndef __ALIGN_BEGIN      
#define __ALIGN_BEGIN   __declspec(align(4))
#endif

#endif

#define USB_DATA_OUT_BUFFER_SIZE    (8U)        /* BUFFER_SIZE ����Ϊ 4 �������� */
#define USB_DATA_IN_BUFFER_SIZE     (64U)       /* BUFFER_SIZE ����Ϊ 4 �������� */
#define CVT_TO_WORD_LENGTH(A)       ((A) / 4U)

/* sizeof(USB_DataOutPkt_t) ������� USB_DATA_OUT_BUFFER_SIZE */
typedef struct {
    uint16_t    PayloadLen;
    uint8_t     Cmd[2];
    uint32_t    CRC_32;
} USB_DataOutPkt_t;

/* sizeof(USB_DataInPkt_t) ������� USB_DATA_IN_BUFFER_SIZE */
typedef struct {
    uint16_t PayloadLen;

    struct {
        uint16_t ADC_SampleValArr[NUM_OF_CHN_TOTAL];

        /* USB_DATA_IN_BUFFER_SIZE ��ȥ������Ա��ռ�ռ伴Ϊ���豣�����ֽ��� */
        uint8_t rsvdData[USB_DATA_IN_BUFFER_SIZE - sizeof(uint16_t) - NUM_OF_CHN_TOTAL * 2 - sizeof(uint32_t)];
    } DataPayload_t;

    uint32_t CRC_32;
} USB_DataInPkt_t;

extern uint8_t* const pUSB_DataOutBuffer;
extern uint8_t* const pUSB_DataInBuffer;

#endif /* STM32_CRC_H_ */
