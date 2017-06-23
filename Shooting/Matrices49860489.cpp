// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <math.h>

#include <mmsystem.h>
#include <Digitalv.h>

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT 1600
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define ENEMY_NUM 150
#define MAX 30
#define BMAX 50
#define MOVEMAX 200

bool tScreen = true;
bool mScreen = false;
bool gScreen = false;
bool wScreen = false;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface



						// sprite declarations
LPDIRECT3DTEXTURE9 sprite_Bg;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;
LPDIRECT3DTEXTURE9 sprite_hero_hit;
LPDIRECT3DTEXTURE9 sprite_boss;
LPDIRECT3DTEXTURE9 sprite_bossbullet;
LPDIRECT3DTEXTURE9 sprite_mScreen; 
LPDIRECT3DTEXTURE9 sprite_gScreen; 
LPDIRECT3DTEXTURE9 sprite_tScreen;
LPDIRECT3DTEXTURE9 sprite_wScreen;
LPDIRECT3DTEXTURE9 sprite_ScoreScreen;
LPDIRECT3DTEXTURE9 sprite_Score0;
LPDIRECT3DTEXTURE9 sprite_Score1;
LPDIRECT3DTEXTURE9 sprite_Score2;
LPDIRECT3DTEXTURE9 sprite_Score3;
LPDIRECT3DTEXTURE9 sprite_Score4;
LPDIRECT3DTEXTURE9 sprite_Score5;
LPDIRECT3DTEXTURE9 sprite_Score6;
LPDIRECT3DTEXTURE9 sprite_Score7;
LPDIRECT3DTEXTURE9 sprite_Score8;
LPDIRECT3DTEXTURE9 sprite_Score9;
LPDIRECT3DTEXTURE9 sprite_Score_One; // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_Score_Ten;

MCI_OPEN_PARMS mciopen;
MCI_PLAY_PARMS mciplay;
MCI_OPEN_PARMS mciopen2;
MCI_PLAY_PARMS mciplay2;
MCI_OPEN_PARMS mciopen3;
MCI_PLAY_PARMS mciplay3;
MCI_OPEN_PARMS mciopen4;
MCI_PLAY_PARMS mciplay4;
int dwID;
int dwID2;
int dwID3;
int dwID4;



									 // function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

bool One = true;

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//기본 클래스 
class entity {

public:
	float x_pos;
	float y_pos;
	int status;
	int HP;

};


bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}

bool sphere_collision_check2(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}

class BackGround :public entity {
public:
	void BgPosition();
};

/*void BgPosition();
{
	
}*/
//주인공 클래스 
class Hero :public entity {

public:
	bool hShow;
	bool hhShow;
	
	void fire();
	void super_fire();
	void move(int i);
	bool show();
	bool hshow();
	
	void init(float x, float y);
	void health(int h);
	void hide();
	void hhide();
	void active();
	void hactive();
	bool check_collision(float x, float y);
	bool check_collision2(float x, float y);

};

void Hero::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool Hero::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		hShow = false;
		return true;
	}
	else {
		return false;
	}
}

bool Hero::check_collision2(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check2(x_pos, y_pos, 32, x, y, 32) == true)
	{
		hhShow = true;		
		return false;
	}
	else {
		return true;
	}
}

void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_UP:
		y_pos -= 10;
		break;

	case MOVE_DOWN:
		y_pos += 10;
		break;


	case MOVE_LEFT:
		x_pos -= 10;
		break;


	case MOVE_RIGHT:
		x_pos += 10;
		break;

	}

}


bool Hero::show()
{
	return hShow;
}

void Hero::hide()
{
	hShow = false;
}

void Hero::active()
{
	hShow = true;
}

bool Hero::hshow()
{
	return hhShow;
}

void Hero::hhide()
{
	hhShow = false;
}

void Hero::hactive()
{
	hhShow = true;
}

// 적 보스 클래스
class EnemyBoss :public entity {

public:	
	bool bossShow;
	bool show();
	bool active();
	bool hide();
	void init(float x, float y);
	void move(float xMove);
	bool check_collision(float x, float y);
};

bool EnemyBoss::show()
{
	return bossShow;
}

bool EnemyBoss::active()
{
	bossShow = true;
	return bossShow;
}

