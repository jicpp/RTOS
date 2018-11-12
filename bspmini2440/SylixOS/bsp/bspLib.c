/*********************************************************************************************************
**
**                                    �й�������Դ��֯
**
**                                   Ƕ��ʽʵʱ����ϵͳ
**
**                                SylixOS(TM)  LW : long wing
**
**                               Copyright All Rights Reserved
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**
** ��   ��   ��: bspLib.c
**
** ��   ��   ��: Han.Hui (����)
**
** �ļ���������: 2007 �� 12 �� 09 ��
**
** ��        ��: S3C2440 ��ҪΪ SylixOS �ṩ�Ĺ���֧��.
*********************************************************************************************************/
#define  __SYLIXOS_KERNEL
#include "config.h"
#include "SylixOS.h"
#include "driver/timer/timer.h"
#include "driver/tty/uart.h"
/*********************************************************************************************************
  BSP ��Ϣ
*********************************************************************************************************/
static const char   _G_pcCpuInfo[]     = "SAMSUNG S3C2440A (ARM920T 405/101MHz NonFPU)";
static const char   _G_pcCacheInfo[]   = "32KBytes L1-Cache (D-16K/I-16K)";
static const char   _G_pcPacketInfo[]  = "Mini2440 Packet";
static const char   _G_pcVersionInfo[] = "BSP version 5.1.2 for "__SYLIXOS_RELSTR;
/*********************************************************************************************************
  �ж����
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspIntInit
** ��������: �ж�ϵͳ��ʼ��
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspIntInit (VOID)
{
    API_InterVectorSetFlag(LW_IRQ_4,  LW_IRQ_FLAG_QUEUE);               /*  EINT 4 ~ 7                  */
    API_InterVectorSetFlag(LW_IRQ_5,  LW_IRQ_FLAG_QUEUE);               /*  EINT 8 ~ 23                 */
    API_InterVectorSetFlag(LW_IRQ_0,  LW_IRQ_FLAG_SAMPLE_RAND);         /*  EINT 0 used to sample random*/
}
/*********************************************************************************************************
** ��������: bspIntHandle
** ��������: �ж����
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspIntHandle (VOID)
{
    REGISTER UINT32   uiIrqVic = rINTOFFSET;

    archIntHandle((ULONG)uiIrqVic, LW_FALSE);
}
/*********************************************************************************************************
** ��������: bspIntVectorEnable
** ��������: ʹ��ָ�����ж�����
** ��  ��  : ulVector     �ж�����
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspIntVectorEnable (ULONG  ulVector)
{
    INTER_CLR_MSK((1u << ulVector));
}
/*********************************************************************************************************
** ��������: bspIntVectorDisable
** ��������: ����ָ�����ж�����
** ��  ��  : ulVector     �ж�����
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspIntVectorDisable (ULONG  ulVector)
{
    INTER_SET_MSK((1u << ulVector));
}
/*********************************************************************************************************
** ��������: bspIntVectorIsEnable
** ��������: ���ָ�����ж������Ƿ�ʹ��
** ��  ��  : ulVector     �ж�����
** ��  ��  : LW_FALSE �� LW_TRUE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
BOOL  bspIntVectorIsEnable (ULONG  ulVector)
{
    return  (INTER_GET_MSK((1u << ulVector)) ? LW_FALSE : LW_TRUE);
}
/*********************************************************************************************************
** ��������: bspIntVectorSetPriority
** ��������: ����ָ�����ж����������ȼ�
** ��  ��  : ulVector     �ж�������
**           uiPrio       ���ȼ�
** �䡡��  : ERROR CODE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
#if LW_CFG_INTER_PRIO > 0

ULONG   bspIntVectorSetPriority (ULONG  ulVector, UINT  uiPrio)
{
    return  (ERROR_NONE);
}
/*********************************************************************************************************
** ��������: bspIntVectorGetPriority
** ��������: ��ȡָ�����ж����������ȼ�
** ��  ��  : ulVector     �ж�������
**           puiPrio      ���ȼ�
** �䡡��  : ERROR CODE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
ULONG   bspIntVectorGetPriority (ULONG  ulVector, UINT  *puiPrio)
{
    *puiPrio = 0;
    return  (ERROR_NONE);
}

#endif                                                                  /*  LW_CFG_INTER_PRIO > 0       */
/*********************************************************************************************************
** ��������: bspIntVectorSetTarget
** ��������: ����ָ�����ж�������Ŀ�� CPU
** �䡡��  : ulVector      �ж�������
**           stSize        CPU ���뼯�ڴ��С
**           pcpuset       CPU ����
** �䡡��  : ERROR CODE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
#if LW_CFG_INTER_TARGET > 0

ULONG   bspIntVectorSetTarget (ULONG  ulVector, size_t  stSize, const PLW_CLASS_CPUSET  pcpuset)
{
    return  (ERROR_NONE);
}
/*********************************************************************************************************
** ��������: bspIntVectorGetTarget
** ��������: ��ȡָ�����ж�������Ŀ�� CPU
** �䡡��  : ulVector      �ж�������
**           stSize        CPU ���뼯�ڴ��С
**           pcpuset       CPU ����
** �䡡��  : ERROR CODE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
ULONG   bspIntVectorGetTarget (ULONG  ulVector, size_t  stSize, PLW_CLASS_CPUSET  pcpuset)
{
    LW_CPU_ZERO(pcpuset);
    LW_CPU_SET(0, pcpuset);
    return  (ERROR_NONE);
}

#endif                                                                  /*  LW_CFG_INTER_TARGET > 0     */
/*********************************************************************************************************
  BSP ��Ϣ
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspInfoCpu
** ��������: BSP CPU ��Ϣ
** �䡡��  : NONE
** �䡡��  : CPU ��Ϣ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
CPCHAR  bspInfoCpu (VOID)
{
    return  (_G_pcCpuInfo);
}
/*********************************************************************************************************
** ��������: bspInfoCache
** ��������: BSP CACHE ��Ϣ
** �䡡��  : NONE
** �䡡��  : CACHE ��Ϣ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
CPCHAR  bspInfoCache (VOID)
{
    return  (_G_pcCacheInfo);
}
/*********************************************************************************************************
** ��������: bspInfoPacket
** ��������: BSP PACKET ��Ϣ
** �䡡��  : NONE
** �䡡��  : PACKET ��Ϣ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
CPCHAR  bspInfoPacket (VOID)
{
    return  (_G_pcPacketInfo);
}
/*********************************************************************************************************
** ��������: bspInfoVersion
** ��������: BSP VERSION ��Ϣ
** �䡡��  : NONE
** �䡡��  : BSP VERSION ��Ϣ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
CPCHAR  bspInfoVersion (VOID)
{
    return  (_G_pcVersionInfo);
}
/*********************************************************************************************************
** ��������: bspInfoHwcap
** ��������: BSP Ӳ������
** �䡡��  : NONE
** �䡡��  : Ӳ������ (���֧��Ӳ����, ���Լ��� HWCAP_VFP , HWCAP_VFPv3 , HWCAP_VFPv3D16 , HWCAP_NEON)
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
ULONG  bspInfoHwcap (VOID)
{
    return  (0ul);
}
/*********************************************************************************************************
** ��������: bspInfoRomBase
** ��������: BSP ROM ����ַ
** �䡡��  : NONE
** �䡡��  : ROM ����ַ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
addr_t bspInfoRomBase (VOID)
{
    return  (0x00000000);
}
/*********************************************************************************************************
** ��������: bspInfoRomSize
** ��������: BSP ROM ��С
** �䡡��  : NONE
** �䡡��  : ROM ��С
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
size_t bspInfoRomSize (VOID)
{
    return  (1024 * 1024 * 2);
}
/*********************************************************************************************************
** ��������: bspInfoRamBase
** ��������: BSP RAM ����ַ
** �䡡��  : NONE
** �䡡��  : RAM ����ַ
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
addr_t bspInfoRamBase (VOID)
{
    return  (0x30000000);
}
/*********************************************************************************************************
** ��������: bspInfoRamSize
** ��������: BSP RAM ��С
** �䡡��  : NONE
** �䡡��  : RAM ��С
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
size_t bspInfoRamSize (VOID)
{
    return  (1024 * 1024 * 64);
}
/*********************************************************************************************************
  BSP HOOK
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspTaskCreateHook
** ��������: ���񴴽� hook
** ��  ��  : ulId     ���� ID
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTaskCreateHook (LW_OBJECT_ID  ulId)
{
    (VOID)ulId;
}
/*********************************************************************************************************
** ��������: bspTaskDeleteHook
** ��������: ����ɾ�� hook
** ��  ��  : ulId         ���� ID
**           pvReturnVal  ����ֵ
**           ptcb         ������ƿ�
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTaskDeleteHook (LW_OBJECT_ID  ulId, PVOID  pvReturnVal, PLW_CLASS_TCB  ptcb)
{
    (VOID)ulId;
    (VOID)pvReturnVal;
    (VOID)ptcb;
}
/*********************************************************************************************************
** ��������: bspTaskSwapHook
** ��������: �����л� hook
** ��  ��  : hOldThread       ������������
**           hNewThread       Ҫ���е�����
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTaskSwapHook (LW_OBJECT_HANDLE   hOldThread, LW_OBJECT_HANDLE   hNewThread)
{
    (VOID)hOldThread;
    (VOID)hNewThread;
}
/*********************************************************************************************************
** ��������: bspTaskIdleHook
** ��������: idle ������ô˺���
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTaskIdleHook (VOID)
{
}
/*********************************************************************************************************
** ��������: bspTaskIdleHook
** ��������: ÿ������ϵͳʱ�ӽ��ģ�ϵͳ�������������
** ��  ��  : i64Tick      ϵͳ��ǰʱ��
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTickHook (INT64   i64Tick)
{
    (VOID)i64Tick;
}
/*********************************************************************************************************
** ��������: bspWdTimerHook
** ��������: ���Ź���ʱ����ʱ��ʱ��������������
** ��  ��  : ulId     ���� ID
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspWdTimerHook (LW_OBJECT_ID  ulId)
{
    (VOID)ulId;
}
/*********************************************************************************************************
** ��������: bspTCBInitHook
** ��������: ��ʼ�� TCB ʱ������������
** ��  ��  : ulId     ���� ID
**           ptcb     ������ƿ�
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTCBInitHook (LW_OBJECT_ID  ulId, PLW_CLASS_TCB   ptcb)
{
    (VOID)ulId;
    (VOID)ptcb;
}
/*********************************************************************************************************
** ��������: bspKernelInitHook
** ��������: ϵͳ��ʼ�����ʱ������������
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspKernelInitHook (VOID)
{
}
/*********************************************************************************************************
** ��������: bspReboot
** ��������: ϵͳ��������
** �䡡��  : iRebootType       ��������
**           ulStartAddress    ������ʼ��ַ
** �䡡��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspReboot (INT  iRebootType, addr_t  ulStartAddress)
{
    (VOID)ulStartAddress;

#ifdef __BOOT_INRAM
    ((VOID (*)(INT))bspInfoRamBase())(iRebootType);
#else
    ((VOID (*)(INT))bspInfoRomBase())(iRebootType);
#endif                                                                  /*  __BOOT_INRAM                */
}
/*********************************************************************************************************
** ��������: bspDebugMsg
** ��������: ��ӡϵͳ������Ϣ
** �䡡��  : pcMsg     ��Ϣ
** �䡡��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspDebugMsg (CPCHAR  pcMsg)
{
    uartSendString(COM0, (PCHAR)pcMsg);
}
/*********************************************************************************************************
  CACHE ��ؽӿ�
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspL2CBase
** ��������: ��� L2 ����������ַ
** ��  ��  : pulBase      ���صĻ���ַ
** ��  ��  : -1 ��ʾ������ L2
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
INT  bspL2CBase (addr_t  *pulBase)
{
    return  (PX_ERROR);
}
/*********************************************************************************************************
** ��������: bspL2CAux
** ��������: ��� L2 ������ Aux ��������
** ��  ��  : puiAuxVal      Aux �Ĵ���ֵ
**           puiAuxMask     Aux ��������
** ��  ��  : -1 ��ʾ������ L2
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
INT  bspL2CAux (UINT32  *puiAuxVal, UINT32  *puiAuxMask)
{
    *puiAuxVal  =  0u;
    *puiAuxMask = ~0u;
    
    return  (ERROR_NONE);
}
/*********************************************************************************************************
  MMU ��ؽӿ�
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspMmuPgdMaxNum
** ��������: ��� PGD �ص�����
** ��  ��  : NONE
** ��  ��  : PGD �ص����� (1 ���ؿ�ӳ�� 4GB �ռ�, �Ƽ����� 1)
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
ULONG  bspMmuPgdMaxNum (VOID)
{
    return  (1);
}
/*********************************************************************************************************
** ��������: bspMmuPgdMaxNum
** ��������: ��� PTE �ص�����
** ��  ��  : NONE
** ��  ��  : PTE �ص����� (ӳ�� 4GB �ռ�, ��Ҫ 4096 �� PTE ��)
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
ULONG  bspMmuPteMaxNum (VOID)
{
    return  (2048);
}
/*********************************************************************************************************
  ����ϵͳ��˽ӿ�
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspMpInt
** ��������: ����һ���˼��ж�
** ��  ��  : ulCPUId      Ŀ�� CPU
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID   bspMpInt (ULONG  ulCPUId)
{
    (VOID)ulCPUId;
}
/*********************************************************************************************************
** ��������: bspCpuUp
** ��������: ����һ�� CPU
** ��  ��  : ulCPUId      Ŀ�� CPU
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID   bspCpuUp (ULONG  ulCPUId)
{
    bspDebugMsg("bspCpuUp() error: this cpu CAN NOT support this operate!\r\n");
}
/*********************************************************************************************************
** ��������: bspCpuDown
** ��������: ֹͣһ�� CPU
** ��  ��  : ulCPUId      Ŀ�� CPU
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID   bspCpuDown (ULONG  ulCPUId)
{
    bspDebugMsg("bspCpuDown() error: this cpu CAN NOT support this operate!\r\n");
}
/*********************************************************************************************************
  ����ϵͳ CPU �ٶȿ��ƽӿ�
*********************************************************************************************************/
/*********************************************************************************************************
** ��������: bspSuspend
** ��������: ϵͳ��������״̬
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID    bspSuspend (VOID)
{
    bspDebugMsg("bspSuspend() error: this BSP CAN NOT support this operate!\r\n");
}
/*********************************************************************************************************
** ��������: bspCpuPowerSet
** ��������: CPU ���������ٶ�
** ��  ��  : uiPowerLevel     �����ٶȼ���
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID    bspCpuPowerSet (UINT  uiPowerLevel)
{
}
/*********************************************************************************************************
** ��������: bspCpuPowerGet
** ��������: CPU ��ȡ�����ٶ�
** ��  ��  : puiPowerLevel    �����ٶȼ���
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID    bspCpuPowerGet (UINT  *puiPowerLevel)
{
    if (puiPowerLevel) {
        *puiPowerLevel = LW_CPU_POWERLEVEL_TOP;
    }
}
/*********************************************************************************************************
  ����ϵͳʱ����غ���
*********************************************************************************************************/
/*********************************************************************************************************
  TICK �����������
*********************************************************************************************************/
#define TICK_IN_THREAD  0
#if TICK_IN_THREAD > 0
static LW_HANDLE    htKernelTicks;                                      /*  ����ϵͳʱ�ӷ����߳̾��    */
#endif                                                                  /*  TICK_IN_THREAD > 0          */
/*********************************************************************************************************
** ��������: __tickThread
** ��������: ��ʼ�� tick �����߳�
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
#if TICK_IN_THREAD > 0

static VOID  __tickThread (VOID)
{
    for (;;) {
        API_ThreadSuspend(htKernelTicks);
        API_KernelTicks();                                              /*  �ں� TICKS ֪ͨ             */
        API_TimerHTicks();                                              /*  ���� TIMER TICKS ֪ͨ       */
    }
}

