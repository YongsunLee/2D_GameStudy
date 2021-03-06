#include "stdafx.h"
#include "Framework/Warp2DFramework.h"
#include "Framework/IndRes/IndRes.h"
#include "Object\item\Item.h"
#include "TestScene.h"

#define GRIDSIZE 20

CTestScene::CTestScene()
{
}


CTestScene::~CTestScene()
{
}

bool CTestScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEWHEEL:	
		break;

		// 프레임 워크 단에서 동작하기 위해서는 false
	default:
		return false;
	}

	return(true);
}

bool CTestScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
	{
		// Camera
		// 윈도우 크기 
		auto rcClient = m_pFramework->GetClientSize();
		m_Camera.SetClientSize(Point2F(rcClient.right, rcClient.bottom));
	}
		break;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEWHEEL:
		return OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
		return OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	
		// 프레임 워크 단에서 동작하기 위해서는 false
	default:
		return false;
	}

	return true;
}

bool CTestScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			m_ptPlayer.x -= 20.f;
			break;
		case 'W':
			m_ptPlayer.y -= 20.f;
			break;
		case 'D':
			m_ptPlayer.x += 20.f;
			break;
		case 'S':
			m_ptPlayer.y += 20.f;
			break;
		case 'Z':
			m_Camera.Scale(m_Camera.GetScale() * 2.f);
			break;
		case 'X':
			m_Camera.Scale(m_Camera.GetScale() * 0.5f);
			break;
		case 'G':
			m_uiInventory.GetItem(m_upItem.get());
			break;
		case 'H':
			m_uiInventory.GetItem(nullptr);
			break;
			// 프레임 워크 단에서 동작하기 위해서는 false
		default:
			return false;
		}
		break;
	
	default:
		return false;
	}
	return(true);
}

bool CTestScene::OnCreate(wstring && tag, CWarp2DFramework * pFramework)
{
	if (!Base::OnCreate(std::move(tag), pFramework)) return false;

	// Camera
	// 윈도우 크기 
	auto rcClient = pFramework->GetClientSize();
	m_Camera.SetClientSize(Point2F(rcClient.right, rcClient.bottom));

	auto rendertarget = pFramework->GetRenderTarget();

	rendertarget->CreateSolidColorBrush(ColorF{ ColorF::Red }, &m_pd2dsbrDefault);
	rendertarget->CreateSolidColorBrush(ColorF{ ColorF::GreenYellow }, &m_pd2dGridBrush);

	/*
	auto dwFactoy = m_pIndRes->dwFactory();

	dwFactoy->CreateTextFormat(
	  L"Arial"
	, nullptr
	, DWRITE_FONT_WEIGHT_NORMAL
	, DWRITE_FONT_STYLE_NORMAL
	, DWRITE_FONT_STRETCH_NORMAL
	, 30
	, L"ko-kr"
	, &m_pdwTextFormat);

	m_pdwTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	m_pdwTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	dwFactoy->CreateTextLayout(
		  L"Hello, World!"
		, 13
		, m_pdwTextFormat.Get()
		, 300
		, 100
		, &m_pdwTextLayout);
	
	auto wicFactory = m_pIndRes->wicFactory();
	LoadImageFromFile(wicFactory
		, rendertarget.Get()
		, L"Hit1.png"
		, &m_pd2dbmpTest
	);
	*/
	
	m_Camera.SetPosition(m_ptPlayer);
	m_Camera.SetAnchor(Point2F(0.0f, 0.0f));		// 조금 고치기 (11/6 완료)
	
	// Item
	m_upItem = make_unique<CItem>(Point2F(100,100), RectF(-10,-10,10,10));
	m_upItem->RegisterImage(m_pIndRes.get(), rendertarget.Get(), "Assets/Icon/Buckler.png");

	// Inventory
	m_uiInventory.BuildObject(this);

	return true;
}

void CTestScene::Update(float fTimeElapsed)
{
	m_Camera.SetPosition(m_ptPlayer);
	m_uiInventory.Update(fTimeElapsed);
}

void CTestScene::Draw(ID2D1HwndRenderTarget * pd2dRenderTarget)
{
	auto cameramtx = m_Camera.RegenerateViewMatrix();
	pd2dRenderTarget->SetTransform(cameramtx);

	pd2dRenderTarget->FillRectangle(RectF(-10, -10, 10, 10) + m_ptPlayer, m_pd2dsbrDefault.Get());

	for (int x = 0; x < 50; ++x) {
		for (int y = 0; y < 50; ++y) {
			pd2dRenderTarget->DrawRectangle(RectF(-510 + (x * GRIDSIZE), -510 + (y * GRIDSIZE), -490 + (x * GRIDSIZE), -490 + (y * GRIDSIZE)), m_pd2dGridBrush.Get());
		}
	}

	m_upItem->Draw(pd2dRenderTarget);

	m_uiInventory.Draw(pd2dRenderTarget);
}
