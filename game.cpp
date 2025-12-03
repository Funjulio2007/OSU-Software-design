#include <FEHLCD.h>
#include <FEHUtility.h>
#include <LCDColors.h>
#include <FEHKeyboard.h>
#include <stdio.h>
#include <FEHSound.h>
#include <FEHImages.h>
#define move_increment  10
//Protypes 
void mainmenu();
void tutorial();
void start();
void STATS ();
void updatestats (int*, int*, float*, char[4]); // (Points, waves, time player, player name)
void updateplayer (int*, int*, int); //update player positions according to keyboard, accepts x position, y position, and buttonpressed as integers
void credits ();
void enablekeyboard();
void tutorial_refresh (float, float);
void background_refresh (float, float);
// These are the gobal variables. Define them here so they can be used throught the code

//Function calls occur here and gameplay
int main(){
    float x_position,y_position;
    float *xptr, *yptr; // put pointer 
    int quit = 0, valid=0;
    xptr = &x_position;
    yptr = &y_position;
// declare an array of four icons called menu
   // make the menu pop up


   // making background music
    FEHSound background1("f72c-7f1e-4181-9c08-2d055d6eaad6-FORGAME.wav");
   background1.play(); // lets figure out how to keep it looping
   
  


    
   mainmenu();
   
   /*Wait for click
   If a click happens
   Track click location
   If click location is within a button, perform that button's function*/
while(valid==0)
{
  LCD.Touch (xptr, yptr);
  printf ("\nThe x-coordinate is %f \n The y-coordinate is %f\n", x_position, y_position);

/*Wait for Touch*/
while (!LCD.Touch (xptr, yptr));
{
   
}


    if ( x_position > 160.00 && x_position <314.00 && y_position > 12.00 && y_position < 120.00) // this is for the tutorial
     {
        printf ("Tutorial coordinates found, playing tutorial");
        background1.restart();
        tutorial();
         
        valid = 1;
    }
    
    
    if ( x_position<160 && x_position>5 && y_position >121 && y_position < 230  ) // credits 
    {
        // this is for credit function 
        background1.restart();
        credits();
         
    }
    if ( x_position <160 && x_position >5 && y_position <120 && y_position > 12 )//start
    {
        // This is for the start function
        background1.restart(); // would probably change this sound to something more action packed 
        start();
         
    }
    if ( x_position < 314 && x_position >160 && y_position <230 && y_position > 121)
    {
        // this is the quit function
        background1.restart();  
        STATS ();
        
    }

    
else
{
 valid=0;
} //end else statement

} //end invalid click loop
 /*Write code for a return to menu button here, ideally after the game ove*/
//while (quit == 1); //end of do while loop to return in menu
    while (1) {
        LCD.Update();    
    }
    return(1);

}

void credits()
{
    int quit =0;
    LCD.Clear();
    LCD.SetBackgroundColor (BLUE);
    LCD.SetFontColor (WHITE);
    LCD.SetFontScale(.5);
    LCD.WriteLine ("This game was made by \nChadwick Lucas and Lucas Clavijo\nThank you For Playing!");
    // I want to some how put some music in
    LCD.SetFontScale(.5);
    LCD.WriteLine("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nReturn to menu,hit escape");
    LCD.SetFontScale(1);

LCD.Update();
     Keyboard.waitSpecificKey(KEY_ESCAPE); //wait for excape button to be pressed
        LCD.Clear(BLACK);
mainmenu();
    
}


// This is the function to make the menu appear 
void mainmenu()
{
  // declare an array of four icons called menu
  LCD.Clear (BLACK);
    FEHIcon::Icon menu[4];

    // define the four menu labels
    char menu_labels[4][20] = {"START GAME","TUTORIAL","CREDITS","STATS"};

    // draw the menu in a 2 by 2 array with top and bottom
    // margins of 10 and left and right margins of 5
    // with the menu labels, gold borders, and green text
    FEHIcon::DrawIconArray(menu, 2, 2, 10, 10, 5, 5, menu_labels, SCARLET, GRAY);
    FEHImage lanternfly ("spotted_lanternfly.png"); // these images are best as 30X30
    lanternfly.Draw (100,100);

    // make button a quit stats button
    LCD.SetFontColor(GREEN);
    LCD.DrawRectangle(284,200,30,30);
   LCD.Update();
   
}


//refreshes the screen in the tutorial after a movement or projectile happens
void tutorial_refresh(float x, float y)
{
    FEHImage rocket ("Rocketship.png");
    LCD.SetFontScale (1);
LCD.SetBackgroundColor (SCARLET);
LCD.Clear();
LCD.SetFontColor (WHITE);
LCD.DrawRectangle (100, 135, 125, 100);
LCD.WriteAt ("How To Play:", 100, 25);
LCD.WriteAt ("Use the arrow keys to move", 5, 50);
LCD.WriteAt ("Use space to shoot", 5, 75);
LCD.WriteAt ("Don't get hit!", 5, 100); //this will generate the tutorial
LCD.SetFontScale (0.5);
LCD.WriteLine ("Press escape to exit                                                            ");
LCD.SetFontScale (1);



        rocket.Draw (x, y); //generate rectangle with the coordinates passed onto it by the tutorial function

LCD.Update();
}



