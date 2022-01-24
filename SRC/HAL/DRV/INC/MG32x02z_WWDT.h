/**
 ******************************************************************************
 *
 * @file        MG32x02z_WWDT.h
 *
 * @brief       MG32x02z WWDT Register Definitions Header File
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12 (Register File Date : 2021_0806)
 * @date        2021/08/09 13:16 (H File Generated Date)
 * @author      HeadCodeGen V1.10
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 * Important!   This file is generated by code generator. Do not edit!
 *
 ******************************************************************************
 */

#ifndef _MG32x02z_WWDT_H
#define _MG32x02z_WWDT_H
#define _MG32x02z_WWDT_H_VER                        1.12    /*!< File Version */

#if !(MG32x02z_H_VER == MG32x02z_WWDT_H_VER)
    #error "MG32x02z_WWDT_H - Main/Module Version Mismatch !"
#endif

/**
 ******************************************************************************
 *
 * @struct      WWDT_Struct
 *              WWDT  [Module Structure Typedef]
 *
 ******************************************************************************
 */
typedef struct
{
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint8_t                :1;     //[0] 
            __IO uint8_t  TF            :1;     //[1] WWDT timer timeout interrupt flag. (set by hardware and clear by software writing 1)
                                        //0 = Normal (No event occurred)
                                        //1 = Happened (Event happened)
            __IO uint8_t  WINF          :1;     //[2] WWDT counter refreshing and value over the window compare threshold condition flag
                                        //0 = Normal (No event occurred)
                                        //1 = Happened (Event happened)
            __IO uint8_t  WRNF          :1;     //[3] WWDT counter warning flag
                                        //0 = Normal (No event occurred)
                                        //1 = Happened (Event happened)
            __I  uint8_t                :4;     //[7..4] 
            __I  uint8_t                :8;     //[15..8] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }STA;                               /*!< STA        ~ Offset[0x00]  WWDT status register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint8_t                :1;     //[0] 
            __IO uint8_t  TIE           :1;     //[1] WWDT timer timeout interrupt enable.
                                        //0 = Disable
                                        //1 = Enable
            __IO uint8_t  WIN_IE        :1;     //[2] WWDT counter refreshing and value over the window compare threshold condition interru
                                        //0 = Disable
                                        //1 = Enable
            __IO uint8_t  WRN_IE        :1;     //[3] WWDT counter warning interrupt enable.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :4;     //[7..4] 
            __I  uint8_t                :8;     //[15..8] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }INT;                               /*!< INT        ~ Offset[0x04]  WWDT interrupt enable register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint8_t                :2;     //[1..0] 
            __IO uint8_t  CK_SEL        :1;     //[2] WWDT input clock CK_WWDT source select.
                                        //0x0 = CK_APB
                                        //0x1 = CK_UT
            __I  uint8_t                :1;     //[3] 
            __IO uint8_t  CK_DIV        :3;     //[6..4] WWDT internal clock CK_WWDT_INT input divider.
                                        //0x0 = DIV1 : divided by 1
                                        //0x1 = DIV2 : divided by 2
                                        //0x2 = DIV4 : divided by 4
                                        //0x3 = DIV8 : divided by 8
                                        //0x4 = DIV16 : divided by 16
                                        //0x5 = DIV32 : divided by 32
                                        //0x6 = DIV64 : divided by 64
                                        //0x7 = DIV128 : divided by 128
            __I  uint8_t                :1;     //[7] 
            __IO uint8_t  CK_PDIV       :1;     //[8] WWDT internal clock CK_WWDT_INT pre-divider value.
                                        //0 = divided by 1
                                        //1 = divided by 256
            __I  uint8_t                :7;     //[15..9] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }CLK;                               /*!< CLK        ~ Offset[0x08]  WWDT clock source register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint16_t KEY           :16;    //[15..0] WWDT key register and counter reload enable control
                                        //0 = Unprotected
                                        //1 = Protected
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }KEY;                               /*!< KEY        ~ Offset[0x0C]  WWDT write protected Key register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint8_t  EN            :1;     //[0] WWDT function enable bit. When disables, WWDT_CNT will keep the counter value.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :3;     //[3..1] 
            __IO uint8_t  RSTF_EN       :1;     //[4] WWDT timer underflow reset generation enable bit.
                                        //0 = Disable
                                        //1 = Enable
            __IO uint8_t  RSTW_EN       :1;     //[5] WWDT reload counter out of window reset generation enable bit.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :2;     //[7..6] 
            __I  uint8_t                :8;     //[15..8] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }CR0;                               /*!< CR0        ~ Offset[0x10]  WWDT control register 0 */

    __I uint32_t  RESERVED0;            /*!< RESERVED0  ~ Offset[0x14]  Reserved */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint16_t CNT           :10;    //[9..0] WWDT counter value register.
            __I  uint8_t                :6;     //[15..10] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }CNT;                               /*!< CNT        ~ Offset[0x18]  WWDT counter register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint16_t RLR           :10;    //[9..0] WWDT counter reload register.
            __I  uint8_t                :6;     //[15..10] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }RLR;                               /*!< RLR        ~ Offset[0x1C]  WWDT reload register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint16_t WIN           :10;    //[9..0] WWDT window compare threshold register.
            __I  uint8_t                :6;     //[15..10] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }WIN;                               /*!< WIN        ~ Offset[0x20]  WWDT window compare register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint16_t WRN           :10;    //[9..0] WWDT warning interrupt compare threshold register.
            __I  uint8_t                :6;     //[15..10] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }WRN;                               /*!< WRN        ~ Offset[0x24]  WWDT warning compare register */

} WWDT_Struct;