#endif                                                                  /*  TICK_IN_THREAD > 0          */
/*********************************************************************************************************
** ��������: __tickTimerIsr
** ��������: tick ��ʱ���жϷ������
** ��  ��  : NONE
** ��  ��  : �жϷ��񷵻�
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
static irqreturn_t  __tickTimerIsr (VOID)
{
    INTER_CLR_PNDING(BIT_TIMER4);                                       /*  ����ж�                    */

    API_KernelTicksContext();                                           /*  ���汻ʱ���жϵ��߳̿��ƿ�  */

#if TICK_IN_THREAD > 0
    API_ThreadResume(htKernelTicks);
#else
    API_KernelTicks();                                                  /*  �ں� TICKS ֪ͨ             */
    API_TimerHTicks();                                                  /*  ���� TIMER TICKS ֪ͨ       */
#endif                                                                  /*  TICK_IN_THREAD > 0          */
    
    return  (LW_IRQ_HANDLED);
}
/*********************************************************************************************************
  ��ȷʱ�任�����
*********************************************************************************************************/
static UINT32   GuiFullCnt;
static UINT64   Gui64NSecPerCnt7;                                       /*  ��� 7bit ����              */
/*********************************************************************************************************
** ��������: bspTickInit
** ��������: ��ʼ�� tick ʱ��
** ��  ��  : NONE
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTickInit (VOID)
{
#if TICK_IN_THREAD > 0
    LW_CLASS_THREADATTR threadattr;
#endif                                                                  /*  TICK_IN_THREAD > 0          */

    GuiFullCnt       = (UINT16)((PCLK / 800) / LW_TICK_HZ);
    Gui64NSecPerCnt7 = ((1000 * 1000 * 1000 / LW_TICK_HZ) << 7) / GuiFullCnt;

