#include "application.hpp"

// this is the main function
Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Magic ball game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640*3,
                                          480*3,
                                          SDL_WINDOW_RESIZABLE);

    window_renderer = SDL_CreateRenderer(window, -1, 0);

    char tmp[256];
    getcwd(tmp, 256);
    //cout << "Current working directory: " << tmp;

    IMG_Init(IMG_INIT_PNG);
    background = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/background.png"));
    cannon = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/cannon.png"));
    red_ball = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/redball.png"));
    blue_ball = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/blueball.png"));
    orange_ball = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/orangeball.png"));
    green_ball = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/greenball.png"));
    purple_ball = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/purpleball.png"));
    start_pic2 = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/start.png"));
    start_mouse_on_play_pic = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/start_mouse_on_play.png"));
    start_mouse_on_exit_pic = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/start_mouse_on_exit.png"));
    pause_pic2 = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/pause.png"));
    pause_mouse_on_resume_pic = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/pause_mouse_on_resume.png"));
    pause_mouse_on_exit_pic = SDL_CreateTextureFromSurface(window_renderer,
        IMG_Load("/home/skyboy/Desktop/cpp_game/pause_mouse_on_exit.png"));
    IMG_Quit();

    cannon_position.x = 240;
    cannon_position.y = 150;
    cannon_position.w = 200;
    cannon_position.h = 345;
}