/**
 ******************************************************************************
 *
 * @name        WWDT  [Base Address/Type]
 *
 ******************************************************************************
 */
///@{
#define WWDT_Base                       ((uint32_t)0x5D010000)              /*!< System Window Watch Dog Timer Control */
#define WWDT                            ((WWDT_Struct*) WWDT_Base)
///@}

/**
 ******************************************************************************
 *
 * @name        WWDT  [Register Definitions]
 *
 ******************************************************************************
 */
/**
 ******************************************************************************
 * @name        WWDT_STA  [register's definitions]
 *              Offset[0x00]  WWDT status register (0x5D010000)
 ******************************************************************************
 */
///@{
#define WWDT_STA_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_STA */
#define WWDT_STA_WRNF_mask_w                        ((uint32_t)0x00000008)  /*!< Bit Mask of 32bit */
#define WWDT_STA_WRNF_mask_h0                       ((uint16_t)0x0008)      /*!< Bit Mask of 16bit */
#define WWDT_STA_WRNF_mask_b0                       ((uint8_t )0x08)        /*!< Bit Mask of 8bit */
#define WWDT_STA_WRNF_normal_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0):Normal of 32bit */
#define WWDT_STA_WRNF_normal_h0                     ((uint16_t)0x0000)      /*!< Bit Value =(0):Normal of 16bit */
#define WWDT_STA_WRNF_normal_b0                     ((uint8_t )0x00)        /*!< Bit Value =(0):Normal of 8bit */
#define WWDT_STA_WRNF_happened_w                    ((uint32_t)0x00000008)  /*!< Bit Value =(1):Happened of 32bit */
#define WWDT_STA_WRNF_happened_h0                   ((uint16_t)0x0008)      /*!< Bit Value =(1):Happened of 16bit */
#define WWDT_STA_WRNF_happened_b0                   ((uint8_t )0x08)        /*!< Bit Value =(1):Happened of 8bit */

