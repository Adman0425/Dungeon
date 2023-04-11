#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;

#include "Dungeon.h"

Dungeon game;

int main() {

	PlaySoundA(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);/*play the music and set the flags at the same time to ensure the music will play correctly*/
	getchar();/*get any character to play the music*/

	cout << "You should keep this in your mind that whoever fights monsters should see to it that in the process he does not become a monster.\n";
	cout << "Wish you can have some disclosure if you're strong enough to survive.\n";

	game.startGame();/*call dungeon and start the game*/

	cout << "You close eyes and it's just like a dream passing.\n";/*when the player win and exit the game*/
	return 0;
}
