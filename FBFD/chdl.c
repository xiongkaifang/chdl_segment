/** ============================================================================
 *
 *  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co.,, Ltd.
 *
 *  @File name:	chdl_fbfd.c
 *
 *  @Author: xiong-kaifang   Version: v1.0   Date: 2016-01-09
 *
 *  @Description:   The description of this file.
 *
 *                  The source file for chdl fbfd implementation.
 *
 *  @Version:       v1.0
 *
 *  @Function List: // 主要函数及功能
 *      1.  －－－－－
 *      2.  －－－－－
 *
 *  @History:       // 历史修改记录
 *
 *  <author>        <time>       <version>      <description>
 *
 *  xiong-kaifang   2016-01-09     v1.0	        Write this module.
 *
 *
 *  ============================================================================
 */

/*  --------------------- Include system headers ---------------------------- */
#include <stdio.h>
#include <stdlib.h>

/*  --------------------- Include user headers   ---------------------------- */
#include "stdafx.h"
#include "chdl.h"
#include "dlist.h"
#include "ta_candlesticks.h"
#include "osa_status.h"

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
#define CANDLESTICKS_INCLUDED

/*
 *  --------------------- Structure definition ---------------------------------
 */

/** ----------------------------------------------------------------------------
 *  @Name:          Structure name
 *
 *  @Description:   Description of the structure.
 *
 *  @Field:         Field1 member
 *
 *  @Field          Field2 member
 *  ----------------------------------------------------------------------------
 */
#if 0
struct __stock_candlesticks_t; typedef struct __stock_candlesticks_t stock_candlesticks_t;
struct __stock_candlesticks_t
{
	void    * m_reserved[2];
	unsigned int m_id;
    unsigned int m_index;
	float    m_open;
	float    m_close;
	float    m_high;
	float    m_low;
};
#endif

typedef ta_candlesticks_t stock_candlesticks_t;

enum __stock_indicator_type_t; typedef enum __stock_indicator_type_t stock_indicator_type_t;
enum __stock_indicator_type_t
{
	STOCK_INDICATOR_TYPE_TREND = 0,
	STOCK_INDICATOR_TYPE_MOMENTUM = 1,
	STOCK_INDICATOR_TYPE_VOLUME = 2,
	STOCK_INDICATOR_TYPE_VOLATILITY = 3,
	STOCK_INDICATOR_TYPE_BREADTH = 4,
	STOCK_INDICATOR_TYPE_SPT_RST = 5, /* Support & resistence */
	STOCK_INDICATOR_TYPE_OTHER = 10
};

struct __stock_macd_indicator_t; typedef struct __stock_macd_indicator_t stock_macd_indicator_t;
struct __stock_macd_indicator_t
{
	stock_indicator_type_t
		m_type;
	float    m_diff;
	float    m_dea;
	float    m_macd;
};

enum __stock_movement_type_t; typedef enum __stock_movement_type_t stock_movement_type_t;
enum __stock_movement_type_t
{
	STOCK_MOVEMENT_TYPE_TENDENCY = 0,
	STOCK_MOVEMENT_TYPE_CONSOLIDATION = 1
};

enum __stock_tendency_type_t; typedef enum __stock_tendency_type_t stock_tendency_type_t;
enum __stock_tendency_type_t
{
	STOCK_TRENDENCY_TYPE_ADVANCING = 0,
	STOCK_TRENDENCY_TYPE_DECLINE = 1
};

enum __stock_chart_period_type_t; typedef enum __stock_chart_period_type_t stock_chart_period_type_t;
enum __stock_chart_period_type_t
{
	STOCK_CHART_PERIOD_TYPE_MIN01 = 0,
	STOCK_CHART_PERIOD_TYPE_MIN05 = 1,
	STOCK_CHART_PERIOD_TYPE_MIN15 = 2,
	STOCK_CHART_PERIOD_TYPE_MIN30 = 3,
	STOCK_CHART_PERIOD_TYPE_MIN60 = 4,
	STOCK_CHART_PERIOD_TYPE_DAY = 5,
	STOCK_CHART_PERIOD_TYPE_WEEK = 6,
	STOCK_CHART_PERIOD_TYPE_MONTH = 7,
	STOCK_CHART_PERIOD_TYPE_YEAR = 8
};

enum __stock_trend_level_type_t; typedef enum __stock_trend_level_type_t stock_trend_level_type_t;
enum __stock_trend_level_type_t
{
	STOCK_TREND_LEVEL_TYPE_MIN01 = 0,
	STOCK_TREND_LEVEL_TYPE_MIN05 = 1,
	STOCK_TREND_LEVEL_TYPE_MIN15 = 2,
	STOCK_TREND_LEVEL_TYPE_MIN30 = 3,
	STOCK_TREND_LEVEL_TYPE_MIN60 = 4,
	STOCK_TREND_LEVEL_TYPE_DAY = 5,
	STOCK_TREND_LEVEL_TYPE_WEEK = 6,
	STOCK_TREND_LEVEL_TYPE_MONTH = 7,
	STOCK_TREND_LEVEL_TYPE_YEAR = 8
};

enum __stock_candlesticks_node_type_t; typedef enum __stock_candlesticks_node_type_t stock_candlesticks_node_type_t;
enum __stock_candlesticks_node_type_t
{
	STOCK_CANDLESTICKS_NODE_TYPE_ELEMENT = 1 < 0,
	STOCK_CANDLESTICKS_NODE_TYPE_SUBSECTION = 1 < 1,  /* Yi Bi */
	STOCK_CANDLESTICKS_NODE_TYPE_SECTION = 1 < 2,  /* Yi Duan */
	STOCK_CANDLESTICKS_NODE_TYPE_PIVOT = 1 < 3,
	STOCK_CANDLESTICKS_NODE_TYPE_TREND_ADV = 1 < 4,
	STOCK_CANDLESTICKS_NODE_TYPE_TREND_DEC = 1 < 5
};

struct __stock_candlesticks_node_t; typedef struct __stock_candlesticks_node_t stock_candlesticks_node_t;
struct __stock_candlesticks_node_t
{
	void *                  reserved[2];

	stock_candlesticks_t    m_candlestick;
	stock_macd_indicator_t  m_indicator;
};

struct __stock_section_t; typedef struct __stock_section_t stock_section_t, ta_section_t;
struct __stock_section_t
{
	void                 * m_reserved[2];
	unsigned int           m_id;
	stock_candlesticks_t * m_start;
	stock_candlesticks_t * m_end;

	ta_candlesticks_t      m_sticks;

	stock_tendency_type_t  m_type;

	dlist_t                m_list;
};

struct __stock_segment_t; typedef struct __stock_segment_t stock_segment_t, ta_segment_t;
struct __stock_segment_t
{
	void                 * m_reserved[2];
	unsigned int           m_id;
#if 0
	stock_section_t *      m_start;
	stock_section_t *      m_end;
#else
	stock_candlesticks_t * m_start;
	stock_candlesticks_t * m_end;

	void                 * m_arg;
#endif

	stock_tendency_type_t  m_type;

	dlist_t                m_list;
};

struct __ta_candlesticks_secseg_t; typedef struct __ta_candlesticks_secseg_t ta_candlesticks_secseg_t;
struct __ta_candlesticks_secseg_t
{
	stock_section_t * m_section;
	dlist_t           m_slist;
	dlist_t           m_clist;
};

struct __ta_section_range_t; typedef struct __ta_section_range_t ta_section_range_t;
struct __ta_section_range_t
{
	stock_section_t	     * m_start;
	stock_section_t      * m_end;
	stock_section_t	     * m_max;
	stock_section_t      * m_min;
	stock_tendency_type_t  m_type;
};

struct __stock_pivot_t; typedef struct __stock_pivot_t stock_pivot_t, ta_pivot_t;
struct __stock_pivot_t
{
	//stock_pivot_type_t   m_type;

	stock_section_t    *   m_pstart;
	stock_section_t    *   m_pend;

	dlist_t                m_list;
};

struct __stock_trendency_t; typedef struct __stock_trendency_t stock_trendency_t, ta_trendency_t;
struct __stock_trendency_t
{
	stock_tendency_type_t  m_type;
	stock_pivot_t *        m_tstart;
	stock_pivot_t *        m_tend;

	dlist_t                m_list;
};

enum __ta_chart_node_type_t; typedef enum __ta_chart_node_type_t ta_chart_node_type_t;
enum __ta_chart_node_type_t
{
	TA_CHART_NODE_TYPE_CANDLESTICKS = 1 < 0,
	TA_CHART_NODE_TYPE_SUBSECTION   = 1 < 1,  /* Yi Bi */
	TA_CHART_NODE_TYPE_SECTION      = 1 < 2,  /* Yi Duan */
	TA_CHART_NODE_TYPE_PIVOT        = 1 < 3,
	TA_CHART_NODE_TYPE_TREND_ADV    = 1 < 4,
	TA_CHART_NODE_TYPE_TREND_DEC    = 1 < 5,
};

struct __stock_chart_node_t; typedef struct __stock_chart_node_t stock_chart_node_t;
struct __stock_chart_node_t
{
	void                 * m_reserved[2];
	stock_candlesticks_node_type_t
		m_node_type;

	union
	{
		stock_candlesticks_node_t
			m_candlesticks;
		stock_section_t    m_section;
		stock_segment_t    m_segment;
		stock_pivot_t      m_pivot;
		stock_trendency_t  m_trend;
	} u;
};

struct __ta_chart_node_t; typedef struct __ta_chart_node_t ta_chart_node_t;
struct __ta_chart_node_t
{
	void                 * m_reserved[2];

	ta_chart_node_type_t   m_type;

	union
	{
		ta_candlesticks_t  m_sticks;
		ta_section_t       m_section;
		ta_segment_t       m_segment;
		ta_pivot_t         m_pivot;
		ta_trendency_t     m_trend;
	} u;
};

enum __stock_candlesticks_pattern_type_t; typedef enum __stock_candlesticks_pattern_type_t stock_candlesticks_pattern_type_t;
enum __stock_candlesticks_pattern_type_t
{
	STOCK_CANDLESTICKS_PATTERN_TYPE_INV = -1,	/* Invalid pattern */
	STOCK_CANDLESTICKS_PATTERN_TYPE_TOP = 0,	/* top pattern     */
	STOCK_CANDLESTICKS_PATTERN_TYPE_BOT = 1   	/* bottom pattern  */
};

