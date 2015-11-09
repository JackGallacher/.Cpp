#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>
//#include <string>

static bool top_right_wall_force;//bool varaible to toggle when the ball hits the top right wall triangle.
static bool back_wall_force;//bool variable to toggle when the ball hits the back wall.
static bool game_reset;//bool variable to trigger when ball reaches theend game zone.
static bool oob_reset;//bool varaible to trigger when the ball goes outside the table.
static bool activate_speed_boost;//bool varaible to trigger the speed boost.
static bool mushroom_one, mushroom_two, mushroom_three, mushroom_four, mushroom_five;//bools to trigger when a mushroom is touched.
static bool platform_mushroom_one, platform_mushroom_two, platform_mushroom_three;//bools to trigger the platfrom mushrooms.

static int lives = 5;

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	//vertices for the enclosure
	static PxVec3 enclosure_verts[] = { PxVec3(-20.f, 0.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.f, 3.0f, 0.0f), PxVec3(-20.f, 3.0f, 0.0f),//Outside box
		PxVec3(-20.f, 0.0f, -40.0f), PxVec3(0.0f, 0.0f, -40.0f), PxVec3(0.0f, 3.0f, -40.0f), PxVec3(-20.f, 3.0f, -40.0f),//Outside box

		PxVec3(-19.8f, 0.0f, -0.2f), PxVec3(-0.2f, 0.0f, -0.2f), PxVec3(-0.2f, 3.0f, -0.2f), PxVec3(-19.8f, 3.0f, -0.2f),//Inside box
		PxVec3(-19.8f, 0.0f, -39.8f), PxVec3(-0.2f, 0.0f, -39.8f), PxVec3(-0.2f, 3.0f, -39.8f), PxVec3(-19.8f, 3.0f, -39.8f) };//Inside box

	//triganometry information for the enclosure.
	static PxU32 enclosure_trigs[] = { 1, 2, 0, 2, 3, 0, 5, 6, 4, 6, 7, 4, 1, 5, 0, 5, 4, 0, 5, 1, 2, 6, 5, 2, 4, 0, 3, 7, 4, 3,//Box 1
		9, 8, 11, 10, 9, 11, 13, 14, 12, 14, 15, 12, 9, 13, 8, 13, 12, 8, 13, 9, 10, 14, 13, 10, 11, 8, 12, 12, 15, 11,//Box 2
		2, 10, 3, 10, 11, 3, 7, 15, 6, 15, 14, 6, 6, 14, 2, 14, 10, 2, 3, 11, 7, 11, 15, 7 };//Fills gaps between the boxes.

	class Enclosure : public TriangleMesh//class for the enclosured to hold the object of the pinball game.
	{
	public:
		Enclosure(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(enclosure_verts), end(enclosure_verts)), vector<PxU32>(begin(enclosure_trigs), end(enclosure_trigs)), pose)
		{
		}
	};
	//vertices for the bottom left wall of the pinball table.
	static PxVec3 backleftwall_verts[] = { PxVec3(0.f, 0.f, 0.f), PxVec3(0.f, 1.f, 0.f), PxVec3(8.f, 0.f, 0.f), PxVec3(8.f, 1.f, 0.f), PxVec3(0.f, 0.f, -5.f), PxVec3(0.f, 1.f, -5.f)};
	//trianomtry information for the back left wall of the pinball table.
	static PxU32 backleftwall_trigs[] = { 0, 2, 1, 2, 3, 1,//front wall
										  0, 5, 4, 5, 0, 1, //left wall					
										  2, 4, 5, 2, 5, 3,// right wall				
										  0, 4, 2, // bottom wall
										  1, 3, 5 // top wall					
										};

	class BackLeftWall : public TriangleMesh//class for the triangle as the bottom left of the pinball table.
	{
	public:
		BackLeftWall(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(backleftwall_verts), end(backleftwall_verts)), vector<PxU32>(begin(backleftwall_trigs), end(backleftwall_trigs)), pose)
		{
		}
	};
	//vertices for the bottom right wall of the pinball table.
	static PxVec3 backrightwall_verts[] = { PxVec3(0.f, 0.f, 0.f), PxVec3(0.f, 1.f, 0.f), PxVec3(-8.f, 0.f, 0.f), PxVec3(-8.f, 1.f, 0.f), PxVec3(0.f, 0.f, -5.f), PxVec3(0.f, 1.f, -5.f) };
	//trianomtry information for the back right wall of the pinball table.
	static PxU32 backrightwall_trigs[] = {  0, 1, 2, 2, 1, 3,//front wall
											0, 4, 5, 5, 1, 0, //left wall
											2, 5, 4, 2, 3, 5,// right wall	
											0, 4, 2, // bottom wall
											1, 5, 3 // top wall		
										 };

	class BackRightWall : public TriangleMesh//class for the triangle at the bottom right of the pinball table.
	{
	public:
		BackRightWall(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(backrightwall_verts), end(backrightwall_verts)), vector<PxU32>(begin(backrightwall_trigs), end(backrightwall_trigs)), pose)
		{
		}
	};
	//vertices for the top right wall of the pinball table.
	static PxVec3 toprightwall_verts[] = {PxVec3(0.0f, 0.0f, 3.0f), PxVec3(0.0f, 1.0f, 3.0f), PxVec3(-6.0f, 0.0f, -5.0f), PxVec3(-6.0f, 1.0f, -5.0f), PxVec3(0.0f, 0.0f, -5.0f), PxVec3(0.0f, 1.0f, -5.0f)};
	//triganometry information for the top right wall of the pinball table.
	static PxU32 toprightwall_trigs[] = { 0, 1, 2, 2, 1, 3,//front wall
										  0, 5, 4, 5, 0, 1, //left wall
										  2, 4, 5, 2, 5, 3,// right wall	
										  0, 4, 2, // bottom wall
										  1, 5, 3 // top wall		
										};

	class TopRightWall : public TriangleMesh// class for the triangle the top right of the pinball table.
	{
	public:
		TopRightWall(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(toprightwall_verts), end(toprightwall_verts)), vector<PxU32>(begin(toprightwall_trigs), end(toprightwall_trigs)), pose)
		{
		}
	};
	//vertices for the back wall
	static PxVec3 back_wall_verts[] = { PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.0f, 0.0f, 1.0f), PxVec3(0.0f, 1.0f, 0.0f), PxVec3(0.0f, 1.0f, 1.0f), PxVec3(-13.7f, 0.0f, 0.0f), PxVec3(-13.7f, 0.0f, 1.0f), PxVec3(-13.7f, 1.0f, 0.0f), PxVec3(-13.7f, 1.0f, 1.0f) };
	//triganometry for the back wall
	static PxU32 back_wall_trigs[] = { 0, 2, 1, 2, 3, 1,//front wall.
									   5, 6, 7, 6, 5, 4,// back wall.
									   0, 2, 4, 4, 2, 6,//left wall.
									   1, 3, 5, 5, 3, 7,//right wall.
									   2, 6, 7, 7, 3, 2,//top wall.
									   4, 5, 0, 5, 1, 0// bottom.
									 };

	class BackWall : public TriangleMesh//class for the left ball chute where the ball starts when the game is played.
	{
	public:
		BackWall(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(back_wall_verts), end(back_wall_verts)), vector<PxU32>(begin(back_wall_trigs), end(back_wall_trigs)), pose)
		{
		}
	};

	//vertices for the left ball chute
	static PxVec3 left_ball_chute_verts[] = { PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.25f, 0.0f, 0.0f), PxVec3(0.0f, 3.0f, 0.0f), PxVec3(0.25f, 3.0f, 0.0f), PxVec3(0.0f, 0.0f, -40.0f), PxVec3(0.25f, 0.0f, -40.0f), PxVec3(0.0f, 3.0f, -40.0f), PxVec3(0.25f, 3.0f, -40.0f)};
	//triganometry for the left ball chute
	static PxU32 left_ball_chute_trigs[] = { 0,1,2,2,1,3,//front wall.
										5,7,6,6,4,5,// back wall.
										0,2,4,4,2,6,//left wall.
										1,5,3,5,7,3,//right wall.
										2,7,6,7,2,3,//top wall.
										4,0,5,5,0,1// bottom.
									  };

	class LeftBallChute : public TriangleMesh//class for the left ball chute.
	{
	public:
		LeftBallChute(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(left_ball_chute_verts), end(left_ball_chute_verts)), vector<PxU32>(begin(left_ball_chute_trigs), end(left_ball_chute_trigs)), pose)
		{
		}
	};
	//vertices for the right ball chute
	static PxVec3 right_ball_chute_verts[] = { PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.25f, 0.0f, 0.0f), PxVec3(0.0f, 1.0f, 0.0f), PxVec3(0.25f, 1.0f, 0.0f), PxVec3(0.0f, 0.0f, -30.0f), PxVec3(0.25f, 0.0f, -30.0f), PxVec3(0.0f, 1.0f, -30.0f), PxVec3(0.25f, 1.0f, -30.0f) };
	//triganometry for the right ball chute
	static PxU32 right_ball_chute_trigs[] = { 0, 1, 2, 2, 1, 3,//front wall.
		5, 7, 6, 6, 4, 5,// back wall.
		0, 2, 4, 4, 2, 6,//left wall.
		1, 5, 3, 5, 7, 3,//right wall.
		2, 7, 6, 7, 2, 3,//top wall.
		4, 0, 5, 5, 0, 1// bottom.
	};

	class RightBallChute : public TriangleMesh//class for the right ball chute where the ball starts when the game is played.
	{
	public:
		RightBallChute(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(right_ball_chute_verts), end(right_ball_chute_verts)), vector<PxU32>(begin(right_ball_chute_trigs), end(right_ball_chute_trigs)), pose)
		{
		}
	};
	//vertices for guide wall.
	static PxVec3 guide_wall_verts[] = { PxVec3(-1.0f, 0.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.0f, 1.0f, 0.0f), PxVec3(-1.0f, 1.0f, 0.0f),
										PxVec3(-1.0f, 0.0f, -1.0f), PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.0f, 1.0f, 0.0f), PxVec3(-1.0f, 1.0f, -1.0f) };
	//triganometry for the guide wall.
	static PxU32 guide_wall_trigs[] = { 0, 1, 3, 2, 3, 1,//left wall.
										4, 1, 7, 6, 7, 1,//right wall.
										0, 4, 7, 0, 7, 3,//back wall.				
										2, 7, 3//front wall.
									  };

	class GuideWall : public TriangleMesh//class for the guide wall which direct the ball into the table.
	{
	public:
		GuideWall(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(guide_wall_verts), end(guide_wall_verts)), vector<PxU32>(begin(guide_wall_trigs), end(guide_wall_trigs)), pose)
		{
		}
	};
	//vertices for reset game square.
	static PxVec3 reset_game_verts[] = { PxVec3(0.0f, 0.0f, 0.0f), PxVec3(3.0f, 0.0f, 0.0f), PxVec3(3.0f, 0.0f, 0.15f), PxVec3(0.0f, 0.0f, 0.15f), };
	//triganometry for the reset game square.
	static PxU32 reset_game_trigs[] = {0, 2, 1, 2, 0, 3};

	class ResetGame : public TriangleMesh//class for reset game square that when triggerd by the ball will reset the game.
	{
	public:
		ResetGame(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(reset_game_verts), end(reset_game_verts)), vector<PxU32>(begin(reset_game_trigs), end(reset_game_trigs)), pose)
		{
		}
	};
	class Plunger//class that creates the plunger to launch the ballinto the table.
	{
		Box *top, *bottom;//creates the two boxes used in the plunger.
		DistanceJoint* spring;//creates the spring to join the two boxes.
	public:
		Plunger(const PxTransform& pose = PxTransform(PxIdentity))
		{
			top = new Box(PxTransform(PxVec3(-0.5f, 1.9f, -5.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//sets the position of the plunger top.
			top->SetKinematic(true);//sets the top of the plunger to a kinematic object.

			bottom = new Box(PxTransform(PxVec3(-0.5f, 1.5f, -5.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the bottom of the plunger.
			bottom->Color(color_palette[1]);
			PxRigidDynamic* CCDbottom = (PxRigidDynamic*)bottom->Get();
			bottom->Name("bottom");
			CCDbottom->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the bottom of the plunger.

			spring = new DistanceJoint(top, PxTransform(PxVec3(0.0f, 0.12f, 0.0f)), bottom, PxTransform(PxVec3(0.0f, 0.0f, 0.0)));//creates a spring distance joint.
			spring->Stiffness(140);//sets the stiffness of the spring.
			spring->Damping(1);//sets the damping of the spring.
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(top);//adds the "top" object to the scene.
			scene->Add(bottom);//adds the "bottom" object to the scene.
		}
	};
	//vertices for the left flipper.
	static PxVec3 leftflipper_verts[] = { PxVec3(0, 0, 0.25), PxVec3(0, 0, -0.25), PxVec3(0.5, 0, 0.5), PxVec3(0.5, 0, -0.5), PxVec3(2.75, 0.1, 0.12),
		PxVec3(2.75, 0.1, -0.125), PxVec3(0, 0.5, 0.25), PxVec3(0, 0.5, -0.25), PxVec3(0.5, 0.5, 0.5), PxVec3(0.5, 0.5, -0.5), PxVec3(2.75, 0.6, 0.125), PxVec3(2.75, 0.6, -0.125) };

	class LeftFlipper : public ConvexMesh//class the creats the left flipper.
	{
	public:
		LeftFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(leftflipper_verts), end(leftflipper_verts)), pose, density)
		{

		}
	};
	//vertices for the right flipper.
	static PxVec3 rightflipper_verts[] = { PxVec3(-2.75, -0.25, 0.125), PxVec3(-2.75, -0.25, -0.125), PxVec3(-0.6, 0, 0.5), PxVec3(-0.5, 0, -0.5), PxVec3(0, 0.1, 0.25),
		PxVec3(0, 0.1, -0.25), PxVec3(-2.75, 0.25, 0.125), PxVec3(-2.75, 0.25, -0.125), PxVec3(-0.5, 0.5, 0.5), PxVec3(-0.5, 0.50, -0.5), PxVec3(0, 0.51, 0.25), PxVec3(0, 0.50, -0.25) };

	class RightFlipper : public ConvexMesh//class the creates the right flipper.
	{
	public:
		RightFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(rightflipper_verts), end(rightflipper_verts)), pose, density)
		{

		}
	};
	//vertices for the left bumper.
	static PxVec3 left_bumper_verts[] = { PxVec3(0.f, 0.f, 0.f), PxVec3(0.f, 0.5f, 0.f), PxVec3(2.5f, 0.f, 1.f), PxVec3(2.5f, 0.5f, 1.f), PxVec3(0.f, 0.f, -4.f), PxVec3(0.f, 0.5f, -4.f) };
	//trianomtry information for the left bumper of the pinball table.
	static PxU32 left_bumper_trigs[] = { 0, 2, 1, 2, 3, 1,//front wall
										 0, 5, 4, 5, 0, 1, //left wall					
										 2, 4, 5, 2, 5, 3,// right wall				
										 0, 4, 2, // bottom wall
										 1, 3, 5 // top wall					
	                                   };

	class LeftBumper : public TriangleMesh//class for the left bumper.
	{
	public:
		LeftBumper(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(left_bumper_verts), end(left_bumper_verts)), vector<PxU32>(begin(left_bumper_trigs), end(left_bumper_trigs)), pose)
		{
		}
	};
	//vertices for the right_bumper.
	static PxVec3 right_bumper_verts[] = { PxVec3(0.f, 0.f, 0.f), PxVec3(0.f, 0.5f, 0.f), PxVec3(-2.5f, 0.f, 1.f), PxVec3(-2.5f, 0.5f, 1.f), PxVec3(0.f, 0.f, -4.f), PxVec3(0.f, 0.5f, -4.f) };
	//trianomtry information for the right bumper of the pinball table.
	static PxU32 right_bumper_trigs[] = { 0, 1, 2, 2, 1, 3,//front wall
										 0, 4, 5, 5, 1, 0, //left wall
										 2, 5, 4, 2, 3, 5,// right wall	
										 0, 4, 2, // bottom wall
										 1, 5, 3 // top wall		
									   };

	class RightBumper : public TriangleMesh//class for the right bumper.
	{
	public:
		RightBumper(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(right_bumper_verts), end(right_bumper_verts)), vector<PxU32>(begin(right_bumper_trigs), end(right_bumper_trigs)), pose)
		{
		}
	};
	//vertices for the extra left flipper.
	static PxVec3 extra_left_flipper_verts[] = { PxVec3(0, 0, 0.25), PxVec3(0, 0, -0.25), PxVec3(0.5, 0, 0.5), PxVec3(0.5, 0, -0.5), PxVec3(2.75, 0.1, 0.12),
		PxVec3(2.75, 0.1, -0.125), PxVec3(0, 0.5, 0.25), PxVec3(0, 0.5, -0.25), PxVec3(0.5, 0.5, 0.5), PxVec3(0.5, 0.5, -0.5), PxVec3(2.75, 0.6, 0.125), PxVec3(2.75, 0.6, -0.125) };

	class ExtraLeftFlipper : public ConvexMesh//class the creats the extra left flipper.
	{
	public:
		ExtraLeftFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(extra_left_flipper_verts), end(extra_left_flipper_verts)), pose, density)
		{

		}
	};
	//vertices for the extra right flipper.
	static PxVec3 extra_right_flipper_verts[] = { PxVec3(-2.75, -0.25, 0.125), PxVec3(-2.75, -0.25, -0.125), PxVec3(-0.6, 0, 0.5), PxVec3(-0.5, 0, -0.5), PxVec3(0, 0.1, 0.25),
		PxVec3(0, 0.1, -0.25), PxVec3(-2.75, 0.25, 0.125), PxVec3(-2.75, 0.25, -0.125), PxVec3(-0.5, 0.5, 0.5), PxVec3(-0.5, 0.50, -0.5), PxVec3(0, 0.51, 0.25), PxVec3(0, 0.50, -0.25) };

	class ExtraRightFlipper : public ConvexMesh//class the creates the extra right flipper.
	{
	public:
		ExtraRightFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(extra_right_flipper_verts), end(extra_right_flipper_verts)), pose, density)
		{

		}
	};
	//vertices for the speed boost
	static PxVec3 speed_boost_verts[] = { PxVec3(2.0, 0.0, 0.0), PxVec3(4.0, 0.0, 0.0), PxVec3(3.0, 0.0, -3.0), };
	//trianomtry information for the speed boost.
	static PxU32 speed_boost_trigs[] = {0, 1, 2};

	class SpeedBoost : public TriangleMesh//class for the speed boost.
	{
	public:
		SpeedBoost(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(speed_boost_verts), end(speed_boost_verts)), vector<PxU32>(begin(speed_boost_trigs), end(speed_boost_trigs)), pose)
		{
		}
	};
	class Windmill : public DynamicActor//class to creates a windmill that is used in the table.
	{
	public:
		Windmill(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, 2.f, .2f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(.5f, 2.f, .2f), density);//creates first propellor for the windmill.
			CreateShape(PxBoxGeometry(PxVec3(.5f, 2.f, .2f)), density);//creates second propellor for the windmill.

			GetShape(0)->setLocalPose(PxTransform(PxVec3(-0.0f, 0.5f, 0.0f)));//sets position of first propellor.
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-0.0f, 0.5f, 0.0f), PxQuat(-50 * (PxPi / 100), PxVec3(1.0, 0.0, 0.0))));//sets positoon of second propellor.
		}
	};
	//vertices for the mushroom.
	static PxVec3 mushroom_verts[] = { PxVec3(0.0, 0.0, 0.0), PxVec3(1.0, 0.0, 0.0), PxVec3(0.0, 1.0, 0.0), PxVec3(1.0, 1.0, 0.0), 
										PxVec3(0.0, 0.0, -1.0), PxVec3(1.0, 0.0, -1.0), PxVec3(0.0, 1.0, -1.0), PxVec3(1.0, 1.0, -1.0), };
	//trianomtry information for the right bumper of the pinball table.
	static PxU32 mushroom_trigs[] = {	0,1,2,2,1,3,//front wall.
										4,6,5,6,7,5,//back wall.
										2,3,6, 6,3,7,//top wall
										0,1,4,4,1,5,//bottom wall.
										1,5,7,7,3,1,//right wall.
										0,6,4,0,2,6//left wall.
									};

	class Mushroom : public TriangleMesh//class for the right bumper.
	{
	public:
		Mushroom(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(mushroom_verts), end(mushroom_verts)), vector<PxU32>(begin(mushroom_trigs), end(mushroom_trigs)), pose)
		{
		}
	};
	static PxVec3 platform_verts[] = { PxVec3(-13.8, 0.0, 0.0), PxVec3(0.0, 0.0, 0.0), PxVec3(-13.8, 0.0f, 4.0), PxVec3(0.0, 0.0f, 4.0),//platform base. 0,1,2,3
										PxVec3(-13.8, 0.0, 0.0), PxVec3(0.0, 0.0, 0.0), PxVec3(-13.8, 4.0, 0.0), PxVec3(0.0, 4.0, 0.0),//platform back wall. 4,5,6,7
										PxVec3(0.0, 0.0, 0.0), PxVec3(0.0, 0.0, 4.0), PxVec3(0.0, 4.0, 0.0), PxVec3(0.0, 4.0, 4.0),//platform right wall. 8,9,10,11
										PxVec3(-13.8, 0.0, 0.0), PxVec3(-13.8, 0.0, 4.0), PxVec3(-13.8, 4.0, 0.0), PxVec3(-13.8, 4.0, 4.0),//platform left wall. 12,13,14,15
										PxVec3(-13.8, 0.0, 4.0), PxVec3(-13.8, -1.5, 9.0), PxVec3(-10.8, 0.0, 4.0), PxVec3(-10.8, -1.5, 9.0),//left ramp. 16,17,18,19
										PxVec3(0.0, 0.0, 4.0), PxVec3(0.0, -1.5, 9.0), PxVec3(-3.0, 0.0, 4.0), PxVec3(-3.0, -1.5, 9.0),//right ramp. 20,21,22,23
										PxVec3(-3.0, 0.0, 4.0), PxVec3(-10.8, 0.0, 4.0), PxVec3(-3.0, 1.0, 4.0), PxVec3(-10.8, 1.0, 4.0),//middle wall. 24,25,26,27
									 };	
	static PxU32 platform_trigs[] = { 0, 2, 1, 1, 2, 3,//platform base
								      4, 5, 6, 5, 7, 6,//platfrom back wall.
									  8, 9, 10, 9, 11, 10,//platform right wall.
									  12, 13, 14, 14, 13, 15,//platfrom left wall.
									  16, 17, 18, 18,17,19,//left ramp
									  20, 22, 21, 22, 23, 21,//right ramp
									  24, 25, 26, 25, 27,26//middle wall.
									  
									};
	class Platform : public TriangleMesh//class for the platform.
	{
	public:
		Platform(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(platform_verts), end(platform_verts)), vector<PxU32>(begin(platform_trigs), end(platform_trigs)), pose)

		{
		}
	};
	struct FilterGroup
	{
		enum Enum
		{
			BALL = (1 << 0),//filter for the ball.
			TOP_RIGHT_WALL = (1 << 1),//filter for the top right wall.
			BACK_WALL = (1 << 2),//filter for the back wall.
			RESET_GAME = (1 << 3),//filter for the rest game block.
			TABLE = (1 << 4),//filter for the table.
			LEFT_BALL_CHUTE = (1 << 5),//filter for the ball chute.
			BACK_LEFT_WALL = (1 << 6),//filter for the back left wall.
			BACK_RIGHT_WALL = (1 << 7),//filter for the back right wall.
			GUIDE_WALL = (1 << 8),//filter for the guide wall.
			LEFT_FLIPPER = (1 << 9),//filter for the left flipper.
			RIGHT_FLIPPER = (1 << 10),//filter for the right flipper.
			PLANE = (1 << 11),//filter for the plane.
			RIGHT_BALL_CHUTE = (1 << 12),//filter for the right ball chute.
			EXTRA_LEFT_FLIPPER = (1 << 13),//filter for the left flipper.
			EXTRA_RIGHT_FLIPPER = (1 << 14),//filter for the right flipper.
			SPEED_BOOST = (1 << 15),//filter for the speed boost.
			LEFT_BUMPER = (1 << 16),//filter for the left bumper.
			RIGHT_BUMPER = (1 << 17),//filter for the right bumper.
			WINDMILL = (1 << 18),//filter for the windmill.
			MUSHROOM = (1 << 19),//filter for the mushroom.
			PLATFORM = (1 << 20)//filter for the platform.
		};
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					string ball_contact_name;
					ball_contact_name = pairHeader.actors[1]->getName();//checks the name of the object the ball has come into contact with.
					if (ball_contact_name == "top_right_wall")//checks condition.
					{
						cerr << "hittng top right wall." << endl;//displays specified text.
						top_right_wall_force = true;//sets bool to true.
					}
					if (ball_contact_name == "back_wall")//checks condition.
					{
						cerr << "hittng back wall." << endl;//displays specified text.
						back_wall_force = true;//sets bool to true.
					}
					if (ball_contact_name == "reset_game")//checks condition.
					{
						cerr << "hit reset game square" << endl;//displays specified text.
						game_reset = true;//sets bool to true.
					}
					if (ball_contact_name == "plane")//checks condition.
					{
						cerr << "hit plane" << endl;//displays specified text.
						oob_reset = true;//sets bool to true.
					}
					if (ball_contact_name == "speed_boost")//checks condition.
					{
						cerr << "hit speed boost" << endl;//displays specified text.
						activate_speed_boost = true;//sets bool to true.
					}
					if (ball_contact_name == "mushroom1")//checks condition.
					{
						mushroom_one = true;//sets bool to true.
					}
					if (ball_contact_name == "mushroom2")//checks condition.
					{
						mushroom_two = true;//sets bool to true.
					}
					if (ball_contact_name == "mushroom3")//checks condition.
					{
						mushroom_three = true;//sets bool to true.
					}
					if (ball_contact_name == "mushroom4")//checks condition.
					{
						mushroom_four = true;//sets bool to true.
					}
					if (ball_contact_name == "mushroom5")//checks condition.
					{
						mushroom_five = true;//sets bool to true.
					}
					if (ball_contact_name == "platform_mushroom1")//checks condition.
					{
						platform_mushroom_one = true;//sets bool to true.
					}
					if (ball_contact_name == "platform_mushroom2")//checks condition.
					{
						platform_mushroom_two = true;//sets bool to true.
					}
					if (ball_contact_name == "platform_mushroom2")//checks condition.
					{
						platform_mushroom_three = true;//sets bool to true.
					}
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
					top_right_wall_force = false;//sets bool to false.
					back_wall_force = false;//sets bool to false.
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{	
		MySimulationEventCallback* my_callback;
		Plane* plane;//creates the plabe which the game rests on.

		Enclosure* table;//declares variable for the table.
		Sphere* ball_bearing;//declares variable for the ball.

		TopRightWall* top_right_wall;//declares variable for the top right wall triangle.
		BackLeftWall* back_left_wall;//declares variable for the back left wall triangle.
		BackRightWall* back_right_wall;//declares variable for the back right wall triangle.
		BackWall* back_wall;//declares varaible for the backwall trigger.

		RightBallChute* right_ball_chute;//declares varaible for the right ball chute.
		LeftBallChute* left_ball_chute;//declares varaible for the left ball chute.
		GuideWall* guide_wall;//declares the variable for the guide wall that direct the ball into the table.

		ResetGame* reset_game;//declares the varaible for the square that will reset the game.

		Plunger* plunger;//declares varaible for the plunger.

		LeftFlipper* left_flipper;//declares varables for the left flipper.
		RightFlipper* right_flipper;//declares variables for the right flipper.
		ExtraLeftFlipper* extra_left_flipper;//declares variable for the extra left flipper.
		ExtraRightFlipper* extra_right_flipper;//declares vaaible for the extra right flipper.

		RevoluteJoint* leftflipper_joint, *extra_leftflipper_joint;//declares varaibles for the two joints of the left flippers.
		RevoluteJoint* rightflipper_joint, *extra_rightflipper_joint;//declares varaibles for the two joints of the right flippers.

		LeftBumper* left_bumper;//declares variable for the left bumper.
		RightBumper* right_bumper;//declares variavbe for the right bumper.

		SpeedBoost* speed_boost, *speed_boost2, *speed_boost3;//declares variable for the speed boosts.

		Windmill* windmill, *windmill2;//declares variables for the windmills.
		RevoluteJoint* windmill_joint, *windmill_joint2;//declares variables for the windmill joints.

		Mushroom* mushroom, *mushroom2, *mushroom3, *mushroom4, *mushroom5;//declares variables for the mushrooms.
		Mushroom* platform_mushroom, *platform_mushroom2, *platform_mushroom3;//declres variables for the platform mushrooms.

		Platform* platform;//declares varaible for the platform.
	
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene(&CustomFilterShader) {};

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
			
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();//enables display of the level.		
			GetMaterial()->setDynamicFriction(.2f);//sets default friction of the level.

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			PxMaterial* ball_bearing_material = CreateMaterial(0.0f, 0.0f, 0.597f);//creates the material for the ball, accurate COE of a steel ball bearing.
			PxMaterial* bumper_material = CreateMaterial(0.0f, 0.0f, 2.0f);
			PxMaterial* spring_wall_material = CreateMaterial(0.0f, 0.0f, 1.0f);
			PxMaterial* mushroom_material = CreateMaterial(0.0f, 0.0f, 2.0f);

			plane = new Plane();//creates the plane which the table rests on.
			plane->Color(PxVec3(0.f,0.f,0.f));//sets the colour of the plane to "grey".
			plane->SetupFiltering(FilterGroup::PLANE, FilterGroup::BALL);
			plane->Name("plane");//sets the name of the object to "plane"
			Add(plane);//adds plane to the scene.

			ball_bearing = new Sphere(PxTransform(PxVec3(-0.5f, 3.0f, -10.5f)), PxReal(0.3f));//(PxTransform(PxVec3(-0.6f, 5.0f, -10.5f)), PxReal(0.3f));
			ball_bearing->Material(ball_bearing_material);//sets the material property of the ball to "ball_bearing_material".
			ball_bearing->Color(color_palette[3]);//sets the colour of the object.
			ball_bearing->SetupFiltering(FilterGroup::BALL, FilterGroup::TOP_RIGHT_WALL|FilterGroup::BACK_WALL|FilterGroup::RESET_GAME|FilterGroup::TABLE|FilterGroup::LEFT_BALL_CHUTE
			|FilterGroup::BACK_LEFT_WALL | FilterGroup::BACK_RIGHT_WALL | FilterGroup::GUIDE_WALL | FilterGroup::LEFT_FLIPPER | FilterGroup::RIGHT_FLIPPER|FilterGroup::PLANE|FilterGroup::RIGHT_BALL_CHUTE
			|FilterGroup::EXTRA_LEFT_FLIPPER|FilterGroup::EXTRA_RIGHT_FLIPPER|FilterGroup::SPEED_BOOST|FilterGroup::LEFT_BUMPER|FilterGroup::RIGHT_BUMPER|FilterGroup::WINDMILL|FilterGroup::MUSHROOM
			|FilterGroup::PLATFORM);//sets the filter groups up for the ball.
			ball_bearing->Name("ball_bearing");//sets the name of the ball to "ball_bearing".
			Add(ball_bearing);//adds the ball to the scene.
			PxRigidDynamic* CCDball_bearing = (PxRigidDynamic*)ball_bearing->Get();//converts the ball to a rigid dynamic for CCD conversion.
			CCDball_bearing->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the ball.

			table = new Enclosure(PxTransform(PxVec3(0.f, 0.5f, 0.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));// Creates table and sets it to 6 degress of tilt.
			table->SetupFiltering(FilterGroup::TABLE, FilterGroup::BALL);//sets up filter groups for the table.
			table->Name("table");//sets the name of the object to "table"
			Add(table);//adds the table to the scene.

			top_right_wall = new TopRightWall(PxTransform(PxVec3(-0.2f, 7.05f, -34.3f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the triangle that sits in the top right of the pinball table.
			top_right_wall->Color(color_palette[1]);//sets the colour of the object.
			top_right_wall->SetupFiltering(FilterGroup::TOP_RIGHT_WALL, FilterGroup::BALL);//sets up filter groups for the top right wall.
			top_right_wall->Name("top_right_wall");//names the object "top_right_wall"
			Add(top_right_wall);//add the top right wall to the scene.

			back_left_wall = new BackLeftWall(PxTransform(PxVec3(-20.0f, 0.5f, -0.1f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the triangle to sit in the back left of the table.
			back_left_wall->Color(color_palette[1]);//sets the colour of the object.
			back_left_wall->SetupFiltering(FilterGroup::BACK_LEFT_WALL, FilterGroup::BALL);//sets up filter groups of the back left wall.
			back_left_wall->Name("back_left_wall");//sets the name of the object to "back left wall."
			Add(back_left_wall);//adds the back left wall to the scene.

			back_right_wall = new BackRightWall(PxTransform(PxVec3(-1.5f, 0.5f, -0.1f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//create the triangle to sit in the back right of the table.
			back_right_wall->Color(color_palette[1]);//sets the colour of the object.
			back_right_wall->SetupFiltering(FilterGroup::BACK_RIGHT_WALL, FilterGroup::BALL);//sets up filter groups for the back right wall.
			back_right_wall->Name("back_right_wall");//sets the name of the object to "back right wall"
			Add(back_right_wall);//adds the back right wall to the scene.

			back_wall = new BackWall(PxTransform(PxVec3(-6.1f, 8.15f, -39.97f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the wall to sit at the back of the table.
			back_wall->Color(color_palette[1]);//sets the colour of the object.
			back_wall->SetupFiltering(FilterGroup::BACK_WALL, FilterGroup::BALL);//sets up filter groups for the back wall.
			back_wall->Name("back_wall");//names the object "back_wall"
			Add(back_wall);//adds the back wall to the scene.

			left_ball_chute = new LeftBallChute(PxTransform(PxVec3(-19.8f, 0.5f, -0.1f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the chute that the ball will travel up at the start of the game.
			left_ball_chute->Material(spring_wall_material);
			left_ball_chute->Color(color_palette[1]);//sets the colour of the object.
			left_ball_chute->SetupFiltering(FilterGroup::LEFT_BALL_CHUTE, FilterGroup::BALL);//sets up filter groups for the ball chute.
			left_ball_chute->Name("left_ball_chute");//sets the name of the object to "ball chute".
			Add(left_ball_chute);//adds the ball chute to the scene.

			right_ball_chute = new RightBallChute(PxTransform(PxVec3(-1.5f, 0.5f, -0.1f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the chute that the ball will travel up at the start of the game.
			right_ball_chute->Material(spring_wall_material);
			right_ball_chute->Color(color_palette[1]);//sets the colour of the object.
			right_ball_chute->SetupFiltering(FilterGroup::RIGHT_BALL_CHUTE, FilterGroup::BALL);//sets up filter groups for the ball chute.
			right_ball_chute->Name("right_ball_chute");//sets the name of the object to "ball chute".
			Add(right_ball_chute);//adds the ball chute to the scene.

			guide_wall = new GuideWall(PxTransform(PxVec3(-0.1f, 6.22f, -30.f), PxQuat(6.f *(PxPi / 100), PxVec3(1.f, 1.0f, 0.f)) * PxQuat(-30.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))));//creates the guide wall which sends the ball into the table.
			guide_wall->Color(color_palette[1]);//sets the colour of the object.
			guide_wall->SetupFiltering(FilterGroup::GUIDE_WALL, FilterGroup::BALL);//sets up filter groups for the guide wall.
			guide_wall->Name("guide_wall");//sets the name of the object to "guide wall".
			Add(guide_wall);//adds the guide wall to the scene.

			reset_game = new ResetGame(PxTransform(PxVec3(-12.23f, 0.75f, -0.35f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the square which resets the game when overlapped
			reset_game->Color(color_palette[1]);//sets the colour of the object.
			reset_game->SetupFiltering(FilterGroup::RESET_GAME, FilterGroup::BALL);//sets up filter groups for the reset game function.
			reset_game->Name("reset_game");//names the object "reset_game"
			Add(reset_game);//adds the rest game square to the scene.

			left_flipper = new LeftFlipper(PxTransform(PxVec3(-15.f, -4.5f, -10.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the left flipper.
			left_flipper->Color(color_palette[1]);//sets the colour of the object.
			left_flipper->SetupFiltering(FilterGroup::LEFT_FLIPPER, FilterGroup::BALL);//sets up filter groups for the left flipper.
			left_flipper->Name("left_flipper");//names the object "left flipper"
			Add(left_flipper);//adds the object to the scene.
			PxRigidDynamic* CCDleft_flipper = (PxRigidDynamic*)left_flipper->Get();//converts the left flipper to a rigid dynamic for CCD conversion.
			CCDleft_flipper->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the left flipper.

			leftflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-13.5f, 1.75f, -5.f), PxQuat(45.f *(PxPi / 100), PxVec3(0.f, 0.0f, 1.f)) * PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), left_flipper, PxTransform(PxVec3(0.25f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))));
			leftflipper_joint->SetLimits(-0.33f, 0.78f);

			right_flipper = new RightFlipper(PxTransform(PxVec3(-15.f, 4.5f, -10.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the right flipper.
			right_flipper->Color(color_palette[1]);//sets the colour of the object.
			right_flipper->SetupFiltering(FilterGroup::RIGHT_FLIPPER, FilterGroup::BALL);//sets up filter groups for the right flipper.
			right_flipper->Name("right_flipper");//names the object "right flipper".
			Add(right_flipper);//adds the object to the scene.
			PxRigidDynamic* CCDright_flipper = (PxRigidDynamic*)right_flipper->Get();//converts the right flipper to a rigid dynamic for CCD conversion.
			CCDright_flipper->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the right flipper.

			rightflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-7.5f, 1.4f, -5.f), PxQuat(45.f *(PxPi / 100), PxVec3(0.f, 0.0f, 1.f)) * PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), right_flipper, PxTransform(PxVec3(-0.25f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))));
			rightflipper_joint->SetLimits(-0.75f, 0.40f);

			extra_left_flipper = new ExtraLeftFlipper(PxTransform(PxVec3(-15.f, 4.3f, -10.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the extra left flipper.
			extra_left_flipper->Color(color_palette[1]);//sets the colour of the object.
			extra_left_flipper->SetupFiltering(FilterGroup::EXTRA_LEFT_FLIPPER, FilterGroup::BALL);//sets up filter groups for the extra left flipper.
			extra_left_flipper->Name("extra_left_flipper");//names the object "extra left flipper"
			Add(extra_left_flipper);//adds the object to the scene.
			PxRigidDynamic* CCDextra_left_flipper = (PxRigidDynamic*)extra_left_flipper->Get();//converts the extra left flipper to a rigid dynamic for CCD conversion.
			CCDextra_left_flipper->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the extra left flipper.

			extra_leftflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-17.0f, 2.75f, -9.8f), PxQuat(45.f *(PxPi / 100), PxVec3(0.f, 0.0f, 1.f)) * PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), extra_left_flipper, PxTransform(PxVec3(0.25f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))));
			extra_leftflipper_joint->SetLimits(-0.33f, 0.78f);

			extra_right_flipper = new ExtraRightFlipper(PxTransform(PxVec3(-15.f, 4.5f, -20.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));//creates the extra right flipper.
			extra_right_flipper->Color(color_palette[1]);//sets the colour of the object.
			extra_right_flipper->SetupFiltering(FilterGroup::EXTRA_RIGHT_FLIPPER, FilterGroup::BALL);//sets up filter groups for the extra right flipper.
			extra_right_flipper->Name("extra_right_flipper");//names the object "extra right flipper".
			Add(extra_right_flipper);//adds the object to the scene.
			PxRigidDynamic* CCDextra_right_flipper = (PxRigidDynamic*)extra_right_flipper->Get();//converts the extra right flipper to a rigid dynamic for CCD conversion.
			CCDextra_right_flipper->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);//enables CCD for the extra right flipper.

			extra_rightflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-3.5f, 2.5f, -10.f), PxQuat(45.f *(PxPi / 100), PxVec3(0.f, 0.0f, 1.f)) * PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), extra_right_flipper, PxTransform(PxVec3(-0.25f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))));
			extra_rightflipper_joint->SetLimits(-0.75f, 0.40f);

			left_bumper = new LeftBumper(PxTransform(PxVec3(-16.8f, 1.5f, -5.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the left bumper.
			left_bumper->Material(bumper_material);//sets the material of the bumper.
			left_bumper->Color(color_palette[1]);//sets the colour of the object.
			left_bumper->SetupFiltering(FilterGroup::LEFT_BUMPER, FilterGroup::BALL);//sets up filter groups for the left bumper.
			Add(left_bumper);//adds the object to the scene.

			right_bumper = new RightBumper(PxTransform(PxVec3(-4.0f, 1.5f, -5.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the right bumper.
			right_bumper->Material(bumper_material);//sets the maerial of the bumper.
			right_bumper->Color(color_palette[1]);//sets the colour of the object.
			right_bumper->SetupFiltering(FilterGroup::RIGHT_BUMPER, FilterGroup::BALL);//sets up filter groups for the right bumper.
			Add(right_bumper);//adds the object to the scene.

			speed_boost = new SpeedBoost(PxTransform(PxVec3(-10.0f, 2.98f, -13.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the right bumper.
			speed_boost->Color(color_palette[1]);//sets the colour of the object.
			speed_boost->SetupFiltering(FilterGroup::SPEED_BOOST, FilterGroup::BALL);//sets up filter groups for the speed boost.
			speed_boost->Name("speed_boost");//sets the name of the object to "speed boost"
			Add(speed_boost);//adds the object to the scene.

			speed_boost2 = new SpeedBoost(PxTransform(PxVec3(-17.0f, 2.98f, -13.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the right bumper.
			speed_boost2->Color(color_palette[1]);//sets the colour of the object.
			speed_boost2->SetupFiltering(FilterGroup::SPEED_BOOST, FilterGroup::BALL);//sets up filter groups for the speed boost.
			speed_boost2->Name("speed_boost");//sets the name of the object to "speed boost"
			Add(speed_boost2);//adds the object to the scene.

			speed_boost3 = new SpeedBoost(PxTransform(PxVec3(-13.5f, 3.362f, -15.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the right bumper.
			speed_boost3->Color(color_palette[1]);//sets the colour of the object.
			speed_boost3->SetupFiltering(FilterGroup::SPEED_BOOST, FilterGroup::BALL);//sets up filter groups for the speed boost.
			speed_boost3->Name("speed_boost");//sets the name of the object to "speed boost"
			Add(speed_boost3);//adds the object to the scene.

			plunger = new Plunger();//creates the plunger.
			plunger->AddToScene(this);//adds the plunger to the scene.

			windmill = new Windmill(PxTransform(PxVec3(-50.0f, 0.5f, 0.0f), PxQuat(6 * (PxPi /100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the windmill
			windmill->Color(color_palette[1]);//sets the colour of the object.
			windmill->SetupFiltering(FilterGroup::WINDMILL, FilterGroup::BALL);//sets up filter groups for the speed boost.
			windmill->Name("windmill");//sets the name of the object to "windmill"
			Add(windmill);//adds the object to the scene.

			windmill_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-15.0f, 4.9f, -20.f), PxQuat(50 * (PxPi / 100), PxVec3(0.f, 1.f, 0.f)) * PxQuat(-45 * (PxPi /100), PxVec3(0.0, 0.0, 1.0))), windmill, PxTransform(PxVec3(0.f, 0.5f, 0.f)));
			windmill_joint->DriveVelocity(5);

			windmill2 = new Windmill(PxTransform(PxVec3(-50.0f, 0.5f, 0.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the windmill
			windmill2->Color(color_palette[1]);//sets the colour of the object.
			windmill2->SetupFiltering(FilterGroup::WINDMILL, FilterGroup::BALL);//sets up filter groups for the speed boost.
			windmill2->Name("windmill2");//sets the name of the windmill to "windmill2"
			Add(windmill2);//adds the object to the scene.

			windmill_joint2 = new RevoluteJoint(NULL, PxTransform(PxVec3(-6.0f, 4.9f, -20.f), PxQuat(50 * (PxPi / 100), PxVec3(0.f, 1.f, 0.f)) * PxQuat(-45 * (PxPi / 100), PxVec3(0.0, 0.0, 1.0))), windmill2, PxTransform(PxVec3(0.f, 0.5f, 0.f)));
			windmill_joint2->DriveVelocity(-5);

			mushroom = new Mushroom(PxTransform(PxVec3(-4.0f, 3.5f, -16.5f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			mushroom->Material(mushroom_material);//applys material to the object
			mushroom->Color(color_palette[1]);//sets the colour of the object.
			mushroom->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			mushroom->Name("mushroom1");//ets the name of the object to "mushroom".
			Add(mushroom);//adds the object to the scene.

			mushroom2 = new Mushroom(PxTransform(PxVec3(-18.0f, 3.5f, -16.5f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			mushroom2->Material(mushroom_material);//applys material to the object
			mushroom2->Color(color_palette[1]);//sets the colour of the object.
			mushroom2->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			mushroom2->Name("mushroom2");//sets the name of the object to "mushroom2"
			Add(mushroom2);//adds the object to the scene.

			mushroom3 = new Mushroom(PxTransform(PxVec3(-11.0f, 5.25f, -25.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			mushroom3->Material(mushroom_material);//applys material to the object
			mushroom3->Color(color_palette[1]);//sets the colour of the object.
			mushroom3->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			mushroom3->Name("mushroom3");//sets the name of the object to "mushroom3"
			Add(mushroom3);//adds the object to thr scene.

			mushroom4 = new Mushroom(PxTransform(PxVec3(-8.0f, 5.5f, -27.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			mushroom4->Material(mushroom_material);//applys material to the object
			mushroom4->Color(color_palette[1]);//sets the colour of the object.
			mushroom4->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			mushroom4->Name("mushroom4");//sets the name of the object to "mushroom4"
			Add(mushroom4);//adds the object to the scene.

			mushroom5 = new Mushroom(PxTransform(PxVec3(-14.0f, 5.5f, -27.0f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			mushroom5->Material(mushroom_material);//applys material to the object
			mushroom5->Color(color_palette[1]);//sets the colour of the object.
			mushroom5->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			mushroom5->Name("mushroom5");//sets the name of the object to "mushroom5"
			Add(mushroom5);//adds the object to the scene.

			platform = new Platform(PxTransform(PxVec3(-5.7f, 9.25f, -38.79f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the platform.
			platform->Color(color_palette[9]);//sets the colour of the object.
			platform->SetupFiltering(FilterGroup::PLATFORM, FilterGroup::BALL);//sets up filter groups for the platform.
			platform->Name("platform");//sets the name of the object to "platform"
			Add(platform);//adss the object to scene.

			platform_mushroom = new Mushroom(PxTransform(PxVec3(-16.0f, 8.8f, -36.5f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			platform_mushroom->Material(mushroom_material);//applys material to the object
			platform_mushroom->Color(color_palette[1]);//sets the colour of the object.
			platform_mushroom->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			platform_mushroom->Name("platform_mushroom1");//sets the name of the object to "mushroom5"
			Add(platform_mushroom);//adds the object to the scene.

			platform_mushroom2 = new Mushroom(PxTransform(PxVec3(-13.0f, 8.8f, -36.5f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			platform_mushroom2->Material(mushroom_material);//applys material to the object
			platform_mushroom2->Color(color_palette[1]);//sets the colour of the object.
			platform_mushroom2->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			platform_mushroom2->Name("platform_mushroom2");//sets the name of the object to "mushroom5"
			Add(platform_mushroom2);//adds the object to the scene.

			platform_mushroom3 = new Mushroom(PxTransform(PxVec3(-10.0f, 8.8f, -36.5f), PxQuat(6 * (PxPi / 100), PxVec3(1.0f, 0.0f, 0.0f))));//creates the mushroom
			platform_mushroom3->Material(mushroom_material);//applys material to the object
			platform_mushroom3->Color(color_palette[1]);//sets the colour of the object.
			platform_mushroom3->SetupFiltering(FilterGroup::MUSHROOM, FilterGroup::BALL);//sets up filter groups for the mushroom.
			platform_mushroom3->Name("platform_mushroom3");//sets the name of the object to "mushroom5"
			Add(platform_mushroom3);//adds the object to the scene.

		}
		//Custom udpate function
		virtual void CustomUpdate() 
		{
			PxRigidDynamic* RDball_bearing = (PxRigidDynamic*)ball_bearing->Get();//converts the ball to a rigid dynamic.
			if (top_right_wall_force == true)
			{
				RDball_bearing->addForce(PxVec3(-10.0f, 0.0f, 10.0f));//adds force to the ball when it comes into contact with the top right wall.
				top_right_wall_force == false;//sets the bool to false.
			}
			if (back_wall_force == true)
			{
				RDball_bearing->addForce(PxVec3(0.0f, 0.0f, 250.0f));//adds force to the ball when it comes into contact with the top right wall.
				back_wall_force == false;//sets the bool to false;
			}
			if (game_reset == true)//geme reset function
			{
				RDball_bearing->setLinearVelocity(PxVec3(0, 0, 0));//resets velocity on thr ball.
				RDball_bearing->clearForce();//clears all force from the ball.
				RDball_bearing->setGlobalPose(PxTransform(PxVec3(-0.5f, 3.0f, -10.5f)));//sets the balls pose to orginal.
				game_reset = false;//resets the bool to false;

				mushroom->Color(color_palette[1]);//changes colour of object
				mushroom2->Color(color_palette[1]);//changes colour of object
				mushroom3->Color(color_palette[1]);//changes colour of object
				mushroom4->Color(color_palette[1]);//changes colour of object
				mushroom5->Color(color_palette[1]);//changes colour of object

			}
			if (oob_reset == true)//out of bounds function.
			{
				RDball_bearing->setLinearVelocity(PxVec3(0, 0, 0));//resets velocity on thr ball.
				RDball_bearing->clearForce();//clears all force from the ball.
				RDball_bearing->setGlobalPose(PxTransform(PxVec3(-0.5f, 3.0f, -10.5f)));//sets the balls pose to orginal.
				game_reset = false;//resets the bool to false;

				mushroom->Color(color_palette[1]);//changes colour of object
				mushroom2->Color(color_palette[1]);//changes colour of object
				mushroom3->Color(color_palette[1]);//changes colour of object
				mushroom4->Color(color_palette[1]);//changes colour of object
				mushroom5->Color(color_palette[1]);//changes colour of object

			}
			if (activate_speed_boost == true)
			{
				RDball_bearing->addForce(PxVec3(0.0f, 0.0f, -25.0f));//adds force to the ball when it hits the speed boost.
				activate_speed_boost = false;//rests the bool to flase.
			}	
			if (mushroom_one == true)
			{
				mushroom->Color(color_palette[9]);//changes colour of object
				mushroom_one = false;//resets the bool to false;
			}
			if (mushroom_two == true)
			{
				mushroom2->Color(color_palette[9]);//changes colour of object
				mushroom_two = false;//resets the bool to false;
			}
			if (mushroom_three == true)
			{
				mushroom3->Color(color_palette[9]);//changes colour of object
				mushroom_three = false;//resets the bool to false;
			}
			if (mushroom_four == true)
			{
				mushroom4->Color(color_palette[9]);//changes colour of object
				mushroom_four = false;//resets the bool to false;
			}
			if (mushroom_five == true)
			{
				mushroom5->Color(color_palette[9]);//changes colour of object
				mushroom_five = false;//resets the bool to false;
			}
			if (platform_mushroom_one == true)
			{
				platform_mushroom->Color(color_palette[9]);//changes colour of object
				platform_mushroom_one = false;//resets the bool to false;
			}
			if (platform_mushroom_two == true)
			{
				platform_mushroom2->Color(color_palette[9]);//changes colour of object
				platform_mushroom_two = false;//resets the bool to false;
			}
			if (platform_mushroom_three == true)
			{
				platform_mushroom3->Color(color_palette[9]);//changes colour of object
				platform_mushroom_three = false;//resets the bool to false;
			}
		}
		void setLeftVelocityforward()
		{
			((PxRigidDynamic*)left_flipper->Get())  ->wakeUp();//wakes up and then gets the object.
			leftflipper_joint->DriveVelocity(+20);//adds force to the joint
			extra_leftflipper_joint->DriveVelocity(+20);//adds force to the joint
		}
		void setLeftVelocitybackward()
		{
			((PxRigidDynamic*)left_flipper->Get()) ->wakeUp();//wakes up and then gets the object.
			leftflipper_joint->DriveVelocity(-20);//removes force from the joint.
			extra_leftflipper_joint->DriveVelocity(-20);//removes force from the joint.
		}
		void setRightVelocityforward()
		{
			((PxRigidDynamic*)right_flipper->Get()) ->wakeUp();//wakes up and then gets the object.
			rightflipper_joint->DriveVelocity(-20);//removes force from the joint.
			extra_rightflipper_joint->DriveVelocity(-20);//removes force from the joint.
		}
		void setRightVelocitybackward()
		{
			((PxRigidDynamic*)right_flipper->Get()) ->wakeUp();//wakes up and then gets the object.
			rightflipper_joint->DriveVelocity(+20);//adds force to the joint
			extra_rightflipper_joint->DriveVelocity(+20);//adds force to the joint
		}
	};
}
