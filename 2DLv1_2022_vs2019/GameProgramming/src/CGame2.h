#pragma once
#include "CUi.h"
#include "CPlayer3.h"

//定数の定義
#define TEXTURE "image.png" //テクスチャのファイル名
#define TIPSIZE 20.0f //マップ要素のサイズ
/*
* CGameクラス
* ゲームクラス
* ゲームのマップを作成し、
* キャラクタを配置する
*/
class CGame2
{
public:
	//デストラクタ
	~CGame2();
	//ゲームクリア判定
	bool IsClear();
	//ゲームクリア処理
	void Clear();
	//ゲームオーバー判定
	bool IsOver();
	//ゲームオーバー処理
	void Over();
	//スタート処理
	void Start();
	CGame2(); //デフォルトコンストラクタ（初期処理）
	void Update(); //更新処理
private:
	int mCdx, mCdy; //カメラとプレイヤーの座標の差分
	void CameraSet(); //カメラ設定
	CPlayer3* mpPlayer; //プレイヤーのポインタ
	int mTime; //経過時間
	CUi* mpUi; //UIクラスのポインタ
};