#define WWDT_STA_WINF_mask_w                        ((uint32_t)0x00000004)  /*!< Bit Mask of 32bit */
#define WWDT_STA_WINF_mask_h0                       ((uint16_t)0x0004)      /*!< Bit Mask of 16bit */
#define WWDT_STA_WINF_mask_b0                       ((uint8_t )0x04)        /*!< Bit Mask of 8bit */
#define WWDT_STA_WINF_normal_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0):Normal of 32bit */
#define WWDT_STA_WINF_normal_h0                     ((uint16_t)0x0000)      /*!< Bit Value =(0):Normal of 16bit */
#define WWDT_STA_WINF_normal_b0                     ((uint8_t )0x00)        /*!< Bit Value =(0):Normal of 8bit */
#define WWDT_STA_WINF_happened_w                    ((uint32_t)0x00000004)  /*!< Bit Value =(1):Happened of 32bit */
#define WWDT_STA_WINF_happened_h0                   ((uint16_t)0x0004)      /*!< Bit Value =(1):Happened of 16bit */
#define WWDT_STA_WINF_happened_b0                   ((uint8_t )0x04)        /*!< Bit Value =(1):Happened of 8bit */

#define WWDT_STA_TF_mask_w                          ((uint32_t)0x00000002)  /*!< Bit Mask of 32bit */
#define WWDT_STA_TF_mask_h0                         ((uint16_t)0x0002)      /*!< Bit Mask of 16bit */
#define WWDT_STA_TF_mask_b0                         ((uint8_t )0x02)        /*!< Bit Mask of 8bit */
#define WWDT_STA_TF_normal_w                        ((uint32_t)0x00000000)  /*!< Bit Value =(0):Normal of 32bit */
#define WWDT_STA_TF_normal_h0                       ((uint16_t)0x0000)      /*!< Bit Value =(0):Normal of 16bit */
#define WWDT_STA_TF_normal_b0                       ((uint8_t )0x00)        /*!< Bit Value =(0):Normal of 8bit */
#define WWDT_STA_TF_happened_w                      ((uint32_t)0x00000002)  /*!< Bit Value =(1):Happened of 32bit */
#define WWDT_STA_TF_happened_h0                     ((uint16_t)0x0002)      /*!< Bit Value =(1):Happened of 16bit */
#define WWDT_STA_TF_happened_b0                     ((uint8_t )0x02)        /*!< Bit Value =(1):Happened of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_INT  [register's definitions]
 *              Offset[0x04]  WWDT interrupt enable register (0x5D010004)
 ******************************************************************************
 */
///@{
#define WWDT_INT_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_INT */
#define WWDT_INT_WRN_IE_mask_w                      ((uint32_t)0x00000008)  /*!< Bit Mask of 32bit */
#define WWDT_INT_WRN_IE_mask_h0                     ((uint16_t)0x0008)      /*!< Bit Mask of 16bit */
#define WWDT_INT_WRN_IE_mask_b0                     ((uint8_t )0x08)        /*!< Bit Mask of 8bit */
#define WWDT_INT_WRN_IE_disable_w                   ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_INT_WRN_IE_disable_h0                  ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_INT_WRN_IE_disable_b0                  ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_INT_WRN_IE_enable_w                    ((uint32_t)0x00000008)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_INT_WRN_IE_enable_h0                   ((uint16_t)0x0008)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_INT_WRN_IE_enable_b0                   ((uint8_t )0x08)        /*!< Bit Value =(1):Enable of 8bit */

#define WWDT_INT_WIN_IE_mask_w                      ((uint32_t)0x00000004)  /*!< Bit Mask of 32bit */
#define WWDT_INT_WIN_IE_mask_h0                     ((uint16_t)0x0004)      /*!< Bit Mask of 16bit */
#define WWDT_INT_WIN_IE_mask_b0                     ((uint8_t )0x04)        /*!< Bit Mask of 8bit */
#define WWDT_INT_WIN_IE_disable_w                   ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_INT_WIN_IE_disable_h0                  ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_INT_WIN_IE_disable_b0                  ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_INT_WIN_IE_enable_w                    ((uint32_t)0x00000004)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_INT_WIN_IE_enable_h0                   ((uint16_t)0x0004)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_INT_WIN_IE_enable_b0                   ((uint8_t )0x04)        /*!< Bit Value =(1):Enable of 8bit */