// like the name of function i am looping over some codes
void Application::loop()
{
    int ball_num = 0;
    double last_ball_num = 80.0;
    Initiate_positions();
    random_color();
    bool ball_shooted = false;
    bool keep_running = true;
    bool game_is_in_start = true;
    bool game_is_pause = false;
    choose_random_color_for_cannnon();
    Initiate_road();
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS("/home/skyboy/Desktop/cpp_game/music.mp3");
    Mix_PlayMusic(music, 1);

    while(keep_running)
    {
		while(SDL_PollEvent(&window_event) > 0)
		{
			switch(window_event.type)
			{
			case SDL_QUIT:
				keep_running = false;
                break;
            //Select surfaces based on key press
            //something for check key presed or not

            case SDL_KEYDOWN:
                switch (window_event.key.keysym.sym)
                {
                    /*
                    case SDLK_KP_ENTER:
                        //SDL_BlitSurface(load_surface("/home/skyboy/Desktop/cpp_game/canon.bmp"), NULL, window_surface, NULL);
                        //SDL_UpdateWindowSurface(window);
                        break;
                    */
                    case SDLK_ESCAPE:
                        if (!game_is_pause){
                            game_is_pause = true;
                        } else {
                            game_is_pause = false;
                        }
                        //std::cout << "esc pressed" << '\n';
                        break;

                }

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_click_x, &mouse_click_y);
                //std::cout << mouse_x << '\n';
                if (game_is_in_start)
                {
                    ////std::cout << mouse_click_x << " - " << mouse_click_y << '\n';
                    if (289<mouse_click_x==true && mouse_click_x<840==true &&
                         550<mouse_click_y==true && mouse_click_y<700==true)
                    {
                        //std::cout << "start" << '\n';
                        game_is_in_start = false;
                        break;
                    }
                    else if (289<mouse_click_x==true && mouse_click_x<840==true &&
                         810<mouse_click_y==true && mouse_click_y<960==true)
                    {
                        //std::cout << "exit" << '\n';
                        keep_running = false;
                        break;
                    }
                }
                else if (game_is_pause)
                {
                    ////std::cout << mouse_click_x << " - " << mouse_click_y << '\n';
                    if (718<mouse_click_x==true && mouse_click_x<1270==true &&
                         635<mouse_click_y==true && mouse_click_y<800==true)
                    {
                        game_is_pause = false;
                        //std::cout << "resume" << '\n';
                        break;
                    }
                    else if (718<mouse_click_x==true && mouse_click_x<1270==true &&
                         880<mouse_click_y==true && mouse_click_y<1045==true)
                    {
                        game_is_in_start = true;
                        game_is_pause = false;
                        Initiate_positions();
                        random_color();
                        //std::cout << "exit" << '\n';
                        break;
                    }
                }
                else
                {
                    ball_shooted = true;
                    first_check = false; // it means ball is not checked for burst
                    ball_on_cannon_is_moving = ball_on_cannon; //choosing color of ball
                    choose_random_color_for_cannnon();
                    cannon_shoot[0] = cannon_shoot2[0] = ball_on_cannon_position.x;
                    cannon_shoot[1] = cannon_shoot2[1] = ball_on_cannon_position.y;
                    SDL_GetMouseState(&mouse_click_x, &mouse_click_y);
                    creat_line_equation();
                    break;
                }
            }
        }

        if (game_is_in_start==true && game_is_pause==false)
        {
            SDL_GetMouseState(&mouse_click_x, &mouse_click_y);
            if (289<mouse_click_x==true && mouse_click_x<840==true &&
                 550<mouse_click_y==true && mouse_click_y<700==true)
            {
                start_pic = start_mouse_on_play_pic;
            }
            else if (289<mouse_click_x==true && mouse_click_x<840==true &&
                 810<mouse_click_y==true && mouse_click_y<960==true)
            {
                start_pic = start_mouse_on_exit_pic;
            }
            else
            {
                start_pic = start_pic2;
            }
            start_menue();
        }
        else if (game_is_pause)
        {
            SDL_GetMouseState(&mouse_click_x, &mouse_click_y);
            ////std::cout << mouse_click_x << " - " << mouse_click_y << '\n';
            if (718<mouse_click_x==true && mouse_click_x<1270==true &&
                 635<mouse_click_y==true && mouse_click_y<800==true)
            {
                pause_pic = pause_mouse_on_resume_pic;
            }
            else if (718<mouse_click_x==true && mouse_click_x<1270==true &&
                 880<mouse_click_y==true && mouse_click_y<1045==true)
            {
                pause_pic = pause_mouse_on_exit_pic;
            }
            else
            {
                pause_pic = pause_pic2;
            }
            pause_menue();
        }
        else
        {
        if (ball_shooted){
                SDL_RenderClear(window_renderer);
                SDL_RenderCopy(window_renderer, background, nullptr, nullptr);
                update_cannon_shoot(1.0/60.0);
                draw_cannon_shoot();
                //if ((int)cannon_shoot[0] >= mouse_click_x || (int)cannon_shoot[1] >= mouse_click_y)
                //    ball_shooted = false;
                update_cannon(1.0/60.0);
                update(1.0/30.0);
                if ((int)(ball_positions[ball_num][0] - last_ball_num) == 94)
                {
                    ball_num += 1;
                    last_ball_num = ball_positions[ball_num][0];
                    //std::cout << ball_num << '\n';
                }
                draw(ball_num);
            } else {
                SDL_RenderClear(window_renderer);
                SDL_RenderCopy(window_renderer, background, nullptr, nullptr);
                update_cannon(1.0/60.0);
                update(1.0/30.0);
                if ((int)(ball_positions[ball_num][0] - last_ball_num) == 94)
                {
                    ball_num += 1;
                    last_ball_num = ball_positions[ball_num][0];
                    //std::cout << ball_num << '\n';
                }
                draw(ball_num);
            }
        }
    }
}

void Application::creat_line_equation()
{
    //(299, 199) first_locaton
    // y = ax + b
    a = ((mouse_click_y - 199) / (double)(mouse_click_x - 299));
    //std::cout << a << '\n';
    //b = mouse_click_y + a * mouse_click_x;
    //b = -b;
}

void Application::random_color()
{
    srand(time(0));
	int lb = 1, ub = 5;
	// This program will create some sequence of random
	// numbers on every program run within range lb to ub
    for (int i=0; i<50 ;i++)
    {
        random_colors[i] = (rand() % (ub - lb + 1)) + lb;
        ////std::cout << random_colors[i] << '-';
    }
    ////std::cout << '\n';
    ////std::cout << '\n';
    ////std::cout << '\n';
}