//runs the tutorial section of the menu
void tutorial ()
{
    int quit;
    float x_position, y_position, *xptr, *yptr;
    x_position = 150;
    y_position = 175;
    xptr = &x_position;
    yptr = &y_position; //declare position variables and the quit variable for the loop


tutorial_refresh(x_position, y_position); //write the background


        LCD.FillRectangle (x_position, y_position, 20, 20); //generate first rectangle
// go back to menu button using the escape
LCD.Update();
quit = 0;
while (quit == 0)
{
    if (Keyboard.isPressed (KEY_ESCAPE))
    {
        quit = 1; //quit if escape is pressed
    }
    else if (Keyboard.isPressed (KEY_RIGHT) && x_position !=200.00) //checks if right key is being pressed
    {
        
        x_position = x_position + 5; //increment x position
 
    }
    else if (Keyboard.isPressed (KEY_LEFT) && x_position !=105) //checks if left key is being pressed
    {
        
        x_position = x_position - 5; //increment x position

    }
    else if (Keyboard.isPressed (KEY_UP) && y_position != 140) //checks if up key is being pressed
    {
        
        y_position = y_position - 5; //increment y position
       
    }
else if (Keyboard.isPressed (KEY_DOWN) && y_position != 210)
    {

        y_position = y_position + 5; //increment x position
       
    }
    else if (Keyboard.isPressed (KEY_SPACE))
    {
        LCD.SetFontColor (GREEN);
        LCD.DrawLine (x_position + 26, y_position, x_position + 26, 0);
        LCD.DrawLine (x_position +23, y_position, x_position+23, 0);
        LCD.Update();
        Sleep (0.1);
    }
    tutorial_refresh (x_position, y_position);
    LCD.Update();
    Sleep (20); //slow down the loop
     }
mainmenu();
}

void background_refresh (float x, float y)

{
    
FEHImage streetbackground;
streetbackground.Open("Streetbackgroundv1.png");
streetbackground.Draw(0,0);
FEHImage rocket;
rocket.Open("Rocketship.png");
rocket.Draw(x,y);
LCD.Update();

}


// THis is for the game its self 
    void start () // this is in its sample mode. Need to add stuff 
{
    int quit;
    
    float rocketx, rockety,lanterflyx,lanterflyy;
    // This background will be worked on
background_refresh (rocketx, rockety);
    quit = 0;
while (quit == 0)
{
    if (Keyboard.isPressed (KEY_ESCAPE))
    {
        quit = 1; //quit if escape is pressed
    }
    else if (Keyboard.isPressed (KEY_RIGHT) && rocketx < 300.00) //checks if right key is being pressed
    {
        
        rocketx = rocketx + move_increment; //increment x position
 
    }
    else if (Keyboard.isPressed (KEY_LEFT) && rocketx > 20) //checks if left key is being pressed
    {
        
        rocketx = rocketx - move_increment; //increment x position

    }
    else if (Keyboard.isPressed (KEY_UP) && rockety > 140) //checks if up key is being pressed
    {
        
        rockety = rockety - move_increment; //increment y position
       
    }
else if (Keyboard.isPressed (KEY_DOWN) && rockety < 220)
    {

        rockety = rockety + move_increment; //increment x position
       
    }
    else if (Keyboard.isPressed (KEY_SPACE))
    {
        LCD.SetFontColor (GREEN);
        LCD.DrawLine (rocketx + 26, rockety, rocketx + 26, 0);
        LCD.DrawLine (rocketx + 23, rockety, rocketx + 23, 0);
        LCD.Update();
        Sleep (0.1);
    }

    background_refresh (rocketx, rockety);
    //enemy refresh
    LCD.Update();
    Sleep (20); //slow down the loop
     }

     // I want to figure out hoow to get the enemies to move down the screen
mainmenu();
    
}

void STATS () // would need to make an exit game 
{
    int quit;
LCD.Clear ();
LCD.SetBackgroundColor (BLUE);
LCD.SetFontColor (WHITE);
LCD.WriteLine ("Sample of STATs game  ");
LCD.Update();
// escape 
LCD.Update();
     Keyboard.waitSpecificKey(KEY_ESCAPE); //wait for excape button to be pressed
        LCD.Clear(BLACK);
mainmenu();
    
    

}
// This is the code for makeing clicking happen

// code for using the keyboard//

