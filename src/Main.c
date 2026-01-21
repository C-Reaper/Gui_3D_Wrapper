#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"

void Setup(AlxWindow* w){
    
}
void Update(AlxWindow* w){
    
    
    Clear(BLACK);
    

}
void Delete(AlxWindow* w){

}

int main() {
    if(Create("3D Wrapper",1000,1000,1,1,Setup,Update,Delete)){
        Start();
    }
    return 0;
}
