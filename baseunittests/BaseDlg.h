
// BaseDlg.h : ͷ�ļ�
//

#pragma once


// CBaseDlg �Ի���
class CBaseDlg : public CDialogEx
{
// ����
public:
	CBaseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BASEUNITTESTS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonmsgloop();
	afx_msg void OnBnClickedButtonRunui();
	afx_msg void OnBnClickedButtonStopui();
};