struct __stock_candlesticks_pattern_t; typedef struct __stock_candlesticks_pattern_t stock_candlesticks_pattern_t;
struct __stock_candlesticks_pattern_t
{
	void                 * m_reserved[2];
	stock_candlesticks_pattern_type_t
		m_type;
	stock_candlesticks_t * m_candlesticks;
};

struct __stock_chart_t; typedef struct __stock_chart_t stock_chart_t;
struct __stock_chart_t
{
	stock_chart_period_type_t
		m_period;

	unsigned int		   m_data_len;
    unsigned int           m_sec_index;
    unsigned int           m_seg_index;
	stock_chart_node_t   * m_node;
	stock_candlesticks_t * m_candlesticks;

    dlist_t                m_node_list;

	dlist_t                m_pattern_list;
	dlist_t                m_csticks_list;
	dlist_t                m_msticks_list;
	dlist_t				   m_section_list;
	dlist_t                m_segment_list;
};

typedef struct __stock_chart_t ta_chart_t;

/*
 *  --------------------- Global variable definition ---------------------------
 */

/** ----------------------------------------------------------------------------
 *  @Name:          Variable name
 *
 *  @Description:   Description of the variable.
 * -----------------------------------------------------------------------------
 */
static stock_chart_t glb_stock_chart_section_obj = {
	STOCK_CHART_PERIOD_TYPE_MIN01,
	0,
    0,
    0,
	NULL,
	NULL,
};

static stock_chart_t glb_stock_chart_segment_obj = {
	STOCK_CHART_PERIOD_TYPE_MIN01,
	0,
	0,
    0,
	NULL,
	NULL,
};

static unsigned int  glb_sec_init = 0;
static unsigned int  glb_seg_init = 0;

/*
 *  --------------------- Local function forward declaration -------------------
 */

/** ============================================================================
 *
 *  @Function:      Local function forward declaration.
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
 *  @Others:        //其它说明
 *
 *  ============================================================================
 */
static int __stock_candlesticks_pattern_map_fxn(dlist_element_t * elem, void * data);

static int __ta_candlesticks_included_process(dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_pattern_stats2(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_pattern_stats3(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_pattern_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_pattern_map(dlist_t * plist, float * pOut);

static int __ta_candlesticks_section_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_segment_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int __ta_candlesticks_segment_stats2(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto);

static int
__ta_candlesticks_segment_stats_internal(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto, ta_section_t * pstart, bool loose);

static int __ta_candlesticks_sequence_map_fxn(dlist_element_t * elem, void * data);

static int __ta_candlesticks_section_map_fxn1(dlist_element_t * elem, void * data);
static int __ta_candlesticks_section_map_fxn2(dlist_element_t * elem, void * data);
static int __ta_candlesticks_section_map_fxn3(dlist_element_t * elem, void * data);
static int __ta_candlesticks_section_map_fxn4(dlist_element_t * elem, void * data);

static stock_candlesticks_pattern_t *
__ta_candlesticks_find_pattern_after_id(dlist_t * plist, int ptype, unsigned int id);

static int __ta_candlesticks_node_free_fxn(dlist_element_t * elem, void * data);

static int __ta_candlesticks_segment_map_fxn(dlist_element_t * elem, void * data);

static int __ta_candlesticks_section_match_fxn(dlist_element_t * elem, void * data);

static bool __ta_candlesticks_section_search_fxn(dlist_element_t * elem, void * data);

static status_t __ta_candlesticks_node_new (ta_chart_t * pobj, void ** ppnode);

static status_t __ta_candlesticks_node_free(ta_chart_t * pobj, void * pnode);

/*
 *  --------------------- Public function definition ---------------------------
 */

/** ============================================================================
 *
 *  @Function:      Public function definition.
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
void ta_chdl_section(unsigned int data_len, float *pOut, float *pINa, float *pINb, float *pINc)
{
	unsigned int                   i;
	unsigned int                   cnt          = 0;
	stock_chart_t                * pobj         = &glb_stock_chart_section_obj;
	stock_candlesticks_t         * pcur_sticks  = NULL;

    if (glb_sec_init++ == 0) {
        dlist_init(&pobj->m_node_list);
    }

	/*
	*	Step0: Reset the output array.
	*/
	for (i = 0; i < data_len; i++) {
		pOut[i] = 0.0;
	}

	dlist_init(&pobj->m_pattern_list);
	dlist_init(&pobj->m_csticks_list);
	dlist_init(&pobj->m_msticks_list);
	dlist_init(&pobj->m_section_list);
	dlist_init(&pobj->m_segment_list);

	pobj->m_sec_index = 0;

	/*
	 *	Step1: Allocate memory for candlesticks if neccessary.
	 */
	if (data_len > pobj->m_data_len) {
		if (pobj->m_candlesticks != NULL) {
			free(pobj->m_candlesticks);
			pobj->m_candlesticks = NULL;
		}

		pobj->m_data_len = data_len;
		pobj->m_candlesticks = calloc(pobj->m_data_len, sizeof(stock_candlesticks_t));
	}

	/* Copy the candlesticks data */
	for (i = 0; i < data_len; i++) {
		pcur_sticks         = &pobj->m_candlesticks[i];
		pcur_sticks->m_id   = i;
		pcur_sticks->m_high = pINa[i];
		pcur_sticks->m_low  = pINb[i];
		pcur_sticks->m_close = pINc[i];
		dlist_initialize_element((dlist_element_t *)pcur_sticks);
		dlist_put_tail(&pobj->m_csticks_list, (dlist_element_t *)pcur_sticks);
	}

	/* Process the included candlesticks */
	__ta_candlesticks_included_process(&pobj->m_csticks_list, &pobj->m_msticks_list);

	/* Count the pattern type */
	__ta_candlesticks_pattern_stats(pobj, &pobj->m_msticks_list, &pobj->m_pattern_list);

	/*
	 *	Step2: Map the pattern to output arrray.
	 */
	__ta_candlesticks_pattern_map(&pobj->m_pattern_list, pOut);

	/*
	 *	Free all the patterns.
	 */
	dlist_map2(&pobj->m_pattern_list, __ta_candlesticks_node_free_fxn, (void *)pobj);
}

void ta_chdl_segment(unsigned int data_len, float *pOut, float *pINa, float *pINb, float *pINc)
{
	unsigned int                   i;
	unsigned int                   cnt          = 0;
	stock_chart_t                * pobj         = &glb_stock_chart_segment_obj;
	stock_candlesticks_t         * pcur_sticks  = NULL;

    if (glb_seg_init++ == 0) {
        dlist_init(&pobj->m_node_list);
    }

	/*
	 *	Step0: Reset the output array.
	 */
	for (i = 0; i < data_len; i++) {
		pOut[i] = 0.0;
	}

	dlist_init(&pobj->m_pattern_list);
	dlist_init(&pobj->m_csticks_list);
	dlist_init(&pobj->m_msticks_list);
	dlist_init(&pobj->m_section_list);
	dlist_init(&pobj->m_segment_list);

	pobj->m_sec_index = 0;
    pobj->m_seg_index = 0;

	/*
	 *	Step1: Allocate memory for candlesticks if neccessary.
	 */
	if (data_len > pobj->m_data_len) {
		if (pobj->m_candlesticks != NULL) {
			free(pobj->m_candlesticks);
			pobj->m_candlesticks = NULL;
		}

		pobj->m_data_len = data_len * 2;
		pobj->m_candlesticks = calloc(pobj->m_data_len, sizeof(stock_candlesticks_t));
	}

	/* Copy the candlesticks data */
	for (i = 0; i < data_len; i++) {
		pcur_sticks = &pobj->m_candlesticks[i];
		pcur_sticks->m_id = i;
		pcur_sticks->m_high = pINa[i];
		pcur_sticks->m_low = pINb[i];
		pcur_sticks->m_close = pINc[i];
		dlist_initialize_element((dlist_element_t *)pcur_sticks);
		dlist_put_tail(&pobj->m_csticks_list, (dlist_element_t *)pcur_sticks);
	}

	/* Process the included candlesticks */
	__ta_candlesticks_included_process(&pobj->m_csticks_list, &pobj->m_msticks_list);

	/* Count the pattern type */
	__ta_candlesticks_pattern_stats(pobj, &pobj->m_msticks_list, &pobj->m_pattern_list);

	/* Count the section and segment */
	__ta_candlesticks_section_stats(pobj, &pobj->m_pattern_list, &pobj->m_section_list);
	__ta_candlesticks_segment_stats(pobj, &pobj->m_section_list, &pobj->m_segment_list);
	//__ta_candlesticks_segment_stats2(pobj, &pobj->m_section_list, &pobj->m_segment_list);

	/* Map the segment to output arrray. */
	dlist_map(&pobj->m_segment_list, __ta_candlesticks_segment_map_fxn, (void *)pOut);

	/* Free all the sections and segments */
	dlist_map2(&pobj->m_section_list, __ta_candlesticks_node_free_fxn, (void *)pobj);
	dlist_map2(&pobj->m_segment_list, __ta_candlesticks_node_free_fxn, (void *)pobj);

	/*
	 *	Free all the patterns.
	 */
	dlist_map2(&pobj->m_pattern_list, __ta_candlesticks_node_free_fxn, (void *)pobj);
}

/*
 *  --------------------- Local function definition ----------------------------
 */

/** ============================================================================
 *
 *  @Function:      Local function definition.
 *
 *  @Description:   //  函数功能、性能等的描述
 *
 *  ============================================================================
 */
static int __stock_candlesticks_pattern_map_fxn(dlist_element_t * elem, void * data)
{
	float                        * pfOut = (float *)data;
	stock_candlesticks_pattern_t * pattern = (stock_candlesticks_pattern_t *)elem;

	if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pattern->m_type) {
		pfOut[pattern->m_candlesticks->m_id] = 1.0;
	}

	if (STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == pattern->m_type) {
		pfOut[pattern->m_candlesticks->m_id] = -1.0;
	}

	return 0;
}

static int __ta_candlesticks_pattern_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
	status_t                           status       = OSA_SOK;
	dlist_t                            tmp_list;
	unsigned int                       cnt          = 0;
	stock_candlesticks_pattern_type_t  pattern_type;
	stock_candlesticks_t             * pbfe_sticks  = NULL;
	stock_candlesticks_t             * plst_sticks  = NULL;
	stock_candlesticks_t             * pcur_sticks  = NULL;
	stock_candlesticks_pattern_t     * pfst_pattern = NULL;
	stock_candlesticks_pattern_t     * plst_pattern = NULL;
	stock_candlesticks_pattern_t     * pcur_pattern = NULL;

	dlist_init(&tmp_list);
	dlist_init(pto);

	status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {
		
		status = dlist_count(&tmp_list, &cnt);

		if (cnt > 1) {
			dlist_last(&tmp_list, (dlist_element_t **)&plst_sticks);
			dlist_prev(&tmp_list, (dlist_element_t *)plst_sticks, (dlist_element_t **)&pbfe_sticks);

			dlist_last(pto, (dlist_element_t **)&plst_pattern);

			/* Initialize the pattern type using default value: invalid pattern */
			pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_INV;

			if (ta_candlesticks_is_top(pbfe_sticks, plst_sticks, pcur_sticks)) {
				/* top-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_TOP;
			}
			if (ta_candlesticks_is_bot(pbfe_sticks, plst_sticks, pcur_sticks)) {
				/* bottom-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_BOT;
			}

			/* TODO: There is a bug here, fix it up tomorrow!!! */
			if (STOCK_CANDLESTICKS_PATTERN_TYPE_INV != pattern_type) {
				if (plst_pattern != NULL) {
					if (plst_pattern->m_type == pattern_type) {
						if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pattern_type &&
							(plst_pattern->m_candlesticks->m_high < plst_sticks->m_high)) {
							/* Update the top-pattern */
							plst_pattern->m_candlesticks = plst_sticks;
						}
						else if (STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == pattern_type &&
							(plst_pattern->m_candlesticks->m_low > plst_sticks->m_low)) {
							/* Update the bottom-pattern */
							plst_pattern->m_candlesticks = plst_sticks;
						}
					}
					else {
						if ((plst_sticks->m_index - plst_pattern->m_candlesticks->m_index > 3) 
							||
							((plst_sticks->m_index - plst_pattern->m_candlesticks->m_index == 3) && 
							 (plst_sticks->m_id - plst_pattern->m_candlesticks->m_id > 3))) {

							/* This is a valid pattern */
							if (((STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pattern_type) && 
								 (plst_sticks->m_high > plst_pattern->m_candlesticks->m_high)) 
								                           ||
								((STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == pattern_type) && 
								 (plst_sticks->m_low  < plst_pattern->m_candlesticks->m_low))) {

								//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                                __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

								pcur_pattern->m_type = pattern_type;
								pcur_pattern->m_candlesticks = plst_sticks;

								dlist_initialize_element((dlist_element_t *)pcur_pattern);
								dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
							}
						}
						else {
							/* Process the Gap */
							dlist_prev(pto, (dlist_element_t *)plst_pattern, (dlist_element_t **)&pfst_pattern);
							if (pfst_pattern != NULL) {
								if ((pfst_pattern->m_type == STOCK_CANDLESTICKS_PATTERN_TYPE_TOP &&
									 plst_sticks->m_high > pfst_pattern->m_candlesticks->m_high)
									/* Upward Gap */
									||
									/* Downward Gap */
									(pfst_pattern->m_type == STOCK_CANDLESTICKS_PATTERN_TYPE_BOT && 
									 plst_sticks->m_low < pfst_pattern->m_candlesticks->m_low)) {

									//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                                    __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

									pcur_pattern->m_type = pattern_type;
									pcur_pattern->m_candlesticks = plst_sticks;

									dlist_initialize_element((dlist_element_t *)pcur_pattern);
									dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
								}
							}
						}
					}
				}
				else {
					/* This is a valid pattern */

					//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                    __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

					pcur_pattern->m_type = pattern_type;
					pcur_pattern->m_candlesticks = plst_sticks;

					dlist_initialize_element((dlist_element_t *)pcur_pattern);
					dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
				}
			}
		}
		
		dlist_initialize_element((dlist_element_t *)pcur_sticks);
		dlist_put_tail(&tmp_list, (dlist_element_t *)pcur_sticks);

		status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	}

#define TA_TAIL_CANDLESTICKS

#if defined(TA_TAIL_CANDLESTICKS)
	/* Process the tail candlesticks */
	dlist_last(pto      , (dlist_element_t **)&plst_pattern);
	dlist_last(&tmp_list, (dlist_element_t **)&plst_sticks);

	float ptn_mid, lst_mid;

	if (plst_pattern != NULL && plst_sticks != NULL) {
		lst_mid = ta_candlesticks_mid(plst_sticks);
		ptn_mid = ta_candlesticks_mid(plst_pattern->m_candlesticks);

		if (lst_mid > ptn_mid) {
			if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == plst_pattern->m_type) {
				plst_pattern->m_candlesticks = plst_sticks;
			}
			else {
				//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

				pcur_pattern->m_type = STOCK_CANDLESTICKS_PATTERN_TYPE_TOP;
				pcur_pattern->m_candlesticks = plst_sticks;

				dlist_initialize_element((dlist_element_t *)pcur_pattern);
				dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
			}
		}
		else if (lst_mid < ptn_mid) {
			if (STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == plst_pattern->m_type) {
				plst_pattern->m_candlesticks = plst_sticks;
			}
			else {
				//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

				pcur_pattern->m_type = STOCK_CANDLESTICKS_PATTERN_TYPE_BOT;
				pcur_pattern->m_candlesticks = plst_sticks;

				dlist_initialize_element((dlist_element_t *)pcur_pattern);
				dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
			}
		}
	}
