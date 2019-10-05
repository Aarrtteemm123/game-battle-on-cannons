
// run only through debugger!
// Release x64
// put on desktop SFML-2.5.0
// How connect SFML-2.5.0 to project https://www.youtube.com/watch?v=4fPBAYu8PFs&t=521s

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>

using namespace sf;
using namespace std;

float volume_music_menu = 0;
float bullet_place_stop = 0;

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1000, 800), "My game!", Style::Fullscreen);

	Texture menu_texture;
	menu_texture.loadFromFile("images/menu.jpg");

	Sprite menu;
	menu.setTexture(menu_texture);

	Music music_menu, music_menu_game_over, music_menu_game_win, music_shoot, music_damage, music_damage2;
	music_menu.openFromFile("music/menu.ogg");
	music_menu_game_win.openFromFile("music/game_win.ogg");
	music_menu_game_over.openFromFile("music/game_over.ogg");
	music_shoot.openFromFile("music/shoot.ogg");
	music_damage.openFromFile("music/damage.ogg");
	music_damage2.openFromFile("music/damage2.ogg");
	music_menu.play();
	music_menu.setVolume(volume_music_menu);
	music_menu.setLoop(true);

	Font font_game, font_title;
	font_game.loadFromFile("font/game.ttf");
	font_title.loadFromFile("font/title.ttf");

	Text Button_exit("Exit", font_game, 100);
	Button_exit.setPosition(160, 600);

	Text Button_info("Info", font_game, 100);
	Button_info.setPosition(160, 450);

	Text Button_start("Start", font_game, 100);
	Button_start.setPosition(160, 300);

	Text Title("Battle On Cannons ", font_title, 180);
	Title.setPosition(310, 30);

	float num_button_menu = 0;

	while (window.isOpen())
	{
		music_menu.setVolume(volume_music_menu);
		Button_start.setFillColor(Color::White);
		Button_info.setFillColor(Color::White);
		Button_exit.setFillColor(Color::White);

		if (IntRect(160, 335, 180, 70).contains(Mouse::getPosition(window)))
		{
			Button_start.setFillColor(Color::Blue);
			num_button_menu = 1;
		}
		if (IntRect(160, 490, 150, 70).contains(Mouse::getPosition(window)))
		{
			num_button_menu = 2;
			Button_info.setFillColor(Color::Blue);
		}
		if (IntRect(160, 635, 160, 70).contains(Mouse::getPosition(window)))
		{
			num_button_menu = 3;
			Button_exit.setFillColor(Color::Blue);
		}
		if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 1)
		{
			music_menu.pause();
			volume_music_menu = 0;

			Image cannon_image, cannon2_image, heart_image;
			cannon2_image.loadFromFile("images/cannon2.jpg");
			cannon_image.loadFromFile("images/cannon.jpg");
			heart_image.loadFromFile("images/heart.jpg");

			cannon_image.createMaskFromColor(Color(255, 255, 255));
			cannon2_image.createMaskFromColor(Color(255, 255, 255));
			heart_image.createMaskFromColor(Color(0, 0, 0));

			Texture map_tex, rust_tex, old_metal_tex, stone_tex, metal_tex, cannon_tex, cannon2_tex, black_tex, heart_tex;
			map_tex.loadFromFile("images/map.jpg");
			rust_tex.loadFromFile("images/rust.jpg");
			old_metal_tex.loadFromFile("images/old_metal.jpg");
			stone_tex.loadFromFile("images/stone.jpg");
			metal_tex.loadFromFile("images/metal.jpg");
			black_tex.loadFromFile("images/black.jpg");
			cannon_tex.loadFromImage(cannon_image);
			cannon2_tex.loadFromImage(cannon2_image);
			heart_tex.loadFromImage(heart_image);

			Sprite map, cannon, cannon2, heart2, heart;
			heart2.setTexture(heart_tex);
			heart2.scale(Vector2f(0.05f, 0.05f));
			heart.setTexture(heart_tex);
			heart.scale(Vector2f(0.05f, 0.05f));
			heart.setPosition(20, 20);
			heart2.setPosition(1860, 20);
			map.setTexture(map_tex);
			cannon.setTexture(cannon_tex);
			cannon.setPosition(1820, 785);
			cannon.scale(Vector2f(0.1f, 0.1f));
			cannon2.setTexture(cannon2_tex);
			cannon2.setPosition(100, 790);
			cannon2.scale(Vector2f(0.1f, 0.1f));

			Text Button_finish("Finish", font_title, 60);
			Button_finish.setPosition(880, 900);

			Text z("z", font_game, 40);
			Text x("x", font_game, 40);
			Text c("c", font_game, 40);
			Text v("v", font_game, 40);

			z.setPosition(795, 955);
			x.setPosition(887, 955);
			c.setPosition(988, 955);
			v.setPosition(1077, 955);

			z.setFillColor(Color::Yellow);
			x.setFillColor(Color::Yellow);
			c.setFillColor(Color::Yellow);
			v.setFillColor(Color::Yellow);

			RectangleShape panel(Vector2f(400, 150));
			RectangleShape hp(Vector2f(250, 20));
			RectangleShape hp2(Vector2f(250, 20));
			hp.setFillColor(Color::Color(255, 69, 0));
			hp.setPosition(1603, 25);
			hp2.setFillColor(Color::Color(255, 69, 0));
			hp2.setPosition(65, 25);

			panel.setFillColor(Color::Color(105, 105, 105));
			panel.setOutlineThickness(10);
			panel.setOutlineColor(Color::Color(250, 150, 100));
			panel.setPosition(750, 900);

			CircleShape bullet_rust(15, 500);
			CircleShape bullet_old_metal(15, 500);
			CircleShape bullet_stone(15, 500);
			CircleShape bullet_metal(15, 500);
			CircleShape bullet(10, 500);

			bullet_rust.setPosition(790, 1010);
			bullet_old_metal.setPosition(880, 1010);
			bullet_stone.setPosition(980, 1010);
			bullet_metal.setPosition(1070, 1010);
			bullet.setPosition(-50, 0);

			bullet_rust.setTexture(&rust_tex);
			bullet_old_metal.setTexture(&old_metal_tex);
			bullet_stone.setTexture(&stone_tex);
			bullet_metal.setTexture(&metal_tex);

			bullet.setTexture(&black_tex);
			bool finish = false;
			bool step = false;
			bool damage = false;
			bool shoot = true;
			bool bullet_stop = false;
			double MouseX, MouseY, angle, distance;
			Sleep(100);

			do
			{
				shoot = true;//щоб п≥сл€ натисненн€ ф≥н≥ш не було ще одного вистр≥лу
				step = false;
				music_shoot.stop();

				do
				{
					//х≥д гравц€
					cannon.setOrigin(790, 678);//в≥сь обертанн€ 1 пушки
					shoot = true;
					Vector2f hp2_size;
					hp2_size = hp2.getSize();	//полоса здоров'€
					Vector2f hp_size;
					hp_size = hp.getSize();
					Vector2f hp_position;
					hp_position = hp.getPosition();
					bullet.setPosition(-100, 0);

					if (hp2_size.x <= 0)			//програш
					{
						music_damage2.stop();
						music_menu_game_over.play();
						bool back_menu = false;
						finish = true;
						step = true;
						window.clear();

						Texture menu_game_over_tex;
						menu_game_over_tex.loadFromFile("images/menu_game_over.jpg");

						Sprite menu_game_over;
						menu_game_over.setTexture(menu_game_over_tex);

						Text Button_back_menu("Back to menu", font_game, 100);
						Text game_over("GAME OVER !!!", font_game, 150);
						Button_back_menu.setPosition(700, 800);
						game_over.setPosition(495, 250);
						game_over.setFillColor(Color::Red);

						while (back_menu == false)
						{
							Button_back_menu.setFillColor(Color::Red);
							num_button_menu = 0;
							if (IntRect(700, 840, 510, 65).contains(Mouse::getPosition(window)))
							{
								num_button_menu = 6;
								Button_back_menu.setFillColor(Color::Blue);
							}
							if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 6)
							{
								back_menu = true;
								music_menu_game_over.stop();
							}
							Sleep(20);
							window.clear();
							window.draw(menu_game_over);
							window.draw(game_over);
							window.draw(Button_back_menu);
							window.display();
						}
					}

					if (hp_size.x <= 0)			//виграш
					{
						music_damage.stop();
						music_menu_game_win.play();
						bool back_menu = false;
						finish = true;
						step = true;
						window.clear();

						Texture menu_game_over_tex;
						menu_game_over_tex.loadFromFile("images/menu_game_over.jpg");

						Sprite menu_game_over;
						menu_game_over.setTexture(menu_game_over_tex);

						Text Button_back_menu("Back to menu", font_game, 100);
						Text game_over("YOU WIN !!!", font_game, 150);
						Button_back_menu.setPosition(700, 800);
						game_over.setPosition(610, 250);
						game_over.setFillColor(Color::Yellow);

						while (back_menu == false)
						{
							Button_back_menu.setFillColor(Color::Yellow);
							num_button_menu = 0;

							if (IntRect(700, 840, 510, 65).contains(Mouse::getPosition(window)))
							{
								num_button_menu = 7;
								Button_back_menu.setFillColor(Color::Blue);
							}
							if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 7)
							{
								back_menu = true;
								music_menu_game_win.stop();
							}

							Sleep(20);
							window.clear();
							window.draw(menu_game_over);
							window.draw(game_over);
							window.draw(Button_back_menu);
							window.display();
						}
					}

					if (hp_size.x > 0 && hp2_size.x > 0)
					{
						Vector2f pos_cannon2 = cannon2.getPosition();
						Vector2i pos_mouse = Mouse::getPosition(window);//забираем коорд курсора
						Vector2f pos_mouse_in_game = window.mapPixelToCoords(pos_mouse);//переводим их в игровые (уходим от коорд окна)
						MouseX = pos_mouse_in_game.x - pos_cannon2.x;
						MouseY = pos_mouse_in_game.y - pos_cannon2.y;
						cannon2.setOrigin(550, 680);   //центр обертанн€ пушки
						angle = (atan2(MouseY, MouseX) * 180 / 3.14159265) + 35;
						if (angle > 35)
							angle = 35;
						if (angle < -40)
							angle = -40;
						cannon2.setRotation(angle);
						distance = sqrt(MouseX*MouseX + MouseY * MouseY);
						Button_finish.setFillColor(Color::Yellow);
						num_button_menu = 0;

						if (IntRect(885, 920, 145, 42).contains(Mouse::getPosition(window)))
						{
							Button_finish.setFillColor(Color::Color(30, 144, 255));
							num_button_menu = 5;
						}
						if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 5) { finish = true; shoot = false; step = true; }
						if (Keyboard::isKeyPressed(Keyboard::Z)) { bullet.setTexture(&rust_tex); }
						if (Keyboard::isKeyPressed(Keyboard::X)) { bullet.setTexture(&old_metal_tex); }
						if (Keyboard::isKeyPressed(Keyboard::C)) { bullet.setTexture(&stone_tex); }
						if (Keyboard::isKeyPressed(Keyboard::V)) { bullet.setTexture(&metal_tex); }
						if (Mouse::isButtonPressed(Mouse::Left) && shoot == true)	//вистр≥л гравц€
						{
							damage = false;
							step = true;
							music_shoot.play();
							float bulletX = 80 + 60 * cos(angle*3.14159265 / 180);
							float bulletY = 740 + 60 * sin(angle*3.14159265 / 180);

							if (angle <= -35) { bulletX -= 25; bulletY += 10; }	//корекц≥€ снар€ду					
							if (angle < -30 && angle>-35) { bulletX -= 20; bulletY += 5; }
							if (angle < -25 && angle>-30) { bulletX -= 20; bulletY += 5; }
							if (angle < -20 && angle>-25) { bulletX -= 17.5; bulletY += 5; }
							if (angle < -15 && angle>-20) { bulletX -= 15; }
							if (angle < -10 && angle>-15) { bulletX -= 10; }
							if (angle < -5 && angle>-10) { bulletX -= 10; }
							if (angle < 0 && angle>-5) { bulletX -= 4; bulletY -= 5; }
							if (angle < 5 && angle>0) { bulletX -= 4; bulletY -= 2; }
							if (angle < 10 && angle>5) { bulletX += 2; bulletY -= 5; }
							if (angle < 15 && angle>10) { bulletX += 5; bulletY -= 2; }
							if (angle < 20 && angle>15) { bulletX += 5; bulletY -= 3; }
							if (angle < 25 && angle>20) { bulletX += 10; bulletY -= 4; }
							if (angle < 30 && angle>25) { bulletX += 13; bulletY -= 2; }
							if (angle <= 35 && angle > 30) { bulletX += 15; }

							float t0 = (15 * pos_mouse_in_game.y - 13430) / -790;
							float t = t0;

							while (bulletY < 790)	//пол≥т снар€ду
							{
								if (bulletX > 1950) { bulletY = 800; }
								bullet.setPosition(bulletX, bulletY);
								bulletX += distance / 100;
								bulletY -= t;
								t -= 0.1;

								if (bulletX > 1780 && bulletX < 1870 && bulletY > 740 && bulletY < 803 && damage == false)//перев≥рка попаданн€
								{
									music_damage.stop();
									music_shoot.stop();
									music_damage.play();
									damage = true;
									hp_size.x -= 0.1*sqrt(pow(distance / 100, 2) + pow(pos_mouse_in_game.y, 2));	//система урона
									hp.setSize(hp_size);
									hp_position.x += 0.1*sqrt(pow(distance / 100, 2) + pow(pos_mouse_in_game.y, 2));
									hp.setPosition(hp_position);
								}

								Sleep(8);
								window.clear();
								window.draw(map);
								window.draw(cannon);
								window.draw(cannon2);
								window.draw(panel);
								window.draw(bullet_rust);
								window.draw(bullet_old_metal);
								window.draw(bullet_stone);
								window.draw(bullet_metal);
								window.draw(Button_finish);
								window.draw(bullet);
								window.draw(heart);
								window.draw(heart2);
								window.draw(hp2);
								window.draw(hp);
								window.draw(z);
								window.draw(x);
								window.draw(c);
								window.draw(v);
								window.display();
							}
						}

						Sleep(15);
						window.clear();
						window.draw(map);
						window.draw(cannon);
						window.draw(cannon2);
						window.draw(panel);
						window.draw(bullet_rust);
						window.draw(bullet_old_metal);
						window.draw(bullet_stone);
						window.draw(bullet_metal);
						window.draw(Button_finish);
						window.draw(bullet);
						window.draw(heart);
						window.draw(heart2);
						window.draw(hp2);
						window.draw(hp);
						window.draw(z);
						window.draw(x);
						window.draw(c);
						window.draw(v);
						window.display();
					}

				} while (step == false);//х≥д гравц€

				Vector2f pos_bullet = bullet.getPosition();
				step = false;
				music_shoot.stop();

				if (finish == false)
				{
					do //х≥д бота
					{

						shoot = true;
						Vector2f hp2_size;
						hp2_size = hp2.getSize();	//полоса здоров'€
						Vector2f hp_size;
						hp_size = hp.getSize();
						Vector2f hp_position;
						hp_position = hp.getPosition();

						if (hp2_size.x <= 0)			//програш
						{
							music_damage2.stop();
							music_menu_game_over.play();
							bool back_menu = false;
							finish = true;
							step = true;
							window.clear();

							Texture menu_game_over_tex;
							menu_game_over_tex.loadFromFile("images/menu_game_over.jpg");

							Sprite menu_game_over;
							menu_game_over.setTexture(menu_game_over_tex);

							Text Button_back_menu("Back to menu", font_game, 100);
							Text game_over("GAME OVER !!!", font_game, 150);
							Button_back_menu.setPosition(700, 800);
							game_over.setPosition(495, 250);
							game_over.setFillColor(Color::Red);

							while (back_menu == false)
							{
								Button_back_menu.setFillColor(Color::Red);
								num_button_menu = 0;

								if (IntRect(700, 840, 510, 65).contains(Mouse::getPosition(window)))
								{
									num_button_menu = 6;
									Button_back_menu.setFillColor(Color::Blue);
								}
								if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 6)
								{
									back_menu = true;
									music_menu_game_over.stop();
								}

								Sleep(20);
								window.clear();
								window.draw(menu_game_over);
								window.draw(game_over);
								window.draw(Button_back_menu);
								window.display();
							}
						}

						if (hp_size.x <= 0)			//виграш
						{
							music_damage.stop();
							music_menu_game_win.play();
							bool back_menu = false;
							finish = true;
							step = true;
							window.clear();

							Texture menu_game_over_tex;
							menu_game_over_tex.loadFromFile("images/menu_game_over.jpg");

							Sprite menu_game_over;
							menu_game_over.setTexture(menu_game_over_tex);

							Text Button_back_menu("Back to menu", font_game, 100);
							Text game_over("YOU WIN !!!", font_game, 150);
							Button_back_menu.setPosition(700, 800);
							game_over.setPosition(610, 250);
							game_over.setFillColor(Color::Yellow);

							while (back_menu == false)
							{
								Button_back_menu.setFillColor(Color::Yellow);
								num_button_menu = 0;

								if (IntRect(700, 840, 510, 65).contains(Mouse::getPosition(window)))
								{
									num_button_menu = 7;
									Button_back_menu.setFillColor(Color::Blue);
								}
								if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 7)
								{
									back_menu = true;
									music_menu_game_win.stop();
								}

								Sleep(20);
								window.clear();
								window.draw(menu_game_over);
								window.draw(game_over);
								window.draw(Button_back_menu);
								window.display();
							}
						}

						if (hp_size.x > 0 && hp2_size.x > 0)
						{
							step = true;
							Vector2f pos_cannon = cannon.getPosition();
							Vector2f pos_mouse_in_game;
							bullet.setPosition(-100, 0);
							int random;//ймов≥рн≥сть
							random = rand() % 5;

							if (bullet_stop == false)//початкова точн≥сть вистр≥лу
							{
								bullet_stop = true;
								bullet_place_stop = pos_cannon.x;
							}

							if (random < 3)	//стр≥л€Ї точн≥ше
							{
								float bullet_place_stop_temp = 0;

								do
								{
									pos_mouse_in_game.x = rand() % 1920;
									angle = rand() % 70 - 35;//(-35...35)

									MouseX = MouseY = 0;
									MouseX = pos_cannon.x - pos_mouse_in_game.x;
									MouseY = MouseX * tan(3.14159265 / 180 * (angle));
									pos_mouse_in_game.y = pos_cannon.y - MouseY;


									float t0 = (13430 - 14 * pos_mouse_in_game.y) / 790;
									float t = t0;
									float bulletX = 1820 - 53.5 * cos(angle*3.14159265 / 180);
									float bulletY = 732 + 53.5 * sin(angle*3.14159265 / 180);
									distance = sqrt(MouseX*MouseX + MouseY * MouseY);


									if (angle <= -30 && angle > -35) { bulletX -= 40; bulletY += 60; }	//корекц≥€ снар€ду
									if (angle <= -25 && angle > -30) { bulletX -= 30; bulletY += 60; }
									if (angle <= -20 && angle > -25) { bulletX -= 20; bulletY += 50; }
									if (angle <= -15 && angle > -20) { bulletX -= 20; bulletY += 40; }
									if (angle <= -10 && angle > -15) { bulletY += 23; }
									if (angle <= -5 && angle > -10) { bulletY += 10; }
									if (angle <= 0 && angle > -5) { bulletX -= 5; bulletY += 10; }
									if (angle <= 5 && angle > 0) { bulletX -= 4; bulletY -= 2; }
									if (angle <= 10 && angle > 5) { bulletX += 2; bulletY -= 5; }
									if (angle <= 15 && angle > 10) { bulletX += 5; bulletY -= 14; }
									if (angle <= 20 && angle > 15) { bulletX += 5; bulletY -= 24; }
									if (angle <= 25 && angle > 20) { bulletX += 5; bulletY -= 35; }
									if (angle <= 30 && angle > 25) { bulletX += 8; bulletY -= 40; }
									if (angle <= 35 && angle > 30) { bulletX += 10; bulletY -= 60; }

									while (bulletY < 800)	//пол≥т снар€ду теоретичний
									{
										bullet.setPosition(bulletX, bulletY);
										bulletX -= distance / 100;
										bulletY -= t;
										t -= 0.1;
									}

									bullet_place_stop_temp = bulletX;

								} while (bullet_place_stop_temp < -1 * bullet_place_stop || bullet_place_stop_temp > bullet_place_stop);

								if (fabs(bullet_place_stop_temp) < 50)
								{
									bullet_place_stop_temp = 200;
								}

								bullet.setPosition(-100, 0);
								bullet_place_stop = fabs(bullet_place_stop_temp);
								pos_mouse_in_game.y = pos_cannon.y - MouseY;
								distance = sqrt(MouseX*MouseX + MouseY * MouseY);

								float t0 = (13430 - 14 * pos_mouse_in_game.y) / 790;
								float t = t0;
								float temp_angle = 35;
								float bulletX = 1820 - 53.5 * cos(angle*3.14159265 / 180);
								float bulletY = 732 + 53.5 * sin(angle*3.14159265 / 180);
								if (1)
								{
									if (angle <= -30 && angle > -35) { bulletX -= 40; bulletY += 60; }	//корекц≥€ снар€ду
									if (angle <= -25 && angle > -30) { bulletX -= 30; bulletY += 60; }
									if (angle <= -20 && angle > -25) { bulletX -= 20; bulletY += 50; }
									if (angle <= -15 && angle > -20) { bulletX -= 20; bulletY += 40; }
									if (angle <= -10 && angle > -15) { bulletY += 23; }
									if (angle <= -5 && angle > -10) { bulletY += 10; }
									if (angle <= 0 && angle > -5) { bulletX -= 5; bulletY += 10; }
									if (angle <= 5 && angle > 0) { bulletX -= 4; bulletY -= 2; }
									if (angle <= 10 && angle > 5) { bulletX += 2; bulletY -= 5; }
									if (angle <= 15 && angle > 10) { bulletX += 5; bulletY -= 14; }
									if (angle <= 20 && angle > 15) { bulletX += 5; bulletY -= 24; }
									if (angle <= 25 && angle > 20) { bulletX += 5; bulletY -= 35; }
									if (angle <= 30 && angle > 25) { bulletX += 8; bulletY -= 40; }
									if (angle <= 35 && angle > 30) { bulletX += 10; bulletY -= 60; }
								}

								while (temp_angle > angle)	//повертаЇм пушку бота на потр≥бний кут
								{

									temp_angle -= 0.4;
									cannon.setRotation(temp_angle);

									if (1)
									{
										Sleep(15);
										window.clear();
										window.draw(map);
										window.draw(cannon);
										window.draw(cannon2);
										window.draw(panel);
										window.draw(bullet_rust);
										window.draw(bullet_old_metal);
										window.draw(bullet_stone);
										window.draw(bullet_metal);
										window.draw(Button_finish);
										window.draw(bullet);
										window.draw(heart);
										window.draw(heart2);
										window.draw(hp2);
										window.draw(hp);
										window.draw(z);
										window.draw(x);
										window.draw(c);
										window.draw(v);
										window.display();
									}	  //малюЇм
								}

								music_shoot.play();

								while (bulletY < 800)	//пол≥т снар€ду
								{
									if (bulletX < 0) { bulletY = 800; bulletX = -100; }
									bullet.setPosition(bulletX, bulletY);
									bulletX -= distance / 100;
									bulletY -= t;
									t -= 0.1;

									if (bulletX > 50 && bulletX < 150 && bulletY > 750 && bulletY < 810 && damage == false)//перев≥рка попаданн€
									{
										music_damage2.stop();
										music_shoot.stop();
										music_damage2.play();
										damage = true;
										hp2_size.x -= 0.1*sqrt(pow(distance / 100, 2) + pow(pos_mouse_in_game.y, 2));	//система урона
										hp2.setSize(hp2_size);
									}

									Sleep(8);
									window.clear();
									window.draw(map);
									window.draw(cannon);
									window.draw(cannon2);
									window.draw(panel);
									window.draw(bullet_rust);
									window.draw(bullet_old_metal);
									window.draw(bullet_stone);
									window.draw(bullet_metal);
									window.draw(Button_finish);
									window.draw(bullet);
									window.draw(heart);
									window.draw(heart2);
									window.draw(hp2);
									window.draw(hp);
									window.draw(z);
									window.draw(x);
									window.draw(c);
									window.draw(v);
									window.display();
								}
							}
							else
							{
								bullet.setPosition(-100, 0);
								pos_mouse_in_game.x = rand() % 1920;
								angle = rand() % 70 - 35;//(-35...35)

								MouseX = MouseY = 0;
								MouseX = pos_cannon.x - pos_mouse_in_game.x;
								MouseY = MouseX * tan(3.14159265 / 180 * (angle));
								pos_mouse_in_game.y = pos_cannon.y - MouseY;


								float t0 = (13430 - 14 * pos_mouse_in_game.y) / 790;
								float t = t0;
								float temp_angle = 35;
								float bulletX = 1820 - 53.5 * cos(angle*3.14159265 / 180);
								float bulletY = 732 + 53.5 * sin(angle*3.14159265 / 180);
								distance = sqrt(MouseX*MouseX + MouseY * MouseY);

								while (temp_angle > angle)	//повертаЇм пушку бота на потр≥бний кут
								{

									temp_angle -= 0.4;
									cannon.setRotation(temp_angle);

									if (1)
									{
										Sleep(15);
										window.clear();
										window.draw(map);
										window.draw(cannon);
										window.draw(cannon2);
										window.draw(panel);
										window.draw(bullet_rust);
										window.draw(bullet_old_metal);
										window.draw(bullet_stone);
										window.draw(bullet_metal);
										window.draw(Button_finish);
										window.draw(bullet);
										window.draw(heart);
										window.draw(heart2);
										window.draw(hp2);
										window.draw(hp);
										window.draw(z);
										window.draw(x);
										window.draw(c);
										window.draw(v);
										window.display();
									}	  //малюЇм
								}

								music_shoot.play();

								if (angle <= -30 && angle > -35) { bulletX -= 40; bulletY += 60; }	//корекц≥€ снар€ду
								if (angle <= -25 && angle > -30) { bulletX -= 30; bulletY += 60; }
								if (angle <= -20 && angle > -25) { bulletX -= 20; bulletY += 50; }
								if (angle <= -15 && angle > -20) { bulletX -= 20; bulletY += 40; }
								if (angle <= -10 && angle > -15) { bulletY += 23; }
								if (angle <= -5 && angle > -10) { bulletY += 10; }
								if (angle <= 0 && angle > -5) { bulletX -= 5; bulletY += 10; }
								if (angle <= 5 && angle > 0) { bulletX -= 4; bulletY -= 2; }
								if (angle <= 10 && angle > 5) { bulletX += 2; bulletY -= 5; }
								if (angle <= 15 && angle > 10) { bulletX += 5; bulletY -= 14; }
								if (angle <= 20 && angle > 15) { bulletX += 5; bulletY -= 24; }
								if (angle <= 25 && angle > 20) { bulletX += 5; bulletY -= 35; }
								if (angle <= 30 && angle > 25) { bulletX += 8; bulletY -= 40; }
								if (angle <= 35 && angle > 30) { bulletX += 10; bulletY -= 60; }

								while (bulletY < 800)	//пол≥т снар€ду
								{
									if (bulletX < 0) { bulletY = 800; }
									bullet.setPosition(bulletX, bulletY);
									bulletX -= distance / 100;
									bulletY -= t;
									t -= 0.1;

									if (bulletX > 50 && bulletX < 150 && bulletY > 750 && bulletY < 810 && damage == false)//перев≥рка попаданн€
									{
										music_damage2.play();
										damage = true;
										hp2_size.x -= 0.1*sqrt(pow(distance / 100, 2) + pow(pos_mouse_in_game.y, 2));	//система урона
										hp2.setSize(hp2_size);
									}

									Sleep(8);
									window.clear();
									window.draw(map);
									window.draw(cannon);
									window.draw(cannon2);
									window.draw(panel);
									window.draw(bullet_rust);
									window.draw(bullet_old_metal);
									window.draw(bullet_stone);
									window.draw(bullet_metal);
									window.draw(Button_finish);
									window.draw(bullet);
									window.draw(heart);
									window.draw(heart2);
									window.draw(hp2);
									window.draw(hp);
									window.draw(z);
									window.draw(x);
									window.draw(c);
									window.draw(v);
									window.display();
								}
							}

						}

					} while (step == false);//х≥д бота
				}

			} while (finish == false);
			music_menu.play();
		}
		if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 2)
		{
			Sleep(100);
			bool button = false;

			Text Button_info_exit("Back to menu", font_game, 100);
			Button_info_exit.setPosition(700, 800);
			Text Devel("Developer : Artem Morarash", font_game, 35);
			Devel.setPosition(70, 950);
			Text Text_info_0("Welcome!", font_game, 100);
			Text_info_0.setPosition(780, 40);
			Text Text_info_1("In this game you have to kill the enemy for the smallest amount of shots.", font_game, 60);
			Text_info_1.setPosition(70, 200);
			Text Text_info_2("With each next shot the enemy will shoot more precisely.", font_game, 60);
			Text_info_2.setPosition(65, 270);
			Text Text_info_3("Time and number of shells is unlimited.", font_game, 60);
			Text_info_3.setPosition(70, 340);
			Text Text_info_4("The damage to the projectile depends on its trajectory.", font_game, 60);
			Text_info_4.setPosition(70, 410);
			Text Text_info_5("The more curve the trajectory is, the less damage.", font_game, 60);
			Text_info_5.setPosition(70, 480);
			Text Text_info_6("Damage does not depend on the core.", font_game, 60);
			Text_info_6.setPosition(70, 550);

			do
			{
				if (volume_music_menu > 10000) { volume_music_menu = 10000; }
				volume_music_menu += 0.13;
				Button_info_exit.setFillColor(Color::White);
				num_button_menu = 0;

				if (IntRect(700, 840, 510, 65).contains(Mouse::getPosition(window)))
				{
					num_button_menu = 4;
					Button_info_exit.setFillColor(Color::Blue);
				}
				if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 4)
				{
					button = true;
				}

				Sleep(20);
				window.clear();
				window.draw(menu);
				window.draw(Button_info_exit);
				window.draw(Devel);
				window.draw(Text_info_0);
				window.draw(Text_info_1);
				window.draw(Text_info_2);
				window.draw(Text_info_3);
				window.draw(Text_info_4);
				window.draw(Text_info_5);
				window.draw(Text_info_6);
				window.display();

			} while (button == false);
		}

		if (Mouse::isButtonPressed(Mouse::Left) && num_button_menu == 3) { window.close(); }
		if (volume_music_menu > 10000) { volume_music_menu = 10000; }
		num_button_menu = 0;
		volume_music_menu += 0.13;

		Sleep(10);
		window.clear();
		window.draw(menu);
		window.draw(Title);
		window.draw(Button_start);
		window.draw(Button_info);
		window.draw(Button_exit);
		window.display();

	}
	return 0;
}