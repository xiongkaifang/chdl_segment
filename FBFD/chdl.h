#pragma once
/** ============================================================================
*
*  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co, Ltd.
*
*  @File Name:	chdl.h
*
*  @Author: xiong-kaifang   Version: v1.0   Date: 2016-01-08
*
*  @Description:   // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
*                  // �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
*                  // �ơ�˳�򡢶����������ȹ�ϵ
*                  //
*
*                  The format for header file.
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
*  xiong-kaifang   2016-01-08     v1.0	        Write this module.
*
*  ============================================================================
*/

#if !defined (__STOCK_CHDL_H)
#define __STOCK_CHDL_H

/*  --------------------- Include system headers ---------------------------- */

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

	/*
	*  --------------------- Public function declaration --------------------------
	*/

	/** =============================================================================
	*
	*  @Function:      __chdl_fbfd
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
	void ta_chdl_section(unsigned int data_len, float *pOut, float *pINa, float *pINb, float *pINc);

	void ta_chdl_segment(unsigned int data_len, float *pOut, float *pINa, float *pINb, float *pINc);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif  /* if !defined ((__STOCK_CHDL_H) */