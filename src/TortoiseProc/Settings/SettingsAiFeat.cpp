#include "stdafx.h"
#include "TortoiseProc.h"
#include "SettingsAiFeat.h"

IMPLEMENT_DYNAMIC(CSettingsAiFeat, ISettingsPropPage)

CSettingsAiFeat::CSettingsAiFeat()
	: ISettingsPropPage(CSettingsAiFeat::IDD)
	, m_bEnableMod(FALSE)
	, m_regEnableMod(L"Software\\TortoiseGit\\AiFeaturesEnabled", FALSE)
	, m_regEndpoint(L"Software\\TortoiseGit\\AiEndpoint", L"")
	, m_regApiKey(L"Software\\TortoiseGit\\AiApiKey", L"")
	, m_regModelId(L"Software\\TortoiseGit\\AiModelId", L"")
	, m_regCommitLang(L"Software\\TortoiseGit\\AiCommitLang", 0)
{
}

CSettingsAiFeat::~CSettingsAiFeat()
{
}

void CSettingsAiFeat::DoDataExchange(CDataExchange* pDX)
{
	ISettingsPropPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AI_ENABLE, m_bEnableMod);
	DDX_Text(pDX, IDC_AI_ENDPOINT, m_sEndpoint);
	DDX_Text(pDX, IDC_AI_APIKEY, m_sApiKey);
	DDX_Text(pDX, IDC_AI_MODELID, m_sModelId);
	DDX_CBIndex(pDX, IDC_AI_COMMITLANG, m_nCommitLang);
}

BEGIN_MESSAGE_MAP(CSettingsAiFeat, ISettingsPropPage)
	ON_BN_CLICKED(IDC_AI_ENABLE, &CSettingsAiFeat::OnEnableClicked)
	ON_EN_CHANGE(IDC_AI_ENDPOINT, &CSettingsAiFeat::OnModified)
	ON_EN_CHANGE(IDC_AI_APIKEY, &CSettingsAiFeat::OnModified)
	ON_EN_CHANGE(IDC_AI_MODELID, &CSettingsAiFeat::OnModified)
	ON_CBN_SELCHANGE(IDC_AI_COMMITLANG, &CSettingsAiFeat::OnModified)
END_MESSAGE_MAP()

BOOL CSettingsAiFeat::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	m_bEnableMod = static_cast<DWORD>(m_regEnableMod) ? TRUE : FALSE;
	m_sEndpoint = static_cast<CString>(m_regEndpoint);
	m_sApiKey = static_cast<CString>(m_regApiKey);
	m_sModelId = static_cast<CString>(m_regModelId);
	m_nCommitLang = static_cast<DWORD>(m_regCommitLang);

	auto pCombo = static_cast<CComboBox*>(GetDlgItem(IDC_AI_COMMITLANG));
	pCombo->AddString(L"English");
	pCombo->AddString(L"Russian");

	UpdateData(FALSE);
	EnableControls(m_bEnableMod);

	return TRUE;
}

BOOL CSettingsAiFeat::OnApply()
{
	UpdateData();

	Store(m_bEnableMod ? 1 : 0, m_regEnableMod);
	Store(m_sEndpoint, m_regEndpoint);
	Store(m_sApiKey, m_regApiKey);
	Store(m_sModelId, m_regModelId);
	Store(static_cast<DWORD>(m_nCommitLang), m_regCommitLang);

	SetModified(FALSE);
	return ISettingsPropPage::OnApply();
}

void CSettingsAiFeat::OnModified()
{
	SetModified();
}

void CSettingsAiFeat::OnEnableClicked()
{
	UpdateData();
	EnableControls(m_bEnableMod);
	SetModified();
}

void CSettingsAiFeat::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_AI_ENDPOINT)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_APIKEY)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_MODELID)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_ENDPOINT_LABEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_APIKEY_LABEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_MODELID_LABEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_GROUP)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_COMMITLANG)->EnableWindow(bEnable);
	GetDlgItem(IDC_AI_COMMITLANG_LABEL)->EnableWindow(bEnable);
}
