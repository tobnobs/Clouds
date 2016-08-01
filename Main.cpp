//01/16/2010 C. Germany Visual Studio 2008 MFC Template
/*
Notes: This is a MFC template to create graphical C++ apps without
using the Visual Studio 2008 wizards. It is stripped down to
a bare minimum of code so apps are as simplified as possible.
You must disable some automated features and manually set a
few properties for projects using this template.
1. Create an EMPTY Win32 project. Click -> "File" -> -> "New"
-> "Project" -> "Win32" -> "Win32 Project".
2. Name is and select a directory.
3. Select "Application Settings" -> "Empty Project" then click "Finish".
4. Rt-click project, select "Properties" -> "Configuration Properties"
-> "General" -> "Use of MFC" and change it to
"Use MFC in a Static Library". This will give you MFC components.
5. Disable Incremental Linking. Rt-click project, select "Properties"
-> "Configuration Properties" -> "Linker" -> "General" ->
"Enable Incremental Linking" and set it to "NO".
6. Add a resources file. Rt-click resources and add a DIALOG object.
7. Change the enumerated constant to match the Dialog name.
8. Note that unlike 2003, when calling SetWindowText() in 2008 the
string passed in must be cast/converted using "L".
*/
//-----------------------------------------------------------------------------------------
#include <afxwin.h>      //MFC core and standard components
#include <afxcmn.h>
#include <afxdtctl.h>	
#include "resource.h"    //main symbols
//-----------------------------------------------------------------------------------------
//Globals
CSliderCtrl * numBlobsInput;
CEdit * numBlobsOutput;
CSliderCtrl * densityInput;
CEdit * densityOutput;
CDateTimeCtrl * timeInput;
CButton * drawClick;

class GAME_FORM : public CDialog
{
public:
	GAME_FORM(CWnd* pParent = NULL) : CDialog(GAME_FORM::IDD, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum { IDD = IDD_Menu };
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		numBlobsInput = (CSliderCtrl *)GetDlgItem(Slider_NumBlobs);
		numBlobsOutput = (CEdit *)GetDlgItem(Label_NumBlobs);
		densityInput = (CSliderCtrl *)GetDlgItem(Slider_Density);
		densityOutput = (CEdit *)GetDlgItem(Label_Density);
		timeInput = (CDateTimeCtrl *)GetDlgItem(Time_TimeInput);
		drawClick = (CButton *)GetDlgItem(CB_Draw);

		numBlobsInput->SetRangeMax(3000, TRUE);
		numBlobsInput->SetPos(300);
		numBlobsOutput->SetWindowText(L"300");
		densityInput->SetRangeMax(500, TRUE);
		densityInput->SetPos(50);
		densityOutput->SetWindowText(L"0.05");
		

		return true;
	}
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeTimeinput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnStnClickedDensity2();
};
//-----------------------------------------------------------------------------------------
class GoClouds : public CWinApp
{
public:
	GoClouds() {  }
public:
	virtual BOOL InitInstance()
	{
		CWinApp::InitInstance();
		GAME_FORM dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		return FALSE;
	} //close function
};
//-----------------------------------------------------------------------------------------
//Need a Message Map Macro for both CDialog and CWinApp
BEGIN_MESSAGE_MAP(GAME_FORM, CDialog)

END_MESSAGE_MAP()
//-----------------------------------------------------------------------------------------
GoClouds theApp;  //Starts the Application

void GAME_FORM::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void GAME_FORM::OnDtnDatetimechangeTimeinput(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void GAME_FORM::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void GAME_FORM::OnStnClickedDensity2()
{
	// TODO: Add your control notification handler code here
}