#endif

	/* Restore the original candlesticks from tmp list to frm list */
	status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {
		status = dlist_initialize_element((dlist_element_t *)pcur_sticks);
		status = dlist_put_tail(pfrm, (dlist_element_t *)pcur_sticks);
		status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	}

	return 0;
}

static int __ta_candlesticks_pattern_stats2(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
	status_t                           status = OSA_SOK;
	dlist_t                            tmp_list;
	unsigned int                       cnt = 0;
	stock_candlesticks_pattern_type_t  pattern_type;
	stock_candlesticks_t             * pbfe_sticks = NULL;
	stock_candlesticks_t             * plst_sticks = NULL;
	stock_candlesticks_t             * pcur_sticks = NULL;
	stock_candlesticks_pattern_t     * pfst_pattern = NULL;
	stock_candlesticks_pattern_t     * plst_pattern = NULL;
	stock_candlesticks_pattern_t     * pcur_pattern = NULL;

	dlist_init(&tmp_list);
	dlist_init(pto);

	status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {

		status = dlist_count(&tmp_list, &cnt);

		if (cnt > 1) {

			dlist_last(&tmp_list, (dlist_element_t **)&plst_sticks);
			dlist_prev(&tmp_list, (dlist_element_t *)plst_sticks, (dlist_element_t **)&pbfe_sticks);

			dlist_last(pto, (dlist_element_t **)&plst_pattern);

			/* Initialize the pattern type using default value: invalid pattern */
			pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_INV;

			if (ta_candlesticks_is_top(pbfe_sticks, plst_sticks, pcur_sticks)) {
				/* top-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_TOP;
			}
			else if (ta_candlesticks_is_bot(pbfe_sticks, plst_sticks, pcur_sticks)) {
				/* bottom-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_BOT;
			}

			if (STOCK_CANDLESTICKS_PATTERN_TYPE_INV != pattern_type) {
				if (plst_pattern != NULL) {
					if (plst_pattern->m_type == pattern_type) {
						if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pattern_type &&
							(plst_pattern->m_candlesticks->m_high < plst_sticks->m_high)) {
							/* Update the top-pattern */
							plst_pattern->m_candlesticks = plst_sticks;
						}
						else if (STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == pattern_type &&
							(plst_pattern->m_candlesticks->m_low > plst_sticks->m_low)) {
							/* Update the bottom-pattern */
							plst_pattern->m_candlesticks = plst_sticks;
						}
					}
					else {
						//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                        __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

						pcur_pattern->m_type = pattern_type;
						pcur_pattern->m_candlesticks = plst_sticks;

						dlist_initialize_element((dlist_element_t *)pcur_pattern);
						dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
					}
				}
				else {
					/* This is a valid pattern */
					//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                    __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

					pcur_pattern->m_type = pattern_type;
					pcur_pattern->m_candlesticks = plst_sticks;

					dlist_initialize_element((dlist_element_t *)pcur_pattern);
					dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
				}
			}
		}

		dlist_initialize_element((dlist_element_t *)pcur_sticks);
		dlist_put_tail(&tmp_list, (dlist_element_t *)pcur_sticks);

		status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	}

	/* Restore the original candlesticks from tmp list to frm list */
	status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {
		status = dlist_initialize_element((dlist_element_t *)pcur_sticks);
		status = dlist_put_tail(pfrm, (dlist_element_t *)pcur_sticks);
		status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	}

	return 0;
}

