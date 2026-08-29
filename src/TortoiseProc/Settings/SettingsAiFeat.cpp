#include "stdafx.h"
#include "TortoiseProc.h"
#include "SettingsAiFeat.h"

IMPLEMENT_DYNAMIC(CSettingsAiFeat, ISettingsPropPage)

CSettingsAiFeat::CSettingsAiFeat()
	: ISettingsPropPage(CSettingsAiFeat::IDD)
	, m_bEnableMod(FALSE)
	, m_regEnableMod(L"Software\\TortoiseGit\\AiFeaturesEnabled", FALSE)
{
}

CSettingsAiFeat::~CSettingsAiFeat()
{
}

void CSettingsAiFeat::DoDataExchange(CDataExchange* pDX)
{
	ISettingsPropPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AI_ENABLE, m_bEnableMod);
}

BEGIN_MESSAGE_MAP(CSettingsAiFeat, ISettingsPropPage)
	ON_BN_CLICKED(IDC_AI_ENABLE, &CSettingsAiFeat::OnModified)
END_MESSAGE_MAP()

BOOL CSettingsAiFeat::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	m_bEnableMod = static_cast<DWORD>(m_regEnableMod) ? TRUE : FALSE;
	UpdateData(FALSE);

	return TRUE;
}

BOOL CSettingsAiFeat::OnApply()
{
	UpdateData();
	Store(m_bEnableMod ? 1 : 0, m_regEnableMod);

	SetModified(FALSE);
	return ISettingsPropPage::OnApply();
}

void CSettingsAiFeat::OnModified()
{
	SetModified();
}
