#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//main
void get_data(char *);
void create_puzzle();
void play();

//front-end
void draw_box();
void put_element(const uint8_t);
int get_conformation(const char *, const char *);
void ask_size();
void display_logo();

#endif // HEADER_H_INCLUDED
