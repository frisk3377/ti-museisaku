#include <Novice.h>
#include <time.h>


const char kWindowTitle[] = "LC1B_セノフウキチ_タイトル";


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	Novice::Initialize(kWindowTitle, 800, 800);

	/*座標*/
	struct vector2 {
		float x;
		float y;
	};

	struct vector {
		int x;
		int y;
	};

	struct Player
	{
		vector2 pos;
		vector2 velocity;
		vector2 acceleration;
		float rad;
		unsigned int color;
	};

	Player player = {
		{360,0},
		{0,0},
		{0,0},
		150,
		WHITE
	};


	struct vector firstBackground {//一番下の背景画像の座標
		0,
			0
	};

	struct vector background1 = {//背景画像の座標
		0,
		-2400
	};

	struct vector background2 = {//ループに使う二枚目の座標
		0,
		-4800
	};

	/*シーン管理*/
	enum GameManager {
		TITLE, //タイトル画面
		INFORMATION,//操作説明
		PLAY,  //ゲーム画面
		RESULT //リザルト画面
	};


	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int playerFootPosY = 0;


	int gameTimer = 0; //プレイ中の時間制限

	int playerCount = 1; //どっちを向いているかの判定用
	int imageCount = 0; //画像の切り替え用
	int imageCount2 = 0;//画像の切り替え用
	int imageTimer = 0; //画像の切り替え用
	int imageTimer2 = 0; //画像の切り替え用

	int timeTen = 3; //１０の位
	int timeOne = 0; //１の位
	int timeCount = 0;
	int timeCount2 = 0;

	int screenY = 0;
	int scroll = 0;

	int footholdPosX[100] = { 0 };
	int footholdPosY[100] = { 0 };

	unsigned int currentTime;

	//int tier1 = false;
	/*/int tier2 = false;
	int tier3 = false;
	int tier4 = false;
	int tier5 = false;
	int tier6 = false;
	int tier7 = false;
	int tier8 = false;
	int tier9 = false;
	int tier10 = false;
	int tier11 = false;
	int tier12 = false;
	int tier13 = false;*/

	int asiba = false;

	int asibanifureteruka0 = false;
	int asibanifureteruka1 = false;
	int asibanifureteruka2 = false;
	int asibanifureteruka3 = false;
	int asibanifureteruka4 = false;
	int asibanifureteruka5 = false;
	int asibanifureteruka6 = false;
	int asibanifureteruka7 = false;
	int asibanifureteruka8 = false;
	int asibanifureteruka9 = false;

	/*リソースの読み込み*/

	//キャラ画像//
	int playerImage[2][6];

	//左向きのキャラ画像
	playerImage[0][0] = Novice::LoadTexture("./PlayerRun1.1.png");
	playerImage[0][1] = Novice::LoadTexture("./PlayerRun1.2.png");
	playerImage[0][2] = Novice::LoadTexture("./PlayerRun1.3.png");
	playerImage[0][3] = Novice::LoadTexture("./PlayerRun1.4.png");
	playerImage[0][4] = Novice::LoadTexture("./PlayerRun1.5.png");
	playerImage[0][5] = Novice::LoadTexture("./PlayerRun1.6.png");

	//右向きのキャラ画像
	playerImage[1][0] = Novice::LoadTexture("./PlayerRun2.1.png");
	playerImage[1][1] = Novice::LoadTexture("./PlayerRun2.2.png");
	playerImage[1][2] = Novice::LoadTexture("./PlayerRun2.3.png");
	playerImage[1][3] = Novice::LoadTexture("./PlayerRun2.4.png");
	playerImage[1][4] = Novice::LoadTexture("./PlayerRun2.5.png");
	playerImage[1][5] = Novice::LoadTexture("./PlayerRun2.6.png");

	//タイトル画面
	int titleImage[7];
	//int titleTelop = Novice::LoadTexture("./TitleTelop.png");

	titleImage[0] = Novice::LoadTexture("./Title1.png");
	titleImage[1] = Novice::LoadTexture("./Title2.png");
	titleImage[2] = Novice::LoadTexture("./Title3.png");
	titleImage[3] = Novice::LoadTexture("./Title4.png");
	titleImage[4] = Novice::LoadTexture("./Title5.png");
	titleImage[5] = Novice::LoadTexture("./Title6.png");
	titleImage[6] = Novice::LoadTexture("./Title7.png");

	//数字画像
	int numberImage[10];
	//int mImage = Novice::LoadTexture("./m.png");

	numberImage[0] = Novice::LoadTexture("./0.png");
	numberImage[1] = Novice::LoadTexture("./1.png");
	numberImage[2] = Novice::LoadTexture("./2.png");
	numberImage[3] = Novice::LoadTexture("./3.png");
	numberImage[4] = Novice::LoadTexture("./4.png");
	numberImage[5] = Novice::LoadTexture("./5.png");
	numberImage[6] = Novice::LoadTexture("./6.png");
	numberImage[7] = Novice::LoadTexture("./7.png");
	numberImage[8] = Novice::LoadTexture("./8.png");
	numberImage[9] = Novice::LoadTexture("./9.png");

	//足場画像
	int footholdImage = Novice::LoadTexture("./scaffold.png");


	//説明画面
	int infoImage = Novice::LoadTexture("./info.png");

	//リザルト画面　

	int result = Novice::LoadTexture("./Result.png");

	//背景画像
	int firstBackgroundImage = Novice::LoadTexture("./firstBackground.png");
	int backgroundImage = Novice::LoadTexture("./background.png");

	int testo = 0;

	GameManager gameManager = TITLE; //シーン管理

	int speed = 8; //プレイヤーのスピード


	while (Novice::ProcessMessage() == 0) {

		Novice::BeginFrame();



		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		switch (gameManager) {

		case TITLE:
			///
			/// ↓更新処理ここから
			///

			//時間制限の初期化
			timeTen = 3; //１０の位
			timeOne = 0; //１の位
			timeCount = 9;
			timeCount2 = 0;

			//背景の位置の初期化
			firstBackground.y = 0;
			background1.y = -2400;
			background2.y = -4800;


			imageTimer += 1;

			/*タイトルの描画*/
			if (imageTimer >= 10) {
				if (imageCount < 7) {
					imageCount += 1;
					imageTimer = 0;
				};
				if (imageCount == 7) {
					imageCount = 0;
					imageTimer = 0;
				};
			};

			/*エンターを押したら説明画面に行く*/
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				gameManager = INFORMATION;
			}


			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, titleImage[imageCount], 1, 1, 0.0f, 0xFFFFFFFF);
			///
			/// ↑描画処理ここまで
			///

			break;
		case INFORMATION:
			///
			/// ↓更新処理ここから
			///

			/*シード値の選出*/

			currentTime = (int)time(nullptr);
			srand(currentTime);

			for (int i = 0; i <= 99; i++) {
				footholdPosX[i] = rand() % 400 + 100;
			}

			/*足場の位置の初期化*/
			footholdPosY[0] = 414;

			for (int i = 1; i <= 99; i++) {
				footholdPosY[i] = footholdPosY[i - 1] - 200;
			}



			/*エンターを押したらゲームが始まる*/
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				gameManager = PLAY;
			}

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, infoImage, 1, 1, 0.0f, 0xFFFFFFFF);
			///
			/// ↑描画処理ここまで
			///
			/// 
			break;


		case PLAY:
			///
			/// ↓更新処理ここから
			///

			/*ゲームの制限時間の管理*/
			gameTimer += 1;
			imageTimer2 += 1;

			/*プレイヤーの描画関係*/
			if (imageTimer2 >= 10) {
				if (imageCount2 < 6) {
					imageCount2 += 1;
					imageTimer2 = 0;
				};
				if (imageCount2 == 6) {
					imageCount2 = 0;
					imageTimer2 = 0;
				};
			};





			/*----------------------プレイヤーの移動処理--------------------*/

			player.pos.x = player.pos.x + speed;

			if (player.pos.x >= 590)
			{
				speed = speed * -1;
				playerCount = 0;
			}

			if (player.pos.x <= 100)
			{
				speed = speed * -1;
				playerCount = 1;
			}

			/*スペースでジャンプ、落下の運動*/
			if (asibanifureteruka0 or asibanifureteruka1 or asibanifureteruka2 or asibanifureteruka3 or asibanifureteruka4 or asibanifureteruka5 or asibanifureteruka6 or asibanifureteruka7 or asibanifureteruka8 or asibanifureteruka9) {
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					player.velocity.y = 0;
					player.acceleration.y = 0;
					player.velocity.y = 20.0f;
					player.acceleration.y = -0.8f;
					asibanifureteruka0 = false;
					asibanifureteruka1 = false;
					asibanifureteruka2 = false;
					asibanifureteruka3 = false;
					asibanifureteruka4 = false;
					asibanifureteruka5 = false;
					asibanifureteruka6 = false;
					asibanifureteruka7 = false;
					asibanifureteruka8 = false;
					asibanifureteruka9 = false;
				}
			}
			if (asibanifureteruka0 == false && asibanifureteruka1 == false && asibanifureteruka2 == false && asibanifureteruka3 == false && asibanifureteruka4 == false && asibanifureteruka5 == false && asibanifureteruka6 == false && asibanifureteruka7 == false && asibanifureteruka8 == false && asibanifureteruka9 == false) {
				player.velocity.x += player.acceleration.x;
				player.velocity.y += player.acceleration.y;

 				player.pos.x += player.velocity.x;
				if (player.velocity.y <= -10) {
					player.velocity.y = -10;
				}

				player.pos.y += player.velocity.y;

				if (player.pos.y <= player.rad) {
					player.pos.y = player.rad;
				}
			}

			screenY = int(player.pos.y);//座標変換
			screenY -= 764;
			screenY *= -1;

			/*-----------------------------------------------------------*/

			/*---------------------画面のスクロール------------------------*/

			scroll = -screenY;

			background1.y = scroll - 1786;
			background2.y = scroll - 4186;
			firstBackground.y = scroll + 614;

			//足場のスクロール
			footholdPosY[0] = firstBackground.y + 414;
			footholdPosY[1] = firstBackground.y + 214;
			footholdPosY[2] = firstBackground.y + 14;
			footholdPosY[3] = firstBackground.y - 214;
			footholdPosY[4] = firstBackground.y - 414;
			footholdPosY[5] = firstBackground.y - 614;
			footholdPosY[6] = firstBackground.y - 814;
			footholdPosY[7] = firstBackground.y - 1014;
			footholdPosY[8] = firstBackground.y - 1214;
			footholdPosY[9] = firstBackground.y - 1414;

			/*----------------------------------------------------------*/

			/*--------------------------足場の当たり判定--------------------*/

			playerFootPosY = screenY + 150;

			if (player.velocity.y <0 ) {
				asiba = true;
				testo += 1;
			} else
			{
				asiba = false;
			}

			if (playerFootPosY >= 764) {
				asibanifureteruka0 = true;
			}





			if (asiba) {
				if (footholdPosY[0] <= playerFootPosY && playerFootPosY <= footholdPosY[0] + 30 && player.pos.x <= footholdPosX[0] + 200 && player.pos.x + 80 >= footholdPosX[0]) {
					asibanifureteruka1 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka1 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[1] <= playerFootPosY && playerFootPosY <= footholdPosY[1] + 30 && player.pos.x <= footholdPosX[1] + 200 && player.pos.x + 80 >= footholdPosX[1]) {
					asibanifureteruka2 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka2 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[2] <= playerFootPosY && playerFootPosY <= footholdPosY[2] + 30 && player.pos.x <= footholdPosX[2] + 200 && player.pos.x + 80 >= footholdPosX[2]) {
					asibanifureteruka3 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka3 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[3] <= playerFootPosY && playerFootPosY <= footholdPosY[3] + 30 && player.pos.x <= footholdPosX[3] + 200 && player.pos.x + 80 >= footholdPosX[3  ]) {
					asibanifureteruka4 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka4 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[4] <= playerFootPosY && playerFootPosY <= footholdPosY[4] + 30 && player.pos.x <= footholdPosX[4] + 200 && player.pos.x + 80 >= footholdPosX[4]) {
					asibanifureteruka5 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka5 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[5] <= playerFootPosY && playerFootPosY <= footholdPosY[5] + 30 && player.pos.x <= footholdPosX[5] + 200 && player.pos.x + 80 >= footholdPosX[5]) {
					asibanifureteruka6 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka6 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[6] <= playerFootPosY && playerFootPosY <= footholdPosY[6] + 30 && player.pos.x <= footholdPosX[6] + 200 && player.pos.x + 80 >= footholdPosX[6]) {
					asibanifureteruka7 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka7 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[7] <= playerFootPosY && playerFootPosY <= footholdPosY[7] + 30 && player.pos.x <= footholdPosX[7] + 200 && player.pos.x + 80 >= footholdPosX[7]) {
					asibanifureteruka8 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka8 = false;
				}
			}

			if (asiba) {
				if (footholdPosY[9] <= playerFootPosY && playerFootPosY <= footholdPosY[9] + 30 && player.pos.x <= footholdPosX[9] + 200 && player.pos.x + 80 >= footholdPosX[9]) {
					asibanifureteruka9 = true;
					player.acceleration.y = 0;
				} else
				{
					asibanifureteruka9 = false;
				}
			}

			/*-----------------------------------------------------------*/

			/*------------------------制限時間の計算----------------------*/

			//位置の位の計算
			if (gameTimer >= 60) {
				timeOne -= 1;
				timeCount += 1;
				timeCount2 += 1;
				gameTimer = 0;
				if (timeOne == -1) {
					timeOne = 9;
				}
			}

			//十の位
			if (timeCount >= 10) {
				timeTen -= 1;
				timeCount = 0;
			}

			//３０秒たったらゲームが終了する
			if (timeCount2 >= 30) {
				gameManager = RESULT;
			}

			/*----------------------------------------------------------*/

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///

			/*背景の描画*/
			Novice::DrawSprite((int)background1.x, (int)background1.y, (int)backgroundImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)background2.x, (int)background2.y, (int)backgroundImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)firstBackground.x, (int)firstBackground.y, (int)firstBackgroundImage, 1, 1, 0.0f, 0xFFFFFFFF);

			/*プレイヤーの描画*/
			Novice::DrawSprite((int)player.pos.x, screenY, playerImage[playerCount][imageCount2], 1, 1, 0.0f, 0xFFFFFFFF);

			/*制限時間の描画*/
			Novice::DrawSprite(0, 0, numberImage[timeTen], 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(64, 0, numberImage[timeOne], 1, 1, 0.0f, 0xFFFFFFFF);

			/*テスト*/
			Novice::ScreenPrintf(50, 50, "%d", testo);

			/*足場の描画*/
			Novice::DrawSprite((int)footholdPosX[0], footholdPosY[0], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[1], footholdPosY[1], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[2], footholdPosY[2], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[3], footholdPosY[3], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[4], footholdPosY[4], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[5], footholdPosY[5], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[6], footholdPosY[6], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[7], footholdPosY[7], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[8], footholdPosY[8], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[9], footholdPosY[9], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[10], footholdPosY[10], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			/*Novice::DrawSprite((int)footholdPosX[11], footholdPosY[11], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[12], footholdPosY[12], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[13], footholdPosY[13], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[14], footholdPosY[14], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[15], footholdPosY[15], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[16], footholdPosY[16], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[17], footholdPosY[17], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[18], footholdPosY[18], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[19], footholdPosY[19], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[20], footholdPosY[20], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[21], footholdPosY[21], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[22], footholdPosY[22], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[23], footholdPosY[23], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[24], footholdPosY[24], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[25], footholdPosY[25], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[26], footholdPosY[26], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[27], footholdPosY[27], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[28], footholdPosY[28], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[29], footholdPosY[29], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[30], footholdPosY[30], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[31], footholdPosY[31], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[32], footholdPosY[32], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[33], footholdPosY[33], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[34], footholdPosY[34], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[35], footholdPosY[35], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[36], footholdPosY[36], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[37], footholdPosY[37], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[38], footholdPosY[38], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[39], footholdPosY[39], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[40], footholdPosY[40], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[41], footholdPosY[41], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[42], footholdPosY[42], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[43], footholdPosY[43], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[44], footholdPosY[44], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[45], footholdPosY[45], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[46], footholdPosY[46], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[47], footholdPosY[47], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[48], footholdPosY[48], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[49], footholdPosY[49], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[50], footholdPosY[50], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[51], footholdPosY[51], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[52], footholdPosY[52], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[53], footholdPosY[53], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[54], footholdPosY[54], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[55], footholdPosY[55], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[56], footholdPosY[56], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[57], footholdPosY[57], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[58], footholdPosY[58], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[59], footholdPosY[59], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[60], footholdPosY[60], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[61], footholdPosY[61], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[62], footholdPosY[62], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[63], footholdPosY[63], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[64], footholdPosY[64], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[65], footholdPosY[65], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[66], footholdPosY[66], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[67], footholdPosY[67], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[68], footholdPosY[68], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[69], footholdPosY[69], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[70], footholdPosY[70], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[71], footholdPosY[71], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[72], footholdPosY[72], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[73], footholdPosY[73], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[74], footholdPosY[74], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[75], footholdPosY[75], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[76], footholdPosY[76], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[77], footholdPosY[77], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[78], footholdPosY[78], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[79], footholdPosY[79], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[80], footholdPosY[80], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[81], footholdPosY[81], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[82], footholdPosY[82], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[83], footholdPosY[83], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[84], footholdPosY[84], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[85], footholdPosY[85], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[86], footholdPosY[86], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[87], footholdPosY[87], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[88], footholdPosY[88], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[89], footholdPosY[89], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[90], footholdPosY[90], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[91], footholdPosY[91], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[92], footholdPosY[92], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[93], footholdPosY[93], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[94], footholdPosY[94], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[95], footholdPosY[95], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[96], footholdPosY[96], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[97], footholdPosY[97], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[98], footholdPosY[98], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite((int)footholdPosX[99], footholdPosY[99], footholdImage, 1, 1, 0.0f, 0xFFFFFFFF);
			*/
			///
			/// ↑描画処理ここまで
			///

			break;

		case RESULT:
			///
			/// ↓更新処理ここから
			///
				/*エンターを押したら説明画面に行く*/
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				gameManager = TITLE;
			}
			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, result, 1, 1, 0.0f, 0xFFFFFFFF);
			///
			/// ↑描画処理ここまで
			///
			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