static int __ta_candlesticks_pattern_stats3(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
	status_t                           status       = OSA_SOK;
	dlist_t                            tmp_list;
	stock_candlesticks_pattern_type_t  pattern_type;
	stock_candlesticks_t             * plst_sticks  = NULL;
	stock_candlesticks_t             * pcur_sticks  = NULL;
	stock_candlesticks_t             * pnex_sticks  = NULL;
	stock_candlesticks_pattern_t     * plst_pattern = NULL;
	stock_candlesticks_pattern_t     * pcur_pattern = NULL;

	dlist_init(&tmp_list);

	dlist_init(pto);

	status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);

	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {

		dlist_last(&tmp_list, (dlist_element_t **)&plst_sticks);

		if (plst_sticks != NULL) {

			dlist_last(pto, (dlist_element_t **)&plst_pattern);

			/* Initialize the pattern type using default value: invalid pattern */
			pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_INV;

			if (ta_candlesticks_is_top2(plst_sticks, pcur_sticks)) {
				/* top-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_TOP;
			}
			else if (ta_candlesticks_is_bot2(plst_sticks, pcur_sticks)) {
				/* bottom-pattern */
				pattern_type = STOCK_CANDLESTICKS_PATTERN_TYPE_BOT;
			}

			if (STOCK_CANDLESTICKS_PATTERN_TYPE_INV != pattern_type) {
				if (plst_pattern != NULL) {
					if (plst_pattern->m_type == pattern_type) {
						if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pattern_type &&
							(plst_pattern->m_candlesticks->m_high < pcur_sticks->m_high)) {
							/* Update the top-pattern */
							plst_pattern->m_candlesticks = pcur_sticks;
						}
						else if (STOCK_CANDLESTICKS_PATTERN_TYPE_BOT == pattern_type &&
							(plst_pattern->m_candlesticks->m_low > pcur_sticks->m_low)) {
							/* Update the bottom-pattern */
							plst_pattern->m_candlesticks = pcur_sticks;
						}
					}
					else {
						//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                        __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

						pcur_pattern->m_type = pattern_type;
						pcur_pattern->m_candlesticks = pcur_sticks;

						dlist_initialize_element((dlist_element_t *)pcur_pattern);
						dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
					}
				}
				else {
					/* This is a valid pattern */
					//pcur_pattern = malloc(sizeof(stock_candlesticks_pattern_t));
                    __ta_candlesticks_node_new(pobj, (void **)&pcur_pattern);

					pcur_pattern->m_type = pattern_type;
					pcur_pattern->m_candlesticks = pcur_sticks;

					dlist_initialize_element((dlist_element_t *)pcur_pattern);
					dlist_put_tail(pto, (dlist_element_t *)pcur_pattern);
				}
			}
		}

		dlist_initialize_element((dlist_element_t *)pcur_sticks);
		dlist_put_tail(&tmp_list, (dlist_element_t *)pcur_sticks);

		status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	}

	/* Restore the original candlesticks from tmp list to frm list */
	status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {
		status = dlist_initialize_element((dlist_element_t *)pcur_sticks);
		status = dlist_put_tail(pfrm, (dlist_element_t *)pcur_sticks);
		status = dlist_get_head(&tmp_list, (dlist_element_t **)&pcur_sticks);
	}

	return 0;
}

