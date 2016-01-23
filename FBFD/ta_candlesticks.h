#pragma once
/** ============================================================================
 *
 *  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co, Ltd.
 *
 *  @File Name:	ta_candlesticks.h
 *
 *  @Author: xiong-kaifang   Version: v1.0   Date: 2015-01-11
 *
 *  @Description:   // 用于详细说明此程序文件完成的主要功能，与其它模块
 *                  // 或函数的接口，输出值，取值范围、含义及参数间的控
 *                  // 制、顺序、独立或依赖等关系
 *                  //
 *
 *                  The header file for technical analysis of candlesticks.
 *
 *  @Others:        // 其它内容说明
 *
 *  @Function List: // 主要函数列表，每条记录就包括函数名及功能简要说明
 *      1.  ...
 *      2.  ...
 *
 *  @History:       // 修改历史记录列表，每条修改记录就包括修改日期、修改
 *                  // 时间及修改内容简述
 *
 *  <author>        <time>       <version>      <description>
 *
 *  xiong-kaifang   2015-01-11     v1.0	        Write this module.
 *
 *  ============================================================================
 */

#if !defined (__TA_CANDLESTICKS_H)
#define __TA_CANDLESTICKS_H

/*  --------------------- Include system headers ---------------------------- */
#include <stdbool.h>

/*  --------------------- Include user headers   ---------------------------- */

#if defined(__cplusplus)
extern "C" {
#endif

/*
 *  --------------------- Macro definition -------------------------------------
 */

/** ============================================================================
 *  @Macro:         Macro name
 *
 *  @Description:   Description of this macro.
 *  ============================================================================
 */

/*
 *  --------------------- Data type definition ---------------------------------
 */

/** ----------------------------------------------------------------------------
 *  @Name:          Structure name
 *
 *  @Description:   Description of the structure.
 *
 *  @Field:         Field1 member
 *
 *  @Field:         Field2 member
 *  ----------------------------------------------------------------------------
 */
struct __ta_candlesticks_t; typedef struct __ta_candlesticks_t ta_candlesticks_t;
struct __ta_candlesticks_t
{
	void          * m_reserved[2];
	unsigned int    m_id;
    unsigned int    m_index;
	float           m_open;
	float           m_close;
	float           m_high;
	float           m_low;

	void          * m_arg;
};

/*
 *  --------------------- Public function declaration --------------------------
 */

/** =============================================================================
 *
 *  @Function:      // 函数名称
 *
 *  @Description:   // 函数功能、性能等的描述
 *
 *  @Calls:	        // 被本函数调用的函数清单
 *
 *  @Called By:	    // 调用本函数的函数清单
 *
 *  @Table Accessed:// 被访问的表（此项仅对于牵扯到数据库操作的程序）
 *
 *  @Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
 *
 *  @Input:	        // 对输入参数的说明
 *
 *  @Output:        // 对输出参数的说明
 *
 *  @Return:        // 函数返回值的说明
 *
 *  @Enter          // Precondition
 *
 *  @Leave          // Postcondition
 *
 *  @Others:        // 其它说明
 *
 *  ============================================================================
 */
static inline
bool ta_candlesticks_is_left_included1(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ((pk1->m_high < pk2->m_high) && (pk1->m_low > pk2->m_low));
}

static inline
bool ta_candlesticks_is_left_included2(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ((pk1->m_high == pk2->m_high) && (pk1->m_low > pk2->m_low));
}

static inline
bool ta_candlesticks_is_left_included3(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ((pk1->m_high < pk2->m_high) && (pk1->m_low == pk2->m_low));
}

static inline
bool ta_candlesticks_is_right_included1(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ta_candlesticks_is_left_included1(pk2, pk1);
}

static inline
bool ta_candlesticks_is_right_included2(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ta_candlesticks_is_left_included2(pk2, pk1);
}

static inline
bool ta_candlesticks_is_right_included3(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ta_candlesticks_is_left_included3(pk2, pk1);
}

static inline
bool ta_candlesticks_is_equal(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return ((pk1->m_high == pk2->m_high) && (pk1->m_low == pk2->m_low));
}

static inline
bool ta_candlesticks_is_top(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2, ta_candlesticks_t * pk3)
{
	return (((pk2->m_high > pk1->m_high) && (pk2->m_high > pk3->m_high)) &&
		    ((pk2->m_low  > pk1->m_low)  && (pk2->m_low  > pk3->m_low)));
}

static inline
bool ta_candlesticks_is_bot(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2, ta_candlesticks_t * pk3)
{
	return (((pk2->m_high < pk1->m_high) && (pk2->m_high < pk3->m_high)) &&
		    ((pk2->m_low < pk1->m_low)   && (pk2->m_low < pk3->m_low)));
}

static inline
bool ta_candlesticks_is_top2(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return (pk2->m_high > pk1->m_high);
}

static inline
bool ta_candlesticks_is_bot2(ta_candlesticks_t * pk1, ta_candlesticks_t * pk2)
{
	return (pk2->m_low < pk1->m_low);
}

static inline
float ta_candlesticks_mid(ta_candlesticks_t * pk)
{
	return ((pk->m_high + pk->m_low) / 2);
}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif  /* if !defined (__TA_CANDLESTICKS_H) */