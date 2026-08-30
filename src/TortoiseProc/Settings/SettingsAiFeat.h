#pragma once
#include "SettingsPropPage.h"
#include "registry.h"

class CSettingsAiFeat : public ISettingsPropPage
{
	DECLARE_DYNAMIC(CSettingsAiFeat)

public:
	CSettingsAiFeat();
	virtual ~CSettingsAiFeat();

	UINT GetIconID() override { return IDI_GENERAL; }

	enum
	{
		IDD = IDD_SETTINGSAI
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override;

	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog() override;
	BOOL OnApply() override;
	afx_msg void OnModified();
	afx_msg void OnEnableClicked();

private:
	void EnableControls(BOOL bEnable);

	BOOL m_bEnableMod;
	CString m_sEndpoint;
	CString m_sApiKey;
	CString m_sModelId;

	CRegDWORD m_regEnableMod;
	CRegString m_regEndpoint;
	CRegString m_regApiKey;
	CRegString m_regModelId;
	int m_nCommitLang;
	CRegDWORD m_regCommitLang;
};
