#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

enum LoadState { TileSet, Map};

int state = 0;

ALLEGRO_BITMAP *tileSet;

void CargarMapa(const char *nombreArchivo, std::vector< std::vector <int> > &mapa){
    std::ifstream openfile(nombreArchivo);
    if(openfile.is_open()){

        std::string line, value;

        while(!openfile.eof()){
            std::getline(openfile, line);

            if(line.find("[TileSet]") != std::string::npos){
                state = TileSet;
                continue;
            }
            else if(line.find("[Map]") != std::string::npos){
                state = Map;
                continue;
            }
            switch(state){
            case TileSet:
                {
                if(line.length() > 0)
                    tileSet = al_load_bitmap(line.c_str());
                break;
                }
            case Map:
                {
                std::stringstream str(line);
                std::vector<int> tempVector;

                while(!str.eof()){
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                        tempVector.push_back(atoi(value.c_str()));
                }
                mapa.push_back(tempVector);
                break;
                }
            }
        }
    }
    else{}
}

void DibujarMapa(std::vector <std::vector <int> > mapa){
    for(int i = 0; i < mapa.size(); i++){
        for(int j = 0; j < mapa[i].size(); j++){
            al_draw_bitmap_region(tileSet, mapa[i][j] * BlockSizeX, 0, BlockSizeX, BlockSizeY, j * BlockSizeX, i * BlockSizeX, NULL);
        }
    }
}

#endif // MAPA_H_INCLUDED