#define WWDT_INT_TIE_mask_w                         ((uint32_t)0x00000002)  /*!< Bit Mask of 32bit */
#define WWDT_INT_TIE_mask_h0                        ((uint16_t)0x0002)      /*!< Bit Mask of 16bit */
#define WWDT_INT_TIE_mask_b0                        ((uint8_t )0x02)        /*!< Bit Mask of 8bit */
#define WWDT_INT_TIE_disable_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_INT_TIE_disable_h0                     ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_INT_TIE_disable_b0                     ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_INT_TIE_enable_w                       ((uint32_t)0x00000002)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_INT_TIE_enable_h0                      ((uint16_t)0x0002)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_INT_TIE_enable_b0                      ((uint8_t )0x02)        /*!< Bit Value =(1):Enable of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_CLK  [register's definitions]
 *              Offset[0x08]  WWDT clock source register (0x5D010008)
 ******************************************************************************
 */
///@{
#define WWDT_CLK_default                            ((uint32_t)0x00000170)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_CLK */
#define WWDT_CLK_CK_PDIV_mask_w                     ((uint32_t)0x00000100)  /*!< Bit Mask of 32bit */
#define WWDT_CLK_CK_PDIV_mask_h0                    ((uint16_t)0x0100)      /*!< Bit Mask of 16bit */
#define WWDT_CLK_CK_PDIV_mask_b1                    ((uint8_t )0x01)        /*!< Bit Mask of 8bit */
#define WWDT_CLK_CK_PDIV_divided_by_1_w             ((uint32_t)0x00000000)  /*!< Bit Value =(0):divided by 1 of 32bit */
#define WWDT_CLK_CK_PDIV_divided_by_1_h0            ((uint16_t)0x0000)      /*!< Bit Value =(0):divided by 1 of 16bit */
#define WWDT_CLK_CK_PDIV_divided_by_1_b1            ((uint8_t )0x00)        /*!< Bit Value =(0):divided by 1 of 8bit */
#define WWDT_CLK_CK_PDIV_divided_by_256_w           ((uint32_t)0x00000100)  /*!< Bit Value =(1):divided by 256 of 32bit */
#define WWDT_CLK_CK_PDIV_divided_by_256_h0          ((uint16_t)0x0100)      /*!< Bit Value =(1):divided by 256 of 16bit */
#define WWDT_CLK_CK_PDIV_divided_by_256_b1          ((uint8_t )0x01)        /*!< Bit Value =(1):divided by 256 of 8bit */