bool EnemyBoss::hide()
{
	bossShow = false;
	return bossShow;
}

bool EnemyBoss::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bossShow = false;
		return true;
	}
	else
		return false;
}

void EnemyBoss::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void EnemyBoss::move(float xMove)
{
	x_pos = xMove;
}

// 적 클래스 
class Enemy :public entity {

public:
	bool eShow;
	bool show();
	bool active();
	bool hide();
	void fire();
	void init(float x, float y);
	void move();

	bool bossCheck;

};

void Enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


void Enemy::move()
{
	y_pos += 5;
}

bool Enemy::show()
{
	return eShow;
}

bool Enemy::active()
{
	eShow = true;
	return eShow;
}

bool Enemy::hide()
{
	eShow = false;
	return eShow;
}

// 보스 총알 클래스
class BossBullet :public entity {

public:
	bool BbShow1;
	bool BbShow2;
	bool BbShow3;

	void init(float x, float y);
	void move1(float xAngle);
	void move2(float xAngle2);
	void move3(float xAngle3);
	bool show1();
	bool show2();
	bool show3();
	void hide();
	void active();
	void hide2();
	void active2();
	void hide3();
	void active3();
	bool check_collision1(float x, float y);
	bool check_collision2(float x, float y);
	bool check_collision3(float x, float y);
};

bool BossBullet::check_collision1(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 8, x, y, 8) == true)
	{
		BbShow1 = false;
		return true;
	}
	else {
		return false;
	}
}

bool BossBullet::check_collision2(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 8, x, y, 8) == true)
	{
		BbShow2 = false;
		return true;
	}
	else {
		return false;
	}
}

bool BossBullet::check_collision3(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 8, x, y, 8) == true)
	{
		BbShow3 = false;
		return true;
	}
	else {
		return false;
	}
}


void BossBullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool BossBullet::show1()
{
	return BbShow1;
}

void BossBullet::hide()
{
	BbShow1 = false;
}

void BossBullet::active()
{
	BbShow1 = true;
}

bool BossBullet::show2()
{
	return BbShow2;
}

void BossBullet::hide2()
{
	BbShow2 = false;
}

void BossBullet::active2()
{
	BbShow3 = true;
}

bool BossBullet::show3()
{
	return BbShow3;
}

void BossBullet::hide3()
{
	BbShow3 = false;
}

void BossBullet::active3()
{
	BbShow3 = true;
}

void BossBullet::move1(float xAngle)
{
	y_pos += 6;
	x_pos += xAngle;
}

void BossBullet::move2(float xAngle2)
{
	y_pos += 6;
	x_pos += xAngle2;
}

void BossBullet::move3(float xAngle3)
{
	y_pos += 6;
	x_pos += xAngle3;
}

class BossBullet3 :public entity {

public:
	bool BbShow;

	void init(float x, float y);	
	void move(float xAngle);
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

bool BossBullet3::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		BbShow = false;
		return true;
	}
	else {
		return false;
	}
}


void BossBullet3::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool BossBullet3::show()
{
	return BbShow;
}


void BossBullet3::active()
{
	BbShow = true;
}

void BossBullet3::move(float xAngle)
{
	y_pos -= 8;
	x_pos += xAngle;
}

void BossBullet3::hide()
{
	BbShow = false;
}

class BossBullet2 :public entity {

public:
	bool BbShow2;

	void init(float x, float y);
	void move1(float xA, float yA);
	void move2(float ShotAngle, float ShotAngleRate, float ShotSpeed);
	bool show();
	void hide();
	void active();
	
	float ShotAngle;
	float ShotAngleRate;
	float ShotSpeed;

	/*BossBullet2(float angle, float angle_rate, float speed)
		: ShotAngle(angle),
		ShotAngleRate(angle_rate),
		ShotSpeed(speed)
	{}*/

	bool check_collision(float x, float y);
};

bool BossBullet2::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		BbShow2 = false;
		return true;
	}
	else {
		return false;
	}
}


void BossBullet2::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool BossBullet2::show()
{
	return BbShow2;
}


void BossBullet2::active()
{
	BbShow2 = true;
}


void BossBullet2::move1(float xA, float yA)
{		
	x_pos += xA;
	y_pos += yA;

	/*float rad = Angle * D3DX_PI * 2;
		
	x_pos += Angle * cosf(rad);
	y_pos += Angle * sinf(rad);
	
	Angle += Angle_rate;
	Speed += Speed_rate;*/

}

