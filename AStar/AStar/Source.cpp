#include "Node.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int startx, starty;
int endx, endy;

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

int map[MAP_WIDTH * MAP_HEIGHT] =
{
	//x
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,//y
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1,
	9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1,
	9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1,
	9, 1, 1, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 9, 9, 9, 1, 1, 9, 9,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 9, 9, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 9, 9, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 9,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 9, 9, 9, 9, 1, 1, 9, 9, 9, 1, 9, 9, 1, 1, 9, 9, 9, 9, 9,
	9, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 1, 1, 1, 1, 1, 9,
	9, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1,
	9, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1,

};//map to pathfind on, 20x20 grid.
int GetMap(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
	{
		return 9;
	}
	return map[(y*MAP_WIDTH) + x];
}
class MapSearchNode
{
public:
	int x;//the x position of the node.
	int y;//the y position of the node.

	MapSearchNode() { x = y = 0; }
	MapSearchNode(int px, int py) { x = px; y = py; }

	float GoalDistanceEstimate(MapSearchNode &nodeGoal);
	bool IsGoal(MapSearchNode &nodeGoal);
	bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node);
	float GetCost(MapSearchNode &successor);
	bool IsSameState(MapSearchNode &rhs);

	void PrintNodeInfo();
};
bool MapSearchNode::IsSameState(MapSearchNode &rhs)
{
	if ((x == rhs.x) && (y == rhs.y))//same state is when x and y are the same.
	{
		return true;
	}
	else
	{
		return false;
	}
}
void MapSearchNode::PrintNodeInfo()//prints the position of the current node.
{
	char str[100];
	sprintf_s(str, "In Co-Ordinate Position : (%d,%d)\n", x, y);
	cout << str;
}
float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal)//estimates the distance from a node to the goal.
{
	float xd = float(((float)x - (float)nodeGoal.x));
	float yd = float(((float)y - (float)nodeGoal.y));
	return xd + yd;
}
bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal)//checks if node is the goal.
{
	if ((x == nodeGoal.x) && (y == nodeGoal.y))
	{
		return true;
	}
	return false;
}
bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node)//generates succesors to a given node.
{
	int parent_x = -1;
	int parent_y = -1;

	if (parent_node)
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	MapSearchNode NewNode;

	if ((GetMap(x - 1, y) < 9) && !((parent_x == x - 1) && (parent_y == y)))// <9
	{
		NewNode = MapSearchNode(x - 1, y);
		astarsearch->AddSuccessor(NewNode);
	}
	if ((GetMap(x, y - 1) < 9) && !((parent_x == x) && (parent_y == y - 1)))
	{
		NewNode = MapSearchNode(x, y - 1);
		astarsearch->AddSuccessor(NewNode);
	}
	if ((GetMap(x + 1, y) < 9) && !((parent_x == x + 1) && (parent_y == y)))
	{
		NewNode = MapSearchNode(x + 1, y);
		astarsearch->AddSuccessor(NewNode);
	}
	if ((GetMap(x, y + 1) < 9) && !((parent_x == x) && (parent_y == y + 1)))
	{
		NewNode = MapSearchNode(x, y + 1);
		astarsearch->AddSuccessor(NewNode);
	}
	return true;
}
float MapSearchNode::GetCost(MapSearchNode &successor)
{
	return (float)GetMap(x, y);
}
void main(int argc, char *argv[])
{
	AStarSearch<MapSearchNode> astarsearch;
	unsigned int SearchCount = 0;
	const unsigned int NumSearches = 1;

	while (SearchCount < NumSearches)
	{
		cout << "Welcome to Jack's pathfinding program!\n";
		cout << "Here is your map! 9`s represent walls and 1`s represent walkable space.";

		cout << "\n\n9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\n";
		cout << "9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,9,9,\n";
		cout << "9,9,9,9,9,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,\n";
		cout << "9,9,9,9,9,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,\n";
		cout << "9,9,9,9,9,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,\n";
		cout << "9,9,9,9,9,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,\n";
		cout << "9,1,1,1,1,1,1,9,9,1,1,1,1,9,1,1,1,1,1,1,\n";
		cout << "1,1,1,1,1,1,1,9,9,1,1,1,1,9,9,9,1,1,9,9,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\n";
		cout << "1,1,1,1,1,9,9,1,1,1,9,9,1,1,1,1,1,1,1,1,\n";
		cout << "1,1,1,1,1,9,9,1,1,1,9,9,1,1,1,1,1,1,1,9,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\n";
		cout << "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\n";
		cout << "1,9,9,9,9,1,1,9,9,9,1,9,9,1,1,9,9,9,9,9,\n";
		cout << "9,1,1,1,1,1,1,1,9,9,1,9,9,1,1,1,1,1,1,9,\n";
		cout << "9,1,1,1,1,1,1,1,9,9,1,1,9,1,1,1,1,1,1,1,\n";
		cout << "9,1,1,1,1,1,1,1,9,9,9,9,9,1,1,1,1,1,1,1,\n\n";

		cout << "Please enter the x start co-ordinate!\n";
		cin >> startx;

		cout << "Please enter the y start co-ordinate!\n";
		cin >> starty;

		cout << "Please enter the x end co-ordinate!\n";
		cin >> endx;

		cout << "Please enter the y end co-ordinate!\n";
		cin >> endy;

		MapSearchNode nodeStart;//creates a start node.                               
		nodeStart.x = startx;
		nodeStart.y = starty;

		MapSearchNode nodeEnd;//creates an end node.										
		nodeEnd.x = endx;
		nodeEnd.y = endy;

		astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);//sets start and end nodes.

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();
			SearchSteps++;
		} while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);
		if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)//if path found.
		{
			cout << "Found a path to the end!\n";
			MapSearchNode *node = astarsearch.GetSolutionStart();

			int steps = 0;

			node->PrintNodeInfo();
			for (;;)
			{
				node = astarsearch.GetSolutionNext();

				if (!node)
				{
					break;
				}

				node->PrintNodeInfo();
				steps++;
			};

			cout << "Steps from start to end : " << steps << endl;
			astarsearch.FreeSolutionNodes();
		}
		else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED)//if path not found.
		{
			cout << "Search terminated. Did not find the end. \n";
		}
		cout << "Amount of paths searched : " << SearchSteps << "\n";
		SearchCount++;
		astarsearch.EnsureMemoryFreed();

	}
	cin.get();
	cin.get();
}