#if TICK_IN_THREAD > 0
    API_ThreadAttrBuild(&threadattr, (8 * LW_CFG_KB_SIZE),
                        LW_PRIO_T_TICK,
                        LW_OPTION_THREAD_STK_CHK |
                        LW_OPTION_THREAD_UNSELECT |
                        LW_OPTION_OBJECT_GLOBAL |
                        LW_OPTION_THREAD_SAFE, LW_NULL);

    htKernelTicks = API_ThreadCreate("t_tick",
                                     (PTHREAD_START_ROUTINE)__tickThread,
                                     &threadattr,
                                     NULL);
#endif                                                                  /*  TICK_IN_THREAD > 0          */

    API_InterVectorConnect(LW_IRQ_14,
                           (PINT_SVR_ROUTINE)__tickTimerIsr,
                           LW_NULL,
                           "tick_timer");

    timerSetPrescaler(1, 99);
    timerSetMuxCnt(4, 2);
    timerSetCnt(4, (UINT16)GuiFullCnt - 1);
    timerConfig(4, TIMER_MANUAL_UPDATE);
    timerConfig(4, TIMER_ENABLE | TIMER_RELOAD | TIMER_UNMANUAL_UPDATE);

    API_InterVectorEnable(LW_IRQ_14);
}
/*********************************************************************************************************
** ��������: bspTickHighResolution
** ��������: ���������һ�� tick ����ǰ�ľ�ȷʱ��.
** �䡡��  : ptv       ��Ҫ������ʱ��
** �䡡��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspTickHighResolution (struct timespec *ptv)
{
    REGISTER UINT32  uiCntCur, uiDone;

    uiCntCur = (UINT32)timerGetCnt(4);
    uiDone   = GuiFullCnt - uiCntCur;

    /*
     *  ����Ƿ��� TICK �ж�����
     */
    if (rSRCPND & BIT_TIMER4) {
        /*
         *  �������� TICK û�м�ʱ����, ������Ҫ���»�ȡ���Ҽ���һ�� TICK ��ʱ��
         */
        uiCntCur = (UINT32)timerGetCnt(4);
        uiDone   = GuiFullCnt - uiCntCur;

        if (uiCntCur != 0) {
            uiDone   += GuiFullCnt;
        }
    } else {
        if (uiCntCur == 0) {
            uiDone = 0;
        }
    }

    ptv->tv_nsec += (LONG)((Gui64NSecPerCnt7 * uiDone) >> 7);
    if (ptv->tv_nsec >= 1000000000) {
        ptv->tv_nsec -= 1000000000;
        ptv->tv_sec++;
    }
}
/*********************************************************************************************************
** ��������: bspDelayUs
** ��������: �ӳ�΢��
** ��  ��  : ulUs     ΢����
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID bspDelayUs (ULONG ulUs)
{
    volatile UINT i;

    while (ulUs) {
        ulUs--;
        for (i = 0; i < 80; i++) {
        }
    }
}
/*********************************************************************************************************
** ��������: bspDelayNs
** ��������: �ӳ�����
** ��  ��  : ulNs     ������
** ��  ��  : NONE
** ȫ�ֱ���:
** ����ģ��:
*********************************************************************************************************/
VOID  bspDelayNs (ULONG ulNs)
{
    volatile UINT i;

    while (ulNs) {
        ulNs = (ulNs < 100) ? (0) : (ulNs - 100);
        for (i = 0; i < 8; i++) {
        }
    }
}
/*********************************************************************************************************
  GCC ����
*********************************************************************************************************/
#ifdef __GNUC__
int  __aeabi_read_tp (void)
{
    return  (0);
}
#endif                                                                  /*  __GNUC__                    */
/*********************************************************************************************************
  END
*********************************************************************************************************/