void Application::choose_random_color_for_cannnon()
{
    srand(time(0));
    int lb = 1, ub = 5;
    ball_on_cannon_number = (rand() % (ub - lb + 1)) + lb;

    if (ball_on_cannon_number==1){
        ball_on_cannon = red_ball;
    } else if (ball_on_cannon_number==2) {
        ball_on_cannon = green_ball;
    } else if (ball_on_cannon_number==3) {
        ball_on_cannon = purple_ball;
    } else if (ball_on_cannon_number==4) {
        ball_on_cannon = blue_ball;
    } else if (ball_on_cannon_number==5) {
        ball_on_cannon = orange_ball;
    }
}

void Application::Initiate_positions()
{
    int num = 0;
    for (int i=0; i<52; i++)
    {
        ball_positions[i][0] = 80.0 + num;
        ball_positions[i][1] = 835.0;
        num = num - 95;
    }
}

void Application::update_cannon_shoot(double delta_time)
{
    // a=5  ---> delta_time 1
    // a=2  ---> delta_time 1*5/
    //delta_time = delta_time*a/0.45;
    if (a<0)
        a = -a;
    if (0.2<=a && a<0.3){
        delta_time = delta_time*4.5/(a*2);
    } else if (0.1<=a && a<0.2){
        delta_time = delta_time*4.5/(a*3);
    } else if (0.05<=a && a<0.1){
        delta_time = delta_time*4.5/(a*8);
    } else if (0<a && a<0.05){
        delta_time = delta_time*4.5/(a*12);
    } else {
        delta_time = delta_time*4.5/a;
    }

    if (cannon_shoot[0] < mouse_click_x-42 || cannon_shoot[1] < mouse_click_y-42 )
    {
        if (mouse_click_x < cannon_shoot2[0])
        {
            cannon_shoot[0] -= (30 * delta_time);
        } else  {
            cannon_shoot[0] += (30 * delta_time);
        }
        if (mouse_click_y < cannon_shoot2[1])
        {
            cannon_shoot[1] -= a * (30 * delta_time);
        } else {
            cannon_shoot[1] += a * (30 * delta_time);
        }
    } else {
        if (first_check == false)
        {
            //first_check = true;
            //check_bals_brust(1.0/30.0);
            //std::cout << "this part of game is developing" << '\n';
        }
    }


    ////std::cout << (int)cannon_shoot[0] << " - " << (int)log(cannon_shoot[1])/log(1.005)+80 << '\n';
    //if ((int)cannon_shoot[0] == (int)log(cannon_shoot[1])/log(1.005)+80)
    //    enough_move = true;
}
        /*
        if (700.0 < cannon_shoot[0] && cannon_shoot[0] < 900.0)
        {
            cannon_shoot[1] -= 10*delta_time;
        }
        else if (cannon_shoot[0] < 1000.0)
        {
            cannon_shoot[1] -= 10*(1.5*delta_time);
        }
        else if (cannon_shoot[0] < 1100.0)
        {
            cannon_shoot[1] -= 10*(1.7*delta_time);
        }
        else if (cannon_shoot[0] < 1500.0)
        {
            cannon_shoot[1] -= 10*(5*delta_time);
        }
        else if (cannon_shoot[0] < 1580.0)
        {
            cannon_shoot[1] -= 10*(15*delta_time);
        }
        else if (cannon_shoot[0] < 1615.0)
        {
            cannon_shoot[1] -= 10*(15*delta_time);
        }
        */


void Application::update_cannon(double delta_time)
{
    delta_mouse_x = mouse_x - 330;
    delta_mouse_y = mouse_y - 250;
    if (delta_mouse_x != 0 && delta_mouse_y !=0 )
    {
        rotate_angel = (atan2(-delta_mouse_x, delta_mouse_y) * 180.0000)/ 3.14159265;
    }
    SDL_GetMouseState(&mouse_x, &mouse_y);
}

void Application::Initiate_road()
{
    road[0] = 835;
    double y = 835;
    int x = 80;
    for (int i=1; i<1722; i++)
    {
        x++;
        y -= pow(1.005, x - 1550);
        road[i] = y;
        ////std::cout << i << " - " << road[i] << '\n';
    }
}