/*oid BossBullet2::move2(float ShotAngle, float ShotAngleRate, float ShotSpeed)
{
	ShotAngle += ShotAngleRate;
	ShotAngle -= floor(ShotAngle);

	move1(x_pos, y_pos, ShotAngle, 0, ShotSpeed, 0);	
}*/

void BossBullet2::hide()
{
	BbShow2 = false;
}

// 총알 클래스 
class Bullet :public entity {

public:
	bool bShow;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
	bool check_collision2(float x, float y);


};


bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}

bool Bullet::check_collision2(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 64, x, y, 64) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}




void Bullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}



bool Bullet::show()
{
	return bShow;
}


void Bullet::active()
{
	bShow = true;

}

void Bullet::move()
{
	y_pos -= 11;
}

void Bullet::hide()
{
	bShow = false;
}






//객체 생성 
Hero hero;
//HeroHit hero_hit;
Enemy enemy[ENEMY_NUM];
Bullet bullet[MAX];
BossBullet2 Bbullet2[BMAX];
BossBullet Bbullet[BMAX];
BossBullet3 Bbullet3[BMAX];
EnemyBoss boss;



// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

		mciopen.lpstrElementName = L"BGM_Alicia.mp3";
		mciopen.lpstrDeviceType = L"MPEGVideo";

		mciSendCommand(dwID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciopen);
		dwID = mciopen.wDeviceID;
		mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay);
			
		mciopen2.lpstrElementName = L"Battle.mp3";
		mciopen2.lpstrDeviceType = L"MPEGVideo";
		
		mciSendCommand(dwID2, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciopen2);
		dwID2 = mciopen2.wDeviceID;

		mciopen3.lpstrElementName = L"Voice_Alicia_Over.mp3";
		mciopen3.lpstrDeviceType = L"MPEGVideo";

		mciSendCommand(dwID3, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciopen3);
		dwID3 = mciopen3.wDeviceID;

		mciopen4.lpstrElementName = L"Voice_Alicia_Win.mp3";
		mciopen4.lpstrDeviceType = L"MPEGVideo";

		mciSendCommand(dwID4, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciopen4);
		dwID4 = mciopen4.wDeviceID;
		
	

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);




		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;

	switch (message)
	{
	case WM_LBUTTONUP:
	{
				
		if (tScreen = true)
		{
			tScreen = false;
			mScreen = true;
			mciSendCommand(1, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay);
			mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay);

			mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
			break;
		}

		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"ScoreScreen.png",    // the file name
		197,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_ScoreScreen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_0.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score0);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_1.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_2.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_3.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_4.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score4);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_5.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score5);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_6.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score6);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_7.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score7);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_8.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score8);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score_9.png",    // the file name
		43,    // default width
		80,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Score9);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"wScreen.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_wScreen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"gScreen.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_gScreen);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"mScreen.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_mScreen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"tScreen2.png",    // the file name
		1000,    // default width
		1600,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_tScreen);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Bg.png",    // the file name
		1000,    // default width
		1600,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Bg);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Alicia.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Shiva.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Attack.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Alicia_hit.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_hit);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss2.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_boss);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"BossBullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bossbullet);

	return;
}

