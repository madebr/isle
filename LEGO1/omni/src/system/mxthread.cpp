#include "mxthread.h"

#include "decomp.h"

#include <process.h>

DECOMP_SIZE_ASSERT(MxThread, 0x1c)

// FUNCTION: LEGO1 0x100bf510
MxThread::MxThread()
{
	m_hThread = NULL;
	m_running = TRUE;
	m_threadId = 0;
}

// FUNCTION: LEGO1 0x100bf5a0
MxThread::~MxThread()
{
	if (m_hThread) {
		CloseHandle((HANDLE) m_hThread);
	}
}

typedef unsigned(__stdcall* ThreadFunc)(void*);

// FUNCTION: LEGO1 0x100bf610
MxResult MxThread::Start(MxS32 p_stackSize, MxS32 p_flag)
{
	MxResult result = FAILURE;

	if (m_semaphore.Init(0, 1) == SUCCESS) {
		if ((m_hThread =
				 _beginthreadex(NULL, p_stackSize * 4, (ThreadFunc) &MxThread::ThreadProc, this, p_flag, &m_threadId)
			)) {
			result = SUCCESS;
		}
	}

	return result;
}

// FUNCTION: LEGO1 0x100bf660
void MxThread::Sleep(MxS32 p_milliseconds)
{
	::Sleep(p_milliseconds);
}

// FUNCTION: LEGO1 0x100bf670
void MxThread::Terminate()
{
	m_running = FALSE;
	m_semaphore.Wait(INFINITE);
}

// FUNCTION: LEGO1 0x100bf680
unsigned MxThread::ThreadProc(void* p_thread)
{
	return static_cast<MxThread*>(p_thread)->Run();
}

// FUNCTION: LEGO1 0x100bf690
MxResult MxThread::Run()
{
	m_semaphore.Release(1);
	return SUCCESS;
}