static int __ta_candlesticks_included_process(dlist_t * pfrm, dlist_t * pto)
{
	bool                   is_upward   = false;
	status_t               status      = OSA_SOK;
	unsigned int           index_seq   = 0;
	stock_candlesticks_t * pbfe_sticks = NULL;
	stock_candlesticks_t * plst_sticks = NULL;
	stock_candlesticks_t * pcur_sticks = NULL;

	dlist_init(pto);

	status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {

		status = dlist_last(pto, (dlist_element_t **)&plst_sticks);

		if (plst_sticks != NULL) {

			dlist_prev(pto, (dlist_element_t *)plst_sticks, (dlist_element_t **)&pbfe_sticks);
			if (pbfe_sticks != NULL) {
				/* There are more than one candlesticks on the candlesticks list */

				is_upward = plst_sticks->m_high > pbfe_sticks->m_high;

				if (ta_candlesticks_is_equal(plst_sticks, pcur_sticks)) {
				}
				else if (ta_candlesticks_is_left_included1(plst_sticks, pcur_sticks)) {
					plst_sticks->m_id = pcur_sticks->m_id;
					if (is_upward) {
						/* Left-included with upward */
						plst_sticks->m_high = pcur_sticks->m_high;
						plst_sticks->m_arg = pcur_sticks->m_arg;
					}
					else {
						/* Left-included with downward */
						plst_sticks->m_low = pcur_sticks->m_low;
						plst_sticks->m_arg = pcur_sticks->m_arg;
					}
				}
				else if (ta_candlesticks_is_left_included2(plst_sticks, pcur_sticks)) {
					if (is_upward) {
						/* Left-included with upward */
					}
					else {
						/* Left-included with downward */
						plst_sticks->m_id = pcur_sticks->m_id;
						plst_sticks->m_low = pcur_sticks->m_low;
						plst_sticks->m_arg = pcur_sticks->m_arg;
					}
				}
				else if (ta_candlesticks_is_left_included3(plst_sticks, pcur_sticks)) {
					if (is_upward) {
						/* Left-included with upward */
						plst_sticks->m_id = pcur_sticks->m_id;
						plst_sticks->m_high = pcur_sticks->m_high;
						plst_sticks->m_arg = pcur_sticks->m_arg;
					}
					else {
						/* Left-included with downward */
					}
				}
				else if (ta_candlesticks_is_right_included1(plst_sticks, pcur_sticks)) {
					if (is_upward) {
						/* Right-included with upward */
						plst_sticks->m_low = pcur_sticks->m_low;
						//plst_sticks->m_arg = pcur_sticks->m_arg;
					}
					else {
						/* Right-included with downward */
						plst_sticks->m_high = pcur_sticks->m_high;
						//plst_sticks->m_arg = pcur_sticks->m_arg;
					}
				}
				else if (ta_candlesticks_is_right_included2(plst_sticks, pcur_sticks)) {
					if (is_upward) {
						/* Right-included with upward */
						plst_sticks->m_low = pcur_sticks->m_low;
						//plst_sticks->m_arg = pcur_sticks->m_arg;
					}
					else {
						/* Right-included with downward */
					}
				}
				else if (ta_candlesticks_is_right_included3(plst_sticks, pcur_sticks)) {
					if (is_upward) {
						/* Right-included with upward */
					}
					else {
						/* Right-included with downward */
						plst_sticks->m_high = pcur_sticks->m_high;
						//plst_sticks->m_arg = pcur_sticks->m_arg;
					}
				}
				else {
					pcur_sticks->m_index = index_seq++;
					dlist_put_tail(pto, (dlist_element_t *)pcur_sticks);
				}
			}
			else {
				/* There is only one candlesticks on the candlesticks list */
				if (ta_candlesticks_is_equal(plst_sticks, pcur_sticks)) {
				}
				else if (ta_candlesticks_is_left_included1(plst_sticks, pcur_sticks)) {
					plst_sticks->m_high = pcur_sticks->m_high;
					plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else if (ta_candlesticks_is_left_included2(plst_sticks, pcur_sticks)) {
					plst_sticks->m_low = pcur_sticks->m_low;
					plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else if (ta_candlesticks_is_left_included3(plst_sticks, pcur_sticks)) {
					plst_sticks->m_high = pcur_sticks->m_high;
					plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else if (ta_candlesticks_is_right_included1(plst_sticks, pcur_sticks)) {
					plst_sticks->m_high = pcur_sticks->m_high;
					//plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else if (ta_candlesticks_is_right_included2(plst_sticks, pcur_sticks)) {
					plst_sticks->m_low = pcur_sticks->m_low;
					//plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else if (ta_candlesticks_is_right_included3(plst_sticks, pcur_sticks)) {
					plst_sticks->m_high = pcur_sticks->m_high;
					//plst_sticks->m_arg = pcur_sticks->m_arg;
				}
				else {
					pcur_sticks->m_index = index_seq++;
					dlist_put_tail(pto, (dlist_element_t *)pcur_sticks);
				}
			}
		}
		else {
			pcur_sticks->m_index = index_seq++;
			dlist_put_tail(pto, (dlist_element_t *)pcur_sticks);
		}

		status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	}

	return 0;
}

static int __ta_candlesticks_included_process2(dlist_t * pfrm, dlist_t * pto)
{
	bool                   is_upward = false;
	status_t               status = OSA_SOK;
	unsigned int           index_seq = 0;
	stock_candlesticks_t * pbfe_sticks = NULL;
	stock_candlesticks_t * plst_sticks = NULL;
	stock_candlesticks_t * pcur_sticks = NULL;

	dlist_init(pto);

	status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	while (!OSA_ISERROR(status) && pcur_sticks != NULL) {

		pcur_sticks->m_index = index_seq++;
		dlist_put_tail(pto, (dlist_element_t *)pcur_sticks);

		status = dlist_get_head(pfrm, (dlist_element_t **)&pcur_sticks);
	}

	return 0;
}

static int __ta_candlesticks_pattern_map(dlist_t * plist, float * pOut)
{
	/* Map the pattern type to output array */
	return dlist_map(plist, __stock_candlesticks_pattern_map_fxn, (void *)pOut);
}

static int __ta_candlesticks_section_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
	unsigned int                   index        = 0;
	status_t                       status       = OSA_SOK;
	stock_candlesticks_pattern_t * pcur_pattern = NULL;
	stock_candlesticks_pattern_t * pnex_pattern = NULL;
	stock_section_t              * psection     = NULL;

	dlist_init(pto);

	status = dlist_first(pfrm, (dlist_element_t **)&pcur_pattern);

	while (!OSA_ISERROR(status) && pcur_pattern != NULL) {
		
		status = dlist_next(pfrm, (dlist_element_t *)pcur_pattern, (dlist_element_t **)&pnex_pattern);
		if (pnex_pattern != NULL) {
			/* We find a section(Yi Bi!!!) */
			//psection = malloc(sizeof(stock_section_t));
            __ta_candlesticks_node_new(pobj, (void **)&psection);
			if (psection == NULL) {
				break;
			}

			psection->m_id = pobj->m_sec_index++;
			psection->m_start = pcur_pattern->m_candlesticks;
			psection->m_end = pnex_pattern->m_candlesticks;

			psection->m_sticks.m_id = psection->m_id / 2;
			if (STOCK_CANDLESTICKS_PATTERN_TYPE_TOP == pnex_pattern->m_type) {
				psection->m_type = STOCK_TRENDENCY_TYPE_ADVANCING;
				psection->m_sticks.m_high = psection->m_end->m_high;
				psection->m_sticks.m_low  = psection->m_start->m_low;
			}
			else {
				psection->m_type = STOCK_TRENDENCY_TYPE_DECLINE;
				psection->m_sticks.m_high = psection->m_start->m_high;
				psection->m_sticks.m_low = psection->m_end->m_low;
			}
			psection->m_sticks.m_arg = (void *)psection;
			dlist_initialize_element((dlist_element_t *)psection);
			dlist_put_tail(pto, (dlist_element_t *)psection);
		}

		pcur_pattern = pnex_pattern;
	}

	return 0;
}

static int __ta_candlesticks_segment_stats(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
    ta_section_t    * pcur_section = NULL;
    ta_section_t    * pnex_section = NULL;
    stock_segment_t * plst_segment = NULL;

    dlist_init(pto);

    /* Count segments */
    __ta_candlesticks_segment_stats_internal(pobj, pfrm, pto, pcur_section, false);

    /* TODO: Process the tail sections !!!! */
    dlist_last(pto, (dlist_element_t **)&plst_segment);

    if (plst_segment == NULL) {
        return 0;
    }

    pcur_section = (stock_section_t *)plst_segment->m_arg;
    dlist_next(pfrm, (dlist_element_t *)pcur_section, (dlist_element_t **)&pnex_section);
    
	return __ta_candlesticks_segment_stats_internal(pobj, pfrm, pto, pnex_section, true);
}

#define TA_SEGMENT_SEARCH

/* Reserved here for backup!!! */
static int __ta_candlesticks_segment_stats2(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto)
{
	unsigned int                   index = 0;
	dlist_t                        cur_plist;
	dlist_t                        nex_plist;
	status_t                       status = OSA_SOK;

	ta_section_range_t			   srange;

	ta_candlesticks_secseg_t       cur_seq, nex_seq;

	stock_section_t              * pbfe_section = NULL;
	stock_section_t              * pcur_section = NULL;
	stock_section_t              * pnex_section = NULL;
	stock_section_t              * ptn_section1 = NULL;
	stock_section_t              * ptn_section2 = NULL;
	stock_section_t              * ptmp_section = NULL;

	stock_segment_t              * pcur_segment = NULL;
	stock_segment_t              * pnex_segment = NULL;
	stock_segment_t              * plst_segment = NULL;

	stock_candlesticks_pattern_t * pcur_pattern = NULL;
	stock_candlesticks_pattern_t * pnex_pattern = NULL;

	status = dlist_first(pfrm, (dlist_element_t **)&pcur_section);

	while (!OSA_ISERROR(status) && pcur_section != NULL) {

		dlist_init(&cur_seq.m_slist);
		dlist_init(&cur_seq.m_clist);
		dlist_init(&nex_seq.m_slist);
		dlist_init(&nex_seq.m_clist);

		dlist_next(pfrm, (dlist_element_t *)pcur_section, (dlist_element_t **)&pnex_section);

		if (pnex_section != NULL) {

			cur_seq.m_section = pcur_section;
			nex_seq.m_section = pnex_section;

			/* Map the current section's sequence  */
			dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&cur_seq);

			__ta_candlesticks_included_process(&cur_seq.m_slist, &cur_seq.m_clist);

			__ta_candlesticks_pattern_stats2(pobj, &cur_seq.m_clist, &cur_plist);

			/* Map the current section's sequence  */
			dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&nex_seq);

			__ta_candlesticks_included_process(&nex_seq.m_slist, &nex_seq.m_clist);

			__ta_candlesticks_pattern_stats2(pobj, &nex_seq.m_clist, &nex_plist);

			/* Find the sequence's pattern */
			pcur_pattern =
				__ta_candlesticks_find_pattern_after_id(&cur_plist,
					STOCK_TRENDENCY_TYPE_ADVANCING == cur_seq.m_section->m_type ?
					STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
					cur_seq.m_section->m_id);

			pnex_pattern =
				__ta_candlesticks_find_pattern_after_id(&nex_plist,
					STOCK_TRENDENCY_TYPE_ADVANCING == nex_seq.m_section->m_type ?
					STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
					nex_seq.m_section->m_id);

#if !defined(TA_SEGMENT_RESERVED)

			if (pcur_pattern != NULL) {
				ptn_section1 = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;
			}
			if (pnex_pattern != NULL) {
				ptn_section2 = (stock_section_t *)pnex_pattern->m_candlesticks->m_arg;
			}

			if (((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id < ptn_section2->m_id))
				||
				 (pcur_pattern != NULL && pnex_pattern == NULL)) {

				/*
				 *	Case 1:  A + B + PA + PB.
				 *	Case 2:  A + B + PA + N/A.
				 *
				 *  Segment 1: A ---> PA.
				 */

				/* We find a segment (Yi Duan!!!) (upward or downward) */
				//pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
				if (pcur_segment == NULL) {
					break;
				}

				pcur_segment->m_id = index++;
				pcur_segment->m_type = pcur_section->m_type;
				pcur_segment->m_start = pcur_section->m_start;
				pcur_segment->m_end = ptn_section1->m_start;

#if defined(TA_SEGMENT_SEARCH)
				srange.m_start = pcur_section;
                srange.m_end = ptn_section1;
                if (pnex_pattern != NULL) {
                    srange.m_end = ptn_section2;
                }
				srange.m_type = pnex_section->m_type;
				srange.m_max = srange.m_min = NULL;

				dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

				if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
					ptmp_section = srange.m_max;
				}
				else {
					ptmp_section = srange.m_min;
				}

				pcur_segment->m_end = ptmp_section->m_start;

				dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
				pcur_segment->m_arg = (void *)pbfe_section;

				ptn_section1 = ptmp_section;
#else
				dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
				pcur_segment->m_arg = (void *)pbfe_section;
#endif

				dlist_initialize_element((dlist_element_t *)pcur_segment);
				dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

				pnex_section = ptn_section1;

				/*
				 *	Modified by: xiong-kaifang.
				 *  Date       : Jan, 20, 2016.
				 *  Description: TODO: Add codes to check the segment2.
				 */
				if (pnex_pattern != NULL) {
					if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
						(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

						/*
						 *	Segment2: B ---> PB.
						 */
						//pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                        __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
						if (pnex_segment == NULL) {
							break;
						}

						pnex_segment->m_id = index++;
						pnex_segment->m_type = pnex_section->m_type;

						pnex_segment->m_start = pcur_segment->m_end;
						pnex_segment->m_end = ptn_section2->m_start;

#if defined(TA_SEGMENT_SEARCH)
						srange.m_start = ptmp_section;
						srange.m_end = ptn_section2;
						srange.m_type = pcur_section->m_type;
						srange.m_max = srange.m_min = NULL;

						dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

						if (STOCK_TRENDENCY_TYPE_ADVANCING == pnex_segment->m_type) {
							ptmp_section = srange.m_max;
						}
						else {
							ptmp_section = srange.m_min;
						}

						pnex_segment->m_end = ptmp_section->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
						pnex_segment->m_arg = (void *)pbfe_section;

						ptn_section2 = ptmp_section;
#else
						dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
						pnex_segment->m_arg = (void *)pbfe_section;
#endif

						dlist_initialize_element((dlist_element_t *)pnex_segment);
						dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

						pnex_section = ptn_section2;
					}
				}
			}
			else if (
				((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id > ptn_section2->m_id))
				||
				(pcur_pattern == NULL && pnex_pattern != NULL)) {

				/*
				 *	Case 3: A + B + PB + PA.
				 *  Case 4: A + B + N/A + PB.
				 *
				 *  Segment 1: A.
				 *  Segment 2: B ---> PB.
				 */

				//pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
				if (pcur_segment == NULL) {
					break;
				}

				pcur_segment->m_id = index++;
				pcur_segment->m_type = pcur_section->m_type;

				srange.m_start = pcur_section;
				srange.m_end = ptn_section2;
				srange.m_type = pnex_section->m_type;
				srange.m_max = srange.m_min = NULL;

				dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

				if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
					ptmp_section = srange.m_max;
				}
				else {
					ptmp_section = srange.m_min;
				}

				pcur_segment->m_start = pcur_section->m_start;
				pcur_segment->m_end = ptmp_section->m_start;

				dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
				pcur_segment->m_arg = (void *)pbfe_section;

				dlist_initialize_element((dlist_element_t *)pcur_segment);
				dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

				pnex_section = ptmp_section;

				if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
					(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
					(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
					(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

					/*
					 *	Segment 2: B ---> PB (upward or downward).
					 */
					//pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                    __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
					if (pnex_segment == NULL) {
						break;
					}

					pnex_segment->m_id = index++;
					pnex_segment->m_type = pnex_section->m_type;

					pnex_segment->m_start = pcur_segment->m_end;
					pnex_segment->m_end = ptn_section2->m_start;

#if defined(TA_SEGMENT_SEARCH)
					srange.m_start = ptmp_section;
					srange.m_end = ptn_section2;
					srange.m_type = pcur_section->m_type;
					srange.m_max = srange.m_min = NULL;

					dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

					if (STOCK_TRENDENCY_TYPE_ADVANCING == pnex_segment->m_type) {
						ptmp_section = srange.m_max;
					}
					else {
						ptmp_section = srange.m_min;
					}

					pnex_segment->m_end = ptmp_section->m_start;

					dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
					pnex_segment->m_arg = (void *)pbfe_section;

					ptn_section2 = ptmp_section;
#else
					dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
					pnex_segment->m_arg = (void *)pbfe_section;
#endif

					dlist_initialize_element((dlist_element_t *)pnex_segment);
					dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

					pnex_section = ptn_section2;
				}
				else {
#if 0
                    /*
                     *  TODO  : Maybe we should process this case.
                     *  Case 3: A + B.
                     */
					if (pcur_pattern != NULL) {
						/* Update the current segment */
						pcur_segment->m_end = ptn_section1->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
						pcur_segment->m_arg = (void *)pbfe_section;

						pnex_section = ptn_section1;
					}
#endif
				}
			}
#else
			if (pcur_pattern != NULL && pnex_pattern != NULL) {

				ptn_section1 = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;
				ptn_section2 = (stock_section_t *)pnex_pattern->m_candlesticks->m_arg;

				if (ptn_section1->m_id < ptn_section2->m_id) {
					/*
					 *	A + B + PA + PB.
					 *	Segment1: A ---> PA.
					 */

					/* We find a segment (Yi Duan!!!) */
					pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
					if (pcur_segment == NULL) {
						break;
					}

					pcur_segment->m_id = index++;
					pcur_segment->m_type = pcur_section->m_type;

					if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}
					else {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}

					dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
					pcur_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pcur_segment);
					dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

#if 0
					/* Segment2: B ---> PB */
					pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
					if (pnex_segment == NULL) {
						break;
					}

					pnex_segment->m_id = index++;
					pnex_segment->m_type = pnex_section->m_type;

					if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}
					else {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}

					dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
					pcur_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pcur_segment);
					dlist_put_tail(pto, (dlist_element_t *)pcur_segment);
#endif

					pnex_section = ptn_section1;
				}
				else {
					/*
					 *	A + B + PB + PA.
					 *	Segment1: A.
					 *	Segment2: B ---> PB.
					 */

					 /*
					  *  Segment 1: This section is a segment.
					  */
					pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
					if (pcur_segment == NULL) {
						break;
					}

					pcur_segment->m_id = index++;
					pcur_segment->m_type = pcur_section->m_type;

					srange.m_start = pcur_section;
					srange.m_end = ptn_section2;
					srange.m_type = pnex_section->m_type;
					srange.m_max = srange.m_min = NULL;

					dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);


					if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = srange.m_max->m_start;
						ptmp_section = srange.m_max;
					}
					else {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = srange.m_min->m_start;
						ptmp_section = srange.m_min;
					}

					dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
					pcur_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pcur_segment);
					dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

					if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
						(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

						/*
						 *	Segment 2: B ---> PB (upward or downward).
						 */
						pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
						if (pnex_segment == NULL) {
							break;
						}

						pnex_segment->m_id = index++;
						pnex_segment->m_type = pnex_section->m_type;

						pnex_segment->m_start = pcur_segment->m_end;
						pnex_segment->m_end = ptn_section2->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
						pnex_segment->m_arg = (void *)pbfe_section;

						dlist_initialize_element((dlist_element_t *)pnex_segment);
						dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

						pnex_section = ptn_section2;
					}
					else {
						/* Update the current segment */
						pcur_segment->m_end = ptn_section1->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
						pcur_segment->m_arg = (void *)pbfe_section;

						pnex_section = ptn_section1;
					}
				}
			}
			else {
				if (pcur_pattern != NULL) {
					/*
					 *	A + B + PA + NULL.
					 *	Segment1: A ---> PA.
					 */
					ptn_section1 = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;

					 /* We find a segment (Yi Duan!!!) */
					pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
					if (pcur_segment == NULL) {
						break;
					}

					pcur_segment->m_id = index++;
					pcur_segment->m_type = pcur_section->m_type;

					if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}
					else {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = ptn_section1->m_start;
					}

					dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
					pcur_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pcur_segment);
					dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

					pnex_section = ptn_section1;
				}

				if (pnex_pattern != NULL) {
					/*
					 *	A + B + NULL + PB.
					 *	Segment1: A.
					 *	Segment2: B ---> PB.
					 */
					ptn_section2 = (stock_section_t *)pnex_pattern->m_candlesticks->m_arg;

					 /*
					 *  Segment 1: This section is a segment.
					 */
					pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
					if (pcur_segment == NULL) {
						break;
					}

					pcur_segment->m_id = index++;
					pcur_segment->m_type = pcur_section->m_type;

					srange.m_start = pcur_section;
					srange.m_end = ptn_section2;
					srange.m_type = pnex_section->m_type;
					srange.m_max = srange.m_min = NULL;

					dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

					if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = srange.m_max->m_start;
						ptmp_section = srange.m_max;
					}
					else {
						pcur_segment->m_start = pcur_section->m_start;
						pcur_segment->m_end = srange.m_min->m_start;
						ptmp_section = srange.m_min;
					}

					dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
					pcur_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pcur_segment);
					dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

					if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
						(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

						/*
						*	Segment 2: B ---> PB (upward | downward).
						*/
						pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
						if (pnex_segment == NULL) {
							break;
						}

						pnex_segment->m_id = index++;
						pnex_segment->m_type = pnex_section->m_type;

						pnex_segment->m_start = pcur_segment->m_end;
						pnex_segment->m_end = ptn_section2->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
						pnex_segment->m_arg = (void *)pbfe_section;

						dlist_initialize_element((dlist_element_t *)pnex_segment);
						dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

						pnex_section = ptn_section2;
					}
				}
			}
