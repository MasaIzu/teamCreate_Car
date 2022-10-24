#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
}

void GameScene::Initialize() {
	srand(time(nullptr));
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//３Dモデルの生成
	model_ = Model::Create();

	// プレイヤーのnew
	player_ = new Player();

	// 敵の生成のnew
	enemyPop_ = new EnemyPop();
	enemy_ = new Enemy();
	enemyPop_->Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye.y += 70;
	viewProjection_.eye.z -= 80;
	viewProjection_.target.y += 0;
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//道路生成
	loadModel_ = Model::CreateFromOBJ("load", true);
	load_ = new Load();
	load_->Initialize(loadModel_);

	//背景生成
	groundRightModel_ = Model::CreateFromOBJ("BackGroundRight", true);
	groundLeftModel_ = Model::CreateFromOBJ("BackGroundLeft", true);

	backGround_ = new BackGround();
	backGround_->Initialize(groundRightModel_, groundLeftModel_);

	//風生成
	wingModel_ = Model::CreateFromOBJ("wing", true);
	wing_ = new Wing();
	wing_->Initialize(wingModel_);

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void GameScene::Update() {

	debugCamera_->Update();

	player_->SetOverTakingCount(enemyPop_->GetEnemyOverTakingCount());
	player_->Updata();

	enemyPop_->SetPlayer(player_);
	enemyPop_->SetWing(wing_);
	enemyPop_->Update(model_);
	

	//道路更新
	load_->Update(player_->GetPlayerSpeed());
	//背景更新
	backGround_->Update(player_->GetPlayerSpeed());

	//風更新
	wing_->Update(player_->GetPlayerPos());

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	//背景描画
	backGround_->Draw(viewProjection_);

	//道路描画
	load_->Draw(viewProjection_);

	//風描画
	wing_->Draw(viewProjection_);
	
	// プレイヤーの描画
	player_->Draw(viewProjection_);

	// 敵の描画
	enemyPop_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
