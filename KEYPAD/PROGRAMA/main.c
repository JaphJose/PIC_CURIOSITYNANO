/*
 * File:   main.c
 * Author: Jose
 *  CERRADURA ELECTRONICA UWU
 * 
 * Created on 23 de abril de 2021, 12:20 PM
 */


#include <xc.h>
#include "config.h"
#include "lcd_header.h"
#include "keypad.h"

/*Declaracion de Funciones*/
void KEYPAD_GPIO_Config(void);
char KEYPAD_Val(void);


void main(void) {
    /*PINES DIGITALES PARA EL KEYPAD*/
    ANSELD &=~((1<<0)|(1<<1)|(1<<2)|(1<<3));
    ANSELF &=~((1<<0)|(1<<1)|(1<<2)|(1<<3));
    
    Lcd_Init();
    Lcd_Cmd(LCD_CURSOR_OFF);
    Lcd_string(1,0,"HELLO");
    __delay_ms(30);
    Lcd_string(2,0,"MOTHERFUCKERS");
    __delay_ms(30);
    Lcd_Cmd(LCD_CLEAR);
    KEYPAD_GPIO_Config();
    /*Array que va alamacenar los datos introducidos en el teclado*/
    char valor[4];
    /*Bandera que indica si la contraseña es corrcta*/
    char flag;
    char contrasena[4]={'1','A','9','D'};
    /*Constante que se puede omitir*/
    int i=0;
    
    while(1){
        
        flag='T';
        Lcd_setCursor(1,0);
        Lcd_print("PASSWORD");
        Lcd_setCursor(2,0);
        /*Menu de Inicializacion -> Solicitud de Contraseña*/
        for(int i=0;i<4;i++){
            do{
            valor[i]=KEYPAD_Val();
            
            if(valor[i]=='P'){
                Lcd_Cmd(LCD_CLEAR);
                Lcd_setCursor(1,0);
                Lcd_print("PASSWORD");
                Lcd_setCursor(2,0);
                i=-1;               
            } 
            
            }
            while(valor[i]=='K');
            Lcd_Chr_CP('*');
            __delay_ms(100);
        }
        
        /*Bucle para validar la Contraseña*/
            for(int j=0;j<4;j++){
                if(valor[j]!=contrasena[j]){
                                        
                    flag='F';       
                }      
            }
            if(flag=='T'){
                Lcd_Cmd(LCD_CLEAR);
                Lcd_string(1,0,"ACEPTAR");
                while(KEYPAD_Val()!='P');
                __delay_ms(90);
            }
            else if(flag=='F'){
                Lcd_Cmd(LCD_CLEAR);
                Lcd_string(1,0,"DENEGAR");
                
                while(KEYPAD_Val()!='P');
                __delay_ms(90);
            }
    }
    
    return;
}