#define WWDT_CLK_CK_DIV_mask_w                      ((uint32_t)0x00000070)  /*!< Bit Mask of 32bit */
#define WWDT_CLK_CK_DIV_mask_h0                     ((uint16_t)0x0070)      /*!< Bit Mask of 16bit */
#define WWDT_CLK_CK_DIV_mask_b0                     ((uint8_t )0x70)        /*!< Bit Mask of 8bit */
#define WWDT_CLK_CK_DIV_div1_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):DIV1 of 32bit */
#define WWDT_CLK_CK_DIV_div1_h0                     ((uint16_t)0x0000)      /*!< Bit Value =(0x0):DIV1 of 16bit */
#define WWDT_CLK_CK_DIV_div1_b0                     ((uint8_t )0x00)        /*!< Bit Value =(0x0):DIV1 of 8bit */
#define WWDT_CLK_CK_DIV_div2_w                      ((uint32_t)0x00000010)  /*!< Bit Value =(0x1):DIV2 of 32bit */
#define WWDT_CLK_CK_DIV_div2_h0                     ((uint16_t)0x0010)      /*!< Bit Value =(0x1):DIV2 of 16bit */
#define WWDT_CLK_CK_DIV_div2_b0                     ((uint8_t )0x10)        /*!< Bit Value =(0x1):DIV2 of 8bit */
#define WWDT_CLK_CK_DIV_div4_w                      ((uint32_t)0x00000020)  /*!< Bit Value =(0x2):DIV4 of 32bit */
#define WWDT_CLK_CK_DIV_div4_h0                     ((uint16_t)0x0020)      /*!< Bit Value =(0x2):DIV4 of 16bit */
#define WWDT_CLK_CK_DIV_div4_b0                     ((uint8_t )0x20)        /*!< Bit Value =(0x2):DIV4 of 8bit */
#define WWDT_CLK_CK_DIV_div8_w                      ((uint32_t)0x00000030)  /*!< Bit Value =(0x3):DIV8 of 32bit */
#define WWDT_CLK_CK_DIV_div8_h0                     ((uint16_t)0x0030)      /*!< Bit Value =(0x3):DIV8 of 16bit */
#define WWDT_CLK_CK_DIV_div8_b0                     ((uint8_t )0x30)        /*!< Bit Value =(0x3):DIV8 of 8bit */
#define WWDT_CLK_CK_DIV_div16_w                     ((uint32_t)0x00000040)  /*!< Bit Value =(0x4):DIV16 of 32bit */
#define WWDT_CLK_CK_DIV_div16_h0                    ((uint16_t)0x0040)      /*!< Bit Value =(0x4):DIV16 of 16bit */
#define WWDT_CLK_CK_DIV_div16_b0                    ((uint8_t )0x40)        /*!< Bit Value =(0x4):DIV16 of 8bit */
#define WWDT_CLK_CK_DIV_div32_w                     ((uint32_t)0x00000050)  /*!< Bit Value =(0x5):DIV32 of 32bit */
#define WWDT_CLK_CK_DIV_div32_h0                    ((uint16_t)0x0050)      /*!< Bit Value =(0x5):DIV32 of 16bit */
#define WWDT_CLK_CK_DIV_div32_b0                    ((uint8_t )0x50)        /*!< Bit Value =(0x5):DIV32 of 8bit */
#define WWDT_CLK_CK_DIV_div64_w                     ((uint32_t)0x00000060)  /*!< Bit Value =(0x6):DIV64 of 32bit */
#define WWDT_CLK_CK_DIV_div64_h0                    ((uint16_t)0x0060)      /*!< Bit Value =(0x6):DIV64 of 16bit */
#define WWDT_CLK_CK_DIV_div64_b0                    ((uint8_t )0x60)        /*!< Bit Value =(0x6):DIV64 of 8bit */
#define WWDT_CLK_CK_DIV_div128_w                    ((uint32_t)0x00000070)  /*!< Bit Value =(0x7):DIV128 of 32bit */
#define WWDT_CLK_CK_DIV_div128_h0                   ((uint16_t)0x0070)      /*!< Bit Value =(0x7):DIV128 of 16bit */
#define WWDT_CLK_CK_DIV_div128_b0                   ((uint8_t )0x70)        /*!< Bit Value =(0x7):DIV128 of 8bit */

#define WWDT_CLK_CK_SEL_mask_w                      ((uint32_t)0x00000004)  /*!< Bit Mask of 32bit */
#define WWDT_CLK_CK_SEL_mask_h0                     ((uint16_t)0x0004)      /*!< Bit Mask of 16bit */
#define WWDT_CLK_CK_SEL_mask_b0                     ((uint8_t )0x04)        /*!< Bit Mask of 8bit */
#define WWDT_CLK_CK_SEL_ck_apb_w                    ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):CK_APB of 32bit */
#define WWDT_CLK_CK_SEL_ck_apb_h0                   ((uint16_t)0x0000)      /*!< Bit Value =(0x0):CK_APB of 16bit */
#define WWDT_CLK_CK_SEL_ck_apb_b0                   ((uint8_t )0x00)        /*!< Bit Value =(0x0):CK_APB of 8bit */
#define WWDT_CLK_CK_SEL_ck_ut_w                     ((uint32_t)0x00000004)  /*!< Bit Value =(0x1):CK_UT of 32bit */
#define WWDT_CLK_CK_SEL_ck_ut_h0                    ((uint16_t)0x0004)      /*!< Bit Value =(0x1):CK_UT of 16bit */
#define WWDT_CLK_CK_SEL_ck_ut_b0                    ((uint8_t )0x04)        /*!< Bit Value =(0x1):CK_UT of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_KEY  [register's definitions]
 *              Offset[0x0C]  WWDT write protected Key register (0x5D01000C)
 ******************************************************************************
 */
