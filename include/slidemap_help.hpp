//
//  slidemap_help.hpp
//  JogoGB
//
//  Created by Psidium on 5/9/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef slidemap_help_hpp
#define slidemap_help_hpp

#include <stdio.h>


//A instrucao pede pra criar uma classe sem propriedades com 3 metodos...
//em c++, isso vai criar uma vtable e organizara codgio de uma maneira inutil
//serao 3 funcoes siples entao

void desenha(float* x, float* y, int c, int l, int tw, int th);
void calc_mouse_click(int* c, int* l, int mx, int my, int tw, int th);
void navegacao();

#endif /* slidemap_help_hpp */
