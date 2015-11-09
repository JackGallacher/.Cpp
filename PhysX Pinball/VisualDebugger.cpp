#include "VisualDebugger.h"
#include <vector>
#include "Extras\Camera.h"
#include "Extras\Renderer.h"
#include "Extras\HUD.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

int counter = 0;
int score = 0;

namespace VisualDebugger
{

	using namespace physx;

	enum RenderMode
	{
		DEBUG,
		NORMAL,
		BOTH
	};

	enum HUDState
	{
		EMPTY = 0,
		HELP = 1,
		PAUSE = 2
	};

	//function declarations
	void KeyHold();
	void KeySpecial(int key, int x, int y);
	void KeyRelease(unsigned char key, int x, int y);
	void KeyPress(unsigned char key, int x, int y);

	void motionCallback(int x, int y);
	void mouseCallback(int button, int state, int x, int y);
	void exitCallback(void);

	void RenderScene();
	void ToggleRenderMode();
	void HUDInit();

	///simulation objects
	Camera* camera;
	PhysicsEngine::MyScene* scene;
	PxReal delta_time = 1.f/60.f;
	PxReal gForceStrength = 20;
	RenderMode render_mode = NORMAL;
	const int MAX_KEYS = 256;
	bool key_state[MAX_KEYS];
	bool hud_show = true;
	HUD hud;

	//Init the debugger
	void Init(const char *window_name, int width, int height)
	{

		///Init PhysX
		PhysicsEngine::PxInit();
		scene = new PhysicsEngine::MyScene();
		scene->Init();

		///Init renderer
		Renderer::BackgroundColor(PxVec3(150.f/255.f,150.f/255.f,150.f/255.f));
		Renderer::SetRenderDetail(40);
		Renderer::InitWindow(window_name, width, height);
		Renderer::Init();

		camera = new Camera(PxVec3(0.0f, 5.0f, 15.0f), PxVec3(0.f,-.1f,-1.f), 5.f);

		//initialise HUD
		HUDInit();

		///Assign callbacks
		//render
		glutDisplayFunc(RenderScene);

		//keyboard
		glutKeyboardFunc(KeyPress);
		glutSpecialFunc(KeySpecial);
		glutKeyboardUpFunc(KeyRelease);

		//mouse
		glutMouseFunc(mouseCallback);
		glutMotionFunc(motionCallback);

		//exit
		atexit(exitCallback);

		//init motion callback
		motionCallback(0,0);
	}
	void HUDInit()
	{
	}

	//Start the main loop
	void Start()
	{ 
		glutMainLoop(); 
	}

	//Render the scene and perform a single simulation step
	void RenderScene()
	{

		string player_score;
		ostringstream convert_score;
		convert_score << score;
		player_score = convert_score.str();
		
		if (mushroom_one || mushroom_two || mushroom_three || mushroom_four || mushroom_five)
		{
			score = score + 10;
		}
		if (platform_mushroom_one||platform_mushroom_two||platform_mushroom_three)
		{
			score = score + 20;
		}
		if (game_reset)
		{
			counter ++;
		}
		if (counter == 0)
		{
			lives = 5;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}

		if (counter == 1)
		{
			lives = 4;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}
		if (counter == 2)
		{
			lives = 3;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}
		if (counter == 3)
		{
			lives = 2;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}
		if (counter == 4)
		{
			lives = 1;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}
		if (counter == 5)
		{
			lives = 0;
			hud.Clear();
			string player_lives;
			ostringstream convert_lives;
			convert_lives << lives;
			player_lives = convert_lives.str();
			hud.AddLine(HELP, " Welcome to my Pinball Machine!");
			hud.AddLine(HELP, " Controls:");
			hud.AddLine(HELP, " F1 - Toggle render modes and see how the shapes/joints were made!");
			hud.AddLine(HELP, " F2 - pause/unpause the game.");
			hud.AddLine(HELP, " F3 - show/hide this menu.");
			hud.AddLine(HELP, " R - Use the Left flipper.");
			hud.AddLine(HELP, " T - Use the Right flippers.");
			hud.AddLine(HELP, " K - Hold to draw back, release to shoot the ball.");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "You have 5 lives, if the ball reaches the bottom of the table you lose a life. Lose all your lives and the game is over!");
			hud.AddLine(HELP, "Hitting the mushrooms will turn them purple and you will gain 10 points.");
			hud.AddLine(HELP, "hitting the mushrooms up the ramp will give you 20 points");
			hud.AddLine(HELP, "hitting the ball out of the table restarts your current life (hope this doesnt happen much!)");
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Score");
			hud.AddLine(HELP, player_score);
			hud.AddLine(HELP, "");
			hud.AddLine(HELP, "Lives");
			hud.AddLine(HELP, player_lives);
			hud.AddLine(HELP, "Game Over! Press F4 to start a new game!");
			hud.FontSize(0.018f);
			//set font color for all screens
			hud.Color(PxVec3(0.f, 0.f, 0.f));
		}

		//handle pressed keys
		KeyHold();

		//start rendering
		Renderer::Start(camera->getEye(), camera->getDir());

		if ((render_mode == DEBUG) || (render_mode == BOTH))
		{
			Renderer::Render(scene->Get()->getRenderBuffer());
		}