///@{
#define WWDT_KEY_default                            ((uint32_t)0x00000001)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_KEY */
#define WWDT_KEY_KEY_mask_w                         ((uint32_t)0x0000FFFF)  /*!< Bit Mask of 32bit */
#define WWDT_KEY_KEY_mask_h0                        ((uint16_t)0xFFFF)      /*!< Bit Mask of 16bit */
#define WWDT_KEY_KEY_unprotected_w                  ((uint32_t)0x00000000)  /*!< Bit Value =(0):Unprotected of 32bit */
#define WWDT_KEY_KEY_unprotected_h0                 ((uint16_t)0x0000)      /*!< Bit Value =(0):Unprotected of 16bit */
#define WWDT_KEY_KEY_unprotected_b0                 ((uint8_t )0x00)        /*!< Bit Value =(0):Unprotected of 8bit */
#define WWDT_KEY_KEY_protected_w                    ((uint32_t)0x00000001)  /*!< Bit Value =(1):Protected of 32bit */
#define WWDT_KEY_KEY_protected_h0                   ((uint16_t)0x0001)      /*!< Bit Value =(1):Protected of 16bit */
#define WWDT_KEY_KEY_protected_b0                   ((uint8_t )0x01)        /*!< Bit Value =(1):Protected of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_CR0  [register's definitions]
 *              Offset[0x10]  WWDT control register 0 (0x5D010010)
 ******************************************************************************
 */
///@{
#define WWDT_CR0_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_CR0 */
#define WWDT_CR0_RSTW_EN_mask_w                     ((uint32_t)0x00000020)  /*!< Bit Mask of 32bit */
#define WWDT_CR0_RSTW_EN_mask_h0                    ((uint16_t)0x0020)      /*!< Bit Mask of 16bit */
#define WWDT_CR0_RSTW_EN_mask_b0                    ((uint8_t )0x20)        /*!< Bit Mask of 8bit */
#define WWDT_CR0_RSTW_EN_disable_w                  ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_CR0_RSTW_EN_disable_h0                 ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_CR0_RSTW_EN_disable_b0                 ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_CR0_RSTW_EN_enable_w                   ((uint32_t)0x00000020)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_CR0_RSTW_EN_enable_h0                  ((uint16_t)0x0020)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_CR0_RSTW_EN_enable_b0                  ((uint8_t )0x20)        /*!< Bit Value =(1):Enable of 8bit */

#define WWDT_CR0_RSTF_EN_mask_w                     ((uint32_t)0x00000010)  /*!< Bit Mask of 32bit */
#define WWDT_CR0_RSTF_EN_mask_h0                    ((uint16_t)0x0010)      /*!< Bit Mask of 16bit */
#define WWDT_CR0_RSTF_EN_mask_b0                    ((uint8_t )0x10)        /*!< Bit Mask of 8bit */
#define WWDT_CR0_RSTF_EN_disable_w                  ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_CR0_RSTF_EN_disable_h0                 ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_CR0_RSTF_EN_disable_b0                 ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_CR0_RSTF_EN_enable_w                   ((uint32_t)0x00000010)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_CR0_RSTF_EN_enable_h0                  ((uint16_t)0x0010)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_CR0_RSTF_EN_enable_b0                  ((uint8_t )0x10)        /*!< Bit Value =(1):Enable of 8bit */