void init_game(void)
{	
		//객체 초기화	
		hero.active();
		hero.hhShow = false;
		hero.init(300, 700);

		//적 생성
		//enemy[BMAX].active();

		enemy[0].init(100, 500 - 600);
		enemy[1].init(150, 500 - 650);
		enemy[2].init(200, 500 - 700);
		enemy[3].init(50, 500 - 550);
		enemy[4].init(250, 500 - 750);

		enemy[5].init(500, 500 - 750);
		enemy[6].init(550, 500 - 700);
		enemy[7].init(600, 500 - 650);
		enemy[8].init(650, 500 - 600);
		enemy[9].init(700, 500 - 550);
		enemy[10].init(750, 500 - 500);
		////////////////////////////////
		enemy[11].init(500, 10 - 750);
		enemy[12].init(550, 10 - 700);
		enemy[13].init(600, 10 - 650);
		enemy[14].init(650, 10 - 700);
		enemy[15].init(700, 10 - 750);

		enemy[16].init(0, 10 - 500);
		enemy[17].init(50, 10 - 550);
		enemy[18].init(100, 10 - 600);
		enemy[19].init(150, 10 - 550);
		enemy[20].init(200, 10 - 500);
		///////////////////////////////
		enemy[21].init(500, 10 - 1250);
		enemy[22].init(550, 10 - 1200);
		enemy[23].init(600, 10 - 1250);
		enemy[24].init(700, 10 - 1200);
		enemy[25].init(750, 10 - 1250);

		enemy[26].init(0, 10 - 1500);
		enemy[27].init(50, 10 - 1550);
		enemy[28].init(100, 10 - 1500);
		enemy[29].init(200, 10 - 1550);
		enemy[30].init(250, 10 - 1500);

		enemy[31].init(0, 10 - 1900);
		enemy[32].init(50, 10 - 1850);
		enemy[33].init(100, 10 - 1800);
		enemy[34].init(200, 10 - 1850);
		enemy[35].init(250, 10 - 1900);

		//적들 초기화 
		for (int j = 0; j < ENEMY_NUM; j++)
		{
			enemy[j].eShow = true;
		}

		//보스 총알 초기화
		for (int j = 0; j < BMAX; j++)
		{
			Bbullet[j].init(boss.x_pos, boss.y_pos);
		}

		for (int i = 0; i < BMAX; i++)
		{
			Bbullet3[i].init(boss.x_pos, boss.y_pos);
		}

		//총알 초기화
		for (int i = 0; i < MAX; i++)
		{
			bullet[i].init(hero.x_pos, hero.y_pos);
		}	
}

float xAngle = 0.0f;
float xAngle2 = 0.0f;
float xAngle3 = 0.0f;
bool xCheck = true;
bool xCheck2 = true;
bool xCheck3 = true;

float xMove = 0.0f;
bool xMoveCheck = true;

bool BulletCheck = false;
int bosshp = 50;

bool bossCheck = false;
int enemyCount = 30;

float xA = 0.0f;
float yA = 0.0f;
float Angle = 0.0f;
float Speed = 0.1f;
float rad = Angle * D3DX_PI * 2;
float Angle_rate = 0.02f;
bool xyCheck = true;

int ScoreCount = 0;
//float Speed_rate = 0.01f;

