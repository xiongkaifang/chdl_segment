#pragma once
/** ============================================================================
*
*  Copyright (C), 1987 - 2015, xiong-kaifang Tech. Co, Ltd.
*
*  @File Name:	osa_status.h
*
*  @Author: xiong-kaifang   Version: v1.0   Date: 2013-04-07
*
*  @Description:   // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
*                  // �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
*                  // �ơ�˳�򡢶����������ȹ�ϵ
*                  //
*
*                  The header file for osa status. This file contains several
*                  types of status code and related routines to get the
*                  description of each status code.
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
*  xiong-kaifang   2013-04-07     v1.0	        Write this module.
*
*  ============================================================================
*/

#if !defined (__OSA_STATUS_H)
#define __OSA_STATUS_H

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
#define OSA_STATUS_CLASS_GENERAL    (0x100000)
#define OSA_STATUS_CLASS_NETWORK    (0x200000)
#define OSA_STATUS_CLASS_IO         (0x400000)
#define OSA_STATUS_CLASS_APP        (0x800000)

#define OSA_STATUS_TYPE_SUCCESS     (0x000000)
#define OSA_STATUS_TYPE_INFO        (0x010000)
#define OSA_STATUS_TYPE_WARNING     (0x020000)
#define OSA_STATUS_TYPE_ERROR       (0x040000)
#define OSA_STATUS_TYPE_FATAL       (0x080000)

#define OSA_STATUS_FLAG_COUNT       (0x001000)

#ifdef  OSA_SOK
#undef  OSA_SOK
#endif

#ifdef  OSA_EFAIL
#undef  OSA_EFAIL
#endif

#define OSA_SOK                     (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_SUCCESS|0|100)
#define OSA_EFAIL                   (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|101)
#define OSA_EMEM                    (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|102)
#define OSA_ENOENT                  (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|103)
#define OSA_EARGS                   (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|104)
#define OSA_EINVAL                  (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|105)
#define OSA_EEXIST                  (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|106)
#define OSA_ERES                    (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|107)
#define OSA_EPERM                   (OSA_STATUS_CLASS_GENERAL|OSA_STATUS_TYPE_ERROR|0|108)
#define OSA_ECONNECT                (OSA_STATUS_CLASS_NETWORK|OSA_STATUS_TYPE_ERROR|0|200)
#define OSA_ETIMEOUT                (OSA_STATUS_CLASS_IO|OSA_STATUS_TYPE_ERROR|0|300)
#define OSA_EEOF                    (OSA_STATUS_CLASS_IO|OSA_STATUS_TYPE_WARNING|0|301)
#define OSA_ENOTIPL                 (OSA_STATUS_CLASS_APP|OSA_STATUS_TYPE_WARNING|0|600)
#define OSA_EBADCMD                 (OSA_STATUS_CLASS_APP|OSA_STATUS_TYPE_ERROR|0|601)

#ifdef  OSA_ISERROR
#undef  OSA_ISERROR
#endif
#define OSA_ISERROR(status)         (status != (OSA_SOK))

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
	typedef int status_t;

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

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif  /* if !defined (__OSA_STATUS_H) */