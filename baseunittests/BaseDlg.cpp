
// BaseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "baseunittests.h"
#include "BaseDlg.h"
#include "afxdialogex.h"

#include "bind.h"
#include "bind_helpers.h"
#include "message_loop.h"

using std::string;
using base::Bind;
using base::MessageLoop;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaseDlg �Ի���



CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_msgloop, &CBaseDlg::OnBnClickedButtonmsgloop)
	ON_BN_CLICKED(IDC_BUTTON_RUNUI, &CBaseDlg::OnBnClickedButtonRunui)
	ON_BN_CLICKED(IDC_BUTTON_STOPUI, &CBaseDlg::OnBnClickedButtonStopui)
END_MESSAGE_MAP()


// CBaseDlg ��Ϣ�������

BOOL CBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

class Foo : public base::RefCounted<Foo> {
public:
	Foo() : test_count_(0) {
	}

	void Test0() {
		++test_count_;
	}

	void Test1ConstRef(const std::string& a) {
		++test_count_;
		result_.append(a);
	}

	void Test1Ptr(std::string* a) {
		++test_count_;
		result_.append(*a);
	}

	void Test1Int(int a) {
		test_count_ += a;
	}

	void Test2Ptr(std::string* a, std::string* b) {
		++test_count_;
		result_.append(*a);
		result_.append(*b);
	}

	void Test2Mixed(const std::string& a, std::string* b) {
		++test_count_;
		result_.append(a);
		result_.append(*b);
	}

	int test_count() const { return test_count_; }
	const std::string& result() const { return result_; }

private:
	friend class base::RefCounted<Foo>;

	~Foo() {}

	int test_count_;
	std::string result_;
};

void CBaseDlg::OnBnClickedButtonmsgloop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageLoop loop(MessageLoop::TYPE_UI);

	// Add tests to message loop
	scoped_refptr<Foo> foo(new Foo());
	string a("a"), b("b"), c("c"), d("d");
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test0, foo.get()));
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test1ConstRef, foo.get(), a));
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test1Ptr, foo.get(), &b));
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test1Int, foo.get(), 100));
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test2Ptr, foo.get(), &a, &c));
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&Foo::Test2Mixed, foo.get(), a, &d));

	// After all tests, post a message that will shut down the message loop
	MessageLoop::current()->PostTask(FROM_HERE, Bind(
		&MessageLoop::Quit, Unretained(base::MessageLoop::current())));

	// Now kick things off
	MessageLoop::current()->Run();

	if (foo->test_count() == 105 && foo->result() == "abacad")
	{
		AfxMessageBox(L"success");
	}
	else
	{
		AfxMessageBox(L"failed");
	}
	/*EXPECT_EQ(foo->test_count(), 105);
	EXPECT_EQ(foo->result(), "abacad");*/
	AfxMessageBox(L"TEST END");
}


void CBaseDlg::OnBnClickedButtonRunui()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageLoop loop(MessageLoop::TYPE_UI);

	AfxMessageBox(L"START UI LOOP");
	loop.Run();
	AfxMessageBox(L"STOP UI LOOP");
}


void CBaseDlg::OnBnClickedButtonStopui()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageLoop::current()->Quit();
}
