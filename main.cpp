#include "./headers/Game.h"
#include "./headers/TitleState.h"

using namespace std;

int main (int argc, char* argv[]) {

    // cout << "Hello World!!" << endl;
    // cin.get();
    
    Game::GetInstance().Push(new TitleState());
    Game::GetInstance().Run();


    //game.Run();

    return 0;
}