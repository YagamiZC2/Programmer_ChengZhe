# include <Siv3D.hpp> // Siv3D v0.6.14
#include "particle_square.h"
#include "particle_circle.h"

#include "emitter.h"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(Palette::Black);
	//ParticleSquare ps({ 200.0f,200.0f }, {0.0f,0.0f }, { 1.0f, 5.0f, 0.1f,1.0f }, 60 * 3);
	//ParticleCircle pc({ 220.0f,200.0f }, { 0.0f,0.0f }, { 0.0f, 1.0f, 0.0f,1.0f }, 60 * 3);
	emitter emt(10000, 20, { 400.0f, 400.0f }, { 0.01f,0.01f }, { 0.001f,0.001f });
	emitter emtx(5000, 1, { 100.f, 100.0f }, { 0.01f,0.01f }, { 0.001f,0.001f });

	while (System::Update())
	{
		//ps.AddForce({ 0.0f, -0.001f });
		//ps.Update();
		//pc.Update();

		//ps.Draw();
		//pc.Draw();
		emt.SetPosition(Cursor::Pos());
		emt.addForce({ 0.0f,0.0f });
		emt.Update();
		emt.Draw();

		const double t = Scene::Time();

		for (auto i : step(6))
		{
			// 円座標系における角度座標
			// 60° ごとに配置し、毎秒 30° の速さで回転する
			const double theta = (i * 60_deg + t * 30_deg);

			const Vec2 pos = OffsetCircular{ Scene::Center(), 200, theta };

			emtx.SetPosition(pos);
		}

		emtx.Update();
		emtx.Draw();

	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