#endif

			/* Free all the patterns */
			dlist_map2(&cur_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
			dlist_map2(&nex_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
		}

		pcur_section = pnex_section;
	}

	/* TODO: Process the tail sections !!!! */
	status = dlist_last(pto, (dlist_element_t **)&plst_segment);

	if (plst_segment == NULL) {
		return 0;
	}

	pcur_section = (stock_section_t *)plst_segment->m_arg;
	status = dlist_next(pfrm, (dlist_element_t *)pcur_section, (dlist_element_t **)&pnex_section);
	pcur_section = pnex_section;

	while (!OSA_ISERROR(status) && pcur_section != NULL) {

		dlist_init(&cur_seq.m_slist);
		dlist_init(&cur_seq.m_clist);
		dlist_init(&nex_seq.m_slist);
		dlist_init(&nex_seq.m_clist);

		dlist_next(pfrm, (dlist_element_t *)pcur_section, (dlist_element_t **)&pnex_section);

		if (pnex_section != NULL) {

			cur_seq.m_section = pcur_section;
			nex_seq.m_section = pnex_section;

			/* Map the current section's sequence  */
			dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&cur_seq);

			__ta_candlesticks_included_process(&cur_seq.m_slist, &cur_seq.m_clist);

			__ta_candlesticks_pattern_stats3(pobj, &cur_seq.m_clist, &cur_plist);

			/* Map the current section's sequence  */
			dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&nex_seq);

			__ta_candlesticks_included_process(&nex_seq.m_slist, &nex_seq.m_clist);

			__ta_candlesticks_pattern_stats3(pobj, &nex_seq.m_clist, &nex_plist);

			/* Find the sequence's pattern */
			pcur_pattern =
				__ta_candlesticks_find_pattern_after_id(&cur_plist,
					STOCK_TRENDENCY_TYPE_ADVANCING == cur_seq.m_section->m_type ?
					STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
					cur_seq.m_section->m_id);

			pnex_pattern =
				__ta_candlesticks_find_pattern_after_id(&nex_plist,
					STOCK_TRENDENCY_TYPE_ADVANCING == nex_seq.m_section->m_type ?
					STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
					nex_seq.m_section->m_id);

			if (pcur_pattern != NULL) {
				ptn_section1 = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;
			}
			if (pnex_pattern != NULL) {
				ptn_section2 = (stock_section_t *)pnex_pattern->m_candlesticks->m_arg;
			}

			if (((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id < ptn_section2->m_id))
				||
				(pcur_pattern != NULL && pnex_pattern == NULL)) {

				/*
			     *	Case 1:  A + B + PA + PB.
				 *	Case 2:  A + B + PA + N/A.
				 *
				 *  Segment 1: A ---> PA.
				 */

				/* We find a segment (Yi Duan!!!) (upward or downward) */
				//pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
				if (pcur_segment == NULL) {
					break;
				}

				pcur_segment->m_id = index++;
				pcur_segment->m_type = pcur_section->m_type;
				pcur_segment->m_start = pcur_section->m_start;
				pcur_segment->m_end = ptn_section1->m_start;

				dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
				pcur_segment->m_arg = (void *)pbfe_section;

				dlist_initialize_element((dlist_element_t *)pcur_segment);
				dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

				pnex_section = ptn_section1;

				/*
			 	 *	Modified by: xiong-kaifang.
				 *  Date       : Jan, 20, 2016.
				 *  Description: TODO: Add codes to check the segment2.
				 */
				if (pnex_pattern != NULL) {
					if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
						(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
						(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

						/*
						 *	Segment2: B ---> PB.
						 */
						//pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                        __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
						if (pnex_segment == NULL) {
							break;
						}

						pnex_segment->m_id = index++;
						pnex_segment->m_type = pnex_section->m_type;

						pnex_segment->m_start = pcur_segment->m_end;
						pnex_segment->m_end = ptn_section2->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
						pnex_segment->m_arg = (void *)pbfe_section;

						dlist_initialize_element((dlist_element_t *)pnex_segment);
						dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

						pnex_section = ptn_section2;
					}
				}
			}
			else if (
				((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id > ptn_section2->m_id))
				||
				(pcur_pattern == NULL && pnex_pattern != NULL)) {

				/*
				 *	Case 3: A + B + PB + PA.
				 *  Case 4: A + B + N/A + PB.
				 *
				 *  Segment 1: A.
				 *  Segment 2: B ---> PB.
				 */

				//pcur_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
				if (pcur_segment == NULL) {
					break;
				}

				pcur_segment->m_id = index++;
				pcur_segment->m_type = pcur_section->m_type;

				srange.m_start = pcur_section;
				srange.m_end = ptn_section2;
				srange.m_type = pnex_section->m_type;
				srange.m_max = srange.m_min = NULL;

				dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);

				if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
					ptmp_section = srange.m_max;
				}
				else {
					ptmp_section = srange.m_min;
				}

				pcur_segment->m_start = pcur_section->m_start;
				pcur_segment->m_end = ptmp_section->m_start;

				dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
				pcur_segment->m_arg = (void *)pbfe_section;

				dlist_initialize_element((dlist_element_t *)pcur_segment);
				dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

				if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
					(ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
					(STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
					(ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

					/*
					 *	Segment 2: B ---> PB (upward or downward).
					 */
					//pnex_segment = (stock_segment_t *)malloc(sizeof(stock_segment_t));
                    __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
					if (pnex_segment == NULL) {
						break;
					}

					pnex_segment->m_id = index++;
					pnex_segment->m_type = pnex_section->m_type;

					pnex_segment->m_start = pcur_segment->m_end;
					pnex_segment->m_end = ptn_section2->m_start;

					dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
					pnex_segment->m_arg = (void *)pbfe_section;

					dlist_initialize_element((dlist_element_t *)pnex_segment);
					dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

					pnex_section = ptn_section2;
				}
				else {
					if (pcur_pattern != NULL) {
						/* Update the current segment */
						pcur_segment->m_end = ptn_section1->m_start;

						dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
						pcur_segment->m_arg = (void *)pbfe_section;

						pnex_section = ptn_section1;
					}
				}
			}

			/* Free all the patterns */
			dlist_map2(&cur_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
			dlist_map2(&nex_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
		}

		pcur_section = pnex_section;
	}

	return 0;
}

