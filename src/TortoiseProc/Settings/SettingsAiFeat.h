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

private:
	BOOL m_bEnableMod;
	CRegDWORD m_regEnableMod;
};
