#ifndef GE_INT_H
#define GE_INT_H

#define GE_MAKE_OP(cmd, arg) (((cmd) << 24) | ((arg) & 0x00FFFFFF))
#define GE_VALID_ADDR(addr) ((int)(addr) >= 0 && \
         (ADDR_IS_SCRATCH(addr) || ADDR_IS_VRAM(addr) || ADDR_IS_RAM(addr)))

#define MAKE_SYSCALL(n)            (0x03FFFFFF & (((u32)(n) << 6) | 0x0000000C))
#define MAKE_JUMP(f)               (0x08000000 | ((u32)(f)  & 0x0FFFFFFC)) 
#define JR_RA                      (0x03E00008)
#define NOP                        (0)

#define SCE_GE_INTERNAL_REG_BASE_ADDR 1
#define SCE_GE_INTERNAL_REG_RADR1 2
#define SCE_GE_INTERNAL_REG_RADR2 4

#define SCE_GE_SIGNAL_ERROR_INVALID_ADDRESS 0
#define SCE_GE_SIGNAL_ERROR_STACK_OVERFLOW 1
#define SCE_GE_SIGNAL_ERROR_STACK_UNDERFLOW 2

/******************************/

int _sceGeReset();
int _sceGeInitCallback3(void *arg0, s32 arg1, void *arg2);
int _sceGeInitCallback4();
int _sceGeSetRegRadr1(int arg0);
int _sceGeSetRegRadr2(int arg0);
int _sceGeSetInternalReg(int type, int arg1, int arg2, int arg3);
int _sceGeInterrupt(int arg0, int arg1, int arg2);
s32 _sceGeSysEventHandler(s32 ev_id, char *ev_name, void *param, s32 *result);
int _sceGeModuleStart();
int _sceGeModuleRebootPhase(s32 arg0 __attribute__((unused)), void *arg1 __attribute__((unused)), s32 arg2 __attribute__((unused)), s32 arg3 __attribute__((unused)));
int _sceGeModuleRebootBefore(void *arg0 __attribute__((unused)), s32 arg1 __attribute__((unused)), s32 arg2 __attribute__((unused)), s32 arg3 __attribute__((unused)));
int _sceGeSetBaseRadr(int arg0, int arg1, int arg2);
int _sceGeEdramResume();
int _sceGeEdramSuspend();
int _sceGeQueueInit();
int _sceGeQueueSuspend();
int _sceGeQueueResume();
void _sceGeFinishInterrupt(int arg0, int arg1, int arg2);
void _sceGeListInterrupt(int arg0, int arg1, int arg2);
int sceGeDebugBreak();
int sceGeDebugContinue(int arg0);
int _sceGeQueueInitCallback();
int _sceGeQueueEnd();
int _sceGeQueueStatus(void);
void _sceGeErrorInterrupt(int arg0, int arg1, int arg2);
void _sceGeListError(u32 cmd, int err);
void _sceGeWriteBp(int *list);
void _sceGeClearBp();
void _sceGeListLazyFlush();
int _sceGeListEnQueue(void *list, void *stall, int cbid, SceGeListArgs * arg,
                      int head);

/****** Structures *********/

typedef struct {
    SceGeDisplayList *curRunning;
    int isBreak;
    SceGeDisplayList *active_first;  //  8
    SceGeDisplayList *active_last;   // 12
    SceGeDisplayList *free_first;    // 16
    SceGeDisplayList *free_last;     // 20
    SceUID drawingEvFlagId;     // 24
    SceUID listEvFlagIds[2];    // 28, 32
    SceGeStack stack[32];       // 36
    int sdkVer;                 // 1060
    int patched;                // 1064
    int syscallId;
    SceGeLazy *lazySyncData;
} SceGeQueue;

typedef struct {
    int unk0;
    int status;
    int listAddr; // 8
    int *stallAddr; // 12
    int intrType; // 16
    int sigCmd;
    int finCmd;
    int endCmd;
} SceGeQueueSuspendInfo;

typedef struct {
    u32 addr; // 0
    int count; // 4
    int oldCmd1; // 8
    int oldCmd2; // 12
} SceGeBpCmd;

typedef struct {
    int busy;
    // breakpoints are already set
    int bpSet;
    int size;
    int size2;
    SceGeBpCmd cmds[8];
    SceGeBpCmd cmds2[2];
} SceGeBpCtrl;

typedef struct {
    char *name;
    u32 *ptr;
} SadrUpdate;

typedef struct {
    char reg1;
    char cmd;
    char reg2;
    char size;
} SceGeMatrix;

#endif
