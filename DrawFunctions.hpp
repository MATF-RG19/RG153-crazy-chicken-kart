#ifndef DRAWFUNC_HPP
#define DRAWFUNC_HPP

void draw_axes(float len);
void drawKart(void);
void setNormalAndVertex();
void drawFence(void);
void drawTrack(void);
void drawGrass(void);
void drawDirt(void);
void drawCompleteScene(void);
void drawChristmasTree(void);
void drawTree(void);
void drawMoon(void);
void drawFixedParts(void);
void drawHilltop(void);
void drawRedWhiteTrack(void);
void drawXtrap(void);
void drawXtrapOnTrack(int track);
void drawBomb(void);
void drawBombOnTrack(int track);
void drawBuggy(void);
void drawTiresForBuggy(void);
void drawRoof(void);
void drawBlock(int blockNumber);
void drawElectricPole(void);
void drawObstacles(void);
void drawObstacle(float x,int type,int track);
void drawHole(void);
void drawHoleOnTrack(int track);
#endif
