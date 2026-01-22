#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Cube.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mesh.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_World3D_GL.h"


Vec3D angle;
Vec3D cam;
World3D world;

/*
void World3D_Set_Menu(World3D* m,int mode){
	if(m->menu==0 && mode==1){
		AlxWindow_Mouse_SetInvisible(&window);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}
	if(m->menu==1 && mode==0){
		AlxWindow_Mouse_SetVisible(&window);
	}
	
	window.MouseBeforeX = GetWidth() / 2;
	window.MouseBeforeY = GetHeight() / 2;
	m->menu = mode;
}
*/

void Setup(AlxWindow* w){
    cam = Vec3D_New(0.0f,0.0f,-1.0f);
    
    world = World3D_New(w);
	//Mesh_Free(&world.trisIn);
	world.normal = WORLD3D_NORMAL_CAP;
	world.tex = WORLD3D_TEX_NONE;

    Lib3D_Cube(&world.trisIn,Vec3D_New(0.0f,0.0f,0.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
    Mesh_Shade(&world.trisIn,Vec3D_New(0.5f,0.6f,-0.7f));
}
void Update(AlxWindow* w){
    if(world.menu==1){
		if(GetMouse().x!=GetMouseBefore().x || GetMouse().y!=GetMouseBefore().y){
			Vec2 d = Vec2_Sub(GetMouse(),GetMouseBefore());
			Vec2 a = Vec2_Mulf(Vec2_Div(d,(Vec2){ window.Width,window.Height }),F32_PI2);
	
			angle.y += a.x;
			angle.x += a.y;
	
			SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
		}
	}

	if(Stroke(ALX_KEY_ESC).PRESSED)
		World3D_Set_Menu(&world,!world.menu);
	
	if(Stroke(ALX_KEY_Z).PRESSED)
		World3D_Set_Mode(&world,world.mode + 1);


    if(Stroke(ALX_KEY_R).DOWN) 		cam = Vec3D_Add(cam,Vec3D_New(0.0f, 5.0f * w->ElapsedTime,0.0f));
	else if(Stroke(ALX_KEY_F).DOWN) cam = Vec3D_Add(cam,Vec3D_New(0.0f,-5.0f * w->ElapsedTime,0.0f));
	
    const M4x4D rot = Matrix_MakeRotationY(angle.y);
	if(Stroke(ALX_KEY_W).DOWN) 	cam = Vec3D_Add(cam,Matrix_MultiplyVector(rot,Vec3D_New(0.0f,0.0f,5.0f * w->ElapsedTime)));
	if(Stroke(ALX_KEY_S).DOWN) 	cam = Vec3D_Add(cam,Matrix_MultiplyVector(rot,Vec3D_New(0.0f,0.0f,-5.0f * w->ElapsedTime)));
	if(Stroke(ALX_KEY_A).DOWN) 	cam = Vec3D_Add(cam,Matrix_MultiplyVector(rot,Vec3D_New(5.0f * w->ElapsedTime,0.0f,0.0f)));
	if(Stroke(ALX_KEY_D).DOWN)  cam = Vec3D_Add(cam,Matrix_MultiplyVector(rot,Vec3D_New(-5.0f * w->ElapsedTime,0.0f,0.0f)));

    World3D_Set_Model(&world,Matrix_MakeWorld((Vec3D){ 0.0f,0.0f,0.0f,1.0f },(Vec3D){ 0.0f,0.0f,0.0f,1.0f }));
	World3D_Set_View(&world,Matrix_MakePerspektive(cam,(Vec3D){ 0.0f,1.0f,0.0f,1.0f },angle));
	World3D_Set_Proj(&world,Matrix_MakeProjection(90,(float)GetHeight() / (float)GetWidth(),0.1f,1000.0f));

    World3D_Update(&world,cam,(Vec2){ GetWidth(),GetHeight() });

    Clear(BLACK);
    
    World3D_Render(WINDOW_STD_ARGS,&world);
}
void Delete(AlxWindow* w){
    World3D_Free(&world);
}

int main() {
    if(Create("3D Wrapper",1900,1000,1,1,Setup,Update,Delete)){
        Start();
    }
    return 0;
}
