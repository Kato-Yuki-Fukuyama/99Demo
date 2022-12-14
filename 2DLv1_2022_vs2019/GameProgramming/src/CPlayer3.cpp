#include "CPlayer3.h"
#include "CApplication.h"
// Use WINDOW_WIDTH
#include "main.h"

CPlayer3* CPlayer3::spInstance = nullptr;

CPlayer3* CPlayer3::Instance()
{
	return spInstance;
}

#define TEXCOORD 115, 126, 70, 62	//テクスチャマッピング
//#define TEXCOORD 168, 188, 158, 128	//テクスチャマッピング
#define TEXCRY 196, 216, 158, 128	//テクスチャマッピング
//#define GRAVITY (TIPSIZE / 20.0f)	//重力加速度
#define JUMPV0 (TIPSIZE / 1.4f)		//ジャンプの初速
#define GRAVITY (0.0f)	//重力加速度

#define TEXCOORD2 136,156,158,128	//右向き2
#define TEXLEFT1 188,168,158,128	//左向き1
#define TEXLEFT2 156,136,158,128	//左向き2
#define VELOCITY 4.0f	//移動速度

#define HP 3 //HPの初期値は3

#define SE_JUMP "res\\jump.wav" //ジャンプの音声ファイル

int CPlayer3::sHp = 0;	//HP

int CPlayer3::Hp()
{
	return sHp;
}

void CPlayer3::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CPlayer3::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o, &x, &y))
		{
			//敵の衝突判定を実行
			o->Collision(o, m);
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
				else
				{	//ジャンプでなければ泣く
					mState = EState::ECRY;
					if (mInvincible == 0)
					{
						mInvincible = 60;
						sHp--;
					}
				}
			}
			else
			{	//ジャンプでなければ泣く
				mState = EState::ECRY;
				if (mInvincible == 0)
				{
					mInvincible = 60;
					sHp--;
				}
			}
		}
		break;
	case ETag::EPLAYER:
		break;
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
	}
}

CPlayer3::CPlayer3(float x, float y, float w, float h, CTexture* pt)
	: mInvincible(0)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
	sHp = HP;
	//ジャンプ音ロード
	mSoundJump.Load(SE_JUMP);

	spInstance = this;
}

void CPlayer3::Update()
{
	//無敵時間中はカウントを減少する
	if (mInvincible > 0)
	{
		mInvincible--;
	}
	if (mState != EState::EJUMP)
	{
		// CLICK TO JUMP
		if (mInput.Key('J') || mInput.Key(VK_LBUTTON))
		{
			//ジャンプ音
			mSoundJump.Play(0.1f);
			mVy = JUMPV0;
			mState = EState::EJUMP;
		}
	}
	//マウスカーソル座標取得
	float mouseX, mouseY;
	mInput.GetMousePosWin(&mouseX, &mouseY);
	//マウスカーソルが画面４０％より左なら左移動
	if (mInput.Key('A'))// || mouseX < WINDOW_WIDTH * 0.4f)
	{
		mVx = -VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	//マウスカーソルが画面５０％より右なら右移動
	if (mInput.Key('D'))// || WINDOW_WIDTH * 0.5f < mouseX)
	{
		mVx = VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	//Y座標にY軸速度を加える
	Y(Y() + mVy);
	//Y軸速度に重力を減算する
	mVy -= GRAVITY;

	if (mInvincible > 0)
	{
		mState = EState::ECRY;
	}
	if (mState == EState::ECRY)
	{
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
	}
	else
	{
		const int PITCH = 32;//画像を切り替える間隔
		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き１を設定
				Texture(Texture(), TEXLEFT1);
			}
			else
			{
				//通常の画像を設定
				Texture(Texture(), TEXCOORD);
			}
		}
		else
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き2を設定
				Texture(Texture(), TEXLEFT2);
			}
			else
			{
				//2番目の画像を設定
				Texture(Texture(), TEXCOORD2);
			}
		}
	}
	Texture(Texture(), TEXCOORD);
}
