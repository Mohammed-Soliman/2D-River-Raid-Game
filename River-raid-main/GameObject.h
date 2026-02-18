#pragma once
#include "Drawable.h"

class Game; // Forward declaration

class GameObject : public Drawable
{
protected:
	color fillColor;	//game object fill color
	color borderColor;	//game object border color

public:
	GameObject(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc);
	GameObject();
	//virtual void draw() const = 0; //for a game object to draw itself on the screen	//for a game object to move itself on the screen
	virtual void draw() const = 0;	//Save the shape parameters to the file
	virtual void move() = 0;
	void setRefPoint(point p);
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;

	int getWidth() const;
	int getHeight() const;

	void setSize(int w, int h);

	color getFillColor() const;
	color getBorderColor() const;
	void setFillColor(color fc);
	void setBorderColor(color bc);

	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	

	//virtual void move() = 0;		//Move the game object
	//virtual void save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file
	//virtual void collisionAction() = 0;    //action that should be performed upon collision

};