void Application::update(double delta_time)
{
    for (int i=0; i<50; i++)
    {
        if (ball_positions[i][0] < 1200.0){
            ball_positions[i][0] +=  20*delta_time;
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        } else if (ball_positions[i][0] < 1276){
            ball_positions[i][0] += (18 * delta_time);
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        } else if (ball_positions[i][0] < 1422){
            ball_positions[i][0] += (16 * delta_time);
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        } else if (ball_positions[i][0] < 1472){
            ball_positions[i][0] += (14 * delta_time);
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        } else if (ball_positions[i][0] < 1592){
            ball_positions[i][0] += (11 * delta_time);
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        } else if (ball_positions[i][0] < 1720){
            ball_positions[i][0] += (7 * delta_time);
            ball_positions[i][1] = road[(int)ball_positions[i][0]];
        }

        //ball_positions[i][1] = 240*sin((ball_positions[i][0] - 1700)/240) +900;
        /*
        if ( ball_positions[i][0] < 700.0)
        {
            ball_positions[i][0] += (20 * delta_time);
        }
        else if (ball_positions[i][0] < 900.0)
        {
            ball_positions[i][0] += (20 * delta_time);
            ball_positions[i][1] -= delta_time;
        }
        else if (ball_positions[i][0] < 1000.0)
        {
            ball_positions[i][0] += (20 * delta_time);
            ball_positions[i][1] -= (1.5*delta_time);
        }
        else if (ball_positions[i][0] < 1100.0)
        {
            ball_positions[i][0] += (20 * delta_time);
            ball_positions[i][1] -= (1.7*delta_time);;
        }
        else if (ball_positions[i][0] < 1500.0)
        {
            ball_positions[i][0] += (20 * delta_time);;
            ball_positions[i][1] -= (5*delta_time);
        }
        else if (ball_positions[i][0] < 1580.0)
        {
            ball_positions[i][0] += (14 * delta_time);
            ball_positions[i][1] -= (15*delta_time);
        }
        else if (ball_positions[i][0] < 1615.0)
        {
            ball_positions[i][0] += (12 * delta_time);
            ball_positions[i][1] -= (15*delta_time);
        }
        else if (ball_positions[i][1] > 80 )
        {
            ball_positions[i][0] += (5 * delta_time);
            ball_positions[i][1] -= (19 * delta_time);
            //std::cout << ball_positions[0][0] << '\n';
        }
        */
    }
}

void Application::start_menue()
{
    SDL_RenderClear(window_renderer);
    SDL_RenderCopy(window_renderer, start_pic, nullptr, nullptr);
    SDL_RenderPresent(window_renderer);
}

void Application::pause_menue()
{
    SDL_RenderClear(window_renderer);
    SDL_RenderCopy(window_renderer, pause_pic, nullptr, nullptr);
    SDL_RenderPresent(window_renderer);
}

void Application::draw_cannon_shoot()
{
    SDL_Rect cannon_shoot_position = {
        (int)cannon_shoot[0],
        (int)cannon_shoot[1],
        95,
        95
    };
    SDL_RenderCopy(window_renderer, ball_on_cannon_is_moving, nullptr, &cannon_shoot_position);
}

