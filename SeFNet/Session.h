#pragma once

#include <memory>
#include "common/MemPool.hpp"
#include "SocketBuffer.h"

class Socket;
// get session from session pool
class Session : public MemElem
{
public:
	virtual bool Init();
	virtual void Clear();
	void SetSocket(Socket* pSocket) { m_pSocket = pSocket; }
	Socket* GetSocket() { return m_pSocket; }
	// call by socket
	void Send(const char* data, int size)
	{
		m_SendBuffer.Write(data, size);
	}
	void Read(char* buf, int size)
	{
		return m_RecvBuffer.Read(buf, size);
	}
	// parse proto by buffer
	void ReadProtoHead(char* buf, int size = 6)
	{
		return m_RecvBuffer.ReadProtoHead(buf, size);
	}

	// socket operate the buffer
	char* GetSendBuf(int& size)
	{
		return m_SendBuffer.GetSendBuf(size);
	}

	void PostSendData(int size)
	{
		return m_SendBuffer.PostSendData(size);
	}

	char* GetRecvBuf(int size)    // socket recv data
	{
		return m_RecvBuffer.GetRecvBuf(size);
	}
	void PostRecvData(int size)
	{
		m_RecvBuffer.PostRecvData(size);
	}

	int GetRecvTotal() { return m_RecvBuffer.TotalLen(); }
#ifdef DEBUG
	// for test
	SocketBuffer& GetSocketSendBuf() { return m_SendBuffer; }
	SocketBuffer& GetSocketRecvBuf() { return m_RecvBuffer; }
#endif
private:
	Socket* m_pSocket{nullptr};
	SocketBuffer m_SendBuffer;
	SocketBuffer m_RecvBuffer;
};

using session_pool_t = MemPool<Session>;
class SessionPool
{
public:
	SessionPool();
	~SessionPool();
	Session* NewSession();
	bool DelSession(Session* session);
	session_pool_t& AllSession();
private:
	session_pool_t m_session_pool;
};

extern std::unique_ptr<SessionPool> g_pSessionPool;