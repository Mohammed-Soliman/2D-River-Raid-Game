#include "Toolbar.h"
#include "GameConfig.h"
#include "game.h"

ToolbarIcon::ToolbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void ToolbarIcon::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

RestartIcon::RestartIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}

void RestartIcon::onClick()
{
	//TO DO: add code for restarting the game here
}

ExitIcon::ExitIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}

void ExitIcon::onClick()
{
	//TO DO: add code for cleanup and game exit here
}
RefreshIcon::RefreshIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void RefreshIcon::onClick()
{
	//TO DO: add code for refreshing the game here
}
SaveIcon::SaveIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void SaveIcon::onClick()
{
	//TO DO: add code for saving the game here
}
Load1Icon::Load1Icon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void Load1Icon::onClick()
{
	//TO DO: add code for loading the game here
}
ResumeIcon::ResumeIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void ResumeIcon::onClick()
{
	//TO DO: add code for resuming the game here
}
PauseIcon::PauseIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void PauseIcon::onClick()
{
	//TO DO: add code for pausing the game here
}


Toolbar::Toolbar(Game* r_pGame, point r_point, int r_width, int r_height) : Drawable(r_pGame, r_point, r_width, r_height)
{
	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_RESTART] = "images\\RESTART.jpg";
	iconsImages[ICON_EXIT] = "images\\EXIT.jpg";
	//iconsImages[ICON_Refresh] = "images\\REFRESH.jpg";
	//iconsImages[ICON_Save] = "images\\SAVE.jpg";->errors
	//iconsImages[ICON_Resume] = "images\\RESUME.jpg"; ->errors
	//iconsImages[ICON_Pause] = "images\\PAUSE.jpg";->errors

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new ToolbarIcon * [ICON_COUNT];

	//For each icon in the tool bar create an object 
	iconsList[ICON_RESTART] = new RestartIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_RESTART]);
	p.x += config.iconWidth;
	iconsList[ICON_EXIT] = new ExitIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_EXIT]);
	//p.x += config.iconWidth;
	//iconsList[ICON_Refresh] = new RefreshIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_Refresh]);
	//p.x += config.iconWidth;
	//iconsList[ICON_Save] = new SaveIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_Save]);
	//p.x += config.iconWidth;
	//iconsList[ICON_Resume] = new ResumeIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_Save]);
	//p.x += config.iconWidth;
	//iconsList[ICON_Pause] = new PauseIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_Pause]);
}
Toolbar::~Toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void Toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, config.toolBarHeight, pWind->GetWidth(), config.toolBarHeight);
}

bool Toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x co-ord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	if (clickedIconIndex == ICON_EXIT) return true;

	return false;

};