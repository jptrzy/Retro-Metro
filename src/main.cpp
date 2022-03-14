// Include standard headers
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
// #include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <math.h>

#define PI_1 M_PI/2
#define PI_2 PI_1*3
#define DR 0.0174533

typedef struct{
    bool w, a, s, d;
}ButtonKeys; ButtonKeys Keys;

float px,py,pdx,pdy,pa;
const int speed = 5;

int tile_size = 64;

int map_w=8;
int map_h=8;
int map_s=map_w*map_h;
int map[]={
    1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,1,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

float dist(float ax, float ay, float bx, float by){
    return sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay));
}

float roundRad(float r){
    return(r<0 ? r+M_PI*2 : ( r>M_PI*2 ? r-M_PI*2 : r ));
}


void updatePlayerDelta(){
    pdx=cos(pa)*speed;
    pdy=sin(pa)*speed;
}

void raycast(float radiant, float inp_x, float inp_y, float* out_dist, float* tx, float* ty){

    float y_offset, x_offset, hor_x, hor_y;

    if(radiant!=0 && radiant!=M_PI){
        float aTan=-1/tan(radiant);

        *ty = (((int)inp_y>>6)<<6)+((radiant > M_PI) ? -0.0001 : tile_size);
        *tx = (inp_y-*ty)*aTan+inp_x;
        float y_offset = ((radiant > M_PI) ? -tile_size : tile_size);
        float x_offset = -y_offset*aTan;   

        for(int d=0; d<8; d++){
            int mi = ((int) (*ty)>>6)*map_w+((int) (*tx)>>6);
            if(mi<map_s && mi>-1 && map[mi]==1){
                break;
            }else{
                *tx+=x_offset;
                *ty+=y_offset;
            }
        }
    }

    hor_x = *tx;
    hor_y = *ty;

    if(radiant!=PI_1 && radiant!=PI_2){

        float nTan=-tan(radiant);

        *tx = (((int)inp_x>>6)<<6)+( (radiant > PI_1 && radiant < PI_2) ? -0.0001 : tile_size);
        *ty = (inp_x-*tx)*nTan+inp_y;
        x_offset = ((radiant > PI_1 && radiant < PI_2) ? -tile_size : tile_size);
        y_offset = -x_offset*nTan;   

        for(int d=0; d<8; d++){
            int mi = ((int) (*ty)>>6)*map_w+((int) (*tx)>>6);
            if(mi<map_s && mi>-1 && map[mi]==1){
                break;
            }else{
                *tx+=x_offset;
                *ty+=y_offset;
            }
        }
    }

    float tDist = dist(inp_x, inp_y, hor_x, hor_y);
    *out_dist = dist(inp_x, inp_y, *tx, *ty);
    if(tDist < *out_dist){
        *tx = hor_x;
        *ty = hor_y;
        *out_dist = tDist;
    }
}

