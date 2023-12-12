#include "Maze.h"
#include "Diamond.cpp"
#include "Player.cpp"
#include "Pottery.cpp"
#include "Malfoy.cpp"
#include "iostream"
#include "ncurses.h"
#include "fstream"
#include "string"
#include "vector"
#include "stack"
#include "queue"

#define ESC_KEY 27 

using namespace std;

Maze::Maze(WINDOW *w, int lines, int columns, Player *pot, Player *mal)
{
	win = w;
	this->lines = lines;
	this->columns = columns;
	adj = new vector<int>[lines*columns];
	pottery = pot;
	malfoy = mal;
}

Maze::Maze(WINDOW *w, Player *pot, Player *mal)
{
	win = w;
	pottery = pot;
	malfoy = mal;
}

Maze::~Maze()
{
	delete win;
	delete[] adj;
	delete pottery;
	delete malfoy;
}

bool Maze::readMap(const char* fileName)
{
	string line;
	ifstream mapFile;
	int i, j, dy;
	
	i = 0;
	mapFile.open(fileName, ios::in);
	if (!mapFile) return false;
	
	while(getline(mapFile, line))
	{
		map.insert(map.end(), line);
		++i;
	}
	lines = i;
	if (lines  > 0 && map[0].size() > 0) columns = map[0].size();
	else return false;
		
	adj = new vector<int>[lines*columns];
	return true;
}

int Maze::handleTrigger(const int ch)
{
	int k,won;
	bool hasmoved, validmove;
	int nextX, nextY;

	k=0;
	won = 0;
	
	if (ch == ESC_KEY) return -1;
	
	validmove = pottery->validMove(ch);
	if (validmove) 
	{
		hasmoved = pottery->move(map);
		if (hasmoved)
		{
			diamond.reduceMoves();
			won = won + pottery->hasWon(diamond.getPosx(), diamond.getPosy());
			if (won != 0) return won;
			
			nextX = getMalfoyNextX();
			nextY = getMalfoyNextY();
			malfoy->setCurrentX(nextX);
			malfoy->setCurrentY(nextY);
			won = won + malfoy->hasWon(diamond.getPosx(), diamond.getPosy());
		}
	}
	return won;
}

void Maze::draw(bool firstDraw) 
{
	int i, j, dy;
	int X_diam, Y_diam;
	int X_pot, Y_pot;
	int X_mal, Y_mal;
	bool d_spawned;
	int src, dest;

	d_spawned = diamond.spawn(map, lines, columns);
	X_diam = diamond.getPosx();
	Y_diam = diamond.getPosy();
	
	if (firstDraw)
	{
		findNeighbours();
		do
		{
			pottery->spawn(map, lines, columns);
			malfoy->spawn(map, lines, columns);
			X_pot = pottery->getCurrentX();
			Y_pot = pottery->getCurrentY();
			X_mal = malfoy->getCurrentX();
			Y_mal = malfoy->getCurrentY();
			
			pottery->setSpawned(false);
			malfoy->setSpawned(false);
		}
		while (X_pot == X_mal && Y_pot == Y_mal);
		
		pottery->setSpawned(true);
		malfoy->setSpawned(true);
	}
	
	X_pot = pottery->getCurrentX();
	Y_pot = pottery->getCurrentY();
	X_mal = malfoy->getCurrentX();
	Y_mal = malfoy->getCurrentY();
	
	if (d_spawned)
	{
		src = (X_mal * columns) + Y_mal;
		dest = (X_diam * columns) + Y_diam;
		findShortestPath(src, dest);	
	}
	
	for (i=0; i<lines; i++ )
	{
		dy = 0;
		for (j=0; j<columns; j++ )
		{	
		
			if (map[i][j] == '*')
				mvwprintw(win, i, dy, "###");
			else if (map[i][j] == '.')
			{
				if (i == X_diam && j == Y_diam)
				{
					init_pair(3, COLOR_BLACK, COLOR_CYAN);
					wattron(win, COLOR_PAIR(3));
					mvwprintw(win, i, dy, "\\^/");
					wattroff(win, COLOR_PAIR(3));
				}
				else if (i == X_pot && j == Y_pot)
				{
					init_color(COLOR_BLUE, 1000, 645, 0);
					init_pair(1, COLOR_BLACK, COLOR_BLUE);
					wattron(win, COLOR_PAIR(1));
					mvwprintw(win, i, dy, "|M|");
					wattroff(win, COLOR_PAIR(1));
				}
				else if (i == X_mal && j == Y_mal)
				{
					init_pair(2, COLOR_BLACK, COLOR_GREEN);
					wattron(win, COLOR_PAIR(2));
					mvwprintw(win, i, dy, "|L|");
					wattroff(win, COLOR_PAIR(2));
				}
				else
					mvwprintw(win, i, dy,"   ");	
			}
			dy = dy + 3;
			
		}
	}
}

