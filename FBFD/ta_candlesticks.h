#pragma once
/** ============================================================================
 *
 *  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co, Ltd.
 *
 *  @File Name:	ta_candlesticks.h
 *
 *  @Author: xiong-kaifang   Version: v1.0   Date: 2015-01-11
 *
 *  @Description:   // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
 *                  // �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
 *                  // �ơ�˳�򡢶����������ȹ�ϵ
 *                  //
 *
 *                  The header file for technical analysis of candlesticks.
 *
 *  @Others:        // ��������˵��
 *
 *  @Function List: // ��Ҫ�����б�ÿ����¼�Ͱ��������������ܼ�Ҫ˵��
 *      1.  ...
 *      2.  ...
 *
 *  @History:       // �޸���ʷ��¼�б�ÿ���޸ļ�¼�Ͱ����޸����ڡ��޸�
 *                  // ʱ�估�޸����ݼ���
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
 *  @Function:      // ��������
 *
 *  @Description:   // �������ܡ����ܵȵ�����
 *
 *  @Calls:	        // �����������õĺ����嵥
 *
 *  @Called By:	    // ���ñ������ĺ����嵥
 *
 *  @Table Accessed:// �����ʵı����������ǣ�������ݿ�����ĳ���
 *
 *  @Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
 *
 *  @Input:	        // �����������˵��
 *
 *  @Output:        // �����������˵��
 *
 *  @Return:        // ��������ֵ��˵��
 *
 *  @Enter          // Precondition
 *
 *  @Leave          // Postcondition
 *
 *  @Others:        // ����˵��
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