//#define TA_SEGMENT_IMPROVE
static int __ta_candlesticks_segment_stats_internal(ta_chart_t * pobj, dlist_t * pfrm, dlist_t * pto, ta_section_t * pstart, bool loose)
{
    unsigned int                   index = 0;
    dlist_t                        cur_plist;
    dlist_t                        nex_plist;
    status_t                       status = OSA_SOK;

    ta_candlesticks_t            * pdummy = NULL;
    ta_section_range_t			   srange;
    ta_candlesticks_secseg_t       cur_seq, nex_seq;

    stock_section_t              * pbfe_section = NULL;
    stock_section_t              * pcur_section = NULL;
    stock_section_t              * pnex_section = NULL;
    stock_section_t              * ptn_section1 = NULL;
    stock_section_t              * ptn_section2 = NULL;
    stock_section_t              * ptmp_section = NULL;

    stock_segment_t              * pcur_segment = NULL;
    stock_segment_t              * pnex_segment = NULL;

    stock_candlesticks_pattern_t * pcur_pattern = NULL;
    stock_candlesticks_pattern_t * pnex_pattern = NULL;

    if (pstart == NULL) {
        status = dlist_first(pfrm, (dlist_element_t **)&pcur_section);
    }
    else {
        pcur_section = pstart;
    }

    while (!OSA_ISERROR(status) && pcur_section != NULL) {

        dlist_init(&cur_seq.m_slist);
        dlist_init(&cur_seq.m_clist);
        dlist_init(&nex_seq.m_slist);
        dlist_init(&nex_seq.m_clist);

        dlist_next(pfrm, (dlist_element_t *)pcur_section, (dlist_element_t **)&pnex_section);

        if (pnex_section != NULL) {

            cur_seq.m_section = pcur_section;
            nex_seq.m_section = pnex_section;

            /* Map the current section's sequence  */
            dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&cur_seq);

            __ta_candlesticks_included_process(&cur_seq.m_slist, &cur_seq.m_clist);

            if (loose) {
                __ta_candlesticks_pattern_stats3(pobj, &cur_seq.m_clist, &cur_plist);
            }
            else {
                __ta_candlesticks_pattern_stats2(pobj, &cur_seq.m_clist, &cur_plist);
            }

            /* Map the current section's sequence  */
            dlist_map(pfrm, __ta_candlesticks_sequence_map_fxn, (void *)&nex_seq);

            __ta_candlesticks_included_process(&nex_seq.m_slist, &nex_seq.m_clist);

            if (loose) {
                __ta_candlesticks_pattern_stats3(pobj, &nex_seq.m_clist, &nex_plist);
            }
            else {
                __ta_candlesticks_pattern_stats2(pobj, &nex_seq.m_clist, &nex_plist);
            }

            /* Find the sequence's pattern */
            pcur_pattern =
                __ta_candlesticks_find_pattern_after_id(&cur_plist,
                    STOCK_TRENDENCY_TYPE_ADVANCING == cur_seq.m_section->m_type ?
                    STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
                    cur_seq.m_section->m_id);

            pnex_pattern =
                __ta_candlesticks_find_pattern_after_id(&nex_plist,
                    STOCK_TRENDENCY_TYPE_ADVANCING == nex_seq.m_section->m_type ?
                    STOCK_CANDLESTICKS_PATTERN_TYPE_TOP : STOCK_CANDLESTICKS_PATTERN_TYPE_BOT,
                    nex_seq.m_section->m_id);

            if (pcur_pattern != NULL) {
                ptn_section1 = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;
            }
            if (pnex_pattern != NULL) {
                ptn_section2 = (stock_section_t *)pnex_pattern->m_candlesticks->m_arg;
            }

            if (((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id < ptn_section2->m_id))
                ||
                (pcur_pattern != NULL && pnex_pattern == NULL)) {

                /*
                 *	Case 1:  A + B + PA + PB.
                 *	Case 2:  A + B + PA + N/A.
                 *
                 *  Segment 1: A ---> PA.
                 */

                /* We find a segment (Yi Duan!!!) (upward or downward) */
                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
                if (pcur_segment == NULL) {
                    break;
                }

                pcur_segment->m_id = pobj->m_seg_index++;
                pcur_segment->m_type = pcur_section->m_type;
                pcur_segment->m_start = pcur_section->m_start;
                pcur_segment->m_end = ptn_section1->m_start;

#if defined(TA_SEGMENT_SEARCH)
                srange.m_start = pcur_section;
                srange.m_end = ptn_section1;
                if (pnex_pattern != NULL) {
                    srange.m_end = ptn_section2;
                }
                srange.m_type = pnex_section->m_type;
                srange.m_max = srange.m_min = NULL;

#if defined(TA_SEGMENT_IMPROVE)
                dlist_search_element(&cur_seq.m_clist, (void *)&srange, (dlist_element_t **)&pdummy, __ta_candlesticks_section_search_fxn);
#else
                dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);
#endif

                if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
                    ptmp_section = srange.m_max;
                }
                else {
                    ptmp_section = srange.m_min;
                }

                pcur_segment->m_end = ptmp_section->m_start;

                dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
                pcur_segment->m_arg = (void *)pbfe_section;

                ptn_section1 = ptmp_section;
#else
                dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
                pcur_segment->m_arg = (void *)pbfe_section;
#endif

                dlist_initialize_element((dlist_element_t *)pcur_segment);
                dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

                pnex_section = ptn_section1;

                /*
                 *	Modified by: xiong-kaifang.
                 *  Date       : Jan, 20, 2016.
                 *  Description: TODO: Add codes to check the segment2.
                 */
                if (pnex_pattern != NULL) {
                    if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
                        (ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
                        (STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
                        (ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

                        /*
                         *	Segment2: B ---> PB.
                         */
                        __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
                        if (pnex_segment == NULL) {
                            break;
                        }

                        pnex_segment->m_id = pobj->m_seg_index++;
                        pnex_segment->m_type = pnex_section->m_type;

                        pnex_segment->m_start = pcur_segment->m_end;
                        pnex_segment->m_end = ptn_section2->m_start;

#if defined(TA_SEGMENT_SEARCH)
                        srange.m_start = ptmp_section;
                        srange.m_end = ptn_section2;
                        srange.m_type = pcur_section->m_type;
                        srange.m_max = srange.m_min = NULL;

#if defined(TA_SEGMENT_IMPROVE)
                        dlist_search_element(&nex_seq.m_clist, (void *)&srange, (dlist_element_t **)&pdummy, __ta_candlesticks_section_search_fxn);
#else
                        dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);
#endif
                        
                        if (STOCK_TRENDENCY_TYPE_ADVANCING == pnex_segment->m_type) {
                            ptmp_section = srange.m_max;
                        }
                        else {
                            ptmp_section = srange.m_min;
                        }

                        pnex_segment->m_end = ptmp_section->m_start;

                        dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
                        pnex_segment->m_arg = (void *)pbfe_section;

                        ptn_section2 = ptmp_section;
#else
                        dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
                        pnex_segment->m_arg = (void *)pbfe_section;
#endif

                        dlist_initialize_element((dlist_element_t *)pnex_segment);
                        dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

                        pnex_section = ptn_section2;
                    }
                }
            }
            else if (
                ((pcur_pattern != NULL && pnex_pattern != NULL) && (ptn_section1->m_id > ptn_section2->m_id))
                ||
                (pcur_pattern == NULL && pnex_pattern != NULL)) {

                /*
                 *	Case 3: A + B + PB + PA.
                 *  Case 4: A + B + N/A + PB.
                 *
                 *  Segment 1: A.
                 *  Segment 2: B ---> PB.
                 */

                __ta_candlesticks_node_new(pobj, (void **)&pcur_segment);
                if (pcur_segment == NULL) {
                    break;
                }

                pcur_segment->m_id = pobj->m_seg_index++;
                pcur_segment->m_type = pcur_section->m_type;

                srange.m_start = pcur_section;
                srange.m_end = ptn_section2;
                srange.m_type = pnex_section->m_type;
                srange.m_max = srange.m_min = NULL;

#if defined(TA_SEGMENT_IMPROVE)
                dlist_search_element(&cur_seq.m_clist, (void *)&srange, (dlist_element_t **)&pdummy, __ta_candlesticks_section_search_fxn);
#else
                dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);
#endif

                if (STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) {
                    ptmp_section = srange.m_max;
                }
                else {
                    ptmp_section = srange.m_min;
                }

                pcur_segment->m_start = pcur_section->m_start;
                pcur_segment->m_end = ptmp_section->m_start;

                dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
                pcur_segment->m_arg = (void *)pbfe_section;

                dlist_initialize_element((dlist_element_t *)pcur_segment);
                dlist_put_tail(pto, (dlist_element_t *)pcur_segment);

                pnex_section = ptmp_section;

                if ((STOCK_TRENDENCY_TYPE_ADVANCING == pcur_segment->m_type) &&
                    (ptn_section2->m_start->m_low < pcur_segment->m_end->m_high) ||
                    (STOCK_TRENDENCY_TYPE_DECLINE == pcur_segment->m_type) &&
                    (ptn_section2->m_start->m_high > pcur_segment->m_end->m_low)) {

                    /*
                     *	Segment 2: B ---> PB (upward or downward).
                     */
                    __ta_candlesticks_node_new(pobj, (void **)&pnex_segment);
                    if (pnex_segment == NULL) {
                        break;
                    }

                    pnex_segment->m_id = pobj->m_seg_index++;
                    pnex_segment->m_type = pnex_section->m_type;

                    pnex_segment->m_start = pcur_segment->m_end;
                    pnex_segment->m_end = ptn_section2->m_start;

#if defined(TA_SEGMENT_SEARCH)
                    srange.m_start = ptmp_section;
                    srange.m_end = ptn_section2;
                    srange.m_type = pcur_section->m_type;
                    srange.m_max = srange.m_min = NULL;

#if defined(TA_SEGMENT_IMPROVE)
                    dlist_search_element(&nex_seq.m_clist, (void *)&srange, (dlist_element_t **)&pdummy, __ta_candlesticks_section_search_fxn);
#else
                    dlist_map(pfrm, __ta_candlesticks_section_match_fxn, (void *)&srange);
#endif

                    if (STOCK_TRENDENCY_TYPE_ADVANCING == pnex_segment->m_type) {
                        ptmp_section = srange.m_max;
                    }
                    else {
                        ptmp_section = srange.m_min;
                    }

                    pnex_segment->m_end = ptmp_section->m_start;

                    dlist_prev(pfrm, (dlist_element_t *)ptmp_section, (dlist_element_t **)&pbfe_section);
                    pnex_segment->m_arg = (void *)pbfe_section;

                    ptn_section2 = ptmp_section;
#else
                    dlist_prev(pfrm, (dlist_element_t *)ptn_section2, (dlist_element_t **)&pbfe_section);
                    pnex_segment->m_arg = (void *)pbfe_section;
#endif

                    dlist_initialize_element((dlist_element_t *)pnex_segment);
                    dlist_put_tail(pto, (dlist_element_t *)pnex_segment);

                    pnex_section = ptn_section2;
                }
                else {
#if 0
                    /*
                     *  TODO  : Maybe we should process this case.
                     *  Case 3: A + B.
                     */
                    if (pcur_pattern != NULL) {
                        /* Update the current segment */
                        pcur_segment->m_end = ptn_section1->m_start;

                        dlist_prev(pfrm, (dlist_element_t *)ptn_section1, (dlist_element_t **)&pbfe_section);
                        pcur_segment->m_arg = (void *)pbfe_section;

                        pnex_section = ptn_section1;
                    }
#endif
                }
            }

            /* Free all the patterns */
            dlist_map2(&cur_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
            dlist_map2(&nex_plist, __ta_candlesticks_node_free_fxn, (void *)pobj);
        }

        pcur_section = pnex_section;
    }

    return 0;
}

