NAME = philo
SRCS = src/main.c $(SRCS_FOLDER)

SRCS_FOLDER = src/launch_box_data.c src/read_input.c src/time.c src/utils.c src/weave_threads.c src/reporting.c src/activity.c

OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g -O2
# -Werror
#-g -fsanitize=thread      (CHECKS FOR DATA RACES)
#-g -fsanitize=address
HEADER = includes
CC = clang

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $< -I $(HEADER)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
