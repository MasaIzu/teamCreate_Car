#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>

float PI = 3.141592f;

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
	viewProjection_.target.y += 2;
	gamePlayCameraPos = viewProjection_.eye;
	cameraMoveFlag = 0;
	Timer = 130;

	//カメラの位置替え
	viewProjection_.eye = { -70,63,-80 };
	keepCamera = viewProjection_.eye;
	cameraTransFlag = 0;
	cameraSpeed = { 1.0f, 1.0f, 1.0f };

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

	//クリアのテクスチャ
	uint32_t result = TextureManager::Load("TitleCar.png");
	spriteResult.reset(
		Sprite::Create(result, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteResult->SetSize(Vector2(800.0f, 600.0f));

	//スタートのカウントののテクスチャ
	uint32_t  stertCount = TextureManager::Load("stert321.png");
	for (int i = 0; i < 3; i++) {
		spriteStertTime[i].reset(
			Sprite::Create(stertCount, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
		spriteStertTime[i]->SetTextureRect(Vector2(256 - (128 * i), 0), Vector2(128, 192));
		spriteStertTime[i]->SetSize(Vector2(128, 128));
	}

	//クリアのテクスチャ
	uint32_t meter = TextureManager::Load("meter.png");
	spriteMeter.reset(
		Sprite::Create(meter, Vector2(1180, 620), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteMeter->SetSize(Vector2(200, 200));

	//針のテクスチャ
	uint32_t needle = TextureManager::Load("needle.png");
	spriteMeterNeedle.reset(
		Sprite::Create(needle, Vector2(1180, 620), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteMeterNeedle->SetSize(Vector2(7, 170));
	spriteMeterNeedle->SetRotation((PI / 180) * -150);

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void GameScene::Update() {

	if (cameraMoveFlag == 1) {
		if (Timer > 0) {
			Timer--;
		}
	}
	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		camera();
		//タイトルと背景自動移動
		load_->Demo();
		backGround_->Demo();
		if (Timer == 0) {
			scene_ = Scene::Stage;
		}
		break;
	case GameScene::Scene::Stage:

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

		if (player_->GetPlayerPos().z > enemyPop_->GetGoalEmemyPos()) {
			scene_ = Scene::Result;
		}
		break;
	case GameScene::Scene::Result:

		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

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

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Stage:
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);
		//風描画
		wing_->Draw(viewProjection_);
		// 敵の描画
		enemyPop_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Result:

		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:

		break;
	case GameScene::Scene::Stage:
		if (player_->GetTimer() > 0) {
			spriteStertTime[(player_->GetTimer() / 60)]->Draw();
		}
		spriteMeter->Draw();

		spriteMeterNeedle->SetRotation((((player_->GetKmH() / 400) * 240) - 150) * (PI / 180));
		spriteMeterNeedle->Draw();
		break;
	case GameScene::Scene::Result:
		spriteResult->Draw();
		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::camera() {
	if (cameraTransFlag == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraMoveFlag = 1;
			cameraTransFlag = 1;
		}
		if (keepCamera.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (keepCamera.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (keepCamera.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (keepCamera.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (keepCamera.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (keepCamera.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}
	else if (cameraTransFlag == 1) {
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraTransFlag = 0;
		}
		if (gamePlayCameraPos.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (gamePlayCameraPos.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (gamePlayCameraPos.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (gamePlayCameraPos.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (gamePlayCameraPos.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (gamePlayCameraPos.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}