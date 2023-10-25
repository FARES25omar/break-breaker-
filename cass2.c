 #include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 700

#define WINDOW_HEIGHT 900
#define FPS 60
int rb;  //rayon ball            
int xb;   //xball
int yb;   //yball              
int x;  //x du carrer
int y;  //y du carrer
int longueur;
int vitesseBallx;
int vitesseBally;
int Tabmax =18;
int Tab[18];
int viebrick[18]; 
int vie =3;



void drawBall(){
   changeColor(255,0,255);
   drawCircle(xb,yb,rb);
   xb+=vitesseBallx; //j'ai liere la vitesse avec la position ;
   yb+=vitesseBally;
    if((xb>(WINDOW_WIDTH-rb) ||(xb<rb)) ){
     vitesseBallx=-vitesseBallx;
    }
    if (yb > WINDOW_HEIGHT - rb) {
        vie--; 
      if (vie > 0) {
         xb = WINDOW_WIDTH / 2;
         yb = WINDOW_HEIGHT / 2;
        } else {
         freeAndTerminate();
            
        }
    }
    if ((yb>(WINDOW_HEIGHT-rb) || (yb<rb)) || ((x<=xb) &&(xb<=x+longueur)&&(yb>=y) ) ){
      vitesseBally=-vitesseBally;       
      
   }
}
void drawSqaure(){
   changeColor(0,225,0); 
      drawSquare(x,y,longueur);
  
}

void init_game(){
   // mettre votre code d'initialisation ici
   xb =WINDOW_WIDTH/2;//position de la balle 
   yb =WINDOW_HEIGHT/2;
   rb =20; 
   vitesseBallx =3;
   vitesseBally = -3;
   x=WINDOW_WIDTH/2;
   y=700;
   longueur=100;
   
  
   for(int i=0;i<Tabmax;i++){
     viebrick[i]=1;
     }
  
     
  } 
  
  
       
     
 void drawbrick(){
   int xr;
   int yr;
   int lr=80;
   int hr=40;
  
   
  
   for( int j=0;j<6;j++){
     changeColor(0,225,225);
     for(int i=j;i<18;i=i+6){
       if(viebrick[i]==1){
         xr=(35+(j*110)); //10 c'est moon ecart 
         yr=40+(i)/6*(lr); 
         drawRect( xr, yr, lr, hr);
      
           if((xb>xr) &&(xb<xr+lr)&&((yb>yr)&&(yb<yr+hr))){
           
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
   
    clear();
    drawBall();
    drawSquare(x,y,150);
    changeColor(255,0,0);
    drawbrick();
    
    //drawCircle(100,100,100);
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
            x=x-10;//collision du squar
            }
            break;
        case SDLK_d:
            //touche d appuyé
            printf("D\n");
            if(x+longueur<WINDOW_WIDTH-longueur/2){
            x=x+10; //collision du squar
            }
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
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