void do_game_logic(void)
{
	if (mScreen)
	{
		if (ScoreCount % 10 == 0)
		{
			sprite_Score_One = sprite_Score0;
		}
		if (ScoreCount % 10 == 1)
		{
			sprite_Score_One = sprite_Score1;
		}
		if (ScoreCount % 10 == 2)
		{
			sprite_Score_One = sprite_Score2;
		}
		if (ScoreCount % 10 == 3)
		{
			sprite_Score_One = sprite_Score3;
		}
		if (ScoreCount % 10 == 4)
		{
			sprite_Score_One = sprite_Score4;
		}
		if (ScoreCount % 10 == 5)
		{
			sprite_Score_One = sprite_Score5;
		}
		if (ScoreCount % 10 == 6)
		{
			sprite_Score_One = sprite_Score6;
		}
		if (ScoreCount % 10 == 7)
		{
			sprite_Score_One = sprite_Score7;
		}
		if (ScoreCount % 10 == 8)
		{
			sprite_Score_One = sprite_Score8;
		}
		if (ScoreCount % 10 == 9)
		{
			sprite_Score_One = sprite_Score9;
		}

		if (ScoreCount / 10 == 0)
		{
			sprite_Score_Ten = sprite_Score0;
		}

		if (ScoreCount / 10 == 1)
		{
			sprite_Score_Ten = sprite_Score1;
		}

		if (ScoreCount / 10 == 2)
		{
			sprite_Score_Ten = sprite_Score2;
		}

		if (ScoreCount / 10 == 3)
		{
			sprite_Score_Ten = sprite_Score3;
		}

		if (ScoreCount / 10 == 4)
		{
			sprite_Score_Ten = sprite_Score4;
		}

		if (ScoreCount / 10 == 5)
		{
			sprite_Score_Ten = sprite_Score5;
		}

		if (ScoreCount / 10 == 6)
		{
			sprite_Score_Ten = sprite_Score6;
		}

		//주인공 처리 
		if (KEY_DOWN(VK_UP))
			hero.move(MOVE_UP);

		if (KEY_DOWN(VK_DOWN))
			hero.move(MOVE_DOWN);

		if (KEY_DOWN(VK_LEFT))
			hero.move(MOVE_LEFT);

		if (KEY_DOWN(VK_RIGHT))
			hero.move(MOVE_RIGHT);

		if (bossCheck == true)
		{
			boss.active();
			boss.init(300, 200);
		}

		boss.move(xMove);
		if (xMove >= 600)
			xMoveCheck = true;
		else if (xMove <= 100)
			xMoveCheck = false;

		if (xMoveCheck == true)
			xMove -= 5;
		else if (xMoveCheck == false)
			xMove += 5;

		//적들 처리 
		for (int j = 0; j < ENEMY_NUM; j++)
		{
			if (enemy[j].y_pos > 1000)
			{
				enemy[j].hide();
				enemy[j].init(3000, 3000);
			}
			else
				enemy[j].move();
		}

		//보스 총알	
		//2에서 -20까지 줄어들때까지 체크	

		if (xAngle >= 50)
		{
			xCheck = true;
		}

		else if (xAngle <= -50)
		{
			xCheck = false;
		}

		if (xCheck == true)
		{
			xAngle -= 3.3f;
		}

		else if (xCheck == false)
		{
			xAngle += 3.3;
		}
		
		//Move2
		if (xAngle2 >= 75)
		{
			xCheck2 = true;
		}

		else if (xAngle2 <= -75)
		{
			xCheck2 = false;
		}

		if (xCheck2 == true)
		{
			xAngle2 -= 5.8f;
		}

		else if (xCheck2 == false)
		{
			xAngle2 += 5.8;
		}

		//Move3
		if (xAngle3 >= 100)
		{
			xCheck3 = true;
		}

		else if (xAngle3 <= -100)
		{
			xCheck3 = false;
		}

		if (xCheck3 == true)
		{
			xAngle3 -= 7.5f;
		}

		else if (xCheck3 == false)
		{
			xAngle3 += 7.5f;
		}

		//Boss 체크
		if (bossCheck == true)
		{
			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show1() == false)
				{
					Bbullet[i].active();
					Bbullet[i].init(boss.x_pos, boss.y_pos);
					break;
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show2() == false)
				{
					Bbullet[i].active2();
					Bbullet[i].init(boss.x_pos, boss.y_pos);
					break;
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show3() == false)
				{
					Bbullet[i].active3();
					Bbullet[i].init(boss.x_pos, boss.y_pos);
					break;
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet3[i].show() == false)
				{
					Bbullet3[i].active();
					Bbullet3[i].init(boss.x_pos, boss.y_pos);
					break;
				}
			}
		}

		if (xA >= 50)
		{
			xyCheck = true;
		}

		else if (xA <= -50)
		{
			xyCheck = false;
		}

		if (xyCheck == true)
		{
			xA -= 0.8f;
		}

		else if (xyCheck == false)
		{
			yA += 0.8f;
		}

		xA += Angle * cosf(rad);
		yA += Angle * sinf(rad);

		Angle += Angle_rate;
		//Speed += Speed_rate;

		if (bossCheck == true)
		{
			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show1() == true)
				{
					if (Bbullet[i].y_pos > 1000)
					{
						Bbullet[i].hide();
					}
					else
						Bbullet[i].move1(xAngle);
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show2() == true)
				{
					if (Bbullet[i].y_pos > 1000)
					{
						Bbullet[i].hide2();
					}
					else
						Bbullet[i].move2(xAngle);
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].show3() == true)
				{
					if (Bbullet[i].y_pos > 1000)
					{
						Bbullet[i].hide3();
					}
					else
						Bbullet[i].move3(xAngle);
				}
			}

			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet3[i].show() == true)
				{
					if (Bbullet3[i].y_pos < 10)
					{
						Bbullet3[i].hide();
					}
					else
						Bbullet3[i].move(xAngle);
				}
			}
		}
		
		//총알 처리

		if (KEY_DOWN(VK_SPACE))
		{
			if (One)
			{
				for (int i = 0; i < MAX;i++)
				{
					if (bullet[i].show() == false)
					{
						bullet[i].active();
						bullet[i].init(hero.x_pos, hero.y_pos);
						One = false;
						break;
					}
				}
			}
		}

		if (KEY_UP(VK_SPACE))
		{
			One = true;

		}

		for (int i = 0;i < MAX;i++)
		{
			if (bullet[i].show() == true)
			{
				if (bullet[i].y_pos < 10)
				{
					bullet[i].hide();
					bullet[i].init(18000, 18000);
				}
				else
					bullet[i].move();
			}
		}
			//충돌 처리 
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				if (bullet[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
				{
					ScoreCount++;
					bullet[i].hide();
					bullet[i].init(18000, 18000);
					enemy[j].hide();
					enemy[j].init(5000, 5000);

					enemyCount -= 1;

					if (enemyCount == 0)
					{
						bossCheck = true;
					}
				}
			}
		}

		for (int i = 0; i < MAX; i++)
		{
			for (int i = 0; i < BMAX; i++)
			{
				if (Bbullet[i].check_collision1(hero.x_pos, hero.y_pos) == true)
				{ 
					mScreen = false;
					gScreen = true;
					if (gScreen = true)
					{
						mciSendCommand(2, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay2);

						mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay3);
						break;
					}
				}
				if (Bbullet[i].check_collision2(hero.x_pos, hero.y_pos) == true)
				{
					mScreen = false;
					gScreen = true;
					if (gScreen = true)
					{
						mciSendCommand(2, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay2);

						mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay3);
						break;
					}
				}
				if (Bbullet[i].check_collision3(hero.x_pos, hero.y_pos) == true)
				{
					mScreen = false;
					gScreen = true;
					if (gScreen = true)
					{
						mciSendCommand(2, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay2);

						mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay3);
						break;
					}
				}
			}
		}
		
		for (int i =0; i < MAX; i++)
		{
				if (bullet[i].check_collision(boss.x_pos, boss.y_pos) == true)
				{
					if (bossCheck == true)
					{
						bosshp -= 1;

						if (bosshp == 0)
						{
							bossCheck = false;
							boss.hide();
							boss.init(3000, 3000);
							for (int i = 0; i < BMAX; i++)
							{
								Bbullet[i].hide();
								Bbullet[i].init(12333, 13222);
								Bbullet3[i].hide();
								Bbullet3[i].init(13333, 13333);
							}
							mScreen = false;
							wScreen = true;
							if (wScreen = true)
							{
								mciSendCommand(2, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
								mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay2);

								mciSendCommand(4, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay4);
								break;
							}
						}
					}
					
				}

		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				mScreen = false;
				gScreen = true;
				if (gScreen = true)
				{
					mciSendCommand(2, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay2);
					mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciplay2);

					mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciplay3);
					break;
				}
				
			}		

			/*else if (hero.check_collision2(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				hero.hactive();
			}

			else if (hero.check_collision2(enemy[i].x_pos, enemy[i].y_pos) == false)
			{
				hero.hhide();
			}		
			else if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				hero.hide();
			}*/
		}
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window to a deep blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

											 //UI 창 렌더링 


											 /*
											 static int frame = 21;    // start the program on the final frame
											 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
											 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

											 // calculate the x-position
											 int xpos = frame * 182 + 1;

											 RECT part;
											 SetRect(&part, xpos, 0, xpos + 181, 128);
											 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
											 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
											 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
											 */

											 //주인공 
	if (mScreen == true)
	{
		RECT part;
		SetRect(&part, 0, 0, 1000, 1600);
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_Bg, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (hero.hShow == true)
		{
			RECT part0;
			SetRect(&part0, 0, 0, 64, 64);
			D3DXVECTOR3 center0(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position0(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hero, &part0, &center0, &position0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		////총알 
		RECT part1;
		SetRect(&part1, 0, 0, 32, 32);
		D3DXVECTOR3 center1(-20.0f, -5.0f, 0.0f);

		for (int i = 0; i < MAX;i++)
		{
			if (bullet[i].bShow == true)
			{
				// center at the upper-left corner
				D3DXVECTOR3 position1(bullet[i].x_pos, bullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}

		////에네미 
		RECT part2;
		SetRect(&part2, 0, 0, 64, 64);
		D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

		for (int j = 0; j<ENEMY_NUM; j++)
		{
			if (enemy[j].eShow == true)
			{
				D3DXVECTOR3 position2(enemy[j].x_pos, enemy[j].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}



		if (hero.hhShow == true)
		{
			RECT part3;
			SetRect(&part3, 0, 0, 64, 64);
			D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position3(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hero_hit, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (boss.bossShow == true)
		{
			RECT part4;
			SetRect(&part4, 0, 0, 128, 128);
			D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position4(boss.x_pos, boss.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_boss, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		RECT part5;
		SetRect(&part5, 0, 0, 32, 32);
		D3DXVECTOR3 center5(-50.0f, -20.0f, 0.0f);	// center at the upper-left corner
		for (int i = 0; i < BMAX; i++)
		{
			if (Bbullet[i].BbShow1 == true)
			{
				D3DXVECTOR3 position5(Bbullet[i].x_pos, Bbullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bossbullet, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}

		RECT part15;
		SetRect(&part15, 0, 0, 32, 32);
		D3DXVECTOR3 center15(-50.0f, -20.0f, 0.0f);	// center at the upper-left corner
		for (int i = 0; i < BMAX; i++)
		{
			if (Bbullet[i].BbShow2 == true)
			{
				D3DXVECTOR3 position15(Bbullet[i].x_pos, Bbullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bossbullet, &part15, &center15, &position15, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}

		RECT part25;
		SetRect(&part25, 0, 0, 32, 32);
		D3DXVECTOR3 center25(-50.0f, -20.0f, 0.0f);	// center at the upper-left corner
		for (int i = 0; i < BMAX; i++)
		{
			if (Bbullet[i].BbShow3 == true)
			{
				D3DXVECTOR3 position25(Bbullet[i].x_pos, Bbullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bossbullet, &part25, &center25, &position25, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}

		RECT part6;
		SetRect(&part6, 0, 0, 32, 32);
		D3DXVECTOR3 center6(-50.0f, -20.0f, 0.0f);	// center at the upper-left corner
		for (int i = 0; i < BMAX; i++)
		{
			if (Bbullet3[i].BbShow == true)
			{
				D3DXVECTOR3 position6(Bbullet3[i].x_pos, Bbullet3[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bossbullet, &part6, &center6, &position6, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}

		RECT part9;
		SetRect(&part9, 0, 0, 32, 32);
		D3DXVECTOR3 center9(-50.0f, -20.0f, 0.0f);	// center at the upper-left corner
		for (int i = 0; i < BMAX; i++)
		{
			if (Bbullet2[i].BbShow2 == true)
			{
				D3DXVECTOR3 position9(Bbullet2[i].x_pos, Bbullet2[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bossbullet, &part9, &center9, &position9, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		
		RECT part110;
		SetRect(&part110, 0, 0, 43, 80);
		D3DXVECTOR3 center110(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position110(247.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_Score_One, &part110, &center110, &position110, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT part111;
		SetRect(&part111, 0, 0, 43, 80);
		D3DXVECTOR3 center111(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position111(217.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_Score_Ten, &part111, &center111, &position111, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT part112;
		SetRect(&part112, 0, 0,197,80);
		D3DXVECTOR3 center112(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position112(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_ScoreScreen, &part112, &center112, &position112, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	if (wScreen == true)
	{
		RECT part10;
		SetRect(&part10, 0, 0, 1000, 1600);
		D3DXVECTOR3 center10(0.0f, 0.0f, 0.0f);	// center at the upper-left corner
		D3DXVECTOR3 position10(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_wScreen, &part10, &center10, &position10, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (tScreen == true)
	{
		RECT part7;
		SetRect(&part7, 0, 0, 1000, 1600);
		D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);	// center at the upper-left corner
		D3DXVECTOR3 position7(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_tScreen, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));
	}	
	
	if (gScreen == true)
	{
		RECT part9;
		SetRect(&part9, 0, 0, 1000, 1600);
		D3DXVECTOR3 center9(0.0f, 0.0f, 0.0f);	// center at the upper-left corner
		D3DXVECTOR3 position9(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_gScreen, &part9, &center9, &position9, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite_Bg->Release();
	d3ddev->Release();
	d3d->Release();

	//객체 해제 
	sprite_hero->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();

	return;
}