void Application::draw(int ball_num)
{
    SDL_Point Center{100, 100}; //175 110
    SDL_RenderCopyEx(window_renderer, cannon, NULL, &cannon_position, rotate_angel , &Center, SDL_FLIP_NONE);
    ball_on_cannon_position = {292, 199, 95, 95};
    SDL_Point Center1{47, 47};
    SDL_RenderCopyEx(window_renderer, ball_on_cannon, NULL, &ball_on_cannon_position, rotate_angel , &Center1, SDL_FLIP_NONE);

    for (int i=0; i <= ball_num; i++)
    {
        SDL_Rect dstrect = {
            (int)ball_positions[i][0],
            (int)ball_positions[i][1],
            95,
            95
        };

        if (random_colors[i] == 1) //red
        {
            SDL_RenderCopy(window_renderer, red_ball, nullptr, &dstrect);
        }
        else if (random_colors[i] == 2) //green
        {
            SDL_RenderCopy(window_renderer, green_ball, nullptr, &dstrect);
        }
        else if (random_colors[i] == 3) //purple
        {
            SDL_RenderCopy(window_renderer, purple_ball, nullptr, &dstrect);
        }
        else if (random_colors[i] == 4) //blue
        {
            SDL_RenderCopy(window_renderer, blue_ball, nullptr, &dstrect);
        }
        else //orange
        {
            SDL_RenderCopy(window_renderer, orange_ball, nullptr, &dstrect);
        }
    }
    SDL_RenderPresent(window_renderer);
}


void Application::check_bals_brust(double delta_time)
{
    int ball_must_fell_in;
    for (int i=0; i<51; i++)
    {
        if (mouse_click_x-40 < ball_positions[i][0] && ball_positions[i][0] < mouse_click_x)
        {
            ball_must_fell_in = i-1;
            //std::cout << "before" << '\n';
        } else if (mouse_click_x < ball_positions[i][0] && ball_positions[i][0] < mouse_click_x+40)
        {
            ball_must_fell_in = i+1;
            //std::cout << "next" << '\n';
        }
    }

    // start adding shooted_ball color in random_collors array
    //std::cout << "colors" << '\n';
    for (int j=0; j<120; j++)
    {
        //std::cout << random_colors[j] << '-';
    }
    //std::cout << '\n';
    //std::cout << '\n';
    //std::cout << '\n';
    for (int i=0; i<120; i++)
    {
        if (random_colors[i] == 0)
            break;

        if (i < ball_must_fell_in)
        {
            random_colors2[i] = random_colors[i];
        }
        else if (i == ball_must_fell_in)
        {
            random_colors2[i] = ball_on_cannon_number;
        } else {
            random_colors2[i+1] = random_colors[i];
        }
    }

    for (int j=0; j<120; j++)
    {
        random_colors[j] = random_colors2[j];
        //std::cout << random_colors[j] << '-';
    }
    //std::cout << '\n';
    //std::cout << '\n';
    //std::cout << '\n';
    //finish adding shooted_ball in random_colors


    //start adding shooted_ball in balls_positions
    int the_ball_we_want_repalace_x = ball_positions[ball_must_fell_in-1][0];
    int the_ball_we_want_repalace_y = ball_positions[ball_must_fell_in-1][1];
    for (int k=0; k<120; k++)
    {
        if (k < ball_must_fell_in)
        {
            //first i push the balls toward
            if (ball_positions[k][0] < 1200.0){
                ball_positions[k][0] +=  20*delta_time;
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            } else if (ball_positions[k][0] < 1276){
                ball_positions[k][0] += (18 * delta_time);
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            } else if (ball_positions[k][0] < 1422){
                ball_positions[k][0] += (16 * delta_time);
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            } else if (ball_positions[k][0] < 1472){
                ball_positions[k][0] += (14 * delta_time);
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            } else if (ball_positions[k][0] < 1592){
                ball_positions[k][0] += (11 * delta_time);
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            } else if (ball_positions[k][0] < 1720){
                ball_positions[k][0] += (7 * delta_time);
                ball_positions[k][1] = road[(int)ball_positions[k][0]];
            }
            //now i add the shooted_ball inside ball positions

            ball_positions2[k][0] = ball_positions[k][0];
            ball_positions2[k][1] = ball_positions[k][1];
        }
    }

    for (int l=0; l<120; l++){

        if (l == ball_must_fell_in){
            ball_positions[l][0] = the_ball_we_want_repalace_x;
            ball_positions[l][1] = the_ball_we_want_repalace_y;
        }
        else
        {
            ball_positions[l][0] = ball_positions2[l][0];
            ball_positions[l][0] = ball_positions2[l][1];
        }
        //std::cout << l << " - " << ball_positions[l][0] << " - " << ball_positions[l][1] << '\n';
    }
}