static int __ta_candlesticks_sequence_map_fxn(dlist_element_t * elem, void * data)
{
	ta_candlesticks_secseg_t * pseq = (ta_candlesticks_secseg_t *)data;
	stock_section_t          * psection = (stock_section_t *)elem;

	if ((psection->m_type != pseq->m_section->m_type) &&
		(psection->m_id >= pseq->m_section->m_id)) {

		if (STOCK_TRENDENCY_TYPE_ADVANCING == psection->m_type) {
			psection->m_sticks.m_high = psection->m_end->m_high;
			psection->m_sticks.m_low  = psection->m_start->m_low;
		}
		else {
			psection->m_sticks.m_high = psection->m_start->m_high;
			psection->m_sticks.m_low  = psection->m_end->m_low;
		}
		
		psection->m_sticks.m_arg = (void *)psection;
		dlist_initialize_element((dlist_element_t *)&psection->m_sticks);
		dlist_put_tail(&pseq->m_slist, (dlist_element_t *)&psection->m_sticks);
	}

	return 0;
}

static int __ta_candlesticks_section_map_fxn1(dlist_element_t * elem, void * data)
{
	ta_candlesticks_secseg_t * pseg = (ta_candlesticks_secseg_t *)data;
	stock_section_t          * psection = (stock_section_t *)elem;

	if (STOCK_TRENDENCY_TYPE_DECLINE == psection->m_type && psection->m_id > pseg->m_section->m_id) {
		psection->m_sticks.m_high = psection->m_start->m_high;
		psection->m_sticks.m_low = psection->m_end->m_low;
		psection->m_sticks.m_arg = (void *)psection;
		dlist_initialize_element((dlist_element_t *)&psection->m_sticks);
		dlist_put_tail(&pseg->m_slist, (dlist_element_t *)&psection->m_sticks);
	}

	return 0;
}

static int __ta_candlesticks_section_map_fxn2(dlist_element_t * elem, void * data)
{
	ta_candlesticks_secseg_t * pseg = (ta_candlesticks_secseg_t *)data;
	stock_section_t          * psection = (stock_section_t *)elem;

	if (STOCK_TRENDENCY_TYPE_ADVANCING == psection->m_type && psection->m_id > pseg->m_section->m_id) {
		psection->m_sticks.m_high = psection->m_end->m_high;
		psection->m_sticks.m_low = psection->m_start->m_low;
		psection->m_sticks.m_arg = (void *)psection;
		dlist_initialize_element((dlist_element_t *)&psection->m_sticks);
		dlist_put_tail(&pseg->m_slist, (dlist_element_t *)&psection->m_sticks);
	}

	return 0;
}

static int __ta_candlesticks_section_map_fxn3(dlist_element_t * elem, void * data)
{
	ta_candlesticks_secseg_t * pseg = (ta_candlesticks_secseg_t *)data;
	stock_section_t          * psection = (stock_section_t *)elem;

	if (STOCK_TRENDENCY_TYPE_DECLINE == psection->m_type && psection->m_id >= pseg->m_section->m_id) {
		psection->m_sticks.m_high = psection->m_start->m_high;
		psection->m_sticks.m_low = psection->m_end->m_low;
		psection->m_sticks.m_arg = (void *)psection;
		dlist_initialize_element((dlist_element_t *)&psection->m_sticks);
		dlist_put_tail(&pseg->m_slist, (dlist_element_t *)&psection->m_sticks);
	}

	return 0;
}

static int __ta_candlesticks_section_map_fxn4(dlist_element_t * elem, void * data)
{
	ta_candlesticks_secseg_t * pseg = (ta_candlesticks_secseg_t *)data;
	stock_section_t          * psection = (stock_section_t *)elem;

	if (STOCK_TRENDENCY_TYPE_ADVANCING == psection->m_type && psection->m_id >= pseg->m_section->m_id) {
		psection->m_sticks.m_high = psection->m_end->m_high;
		psection->m_sticks.m_low = psection->m_start->m_low;
		psection->m_sticks.m_arg = (void *)psection;
		dlist_initialize_element((dlist_element_t *)&psection->m_sticks);
		dlist_put_tail(&pseg->m_slist, (dlist_element_t *)&psection->m_sticks);
	}

	return 0;
}

static stock_candlesticks_pattern_t *
__ta_candlesticks_find_pattern_after_id(dlist_t * plist, int ptype, unsigned int id)
{
	status_t                       status       = OSA_SOK;
	stock_section_t              * psection     = NULL;
	stock_candlesticks_pattern_t * pcur_pattern = NULL;
	stock_candlesticks_pattern_t * pnex_pattern = NULL;

	status = dlist_first(plist, (dlist_element_t **)&pcur_pattern);
	while (!OSA_ISERROR(status) && pcur_pattern != NULL) {
#if 0
		psection = (stock_section_t *)pcur_pattern->m_candlesticks->m_arg;

		if ((pcur_pattern->m_type == ptype) && (psection->m_id > id))
			break;
#else
		if (pcur_pattern->m_type == ptype)
			break;
#endif

		status = dlist_next(plist, (dlist_element_t *)pcur_pattern, (dlist_element_t **)&pnex_pattern);
		pcur_pattern = pnex_pattern;
	}

	return pcur_pattern;
}

static int __ta_candlesticks_node_free_fxn(dlist_element_t * elem, void * data)
{
    ta_chart_t * pobj = (ta_chart_t *)data;
    return __ta_candlesticks_node_free(pobj, (void *)elem);
}

static int __ta_candlesticks_segment_map_fxn(dlist_element_t * elem, void * data)
{
	float           * pfOut    = (float *)data;
	stock_segment_t * psegment = (stock_segment_t *)elem;

	if (STOCK_TRENDENCY_TYPE_ADVANCING == psegment->m_type) {
		pfOut[psegment->m_start->m_id] = -1.0;
		pfOut[psegment->m_end->m_id]   = 1.0;
	}

	if (STOCK_TRENDENCY_TYPE_DECLINE == psegment->m_type) {
		pfOut[psegment->m_start->m_id] = 1.0;
		pfOut[psegment->m_end->m_id]   = -1.0;
	}

	return 0;
}

static int __ta_candlesticks_section_match_fxn(dlist_element_t * elem, void * data)
{
	ta_section_range_t        * prange       = (ta_section_range_t *)data;
	stock_section_t           * pcur_section = (stock_section_t *)elem;

	if (pcur_section->m_id > prange->m_start->m_id && pcur_section->m_id <= prange->m_end->m_id) {
		if (STOCK_TRENDENCY_TYPE_ADVANCING == prange->m_type) {
			if (prange->m_min == NULL) {
				prange->m_min = pcur_section;
			}
			else {
				if (prange->m_min->m_start->m_low > pcur_section->m_start->m_low)
					prange->m_min = pcur_section;
			}
		}
		else {
			if (prange->m_max == NULL) {
				prange->m_max = pcur_section;
			}
			else {
				if (prange->m_max->m_start->m_high < pcur_section->m_start->m_high)
					prange->m_max = pcur_section;
			}
		}
	}

	return 0;
}

static bool __ta_candlesticks_section_search_fxn(dlist_element_t * elem, void * data)
{
    bool                 matched      = false;
    ta_section_range_t * prange       = (ta_section_range_t *)data;
    stock_section_t    * pcur_section = (ta_section_t *)(((ta_candlesticks_t *)elem)->m_arg);

    if (STOCK_TRENDENCY_TYPE_ADVANCING == prange->m_type) {
        if (prange->m_min == NULL) {
            prange->m_min = pcur_section;
        }
        else {
            if (prange->m_min->m_start->m_low > pcur_section->m_start->m_low)
                prange->m_min = pcur_section;
        }
    }
    else {
        if (prange->m_max == NULL) {
            prange->m_max = pcur_section;
        }
        else {
            if (prange->m_max->m_start->m_high < pcur_section->m_start->m_high)
                prange->m_max = pcur_section;
        }
    }

    if (pcur_section->m_id >= prange->m_end->m_id) {
        matched = true;
    }

    return matched;
}

static status_t __ta_candlesticks_node_new(ta_chart_t * pobj, void ** ppnode)
{
    status_t          status = OSA_SOK;
    ta_chart_node_t * pnode  = NULL;

    if (!dlist_is_empty(&pobj->m_node_list)) {
        status = dlist_get_head(&pobj->m_node_list, (dlist_element_t **)&pnode);
    }
    else {
        pnode = (ta_chart_node_t *)malloc(sizeof(ta_chart_node_t));
    }

    (*ppnode) = pnode;

    return status;
}

static status_t __ta_candlesticks_node_free(ta_chart_t * pobj, void * pnode)
{
    dlist_initialize_element((dlist_element_t *)pnode);
    return dlist_put_tail(&pobj->m_node_list, (dlist_element_t *)pnode);
}

#if defined(__cplusplus)
}
#endif