#define WWDT_CR0_EN_mask_w                          ((uint32_t)0x00000001)  /*!< Bit Mask of 32bit */
#define WWDT_CR0_EN_mask_h0                         ((uint16_t)0x0001)      /*!< Bit Mask of 16bit */
#define WWDT_CR0_EN_mask_b0                         ((uint8_t )0x01)        /*!< Bit Mask of 8bit */
#define WWDT_CR0_EN_disable_w                       ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define WWDT_CR0_EN_disable_h0                      ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define WWDT_CR0_EN_disable_b0                      ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define WWDT_CR0_EN_enable_w                        ((uint32_t)0x00000001)  /*!< Bit Value =(1):Enable of 32bit */
#define WWDT_CR0_EN_enable_h0                       ((uint16_t)0x0001)      /*!< Bit Value =(1):Enable of 16bit */
#define WWDT_CR0_EN_enable_b0                       ((uint8_t )0x01)        /*!< Bit Value =(1):Enable of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_CNT  [register's definitions]
 *              Offset[0x18]  WWDT counter register (0x5D010018)
 ******************************************************************************
 */
///@{
#define WWDT_CNT_default                            ((uint32_t)0x000003FF)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_CNT */
#define WWDT_CNT_CNT_mask_w                         ((uint32_t)0x000003FF)  /*!< Bit Mask of 32bit */
#define WWDT_CNT_CNT_mask_h0                        ((uint16_t)0x03FF)      /*!< Bit Mask of 16bit */
#define WWDT_CNT_CNT_shift_w                        (0)                     /*!< Bit Shift of 32bit */
#define WWDT_CNT_CNT_shift_h0                       (0)                     /*!< Bit Shift of 16bit */
#define WWDT_CNT_CNT_shift_b0                       (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_RLR  [register's definitions]
 *              Offset[0x1C]  WWDT reload register (0x5D01001C)
 ******************************************************************************
 */
///@{
#define WWDT_RLR_default                            ((uint32_t)0x000003FF)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_RLR */
#define WWDT_RLR_RLR_mask_w                         ((uint32_t)0x000003FF)  /*!< Bit Mask of 32bit */
#define WWDT_RLR_RLR_mask_h0                        ((uint16_t)0x03FF)      /*!< Bit Mask of 16bit */
#define WWDT_RLR_RLR_shift_w                        (0)                     /*!< Bit Shift of 32bit */
#define WWDT_RLR_RLR_shift_h0                       (0)                     /*!< Bit Shift of 16bit */
#define WWDT_RLR_RLR_shift_b0                       (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_WIN  [register's definitions]
 *              Offset[0x20]  WWDT window compare register (0x5D010020)
 ******************************************************************************
 */
///@{
#define WWDT_WIN_default                            ((uint32_t)0x000003FF)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_WIN */
#define WWDT_WIN_WIN_mask_w                         ((uint32_t)0x000003FF)  /*!< Bit Mask of 32bit */
#define WWDT_WIN_WIN_mask_h0                        ((uint16_t)0x03FF)      /*!< Bit Mask of 16bit */
#define WWDT_WIN_WIN_shift_w                        (0)                     /*!< Bit Shift of 32bit */
#define WWDT_WIN_WIN_shift_h0                       (0)                     /*!< Bit Shift of 16bit */
#define WWDT_WIN_WIN_shift_b0                       (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        WWDT_WRN  [register's definitions]
 *              Offset[0x24]  WWDT warning compare register (0x5D010024)
 ******************************************************************************
 */
///@{
#define WWDT_WRN_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of WWDT_WRN */
#define WWDT_WRN_WRN_mask_w                         ((uint32_t)0x000003FF)  /*!< Bit Mask of 32bit */
#define WWDT_WRN_WRN_mask_h0                        ((uint16_t)0x03FF)      /*!< Bit Mask of 16bit */
#define WWDT_WRN_WRN_shift_w                        (0)                     /*!< Bit Shift of 32bit */
#define WWDT_WRN_WRN_shift_h0                       (0)                     /*!< Bit Shift of 16bit */
#define WWDT_WRN_WRN_shift_b0                       (0)                     /*!< Bit Shift of 8bit */

///@}

#endif  // _MG32x02z_WWDT_H

/*----------------------------------------------------------------------------*/
/*                        End of file MG32x02z_WWDT.h                         */
/*----------------------------------------------------------------------------*/
