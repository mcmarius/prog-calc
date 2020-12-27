#include <stdio.h>
#include <stdlib.h>
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
    sfVideoMode mode = {WIDTH, HEIGHT, 24};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Pong", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);

    sfRectangleShape *player1 = sfRectangleShape_create();
    sfRectangleShape *player2 = sfRectangleShape_create();

    sfVector2f pos1 = {P1_X, (HEIGHT - PSIZE_Y) / 2};
    sfVector2f pos2 = {P2_X, (HEIGHT - PSIZE_Y) / 2};
    sfRectangleShape_setPosition(player1, pos1);
    sfRectangleShape_setPosition(player2, pos2);

    sfVector2f size = {PSIZE_X, PSIZE_Y};
    sfRectangleShape_setSize(player1, size);
    sfRectangleShape_setSize(player2, size);

    // fileu
    int n_points = HEIGHT / 30;
    sfRectangleShape **middle = malloc(n_points * sizeof(sfRectangleShape*));
    for(int i = 0; i < n_points - 1; i++) {
        middle[i] = sfRectangleShape_create();
        sfVector2f pos_mid = {WIDTH / 2, 30 * i + 25};
        sfVector2f size_mid = {10, 10};
        sfRectangleShape_setPosition(middle[i], pos_mid);
        sfRectangleShape_setSize(middle[i], size_mid);
    }

    sfRectangleShape *walls = sfRectangleShape_create();
    sfVector2f pos_wall = {10, 10};
    sfVector2f size_wall = {WIDTH - 20, HEIGHT - 20};
    sfRectangleShape_setFillColor(walls, sfTransparent);
    sfRectangleShape_setPosition(walls, pos_wall);
    sfRectangleShape_setSize(walls, size_wall);
    sfRectangleShape_setOutlineThickness(walls, 10);
    sfRectangleShape_setOutlineColor(walls, sfBlack);

    sfFont *scoreFont = sfFont_createFromFile("Digital7Mono-B1g5.ttf");
    if(!scoreFont) {
        printf("Error! File %s not found!\n", "Digital7Mono-B1g5.ttf");
        return 1;
    }

    int score_offset = 100;
    sfText *score_text1 = sfText_create();
    sfText *score_text2 = sfText_create();
    sfText_setFont(score_text1, scoreFont);
    sfText_setFont(score_text2, scoreFont);

    sfVector2f score1_pos = {WIDTH / 2 - score_offset, 20};
    // acel 25 e hardcoded... trebuie sa scadem cat ocupa scorul pe x
    sfVector2f score2_pos = {WIDTH / 2 + score_offset - 25, 20};
    sfText_setPosition(score_text1, score1_pos);
    sfText_setPosition(score_text2, score2_pos);

    sfText_setCharacterSize(score_text1, 72);
    sfText_setCharacterSize(score_text2, 72);
    sfText_setString(score_text1, "0");
    sfText_setString(score_text2, "0");

    while(sfRenderWindow_isOpen(window)) {
        if(sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window);
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfColor_fromRGB(60, 60, 60));
        // fileu
        for(int i = 0; i < n_points - 1; i++) {
            sfRenderWindow_drawRectangleShape(window, middle[i], NULL);
        }
        sfRenderWindow_drawRectangleShape(window, walls, NULL);
        sfRenderWindow_drawText(window, score_text1, NULL);
        sfRenderWindow_drawText(window, score_text2, NULL);
        sfRenderWindow_drawRectangleShape(window, player1, NULL);
        sfRenderWindow_drawRectangleShape(window, player2, NULL);
        sfRenderWindow_display(window);
    }

    sfRectangleShape_destroy(player1);
    sfRectangleShape_destroy(player2);

    // fileu
    for(int i = 0; i < n_points; i++)
        sfRectangleShape_destroy(middle[i]);
    free(middle);

    sfRectangleShape_destroy(walls);
    sfText_destroy(score_text1);
    sfText_destroy(score_text2);
    sfFont_destroy(scoreFont);

    sfRenderWindow_destroy(window);
    return 0;
}
