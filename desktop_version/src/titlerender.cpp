#include "titlerender.h"

#include "Graphics.h"
#include "UtilityClass.h"
#include "Maths.h"
#include "Entity.h"
#include "Map.h"
#include "Script.h"
#include "FileSystemUtils.h"

#include "MakeAndPlay.h"

extern scriptclass script;

Stage stage;
Stage swfStage;
int temp;

int tr;
int tg;
int tb;

growing_vector<std::string> changelog = {
    // [line] is a huge line, have fun with that
    // The text should not be bigger than this line:
    // --------------------------------------
    "Version c1.0",
    "[line]",
    "- Added UTF-8 support",
    "- Removed having to use a load script",
    "  to use internal scripting",
    "- pdelay(n) - a delay(n) that doesn't",
    "  lock the players movement",
    "- setroomname() - sets the roomname to",
    "  the next line",
    "- settile(x,y,tile) - place a tile",
    "  temporarily in the room",
    "- textcolo(u)r(r,g,b,x,y,lines) - text()",
    "  but you can set the color directly",
    "- reloadroom() - reloads the current",
    "  room",
    "- toceil() - inverted tofloor()",
    "- movetoroom(x,y) - a relative",
    "  gotoroom()",
    "- playfile(file[, id]) - play a file as",
    "  either music or a sound effect. if you",
    "  specify an id, the file loops",
    "- stopfile(id) - stops playing a looping",
    "  audio file",
    "- ifnotflag() - an inverted version of",
    "  ifflag()",
    "- drawtext(x,y,r,g,b,center) - draw text",
    "  for one frame. The text you want to",
    "  display should be after the command.",
    "  center should be either 0 or 1.",
    "- drawrect(x,y,w,h,r,g,b) - draw a",
    "  rectangle for one frame.",
    "- followposition now works for the",
    "  player",
    "- There's now an option to disable only",
    "  the music",
    "- All limits have been removed except",
    "  for the 20x20 map size limit",
    "- destroy(platformsreal) - A version of",
    "  destroy(platforms) that isn't bugged",
    "- destroy(enemies)",
    "- destroy(trinkets)",
    "- destroy(warplines)",
    "- destroy(checkpoints)",
    "- destroy(all)",
    "- destroy(conveyors)",
    "- killplayer()",
    "- customquicksave()",
    "- niceplay() - use this for better area",
    "  music transitions",
    "- destroy(terminals)",
    "- destroy(scriptboxes)",
    "- destroy(disappearingplatforms)",
    "- destroy(1x1quicksand)",
    "- destroy(coins)",
    "- destroy(gravitytokens)",
    "- destroy(roomtext)",
    "- destroy(crewmates) - destroy non-",
    "  rescuable crewmates",
    "- destroy(customcrewmates) - destroy",
    "  rescuable crewmates",
    "- destroy(teleporter)",
    "- destroy(activityzones)",
    "- inf - like do(x), but an infinite",
    "  amount of times",
    "- Add seventh argument to createcrewman,",
    "  if it is flip spawn a flipped crewmate",
    "- fatal_left() - Makes the left side of",
    "  the screen deadly",
    "- fatal_right() - Makes the right side",
    "  of the screen deadly",
    "- fatal_top() - Makes the top of the",
    "  screen deadly",
    "- fatal_bottom() - Makes the bottom of",
    "  the screen deadly",
    "- ifrand(n,script) - Has a 1/n chance to",
    "  execute the script",
    "- gotocheckpoint() - Teleports the",
    "  player to their last checkpoint",
    "- Added 6th argument to createentity",
    "  that sets the raw color",
    "- Added 7th argument to createentity",
    "  that sets entity 1/56 type (Ved",
    "  numbers)",
    "- Automatically pause/unpause all audio",
    "  on focus change",
    "- Instead of defaulting to gray, assume",
    "  unknown colors in createcrewman/",
    "  changecolour are internal ones",
    "- Added an argument to createcrewman to",
    "  set a name (instead of pink/blue/etc),",
    "  useful in combination with the above",
    "  or when having multiple crewmen of the",
    "  same color",
    "- Added color aliases for all colour",
    "  functions",
    "- Added optional parameter to play() to",
    "  set the fade-in time in milliseconds",
    "  (default 3000)",
    "- markmap(x,y,tile) to put a tile on any",
    "  minimap coordinate",
    "- unmarkmap(x,y) to undo the above",
    "- mapimage(path/name.png) to use any map",
    "  image",
    "- automapimage to undo",
    "- enablefog/disablefog to enable/disable",
    "  hiding unexplored rooms (called fog in",
    "  the code)",
    "- All names (including player) now work",
    "  with all functions",
    "- Added hourglasses as enemy type 10",
    "- Fixed enemies in Warp Zone gray not",
    "  being gray",
    "- createroomtext(x,y) - x,y in tiles,",
    "  roomtext on next line",
    "- createscriptbox(x,y,w,h,script) -",
    "  x,y,w,h in pixels",
    "- Allowed placed terminals to use any",
    "  sprite they want",
    "- You can now place flipped terminals",
    "- Add showmarkers/hidemarkers to",
    "  temporarily disable markmap markers",
    "- setspeed(x) - set player speed, 3",
    "  by default",
    "- setvelocity(x) - push the player",
    "  (affected by inertia)",
    "- pinf - variant of inf to automatically",
    "  pdelay(1) if no delay occurred",
    "- nobars() - to disable automatic",
    "  cutscene bars from a script",
    "- finalstretchon - turn on Final Level",
    "  palette swap",
    "- finalstretchoff - turn off Final Level",
    "  palette swap",
    "- reloadscriptboxes() - reload script",
    "  boxes without affecting entities",
    "- puntilbars() - untilbars() with pdelay",
    "- puntilfade() - untilfade() with pdelay",
    "- You can now use the Warp Zone gray",
    "  tileset in the editor",
    "- disableflip - disables flipping",
    "- enableflip - enables flipping",
    "- enableinfiniflip - enables flipping in",
    "  mid-air",
    "- disableinfiniflip - disables flipping",
    "  in mid-air",
    "- untilmusic() - wait until the current",
    "  track has finished fading in or out",
    "- puntilmusic() - untilmusic with pdelay",
    "- Edentity conveyors no longer have tile",
    "  1s underneath them",
    "- Added a label and goto system - write",
    "  down $label$ on a line, then to go to",
    "  it, use $label$ as a script name if",
    "  you're in the same script, or write",
    "  scriptname$label$ to jump to the label",
    "  from another script",
    "- ifvce() - detect if game is VVVVVV-CE",
    "  or not",
    "- disablesuicide - Disable pressing R",
    "- enablesuicide - Enable pressing R",
    "- customactivityzone(x,y,w,h,color,",
    "  script) - x,y,w,h in pixels, color is",
    "  red/orange/yellow/green/cyan/blue/pink",
    "  /purple (actually pink)/white/gray, if",
    "  invalid it defaults to gray, prompt",
    "  goes on the next line",
    "- customactivityzonergb(x,y,w,h,r,g,b,",
    "  script) - x,y,w,h in pixels, prompt",
    "  goes on the next line",
    "- Fixed the 2-frame delay to execute a",
    "  script when entering a room",
    "- position(centerx,<line>) - ",
    "  Horizontally center the text box",
    "  around the line x=<line>",
    "- position(centery,<line>) - Vertically",
    "  center the text box around the line y=",
    "  line",
    "- Added the Tower tileset",
    "- Added altstates - F6 to create, F7 to",
    "  delete, press A to switch between",

};

std::string tempstring;

void updategraphicsmode(Game& game, Graphics& dwgfx)
{
    swfStage = stage;
}

