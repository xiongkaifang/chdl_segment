#pragma once
/** ============================================================================
*
*  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co, Ltd.
*
*  @File Name:	dlist.h
*
*  @Author: xiong-kaifang   Version: v1.0   Date: 2012-09-14
*
*  @Description:   // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
*                  // �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
*                  // �ơ�˳�򡢶����������ȹ�ϵ
*                  //
*
*                  The header file for double link list.
*
*  @Others:        //	��������˵��
*
*  @Function List: //	��Ҫ�����б�ÿ����¼�Ͱ��������������ܼ�Ҫ˵��
*      1.  ...
*      2.  ...
*
*  @History:       // �޸���ʷ��¼�б�ÿ���޸ļ�¼�Ͱ����޸����ڡ��޸�
*                  // ʱ�估�޸����ݼ���
*
*  <author>        <time>       <version>      <description>
*
*  xiong-kaifang   2012-09-14     v1.0	        Write this module.
*
*  xiong-kaifang   2015-08-21     V1.1         Add macro
*                                              'DLIST_ELEMENT_RESERVED'.
*
*  xiont-kaifang   2015-09-16     v1.2         Add two routines:
*                                              dlist_prev
*                                              dlist_map2
*
*  ============================================================================
*/

#if !defined (__OSA_DLIST_H)
#define __OSA_DLIST_H

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
	struct __dlist_element_t; typedef struct __dlist_element_t dlist_element_t;
	struct __dlist_element_t {
		struct __dlist_element_t * next;
		struct __dlist_element_t * prev;
	};

	struct __dlist_t; typedef struct __dlist_t dlist_t;
	struct __dlist_t {
		dlist_element_t head;
	};

	typedef bool(*DLIST_MATCH_FXN)(dlist_element_t * elem, void * data);

	typedef int(*DLIST_APPLY_FXN)(dlist_element_t * elem, void * data);

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
	int  dlist_init(dlist_t * list);

	int  dlist_is_empty(dlist_t * list);

	int  dlist_initialize_element(dlist_element_t * element);

	int  dlist_insert_before(dlist_t *          list,
		dlist_element_t *  insert_element,
		dlist_element_t *  existing_element);

	int  dlist_put_tail(dlist_t * list, dlist_element_t * element);

	int  dlist_remove_element(dlist_t * list, dlist_element_t * element);

	int  dlist_first(dlist_t * list, dlist_element_t ** element);

	int  dlist_last(dlist_t * list, dlist_element_t ** element);

	int  dlist_get_head(dlist_t * list, dlist_element_t ** head_element);

	int  dlist_next(dlist_t *          list,
		dlist_element_t *  current_element,
		dlist_element_t ** next_element);

	int  dlist_prev(dlist_t *          list,
		dlist_element_t *  current_element,
		dlist_element_t ** prev_element);

	int  dlist_search_element(dlist_t *          list,
		void    *          data,
		dlist_element_t ** elem,
		DLIST_MATCH_FXN    match_fxn);

	int dlist_map(dlist_t * list, DLIST_APPLY_FXN apply_fxn, void * data);

	int dlist_map2(dlist_t * list, DLIST_APPLY_FXN apply_fxn, void * data);

	int dlist_count(dlist_t * list, unsigned int * count);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif  /* if !defined (__OSA_DLIST_H) */