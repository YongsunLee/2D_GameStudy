#include "stdafx.h"
#include "UIbase.h"


CUIbase::CUIbase()
{
}


CUIbase::~CUIbase()
{
}

bool CUIbase::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	default:
		return true;
	}
	return(true);
}

bool CUIbase::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:	break;
	case WM_MBUTTONDOWN:	break;
	case WM_RBUTTONDOWN:	break;
	case WM_MOUSEMOVE:		break;
	case WM_LBUTTONUP:		break;
	case WM_MBUTTONUP:		break;
	case WM_RBUTTONUP:		break;
	case WM_MOUSEWHEEL:		break;
	default:
		return false;
	}

	return(true);
}

void CUIbase::Draw(ID2D1HwndRenderTarget * renderTarget)
{
	// MergeRect :: rect 2���� �޾Ƽ� ��ġ�� �Լ� by ���� �����
	// MergeRect(m_rcCaption, m_rcClient)

	// Caption
	renderTarget->SetTransform(Matrix3x2F::Translation(m_ptOrigin.x, m_ptOrigin.y));
	renderTarget->PushAxisAlignedClip(
		m_rcCaption, 
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	DrawCaption(renderTarget);

	renderTarget->PopAxisAlignedClip();

	// Client
	renderTarget->SetTransform(Matrix3x2F::Translation(m_ptOrigin.x, m_ptOrigin.y + m_rcCaption.bottom));
	renderTarget->PushAxisAlignedClip(
		m_rcClient, 
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	DrawClient(renderTarget);

	renderTarget->PopAxisAlignedClip();

}

void CUIbase::DrawClient(ID2D1HwndRenderTarget * renderTarget)
{
}

void CUIbase::DrawCaption(ID2D1HwndRenderTarget * renderTarget)
{
	// Brush�� ��Ʈ�� �ʿ��ѵ� �߻� Ŭ���������� �������� �ʴ´�.
}

void CUIbase::BuildObject(CScene * scene)
{
}