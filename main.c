 #include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 700

#define WINDOW_HEIGHT 900
#define FPS 60
int rb;  //rayon ball            
int xb;   //xball
int yb;   //yball              
int x;  //x du barre
int y;  //y du barre
int longueur;
int hauteur;
int xr; //xbrick 
int yr; //ybrick
int lr;
int hr;
int vitesseBallx;
int vitesseBally;
int Tabmax ;
int Tab[18];
int viebrick[18]; 
int positionx;
int positiony;
int espace;
int nbbrick;
int nbcolone;
int vie ;
int largbare;
int goo;
int espcitroullie;

void barredevie(){
    changeColor(0,0,0);
    drawRect(0, (WINDOW_HEIGHT-largbare), WINDOW_WIDTH, largbare);
    for (int i=0; i<vie; i++){
        changeColor(0, 0, 0);
        sprite((espcitroullie*i),(WINDOW_HEIGHT-(largbare)) , "/home/fares25/Downloads/Design-sans-titre.bmp");
    }
  
    }
void drawBall(){
   changeColor(220,152,0);
   drawCircle(xb,yb,rb);
   xb+=vitesseBallx; //j'ai liere la vitesse avec la position ;
   yb+=vitesseBally;
   if((xb>(WINDOW_WIDTH-rb) ||(xb<rb)) ){
     vitesseBallx=-vitesseBallx;
   }

    if ((yb>(WINDOW_HEIGHT-rb)|| (yb<rb)) || (((xb+rb>=x) && (xb-rb<x+longueur)) && yb>y-rb)){
      vitesseBally=-vitesseBally;       
   }
     
   if (yb +rb> WINDOW_HEIGHT -largbare) {
        vie--; 
        if (vie > 0) {
         xb = WINDOW_WIDTH / 2;
         yb = WINDOW_HEIGHT / 2;
         vitesseBallx = 0;
         vitesseBally = 0;
        }
  }
}
void drawBarr(){
   changeColor(255,75,0); 
   drawRect(x, y,longueur, hauteur);
   
}

  


void init_game(){
   // mettre votre code d'initialisation ici
   xb =WINDOW_WIDTH/2;//position x de la balle 
   yb =WINDOW_HEIGHT/2;//position y de la balle 
   rb =20; // rayon de la bale 
   vitesseBallx =0; //vitesse de la balle en x 
   vitesseBally = 0; //vitesse de la balle de en y 
   x=WINDOW_WIDTH/2;
   y=WINDOW_WIDTH+90;
   longueur=200; //longeure de la barre
   hauteur=5; //hauteur de la barre 
   Tabmax =18; //initialisation de on tableau de brick 
   nbcolone=6; //nobre de colone que j'ai dans mon tabelau  
   viebrick[18]; 
   lr=80;//largeure de brick
   hr=40;//hauteure de brick 
   positionx=35;
   positiony=40;
   espace=110; //c'est mes espaces entre les brick 
   nbbrick=18; // c'est le nombre de brick que j'ai 
   vie= 5; //c'est le nobre d'essaye que j'ai 
   largbare=70;//c'est ma largeure de barre 
   goo=1;
   espcitroullie=80;//mon espace de citroullie
   for(int i=0;i<Tabmax;i++){
     viebrick[i]=1;
     }
 } 
  
  
       
     
 void drawbrick(){
 
   for( int j=0;j<nbcolone;j++){
     changeColor(232,84,9);
     for(int i=j;i<Tabmax;i=i+nbcolone){
       if(viebrick[i]==1){
         xr=(positionx+(j*espace)); 
         yr=positiony+(i)/nbcolone*(lr); 
         drawRect( xr, yr, lr, hr);
         if ((xb + rb >= xr && xb - rb <= xr + lr) && (yb + rb >= yr && yb - rb <= yr + hr)) {
            nbbrick--;
            viebrick[i]=0;
            vitesseBally=-vitesseBally;  
         }
       }
    }
  }  
} 

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
     if(goo==1){
      clear();
      sprite(0, 0,"/home/fares25/Downloads/casse-brick.bmp");
         
      }else if(vie>0){
  
        clear();
        sprite(0, 0,"/home/fares25/Downloads/halloween.bmp");
        barredevie();
        drawBall();
        drawBarr();
       // changeColor(255,0,0);
        drawbrick();
     }
    if(nbbrick==0){
     sprite(0, 0,"/home/fares25/Downloads/GAME-OVER_4_.bmp");
     }else if(vie==0){
     sprite(0, 0,"/home/fares25/Downloads/halolo.bmp");
     }
    
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_q:
            //touche q appuyé
            printf("Q\n");
            if(x>0){
            x=x-10;//collision du squar avec la largeure de la fentre 
            }
            break;
        case SDLK_d:
            //touche d appuyé
            printf("D\n");
            if(x+longueur<WINDOW_WIDTH){
            x=x+10; //collision du squar
            }
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
            case SDLK_SPACE:
              vitesseBallx =-6;
              vitesseBally = -6;
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                     if ((event.motion.x<498 && event.motion.x>216 ) && (event.motion.y<795&& event.motion.y>735)){
                        goo=0;
                    }
                    break;
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}
