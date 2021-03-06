NAME = doom-nukem

SRC_PATH = src

SRC_NAME =	main.c			\
			ttf.c							\
			ttf2.c							\
			ttf3.c							\
			time.c							\
			message.c						\
			menu.c							\
			sounds.c						\
			save_map.c						\
			save_map2.c						\
			save_map3.c						\
			launching/load_storm_anim.c 	\
			launching/load_storm_anim_2.c 	\
			launching/load_wp_anim.c 		\
			launching/load_anims.c			\
			launching/load_anims_2.c		\
			launching/structs_initialize.c	\
			launching/structs_initialize_2.c\
			launching/structs_initialize_3.c\
			editor/editor_launcher.c		\
			editor/actions.c				\
			editor/selected.c				\
			editor/selected_2.c				\
			editor/selected_3.c				\
			editor/images.c					\
			editor/editor.c					\
			editor/editor_2.c				\
			editor/errors.c					\
			editor/editor_controls.c		\
			editor/editor_controls_2.c		\
			editor/editor_controls_3.c		\
			editor/mouse_left_click.c		\
			editor/mouse_left_release.c		\
			editor/mouse_move.c				\
			editor/lines.c					\
			editor/ft_lines.c				\
			editor/parsing.c				\
			editor/parsing2.c				\
			editor/parsing3.c				\
			editor/parsing4.c				\
			editor/parsing5.c				\
			editor/parsing6.c				\
			editor/chainlist.c				\
			editor/chainlist2.c				\
			editor/utils_1.c				\
			editor/utils_2.c				\
			editor/utils_3.c				\
			editor/utils_4.c				\
			editor/anchors_general.c		\
			editor/mode_vertex.c			\
			editor/mode_vertex2.c			\
			editor/mode_vertex3.c			\
			editor/mode_sprite.c			\
			editor/mode_sprite2.c			\
			editor/mode_sprite3.c			\
			editor/mode_sprite4.c			\
			editor/remove_sectors.c			\
			editor/wall.c					\
			editor/wall2.c					\
			editor/wall3.c					\
			editor/mode_deplacement.c		\
			editor/ft_is_in_sector.c		\
			editor/ft_is_in_sector2.c		\
			editor/display_map.c			\
			editor/player.c					\
			editor/mode_floor.c				\
			editor/free.c					\
			editor/free_sounds.c			\
			editor/free_images.c			\
			editor/parser_tga.c				\
			editor/edit_portals.c			\
			editor/edit_portals2.c			\
			editor/edit_portals3.c			\
			editor/list_utils.c				\
			editor/polygon_center.c			\
			editor/sector_sens.c			\
			editor/sector_sens2.c			\
			game/texture.c					\
			game/texture2.c					\
			game/game_launcher.c			\
			game/game_controls.c			\
			game/visu.c						\
			game/visu2.c					\
			game/visu_portal.c				\
			game/visu_portal2.c				\
			game/visu_drawing.c				\
			game/create_new_wall.c			\
			game/ft_limit_ceiling_floor.c	\
			editor/ft_find_intersection.c	\
			game/utils_2.c					\
			game/hud.c						\
			game/hud_2.c					\
			game/anim.c						\
			game/anim_2.c					\
			game/sprite.c					\
			game/sprite2.c					\
			game/sprite3.c					\
			game/fire_mode.c				\
			game/skybox.c					\
			game/ia.c						\
			game/collisions.c				\
			game/collisions_2.c				\
			game/walls.c					\
			game/teleport.c					\
			game/draw_wall.c				\
			game/create_wall.c				\
			game/fly.c						\
			game/multithreading.c


LIBINC = -I libft/includes/ -I /usr/local/include/ -MMD

LDFLAGS = -L libft/ -lft  -L /usr/local/include/ -lm -pthread

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj

HEADER_PATH = includes/
HEADER_NAME = doom.h

SDL2 = SDL2

ID = $(shell id -un)

