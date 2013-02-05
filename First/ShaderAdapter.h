#pragma once

class ShaderAdapter
{
private:
	IDirect3DVertexShader9* m_pVertexShader;
	IDirect3DPixelShader9* m_pPixelShader;
	ID3DXConstantTable* m_pVSConstantsTable;
	ID3DXConstantTable* m_pPSConstantsTable;

public:
	ShaderAdapter();
	virtual ~ShaderAdapter();

	bool initVertexShader(IDirect3DDevice9* pDevice, const std::string& strFile,
		const std::string& strMain = "vs_main", const std::string& strVersion = "vs_2_0");

	bool initPixelShader(IDirect3DDevice9* pDevice, const std::string& strFile,
		const std::string& strMain = "ps_main", const std::string& strVersion = "ps_2_0");

	void update(unsigned int timeMs);
	void render();
	
	virtual void onUpdate();
	virtual void onRender();

	virtual void onConstants() = 0;
};