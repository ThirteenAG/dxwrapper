/**
* Copyright (C) 2025 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "d3d9.h"

HRESULT m_IDirect3DIndexBuffer9::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ") " << riid;

	if (riid == IID_IUnknown || riid == WrapperID || riid == IID_IDirect3DResource9)
	{
		HRESULT hr = ProxyInterface->QueryInterface(WrapperID, ppvObj);

		if (SUCCEEDED(hr))
		{
			*ppvObj = this;
		}

		return hr;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		D3d9Wrapper::genericQueryInterface(riid, ppvObj, m_pDeviceEx);
	}

	return hr;
}

ULONG m_IDirect3DIndexBuffer9::AddRef(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->AddRef())
}

ULONG m_IDirect3DIndexBuffer9::Release(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	ULONG ref = ProxyInterface->Release();

	if (ref ==0 && m_pDeviceEx->GetClientDXVersion() <8)
	{
		m_pDeviceEx->GetLookupTable()->DeleteAddress(this);

		delete this;
	}

	return ref;
}

HRESULT m_IDirect3DIndexBuffer9::GetDevice(THIS_ IDirect3DDevice9** ppDevice)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	if (!ppDevice)
	{
		return D3DERR_INVALIDCALL;
	}

	return m_pDeviceEx->QueryInterface(m_pDeviceEx->GetIID(), (LPVOID*)ppDevice);
}

HRESULT m_IDirect3DIndexBuffer9::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->SetPrivateData(refguid, pData, SizeOfData, Flags))
}

HRESULT m_IDirect3DIndexBuffer9::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->GetPrivateData(refguid, pData, pSizeOfData))
}

HRESULT m_IDirect3DIndexBuffer9::FreePrivateData(THIS_ REFGUID refguid)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->FreePrivateData(refguid))
}

DWORD m_IDirect3DIndexBuffer9::SetPriority(THIS_ DWORD PriorityNew)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->SetPriority(PriorityNew))
}

DWORD m_IDirect3DIndexBuffer9::GetPriority(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->GetPriority())
}

void m_IDirect3DIndexBuffer9::PreLoad(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	VOID_CALL_AND_HANDLE(ProxyInterface->PreLoad())
}

D3DRESOURCETYPE m_IDirect3DIndexBuffer9::GetType(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->GetType())
}

HRESULT m_IDirect3DIndexBuffer9::Lock(THIS_ UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->Lock(OffsetToLock, SizeToLock, ppbData, Flags))
}

HRESULT m_IDirect3DIndexBuffer9::Unlock(THIS)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->Unlock())
}

HRESULT m_IDirect3DIndexBuffer9::GetDesc(THIS_ D3DINDEXBUFFER_DESC *pDesc)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return CALL_AND_HANDLE(ProxyInterface->GetDesc(pDesc))
}
