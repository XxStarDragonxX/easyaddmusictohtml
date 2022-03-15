#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Programma per aggiungere nuove canzoni piu in fretta */
static const char filehtml[] = { "index.html" }; /* al posto di index.html metti l'html della tua pagina dove vuoi che vengano aggiunte le canzoni */
static const char path[] = { "./mp3/" }; /* qui e il path dei file mp3, puo essere sia assoluto che relativo */
 
int main(int argc, char *argv[]){
         FILE *fptr = fopen(filehtml, "r");
 
         if(!fptr){
                 printf("Impossibile aprire file\n");
                 return 1;
         }
 
         if(argc != 4){
                 printf("Usage: %s nomefile.mp3 nome link\n", argv[0]);
                 return 1;
         }
 
         char nomefile[50];
         char nome[50];
         char link[50];
 
         strcpy(nomefile, argv[1]);
         strcpy(nome, argv[2]);
         strcpy(link, argv[3]);
 
         char *cmd[] = { "yt-dlp", "-x", "-P", path, "-o", nomefile, "--audio-format", "mp3", link, NULL };
 
         if(!fork()){
                 execvp(cmd[0], cmd);
                 printf("execvp non ha funzionato, che si fa ora?\n");
                 return 1;
         }else{
                 wait();
         }
 
 
         FILE *fptrnew = fopen("new.html", "w");
         
         if(!fptrnew){
                 printf("Errore con la creazione del file temporaneo\n");
                 return 1;
         }
 
         char line[1000];
         fgets(line, 1000, fptr);
         
         while(strcmp(line, "</html>") && strcmp(line, "</html>\n")){
                 fprintf(fptrnew, line);
                 fgets(line, 1000, fptr);
         }
         
         fprintf(fptrnew, "\t<a>%s</a><br>\n\t<audio controls loop>\n\t\t<source src=\"%s%s\" type=\"audio/mp3\" id=\"%s\">\n\t</audio><br>\n\n", nome, path, nomefile, li    nk);
         fprintf(fptrnew, "</html>");
 
         fclose(fptr);
         fclose(fptrnew);
         
         system("mv new.html index.html");
 
         printf("fatto, ma con un po di bloat, mi spiace...\n");
 
         return 0;
}            
