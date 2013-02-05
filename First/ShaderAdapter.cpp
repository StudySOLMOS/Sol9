#include "PCH.h"
#include "ShaderAdapter.h"

ShaderAdapter::ShaderAdapter()
	: m_pVertexShader(nullptr), m_pPixelShader(nullptr)
	, m_pVSConstantsTable(nullptr), m_pPSConstantsTable(nullptr)
{
}

ShaderAdapter::~ShaderAdapter()
{
	if (m_pVSConstantsTable)
		m_pVSConstantsTable->Release();

	if (m_pPSConstantsTable)
		m_pPSConstantsTable->Release();

	if (m_pVertexShader)
		m_pVertexShader->Release();

	if (m_pPixelShader)
		m_pPixelShader->Release();
}

void ShaderAdapter::update(unsigned int timeMs)
{
	onUpdate();
}

void ShaderAdapter::render()
{
	onRender();

	//if (m_pDevice)
	//	return;

	//D3DXMATRIX v, p;
	//m_pDevice->GetTransform(D3DTS_VIEW, &v);
	//m_pDevice->GetTransform(D3DTS_PROJECTION, &p);

	//m_pVSConstantsTable->SetMatrix(m_pDevice, "matWorld", &m_matWorld);
	//m_pVSConstantsTable->SetMatrix(m_pDevice, "matView", &v);
	//m_pVSConstantsTable->SetMatrix(m_pDevice, "matProj", &p);

	//m_pDevice->SetVertexShader(m_pVertexShader);
	//m_pDevice->SetPixelShader(m_pPixelShader);
}
	
void ShaderAdapter::onUpdate()
{
}

void ShaderAdapter::onRender()
{
}

bool ShaderAdapter::initVertexShader(IDirect3DDevice9* pDevice, const std::string& strFile, const std::string& strMain, const std::string& strVersion)
{
	if (!pDevice)
		return false;

	ID3DXBuffer* buffer = nullptr;
	ID3DXBuffer* error = nullptr;

	HRESULT r = 0;
	r = D3DXCompileShaderFromFileA(strFile.c_str(), nullptr, nullptr,
		strMain.c_str(), strVersion.c_str(), 0, &buffer, &error, &m_pVSConstantsTable);

	if (FAILED(r))
	{
		if (error)
		{
			char* e = (char*)error->GetBufferPointer();
			error->Release();

			if (buffer)
				buffer->Release();
		}

		return false;
	}

	if (error)
		error->Release();

	if (buffer)
	{
		r = pDevice->CreateVertexShader((DWORD*)buffer->GetBufferPointer(), &m_pVertexShader);

		if (FAILED(r))
		{
			buffer->Release();
			return false;
		}

		buffer->Release();
		return true;
	}

	return false;
}

bool ShaderAdapter::initPixelShader(IDirect3DDevice9* pDevice, const std::string& strFile, const std::string& strMain, const std::string& strVersion)
{
	if (!pDevice)
		return false;

	ID3DXBuffer* buffer = nullptr;
	ID3DXBuffer* error = nullptr;

	HRESULT r = 0;
	r = D3DXCompileShaderFromFileA(strFile.c_str(), nullptr, nullptr,
		strMain.c_str(), strVersion.c_str(), 0, &buffer, &error, &m_pVSConstantsTable);

	if (FAILED(r))
	{
		if (error)
		{
			char* e = (char*)error->GetBufferPointer();
			error->Release();

			if (buffer)
				buffer->Release();
		}

		return false;
	}

	if (error)
		error->Release();

	if (buffer)
	{
		r = pDevice->CreateVertexShader((DWORD*)buffer->GetBufferPointer(), &m_pVertexShader);

		if (FAILED(r))
		{
			buffer->Release();
			return false;
		}

		buffer->Release();
		return true;
	}

	return false;
}