void Maze::findNeighbours()
{
	int i, j;
	int node_id, neighbour_id;
	
	for (i=0; i<lines; i++)
	{
		for (j=0; j<columns; j++) 
		{
			
			if (map[i][j] == '.')
			{
				node_id = (i * columns) + j;
				if (i % 2 == 1 && map[i-1][j] == '.')
				{
					neighbour_id = ((i-1) * columns) + j;
					adj[node_id].push_back(neighbour_id);
					adj[neighbour_id].push_back(node_id);
				}
				
				if (i % 2 == 1 && map[i+1][j] == '.')
				{
					neighbour_id = ((i+1) * columns) + j;
					adj[node_id].push_back(neighbour_id);
					adj[neighbour_id].push_back(node_id);
				}
				if (map[i][j+1] == '.')
				{
					neighbour_id = (i * columns) + j + 1;
					adj[node_id].push_back(neighbour_id);
					adj[neighbour_id].push_back(node_id);
				}
			}
		}
	
	}
}

void Maze::BFS (int src, int dest, vector<int> &parent, vector<int> &dist)
{
	int V = lines * columns;
        vector<bool> vis(V, 0); // Διάνυσμα αποθήκευσης των επισκευθέντων κόμβων. 
        queue<int> q; // Στοίβα αποθήκευσης των κόμβων που πρόκειται να επισκευθούν κατά πλάτος.
        q.push(src); 
        vis[src] = 1;
        
        while(!q.empty())
        {
        	int q_size = q.size();
		while(q_size--)
		{
                	int node = q.front();
                	q.pop(); 
                	vis[node] = 1;
                	
                	for(int adjNode : this->adj[node])
                	{
                    	
                    		if(!vis[adjNode])
                    		{       vis[adjNode] = 1; 
		               	dist[adjNode] = dist[node] + 1;
		              	  	parent[adjNode] = node;
		               	q.push(adjNode);
		            	}
		            	
                	}
            
            	}
        }
  
}

void Maze::findShortestPath (int src, int dest)
{
	int V = lines * columns;
	vector<int> dist(V, 0); // Διάνυσμα αποθήκευσης της απόστασης κάθε κόμβου από το πετράδι. 
	vector<int> parent(V); // Διάνυσμα αποθήκευσης του κόμβου-πατέρα για κάθε κόμβο.
	
        for(int i=0; i<V; ++i)
        {
        	parent[i] = i;
        }
        
        BFS(src, dest, parent, dist);

        while(parent[dest] != dest)
        {
            path.push(dest);
            dest = parent[dest];
        }
        path.push(dest);  
}


int Maze::getMalfoyNextX()
{
	path.pop();
	int nextNode = path.top();
	int nextX = nextNode / columns;
	return nextX; 
}

int Maze::getMalfoyNextY()
{
	int nextNode = path.top();
	int nextY = nextNode % columns;
	return nextY;
}

void Maze::Replay()
{
	diamond.InitRemainingMoves();
	pottery->setSpawned(false);
	malfoy->setSpawned(false);
}

int Maze::getLines()
{
	return lines;
}

int Maze::getColumns()
{
	return columns;
}
