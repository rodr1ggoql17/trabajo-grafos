/*
    INFB8061: Grafos y lenguajes formales 
    Sección: 411
    Docente: Michael Emil Cristi Capstick 
    Integrantes:
        -> Valentin Lara
        -> Diego Troncoso
        -> Hugo Osses
        -> Miguel Espildora
        -> Rodrigo Reyes
*/
#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

class Laberinto{ // Construimos la clase la cual construira nuestro laberinto
    private:
        int x_inicio,
            y_inicio,
            x_final,
            y_final;
        static const int col = 13,
                         fil = 14;
        const char escribir = 219,
                   espacio = ' ';
        char matriz[fil][col] = // matriz la cual almacena el laberinto (valores por default cambian cuando el usuario genera un laberinto)
        {   {escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir},
            {escribir,espacio,espacio,espacio,espacio,espacio,espacio,espacio,espacio,espacio,espacio,escribir},
            {espacio,espacio,escribir,espacio,escribir,espacio,escribir,escribir,escribir,escribir,espacio,escribir},
            {escribir,escribir,escribir,espacio,escribir,espacio,espacio,espacio,espacio,escribir,espacio,escribir},
            {escribir,espacio,espacio,espacio,espacio,escribir,escribir,escribir,espacio,escribir,espacio,espacio},
            {escribir,escribir,escribir,escribir,espacio,escribir,espacio,escribir,espacio,escribir,espacio,escribir},
            {escribir,espacio,espacio,escribir,espacio,escribir,espacio,escribir,espacio,escribir,espacio,escribir},
            {escribir,escribir,espacio,escribir,espacio,escribir,espacio,escribir,espacio,escribir,espacio,escribir},
            {escribir,escribir,escribir,escribir,escribir,escribir,espacio,escribir,escribir,escribir,espacio,escribir},
            {escribir,espacio,espacio,espacio,espacio,espacio,espacio,escribir,espacio,espacio,espacio,escribir},
            {escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir,escribir}};
  public:
  // metodos
    void resolver(){ // determina si el laberinto tiene solucion o no
      if(resolver(x_inicio,y_inicio)){
        cout << "Terminado, tiene Solucion :D" << endl;
      }else{
        cout << "No tiene solucion :c" << endl;
      }
    }

  bool resolver(int fila_actual,int columna_actual){
    // caso base, si es que nuestra posicion actual llego al final
    if(fila_actual== x_final && columna_actual == y_final){
      return true;
    }
    // caso base, si es que no es el final de la ejecucion
    if(!es_final(fila_actual,columna_actual)){
      return false;
    }
    matriz[fila_actual][columna_actual] = '*'; // pintamos el camino
    // analizamos el norte,sur,este y oeste
    if (resolver(fila_actual+1,columna_actual)|| resolver(fila_actual-1,columna_actual)|| resolver(fila_actual,columna_actual+1)|| resolver(fila_actual,columna_actual-1)){
      return true;
    }else{
      // si no existe una casilla en la que nos podamos mover, borra el camino
      matriz[fila_actual][columna_actual] = espacio;
      return false;
    }
    return false;
  }
  bool es_final(int x,int y){ // verifica si el camino es el correcto
    if(x>=0 && y>=0 && x<fil && y<col){
      if(matriz[x][y]==espacio){
        return true;
      }
    }
    return false;
  }
  void show_matriz(){ // ver laberinto
    for(int r=0;r<fil;r++){
      for(int c=0;c<col;c++){
        cout << matriz[r][c] << " ";
      }
      cout<<endl;
    }
  }
  void generar(){ // genera laberinto aleatorio
    for(int i=0;i<fil;i++){
      for(int j=0;j<col;j++){
        if(i==0 || i==(fil-1)||j==0 || j==(col-1)){
          matriz[i][j] = escribir;
        }else{
          matriz[i][j] = espacio;
        }
      }
    }
    for(int i=1;i<fil;i++){
      for(int j=1;j<col;j++){
        if(i%2==0 && j%2==0){
          matriz[i][j] = escribir;
        }
      }
    }
    int value1 = 2+rand() % 14,
        value2 = 2+rand() % 14;
    int iterador = 0;
    // copia
    char maze_aux[fil][col];
    for(int i=0;i<fil;i++){
      for(int j=0;j<col;j++){
        maze_aux[i][j] =matriz[i][j]; 
      }
    }
    for(int i=1;i<(fil-1);i++){
      for(int j=1;j<(col-1);j++){
        if(maze_aux[i][j]==escribir){
          for(int args=0;args<4;args++){
            int x[] = {i+1,i-1,i,i},
                y[] = {j,j,j+1,j-1};
            if(maze_aux[x[args]][y[args]]==espacio){
              if(rand()%101 < 25){
                matriz[x[args]][y[args]] = escribir;
              }else{
                continue;
              }
            }
          }
        }
      }
    }
    // generamos entrada y salida aleatoria
    int entrada = 1+rand() % (col-2),
        salida = 1+rand() % (col-2);
    matriz[entrada][0] = espacio;
    matriz[salida][col-1] = espacio;

    x_inicio = entrada;
    y_inicio = 0;
    x_final = salida;
    y_final = col-1;
  }
  //getters para obtener inicio y final
  int obtener_xinicio(){
    return x_inicio;
  }
  int obtener_yinicio(){
    return y_inicio;
  }
  int obtener_xfinal(){
    return  x_final;
  }
  int obtener_yfinal(){
    return y_final;
  }
};
void menu(Laberinto maze){ // menu de opciones
    cout << "\t\t\tBIENVENIDO!!!!!!!\n";
    bool ok = true;
    char op = ' ';
    while(ok){
        cout << "Listado de opciones\n\n";
        cout << "1. Generar Laberinto Aleatorio " << endl;
        cout << "2. Ver Laberinto Generado " << endl;
        cout << "3. Solucionar Laberinto si es Posible " << endl;
        cout << "4. Finalizar Ejecucion " << endl;
        cout << "Ingrese su respuesta:";
        cin >> op;
        switch(op){
            case '1': maze.generar();
                      cout <<endl<< "Laberinto Generado" << endl;
                      cout << "Inicio Generado : " << "["<<maze.obtener_xinicio() <<"]["<<maze.obtener_yinicio()<<"]" << endl;
                      cout << "Final Generado : " << "["<<maze.obtener_xfinal() <<"]["<<maze.obtener_yfinal()<<"]" << endl << endl;
                      break;
            case '2': cout << endl << "Mostrando Laberinto..." << endl << endl; 
                      maze.show_matriz();
                      cout << endl << endl;
                      break;
            case '3': cout << endl <<"Usando Toda la Computacion Cuantica Posible..." << endl;
                      maze.resolver();
                      maze.show_matriz();
                      cout << endl;
                      break;
            case '4': cout << endl << endl <<"      Gracias por usar Nuestro Programa       " << endl;
                      exit(1);
                      break;
            default: 
                      cout << "Respuesta ingresada NO es valida" << endl;
        }
    }
}
int main() {
  srand(time(NULL));
  Laberinto mi_laberinto;
  menu(mi_laberinto);
  return 0;
}