void titlerender(Graphics& dwgfx, mapclass& map, Game& game, entityclass& obj, UtilityClass& help, musicclass& music)
{

    FillRect(dwgfx.backBuffer, 0,0,dwgfx.backBuffer->w, dwgfx.backBuffer->h, 0x00000000 );

    if (!game.menustart)
    {
        tr = (int)(164 - (help.glow / 2) - int(fRandom() * 4));
        tg = 164 - (help.glow / 2) - int(fRandom() * 4);
        tb = 164 - (help.glow / 2) - int(fRandom() * 4);

        dwgfx.drawsprite((160 - 96) + 0 * 32, 50, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 1 * 32, 50, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 2 * 32, 50, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 3 * 32, 50, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 4 * 32, 50, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 5 * 32, 50, 23, tr, tg, tb);
        dwgfx.Print(-1,95,"COMMUNITY EDITION",tr, tg, tb, true);

        dwgfx.Print(5, 175, "[ ACTION をおしてスタート ]", tr, tg, tb, true);
        dwgfx.Print(5, 195, "ACTION = SPACE, Z, V", int(tr*0.5f), int(tg*0.5f), int(tb*0.5f), true);

    }
    else
    {
        if(!game.colourblindmode) dwgfx.drawtowerbackgroundsolo(map);

        tr = map.r - (help.glow / 4) - int(fRandom() * 4);
        tg = map.g - (help.glow / 4) - int(fRandom() * 4);
        tb = map.b - (help.glow / 4) - int(fRandom() * 4);

        tr = std::clamp(tr, 0, 255);
        tg = std::clamp(tg, 0, 255);
        tb = std::clamp(tb, 0, 255);

        if(game.currentmenuname=="mainmenu")
        {
            dwgfx.drawsprite((160 - 96) + 0 * 32, 50, 23, tr, tg, tb);
            dwgfx.drawsprite((160 - 96) + 1 * 32, 50, 23, tr, tg, tb);
            dwgfx.drawsprite((160 - 96) + 2 * 32, 50, 23, tr, tg, tb);
            dwgfx.drawsprite((160 - 96) + 3 * 32, 50, 23, tr, tg, tb);
            dwgfx.drawsprite((160 - 96) + 4 * 32, 50, 23, tr, tg, tb);
            dwgfx.drawsprite((160 - 96) + 5 * 32, 50, 23, tr, tg, tb);
            dwgfx.Print(-1,95,"COMMUNITY EDITION",tr, tg, tb, true);
            dwgfx.Print( 310 - (4*8), 230, "c1.0", tr/2, tg/2, tb/2);
			if (music.mmmmmm) {
			    dwgfx.Print( 10, 230, "[MMMMMM Mod 導入済み]", tr/2, tg/2, tb/2);
		    } else {
                dwgfx.Print( 10, 230, "git.io/v6ce-jp", tr/2, tg/2, tb/2);
            }
        }
        else if (game.currentmenuname == "changelog")
        {
            dwgfx.bigprint( -1, 20, "こうしんりれき:", tr, tg, tb, true, 2);


            // Let's clamp the offset--we can't really
            // use std::clamp because it's unsigned
            if (game.changelogoffset + 13 >= changelog.size()) {
                game.changelogoffset = changelog.size() - 14;
            }

            // We can just make more variables instead of ifs
            int temp_tr = tr;
            int temp_tg = tg;
            int temp_tb = tb;

            for(growing_vector<std::string>::size_type i = 0 + game.changelogoffset; i != (14 + game.changelogoffset) && i < changelog.size(); i++) {
                // Huge if, I swear this made sense when I wrote it
                // If there's more lines above the top line displayed, or if
                // there's more lines below the bottom lined displayed, make
                // the color darker.
                if ((i == 0 + game.changelogoffset && (game.changelogoffset != 0)) || (i == 13 + game.changelogoffset && game.changelogoffset != changelog.size() - 14)) {
                    temp_tr = tr / 2;
                    temp_tg = tg / 2;
                    temp_tb = tb / 2;
                } else {
                    temp_tr = tr;
                    temp_tg = tg;
                    temp_tb = tb;
                }
                if (changelog[i] == "[line]") {
                    // If the string is literally "[line]", just replace it
                    dwgfx.Print(0, 48 + ((i - game.changelogoffset) * 10), "________________________________________", temp_tr, temp_tg, temp_tb);
                } else {
                    dwgfx.Print(0, 50 + ((i - game.changelogoffset) * 10), changelog[i], temp_tr, temp_tg, temp_tb);
                }
            }
        }
        else if (game.currentmenuname == "levellist")
        {
          if(ed.ListOfMetaData.size()==0){
          dwgfx.Print( -1, 100, "エラー: レベルがみつかりません。", tr, tg, tb, true);
          }
          int tmp=game.currentmenuoption+(game.levelpage*8);
          if(tmp>=0 && tmp < (int) ed.ListOfMetaData.size()){ // FIXME: size_t/int! -flibit
            //Don't show next page or return to menu options here!
            if(game.nummenuoptions - game.currentmenuoption<=2){

            }else{
              dwgfx.bigprint( -1, 15, ed.ListOfMetaData[tmp].title, tr, tg, tb, true);
              dwgfx.Print( -1, 40, ed.ListOfMetaData[tmp].creator + " さく", tr, tg, tb, true);
              dwgfx.Print( -1, 50, ed.ListOfMetaData[tmp].website, tr, tg, tb, true);
              dwgfx.Print( -1, 70, ed.ListOfMetaData[tmp].Desc1, tr, tg, tb, true);
              dwgfx.Print( -1, 80, ed.ListOfMetaData[tmp].Desc2, tr, tg, tb, true);
              dwgfx.Print( -1, 90, ed.ListOfMetaData[tmp].Desc3, tr, tg, tb, true);
            }
          }
        }
        else if (game.currentmenuname == "errornostart")
        {
          dwgfx.Print( -1, 65, "エラー: このレベルには", tr, tg, tb, true);
          dwgfx.Print( -1, 75, "スタートちてんがありません!", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "options")
        {
				
						#if defined(MAKEANDPLAY)
							if (game.currentmenuoption == 0)
							{
									dwgfx.bigprint( -1, 30, "アクセシビリティ", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "スクリーンエフェクトのきりかえや", tr, tg, tb, true);
									dwgfx.Print( -1, 75, "ていそくモード、むてきモードのきりかえ", tr, tg, tb, true);
							}
							else if (game.currentmenuoption == 1)
							{
								dwgfx.bigprint( -1, 30, "ゲームパッドのせってい", tr, tg, tb, true);
								dwgfx.Print( -1, 65, "コントローラーのわりあてのせっていや", tr, tg, tb, true);
								dwgfx.Print( -1, 75, "かんどのちょうせつ", tr, tg, tb, true);
							}
							else if (game.currentmenuoption == 2)
							{
									dwgfx.bigprint( -1, 30, "データをけす", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "セーブデータと、かいほうした", tr, tg, tb, true);
									dwgfx.Print( -1, 75, "すべてのプレイモードをけす", tr, tg, tb, true);
							}else if (game.currentmenuoption == 3){
								if(music.mmmmmm){
									dwgfx.bigprint( -1, 30, "サウンドトラック", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "MMMMMM と PPPPPP のおんがくのきりかえ", tr, tg, tb, true);
									if(music.usingmmmmmm){
										dwgfx.Print( -1, 85, "げんざいのサウンドトラック: MMMMMM", tr, tg, tb, true);
									}else{
										dwgfx.Print( -1, 85, "げんざいのサウンドトラック: PPPPPP", tr, tg, tb, true);
									}
								}
							}
						#elif !defined(MAKEANDPLAY)
							if (game.currentmenuoption == 0)
							{
									dwgfx.bigprint( -1, 30, "Accessibility", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "Disable screen effects, enable", tr, tg, tb, true);
									dwgfx.Print( -1, 75, "slowdown modes or invincibility", tr, tg, tb, true);
							}
							else if (game.currentmenuoption == 1)
							{
									dwgfx.bigprint( -1, 30, "Unlock Play Modes", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "Unlock parts of the game normally", tr, tg, tb, true);
									dwgfx.Print( -1, 75, "unlocked as you progress", tr, tg, tb, true);
							}
							else if (game.currentmenuoption == 2)
							{
								dwgfx.bigprint( -1, 30, "Game Pad Options", tr, tg, tb, true);
								dwgfx.Print( -1, 65, "Rebind your controllers buttons", tr, tg, tb, true);
								dwgfx.Print( -1, 75, "and adjust sensitivity", tr, tg, tb, true);
							}
							else if (game.currentmenuoption == 3)
							{
									dwgfx.bigprint( -1, 30, "Clear Data", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "Delete your save data", tr, tg, tb, true);
									dwgfx.Print( -1, 75, "and unlocked play modes", tr, tg, tb, true);
							}else if (game.currentmenuoption == 4)
							{
							if(music.mmmmmm){
									dwgfx.bigprint( -1, 30, "Soundtrack", tr, tg, tb, true);
									dwgfx.Print( -1, 65, "Toggle between MMMMMM and PPPPPP", tr, tg, tb, true);
									if(music.usingmmmmmm){
										dwgfx.Print( -1, 85, "Current soundtrack: MMMMMM", tr, tg, tb, true);
									}else{
										dwgfx.Print( -1, 85, "Current soundtrack: PPPPPP", tr, tg, tb, true);
									}
							}
							}
						#endif
        }
        else if (game.currentmenuname == "graphicoptions")
        {
          if (game.currentmenuoption == 0)
          {
              dwgfx.bigprint( -1, 30, "フルスクリーンのきりかえ", tr, tg, tb, true);
              dwgfx.Print( -1, 65, "フルスクリーン・ウィンドウモードをえらぶ", tr, tg, tb, true);

              if(game.fullscreen){
                dwgfx.Print( -1, 85, "げんざいのモード: フルスクリーン", tr, tg, tb, true);
              }else{
                dwgfx.Print( -1, 85, "げんざいのモード: ウィンドウ", tr, tg, tb, true);
              }

          }else if (game.currentmenuoption == 1)
                {
                    dwgfx.bigprint( -1, 30, "がめんのひきのばし", tr, tg, tb, true);
                    dwgfx.Print( -1, 65, "レターボックス・ひきのばし・せいすうからえらぶ", tr, tg, tb, true);

              if(game.stretchMode == 2){
                dwgfx.Print( -1, 85, "げんんざいのモード: せいすう", tr, tg, tb, true);
              }else if (game.stretchMode == 1){
                dwgfx.Print( -1, 85, "げんざいのモード: ひきのばし", tr, tg, tb, true);
              }else{
                dwgfx.Print( -1, 85, "げんざいのモード: レターボックス", tr, tg, tb, true);
              }
          }else if (game.currentmenuoption == 2)
                {
                    dwgfx.bigprint( -1, 30, "フィルターのきりかえ", tr, tg, tb, true);
                    dwgfx.Print( -1, 65, "ニアレスト・バイリニアにへんこう", tr, tg, tb, true);

              if(game.useLinearFilter){
                dwgfx.Print( -1, 85, "げんざいのモード: バイリニア", tr, tg, tb, true);
              }else{
                dwgfx.Print( -1, 85, "げんざいのモード: ニアレスト", tr, tg, tb, true);
              }

                } else if (game.currentmenuoption == 3)
                {
                    dwgfx.bigprint( -1, 30, "アナログモード", tr, tg, tb, true);
                    dwgfx.Print( -1, 65, "あなたのテレビがめんはせいじょう", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "です。がめんのちょうせつを", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "しようとしないでください。", tr, tg, tb, true);
                }
        }
        else if (game.currentmenuname == "credits")
        {
            dwgfx.Print( -1, 50, "VVVVVV せいさくしゃ", tr, tg, tb, true);
            dwgfx.bigprint( 40, 65, "Terry Cavanagh", tr, tg, tb, true, 2);

            dwgfx.drawimagecol(7, -1, 86, tr *0.75, tg *0.75, tb *0.75, true);
            //dwgfx.Print( 40, 85, "http://www.distractionware.com", tr, tg, tb, true);

            dwgfx.Print( -1, 120, "おんがくたんとう", tr, tg, tb, true);
            dwgfx.bigprint( 40, 135, "Magnus P~lsson", tr, tg, tb, true, 2);
            dwgfx.drawimagecol(8, -1, 156, tr *0.75, tg *0.75, tb *0.75, true);
            //dwgfx.Print( 40, 155, "http://souleye.madtracker.net", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "credits_ce")
        {
            auto base = 57; // x = 240 - 126 - x
            dwgfx.Print( -1, base, "VVVVVV: Community Edition は", tr, tg, tb, true);
            dwgfx.Print( -1, base + 15, "このかたたちによってつくられています:", tr, tg, tb, true);
            dwgfx.bigprint( -1, base + 30, "Info Teddy", tr, tg, tb, true, 2);
            dwgfx.bigprint( -1, base + 50, "AllyTally",  tr, tg, tb, true, 2);
            dwgfx.bigprint( -1, base + 70, "leo60228",  tr, tg, tb, true, 2);
            dwgfx.bigprint( -1, base + 90, "FIQ",  tr, tg, tb, true, 2);
            dwgfx.bigprint( -1, base + 110, "Stelpjo",  tr, tg, tb, true, 2);
        }
        else if (game.currentmenuname == "credits2")
        {
            dwgfx.Print( -1, 50, "へやのなまえ", tr, tg, tb, true);
            dwgfx.bigprint( 40, 65, "Bennett Foddy", tr, tg, tb, true);
            dwgfx.drawimagecol(9, -1, 86, tr*0.75, tg *0.75, tb *0.75, true);
            //dwgfx.Print( 40, 80, "http://www.distractionware.com", tr, tg, tb);
            dwgfx.Print( -1, 110, "C++バージョンせいさく", tr, tg, tb, true);
            dwgfx.bigprint( 40, 125, "Simon Roth", tr, tg, tb, true);
						dwgfx.bigprint( 40, 145, "Ethan Lee", tr, tg, tb, true);
           //dwgfx.drawimagecol(11, -1, 156, tr*0.75, tg *0.75, tb *0.75, true);
        }
        else if (game.currentmenuname == "credits25")
        {
            dwgfx.Print( -1, 40, "ベータテスター", tr, tg, tb, true);
            dwgfx.bigprint( 40, 55, "Sam Kaplan", tr, tg, tb, true);
            dwgfx.bigprint( 40, 75, "Pauli Kohberger", tr, tg, tb, true);
            dwgfx.Print( -1, 130, "Ending Picture by", tr, tg, tb, true);
            dwgfx.bigprint( 40, 145, "Pauli Kohberger", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "credits3")
        {
            dwgfx.Print( -1, 20, "VVVVVV はこのかたたちに", tr, tg, tb, true);
            dwgfx.Print( 40, 30, "よってしえんされています", tr, tg, tb, true);

            dwgfx.Print( 80-16, 40+20, "Anders Ekermo", tr, tg, tb);
            dwgfx.Print( 80-12, 54+20, "Andreas K|mper", tr, tg, tb);
            dwgfx.Print( 80-8, 68+20, "Anthony Burch", tr, tg, tb);
            dwgfx.Print( 80-4, 82+20, "Bennett Foddy", tr, tg, tb);
            dwgfx.Print( 80, 96+20, "Brendan O'Sullivan", tr, tg, tb);
            dwgfx.Print( 80+4, 110+20, "Christopher Armstrong", tr, tg, tb);
            dwgfx.Print( 80+8, 124+20, "Daniel Benmergui", tr, tg, tb);
            dwgfx.Print( 80+12, 138+20, "David Pittman", tr, tg, tb);
            dwgfx.Print( 80+16, 152+20, "Ian Bogost", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits4")
        {
            dwgfx.Print( -1, 20, "VVVVVV はこのかたたちに", tr, tg, tb, true);
            dwgfx.Print( 40, 30, "よってしえんされています", tr, tg, tb, true);
            dwgfx.Print( 80-16, 20+40, "Ian Poma", tr, tg, tb);
            dwgfx.Print( 80-12, 34+40, "Jaz McDougall", tr, tg, tb);
            dwgfx.Print( 80-8, 48+40, "John Faulkenbury", tr, tg, tb);
            dwgfx.Print( 80-4, 62+40, "Jonathan Whiting", tr, tg, tb);
            dwgfx.Print( 80, 76+40, "Kyle Pulver", tr, tg, tb);
            dwgfx.Print( 80+4, 90+40, "Markus Persson", tr, tg, tb);
            dwgfx.Print( 80+8, 104+40, "Nathan Ostgard", tr, tg, tb);
            dwgfx.Print( 80+12, 118+40, "Nick Easler", tr, tg, tb);
            dwgfx.Print( 80+16, 132+40, "Stephen Lavelle", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits5")
        {
            dwgfx.Print( -1, 20, "そのほか", tr, tg, tb, true);

            dwgfx.Print( 80, 40,"Adam Wendt", tr, tg, tb);
            dwgfx.Print( 80, 50,"Andreas J{rgensen", tr, tg, tb);
            dwgfx.Print( 80, 60,"}ngel Louzao Penalva", tr, tg, tb);
            dwgfx.Print( 80, 70,"Ashley Burton", tr, tg, tb);
            dwgfx.Print( 80, 80,"Aubrey Hesselgren", tr, tg, tb);
            dwgfx.Print( 80, 90,"Bradley Rose", tr, tg, tb);
            dwgfx.Print( 80, 100,"Brendan Urquhart", tr, tg, tb);
            dwgfx.Print( 80, 110,"Chris Ayotte", tr, tg, tb);
            dwgfx.Print( 80, 120,"Christopher Zamanillo", tr, tg, tb);
            dwgfx.Print( 80, 130,"Daniel Schuller", tr, tg, tb);
            dwgfx.Print( 80, 140,"Hybrid Mind Studios", tr, tg, tb);
            dwgfx.Print( 80, 150,"Emilie McGinley", tr, tg, tb);
            dwgfx.Print( 80, 160,"Francisco Solares", tr, tg, tb);
            dwgfx.Print( 80, 170,"Hal Helms", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits6")
        {
            dwgfx.Print( -1, 20, "そのほか", tr, tg, tb, true);

            dwgfx.Print( 80, 40,"Hayden Scott-Baron", tr, tg, tb);
            dwgfx.Print( 80, 50,"Hermit Games", tr, tg, tb);
            dwgfx.Print( 80, 60,"Ido Yehieli", tr, tg, tb);
            dwgfx.Print( 80, 70,"Jade Vault Games", tr, tg, tb);
            dwgfx.Print( 80, 80,"James Andrews", tr, tg, tb);
            dwgfx.Print( 80, 90,"James Riley", tr, tg, tb);
            dwgfx.Print( 80, 100,"James Hsieh", tr, tg, tb);
            dwgfx.Print( 80, 110,"Jasper Byrne", tr, tg, tb);
            dwgfx.Print( 80, 120,"Jedediah Baker", tr, tg, tb);
            dwgfx.Print( 80, 130,"Jens Bergensten", tr, tg, tb);
            dwgfx.Print( 80, 140,"Jeremy J. Penner", tr, tg, tb);
            dwgfx.Print( 80, 150,"Jeremy Peterson", tr, tg, tb);
            dwgfx.Print( 80, 160,"Jim McGinley", tr, tg, tb);
            dwgfx.Print( 80, 170,"Jonathan Cartwright", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits7")
        {
            dwgfx.Print( -1, 20, "そのほか", tr, tg, tb, true);

            dwgfx.Print( 80, 40,"John Nesky", tr, tg, tb);
            dwgfx.Print( 80, 50,"Jos Yule", tr, tg, tb);
            dwgfx.Print( 80, 60,"Jose Flores", tr, tg, tb);
            dwgfx.Print( 80, 70,"Josh Bizeau", tr, tg, tb);
            dwgfx.Print( 80, 80,"Joshua Buergel", tr, tg, tb);
            dwgfx.Print( 80, 90,"Joshua Hochner", tr, tg, tb);
            dwgfx.Print( 80, 100,"Kurt Ostfeld", tr, tg, tb);
            dwgfx.Print( 80, 110,"Magnus P~lsson", tr, tg, tb);
            dwgfx.Print( 80, 120,"Mark Neschadimenko", tr, tg, tb);
            dwgfx.Print( 80, 130,"Matt Antonellis", tr, tg, tb);
            dwgfx.Print( 80, 140,"Matthew Reppert", tr, tg, tb);
            dwgfx.Print( 80, 150,"Michael Falkensteiner", tr, tg, tb);
            dwgfx.Print( 80, 160,"Michael Vendittelli", tr, tg, tb);
            dwgfx.Print( 80, 170,"Mike Kasprzak", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits8")
        {
            dwgfx.Print( -1, 20, "そのほか", tr, tg, tb, true);

            dwgfx.Print( 80, 70,"Mitchel Stein", tr, tg, tb);
            dwgfx.Print( 80, 80,"Sean Murray", tr, tg, tb);
            dwgfx.Print( 80, 90,"Simon Michael", tr, tg, tb);
            dwgfx.Print( 80, 100,"Simon Schmid", tr, tg, tb);
            dwgfx.Print( 80, 110,"Stephen Maxwell", tr, tg, tb);
            dwgfx.Print( 80, 120,"Swing Swing Submarine", tr, tg, tb);
            dwgfx.Print( 80, 130,"Tam Toucan", tr, tg, tb);
            dwgfx.Print( 80, 140,"Terry Dooher", tr, tg, tb);
            dwgfx.Print( 80, 150,"Tim W.", tr, tg, tb);
            dwgfx.Print( 80, 160,"Timothy Bragan", tr, tg, tb);
        }
        else if (game.currentmenuname == "credits9")
        {
            dwgfx.Print( -1, 20, "and thanks also to:", tr, tg, tb, true);

            dwgfx.bigprint(80, 60, "You!", tr, tg, tb, true);

            dwgfx.Print( 80, 100, "Your support makes it possible", tr, tg, tb,true);
            dwgfx.Print( 80, 110,"for me to continue making the", tr, tg, tb,true);
            dwgfx.Print( 80, 120,"games I want to make, now", tr, tg, tb,true);
            dwgfx.Print( 80, 130, "and into the future.", tr, tg, tb, true);

            dwgfx.Print( 80, 150,"Thank you!", tr, tg, tb,true);
        }
        else if (game.currentmenuname == "setinvincibility")
        {
            dwgfx.Print( -1, 100, "むてきモードを", tr, tg, tb, true);
            dwgfx.Print( -1, 110, "アリにしますか?", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "setslowdown1")
        {
            dwgfx.Print( -1, 90, "ちゅうい! ゲームのそくどをかえるには", tr, tg, tb, true);
            dwgfx.Print( -1, 100, "さいきどうがひつようです。 また、", tr, tg, tb, true);
            dwgfx.Print( -1, 110, "げんざいのセーブデータはきえます。", tr, tg, tb, true);
            dwgfx.Print( -1, 120, "よろしいですか?", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "setslowdown2")
        {
            dwgfx.bigprint( -1, 40, "ゲームのそくど", tr, tg, tb, true);
            dwgfx.Print( -1, 75, "ゲームのそくどをえらんでください。", tr, tg, tb, true);
            if (game.gameframerate == 34)
            {
                dwgfx.Print(-1, 105, "ゲームのそくどは ふつう です。", tr / 2, tg / 2, tb / 2, true);
            }
            else if (game.gameframerate==41)
            {
                dwgfx.Print( -1, 105, "ゲームのそくどは 80% です。", tr, tg, tb, true);
            }
            else if (game.gameframerate==55)
            {
                dwgfx.Print( -1, 105, "ゲームのそくどは 60% です。", tr, tg, tb, true);
            }
            else if (game.gameframerate==83)
            {
                dwgfx.Print( -1, 105, "ゲームのそくどは 40% です。", tr, tg, tb, true);
            }
        }
        else if (game.currentmenuname == "newgamewarning")
        {
            dwgfx.Print( -1, 100, "Are you sure? This will", tr, tg, tb, true);
            dwgfx.Print( -1, 110, "delete your current saves...", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "cleardatamenu")
        {
            dwgfx.Print( -1, 100, "げんざいのセーブデータを", tr, tg, tb, true);
            dwgfx.Print( -1, 110, "すべてけしてもよろしいですか?", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "startnodeathmode")
        {
            dwgfx.Print( -1, 45, "Good luck!", tr, tg, tb, true);
            dwgfx.Print( -1, 80, "You cannot save in this mode.", tr, tg, tb, true);
            dwgfx.Print( -1, 100, "Would you like to disable the", tr, tg, tb, true);
            dwgfx.Print( -1, 112, "cutscenes during the game?", tr, tg, tb, true);
        }
		else if (game.currentmenuname == "controller")
		{
			dwgfx.bigprint( -1, 30, "ゲームパッド", tr, tg, tb, true);
			dwgfx.Print( -1, 55, "コントローラーのせっていをへんこうできます。", tr, tg, tb, true);
			if (game.currentmenuoption == 0)
			{
				switch(game.controllerSensitivity)
				{
				case 0:
					dwgfx.Print( -1, 85, " ひくい     ふつう     たかい", tr, tg, tb, true);
					dwgfx.Print( -1, 95, "[]..................", tr, tg, tb, true);
					break;
				case 1:
					dwgfx.Print( -1, 85, " ひくい     ふつう     たかい", tr, tg, tb, true);
					dwgfx.Print( -1, 95, ".....[].............", tr, tg, tb, true);
					break;
				case 2:
					dwgfx.Print( -1, 85, " ひくい     ふつう     たかい", tr, tg, tb, true);
					dwgfx.Print( -1, 95, ".........[].........", tr, tg, tb, true);
					break;
				case 3:
					dwgfx.Print( -1, 85, " ひくい     ふつう     たかい", tr, tg, tb, true);
					dwgfx.Print( -1, 95, ".............[].....", tr, tg, tb, true);
					break;
				case 4:
					dwgfx.Print( -1, 85, " ひくい     ふつう     たかい", tr, tg, tb, true);
					dwgfx.Print( -1, 95, "..................[]", tr, tg, tb, true);
					break;
				}
			}
			if (    game.currentmenuoption == 1 ||
                                game.currentmenuoption == 2 ||
                                game.currentmenuoption == 3     )
			{
				dwgfx.Print( -1, 85, "はんてんのボタン: " + std::string(UtilityClass::GCString(game.controllerButton_flip)) , tr, tg, tb, true);
				dwgfx.Print( -1, 95, "ENTERのボタン: "  + std::string(UtilityClass::GCString(game.controllerButton_map)), tr, tg, tb, true);
				dwgfx.Print( -1, 105, "メニューのボタン: " + std::string(UtilityClass::GCString(game.controllerButton_esc)) , tr, tg, tb, true);
			}


		}
        else if (game.currentmenuname == "accessibility")
        {
            if (game.currentmenuoption == 0)
            {
                dwgfx.bigprint( -1, 40, "はいけい", tr, tg, tb, true);
                if (!game.colourblindmode)
                {
                    dwgfx.Print( -1, 75, "はいけい: アリ", tr, tg, tb, true);
                }
                else
                {
                    dwgfx.Print( -1, 75, "はいけい: ナシ", tr/2, tg/2, tb/2, true);
                }
            }
            else if (game.currentmenuoption == 1)
            {
                dwgfx.bigprint( -1, 40, "スクリーンエフェクト", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "がめんのゆれとてんめつをきりかえる", tr, tg, tb, true);
                if (!game.noflashingmode)
                {
                    dwgfx.Print( -1, 85, "スクリーンエフェクト: アリ", tr, tg, tb, true);
                }
                else
                {
                    dwgfx.Print( -1, 85, "スクリーンエフェクト: ナシ", tr/2, tg/2, tb/2, true);
                }
            }
            else if (game.currentmenuoption == 2)
            {
                dwgfx.bigprint( -1, 40, "もじのふちどり", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "ゲームないのもじのふちどりをきりかえる", tr, tg, tb, true);
                // FIXME: Maybe do an outlined print instead? -flibit
                if (!dwgfx.notextoutline)
                {
                    dwgfx.Print( -1, 85, "もじのふちどり: アリ", tr, tg, tb, true);
                }
                else
                {
                    dwgfx.Print( -1, 85, "もじのふちどり: ナシ", tr/2, tg/2, tb/2, true);
                }
            }
            else if (game.currentmenuoption == 3)
            {
                dwgfx.bigprint( -1, 40, "むてきモード", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "ゲームしょしんしゃのてだすけようです。", tr, tg, tb, true);
                dwgfx.Print( -1, 85, "バグをひきおこすかのうせいがります。", tr, tg, tb, true);
                if (map.invincibility)
                {
                    dwgfx.Print( -1, 105, "むてきモード: アリ", tr, tg, tb, true);
                }
                else
                {
                    dwgfx.Print( -1, 105, "むてきモード: ナシ", tr/2, tg/2, tb/2, true);
                }
            }
            else if (game.currentmenuoption == 4)
            {
                dwgfx.bigprint( -1, 40, "ゲームのそくど", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "そうさのやりにくいきしゅをしよう", tr, tg, tb, true);
                dwgfx.Print( -1, 85, "しているばあいにやくにたちます。", tr, tg, tb, true);
                if (game.gameframerate==34)
                {
                    dwgfx.Print( -1, 105, "ゲームのそくどは ふつう です。", tr/2, tg/2, tb/2, true);
                }
                else if (game.gameframerate==41)
                {
                    dwgfx.Print( -1, 105, "ゲームのそくどは 80% です。", tr, tg, tb, true);
                }
                else if (game.gameframerate==55)
                {
                    dwgfx.Print( -1, 105, "ゲームのそくどは 60% です。", tr, tg, tb, true);
                }
                else if (game.gameframerate==83)
                {
                    dwgfx.Print( -1, 105, "ゲームのそくどは 40% です。", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 5)
            {
                dwgfx.bigprint( -1, 40, "おんがく", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "おんがくをきりかえます。", tr, tg, tb, true);
                if (!music.muted)
                {
                    dwgfx.Print( -1, 85, "おんがく: アリ", tr, tg, tb, true);
                }
                else
                {
                    dwgfx.Print( -1, 85, "おんがく: ナシ", tr/2, tg/2, tb/2, true);
                }
            }
        }
        else if (game.currentmenuname == "playint1" || game.currentmenuname == "playint2")
        {
            dwgfx.Print( -1, 65, "Who do you want to play", tr, tg, tb, true);
            dwgfx.Print( -1, 75, "the level with?", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "playmodes")
        {
            if (game.currentmenuoption == 0)
            {
                dwgfx.bigprint( -1, 30, "Time Trials", tr, tg, tb, true);
                dwgfx.Print( -1, 65, "Replay any level in the game in", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "a competitive time trial mode.", tr, tg, tb, true);

                if (game.gameframerate > 34 || map.invincibility)
                {
                    dwgfx.Print( -1, 105, "Time Trials are not available", tr, tg, tb, true);
                    dwgfx.Print( -1, 115, "with slowdown or invincibility.", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 1)
            {
                dwgfx.bigprint( -1, 30, "Intermissions", tr, tg, tb, true);
                dwgfx.Print( -1, 65, "Replay the intermission levels.", tr, tg, tb, true);

                if (!game.unlock[15] && !game.unlock[16])
                {
                    dwgfx.Print( -1, 95, "TO UNLOCK: Complete the", tr, tg, tb, true);
                    dwgfx.Print( -1, 105, "intermission levels in-game.", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 2)
            {
                dwgfx.bigprint( -1, 30, "No Death Mode", tr, tg, tb, true);
                dwgfx.Print( -1, 65, "Play the entire game", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "without dying once.", tr, tg, tb, true);

                if (game.gameframerate > 34 || map.invincibility)
                {
                    dwgfx.Print( -1, 105, "No death mode is not available", tr, tg, tb, true);
                    dwgfx.Print( -1, 115, "with slowdown or invincibility.", tr, tg, tb, true);
                }
                else if (!game.unlock[17])
                {
                    dwgfx.Print( -1, 105, "TO UNLOCK: Achieve an S-rank or", tr, tg, tb, true);
                    dwgfx.Print( -1, 115, "above in at least 4 time trials.", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 3)
            {
                dwgfx.bigprint( -1, 30, "Flip Mode", tr, tg, tb, true);
                dwgfx.Print( -1, 65, "Flip the entire game vertically.", tr, tg, tb, true);
                dwgfx.Print( -1, 75, "Compatible with other game modes.", tr, tg, tb, true);

                if (game.unlock[18])
                {
                    if (dwgfx.setflipmode)
                    {
                        dwgfx.Print( -1, 105, "Currently ENABLED!", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( -1, 105, "Currently Disabled.", tr/2, tg/2, tb/2, true);
                    }
                }
                else
                {
                    dwgfx.Print( -1, 105, "TO UNLOCK: Complete the game.", tr, tg, tb, true);
                }
            }
        }
        else if (game.currentmenuname == "youwannaquit")
        {
            dwgfx.Print( -1, 75, "ゲームをしゅうりょうしてもよろしいですか?", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "continue")
        {
            dwgfx.crewframedelay--;
            if (dwgfx.crewframedelay <= 0)
            {
                dwgfx.crewframedelay = 8;
                dwgfx.crewframe = (dwgfx.crewframe + 1) % 2;
            }
            if (game.currentmenuoption == 0)
            {
                //Show teleporter save info
                dwgfx.drawpixeltextbox(25, 65-20, 270, 90, 34,12, 65, 185, 207,0,4);

                dwgfx.bigprint(-1, 20, "Tele Save", tr, tg, tb, true);
                dwgfx.Print(0, 80-20, game.tele_currentarea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                for (int i = 0; i < 6; i++)
                {
                    dwgfx.drawcrewman(169-(3*42)+(i*42), 95-20, i, game.tele_crewstats[i], help, true);
                }
                dwgfx.Print(160 - 84, 132-20, game.tele_gametime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                dwgfx.Print(160 + 40, 132-20, help.number(game.tele_trinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                dwgfx.drawspritesetcol(50, 126-20, 50, 18, help);
                dwgfx.drawspritesetcol(175, 126-20, 22, 18, help);
            }
            else if (game.currentmenuoption == 1)
            {
                //Show quick save info
                dwgfx.drawpixeltextbox(25, 65-20, 270, 90, 34,12, 65, 185, 207,0,4);

                dwgfx.bigprint(-1, 20, "Quick Save", tr, tg, tb, true);
                dwgfx.Print(0, 80-20, game.quick_currentarea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                for (int i = 0; i < 6; i++)
                {
                    dwgfx.drawcrewman(169-(3*42)+(i*42), 95-20, i, game.quick_crewstats[i], help, true);
                }
                dwgfx.Print(160 - 84, 132-20, game.quick_gametime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                dwgfx.Print(160 + 40, 132-20, help.number(game.quick_trinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                dwgfx.drawspritesetcol(50, 126-20, 50, 18, help);
                dwgfx.drawspritesetcol(175, 126-20, 22, 18, help);
            }
        }
        else if (game.currentmenuname == "gameover" || game.currentmenuname == "gameover2")
        {
            dwgfx.bigprint( -1, 25, "GAME OVER", tr, tg, tb, true, 3);

            dwgfx.crewframedelay--;
            if (dwgfx.crewframedelay <= 0)
            {
                dwgfx.crewframedelay = 8;
                dwgfx.crewframe = (dwgfx.crewframe + 1) % 2;
            }
            for (int i = 0; i < 6; i++)
            {
                dwgfx.drawcrewman(169-(3*42)+(i*42), 68, i, game.crewstats[i], help, true);
            }
            tempstring = "You rescued " + help.number(game.crewrescued()) + " crewmates";
            dwgfx.Print(0, 100, tempstring, tr, tg, tb, true);

            tempstring = "and found " + help.number(game.trinkets) + " trinkets.";
            dwgfx.Print(0, 110, tempstring, tr, tg, tb, true);

            tempstring = "You managed to reach:";
            dwgfx.Print(0, 145, tempstring, tr, tg, tb, true);
            dwgfx.Print(0, 155, game.hardestroom, tr, tg, tb, true);

            if (game.crewrescued() == 1)
            {
                tempstring = "Keep trying! You'll get there!";
            }
            else if (game.crewrescued() == 2)
            {
                tempstring = "Nice one!";
            }
            else if (game.crewrescued() == 3)
            {
                tempstring = "Wow! Congratulations!";
            }
            else if (game.crewrescued() == 4)
            {
                tempstring = "Incredible!";
            }
            else if (game.crewrescued() == 5)
            {
                tempstring = "Unbelievable! Well done!";
            }
            else if (game.crewrescued() == 6)
            {
                tempstring = "Er, how did you do that?";
            }

            dwgfx.Print(0, 190, tempstring, tr, tg, tb, true);
        }
        else if (game.currentmenuname == "nodeathmodecomplete" || game.currentmenuname == "nodeathmodecomplete2")
        {
            dwgfx.bigprint( -1, 8, "WOW", tr, tg, tb, true, 4);

            dwgfx.crewframedelay--;
            if (dwgfx.crewframedelay <= 0)
            {
                dwgfx.crewframedelay = 8;
                dwgfx.crewframe = (dwgfx.crewframe + 1) % 2;
            }
            for (int i = 0; i < 6; i++)
            {
                dwgfx.drawcrewman(169-(3*42)+(i*42), 68, i, game.crewstats[i], help, true);
            }
            tempstring = "You rescued all the crewmates!";
            dwgfx.Print(0, 100, tempstring, tr, tg, tb, true);

            tempstring = "And you found " + help.number(game.trinkets) + " trinkets.";
            dwgfx.Print(0, 110, tempstring, tr, tg, tb, true);

            dwgfx.Print(0, 160, "A new trophy has been awarded and", tr, tg, tb, true);
            dwgfx.Print(0, 170, "placed in the secret lab to", tr, tg, tb, true);
            dwgfx.Print(0, 180, "acknowledge your achievement!", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "timetrialcomplete" || game.currentmenuname == "timetrialcomplete2"
                 || game.currentmenuname == "timetrialcomplete3" || game.currentmenuname == "timetrialcomplete4")
        {
            dwgfx.bigprint( -1, 20, "Results", tr, tg, tb, true, 3);

            tempstring = game.resulttimestring(help) + " / " + game.partimestring(help);

            dwgfx.drawspritesetcol(30, 80-15, 50, 22, help);
            dwgfx.Print(65, 80-15, "TIME TAKEN:", 255, 255, 255);
            dwgfx.Print(65, 90-15, tempstring, tr, tg, tb);
            if (game.timetrialresulttime <= game.timetrialpar)
            {
                dwgfx.Print(220, 85-15, "+1 Rank!", 255, 255, 255);
            }

            tempstring = help.String(game.deathcounts);
            dwgfx.drawspritesetcol(30-4, 80+20-4, 12, 22, help);
            dwgfx.Print(65, 80+20, "NUMBER OF DEATHS:", 255, 255, 255);
            dwgfx.Print(65, 90+20, tempstring, tr, tg, tb);
            if (game.deathcounts == 0)
            {
                dwgfx.Print(220, 85+20, "+1 Rank!", 255, 255, 255);
            }

            tempstring = help.String(game.trinkets) + " of " + help.String(game.timetrialshinytarget);
            dwgfx.drawspritesetcol(30, 80+55, 22, 22, help);
            dwgfx.Print(65, 80+55, "SHINY TRINKETS:", 255, 255, 255);
            dwgfx.Print(65, 90+55, tempstring, tr, tg, tb);
            if (game.trinkets >= game.timetrialshinytarget)
            {
                dwgfx.Print(220, 85+55, "+1 Rank!", 255, 255, 255);
            }

            if (game.currentmenuname == "timetrialcomplete2" || game.currentmenuname == "timetrialcomplete3")
            {
                dwgfx.bigprint( 100, 175, "Rank:", tr, tg, tb, false, 2);
            }

            if (game.currentmenuname == "timetrialcomplete3")
            {
                switch(game.timetrialrank)
                {
                case 0:
                    dwgfx.bigprint( 195, 165, "B", 255, 255, 255, false, 4);
                    break;
                case 1:
                    dwgfx.bigprint( 195, 165, "A", 255, 255, 255, false, 4);
                    break;
                case 2:
                    dwgfx.bigprint( 195, 165, "S", 255, 255, 255, false, 4);
                    break;
                case 3:
                    dwgfx.bigprint( 195, 165, "V", 255, 255, 255, false, 4);
                    break;
                }
            }
        }
        else if (game.currentmenuname == "unlockmenutrials")
        {
            dwgfx.bigprint( -1, 30, "Unlock Time Trials", tr, tg, tb, true);
            dwgfx.Print( -1, 65, "You can unlock each time", tr, tg, tb, true);
            dwgfx.Print( -1, 75, "trial separately.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "timetrials")
        {
            if (game.currentmenuoption == 0)
            {
                if(game.unlock[9])
                {
                    dwgfx.bigprint( -1, 30, "Space Station 1", tr, tg, tb, true);
                    if (game.besttimes[0] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[0], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[0])+"/2", tr, tg, tb);
                        dwgfx.Print( 110, 85,help.String(game.bestlives[0]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    1:15", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[0])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Rescue Violet", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find three trinkets", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 1)
            {
                if(game.unlock[10])
                {
                    dwgfx.bigprint( -1, 30, "The Laboratory", tr, tg, tb, true);
                    if (game.besttimes[1] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[1], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[1])+"/4", tr, tg, tb);
                        dwgfx.Print( 110, 85, help.String(game.bestlives[1]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    2:45", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[1])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Rescue Victoria", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find six trinkets", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 2)
            {
                if(game.unlock[11])
                {
                    dwgfx.bigprint( -1, 30, "The Tower", tr, tg, tb, true);
                    if (game.besttimes[2] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[2], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[2])+"/2", tr, tg, tb);
                        dwgfx.Print( 110, 85, help.String(game.bestlives[2]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    1:45", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[2])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Rescue Vermilion", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find nine trinkets", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 3)
            {
                if(game.unlock[12])
                {
                    dwgfx.bigprint( -1, 30, "Space Station 2", tr, tg, tb, true);
                    if (game.besttimes[3] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[3], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[3])+"/5", tr, tg, tb);
                        dwgfx.Print( 110, 85, help.String(game.bestlives[3]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    3:20", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[3])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Rescue Vitellary", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find twelve trinkets", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 4)
            {
                if(game.unlock[13])
                {
                    dwgfx.bigprint( -1, 30, "The Warp Zone", tr, tg, tb, true);
                    if (game.besttimes[4] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[4], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[4])+"/1", tr, tg, tb);
                        dwgfx.Print( 110, 85, help.String(game.bestlives[4]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    2:00", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[4])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Rescue Verdigris", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find fifteen trinkets", tr, tg, tb, true);
                }
            }
            else if (game.currentmenuoption == 5)
            {
                if(game.unlock[14])
                {
                    dwgfx.bigprint( -1, 30, "The Final Level", tr, tg, tb, true);
                    if (game.besttimes[5] == -1)
                    {
                        dwgfx.Print( -1, 75, "Not yet attempted", tr, tg, tb, true);
                    }
                    else
                    {
                        dwgfx.Print( 16, 65, "BEST TIME  ", tr, tg, tb);
                        dwgfx.Print( 16, 75, "BEST SHINY ", tr, tg, tb);
                        dwgfx.Print( 16, 85, "BEST LIVES ", tr, tg, tb);
                        dwgfx.Print( 110, 65, game.timetstring(game.besttimes[5], help), tr, tg, tb);
                        dwgfx.Print( 110, 75, help.String(game.besttrinkets[5])+"/1", tr, tg, tb);
                        dwgfx.Print( 110, 85, help.String(game.bestlives[5]), tr, tg, tb);


                        dwgfx.Print( 170, 65, "PAR TIME    2:15", tr, tg, tb);
                        dwgfx.Print( 170, 85, "Best Rank", tr, tg, tb);
                        switch(game.bestrank[5])
                        {
                        case 0:
                            dwgfx.bigprint( 275, 82, "B", 225, 225, 225);
                            break;
                        case 1:
                            dwgfx.bigprint( 275, 82, "A", 225, 225, 225);
                            break;
                        case 2:
                            dwgfx.bigprint( 275, 82, "S", 225, 225, 225);
                            break;
                        case 3:
                            dwgfx.bigprint( 275, 82, "V", 225, 225, 225);
                            break;
                        }
                    }

                }
                else
                {
                    dwgfx.bigprint( -1, 30, "???", tr, tg, tb, true);
                    dwgfx.Print( -1, 60, "TO UNLOCK:", tr, tg, tb, true);
                    dwgfx.Print( -1, 75, "Complete the game", tr, tg, tb, true);
                    dwgfx.Print( -1, 85, "Find eighteen trinkets", tr, tg, tb, true);
                }
            }
        }
        else if (game.currentmenuname == "gamecompletecontinue")
        {
            dwgfx.bigprint( -1, 25, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 45, "Your save files have been updated.", tr, tg, tb, true);

            dwgfx.Print( -1, 110, "If you want to keep exploring", tr, tg, tb, true);
            dwgfx.Print( -1, 120, "the game, select CONTINUE", tr, tg, tb, true);
            dwgfx.Print( -1, 130, "from the play menu.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlockmenu")
        {
            dwgfx.bigprint( -1, 25, "Unlock Play Modes", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 55, "From here, you may unlock parts", tr, tg, tb, true);
            dwgfx.Print( -1, 65, "of the game that are normally", tr, tg, tb, true);
            dwgfx.Print( -1, 75, "unlocked as you play.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlocktimetrial")
        {
            dwgfx.bigprint( -1, 45, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 125, "Your have unlocked", tr, tg, tb, true);
            dwgfx.Print( -1, 135, "a new Time Trial.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlocktimetrials")
        {
            dwgfx.bigprint( -1, 45, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 125, "Your have unlocked some", tr, tg, tb, true);
            dwgfx.Print( -1, 135, "new Time Trials.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlocknodeathmode")
        {
            dwgfx.bigprint( -1, 45, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 125, "Your have unlocked", tr, tg, tb, true);
            dwgfx.Print( -1, 135, "No Death Mode.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlockflipmode")
        {
            dwgfx.bigprint( -1, 45, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 125, "Your have unlocked", tr, tg, tb, true);
            dwgfx.Print( -1, 135, "Flip Mode.", tr, tg, tb, true);
        }
        else if (game.currentmenuname == "unlockintermission")
        {
            dwgfx.bigprint( -1, 45, "Congratulations!", tr, tg, tb, true, 2);

            dwgfx.Print( -1, 125, "Your have unlocked", tr, tg, tb, true);
            dwgfx.Print( -1, 135, "the intermission levels.", tr, tg, tb, true);
        }else if (game.currentmenuname == "playerworlds")
        {   
						dwgfx.tempstring = FILESYSTEM_getUserLevelDirectory();
						if(dwgfx.tempstring.length()>80){
							dwgfx.Print( -1, 160, "プレイヤーレベルをどうにゅうするにはこの", tr, tg, tb, true);
							dwgfx.Print( -1, 170, "フォルダに.vvvvvvファイルをいれてください:", tr, tg, tb, true);
							dwgfx.Print( 320-((dwgfx.tempstring.length()-80)*8), 190, dwgfx.tempstring.substr(0,dwgfx.tempstring.length()-80), tr, tg, tb);
							dwgfx.Print( 0, 200, dwgfx.tempstring.substr(dwgfx.tempstring.length()-80,40), tr, tg, tb);
							dwgfx.Print( 0, 210, dwgfx.tempstring.substr(dwgfx.tempstring.length()-40,40), tr, tg, tb);
						}else if(dwgfx.tempstring.length()>40){
							dwgfx.Print( -1, 170, "プレイヤーレベルをどうにゅうするにはこの", tr, tg, tb, true);
							dwgfx.Print( -1, 180, "フォルダに.vvvvvvファイルをいれてください:", tr, tg, tb, true);
							dwgfx.Print( 320-((dwgfx.tempstring.length()-40)*8), 200, dwgfx.tempstring.substr(0,dwgfx.tempstring.length()-40), tr, tg, tb);
							dwgfx.Print( 0, 210, dwgfx.tempstring.substr(dwgfx.tempstring.length()-40,40), tr, tg, tb);
						}else{
							dwgfx.Print( -1, 180, "プレイヤーレベルをどうにゅうするにはこの", tr, tg, tb, true);
							dwgfx.Print( -1, 190, "フォルダに.vvvvvvファイルをいれてください:", tr, tg, tb, true);
							dwgfx.Print( 320-(dwgfx.tempstring.length()*8), 210, dwgfx.tempstring, tr, tg, tb);
						}
        }

        /*
        switch(game.mainmenu) {
        	case 0:
        		dwgfx.Print(5, 115, "[ NEW GAME ]", tr, tg, tb, true);
        	break;
        	case 1:
        		if (game.telesummary == "") {
        			dwgfx.Print(5, 115, "[ no teleporter save ]", tr/3, tg/3, tb/3, true);
        		}else {
        			dwgfx.Print(5, 115, "[ RESTORE FROM LAST TELEPORTER ]", tr, tg, tb, true);
        			dwgfx.Print(5, 125, game.telesummary, tr, tg, tb, true);
        		}
        	break;
        	case 2:
        		if (game.quicksummary == "") {
        			dwgfx.Print(5, 115, "[ no quicksave ]", tr/3, tg/3, tb/3, true);
        		}else {
        			dwgfx.Print(5, 115, "[ RESTORE FROM LAST QUICKSAVE ]", tr, tg, tb, true);
        			dwgfx.Print(5, 125, game.quicksummary, tr, tg, tb, true);
        		}
        	break;
        }
        */

        tr = int(tr * .8f);
        tg = int(tg * .8f);
        tb = int(tb * .8f);
        if (tr < 0) tr = 0;
        if(tr>255) tr=255;
        if (tg < 0) tg = 0;
        if(tg>255) tg=255;
        if (tb < 0) tb = 0;
        if(tb>255) tb=255;
        if (game.currentmenuname == "timetrials" || game.currentmenuname == "unlockmenutrials")
        {
            dwgfx.drawmenu(game, tr, tg, tb, 15);
        }
        else if (game.currentmenuname == "unlockmenu")
        {
            dwgfx.drawmenu(game, tr, tg, tb, 15);
        }
        else if (game.currentmenuname == "playmodes")
        {
            dwgfx.drawmenu(game, tr, tg, tb, 20);
        }
        else if (game.currentmenuname == "mainmenu")
        {
            dwgfx.drawmenu(game, tr, tg, tb, 15);
        }
        else if (game.currentmenuname == "playerworlds")
        {
            dwgfx.drawmenu(game, tr, tg, tb, 15);
        }
        else if (game.currentmenuname == "levellist")
        {
            dwgfx.drawlevelmenu(game, tr, tg, tb, 5);
        }
        else
        {
            dwgfx.drawmenu(game, tr, tg, tb);
        }

        //dwgfx.Print(5, 228, "Left/Right to Choose, V to Select", tr, tg, tb, true);
    }

    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    dwgfx.drawfade();

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (game.screenshake > 0  && !game.noflashingmode)
    {
        game.screenshake--;
        dwgfx.screenshake();
    }
    else
    {
        dwgfx.render();
    }
    //dwgfx.backbuffer.unlock();
}

void gamecompleterender(Graphics& dwgfx, Game& game, entityclass& obj, UtilityClass& help, mapclass& map)
{
    //dwgfx.backbuffer.lock();
    FillRect(dwgfx.backBuffer, 0x000000);

    if(!game.colourblindmode) dwgfx.drawtowerbackgroundsolo(map);
    //dwgfx.drawtowermap(map);

    for (int i = 0; i < 6; i++)
    {
        //dwgfx.drawsprite((160-96)+ i * 32, 10, 23, 96+(i*10)+(random()*16), 196-(help.glow)-(random()*16), 255 - (help.glow*2));
    }

    tr = map.r - (help.glow / 4) - fRandom() * 4;
    tg = map.g - (help.glow / 4) - fRandom() * 4;
    tb = map.b - (help.glow / 4) - fRandom() * 4;
    if (tr < 0) tr = 0;
    if(tr>255) tr=255;
    if (tg < 0) tg = 0;
    if(tg>255) tg=255;
    if (tb < 0) tb = 0;
    if(tb>255) tb=255;


    //rendering starts... here!

    if (dwgfx.onscreen(220 + game.creditposition))
    {
        temp = 220 + game.creditposition;
        dwgfx.drawsprite((160 - 96) + 0 * 32, temp, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 1 * 32, temp, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 2 * 32, temp, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 3 * 32, temp, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 4 * 32, temp, 23, tr, tg, tb);
        dwgfx.drawsprite((160 - 96) + 5 * 32, temp, 23, tr, tg, tb);
    }

    if (dwgfx.onscreen(290 + game.creditposition)) dwgfx.bigprint( -1, 290 + game.creditposition, "Starring", tr, tg, tb, true, 2);

    if (dwgfx.onscreen(320 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 320 + game.creditposition, 0, true, help);
        dwgfx.Print(100, 330 + game.creditposition, "Captain Viridian", tr, tg, tb);
    }
    if (dwgfx.onscreen(350 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 350 + game.creditposition, 1, true, help);
        dwgfx.Print(100, 360 + game.creditposition, "Doctor Violet", tr, tg, tb);
    }
    if (dwgfx.onscreen(380 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 380 + game.creditposition, 2, true, help);
        dwgfx.Print(100, 390 + game.creditposition, "Professor Vitellary", tr, tg, tb);
    }
    if (dwgfx.onscreen(410 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 410 + game.creditposition, 3, true, help);
        dwgfx.Print(100, 420 + game.creditposition, "Officer Vermilion", tr, tg, tb);
    }
    if (dwgfx.onscreen(440 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 440 + game.creditposition, 4, true, help);
        dwgfx.Print(100, 450 + game.creditposition, "Chief Verdigris", tr, tg, tb);
    }
    if (dwgfx.onscreen(470 + game.creditposition))
    {
        dwgfx.drawcrewman(70, 470 + game.creditposition, 5, true, help);
        dwgfx.Print(100, 480 + game.creditposition, "Doctor Victoria", tr, tg, tb);
    }

    if (dwgfx.onscreen(520 + game.creditposition)) dwgfx.bigprint( -1, 520 + game.creditposition, "Credits", tr, tg, tb, true, 3);

    if (dwgfx.onscreen(560 + game.creditposition))
    {
        dwgfx.Print(40, 560 + game.creditposition, "Created by", tr, tg, tb);
        dwgfx.bigprint(60, 570 + game.creditposition, "Terry Cavanagh", tr, tg, tb);
    }

    if (dwgfx.onscreen(600 + game.creditposition))
    {
        dwgfx.Print(40, 600 + game.creditposition, "With Music by", tr, tg, tb);
        dwgfx.bigprint(60, 610 + game.creditposition, "Magnus P~lsson", tr, tg, tb);
    }

    if (dwgfx.onscreen(640 + game.creditposition))
    {
        dwgfx.Print(40, 640 + game.creditposition, "Rooms Named by", tr, tg, tb);
        dwgfx.bigprint(60, 650 + game.creditposition, "Bennett Foddy", tr, tg, tb);
    }

    if (dwgfx.onscreen(680 + game.creditposition))
    {
        dwgfx.Print(40, 680 + game.creditposition, "C++ Port by", tr, tg, tb);
        dwgfx.bigprint(60, 690 + game.creditposition, "Simon Roth", tr, tg, tb);
        dwgfx.bigprint(60, 710 + game.creditposition, "Ethan Lee", tr, tg, tb);
    }


    if (dwgfx.onscreen(740 + game.creditposition))
    {
        dwgfx.Print(40, 740 + game.creditposition, "Beta Testing by", tr, tg, tb);
        dwgfx.bigprint(60, 750 + game.creditposition, "Sam Kaplan", tr, tg, tb);
        dwgfx.bigprint(60, 770 + game.creditposition, "Pauli Kohberger", tr, tg, tb);
    }

    if (dwgfx.onscreen(800 + game.creditposition))
    {
        dwgfx.Print(40, 800 + game.creditposition, "Ending Picture by", tr, tg, tb);
        dwgfx.bigprint(60, 810 + game.creditposition, "Pauli Kohberger", tr, tg, tb);
    }

    if (dwgfx.onscreen(890 + game.creditposition)) dwgfx.bigprint( -1, 870 + game.creditposition, "Patrons", tr, tg, tb, true, 3);

    int creditOffset = 930;

    for (size_t i = 0; i < game.superpatrons.size(); i += 1)
    {
        if (dwgfx.onscreen(creditOffset + game.creditposition))
        {
            dwgfx.Print(-1, creditOffset + game.creditposition, game.superpatrons[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 10;
    if (dwgfx.onscreen(creditOffset + game.creditposition)) dwgfx.Print( -1, creditOffset + game.creditposition, "and", tr, tg, tb, true);
    creditOffset += 20;

    for (size_t i = 0; i < game.patrons.size(); i += 1)
    {
        if (dwgfx.onscreen(creditOffset + game.creditposition))
        {
            dwgfx.Print(-1, creditOffset + game.creditposition, game.patrons[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 20;
    if (dwgfx.onscreen(creditOffset + game.creditposition)) dwgfx.bigprint(40, creditOffset + game.creditposition, "GitHub Contributors", tr, tg, tb, true);
    creditOffset += 30;

    for (size_t i = 0; i < game.githubfriends.size(); i += 1)
    {
        if (dwgfx.onscreen(creditOffset + game.creditposition))
        {
            dwgfx.Print(-1, creditOffset + game.creditposition, game.githubfriends[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 140;
    if (dwgfx.onscreen(creditOffset + game.creditposition)) dwgfx.bigprint( -1, creditOffset + game.creditposition, "Thanks for playing!", tr, tg, tb, true, 2);

    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    dwgfx.drawfade();

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (game.screenshake > 0 && !game.noflashingmode)
    {
        game.screenshake--;
        dwgfx.screenshake();
    }
    else
    {
        dwgfx.render();
    }
    //dwgfx.backbuffer.unlock();
}

void gamecompleterender2(Graphics& dwgfx, Game& game, entityclass& obj, UtilityClass& help)
{
    //dwgfx.backbuffer.lock();
    FillRect(dwgfx.backBuffer, 0x000000);

    dwgfx.drawimage(10, 0, 0);

    for (int j = 0; j < 30; j++)
    {
        for (int i = 0; i < 40; i++)
        {
            if (j == game.creditposy)
            {
                if (i > game.creditposx)
                {
                    FillRect(dwgfx.backBuffer, i * 8, j * 8, 8, 8, 0, 0, 0);
                }
            }

            if (j > game.creditposy)
            {
                FillRect(dwgfx.backBuffer, i * 8, j * 8, 8, 8, 0, 0, 0);
            }
        }
    }

    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    dwgfx.drawfade();

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (game.screenshake > 0 && !game.noflashingmode)
    {
        game.screenshake--;
        dwgfx.screenshake();
    }
    else
    {
        dwgfx.render();
    }
    //dwgfx.backbuffer.unlock();
}

void gamerender(Graphics& dwgfx, mapclass& map, Game& game, entityclass& obj, UtilityClass& help)
{



    if(!game.blackout)
    {

        if(!game.colourblindmode)
		{
        dwgfx.drawbackground(map.background, map);
		}
		else
		{
			FillRect(dwgfx.backBuffer,0x00000);
		}
        if (map.final_colormode)
		{
        	dwgfx.drawfinalmap(map);
        }
        else
		{
        dwgfx.drawmap(map);
        }


        if(!game.completestop)
        {
            for (int i = 0; i < obj.nentity; i++)
            {
                //Is this entity on the ground? (needed for jumping)
                if (obj.entitycollidefloor(map, i))
                {
                    obj.entities[i].onground = 2;
                }
                else
                {
                    obj.entities[i].onground--;
                }

                if (obj.entitycollideroof(map, i))
                {
                    obj.entities[i].onroof = 2;
                }
                else
                {
                    obj.entities[i].onroof--;
                }

                //Animate the entities
                obj.animateentities(i, game, help);
            }
        }

        dwgfx.drawentities(map, obj, help);
    }

    /*for(int i=0; i<obj.nblocks; i++){
    if (obj.blocks[i].active) {
    		dwgfx.backbuffer.fillRect(obj.blocks[i].rect, 0xDDDDDD);
    }
      }*/
    //dwgfx.drawminimap(game, map);

    if(map.extrarow==0 || (map.custommode && map.roomname!=""))
    {
        FillRect(dwgfx.backBuffer, dwgfx.footerrect, 0);

        if (map.finalmode)
        {
        	map.glitchname = map.getglitchname(game.roomx, game.roomy);
          dwgfx.Print(5, 231, map.glitchname, 196, 196, 255 - help.glow, true);
        }else{
          dwgfx.Print(5, 231, map.roomname, 196, 196, 255 - help.glow, true);
        }
    }

    if (map.roomtexton)
    {
        //Draw room text!
        for (int i = 0; i < map.roomtextnumlines; i++)
        {
            dwgfx.Print(map.roomtextx[i]*8, (map.roomtexty[i]*8), map.roomtext[i], 196, 196, 255 - help.glow);
        }
    }

    // scriptrender

    for(growing_vector<std::string>::size_type i = 0; i < script.scriptrender.size(); i++) {
        scriptimage current = script.scriptrender[i];
        if (current.type == 0) {
            dwgfx.Print(current.x,current.y,current.text,current.r,current.g,current.b, current.center);
        } else if (current.type == 1) {
            auto pixels = (uint8_t*) dwgfx.backBuffer->pixels;
            auto row = pixels + dwgfx.backBuffer->pitch * current.y;
            auto pixel = (uint32_t*) (row + current.x);
            *pixel = dwgfx.getRGB(current.r, current.g, current.b);
        } else if (current.type == 2) {
            SDL_Rect temprect;
            temprect.x = current.x;
            temprect.y = current.y;
            temprect.w = current.w;
            temprect.h = current.h;
            SDL_FillRect(dwgfx.backBuffer, &temprect, dwgfx.getRGB(current.r,current.g,current.b));
            //dwgfx.FillRect(dwgfx.backBuffer, current.x, current.y, current.w, current.h, current.r, current.g, current.b);
        }
    }
    script.scriptrender.clear();

    if(map.custommode && !map.custommodeforreal && !game.advancetext){
        //Return to level editor
        dwgfx.bprint(5, 5, "[ENTERをおしてエディターへ戻る]", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
    }


    dwgfx.cutscenebars();
    dwgfx.drawfade();
	BlitSurfaceStandard(dwgfx.backBuffer, NULL, dwgfx.tempBuffer, NULL);

    dwgfx.drawgui(help);
    if (dwgfx.flipmode)
    {
        if (game.advancetext) dwgfx.bprint(5, 228, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }
    else
    {
        if (game.advancetext) dwgfx.bprint(5, 5, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }

    if (game.readytotele > 100 && !game.advancetext && game.hascontrol && (!script.running || (script.running && script.passive)) && !game.intimetrial)
    {
        if(dwgfx.flipmode)
        {
            dwgfx.bprint(5, 20, "- ENTER をおしてテレポート -", game.readytotele - 20 - (help.glow / 2), game.readytotele - 20 - (help.glow / 2), game.readytotele, true);
        }
        else
        {
            dwgfx.bprint(5, 210, "- ENTER をおしてテレポート -", game.readytotele - 20 - (help.glow / 2), game.readytotele - 20 - (help.glow / 2), game.readytotele, true);
        }
    }

    if (game.swnmode)
    {
        if (game.swngame == 0)
        {
            tempstring = help.timestring(game.swntimer);
            dwgfx.bigprint( -1, 20, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
        }
        else if (game.swngame == 1)
        {
            if (game.swnmessage == 0)
            {
                tempstring = help.timestring(game.swntimer);
                dwgfx.Print( 10, 10, "げんざいのタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                dwgfx.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecord);
                dwgfx.Print( 240, 10, "じこベストタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                dwgfx.bigrprint( 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    dwgfx.Print( -1, 204, "5びょうでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 1:
                    dwgfx.Print( -1, 204, "10びょうでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 2:
                    dwgfx.Print( -1, 204, "15びょうでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 3:
                    dwgfx.Print( -1, 204, "20びょうでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 4:
                    dwgfx.Print( -1, 204, "30びょうでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 5:
                    dwgfx.Print( -1, 204, "1ふんでつぎのトロフィー", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 6:
                    dwgfx.Print( -1, 204, "トロフィーをすべてかくとく!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                }
            }
            else if (game.swnmessage == 1)
            {
                tempstring = help.timestring(game.swntimer);
                dwgfx.Print( 10, 10, "げんざいのタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                dwgfx.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecord);
                if (int(game.deathseq / 5) % 2 == 1)
                {
                    dwgfx.Print( 240, 10, "じこベストタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                    dwgfx.bigrprint( 300, 24, tempstring, 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2), false, 2);

                    dwgfx.bigprint( -1, 200, "きろくこうしん!", 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2), true, 2);
                }
            }
            else if (game.swnmessage >= 2)
            {
                game.swnmessage--;
                if (game.swnmessage == 2) game.swnmessage = 0;
                tempstring = help.timestring(game.swntimer);
                dwgfx.Print( 10, 10, "げんざいのじかん", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                dwgfx.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecord);
                dwgfx.Print( 240, 10, "じこベストタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                dwgfx.bigrprint( 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);

                if (int(game.swnmessage / 5) % 2 == 1)
                {
                    dwgfx.bigprint( -1, 200, "きろくこうしん!", 220 - (help.glow), 128 - (help.glow), 128 - (help.glow / 2), true, 2);
                }
            }

            dwgfx.Print( 20, 228, "[ENTER をおしてしゅうりょう]", 160 - (help.glow/2), 160 - (help.glow/2), 160 - (help.glow/2), true);
        }
        else if(game.swngame==2)
        {
            if (int(game.swndelay / 15) % 2 == 1 || game.swndelay >= 120)
            {
                if (dwgfx.flipmode)
                {
                    dwgfx.bigprint( -1, 30, "60びょうかん", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                    dwgfx.bigprint( -1, 10, "いきのびろ！", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                }
                else
                {
                    dwgfx.bigprint( -1, 10, "60びょうかん", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                    dwgfx.bigprint( -1, 30, "いきのびろ！", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                }
            }
        }
        else if(game.swngame==7)
        {
            if (game.swndelay >= 60)
            {
                dwgfx.bigprint( -1, 20, "スーパーグラビトロン", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);

                tempstring = help.timestring(game.swnrecord);
                dwgfx.Print( 240, 190, "じこベストタイム", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                dwgfx.bigrprint( 300, 205, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
            }
            else	if (int(game.swndelay / 10) % 2 == 1)
            {
                dwgfx.bigprint( -1, 20, "スーパーグラビトロン", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                dwgfx.bigprint( -1, 200, "スタート!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 3);
            }
        }
    }

    if (game.intimetrial && dwgfx.fademode==0)
    {
        //Draw countdown!
        if (game.timetrialcountdown > 0)
        {
            if (game.timetrialcountdown < 30)
            {
                game.resetgameclock();
                if (int(game.timetrialcountdown / 4) % 2 == 0) dwgfx.bigprint( -1, 100, "Go!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 60)
            {
                dwgfx.bigprint( -1, 100, "1", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 90)
            {
                dwgfx.bigprint( -1, 100, "2", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 120)
            {
                dwgfx.bigprint( -1, 100, "3", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
        }
        else
        {
            //Draw OSD stuff
            dwgfx.bprint(6, 18, "TIME :",  255,255,255);
            dwgfx.bprint(6, 30, "DEATH:",  255, 255, 255);
            dwgfx.bprint(6, 42, "SHINY:",  255,255,255);

            if(game.timetrialparlost)
            {
                dwgfx.bprint(56, 18, game.timestring(help),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 18, game.timestring(help),  196, 196, 196);
            }
            if(game.deathcounts>0)
            {
                dwgfx.bprint(56, 30,help.String(game.deathcounts),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 30,help.String(game.deathcounts),  196, 196, 196);
            }
            if(game.trinkets<game.timetrialshinytarget)
            {
                dwgfx.bprint(56, 42,help.String(game.trinkets) + " of " +help.String(game.timetrialshinytarget),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 42,help.String(game.trinkets) + " of " +help.String(game.timetrialshinytarget),  196, 196, 196);
            }

            if(game.timetrialparlost)
            {
                dwgfx.bprint(195, 214, "PAR TIME:",  80, 80, 80);
                dwgfx.bprint(275, 214, game.partimestring(help),  80, 80, 80);
            }
            else
            {
                dwgfx.bprint(195, 214, "PAR TIME:",  255, 255, 255);
                dwgfx.bprint(275, 214, game.partimestring(help),  196, 196, 196);
            }
        }
    }

    if (game.activeactivity > -1)
    {
        //dwgfx.backbuffer.fillRect(new Rectangle(0, 0, 320, 18), 0x000000);
        game.activity_lastprompt = obj.blocks[game.activeactivity].prompt;
        game.activity_r = obj.blocks[game.activeactivity].r;
        game.activity_g = obj.blocks[game.activeactivity].g;
        game.activity_b = obj.blocks[game.activeactivity].b;
        if(game.act_fade<5) game.act_fade=5;
        if(game.act_fade<10)
        {
            game.act_fade++;
        }
        dwgfx.drawtextbox(16, 4, 36, 3, game.activity_r*(game.act_fade/10.0f), game.activity_g*(game.act_fade/10.0f), game.activity_b*(game.act_fade/10.0f));
        dwgfx.Print(5, 12, game.activity_lastprompt, game.activity_r*(game.act_fade/10.0f), game.activity_g*(game.act_fade/10.0f), game.activity_b*(game.act_fade/10.0f), true);
    }
    else
    {
        if(game.act_fade>5)
        {
            dwgfx.drawtextbox(16, 4, 36, 3, game.activity_r*(game.act_fade/10.0f), game.activity_g*(game.act_fade/10.0f), game.activity_b*(game.act_fade/10.0f));
            dwgfx.Print(5, 12, game.activity_lastprompt, game.activity_r*(game.act_fade/10.0f), game.activity_g*(game.act_fade/10.0f), game.activity_b*(game.act_fade/10.0f), true);
            game.act_fade--;
        }
    }

    if (obj.trophytext > 0)
    {
        dwgfx.drawtrophytext(obj, help);
        obj.trophytext--;
    }

    //dwgfx.rprint(5, 231,help.String(game.coins), 255 - help.glow/2, 255 - help.glow/2, 196, true);
    //dwgfx.drawhuetile(311, 230, 48, 1);

    //Level complete image
    //if (game.state >= 3007) {
    //	dwgfx.drawimage(0, 0, 12, true);
    //}

    //state changes

    /*
    game.test = true;
    if (game.teststring !=help.String(game.state)) trace(game.state);
    game.teststring =help.String(game.state);
    */

    //Detail entity info for debuging
    /*
    for (int i = 0; i < obj.nentity; i++) {
    	game.tempstring =help.String(obj.entities[i].type) +", (" +help.String(obj.entities[i].xp) + "," +help.String(obj.entities[i].yp) + ")";
    	game.tempstring += " state:" +obj.entities[i].state + ", delay:" + obj.entities[i].statedelay;
    	dwgfx.Print(5, 5 + i * 8, game.tempstring, 255, 255, 255);
    }
    */

    /*
    game.test = true;
    game.teststring =help.String(int(obj.entities[obj.getplayer()].xp)) + "," +help.String(int(obj.entities[obj.getplayer()].yp));
    game.teststring += "   [" +help.String(game.roomx) + "," +help.String(game.roomy) + "]";
    */

    //game.test = true;
    //game.teststring = "Current room deaths: " +help.String(game.currentroomdeaths);

    //Special thing for loading:
    /*
    if(dwgfx.fademode==1){
      if(game.mainmenu==22){
        dwgfx.Print(5, 225, "Loading...", 196, 196, 255 - help.glow, false);
      }
    }
    */


    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (game.screenshake > 0 && !game.noflashingmode)
    {
        game.screenshake--;
        dwgfx.screenshake();
    }
    else
    {
        dwgfx.render();
    }

    //dwgfx.backbuffer.unlock();
}

void maprender(Graphics& dwgfx, Game& game, mapclass& map, entityclass& obj, UtilityClass& help)
{
    //dwgfx.backbuffer.lock();


    dwgfx.drawgui(help);

    //draw screen alliteration
    //Roomname:
	//CRASH
    temp = map.area(game.roomx, game.roomy);
    if (temp < 2 && !map.custommode && dwgfx.fademode==0)
    {
        if (game.roomx >= 102 && game.roomx <= 104 && game.roomy >= 110 && game.roomy <= 111)
        {
            dwgfx.Print(5, 2, "The Ship", 196, 196, 255 - help.glow, true);
        }
        else
        {
            dwgfx.Print(5, 2, "Dimension VVVVVV", 196, 196, 255 - help.glow, true);
        }
    }
    else
    {
      if (map.finalmode){
        map.glitchname = map.getglitchname(game.roomx, game.roomy);
        dwgfx.Print(5, 2, map.glitchname, 196, 196, 255 - help.glow, true);
      }else{
        dwgfx.Print(5, 2, map.roomname, 196, 196, 255 - help.glow, true);
      }
    }

    //Background color
    //dwgfx.drawfillrect(0, 12, 320, 240, 10, 24, 26);
    FillRect(dwgfx.backBuffer,0, 12, 320, 240, 10, 24, 26 );

    dwgfx.crewframedelay--;
    if (dwgfx.crewframedelay <= 0)
    {
        dwgfx.crewframedelay = 8;
        dwgfx.crewframe = (dwgfx.crewframe + 1) % 2;
    }



    //Menubar:
    dwgfx.drawtextbox( -10, 212, 42, 3, 65, 185, 207);
    switch(game.menupage)
    {
    case 0:
        dwgfx.Print(30 - 8, 220, "[マップ]", 196, 196, 255 - help.glow);
        if (game.insecretlab)
        {
            dwgfx.Print(103, 220, "グラビトロン", 64, 64, 64);
        }
        else if (obj.flags[67] == 1 && !map.custommode)
        {
            dwgfx.Print(103, 220, "うちゅうせん", 64,64,64);
        }
        else
        {
            dwgfx.Print(103, 220, "なかま", 64,64,64);
        }
        dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
        dwgfx.Print(258, 220, "セーブ", 64,64,64);

        if (map.finalmode || (map.custommode&&!map.customshowmm))
        {
            //draw the map image
            dwgfx.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
            dwgfx.drawimage(1, 40, 21, false);
            for (int j = 0; j < 20; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    dwgfx.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
                }
            }
            dwgfx.Print(-1, 105, "しんごうなし", 245, 245, 245, true);
        }
        else if(map.custommode)
        {
          //draw the map image
          dwgfx.drawcustompixeltextbox(35+map.custommmxoff, 16+map.custommmyoff, map.custommmxsize+10, map.custommmysize+10, (map.custommmxsize+10)/8, (map.custommmysize+10)/8, 65, 185, 207,4,0);
          dwgfx.drawpartimage(12, 40+map.custommmxoff, 21+map.custommmyoff, map.custommmxsize,map.custommmysize);

          //Black out here
          if (!map.nofog) {
            if(map.customzoom==4){
                for (int j = 0; j < map.customheight; j++){
                for (int i = 0; i < map.customwidth; i++){
                    if(map.explored[i+(j*20)]==0){
                    //Draw the fog of war on the map
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36), false);

                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+ 21 + 9 + (j * 36), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36), false);

                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36)+18, false);

                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + 9 + (j * 36)+18, false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36)+18, false);
                    }
                }
                }
            }else if(map.customzoom==2){
                for (int j = 0; j < map.customheight; j++){
                for (int i = 0; i < map.customwidth; i++){
                    if(map.explored[i+(j*20)]==0){
                    //Draw the fog of war on the map
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + 9 + (j * 18), false);
                    dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + 9+ (j * 18), false);
                    }
                }
                }
            }else{
                for (int j = 0; j < map.customheight; j++){
                for (int i = 0; i < map.customwidth; i++){
                    if(map.explored[i+(j*20)]==0){
                    //Draw the fog of war on the map
                    dwgfx.drawimage(2, map.custommmxoff+40 + (i * 12), map.custommmyoff+21 + (j * 9), false);
                    }
                }
                }
            }
          }

          if (map.cursorstate == 0){
            map.cursordelay++;
            if (map.cursordelay > 10){
              map.cursorstate = 1;
              map.cursordelay = 0;
            }
          }else if (map.cursorstate == 1){
            map.cursordelay++;
            if (map.cursordelay > 30) map.cursorstate = 2;
          }else if (map.cursorstate == 2){
            map.cursordelay++;
          }

          //normal size maps
          if(map.customzoom==4){
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 48) +map.custommmxoff, 21 + ((game.roomy - 100) * 36)+map.custommmyoff , 48 , 36 , 255,255,255);
                dwgfx.drawrect(40 + ((game.roomx - 100) * 48) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 36) + 2+map.custommmyoff, 48 - 4, 36 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 48) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 36) + 2+map.custommmyoff, 48 - 4, 36 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }else if(map.customzoom==2){
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 24)+map.custommmxoff , 21 + ((game.roomy - 100) * 18)+map.custommmyoff , 24 , 18 , 255,255,255);
                dwgfx.drawrect(40 + ((game.roomx - 100) * 24) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 18) + 2+map.custommmyoff, 24 - 4, 18 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 24) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 18) + 2+map.custommmyoff, 24 - 4, 18 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }else{
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 12)+map.custommmxoff , 21 + ((game.roomy - 100) * 9)+map.custommmyoff , 12 , 9 , 255,255,255);
                dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 9) + 2+map.custommmyoff, 12 - 4, 9 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 9) + 2+map.custommmyoff, 12 - 4, 9 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }
            for (auto marker : game.scriptmarkers)
            {
                if (!game.hidemarkers) dwgfx.drawtile(43 + (marker.x * 12), 22 + (marker.y * 9), marker.tile);
            }
        }
        else
        {
            //draw the map image
            dwgfx.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
            dwgfx.drawimage(1, 40, 21, false);

            //black out areas we can't see yet
            for (int j = 0; j < 20; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    if(map.explored[i+(j*20)]==0)
                    {
                        //Draw the fog of war on the map
                        dwgfx.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
                    }
                }
            }
            //draw the coordinates
            if (game.roomx == 109)
            {
                //tower!instead of room y, scale map.ypos
                /*if (map.ypos > (0.57 * (680 * 8))) {
                	i = int(map.ypos - (0.57 * (680 * 8)));
                	i = int((i / (0.43 * (680 * 8)))*9);
                	dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + i + 2, 12 - 4, 9 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
                }*/
                if (map.cursorstate == 0)
                {
                    map.cursordelay++;
                    if (map.cursordelay > 10)
                    {
                        map.cursorstate = 1;
                        map.cursordelay = 0;
                    }
                }
                else if (map.cursorstate == 1)
                {
                    map.cursordelay++;
                    if (int(map.cursordelay / 4) % 2 == 0)
                    {
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) , 21 , 12, 180, 255,255,255);
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2 , 21  + 2, 12 - 4, 180 - 4, 255,255,255);
                    }
                    if (map.cursordelay > 30) map.cursorstate = 2;
                }
                else if (map.cursorstate == 2)
                {
                    map.cursordelay++;
                    if (int(map.cursordelay / 15) % 2 == 0)
                    {
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2 , 21  + 2, 12 - 4, 180 - 4,16, 245 - (help.glow), 245 - (help.glow));
                    }
                }
            }
            else
            {
                if (map.cursorstate == 0)
                {
                    map.cursordelay++;
                    if (map.cursordelay > 10)
                    {
                        map.cursorstate = 1;
                        map.cursordelay = 0;
                    }
                }
                else if (map.cursorstate == 1)
                {
                    map.cursordelay++;
                    if (int(map.cursordelay / 4) % 2 == 0)
                    {
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) , 21 + ((game.roomy - 100) * 9) , 12 , 9 , 255,255,255);
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 255,255,255);
                    }
                    if (map.cursordelay > 30) map.cursorstate = 2;
                }
                else if (map.cursorstate == 2)
                {
                    map.cursordelay++;
                    if (int(map.cursordelay / 15) % 2 == 0)
                    {
                        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 16, 245 - (help.glow), 245 - (help.glow));
                    }
                }
            }

            //draw legend details
            for (int i = 0; i < map.numteleporters; i++)
            {
                if (map.showteleporters && map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)] > 0)
                {
                    temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
                    if (dwgfx.flipmode) temp += 3;
                    dwgfx.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
                }
                else if(map.showtargets && map.explored[map.teleporters[i].x+(20*map.teleporters[i].y)]==0)
                {
                    temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
                    if (dwgfx.flipmode) temp += 3;
                    dwgfx.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
                }
                //dwgfx.drawtile(40+3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), 1086); //for shiny trinkets, do later
            }

            if (map.showtrinkets)
            {
                for (int i = 0; i < map.numshinytrinkets; i++)
                {
                    if (obj.collect[i] == 0)
                    {
                        temp = 1086;
                        if (dwgfx.flipmode) temp += 3;
                        dwgfx.drawtile(40 + 3 + (map.shinytrinkets[i].x * 12), 22 + (map.shinytrinkets[i].y * 9),	temp);
                    }
                }
            }
        }
        break;
    case 1:
        if (game.insecretlab)
        {
            dwgfx.Print(30, 220, "マップ", 64,64,64);
            dwgfx.Print(103-8, 220, "[グラビトロン]", 196, 196, 255 - help.glow);
            dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
            dwgfx.Print(258, 220, "セーブ", 64, 64, 64);

            if (dwgfx.flipmode)
            {
                dwgfx.Print(0, 174, "SUPER GRAVITRON HIGHSCORE", 196, 196, 255 - help.glow, true);

                tempstring = help.timestring(game.swnrecord);
                dwgfx.Print( 240, 124, "Best Time", 196, 196, 255 - help.glow, true);
                dwgfx.bigrprint( 300, 94, tempstring, 196, 196, 255 - help.glow, true, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    dwgfx.Print( -1, 40, "Next Trophy at 5 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 1:
                    dwgfx.Print( -1, 40, "Next Trophy at 10 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 2:
                    dwgfx.Print( -1, 40, "Next Trophy at 15 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 3:
                    dwgfx.Print( -1, 40, "Next Trophy at 20 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 4:
                    dwgfx.Print( -1, 40, "Next Trophy at 30 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 5:
                    dwgfx.Print( -1, 40, "Next Trophy at 1 minute", 196, 196, 255 - help.glow, true);
                    break;
                case 6:
                    dwgfx.Print( -1, 40, "All Trophies collected!", 196, 196, 255 - help.glow, true);
                    break;
                }
            }
            else
            {
                dwgfx.Print(0, 40, "SUPER GRAVITRON HIGHSCORE", 196, 196, 255 - help.glow, true);

                tempstring = help.timestring(game.swnrecord);
                dwgfx.Print( 240, 90, "Best Time", 196, 196, 255 - help.glow, true);
                dwgfx.bigrprint( 300, 104, tempstring, 196, 196, 255 - help.glow, true, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    dwgfx.Print( -1, 174, "Next Trophy at 5 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 1:
                    dwgfx.Print( -1, 174, "Next Trophy at 10 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 2:
                    dwgfx.Print( -1, 174, "Next Trophy at 15 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 3:
                    dwgfx.Print( -1, 174, "Next Trophy at 20 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 4:
                    dwgfx.Print( -1, 174, "Next Trophy at 30 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 5:
                    dwgfx.Print( -1, 174, "Next Trophy at 1 minute", 196, 196, 255 - help.glow, true);
                    break;
                case 6:
                    dwgfx.Print( -1, 174, "All Trophies collected!", 196, 196, 255 - help.glow, true);
                    break;
                }
            }
        }
        else if (obj.flags[67] == 1 && !map.custommode)
        {
            dwgfx.Print(30, 220, "マップ", 64,64,64);
            dwgfx.Print(103-8, 220, "[うちゅうせん]", 196, 196, 255 - help.glow);
            dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
            dwgfx.Print(258, 220, "セーブ", 64, 64, 64);

            dwgfx.Print(0, 105, "Press ACTION to warp to the ship.", 196, 196, 255 - help.glow, true);
        }
        else if(map.custommode){
          dwgfx.Print(30, 220, "マップ", 64,64,64);
            dwgfx.Print(103-8, 220, "[なかま]", 196, 196, 255 - help.glow);
            dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
            dwgfx.Print(258, 220, "セーブ", 64, 64, 64);

            if (dwgfx.flipmode)
            {
              dwgfx.bigprint( -1, 220-45, ed.ListOfMetaData[game.playcustomlevel].title, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 220-70, "by " + ed.ListOfMetaData[game.playcustomlevel].creator, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 220-80, ed.ListOfMetaData[game.playcustomlevel].website, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 220-100, ed.ListOfMetaData[game.playcustomlevel].Desc1, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 220-110, ed.ListOfMetaData[game.playcustomlevel].Desc2, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 220-120, ed.ListOfMetaData[game.playcustomlevel].Desc3, 196, 196, 255 - help.glow, true);

              if(map.customcrewmates-game.crewmates==1){
                dwgfx.Print(1,220-165, help.number(int(map.customcrewmates-game.crewmates))+ " にんのなかまがのこっている", 196, 196, 255 - help.glow, true);
              }else if(map.customcrewmates-game.crewmates>0){
                dwgfx.Print(1,220-165, help.number(int(map.customcrewmates-game.crewmates))+ " にんのなかまがのこっている", 196, 196, 255 - help.glow, true);
              }
            }
            else
            {
              dwgfx.bigprint( -1, 45, ed.ListOfMetaData[game.playcustomlevel].title, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 70, "by " + ed.ListOfMetaData[game.playcustomlevel].creator, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 80, ed.ListOfMetaData[game.playcustomlevel].website, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 100, ed.ListOfMetaData[game.playcustomlevel].Desc1, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 110, ed.ListOfMetaData[game.playcustomlevel].Desc2, 196, 196, 255 - help.glow, true);
              dwgfx.Print( -1, 120, ed.ListOfMetaData[game.playcustomlevel].Desc3, 196, 196, 255 - help.glow, true);

              if(map.customcrewmates-game.crewmates==1){
                dwgfx.Print(1,165, help.number(int(map.customcrewmates-game.crewmates))+ " にんのなかまがのこっている", 196, 196, 255 - help.glow, true);
              }else if(map.customcrewmates-game.crewmates>0){
                dwgfx.Print(1,165, help.number(int(map.customcrewmates-game.crewmates))+ " にんのなかまがのこっている", 196, 196, 255 - help.glow, true);
              }
            }
        }
        else
        {
            dwgfx.Print(30, 220, "マップ", 64,64,64);
            dwgfx.Print(103-8, 220, "[なかま]", 196, 196, 255 - help.glow);
            dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
            dwgfx.Print(258, 220, "セーブ", 64, 64, 64);

            if (dwgfx.flipmode)
            {
                for (int i = 0; i < 3; i++)
                {
                    dwgfx.drawcrewman(16, 32 + (i * 64), 2-i, game.crewstats[2-i], help);
                    if (game.crewstats[(2-i)])
                    {
                        dwgfx.printcrewname(44, 32 + (i * 64)+4+10, 2-i);
                        dwgfx.printcrewnamestatus(44, 32 + (i * 64)+4, 2-i);
                    }
                    else
                    {
                        dwgfx.printcrewnamedark(44, 32 + (i * 64)+4+10, 2-i);
                        dwgfx.Print(44, 32 + (i * 64) + 4, "ふめい...", 64,64,64);
                    }

                    dwgfx.drawcrewman(16+160, 32 + (i * 64), (2-i)+3, game.crewstats[(2-i)+3], help);
                    if (game.crewstats[(2-i)+3])
                    {
                        dwgfx.printcrewname(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                        dwgfx.printcrewnamestatus(44+160, 32 + (i * 64)+4, (2-i)+3);
                    }
                    else
                    {
                        dwgfx.printcrewnamedark(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                        dwgfx.Print(44+160, 32 + (i * 64) + 4, "ふめい...", 64,64,64);
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    dwgfx.drawcrewman(16, 32 + (i * 64), i, game.crewstats[i], help);
                    if (game.crewstats[i])
                    {
                        dwgfx.printcrewname(44, 32 + (i * 64)+4, i);
                        dwgfx.printcrewnamestatus(44, 32 + (i * 64)+4+10, i);
                    }
                    else
                    {
                        dwgfx.printcrewnamedark(44, 32 + (i * 64)+4, i);
                        dwgfx.Print(44, 32 + (i * 64) + 4 + 10, "ふめい...", 64,64,64);
                    }

                    dwgfx.drawcrewman(16+160, 32 + (i * 64), i+3, game.crewstats[i+3], help);
                    if (game.crewstats[i+3])
                    {
                        dwgfx.printcrewname(44+160, 32 + (i * 64)+4, i+3);
                        dwgfx.printcrewnamestatus(44+160, 32 + (i * 64)+4+10, i+3);
                    }
                    else
                    {
                        dwgfx.printcrewnamedark(44+160, 32 + (i * 64)+4, i+3);
                        dwgfx.Print(44+160, 32 + (i * 64) + 4 + 10, "ふめい...", 64,64,64);
                    }
                }
            }
        }
        break;
    case 2:
        dwgfx.Print(30, 220, "マップ", 64,64,64);
        if (game.insecretlab)
        {
            dwgfx.Print(103, 220, "グラビトロン", 64, 64, 64);
        }
        else if (obj.flags[67] == 1 && !map.custommode)
        {
            dwgfx.Print(103, 220, "うちゅうせん", 64,64,64);
        }
        else
        {
            dwgfx.Print(103, 220, "なかま", 64,64,64);
        }
        dwgfx.Print(185-12, 220, "[ステータス]", 196, 196, 255 - help.glow);
        dwgfx.Print(258, 220, "セーブ", 64, 64, 64);

        if(map.custommode){
          if (dwgfx.flipmode)
          {
              dwgfx.Print(0, 164, "[あつめたトリンケット]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 152, help.number(map.customtrinkets) + "こ ちゅうの " + help.number(game.trinkets) + "こ", 96,96,96, true);

              dwgfx.Print(0, 114, "[しんだかいすう]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 102,help.String(game.deathcounts),  96,96,96, true);

              dwgfx.Print(0, 64, "[かかったじかん]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 52, game.timestring(help),  96, 96, 96, true);
          }
          else
          {
              dwgfx.Print(0, 52, "[あつめたトリンケット]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 64, help.number(map.customtrinkets) + "こ ちゅうの " + help.number(game.trinkets) + "こ", 96,96,96, true);

              dwgfx.Print(0, 102, "[しんだかいすう]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 114,help.String(game.deathcounts),  96,96,96, true);

              dwgfx.Print(0, 152, "[かかったじかん]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 164, game.timestring(help),  96, 96, 96, true);
          }
        }else{
          if (dwgfx.flipmode)
          {
              dwgfx.Print(0, 164, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 152, help.number(game.trinkets) + " out of Twenty", 96,96,96, true);

              dwgfx.Print(0, 114, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 102,help.String(game.deathcounts),  96,96,96, true);

              dwgfx.Print(0, 64, "[Time Taken]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 52, game.timestring(help),  96, 96, 96, true);
          }
          else
          {
              dwgfx.Print(0, 52, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 64, help.number(game.trinkets) + " out of Twenty", 96,96,96, true);

              dwgfx.Print(0, 102, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 114,help.String(game.deathcounts),  96,96,96, true);

              dwgfx.Print(0, 152, "[Time Taken]", 196, 196, 255 - help.glow, true);
              dwgfx.Print(0, 164, game.timestring(help),  96, 96, 96, true);
          }
        }
        break;
    case 3:
        dwgfx.Print(30, 220, "マップ", 64,64,64);
        if (game.insecretlab)
        {
            dwgfx.Print(103, 220, "グラビトロン", 64, 64, 64);
        }
        else if (obj.flags[67] == 1 && !map.custommode)
        {
            dwgfx.Print(103, 220, "うちゅうせん", 64,64,64);
        }
        else
        {
            dwgfx.Print(103, 220, "なかま", 64,64,64);
        }
        dwgfx.Print(185-4, 220, "ステータス", 64,64,64);
        dwgfx.Print(258 - 8, 220, "[セーブ]", 196, 196, 255 - help.glow);

        if (game.inintermission)
        {
            dwgfx.Print(0, 115, "Cannot Save in Level Replay", 146, 146, 180, true);
        }
        else if (game.nodeathmode)
        {
            dwgfx.Print(0, 115, "Cannot Save in No Death Mode", 146, 146, 180, true);
        }
        else if (game.intimetrial)
        {
            dwgfx.Print(0, 115, "Cannot Save in Time Trial", 146, 146, 180, true);
        }
        else if (game.insecretlab)
        {
            dwgfx.Print(0, 115, "Cannot Save in Secret Lab", 146, 146, 180, true);
        }
        else if (map.custommode)
        {
          if (game.gamesaved)
            {
                dwgfx.Print(0, 36, "ゲームをほぞんしました!", 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2), true);

                dwgfx.drawpixeltextbox(25, 65, 270, 90, 34,12, 65, 185, 207,0,4);

                if (dwgfx.flipmode)
                {
                    dwgfx.Print(0, 122, game.customleveltitle, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    dwgfx.Print(160 - 84, 78, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    dwgfx.Print(160 + 40, 78, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    dwgfx.drawspritesetcol(50, 74, 50, 18, help);
                    dwgfx.drawspritesetcol(175, 74, 22, 18, help);
                }
                else
                {
                    dwgfx.Print(0, 90, game.customleveltitle, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    dwgfx.Print(160 - 84, 132, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    dwgfx.Print(160 + 40, 132, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    dwgfx.drawspritesetcol(50, 126, 50, 18, help);
                    dwgfx.drawspritesetcol(175, 126, 22, 18, help);
                }
            }
            else
            {
                dwgfx.Print(0, 80, "[ACTION でゲームをほぞん]", 255 - (help.glow * 2), 255 - (help.glow * 2), 255 - help.glow, true);
            }
        }
        else
        {
            if (dwgfx.flipmode)
            {
                dwgfx.Print(0, 186, "(Note: The game is autosaved", 146, 146, 180, true);
                dwgfx.Print(0, 174, "at every teleporter.)", 146, 146, 180, true);
            }
            else
            {
                dwgfx.Print(0, 174, "(Note: The game is autosaved", 146, 146, 180, true);
                dwgfx.Print(0, 186, "at every teleporter.)", 146, 146, 180, true);
            }

            if (game.gamesaved)
            {
                dwgfx.Print(0, 36, "Game saved ok!", 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2), true);

                dwgfx.drawpixeltextbox(25, 65, 270, 90, 34,12, 65, 185, 207,0,4);

                if (dwgfx.flipmode)
                {
                    dwgfx.Print(0, 132, game.savearea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    for (int i = 0; i < 6; i++)
                    {
                        dwgfx.drawcrewman(169-(3*42)+(i*42), 98, i, game.crewstats[i], help, true);
                    }
                    dwgfx.Print(160 - 84, 78, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    dwgfx.Print(160 + 40, 78, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    dwgfx.drawspritesetcol(50, 74, 50, 18, help);
                    dwgfx.drawspritesetcol(175, 74, 22, 18, help);
                }
                else
                {
                    dwgfx.Print(0, 80, game.savearea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    for (int i = 0; i < 6; i++)
                    {
                        dwgfx.drawcrewman(169-(3*42)+(i*42), 95, i, game.crewstats[i], help, true);
                    }
                    dwgfx.Print(160 - 84, 132, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    dwgfx.Print(160 + 40, 132, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    dwgfx.drawspritesetcol(50, 126, 50, 18, help);
                    dwgfx.drawspritesetcol(175, 126, 22, 18, help);
                }
            }
            else
            {
                dwgfx.Print(0, 80, "[Press ACTION to save your game]", 255 - (help.glow * 2), 255 - (help.glow * 2), 255 - help.glow, true);

                if (game.quicksummary != "")
                {
                    if (dwgfx.flipmode)
                    {
                        dwgfx.Print(0, 110, "Last Save:", 164 - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                        dwgfx.Print(0, 100, game.quicksummary, 164  - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                    }
                    else
                    {
                        dwgfx.Print(0, 100, "Last Save:", 164 - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                        dwgfx.Print(0, 110, game.quicksummary, 164  - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                    }
                }
            }
        }
        break;
    case 10:
        dwgfx.Print(128, 220, "[ QUIT ]", 196, 196, 255 - help.glow);

        if (dwgfx.flipmode)
        {
            if (game.intimetrial || game.insecretlab || game.nodeathmode || game.menukludge)
            {
                dwgfx.Print(0, 135, "メインメニューへもどりますか?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                dwgfx.Print(0, 142, "メインメニューへもどりますか? セーブして", 196, 196, 255 - help.glow, true);
                dwgfx.Print(0, 130, "いないないようはきえてしまいます。", 196, 196, 255 - help.glow, true);
            }

            dwgfx.Print(80-16, 88, "[ まだあそぶ ]", 196, 196, 255 - help.glow);
            dwgfx.Print(80 + 32, 76, "メニューへもどる",  96, 96, 96);
        }
        else
        {

            if (game.intimetrial || game.insecretlab || game.nodeathmode || game.menukludge)
            {
                dwgfx.Print(0, 80, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                dwgfx.Print(0, 76, "メインメニューへもどりますか? セーブして", 196, 196, 255 - help.glow, true);
                dwgfx.Print(0, 88, "いないないようはきえてしまいます。", 196, 196, 255 - help.glow, true);
            }

            dwgfx.Print(80-16, 130, "[ まだあそぶ ]", 196, 196, 255 - help.glow);
            dwgfx.Print(80 + 32, 142, "メニューへもどる",  96, 96, 96);

        }
        break;
    case 11:
        dwgfx.Print(128, 220, "[ QUIT ]", 196, 196, 255 - help.glow);

        if (dwgfx.flipmode)
        {
            if (game.intimetrial || game.insecretlab || game.nodeathmode || game.menukludge)
            {
                dwgfx.Print(0, 135, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                dwgfx.Print(0, 142, "メインメニューへもどりますか? セーブして", 196, 196, 255 - help.glow, true);
                dwgfx.Print(0, 130, "いないないようはきえてしまいます。", 196, 196, 255 - help.glow, true);
            }

            dwgfx.Print(80, 88, "まだあそぶ", 96,96,96);
            dwgfx.Print(80+32-16, 76, "[ メニューへもどる ]",  196, 196, 255 - help.glow);
        }
        else
        {
            if (game.intimetrial || game.insecretlab || game.nodeathmode || game.menukludge)
            {
                dwgfx.Print(0, 80, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                dwgfx.Print(0, 76, "メインメニューへもどりますか? セーブして", 196, 196, 255 - help.glow, true);
                dwgfx.Print(0, 88, "いないないようはきえてしまいます。", 196, 196, 255 - help.glow, true);
            }

            dwgfx.Print(80, 130, "まだあそぶ", 96,96,96);
            dwgfx.Print(80+32-16, 142, "[ メニューへもどる ]", 196, 196, 255 - help.glow);
        }
        break;
    case 20:
        dwgfx.Print(128, 220, "[ GRAVITRON ]", 196, 196, 255 - help.glow, true);

        if (dwgfx.flipmode)
        {
            dwgfx.Print(0, 76, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            dwgfx.Print(0, 88, "Do you want to return to", 196, 196, 255 - help.glow, true);
            dwgfx.Print(80-16, 142, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            dwgfx.Print(80 + 32, 130, "yes, return",  96, 96, 96);
        }
        else
        {
            dwgfx.Print(0, 76, "Do you want to return to", 196, 196, 255 - help.glow, true);
            dwgfx.Print(0, 88, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            dwgfx.Print(80-16, 130, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            dwgfx.Print(80 + 32, 142, "yes, return",  96, 96, 96);
        }

        break;
    case 21:
        dwgfx.Print(128, 220, "[ GRAVITRON ]", 196, 196, 255 - help.glow, true);

        if (dwgfx.flipmode)
        {
            dwgfx.Print(0, 76, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            dwgfx.Print(0, 88, "Do you want to return to", 196, 196, 255 - help.glow, true);
            dwgfx.Print(80, 142, "no, keep playing", 96, 96, 96);
            dwgfx.Print(80 + 32-16, 130, "[ YES, RETURN ]",  196, 196, 255 - help.glow);
        }
        else
        {
            dwgfx.Print(0, 76, "Do you want to return to", 196, 196, 255 - help.glow, true);
            dwgfx.Print(0, 88, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            dwgfx.Print(80, 130, "no, keep playing", 96, 96, 96);
            dwgfx.Print(80 + 32-16, 142, "[ YES, RETURN ]",  196, 196, 255 - help.glow);
        }

    }




    dwgfx.drawfade();

    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (dwgfx.resumegamemode)
    {
        dwgfx.menuoffset += 25;
        if (map.extrarow)
        {
            if (dwgfx.menuoffset >= 230)
            {
                dwgfx.menuoffset = 230;
                //go back to gamemode!
                game.mapheld = true;
                game.gamestate = GAMEMODE;
            }
        }
        else
        {
            if (dwgfx.menuoffset >= 240)
            {
                dwgfx.menuoffset = 240;
                //go back to gamemode!
                game.mapheld = true;
                game.gamestate = GAMEMODE;
            }
        }
        dwgfx.menuoffrender();
    }
    else if (dwgfx.menuoffset > 0)
    {
        dwgfx.menuoffset -= 25;
        if (dwgfx.menuoffset < 0) dwgfx.menuoffset = 0;
        dwgfx.menuoffrender();
    }
    else
    {
        if (game.screenshake > 0 && !game.noflashingmode)
        {
            game.screenshake--;
            dwgfx.screenshake();
        }
        else
        {
            dwgfx.render();
        }
    }

    //dwgfx.backbuffer.unlock();
}

void towerrender(Graphics& dwgfx, Game& game, mapclass& map, entityclass& obj, UtilityClass& help)
{

    FillRect(dwgfx.backBuffer, 0x000000);

    if (!game.colourblindmode)
    {
        dwgfx.drawtowerbackground(map);
        dwgfx.drawtowermap(map);
    }
    else
    {
        dwgfx.drawtowermap_nobackground(map);
    }

    if(!game.completestop)
    {
        for (int i = 0; i < obj.nentity; i++)
        {
            //Is this entity on the ground? (needed for jumping)
            if (obj.entitycollidefloor(map, i))
            {
                obj.entities[i].onground = 2;
            }
            else
            {
                obj.entities[i].onground--;
            }

            if (obj.entitycollideroof(map, i))
            {
                obj.entities[i].onroof = 2;
            }
            else
            {
                obj.entities[i].onroof--;
            }

            //Animate the entities
            obj.animateentities(i, game, help);
        }
    }

    dwgfx.drawtowerentities(map, obj, help);

    dwgfx.drawtowerspikes(map);


    /*for(int i=0; i<obj.nblocks; i++){
    if (obj.blocks[i].active) {
    		dwgfx.backbuffer.fillRect(obj.blocks[i].rect, 0xDDDDDD);
    }
      }*/
    dwgfx.cutscenebars();

    dwgfx.drawgui(help);
    if (dwgfx.flipmode)
    {
        if (game.advancetext) dwgfx.bprint(5, 228, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }
    else
    {
        if (game.advancetext) dwgfx.bprint(5, 5, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }


    FillRect(dwgfx.backBuffer, dwgfx.footerrect, 0x000000);
    dwgfx.Print(5, 231, map.roomname, 196, 196, 255 - help.glow, true);

    //dwgfx.rprint(5, 231,help.String(game.coins), 255 - help.glow/2, 255 - help.glow/2, 196, true);
    //dwgfx.drawhuetile(311, 230, 48, 1);

    if (game.intimetrial && dwgfx.fademode==0)
    {
        //Draw countdown!
        if (game.timetrialcountdown > 0)
        {
            if (game.timetrialcountdown < 30)
            {
                game.resetgameclock();
                if (int(game.timetrialcountdown / 4) % 2 == 0) dwgfx.bigprint( -1, 100, "Go!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 60)
            {
                dwgfx.bigprint( -1, 100, "1", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 90)
            {
                dwgfx.bigprint( -1, 100, "2", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 120)
            {
                dwgfx.bigprint( -1, 100, "3", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
        }
        else
        {
            //Draw OSD stuff
            dwgfx.bprint(6, 18, "TIME :",  255,255,255);
            dwgfx.bprint(6, 30, "DEATH:",  255, 255, 255);
            dwgfx.bprint(6, 42, "SHINY:",  255,255,255);

            if(game.timetrialparlost)
            {
                dwgfx.bprint(56, 18, game.timestring(help),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 18, game.timestring(help),  196, 196, 196);
            }
            if(game.deathcounts>0)
            {
                dwgfx.bprint(56, 30,help.String(game.deathcounts),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 30,help.String(game.deathcounts),  196, 196, 196);
            }
            if(game.trinkets<game.timetrialshinytarget)
            {
                dwgfx.bprint(56, 42,help.String(game.trinkets) + " of " +help.String(game.timetrialshinytarget),  196, 80, 80);
            }
            else
            {
                dwgfx.bprint(56, 42,help.String(game.trinkets) + " of " +help.String(game.timetrialshinytarget),  196, 196, 196);
            }

            if(game.timetrialparlost)
            {
                dwgfx.bprint(195, 214, "PAR TIME:",  80, 80, 80);
                dwgfx.bprint(275, 214, game.partimestring(help),  80, 80, 80);
            }
            else
            {
                dwgfx.bprint(195, 214, "PAR TIME:",  255, 255, 255);
                dwgfx.bprint(275, 214, game.partimestring(help),  196, 196, 196);
            }
        }
    }

    dwgfx.drawfade();

    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    dwgfx.render();
}

void teleporterrender(Graphics& dwgfx, Game& game, mapclass& map, entityclass& obj, UtilityClass& help)
{
    //dwgfx.backbuffer.lock();
    int tempx;
    int tempy;
    //draw screen alliteration
    //Roomname:
    temp = map.area(game.roomx, game.roomy);
    if (temp < 2 && !map.custommode && dwgfx.fademode==0)
    {
        if (game.roomx >= 102 && game.roomx <= 104 && game.roomy >= 110 && game.roomy <= 111)
        {
            dwgfx.Print(5, 2, "The Ship", 196, 196, 255 - help.glow, true);
        }
        else
        {
            dwgfx.Print(5, 2, "Dimension VVVVVV", 196, 196, 255 - help.glow, true);
        }
    }
    else
    {
        dwgfx.Print(5, 2, map.roomname, 196, 196, 255 - help.glow, true);
    }

    //Background color
    FillRect(dwgfx.backBuffer, 0, 12, 320, 240, 10, 24, 26);

    //draw the map image
    dwgfx.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
    if (map.custommode) {
        dwgfx.drawimage(12, 40, 21, false);
    } else {
        dwgfx.drawimage(1, 40, 21, false);
    }
    //black out areas we can't see yet
    if (!map.custommode) {
        for (int j = 0; j < 20; j++)
        {
            for (int i = 0; i < 20; i++)
            {
                if(map.explored[i+(j*20)]==0)
                {
                    //dwgfx.drawfillrect(10 + (i * 12), 21 + (j * 9), 12, 9, 16, 16, 16);
                    dwgfx.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
                }
            }
        }
    } else if (!map.nofog) {
        if (map.customzoom==4) {
            for (int j = 0; j < map.customheight; j++){
            for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                //Draw the fog of war on the map
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36), false);

                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+ 21 + 9 + (j * 36), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36), false);

                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36)+18, false);

                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + 9 + (j * 36)+18, false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36)+18, false);
                }
            }
            }
        }else if(map.customzoom==2){
            for (int j = 0; j < map.customheight; j++){
            for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                //Draw the fog of war on the map
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + 9 + (j * 18), false);
                dwgfx.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + 9+ (j * 18), false);
                }
            }
            }
        }else{
            for (int j = 0; j < map.customheight; j++){
            for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                //Draw the fog of war on the map
                dwgfx.drawimage(2, map.custommmxoff+40 + (i * 12), map.custommmyoff+21 + (j * 9), false);
                }
            }
            }
        }
    }

    //draw the coordinates //current
    if (game.roomx == 109)
    {
        //tower!instead of room y, scale map.ypos
        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21  + 2, 12 - 4, 180 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
    }
    else
    {
        dwgfx.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
    }

    if (game.useteleporter)
    {
        //Draw the chosen destination coordinate!
		//TODO
        //draw the coordinates //destination
        int tempx = map.teleporters[game.teleport_to_teleporter].x;
        int tempy = map.teleporters[game.teleport_to_teleporter].y;
        dwgfx.drawrect(40 + (tempx * 12) + 1, 21 + (tempy * 9) + 1, 12 - 2, 9 - 2, 245 - (help.glow * 2), 16, 16);
        dwgfx.drawrect(40 + (tempx * 12) + 3, 21 + (tempy * 9) + 3, 12 - 6, 9 - 6, 245 - (help.glow * 2), 16, 16);
    }

    //draw legend details
    for (int i = 0; i < map.numteleporters; i++)
    {
        if (map.showteleporters && map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)] > 0)
        {
            temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
            if (dwgfx.flipmode) temp += 3;
            dwgfx.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
        }
        else if(map.showtargets && map.explored[map.teleporters[i].x+(20*map.teleporters[i].y)]==0)
        {
            temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
            if (dwgfx.flipmode) temp += 3;
            dwgfx.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
        }
        //dwgfx.drawtile(40+3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), 1086); //for shiny trinkets, do later
    }

    if (map.showtrinkets)
    {
        for (int i = 0; i < map.numshinytrinkets; i++)
        {
            if (obj.collect[i] == 0)
            {
                temp = 1086;
                if (dwgfx.flipmode) temp += 3;
                dwgfx.drawtile(40 + 3 + (map.shinytrinkets[i].x * 12), 22 + (map.shinytrinkets[i].y * 9),	temp);
            }
        }
    }

	tempx = map.teleporters[game.teleport_to_teleporter].x;
	tempy = map.teleporters[game.teleport_to_teleporter].y;
    if (game.useteleporter && ((help.slowsine%16)>8))
    {
        //colour in the legend
        temp = 1128;
        if (dwgfx.flipmode) temp += 3;
        dwgfx.drawtile(40 + 3 + (tempx * 12), 22 + (tempy * 9), temp);
    }

    dwgfx.cutscenebars();


    if (game.useteleporter)
    {
        //Instructions!
        dwgfx.Print(5, 210, "Press Left/Right to choose a Teleporter", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
        dwgfx.Print(5, 225, "Press ENTER to Teleport", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }

    dwgfx.drawgui(help);

    if (dwgfx.flipmode)
    {
        if (game.advancetext) dwgfx.bprint(5, 228, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }
    else
    {
        if (game.advancetext) dwgfx.bprint(5, 5, "- ACTION をおしてつぎへすすむ -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }


    if (game.test)
    {
        dwgfx.Print(5, 5, game.teststring, 196, 196, 255, false);
    }

    if (game.flashlight > 0 && !game.noflashingmode)
    {
        game.flashlight--;
        dwgfx.flashlight();
    }

    if (dwgfx.resumegamemode)
    {
        dwgfx.menuoffset += 25;
        if (map.extrarow)
        {
            if (dwgfx.menuoffset >= 230)
            {
                dwgfx.menuoffset = 230;
                //go back to gamemode!
                game.mapheld = true;
                game.gamestate = GAMEMODE;
            }
        }
        else
        {
            if (dwgfx.menuoffset >= 240)
            {
                dwgfx.menuoffset = 240;
                //go back to gamemode!
                game.mapheld = true;
                game.gamestate = GAMEMODE;
            }
        }
        dwgfx.menuoffrender();
    }
    else if (dwgfx.menuoffset > 0)
    {
        dwgfx.menuoffset -= 25;
        if (dwgfx.menuoffset < 0) dwgfx.menuoffset = 0;
        dwgfx.menuoffrender();
    }
    else
    {
        if (game.screenshake > 0 && !game.noflashingmode)
        {
            game.screenshake--;
            dwgfx.screenshake();
        }
        else
        {
            dwgfx.render();
        }
    }

    //dwgfx.backbuffer.unlock();
}
