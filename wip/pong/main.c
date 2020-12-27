#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>

const int WIDTH = 1280;
const int HEIGHT = 720;
const int P1_X = 30;
const int P2_X = WIDTH - 2*P1_X;
const int P_Y = 100;
const int PSIZE_X = 30;
const int PSIZE_Y = 100;

int main()
{
    // https://www.sfml-dev.org/tutorials/2.5/
    // https://www.sfml-dev.org/documentation/2.5.1/
    // https://epitech-2022-technical-documentation.readthedocs.io/en/latest/csfml.html
    sfVideoMode mode = {WIDTH, HEIGHT, 24};  // 24 bit depth, "true" color, 16 mil colors
    sfRenderWindow *window = sfRenderWindow_create(mode, "Pong", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);  // 60 frames per second

    sfRectangleShape *player1 = sfRectangleShape_create();
    sfRectangleShape *player2 = sfRectangleShape_create();

    sfVector2f pos_player1 = {P1_X, (HEIGHT - PSIZE_Y) / 2};
    sfVector2f pos_player2 = {P2_X, (HEIGHT - PSIZE_Y) / 2};

    sfVector2f size_player = {PSIZE_X, PSIZE_Y};
    sfRectangleShape_setSize(player1, size_player);
    sfRectangleShape_setSize(player2, size_player);

    sfCircleShape *ball = sfCircleShape_create();
    const int ball_radius = 25;
    sfVector2f pos_ball = {WIDTH / 2 - ball_radius, HEIGHT / 2 - ball_radius};
    sfCircleShape_setRadius(ball, ball_radius);
    sfCircleShape_setFillColor(ball, sfBlue);
    ////////////////////////////////////////////////////////////////
    /// initializations for middle bar, walls, score and fonts
    /// fileu
    const int dist_points = 30;
    int n_points = (HEIGHT / dist_points) - 1; /// -1 because of the walls
    sfRectangleShape **middle = malloc(n_points * sizeof(sfRectangleShape*));
    for(int i = 0; i < n_points; i++) {
        middle[i] = sfRectangleShape_create();
        // -5 correction to be exactly in the middle
        // 25 because the wall is 10 px and we need a bit of extra space
        sfVector2f pos_mid = {WIDTH / 2 - 5, dist_points * i + 25};
        sfVector2f size_mid = {10, 10};
        sfRectangleShape_setPosition(middle[i], pos_mid);
        sfRectangleShape_setSize(middle[i], size_mid);
    }

    sfRectangleShape *walls = sfRectangleShape_create();
    const int wall_thickness = 10;
    sfVector2f pos_wall = {wall_thickness, wall_thickness};
    sfVector2f size_wall = {WIDTH - 2*wall_thickness, HEIGHT - 2*wall_thickness};
    sfRectangleShape_setFillColor(walls, sfTransparent);
    sfRectangleShape_setPosition(walls, pos_wall);
    sfRectangleShape_setSize(walls, size_wall);
    sfRectangleShape_setOutlineThickness(walls, wall_thickness);
    sfRectangleShape_setOutlineColor(walls, sfBlack);

    const char *font_file = "Digital7Mono-B1g5.ttf";
    sfFont *score_font = sfFont_createFromFile(font_file);
    if(!score_font) {
        printf("Error! File %s not found!\n", font_file);
        return 1;
    }

    const int score_width_offset = 200;
    const int score_height_offset = 20;
    sfText *score_text1 = sfText_create();
    sfText *score_text2 = sfText_create();
    sfText_setFont(score_text1, score_font);
    sfText_setFont(score_text2, score_font);

    sfVector2f pos_score1 = {WIDTH / 2 - score_width_offset, score_height_offset};
    // acel 25 e hardcoded... trebuie sa scadem cat ocupa scorul pe x
    sfVector2f pos_score2 = {WIDTH / 2 + score_width_offset - 25, score_height_offset};
    sfText_setPosition(score_text1, pos_score1);
    sfText_setPosition(score_text2, pos_score2);

    const int score_size = 72;
    sfText_setCharacterSize(score_text1, score_size);
    sfText_setCharacterSize(score_text2, score_size);

    unsigned int player1_score = 0;
    unsigned int player2_score = 0;
    const int score_buf_size = 20;
    char player1_score_buf[score_buf_size];
    char player2_score_buf[score_buf_size];
    /// end initializations for middle bar, walls, score and fonts
    ////////////////////////////////////////////////////////////////

    while(sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            else if(event.type == sfEvtKeyPressed) {
                /// keyboard events
                switch(event.key.code) {
                case sfKeyEscape:
                    sfRenderWindow_close(window);
                    break;
                case sfKeyW:
                    break;
                case sfKeyS:
                    break;                case sfKeyI:
                    break;
                case sfKeyK:
                    break;
                default:
                    break;
                }
                /// end keyboard events
            }
        }

        /// update positions
        sfRectangleShape_setPosition(player1, pos_player1);
        sfRectangleShape_setPosition(player2, pos_player2);
        sfCircleShape_setPosition(ball, pos_ball);

        /// update text scores
        sprintf(player1_score_buf, "%u", player1_score);
        sprintf(player2_score_buf, "%u", player2_score);
        sfText_setString(score_text1, player1_score_buf);
        sfText_setString(score_text2, player2_score_buf);

        ////////////////////////////////////////////////////////////////
        /// rendering
        sfRenderWindow_clear(window, sfColor_fromRGB(60, 60, 60));
        /// fileu
        for(int i = 0; i < n_points; i++) {
            sfRenderWindow_drawRectangleShape(window, middle[i], NULL);
        }
        sfRenderWindow_drawRectangleShape(window, walls, NULL);
        sfRenderWindow_drawText(window, score_text1, NULL);
        sfRenderWindow_drawText(window, score_text2, NULL);
        sfRenderWindow_drawRectangleShape(window, player1, NULL);
        sfRenderWindow_drawRectangleShape(window, player2, NULL);
        sfRenderWindow_drawCircleShape(window, ball, NULL);
        sfRenderWindow_display(window);
        /// end rendering
        ////////////////////////////////////////////////////////////////
    }

    sfRectangleShape_destroy(player1);
    sfRectangleShape_destroy(player2);
    sfCircleShape_destroy(ball);

    /// fileu
    for(int i = 0; i < n_points; i++)
        sfRectangleShape_destroy(middle[i]);
    free(middle);

    sfRectangleShape_destroy(walls);
    sfText_destroy(score_text1);
    sfText_destroy(score_text2);
    sfFont_destroy(score_font);

    sfRenderWindow_destroy(window);
    return 0;
}