SDLINCL = $(shell $(ABSOLUTE_DIR)/SDL2/bin/sdl2-config --cflags)
SDLFLAGS =  $(SDLINCL) $(shell $(ABSOLUTE_DIR)/SDL2/bin/sdl2-config --libs)

MIXINCL = -I ./SDL2/include/SDL2/
MIXFLAGS = $(MIXINCL) -L./SDL2/lib -lSDL2_mixer -lSDL2_ttf

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

ABSOLUTE_DIR = $(shell pwd)
SDL2_SRC = $(ABSOLUTE_DIR)/SDL2-2.0.9
SDL2_MIX_SRC = $(ABSOLUTE_DIR)/SDL2_mixer-2.0.4
SDL2_TTF_SRC = $(ABSOLUTE_DIR)/SDL2_ttf-2.0.15

all: $(NAME)

sdl :
	if test ! -f SDL_2.0.9.tar.gz; \
	then curl http://libsdl.org/release/SDL2-2.0.9.tar.gz -o SDL_2.0.9.tar.gz; \
	fi
	if test ! -d SDL2-2.0.9; \
	then tar xvf SDL_2.0.9.tar.gz; \
	fi
	mkdir -p SDL2 2> /dev/null || true
	mkdir -p SDL2/build 2> /dev/null || true
	cd SDL2/build; \
		$(SDL2_SRC)/configure --prefix $(ABSOLUTE_DIR)/SDL2; \
		@make -j6; \
		make install;
	cd $(ABSOLUTE_DIR)
	if test ! -f SDL2_mixer-2.0.4.tar.gz; \
	then curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -o SDL2_mixer-2.0.4.tar.gz; \
	fi
	if test ! -d SDL2_mixer-2.0.4; \
	then tar xvf SDL2_mixer-2.0.4.tar.gz; \
	fi
	cd SDL2/build; \
		$(SDL2_MIX_SRC)/configure --prefix $(ABSOLUTE_DIR)/SDL2; \
		@make -j6; \
		make install;
	cd $(ABSOLUTE_DIR)
	if test ! -f SDL2_ttf-2.0.15.tar.gz; \
	then curl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -o SDL2_ttf-2.0.15.tar.gz; \
	fi
	if test ! -d SDL2_ttf-2.0.15; \
	then tar xvf SDL2_ttf-2.0.15.tar.gz; \
	fi
	cd SDL2/build; \
		$(SDL2_TTF_SRC)/configure --prefix $(ABSOLUTE_DIR)/SDL2; \
		@make -j6; \
		make install;

https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz

$(NAME): $(OBJ)
	make -C libft/
	# @$(CC) $(CFLAGS) $(LDFLAGS) $(SDLFLAGS) $(MIXFLAGS) $(MIXINCL) $(LDLIBS) $(SDLFMK) $^ -o $@
	$(CC) $(CFLAGS) $(MIXINCL) $(SDLINCL) $(LIBINC) $(SDLFMK) $^ -o $@ $(SDLFLAGS) $(MIXFLAGS) $(LDFLAGS)
	echo "[32m Doom_nukem OK ✓ [0m"
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LIBINC) -I $(HEADER_PATH) $(SDLINCL) $(MIXINCL) -o $@ -c $<

$(SDL2):
	make sdl

$(OBJ_PATH): $(SDL2)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/editor 2> /dev/null || true
	@mkdir $(OBJ_PATH)/launching 2> /dev/null || true
	@mkdir $(OBJ_PATH)/game 2> /dev/null || true

sdlclean:
	@rm -rf $(SDL2_SRC) $(SDL2_MIX_SRC) $(SDL2_TTF_SRC) SDL_2.0.9.tar.gz SDL2_mixer-2.0.4.tar.gz SDL2_ttf-2.0.15.tar.gz SDL2
	@echo "[32m Sdlclean OK ✓ [0m"

clean:
	@make clean -C libft/
	@rm -f $(OBJ) $(OBJ:.o=.d)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@echo "[32m Clean OK ✓ [0m"

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: make clean fclean re sdl sdlclean

-include $(OBJ:.o=.d)
