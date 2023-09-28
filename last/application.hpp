#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
//#include "ball.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <random>
#include <time.h>
#include <string>
#include <memory>
#include <cmath>
#include <filesystem>
#include <unistd.h>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;

class Application
{
public:
    Application();
    ~Application()= default;

    void start_menue();
    void pause_menue();
    void Initiate_positions();
    void random_color();
    void choose_random_color_for_cannnon();
    void creat_line_equation();
    void update_cannon_shoot(double delta_time);
    void update(double delta_time);
    void update_cannon(double delta_time);
    void loop();
    void draw_cannon_shoot();
    void draw(int ball_num);
    void check_bals_brust(double delta_time);
    void create_map();
    void Initiate_road();
private:
    Mix_Music* music;

    double       road[1750];
    double       ball_positions[120][2];
    double       ball_positions2[120][2];

    int          random_colors[120];
    int          random_colors2[120]; // its for adding shooted_ball inside balls train
    int mouse_x, mouse_y, last_mouse_x, last_mouse_y;
    double delta_mouse_x, delta_mouse_y, result;
    double rotate_angel;

    int mouse_click_x, mouse_click_y;
    double a, b; //for line_equation
    double       cannon_shoot[2];
    double       cannon_shoot2[2];
    int          ball_on_cannon_number;
    bool         first_check; //its for one time check shooted_ball when arrived in rood

    SDL_Texture *background;
    SDL_Texture *start_pic;
    SDL_Texture *start_pic2;
    SDL_Texture *start_mouse_on_play_pic;
    SDL_Texture *start_mouse_on_exit_pic;
    SDL_Texture *pause_pic;
    SDL_Texture *pause_pic2;
    SDL_Texture *pause_mouse_on_resume_pic;
    SDL_Texture *pause_mouse_on_exit_pic;
    SDL_Texture *cannon;
    SDL_Rect     cannon_position;
    SDL_Texture *ball_on_cannon;
    SDL_Texture *ball_on_cannon_is_moving;
    SDL_Rect     ball_on_cannon_position;
    SDL_Texture *orange_ball;
    SDL_Texture *red_ball;
    SDL_Texture *purple_ball;
    SDL_Texture *green_ball;
    SDL_Texture *blue_ball;
    SDL_Window  *window;
    SDL_Event    window_event;
    SDL_Renderer *window_renderer;
};