		if ((render_mode == NORMAL) || (render_mode == BOTH))
		{
			std::vector<PxActor*> actors = scene->GetAllActors();
			if (actors.size())
				Renderer::Render(&actors[0], (PxU32)actors.size());
		}

		//adjust the HUD state
		if (hud_show)
		{
			if (scene->Pause())
				hud.ActiveScreen(PAUSE);
			else
				hud.ActiveScreen(HELP);
		}
		else
			hud.ActiveScreen(EMPTY);

		//render HUD	
		hud.Render();

		//finish rendering
		Renderer::Finish();

		//perform a single simulation step
		scene->Update(delta_time);

	}

	//user defined keyboard handlers
	void UserKeyPress(int key)
	{
		switch (toupper(key))
		{
		case 'R'://Applies force to left flipper
			scene->setLeftVelocityforward();
			break;
		case 'T'://Applies force to right flipper
			scene->setRightVelocityforward();
			break;
		default:
			break;
		}
	}

	void UserKeyRelease(int key)
	{
		switch (toupper(key))
		{
		case 'R'://Returns left flipper to normal position.
			scene->setLeftVelocitybackward();
			break;
		case 'T'://Returns right flipper to normal position.
			scene->setRightVelocitybackward();
			break;
		default:			
			break;
		}
	}

	void UserKeyHold(int key)
	{
	}

	//handle camera control keys
	void CameraInput(int key)
	{
		switch (toupper(key))
		{
		case 'W':
			//camera->MoveForward(delta_time);
			break;
		case 'S':
			//camera->MoveBackward(delta_time);
			break;
		case 'A':
			//camera->MoveLeft(delta_time);
			break;
		case 'D':
			//camera->MoveRight(delta_time);
			break;
		case 'Q':
			//camera->MoveUp(delta_time);
			break;
		case 'Z':
			//camera->MoveDown(delta_time);
			break;
		default:
			break;
		}
	}

	//handle force control keys
	void ForceInput(int key)
	{
		if (!scene->GetSelectedActor())
			return;

		switch (toupper(key))
		{
		//	// Force controls on the selected actor
		//case 'I': //forward
		//	scene->GetSelectedActor()->addForce(PxVec3(0,0,-1)*gForceStrength);
		//	break;
		case 'K': //backward
			scene->GetSelectedActor()->addForce(PxVec3(0,0,+35)*gForceStrength);
			break;
		//case 'J': //left
		//	scene->GetSelectedActor()->addForce(PxVec3(-1,0,0)*gForceStrength);
		//	break;
		//case 'L': //right
		//	scene->GetSelectedActor()->addForce(PxVec3(1,0,0)*gForceStrength);
		//	break;
		//case 'U': //up
		//	scene->GetSelectedActor()->addForce(PxVec3(0,1,0)*gForceStrength);
		//	break;
		//case 'M': //down
		//	scene->GetSelectedActor()->addForce(PxVec3(0,-20,0)*gForceStrength);
		//	break;
		//default:
		//	break;
		}
	}

	///handle special keys
	void KeySpecial(int key, int x, int y)
	{
		//simulation control
		switch (key)
		{
			//display control
		case GLUT_KEY_F3:
			//hud on/off
			hud_show = !hud_show;
			break;
		//case GLUT_KEY_F6:
			//shadows on/off
			//Renderer::ShowShadows(!Renderer::ShowShadows());
			//break;
		case GLUT_KEY_F1:
			//toggle render mode
			ToggleRenderMode();
			break;
		//case GLUT_KEY_F8:
			//reset camera view
			//camera->Reset();
			//break;
			//simulation control
		//case GLUT_KEY_F9:
			//select next actor
			//scene->SelectNextActor();
			//break;
		case GLUT_KEY_F2:
			//toggle scene pause
			scene->Pause(!scene->Pause());
			break;
		case GLUT_KEY_F4:
			counter = 0;
			score = 0;
			break;
		//case GLUT_KEY_F12:
			//resect scene
			//scene->Reset();
			//break;
		default:
			break;
		}
	}

	//handle single key presses
	void KeyPress(unsigned char key, int x, int y)
	{
		//do it only once
		if (key_state[key] == true)
			return;

		key_state[key] = true;

		//exit
		if (key == 27)
			exit(0);

		UserKeyPress(key);
	}

	//handle key release
	void KeyRelease(unsigned char key, int x, int y)
	{
		key_state[key] = false;
		UserKeyRelease(key);
	}

	//handle holded keys
	void KeyHold()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			if (key_state[i]) // if key down
			{
				CameraInput(i);
				ForceInput(i);
				UserKeyHold(i);
			}
		}
	}

	//mouse handling
	int mMouseX = 0;
	int mMouseY = 0;

	void motionCallback(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		//camera->Motion(dx, dy, delta_time);

		//mMouseX = x;
		//mMouseY = y;
	}

	void mouseCallback(int button, int state, int x, int y)
	{
		//mMouseX = x;
		//mMouseY = y;
	}

	void ToggleRenderMode()
	{
		if (render_mode == NORMAL)
			render_mode = DEBUG;
		else if (render_mode == DEBUG)
			render_mode = BOTH;
		else if (render_mode == BOTH)
			render_mode = NORMAL;
	}

	///exit callback
	void exitCallback(void)
	{
		delete camera;
		delete scene;
		PhysicsEngine::PxRelease();
	}
}

