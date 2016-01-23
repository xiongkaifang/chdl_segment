// FBFD.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "TCalcFuncSets.h"
#include "chdl.h"

//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�

void TestPlugin1(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{
	for (int i = 0; i < DataLen; i++)
		pfOUT[i] = pfINb[i];
}

void FBFD_Plugin1(int DataLen, float *pfOut, float *pfINa, float *pfINb, float *pfINc)
{
	ta_chdl_section((unsigned int)DataLen, pfOut, pfINa, pfINb, pfINc);
}

void FBFD_Plugin2(int DataLen, float *pfOut, float *pfINa, float *pfINb, float *pfINc)
{
	ta_chdl_segment((unsigned int)DataLen, pfOut, pfINa, pfINb, pfINc);
}

//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] =
{
	{ 1, (pPluginFUNC)&FBFD_Plugin1 },
	{ 2, (pPluginFUNC)&FBFD_Plugin2 },
	{ 0, NULL }
};

//������TCalc��ע�ắ��
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if (*pFun == NULL) {
		(*pFun) = g_CalcFuncSets;
		return TRUE;
	}

	return FALSE;
}