void drawRays3D(){

    // float rx,ry,ra,xo,yo;
    // int d=0, r, mx, my, mi, dl = 16;
    // float hDis, dis;

    // float hx, hy;

    float ra;
    int r;

    ra=roundRad(pa-32*DR);

    for(r=0; r<=128; r++){
        //-----
        // d=0;
        // float aTan=-1/tan(ra);

    //     // if(ra>M_PI){ty}
    //     if(ra > M_PI){
    //         ry = (((int)py>>6)<<6)-0.0001;
    //         rx = (py-ry)*aTan+px;
    //         yo = -tile_size;
    //         xo = -yo*aTan;
    //     }else if(ra < M_PI){
    //         ry = (((int)py>>6)<<6)+tile_size;
    //         rx = (py-ry)*aTan+px;
    //         yo = tile_size;
    //         xo = -yo*aTan;
    //     }else if(ra==0 || ra==M_PI){rx=px; ry=py; d=dl;}
        
    //     while(d++<dl){
    //         mx = (int) (rx)>>6;
    //         my = (int) (ry)>>6;
    //         mi = my*map_w+mx;
    //         if(mi<map_s && mi>-1 && map[mi]==1){
    //             d=dl;
    //         }else{
    //             rx+=xo;
    //             ry+=yo;
    //         }
    //     }

    //     hx=rx;
    //     hy=ry;

    //     //||
    //     d=0;
    //     float nTan=-tan(ra);

    //     // if(ra>M_PI){ty}
    //     if(ra > PI_1 && ra < PI_2){
    //         rx = (((int)px>>6)<<6)-0.0001;
    //         ry = (px-rx)*nTan+py;
    //         xo = -tile_size;
    //         yo = -xo*nTan;
    //     }else if(ra < PI_1 || ra > PI_2){
    //         rx = (((int)px>>6)<<6)+tile_size;
    //         ry = (px-rx)*nTan+py;
    //         xo = tile_size;
    //         yo = -xo*nTan;
    //     }else if(ra==PI_1 || ra==PI_2){rx=px; ry=py; d=dl;}
        
    //     while(d++<dl){
    //         mx = (int) (rx)>>6;
    //         my = (int) (ry)>>6;
    //         mi = my*map_w+mx;
    //         if(mi<map_s && mi>-1 && map[mi]==1){
    //             d=dl;
    //         }else{
    //             rx+=xo;
    //             ry+=yo;
    //         }
    //     }

    //     float col = 0;
    //     hDis = dist(px, py, hx, hy);
    //     dis = dist(px, py, rx, ry);
    //     if(hDis < dis){
    //         rx = hx;
    //         ry = hy;
    //         col = 1;
    //         dis = hDis;
    //     }

    //     // glColor3f(col,0,col);
    //     // glLineWidth(3);
    //     // glBegin(GL_LINES);
    //     // glVertex2i(px, py);
    //     // glVertex2i(rx, ry);
    //     // glEnd();


        float ray_x=0;
        float ray_y=0;
        float ray_dist=0;
        raycast(ra, px, py, &ray_dist, &ray_x, &ray_y);
        
        float col = 5000 / ray_dist / tile_size ;

        glColor3f(col,0,col);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(ray_x, ray_y);
        glEnd();

        //Draw Wall

        ray_dist = ray_dist * cos(pa - ra);

        int lineH = (int) 320*tile_size/ray_dist;
        int off = (512 - lineH) / 2;
        lineH += off;

        glColor3f(col,0,col);
        glBegin(GL_QUADS);
        glVertex2i(512+r*4, off);
        glVertex2i(512+r*4, lineH);
        glVertex2i(512+(r+1)*4, lineH);
        glVertex2i(512+(r+1)*4, off);
        glEnd();

        ra=roundRad(ra+DR/2);
    }
}

void drawMap(){
    int col;
    for(int y=0; y<map_h; y++){
        for(int x=0; x<map_w; x++){
            col = map[x+y*map_w];
            glColor3f(col,col,col);
            glBegin(GL_QUADS);
            glVertex2i(x*tile_size+1, y*tile_size+1);
            glVertex2i(x*tile_size+1, (y+1)*tile_size-1);
            glVertex2i((x+1)*tile_size-1, (y+1)*tile_size-1);
            glVertex2i((x+1)*tile_size-1, y*tile_size+1);
            glEnd();
        }
    }
}

void drawPlayer(){
    glColor3f(1,1,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();
}

float frame1, frame2, fps;

void display(){
    frame2=glutGet(GLUT_ELAPSED_TIME); fps = frame2-frame1; frame1 = glutGet(GLUT_ELAPSED_TIME);


    if(Keys.w){px+=pdx*0.05*fps; py+=pdy*0.05*fps;}
    if(Keys.s){px-=pdx*0.05*fps; py-=pdy*0.05*fps;}
    if(Keys.a){pa=roundRad(pa-0.005*fps); updatePlayerDelta();}
    if(Keys.d){pa=roundRad(pa+0.005*fps); updatePlayerDelta();}
    glutPostRedisplay();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawMap();
    drawRays3D();
    drawPlayer();

    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y){
    if(key == 'w'){Keys.w=1;}
    if(key == 's'){Keys.s=1;}
    if(key == 'a'){Keys.a=1;}
    if(key == 'd'){Keys.d=1;}

    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
    if(key == 'w'){Keys.w=0;}
    if(key == 's'){Keys.s=0;}
    if(key == 'a'){Keys.a=0;}
    if(key == 'd'){Keys.d=0;}

    glutPostRedisplay();
}

void init(){
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);

    px=356.082550;
    py=352.083557;
    // pa=0.853985;

    updatePlayerDelta();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //Create Window
    glutInitWindowSize(1024, 512);
    glutCreateWindow("HELP");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
}